/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "collect4output.h"

#include "scribus.h"
#include "scribusdoc.h"
#include "scribuscore.h"
#include "util.h"
#include "prefscontext.h"
#include "prefsfile.h"
#include "prefsmanager.h"
#include "commonstrings.h"
#include "undomanager.h"
#include "filewatcher.h"
#include "pageitem.h"
#ifdef HAVE_OSG
	#include "pageitem_osgframe.h"
#endif
#include "scraction.h"
#include "scpattern.h"
#include "util_file.h"

#include <QDir>
#include <QMap>
#include <QMessageBox>
#include <QProgressBar>
#include <QString>

CollectForOutput::CollectForOutput(ScribusDoc* doc, QString outputDirectory, bool withFonts, bool withProfiles, bool compressDoc)
	: QObject(ScCore),
	m_Doc(0),
	m_outputDirectory(QString::null),
	profileCount(0),
	itemCount(0),
	fontCount(0),
	patternCount(0),
	uiCollect(false)
{
	m_Doc=doc;
	if (outputDirectory!=QString::null)
		m_outputDirectory=outputDirectory;
	m_compressDoc = compressDoc;
	m_withFonts = withFonts;
	m_withProfiles = withProfiles;
	dirs = PrefsManager::instance()->prefsFile->getContext("dirs");
	collectedFiles.clear();

	if (m_withFonts)
		fontCount = m_Doc->UsedFonts.count();
	if (m_withProfiles)
		m_Doc->getUsedProfiles(docProfiles);
	profileCount = m_withProfiles ? docProfiles.count() : 0;
	itemCount= m_Doc->MasterItems.count()+m_Doc->DocItems.count()+m_Doc->FrameItems.count();
	patterns = m_Doc->getUsedPatterns();
	patternCount=patterns.count();
}

bool CollectForOutput::newDirDialog()
{
	QString curDir = QDir::currentPath();
	if (ScCore->usingGUI())
	{
		QString wdir = ".";
		QString prefsDocDir = PrefsManager::instance()->documentDir();
		if (!prefsDocDir.isEmpty())
			wdir = dirs->get("collect", prefsDocDir);
		else
			wdir = dirs->get("collect", ".");
		m_outputDirectory = ScCore->primaryMainWindow()->CFileDialog(wdir, tr("Choose a Directory"), "", "", fdDirectoriesOnly, &m_compressDoc, &m_withFonts, &m_withProfiles);
	}
	if (m_outputDirectory.isEmpty())
		return false;
	if (!m_outputDirectory.endsWith("/"))
		m_outputDirectory += "/";

	docProfiles.clear();
	if (m_withProfiles)
		m_Doc->getUsedProfiles(docProfiles);
	fontCount = m_withFonts ? m_Doc->UsedFonts.count() : 0;
	profileCount = m_withProfiles ? docProfiles.count() : 0;

	QStringList directories;
	directories.append(m_outputDirectory);
	directories.append(m_outputDirectory + "images/");
	if (m_withFonts)
		directories.append(m_outputDirectory + "fonts/");
	if (m_withProfiles)
		directories.append(m_outputDirectory + "profiles/");

	for (int i = 0; i < directories.count(); ++i)
	{
		QDir dir(directories[i]);
		if (dir.exists()) continue;
		
		bool created = dir.mkpath(directories[i]);
		if (!created)
		{
			QMessageBox::warning(ScCore->primaryMainWindow(), CommonStrings::trWarning,
			                     "<qt>" + tr("Cannot create directory:\n%1").arg(directories[i]) + "</qt>",
			                     CommonStrings::tr_OK);
			return false;
		}
	}
	return true;
}

