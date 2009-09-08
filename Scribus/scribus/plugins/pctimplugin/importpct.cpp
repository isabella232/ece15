/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#include <QByteArray>
#include <QCursor>
#include <QDrag>
#include <QFile>
#include <QList>
#include <QMimeData>
#include <QRegExp>
#include <QStack>
#include <QDebug>

#include <cmath>
#include <cstdlib>

#include "commonstrings.h"
#include "ui/customfdialog.h"
#include "importpct.h"
#include "loadsaveplugin.h"
#include "ui/missing.h"
#include "ui/multiprogressdialog.h"
#include "pagesize.h"
#include "prefscontext.h"
#include "prefsfile.h"
#include "prefsmanager.h"
#include "prefsmanager.h"
#include "prefstable.h"
#include "ui/propertiespalette.h"
#include "rawimage.h"
#include "scclocale.h"
#include "sccolorengine.h"
#include "scconfig.h"
#include "scmimedata.h"
#include "scpaths.h"
#include "scpattern.h"
#include "scpattern.h"
#include "scribus.h"
#include "scribusXml.h"
#include "scribuscore.h"
#include "sctextstream.h"
#include "selection.h"
#include "undomanager.h"
#include "util.h"
#include "util_formats.h"
#include "util_icon.h"
#include "util_math.h"

extern SCRIBUS_API ScribusQApp * ScQApp;

PctPlug::PctPlug(ScribusDoc* doc, int flags)
{
	tmpSel=new Selection(this, false);
	m_Doc=doc;
	interactive = (flags & LoadSavePlugin::lfInteractive);
}

bool PctPlug::import(QString fNameIn, const TransactionSettings& trSettings, int flags, bool showProgress)
{
	QString fName = fNameIn;
	bool success = false;
	interactive = (flags & LoadSavePlugin::lfInteractive);
	importerFlags = flags;
	cancel = false;
	double x, y, b, h;
	bool ret = false;
	CustColors.clear();
	QFileInfo fi = QFileInfo(fName);
	if ( !ScCore->usingGUI() )
	{
		interactive = false;
		showProgress = false;
	}
	baseFile = QDir::cleanPath(QDir::toNativeSeparators(fi.absolutePath()+"/"));
	if ( showProgress )
	{
		ScribusMainWindow* mw=(m_Doc==0) ? ScCore->primaryMainWindow() : m_Doc->scMW();
		progressDialog = new MultiProgressDialog( tr("Importing: %1").arg(fi.fileName()), CommonStrings::tr_Cancel, mw );
		QStringList barNames, barTexts;
		barNames << "GI";
		barTexts << tr("Analyzing File:");
		QList<bool> barsNumeric;
		barsNumeric << false;
		progressDialog->addExtraProgressBars(barNames, barTexts, barsNumeric);
		progressDialog->setOverallTotalSteps(3);
		progressDialog->setOverallProgress(0);
		progressDialog->setProgress("GI", 0);
		progressDialog->show();
		connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelRequested()));
		qApp->processEvents();
	}
	else
		progressDialog = NULL;
