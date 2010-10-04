/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
	copyright            : (C) 2006 by Craig Bradney
	email                : cbradney@zip.com.au
***************************************************************************/

#include "colorsetmanager.h"
#include "scpaths.h"
#include "util.h"
#include "commonstrings.h"
#include "prefsstructs.h"
#include <QDomElement>
#include <QTextStream>
#include <QByteArray>

ColorSetManager::ColorSetManager()
{
}

ColorSetManager::~ColorSetManager()
{
}

void ColorSetManager::initialiseDefaultPrefs(struct ApplicationPrefs& appPrefs)
{
	QString defaultSwatch = ScPaths::instance().libDir() + "swatches/" + "Scribus_Basic.xml";
	QFile fiC(defaultSwatch);
	if (!fiC.exists())
	{
		appPrefs.colorPrefs.DColors.insert("White", ScColor(0, 0, 0, 0));
		appPrefs.colorPrefs.DColors.insert("Black", ScColor(0, 0, 0, 255));
		ScColor cc = ScColor(255, 255, 255, 255);
		cc.setRegistrationColor(true);
		appPrefs.colorPrefs.DColors.insert("Registration", cc);
		appPrefs.colorPrefs.DColors.insert("Blue", ScColor(255, 255, 0, 0));
		appPrefs.colorPrefs.DColors.insert("Cyan", ScColor(255, 0, 0, 0));
		appPrefs.colorPrefs.DColors.insert("Green", ScColor(255, 0, 255, 0));
		appPrefs.colorPrefs.DColors.insert("Red", ScColor(0, 255, 255, 0));
		appPrefs.colorPrefs.DColors.insert("Yellow", ScColor(0, 0, 255, 0));
		appPrefs.colorPrefs.DColors.insert("Magenta", ScColor(0, 255, 0, 0));
		appPrefs.colorPrefs.DColorSet = "Scribus_Small";
	}
	else
	{
		if (fiC.open(QIODevice::ReadOnly))
		{
			QString ColorEn, Cname;
			int Rval, Gval, Bval;
			QTextStream tsC(&fiC);
			ColorEn = tsC.readLine();
			if (ColorEn.startsWith("<?xml version="))
			{
				QByteArray docBytes("");
				loadRawText(defaultSwatch, docBytes);
				QString docText("");
				docText = QString::fromUtf8(docBytes);
				QDomDocument docu("scridoc");
				docu.setContent(docText);
				ScColor lf = ScColor();
				QDomElement elem = docu.documentElement();
				QDomNode PAGE = elem.firstChild();
				while(!PAGE.isNull())
				{
					QDomElement pg = PAGE.toElement();
					if(pg.tagName()=="COLOR" && pg.attribute("NAME")!=CommonStrings::None)
					{
						if (pg.hasAttribute("CMYK"))
							lf.setNamedColor(pg.attribute("CMYK"));
						else
							lf.fromQColor(QColor(pg.attribute("RGB")));
						if (pg.hasAttribute("Spot"))
							lf.setSpotColor(static_cast<bool>(pg.attribute("Spot").toInt()));
						else
							lf.setSpotColor(false);
						if (pg.hasAttribute("Register"))
							lf.setRegistrationColor(static_cast<bool>(pg.attribute("Register").toInt()));
						else
							lf.setRegistrationColor(false);
						appPrefs.colorPrefs.DColors.insert(pg.attribute("NAME"), lf);
					}
					PAGE=PAGE.nextSibling();
				}
			}
			else
			{
				while (!tsC.atEnd())
				{
					ColorEn = tsC.readLine();
					QTextStream CoE(&ColorEn, QIODevice::ReadOnly);
					CoE >> Rval;
					CoE >> Gval;
					CoE >> Bval;
					CoE >> Cname;
					ScColor tmp;
					tmp.setColorRGB(Rval, Gval, Bval);
					appPrefs.colorPrefs.DColors.insert(Cname, tmp);
				}
			}
			fiC.close();
		}
		appPrefs.colorPrefs.DColorSet = "Scribus Basic";
	}
}

void ColorSetManager::findPaletteLocations()
{
	paletteLocations.clear();
	QStringList locations=ScPaths::instance().getSystemCreateSwatchesDirs();
	locations << ScPaths::instance().shareDir()+"swatches/";
	locations << ScPaths::instance().getDirsFromEnvVar("XDG_DATA_HOME", "scribus/swatches/");
	for ( QStringList::Iterator it = locations.begin(); it != locations.end(); ++it )
	{
		QFile paletteDir(*it);
		if (paletteDir.exists())
		{
			paletteLocations << (*it);
			paletteLocationLocks.insert((*it), false);
		}
	}
	QStringList xdgSysLocations=ScPaths::instance().getDirsFromEnvVar("XDG_DATA_DIRS", "scribus/swatches/");
	for ( QStringList::Iterator it = xdgSysLocations.begin(); it != xdgSysLocations.end(); ++it )
	{
		QFile paletteDir(*it);
		if (paletteDir.exists())
		{
			paletteLocations << (*it);
			paletteLocationLocks.insert((*it), true);
		}
	}
}

void ColorSetManager::findPalettes()
{
	palettes.clear();
	QString path;
	for ( QStringList::Iterator it = paletteLocations.begin(); it != paletteLocations.end(); ++it )
	{
		path=(*it);
		QDir dir(path , "*.xml *.gpl *.eps *.ai *.sla *.soc", QDir::Name, QDir::Files | QDir::NoSymLinks);
		if (dir.exists() && (dir.count() != 0))
		{
			for (uint i = 0; i < dir.count(); ++i) 
			{
				QFileInfo file(path + dir[i]);
				QString setName=file.baseName();
				setName.replace("_", " ");
				palettes.insert(setName, file.absoluteFilePath());
			}
		}
	}
}

QStringList ColorSetManager::paletteNames( )
{
	QStringList nameList;
	for ( QMap<QString, QString>::Iterator it = palettes.begin(); it != palettes.end(); ++it )
		nameList << it.key();
	return nameList;
}

QString ColorSetManager::paletteFileFromName(const QString& paletteName)
{
	if (palettes.contains(paletteName))
		return palettes[paletteName];
	return QString();
}

bool ColorSetManager::paletteLocationLocked(const QString& palettePath)
{
	return (paletteLocationLocks.contains(palettePath) && paletteLocationLocks.value(palettePath)==true);
}