QString CollectForOutput::collect(QString &newFileName)
{
	if (!newDirDialog())
		return "Collect cancelled or unable to create collect destination directory";
	ScCore->fileWatcher->forceScan();
	ScCore->fileWatcher->stop();
	dirs->set("collect", m_outputDirectory.left(m_outputDirectory.lastIndexOf("/",-2)));
	ScCore->primaryMainWindow()->setStatusBarInfoText( tr("Collecting..."));

	if (!collectItems())
	{
		QString errorMsg( tr("Cannot collect all files for output for file:\n%1").arg(newName) );
		QMessageBox::warning(ScCore->primaryMainWindow(), CommonStrings::trWarning,
							 "<qt>" + errorMsg + "</qt>",
							 CommonStrings::tr_OK);
		return errorMsg;
	}

	if (m_withFonts)
		collectFonts();
	if (m_withProfiles)
		collectProfiles();

	/* collect document must go last because of image paths changes in collectItems() */
	if (!collectDocument())
	{
		QString errorMsg( tr("Cannot collect the file: \n%1").arg(newName) );
		QMessageBox::warning(ScCore->primaryMainWindow(), CommonStrings::trWarning, "<qt>" + errorMsg + "</qt>", CommonStrings::tr_OK);
		return errorMsg;
	}

	QDir::setCurrent(m_outputDirectory);
	ScCore->primaryMainWindow()->updateActiveWindowCaption(newName);
	UndoManager::instance()->renameStack(newName);
	ScCore->primaryMainWindow()->scrActions["fileSave"]->setEnabled(false);
	ScCore->primaryMainWindow()->scrActions["fileRevert"]->setEnabled(false);
	ScCore->primaryMainWindow()->updateRecent(newName);
	ScCore->primaryMainWindow()->setStatusBarInfoText("");
	ScCore->primaryMainWindow()->mainWindowProgressBar->reset();
	ScCore->fileWatcher->start();
	collectedFiles.clear();
	newFileName = newName;

	return QString::null;
}

bool CollectForOutput::collectDocument()
{
	QFileInfo fi = QFileInfo(m_outputDirectory);
	newName = m_outputDirectory;
	if (!fi.exists())
		return false;
	if (!fi.isDir() || !fi.isWritable())
		return false;

	if ((m_Doc->hasName) && (!m_Doc->isConverted))
	{
		QFileInfo fis(m_Doc->DocName);
		newName += fis.fileName();
	}
	else
		newName += m_Doc->DocName+".sla";

	m_Doc->hasName = true;
	if (m_compressDoc)
	{
		if (!newName.endsWith(".gz"))
			newName += ".gz";
	}
	else
	{
		if (newName.endsWith(".gz"))
			newName = newName.remove(".gz");
	}

	if (!overwrite(ScCore->primaryMainWindow(), newName))
		return false;
	if (!ScCore->primaryMainWindow()->DoFileSave(newName))
		return false;
	return true;
}

bool CollectForOutput::collectItems()
{
	uint counter = 0;
	int c=0;
	QList<PageItem*> allItems;
	PageItem* ite = NULL;
	for (uint lc = 0; lc < 2; ++lc)
	{
		switch (lc)
		{
			case 0:
				counter = m_Doc->MasterItems.count();
				break;
			case 1:
				counter = m_Doc->DocItems.count();
				break;
		}
		for (uint b = 0; b < counter; ++b)
		{
			switch (lc)
			{
				case 0:
					ite = m_Doc->MasterItems.at(b);
					break;
				case 1:
					ite = m_Doc->DocItems.at(b);
					break;
			}
			if (ite->isGroup())
				allItems = ite->getItemList();
			else
				allItems.append(ite);
			for (int ii = 0; ii < allItems.count(); ii++)
			{
				ite = allItems.at(ii);
				processItem(ite);
			}
			allItems.clear();
			if (uiCollect)
				emit itemsCollected(c++);
		}
	}
	for (QHash<short, PageItem*>::iterator itf = m_Doc->FrameItems.begin(); itf != m_Doc->FrameItems.end(); ++itf)
	{
		PageItem *it = itf.value();
		if (it->isGroup())
			allItems = it->asGroupFrame()->getItemList();
		else
			allItems.append(it);
		for (int ii = 0; ii < allItems.count(); ii++)
		{
			it = allItems.at(ii);
			processItem(it);
		}
		allItems.clear();
		if (uiCollect)
			emit itemsCollected(c++);
	}
	for (int c = 0; c < patterns.count(); ++c)
	{
		ScPattern pa = m_Doc->docPatterns[patterns[c]];
		for (int o = 0; o < pa.items.count(); o++)
		{
			ite = pa.items.at(o);
			if (ite->isGroup())
				allItems = ite->getItemList();
			else
				allItems.append(ite);
			for (int ii = 0; ii < allItems.count(); ii++)
			{
				ite = allItems.at(ii);
				processItem(ite);
			}
			allItems.clear();
		}
		if (uiCollect)
			emit patternsCollected(c);
	}
	return true;
}