/* Set default Page to size defined in Preferences */
	x = 0.0;
	y = 0.0;
	b = 0.0;
	h = 0.0;
	if (progressDialog)
	{
		progressDialog->setOverallProgress(1);
		qApp->processEvents();
	}
	parseHeader(fName, b, h);
	if (b == 0.0)
		b = PrefsManager::instance()->appPrefs.docSetupPrefs.pageWidth;
	if (h == 0.0)
		h = PrefsManager::instance()->appPrefs.docSetupPrefs.pageHeight;
	docWidth = b;
	docHeight = h;
	baseX = 0;
	baseY = 0;
	if (!interactive || (flags & LoadSavePlugin::lfInsertPage))
	{
		m_Doc->setPage(docWidth, docHeight, 0, 0, 0, 0, 0, 0, false, false);
		m_Doc->addPage(0);
		m_Doc->view()->addPage(0, true);
		baseX = 0;
		baseY = 0;
	}
	else
	{
		if (!m_Doc || (flags & LoadSavePlugin::lfCreateDoc))
		{
			m_Doc=ScCore->primaryMainWindow()->doFileNew(docWidth, docHeight, 0, 0, 0, 0, 0, 0, false, false, 0, false, 0, 1, "Custom", true);
			ScCore->primaryMainWindow()->HaveNewDoc();
			ret = true;
			baseX = 0;
			baseY = 0;
			baseX = m_Doc->currentPage()->xOffset();
			baseY = m_Doc->currentPage()->yOffset();
		}
	}
	if ((!ret) && (interactive))
	{
		baseX = m_Doc->currentPage()->xOffset();
		baseY = m_Doc->currentPage()->yOffset();
	}
	if ((ret) || (!interactive))
	{
		if (docWidth > docHeight)
			m_Doc->PageOri = 1;
		else
			m_Doc->PageOri = 0;
		m_Doc->m_pageSize = "Custom";
	}
	Elements.clear();
	FPoint minSize = m_Doc->minCanvasCoordinate;
	FPoint maxSize = m_Doc->maxCanvasCoordinate;
	FPoint cOrigin = m_Doc->view()->canvasOrigin();
	m_Doc->setLoading(true);
	m_Doc->DoDrawing = false;
	m_Doc->view()->updatesOn(false);
	m_Doc->scMW()->ScriptRunning = true;
	qApp->changeOverrideCursor(QCursor(Qt::WaitCursor));
	QString CurDirP = QDir::currentPath();
	QDir::setCurrent(fi.path());
	if (convert(fName))
	{
		tmpSel->clear();
		QDir::setCurrent(CurDirP);
		if ((Elements.count() > 1) && (!(importerFlags & LoadSavePlugin::lfCreateDoc)))
		{
			bool isGroup = true;
			int firstElem = -1;
			if (Elements.at(0)->Groups.count() != 0)
				firstElem = Elements.at(0)->Groups.top();
			for (int bx = 0; bx < Elements.count(); ++bx)
			{
				PageItem* bxi = Elements.at(bx);
				if (bxi->Groups.count() != 0)
				{
					if (bxi->Groups.top() != firstElem)
						isGroup = false;
				}
				else
					isGroup = false;
			}
			if (!isGroup)
			{
				double minx = 99999.9;
				double miny = 99999.9;
				double maxx = -99999.9;
				double maxy = -99999.9;
				uint lowestItem = 999999;
				uint highestItem = 0;
				for (int a = 0; a < Elements.count(); ++a)
				{
					Elements.at(a)->Groups.push(m_Doc->GroupCounter);
					PageItem* currItem = Elements.at(a);
					lowestItem = qMin(lowestItem, currItem->ItemNr);
					highestItem = qMax(highestItem, currItem->ItemNr);
					double x1, x2, y1, y2;
					currItem->getVisualBoundingRect(&x1, &y1, &x2, &y2);
					minx = qMin(minx, x1);
					miny = qMin(miny, y1);
					maxx = qMax(maxx, x2);
					maxy = qMax(maxy, y2);
				}
				double gx = minx;
				double gy = miny;
				double gw = maxx - minx;
				double gh = maxy - miny;
				PageItem *high = m_Doc->Items->at(highestItem);
				int z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Rectangle, gx, gy, gw, gh, 0, m_Doc->itemToolPrefs.dBrush, m_Doc->itemToolPrefs.dPen, true);
				PageItem *neu = m_Doc->Items->takeAt(z);
				m_Doc->Items->insert(lowestItem, neu);
				neu->Groups.push(m_Doc->GroupCounter);
				neu->setItemName( tr("Group%1").arg(neu->Groups.top()));
				neu->AutoName = false;
				neu->isGroupControl = true;
				neu->groupsLastItem = high;
				neu->setTextFlowMode(PageItem::TextFlowDisabled);
				for (int a = 0; a < m_Doc->Items->count(); ++a)
				{
					m_Doc->Items->at(a)->ItemNr = a;
				}
				Elements.prepend(neu);
				m_Doc->GroupCounter++;
			}
		}
		m_Doc->DoDrawing = true;
		m_Doc->scMW()->ScriptRunning = false;
		m_Doc->setLoading(false);
		qApp->changeOverrideCursor(QCursor(Qt::ArrowCursor));
		if ((Elements.count() > 0) && (!ret) && (interactive))
		{
			if (flags & LoadSavePlugin::lfScripted)
			{
				bool loadF = m_Doc->isLoading();
				m_Doc->setLoading(false);
				m_Doc->changed();
				m_Doc->setLoading(loadF);
				m_Doc->m_Selection->delaySignalsOn();
				for (int dre=0; dre<Elements.count(); ++dre)
				{
					m_Doc->m_Selection->addItem(Elements.at(dre), true);
				}
				m_Doc->m_Selection->delaySignalsOff();
				m_Doc->m_Selection->setGroupRect();
				m_Doc->view()->updatesOn(true);
			}
			else
			{
				m_Doc->DragP = true;
				m_Doc->DraggedElem = 0;
				m_Doc->DragElements.clear();
				m_Doc->m_Selection->delaySignalsOn();
				for (int dre=0; dre<Elements.count(); ++dre)
				{
					m_Doc->DragElements.append(Elements.at(dre)->ItemNr);
					tmpSel->addItem(Elements.at(dre), true);
				}
				tmpSel->setGroupRect();
				ScriXmlDoc *ss = new ScriXmlDoc();
				ScElemMimeData* md = new ScElemMimeData();
				md->setScribusElem(ss->WriteElem(m_Doc, m_Doc->view(), tmpSel));
				delete ss;
				m_Doc->itemSelection_DeleteItem(tmpSel);
				m_Doc->view()->updatesOn(true);
				m_Doc->m_Selection->delaySignalsOff();
				// We must copy the TransationSettings object as it is owned
				// by handleObjectImport method afterwards
				TransactionSettings* transacSettings = new TransactionSettings(trSettings);
				m_Doc->view()->handleObjectImport(md, transacSettings);
				m_Doc->DragP = false;
				m_Doc->DraggedElem = 0;
				m_Doc->DragElements.clear();
			}
		}
		else
		{
			m_Doc->changed();
			m_Doc->reformPages();
			m_Doc->view()->updatesOn(true);
		}
		success = true;
	}
	else
	{
		QDir::setCurrent(CurDirP);
		m_Doc->DoDrawing = true;
		m_Doc->scMW()->ScriptRunning = false;
		m_Doc->view()->updatesOn(true);
		qApp->changeOverrideCursor(QCursor(Qt::ArrowCursor));
	}
	if (interactive)
		m_Doc->setLoading(false);
	//CB If we have a gui we must refresh it if we have used the progressbar
	if ((showProgress) && (!interactive))
		m_Doc->view()->DrawNew();
	return success;
}