void CollectForOutput::processItem(PageItem *ite)
{
	if (ite->asImageFrame())
	{
		/* hack for subsequent c4o "./" -> "/doc/full/path" */
		if (!ite->isInlineImage)
		{
			QString ofName(ite->Pfile);
			QFileInfo itf = QFileInfo(ofName);
			if (!itf.exists())
			{
				ofName = QDir::toNativeSeparators(PrefsManager::instance()->documentDir() + "/" + ofName);
				itf.setFile(ofName);
			}
		// end of hack
			if (itf.exists())
			{
				QString oldFile = ofName;
				ite->Pfile = collectFile(oldFile, itf.fileName());
				ScCore->fileWatcher->removeFile(oldFile);
				ScCore->fileWatcher->addFile(ite->Pfile);
			}
		}
	}
#ifdef HAVE_OSG
	if (ite->asOSGFrame())
	{
		PageItem_OSGFrame *osgframe = ite->asOSGFrame();
		QString ofName(osgframe->modelFile);
		QFileInfo itf = QFileInfo(ofName);
		if (!itf.exists())
		{
			ofName = QDir::toNativeSeparators(PrefsManager::instance()->documentDir() + "/" + ofName);
			itf.setFile(ofName);
		}
		if (itf.exists())
		{
			QString oldFile = ofName;
			osgframe->modelFile = collectFile(oldFile, itf.fileName());
		}
	}
#endif
	if (ite->asTextFrame())
	{
		if (ite->isAnnotation())
		{
			QFileInfo itf;
			if (!ite->Pfile.isEmpty())
			{
				if (!ite->isInlineImage)
				{
					itf = QFileInfo(ite->Pfile);
					if (itf.exists())
					{
						QString oldFile = ite->Pfile;
						ite->Pfile = collectFile(oldFile, itf.fileName());
						ScCore->fileWatcher->removeFile(oldFile);
						ScCore->fileWatcher->addFile(ite->Pfile);
					}
				}
			}
			if (!ite->Pfile2.isEmpty())
			{
				itf = QFileInfo(ite->Pfile2);
				if (itf.exists())
					ite->Pfile2 = collectFile(ite->Pfile2, itf.fileName());
			}
			if (!ite->Pfile3.isEmpty())
			{
				itf = QFileInfo(ite->Pfile3);
				if (itf.exists())
					ite->Pfile3 = collectFile(ite->Pfile3, itf.fileName());
			}
		}
	}
}

bool CollectForOutput::collectFonts()
{
	PrefsManager *prefsManager = PrefsManager::instance();
	QMap<QString,int>::Iterator it3;
	QMap<QString,int>::Iterator it3end = m_Doc->UsedFonts.end();
	int c=0;
	for (it3 = m_Doc->UsedFonts.begin(); it3 != it3end; ++it3)
	{
		QFileInfo itf(prefsManager->appPrefs.fontPrefs.AvailFonts[it3.key()].fontFilePath());
		copyFileAtomic(prefsManager->appPrefs.fontPrefs.AvailFonts[it3.key()].fontFilePath(), m_outputDirectory + "fonts/" + itf.fileName());
		if (prefsManager->appPrefs.fontPrefs.AvailFonts[it3.key()].type() == ScFace::TYPE1)
		{
			QStringList metrics;
			QString fontDir  = itf.absolutePath();
			QString fontFile = itf.fileName();
			metrics += findFontMetrics(fontDir, fontFile);
			if ( metrics.size() <= 0 )
			{
				QDir dir;
				if (dir.exists(fontDir + "/AFMs"))
					metrics += findFontMetrics(fontDir + "/AFMs", fontFile);
				if (dir.exists(fontDir + "/afm") && metrics.size() <= 0)
					metrics += findFontMetrics(fontDir + "/afm", fontFile);
				if (dir.exists(fontDir + "/Pfm") && metrics.size() <= 0)
					metrics += findFontMetrics(fontDir + "/Pfm", fontFile);
				if (dir.exists(fontDir + "/pfm") && metrics.size() <= 0)
					metrics += findFontMetrics(fontDir + "/pfm", fontFile);
			}
			for (int a = 0; a < metrics.size(); a++)
			{
				QString origAFM = metrics[a];
				QFileInfo fi(origAFM);
				copyFileAtomic(origAFM, m_outputDirectory + "fonts/" + fi.fileName());
			}
		}
		if (uiCollect)
			emit fontsCollected(c++);
	}
	return true;
}

QStringList CollectForOutput::findFontMetrics(const QString& baseDir, const QString& baseName) const
{
	QStringList metricsFiles;
	QString     basePath = baseDir + "/" + baseName;
	QString     afnm(basePath);
	afnm.chop(3);

	// Look for afm files
	QString afmName(afnm+"afm");
	if(QFile::exists(afmName))
		metricsFiles.append(afmName);
	else
	{
		afmName = afnm+"Afm";
		if(QFile::exists(afmName))
			metricsFiles.append(afmName);
		else
		{
			afmName = afnm+"AFM";
			if(QFile::exists(afmName))
				metricsFiles.append(afmName);
		}
	}
	// Look for pfm files
	QString pfmName(afnm+"pfm");
	if(QFile::exists(pfmName))
		metricsFiles.append(pfmName);
	else
	{
		pfmName = afnm+"Pfm";
		if(QFile::exists(pfmName))
			metricsFiles.append(pfmName);
		else
		{
			afmName = afnm+"PFM";
			if(QFile::exists(pfmName))
				metricsFiles.append(pfmName);
		}
	}
	return metricsFiles;
}

bool CollectForOutput::collectProfiles()
{
	int c = 0;
	ProfilesL::Iterator itend = docProfiles.end();
	for (ProfilesL::Iterator it = docProfiles.begin(); it != itend; ++it)
	{
		QString profileName(it.key());
		QString profilePath(it.value());
		copyFileAtomic(profilePath, m_outputDirectory + "profiles/" + QFileInfo(profilePath).fileName());
		if (uiCollect)
			emit profilesCollected(c++);
	}
	return true;
}

QString CollectForOutput::collectFile(QString oldFile, QString newFile)
{
	uint cnt = 1;
	bool copy = true;

	while (collectedFiles.contains(newFile))
	{
		// overwrite only different sources
		if (collectedFiles[newFile] == oldFile)
		{
			copy = false;
			break;
		}
		QFileInfo fi(newFile);
		QString basename = fi.baseName().left(fi.baseName().lastIndexOf("_"));
		newFile = QString("%1_%2.%3").arg(basename).arg(cnt).arg(fi.completeSuffix());
		++cnt;
	}
	if (copy)
	{
		copyFileAtomic(oldFile, m_outputDirectory + "images/" + newFile);
	}
	collectedFiles[newFile] = oldFile;
	return m_outputDirectory + "images/" + newFile;
}