PctPlug::~PctPlug()
{
	if (progressDialog)
		delete progressDialog;
	delete tmpSel;
}

void PctPlug::parseHeader(QString fName, double &b, double &h)
{
	QFile f(fName);
	if (f.open(QIODevice::ReadOnly))
	{
		QDataStream ts(&f);
		ts.device()->seek(512);
		quint16 pgX, pgY, pgW, pgH, dummy;
		ts >> dummy >> pgX >> pgY >> pgW >> pgH;
		b = pgW - pgX;
		h = pgH - pgY;
		f.close();
		qDebug() << "W" << pgW << "H" << pgH;
	}
}

bool PctPlug::convert(QString fn)
{
	QString tmp;
	CurrColorFill = "White";
	CurrFillShade = 100.0;
	CurrColorStroke = "Black";
	CurrStrokeShade = 100.0;
	Coords.resize(0);
	Coords.svgInit();
	LineW = 1.0;
	importedColors.clear();
	QList<PageItem*> gElements;
	groupStack.push(gElements);
	currentItemNr = 0;
	if(progressDialog)
	{
		progressDialog->setOverallProgress(2);
		progressDialog->setLabel("GI", tr("Generating Items"));
		qApp->processEvents();
	}
	QFile f(fn);
	if (f.open(QIODevice::ReadOnly))
	{
		oldDocItemCount = m_Doc->Items->count();
		int fSize = (int) f.size();
		if (progressDialog)
		{
			progressDialog->setTotalSteps("GI", fSize);
			qApp->processEvents();
		}
		QDataStream ts(&f);
		ts.device()->seek(522);
		quint16 vers;
		ts >> vers;
		if (vers == 0x1101)
		{
			pctVersion = 1;		// Pict Version 1
			parsePictVersion1(ts);
		}
		else
		{
			ts.skipRawData(4);	// skip the next 4 Bytes
			ts >> vers;		// read the version info
			if (vers == 0x0FFFE)
				pctVersion = 2;	// Pict Extended Version 2
			else if (vers == 0x0FFFF)
				pctVersion = 3;	// Pict Version 2
			else
			{
				if (progressDialog)
					progressDialog->close();
				f.close();
				return false;	// bail out, no Mac Pict
			}
			ts.skipRawData(22);
			parsePictVersion2(ts);
		}
		if (Elements.count() == 0)
		{
			if (importedColors.count() != 0)
			{
				for (int cd = 0; cd < importedColors.count(); cd++)
				{
					m_Doc->PageColors.remove(importedColors[cd]);
				}
			}
		}
		f.close();
	}
	if (progressDialog)
		progressDialog->close();
	return true;
}

void PctPlug::parsePictVersion1(QDataStream &ts)
{
	qDebug() << "Pict Version 1 not supported yet";
}

void PctPlug::parsePictVersion2(QDataStream &ts)
{
	QString notImpl;
	while (!ts.atEnd())
	{
		quint16 opCode, dataLen;
		ts >> opCode;
		QString tmp;
		tmp.sprintf("%04X", opCode);
		notImpl = "0x"+tmp;
		switch (opCode)
		{
			case 0x0000:		// NOP
				qDebug() << "NOP";
				break;
			case 0x0001:		// Clipping Region
				qDebug() << "Clipping Region";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0002:		// Background Pattern
				qDebug() << "Background Pattern";
				ts.skipRawData(8);
				break;
			case 0x0003:		// Text Font
				qDebug() << "Text Font";
				ts.skipRawData(2);
				break;
			case 0x0004:		// Text Style
				qDebug() << "Text Style";
				ts.skipRawData(1);
				break;
			case 0x0005:		// Text Mode
				qDebug() << "Text Mode";
				ts.skipRawData(2);
				break;
			case 0x0006:		// Extra Space
				qDebug() << "Extra Space";
				ts.skipRawData(4);
				break;
			case 0x0007:		// Pen Size
				qDebug() << "Pen Size";
				ts.skipRawData(4);
				break;
			case 0x0008:		// Pen Mode
				qDebug() << "Pen Mode";
				ts.skipRawData(2);
				break;
			case 0x0009:		// Pen Pattern
				qDebug() << "Pen Pattern";
				ts.skipRawData(8);
				break;
			case 0x000A:		// Fill Pattern
				qDebug() << "Fill Pattern";
				ts.skipRawData(8);
				break;
			case 0x000B:		// Oval Size
				qDebug() << "Oval Size";
				ts.skipRawData(4);
				break;
			case 0x000C:		// Origin
				qDebug() << "Origin";
				ts.skipRawData(4);
				break;
			case 0x000D:		// Text Size
				qDebug() << "Text Size";
				ts.skipRawData(2);
				break;
			case 0x000E:		// Foreground Color
				qDebug() << "Foreground Color";
				ts.skipRawData(4);
				break;
			case 0x000F:		// Background Color
				qDebug() << "Background Color";
				ts.skipRawData(4);
				break;
			case 0x0010:		// Text Ratio
				qDebug() << "Text Ratio";
				ts.skipRawData(8);
				break;
			case 0x0011:		// Version
				qDebug() << "Version";
				ts.skipRawData(1);
				break;
			case 0x0015:		// Fractional pen position
				qDebug() << "Fractional pen position";
				ts.skipRawData(2);
				break;
			case 0x0016:		// Extra char space
				qDebug() << "Extra char space";
				ts.skipRawData(2);
				break;
			case 0x0017:
			case 0x0018:
			case 0x0019:
				qDebug() << "Reserved by Apple";
				break;
			case 0x001A:		// Foreground color RGB
				handleColorRGB(ts, false);
				break;
			case 0x001B:		// Background color RGB
				handleColorRGB(ts, true);
				break;
			case 0x001C:		// Highlight mode
				qDebug() << "Highlight mode";
				break;
			case 0x001D:		// Highlight color RGB
				qDebug() << "Highlight color RGB";
				ts.skipRawData(6);
				break;
			case 0x001E:		// Use default highlight color
				qDebug() << "Use default highlight color";
				break;
			case 0x0020:		// Line
				qDebug() << "Line";
				ts.skipRawData(8);
				break;
			case 0x0021:		// Line To
				qDebug() << "Line To";
				ts.skipRawData(4);
				break;
			case 0x0022:		// Short Line
				qDebug() << "Short Line";
				ts.skipRawData(6);
				break;
			case 0x0023:		// Short Line To
				qDebug() << "Short Line To";
				ts.skipRawData(2);
				break;
			case 0x002D:		// Line justify
				qDebug() << "Line justify";
				ts.skipRawData(10);
				break;
			case 0x002E:		// Glyph state
				qDebug() << "Glyph state";
				ts.skipRawData(8);
				break;
			case 0x0030:		// Frame rect
				qDebug() << "Frame rect";
				ts.skipRawData(8);
				break;
			case 0x0031:		// Paint rect
				qDebug() << "Paint rect";
				ts.skipRawData(8);
				break;
			case 0x0032:		// Erase rect
				qDebug() << "Erase rect";
				ts.skipRawData(8);
				break;
			case 0x0033:		// Invert rect
				qDebug() << "Invert rect";
				ts.skipRawData(8);
				break;
			case 0x0034:		// Fill rect
				qDebug() << "Fill rect";
				ts.skipRawData(8);
				break;
			case 0x0035:
			case 0x0036:
			case 0x0037:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				ts.skipRawData(8);
				break;
			case 0x0038:		// Frame same rect
				qDebug() << "Frame same rect";
				break;
			case 0x0039:		// Paint same rect
				qDebug() << "Paint same rect";
				break;
			case 0x003A:		// Erase same rect
				qDebug() << "Erase same rect";
				break;
			case 0x003B:		// Invert same rect
				qDebug() << "Invert same rect";
				break;
			case 0x003C:		// Fill same rect
				qDebug() << "Fill same rect";
				break;
			case 0x003D:
			case 0x003E:
			case 0x003F:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				break;
			case 0x0040:		// Frame round rect
				qDebug() << "Frame round rect";
				ts.skipRawData(8);
				break;
			case 0x0041:		// Paint round rect
				qDebug() << "Paint round rect";
				ts.skipRawData(8);
				break;
			case 0x0042:		// Erase round rect
				qDebug() << "Erase round rect";
				ts.skipRawData(8);
				break;
			case 0x0043:		// Invert round rect
				qDebug() << "Invert round rect";
				ts.skipRawData(8);
				break;
			case 0x0044:		// Fill round rect
				qDebug() << "Fill round rect";
				ts.skipRawData(8);
				break;
			case 0x0045:
			case 0x0046:
			case 0x0047:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				ts.skipRawData(8);
				break;
			case 0x0048:		// Frame same round rect
				qDebug() << "Frame same round rect";
				break;
			case 0x0049:		// Paint same round rect
				qDebug() << "Paint same round rect";
				break;
			case 0x004A:		// Erase same round rect
				qDebug() << "Erase same round rect";
				break;
			case 0x004B:		// Invert same round rect
				qDebug() << "Invert same round rect";
				break;
			case 0x004C:		// Fill same round rect
				qDebug() << "Fill same round rect";
				break;
			case 0x004D:
			case 0x004E:
			case 0x004F:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				break;
			case 0x0050:		// Frame oval
				qDebug() << "Frame oval";
				ts.skipRawData(8);
				break;
			case 0x0051:		// Paint oval
				qDebug() << "Paint oval";
				ts.skipRawData(8);
				break;
			case 0x0052:		// Erase oval
				qDebug() << "Erase oval";
				ts.skipRawData(8);
				break;
			case 0x0053:		// Invert oval
				qDebug() << "Invert oval";
				ts.skipRawData(8);
				break;
			case 0x0054:		// Fill oval
				qDebug() << "Fill oval";
				ts.skipRawData(8);
				break;
			case 0x0055:
			case 0x0056:
			case 0x0057:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				ts.skipRawData(8);
				break;
			case 0x0058:		// Frame same oval
				qDebug() << "Frame same oval";
				break;
			case 0x0059:		// Paint same oval
				qDebug() << "Paint same oval";
				break;
			case 0x005A:		// Erase same oval
				qDebug() << "Erase same oval";
				break;
			case 0x005B:		// Invert same oval
				qDebug() << "Invert same oval";
				break;
			case 0x005C:		// Fill same oval
				qDebug() << "Fill same oval";
				break;
			case 0x005D:
			case 0x005E:
			case 0x005F:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				break;
			case 0x0060:		// Frame arc
				qDebug() << "Frame arc";
				ts.skipRawData(12);
				break;
			case 0x0061:		// Paint arc
				qDebug() << "Paint arc";
				ts.skipRawData(12);
				break;
			case 0x0062:		// Erase arc
				qDebug() << "Erase arc";
				ts.skipRawData(12);
				break;
			case 0x0063:		// Invert arc
				qDebug() << "Invert arc";
				ts.skipRawData(12);
				break;
			case 0x0064:		// Fill arc
				qDebug() << "Fill arc";
				ts.skipRawData(12);
				break;
			case 0x0065:
			case 0x0066:
			case 0x0067:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				ts.skipRawData(12);
				break;
			case 0x0068:		// Frame same arc
				qDebug() << "Frame same arc";
				ts.skipRawData(4);
				break;
			case 0x0069:		// Paint same arc
				qDebug() << "Paint same arc";
				ts.skipRawData(4);
				break;
			case 0x006A:		// Erase same arc
				qDebug() << "Erase same arc";
				ts.skipRawData(4);
				break;
			case 0x006B:		// Invert same arc
				qDebug() << "Invert same arc";
				ts.skipRawData(4);
				break;
			case 0x006C:		// Fill same arc
				qDebug() << "Fill same arc";
				ts.skipRawData(4);
				break;
			case 0x006D:
			case 0x006E:
			case 0x006F:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				ts.skipRawData(4);
				break;
			case 0x0070:		// Frame poly
			case 0x0071:		// Paint poly
			case 0x0072:		// Erase poly
			case 0x0073:		// Invert poly
			case 0x0074:		// Fill poly
				handlePolygon(ts, opCode);
				break;
			case 0x0075:
			case 0x0076:
			case 0x0077:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0078:		// Frame same poly
				qDebug() << "Frame same poly";
				break;
			case 0x0079:		// Paint same poly
				qDebug() << "Paint same poly";
				break;
			case 0x007A:		// Erase same poly
				qDebug() << "Erase same poly";
				break;
			case 0x007B:		// Invert same poly
				qDebug() << "Invert same poly";
				break;
			case 0x007C:		// Fill same poly
				qDebug() << "Fill same poly";
				break;
			case 0x007D:
			case 0x007E:
			case 0x007F:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				break;
			case 0x0080:		// Frame region
				qDebug() << "Frame region";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0081:		// Paint region
				qDebug() << "Paint region";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0082:		// Erase region
				qDebug() << "Erase region";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0083:		// Invert region
				qDebug() << "Invert region";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0084:		// Fill region
				qDebug() << "Fill region";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0085:
			case 0x0086:
			case 0x0087:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				ts >> dataLen;
				ts.skipRawData(dataLen-2);
				break;
			case 0x0088:		// Frame same region
				qDebug() << "Frame same region";
				break;
			case 0x0089:		// Paint same region
				qDebug() << "Paint same region";
				break;
			case 0x008A:		// Erase same region
				qDebug() << "Erase same region";
				break;
			case 0x008B:		// Invert same region
				qDebug() << "Invert same region";
				break;
			case 0x008C:		// Fill same region
				qDebug() << "Fill same region";
				break;
			case 0x008D:
			case 0x008E:
			case 0x008F:		// Reserved by Apple
				qDebug() << "Reserved by Apple";
				break;
			case 0x00FF:		// End of Pict
				qDebug() << "End of Pict";
				return;
				break;
			default:
				qDebug() << "Not implemented OpCode: " << notImpl;
				return;
				break;
		}
		if (progressDialog)
		{
			progressDialog->setProgress("GI", ts.device()->pos());
			qApp->processEvents();
		}
	}
}

void PctPlug::handleColorRGB(QDataStream &ts, bool back)
{
	QString tmpName = CommonStrings::None;
	ScColor tmp;
	ColorList::Iterator it;
	quint16 Rc, Gc, Bc;
	int redC, greenC, blueC, hR, hG, hB;
	ts >> Rc >> Gc >> Bc;
	redC = qRound((Rc / 65535.0) * 255.0);
	greenC = qRound((Gc / 65535.0) * 255.0);
	blueC = qRound((Bc / 65535.0) * 255.0);
	bool found = false;
	QColor c = QColor(redC, greenC, blueC);
	for (it = m_Doc->PageColors.begin(); it != m_Doc->PageColors.end(); ++it)
	{
		if (it.value().getColorModel() == colorModelRGB)
		{
			it.value().getRGB(&hR, &hG, &hB);
			if ((redC == hR) && (greenC == hG) && (blueC == hB))
			{
				tmpName = it.key();
				found = true;
				break;
			}
		}
	}
	if (!found)
	{
		tmp.setColorRGB(redC, greenC, blueC);
		tmp.setSpotColor(false);
		tmp.setRegistrationColor(false);
		tmpName = "FromPict"+c.name();
		m_Doc->PageColors.insert(tmpName, tmp);
		importedColors.append(tmpName);
	}
	if (back)
		CurrColorFill = tmpName;
	else
		CurrColorStroke = tmpName;
}

void PctPlug::handlePolygon(QDataStream &ts, quint16 opCode)
{
	quint16 polySize;
	ts >> polySize;				// read polygon size
	ts.skipRawData(8);			// skip bounding rect;
	polySize -= 14;				// subtract size count, bounding rect and first point from size
	quint16 x, y;
	ts >> y >> x;
	Coords.resize(0);
	Coords.svgInit();
	PageItem *ite;
	Coords.svgMoveTo(x, y);
	for(unsigned i = 0; i < polySize; i += 4)
	{
		ts >> y >> x;
		Coords.svgLineTo(x, y);
	}
	if (Coords.size() > 0)
	{
		int z;
		if (opCode == 0x0070)
			z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Unspecified, baseX, baseY, 10, 10, LineW, CommonStrings::None, CurrColorStroke, true);
		else
			z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Unspecified, baseX, baseY, 10, 10, LineW, CurrColorFill, CurrColorStroke, true);
		ite = m_Doc->Items->at(z);
		ite->PoLine = Coords.copy();
		ite->PoLine.translate(m_Doc->currentPage()->xOffset(), m_Doc->currentPage()->yOffset());
		finishItem(ite);
	}
}

void PctPlug::finishItem(PageItem* ite)
{
	ite->ClipEdited = true;
	ite->Frame = false;
	ite->FrameType = 3;
	ite->setFillShade(CurrFillShade);
	ite->setLineShade(CurrStrokeShade);
	FPoint wh = getMaxClipF(&ite->PoLine);
	ite->setWidthHeight(wh.x(),wh.y());
	ite->setTextFlowMode(PageItem::TextFlowDisabled);
	m_Doc->AdjustItemSize(ite);
	ite->OldB2 = ite->width();
	ite->OldH2 = ite->height();
	ite->updateClip();
	Elements.append(ite);
}
