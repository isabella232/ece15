/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "scribus13format.h"
#include "scribus13formatimpl.h"

#include "../../formatidlist.h"
#include "commonstrings.h"
#include "ui/missing.h"
#include "prefsmanager.h"
#include "scconfig.h"
#include "scribusdoc.h"
#include "scribusview.h"
#include "sctextstream.h"
#include "sccolorengine.h"
#include "undomanager.h"
#include "units.h"
#include "util.h"
#include "util_color.h"
#include "util_layer.h"
#include "util_math.h"
#include "util_text.h"
#include "scclocale.h"
#include "scgzfile.h"
#include "scribuscore.h"
#include <QCursor>
// #include <QDebug>
#include <QFileInfo>
#include <QByteArray>
#include <QDataStream>
#include <QApplication>
#include <QMessageBox>


// See scplugin.h and pluginmanager.{cpp,h} for detail on what these methods
// do. That documentatation is not duplicated here.
// Please don't implement the functionality of your plugin here; do that
// in scribus13formatimpl.h and scribus13formatimpl.cpp .

Scribus13Format::Scribus13Format() :
	LoadSavePlugin()
{
	// Set action info in languageChange, so we only have to do
	// it in one place. This includes registering file formats.
	languageChange();
}

Scribus13Format::~Scribus13Format()
{
	unregisterAll();
};

void Scribus13Format::languageChange()
{
	//(Re)register file formats.
	unregisterAll();
	registerFormats();
}

const QString Scribus13Format::fullTrName() const
{
	return QObject::tr("Scribus 1.3.0->1.3.3.x Support");
}

const ScActionPlugin::AboutData* Scribus13Format::getAboutData() const
{
	AboutData* about = new AboutData;
	Q_CHECK_PTR(about);
	about->authors = QString::fromUtf8(
			"Franz Schmid <franz@scribus.info>, "
			"The Scribus Team");
	about->shortDescription = tr("Scribus 1.3.x File Format Support");
	about->description = tr("Allows Scribus to read Scribus 1.3.0->1.3.3.x formatted files.");
	// about->version
	// about->releaseDate
	// about->copyright
	about->license = "GPL";
	return about;
}

void Scribus13Format::deleteAboutData(const AboutData* about) const
{
	Q_ASSERT(about);
	delete about;
}

void Scribus13Format::registerFormats()
{
	FileFormat fmt(this);
	fmt.trName = tr("Scribus 1.3.0->1.3.3.7 Document");
	fmt.formatId = FORMATID_SLA13XIMPORT;
	fmt.load = true;
	fmt.save = false; //Only support 134format saving in 134cvs
	fmt.colorReading = true;
	fmt.filter = fmt.trName + " (*.sla *.SLA *.sla.gz *.SLA.GZ *.scd *.SCD *.scd.gz *.SCD.GZ)";
	fmt.nameMatch = QRegExp("\\.(sla|scd)(\\.gz)?", Qt::CaseInsensitive);
	fmt.mimeTypes = QStringList();
	fmt.mimeTypes.append("application/x-scribus");
	fmt.fileExtensions = QStringList() << "sla" << "sla.gz" << "scd" << "scd.gz";
	fmt.priority = 64;
	registerFormat(fmt);
}

bool Scribus13Format::fileSupported(QIODevice* /* file */, const QString & fileName) const
{
	QByteArray docBytes("");
	if(fileName.right(2) == "gz")
	{
		if (!ScGzFile::readFromFile(fileName, docBytes, 4096))
		{
			// FIXME: Needs better error return
			return false;
		}
	}
	else
	{
		// Not gzip encoded, just load it
		loadRawText(fileName, docBytes);
	}
	if (docBytes.left(16) == "<SCRIBUSUTF8NEW " && !docBytes.left(35).contains("Version=\"1.3.4"))
		return true;
	return false;
}

QString Scribus13Format::readSLA(const QString & fileName)
{
	QByteArray docBytes("");
	if(fileName.right(2) == "gz")
	{
		if (!ScGzFile::readFromFile(fileName, docBytes))
		{
			// FIXME: Needs better error return
			return false;
		}
	}
	else
	{
		// Not gzip encoded, just load it
		loadRawText(fileName, docBytes);
	}
	QString docText("");
	if (docBytes.left(16) == "<SCRIBUSUTF8NEW " && !docBytes.left(35).contains("Version=\"1.3.4"))
		docText = QString::fromUtf8(docBytes);
	else
		return QString::null;
	if (docText.endsWith(QChar(10)) || docText.endsWith(QChar(13)))
		docText.truncate(docText.length()-1);
	return docText;
}

void Scribus13Format::getReplacedFontData(bool & getNewReplacement, QMap<QString,QString> &getReplacedFonts, QList<ScFace> &getDummyScFaces)
{
	getNewReplacement=newReplacement;
	getReplacedFonts=ReplacedFonts;
//	getDummyScFaces=dummyScFaces;
}

bool Scribus13Format::loadFile(const QString & fileName, const FileFormat & /* fmt */, int /* flags */, int /* index */)
{
	if (m_Doc==0 || m_AvailableFonts==0)
	{
		Q_ASSERT(m_Doc==0 || m_AvailableFonts==0);
		return false;
	}
	ReplacedFonts.clear();
	newReplacement = false;
	ParagraphStyle vg;
	struct ScribusDoc::BookMa bok;
	int counter;//, Pgc;
	//bool AtFl;
	bool newVersion = false;
	QString tmp, tmpf, tmp2, tmp3, tmp4, PgNam, Defont, tmf;
	QFont fo;
	QMap<int,int> TableID;
	QList<PageItem*> TableItems;
	QMap<int,int> TableIDM;
	QList<PageItem*> TableItemsM;
	QMap<int,int> TableIDF;
	QList<PageItem*> TableItemsF;
	int a;
	PageItem *Neu;
	Page* Apage;
	groupRemap.clear();
	itemRemap.clear();
	itemNext.clear();
	itemCount = 0;
	DoVorl.clear();
	DoVorl[0] = "";
	DoVorl[1] = "";
	DoVorl[2] = "";
	DoVorl[3] = "";
	DoVorl[4] = "";
	VorlC = 5;
	QDomDocument docu("scridoc");
	QString f(readSLA(fileName));
	if (f.isEmpty())
	{
		setFileReadError();
		return false;
	}
	QString fileDir = QFileInfo(fileName).absolutePath();
	/* 2004/10/02 - petr vanek - bug #1092 - missing <PAGE> crash Scribus. The check constraint moved into IsScribus()
	FIXME: I've add test on containig tag PAGE but returning false freezes S. in scribus.cpp need some hack too...  */
	QString errorMsg;
	int errorLine, errorColumn;
	if (!docu.setContent(f, &errorMsg, &errorLine, &errorColumn))
	{
		setDomParsingError(errorMsg, errorLine, errorColumn);
		return false;
	}
	m_Doc->PageColors.clear();
	m_Doc->Layers.clear();
	int layerToSetActive=0;
	ScColor lf = ScColor();
	QDomElement elem=docu.documentElement();
	if (elem.tagName() != "SCRIBUSUTF8NEW")
		return false;
	if (elem.hasAttribute("Version"))
		newVersion = true;
	QDomNode DOC=elem.firstChild();
	if (m_mwProgressBar!=0)
	{
		m_mwProgressBar->setMaximum(DOC.childNodes().count());
		m_mwProgressBar->setValue(0);
	}
	// Stop  autosave timer,it will be started only if doc has autosave feature is enabled
	if (m_Doc->autoSaveTimer->isActive())
		m_Doc->autoSaveTimer->stop();
	int ObCount = 0;
	TableItems.clear();
	TableID.clear();
	TableItemsM.clear();
	TableIDM.clear();
	TableItemsF.clear();
	TableIDF.clear();
	PrefsManager* prefsManager=PrefsManager::instance();
	while(!DOC.isNull())
	{
		QDomElement dc=DOC.toElement();
	/*
	* Attribute von DOCUMENT auslesen
	*/
		//CB Add this in to set this in the file in memory. Its saved, why not load it.
		//Will of course be replaced by per page settings although we still probably need a document default
		m_Doc->m_pageSize = dc.attribute("PAGESIZE");
		m_Doc->PageOri = dc.attribute("ORIENTATION", "0").toInt();
		m_Doc->FirstPnum = dc.attribute("FIRSTNUM", "1").toInt();
		m_Doc->currentPageLayout=dc.attribute("BOOK", "0").toInt();
		int fp;
		if (m_Doc->currentPageLayout == 0)
			fp = 0;
		else
		{
			if (dc.attribute("FIRSTLEFT", "0").toInt() == 1)
				fp = 0;
			else
				fp = 1;
		}
		if (DOC.namedItem("PageSets").isNull())
		{
			m_Doc->setPageSetFirstPage(m_Doc->currentPageLayout, fp);
//			m_Doc->pageSets[m_Doc->currentPageLayout].GapHorizontal = dc.attribute("GapHorizontal", "0").toDouble();
//			m_Doc->pageSets[m_Doc->currentPageLayout].GapVertical = 0.0;
//			m_Doc->pageSets[m_Doc->currentPageLayout].GapBelow = dc.attribute("GapVertical", "40").toDouble();
		}
		m_Doc->setUsesAutomaticTextFrames(dc.attribute("AUTOTEXT").toInt());
		m_Doc->PageSp = dc.attribute("AUTOSPALTEN").toInt();
		m_Doc->PageSpa= ScCLocale::toDoubleC(dc.attribute("ABSTSPALTEN"));
		m_Doc->setUnitIndex(dc.attribute("UNITS", "0").toInt());
		m_Doc->itemToolPrefs().textSize=qRound(ScCLocale::toDoubleC(dc.attribute("DSIZE")) * 10);
		Defont=dc.attribute("DFONT");
		//findFont will use that if it doesnt find the font:
		m_Doc->itemToolPrefs().textFont = prefsManager->appPrefs.itemToolPrefs.textFont;
		m_AvailableFonts->findFont(Defont, m_Doc);
		m_Doc->itemToolPrefs().textFont = Defont;
		m_Doc->itemToolPrefs().textColumns= dc.attribute("DCOL", "1").toInt();
		m_Doc->itemToolPrefs().textColumnGap = ScCLocale::toDoubleC(dc.attribute("DGAP"), 0.0);
		m_Doc->documentInfo.setAuthor(dc.attribute("AUTHOR"));
		m_Doc->documentInfo.setComments(dc.attribute("COMMENTS"));
		m_Doc->documentInfo.setKeywords(dc.attribute("KEYWORDS",""));
		m_Doc->documentInfo.setTitle(dc.attribute("TITLE"));
		m_Doc->documentInfo.setPublisher(dc.attribute("PUBLISHER", ""));
		m_Doc->documentInfo.setDate(dc.attribute("DOCDATE", ""));
		m_Doc->documentInfo.setType(dc.attribute("DOCTYPE", ""));
		m_Doc->documentInfo.setFormat(dc.attribute("DOCFORMAT", ""));
		m_Doc->documentInfo.setIdent(dc.attribute("DOCIDENT", ""));
		m_Doc->documentInfo.setSource(dc.attribute("DOCSOURCE", ""));
		m_Doc->documentInfo.setLangInfo(dc.attribute("DOCLANGINFO", ""));
		m_Doc->documentInfo.setRelation(dc.attribute("DOCRELATION", ""));
		m_Doc->documentInfo.setCover(dc.attribute("DOCCOVER", ""));
		m_Doc->documentInfo.setRights(dc.attribute("DOCRIGHTS", ""));
		m_Doc->documentInfo.setContrib(dc.attribute("DOCCONTRIB", ""));
		m_Doc->typographicPrefs().valueSuperScript = dc.attribute("VHOCH").toInt();
		m_Doc->typographicPrefs().scalingSuperScript = dc.attribute("VHOCHSC").toInt();
		m_Doc->typographicPrefs().valueSubScript = dc.attribute("VTIEF").toInt();
		m_Doc->typographicPrefs().scalingSubScript = dc.attribute("VTIEFSC").toInt();
		m_Doc->typographicPrefs().valueSmallCaps = dc.attribute("VKAPIT").toInt();
		m_Doc->guidesPrefs().valueBaselineGrid  = ScCLocale::toDoubleC(dc.attribute("BASEGRID"), 12.0);
		m_Doc->guidesPrefs().offsetBaselineGrid = ScCLocale::toDoubleC(dc.attribute("BASEO"), 0.0);
		m_Doc->typographicPrefs().autoLineSpacing = dc.attribute("AUTOL", "20").toInt();
		m_Doc->typographicPrefs().valueUnderlinePos = dc.attribute("UnderlinePos", "-1").toInt();
		m_Doc->typographicPrefs().valueUnderlineWidth = dc.attribute("UnderlineWidth", "-1").toInt();
		m_Doc->typographicPrefs().valueStrikeThruPos = dc.attribute("StrikeThruPos", "-1").toInt();
		m_Doc->typographicPrefs().valueStrikeThruWidth = dc.attribute("StrikeThruWidth", "-1").toInt();
		m_Doc->GroupCounter = 1 /*dc.attribute("GROUPC", "1").toInt()*/;
		//m_Doc->HasCMS = static_cast<bool>(dc.attribute("HCMS", "0").toInt());
		m_Doc->CMSSettings.SoftProofOn = static_cast<bool>(dc.attribute("DPSo", "0").toInt());
		m_Doc->CMSSettings.SoftProofFullOn = static_cast<bool>(dc.attribute("DPSFo", "0").toInt());
		m_Doc->CMSSettings.CMSinUse = static_cast<bool>(dc.attribute("DPuse", "0").toInt());
		m_Doc->CMSSettings.GamutCheck = static_cast<bool>(dc.attribute("DPgam", "0").toInt());
		m_Doc->CMSSettings.BlackPoint = static_cast<bool>(dc.attribute("DPbla", "1").toInt());
		m_Doc->CMSSettings.DefaultMonitorProfile = dc.attribute("DPMo","");
		m_Doc->CMSSettings.DefaultPrinterProfile = dc.attribute("DPPr","");
		m_Doc->CMSSettings.DefaultImageRGBProfile = dc.attribute("DPIn","");
		m_Doc->CMSSettings.DefaultImageCMYKProfile = dc.attribute("DPInCMYK","");
		m_Doc->CMSSettings.DefaultSolidColorRGBProfile = dc.attribute("DPIn2","");
		if (dc.hasAttribute("DPIn3"))
			m_Doc->CMSSettings.DefaultSolidColorCMYKProfile = dc.attribute("DPIn3","");
		else
			m_Doc->CMSSettings.DefaultSolidColorCMYKProfile = dc.attribute("DPPr","");
		//m_Doc->CMSSettings.DefaultIntentPrinter = dc.attribute("DIPr", "0").toInt();
		//m_Doc->CMSSettings.DefaultIntentMonitor = dc.attribute("DIMo", "1").toInt();
		m_Doc->CMSSettings.DefaultIntentColors = (eRenderIntent) dc.attribute("DISc", "1").toInt();
		m_Doc->CMSSettings.DefaultIntentImages = (eRenderIntent) dc.attribute("DIIm", "0").toInt();
		layerToSetActive=dc.attribute("ALAYER", "0").toInt();
		m_Doc->setHyphLanguage(dc.attribute("LANGUAGE", ""));
		m_Doc->setHyphMinimumWordLength(dc.attribute("MINWORDLEN", "3").toInt());
		m_Doc->setHyphConsecutiveLines(dc.attribute("HYCOUNT", "2").toInt());
		if (dc.hasAttribute("PAGEWIDTH"))
			m_Doc->pageWidth = ScCLocale::toDoubleC(dc.attribute("PAGEWIDTH"));
		else
			m_Doc->pageWidth = ScCLocale::toDoubleC(dc.attribute("PAGEWITH"));
		m_Doc->pageHeight = ScCLocale::toDoubleC(dc.attribute("PAGEHEIGHT"));
		m_Doc->pageMargins.Left  = qMax(0.0, ScCLocale::toDoubleC("BORDERLEFT"));
		m_Doc->pageMargins.Right = qMax(0.0, ScCLocale::toDoubleC("BORDERRIGHT"));
		m_Doc->pageMargins.Top   = qMax(0.0, ScCLocale::toDoubleC("BORDERTOP"));
		m_Doc->pageMargins.Bottom= qMax(0.0, ScCLocale::toDoubleC("BORDERBOTTOM"));
		m_Doc->marginPreset = dc.attribute("PRESET", "0").toInt();
		m_Doc->setHyphAutomatic(static_cast<bool>(dc.attribute("AUTOMATIC", "1").toInt()));
		m_Doc->setHyphAutoCheck(static_cast<bool>(dc.attribute("AUTOCHECK", "0").toInt()));
		m_Doc->GuideLock = static_cast<bool>(dc.attribute("GUIDELOCK", "0").toInt());
		m_Doc->guidesPrefs().minorGridSpacing = ScCLocale::toDoubleC(dc.attribute("MINGRID"), prefsManager->appPrefs.guidesPrefs.minorGridSpacing);
		m_Doc->guidesPrefs().majorGridSpacing = ScCLocale::toDoubleC(dc.attribute("MAJGRID"), prefsManager->appPrefs.guidesPrefs.majorGridSpacing);
		m_Doc->guidesPrefs().gridShown = static_cast<bool>(dc.attribute("SHOWGRID", "0").toInt());
		m_Doc->guidesPrefs().guidesShown = static_cast<bool>(dc.attribute("SHOWGUIDES", "1").toInt());
		m_Doc->guidesPrefs().colBordersShown = static_cast<bool>(dc.attribute("showcolborders", "0").toInt());
		m_Doc->guidesPrefs().framesShown = static_cast<bool>(dc.attribute("SHOWFRAME", "1").toInt());
		m_Doc->guidesPrefs().layerMarkersShown = static_cast<bool>(dc.attribute("SHOWLAYERM", "0").toInt());
		m_Doc->guidesPrefs().marginsShown = static_cast<bool>(dc.attribute("SHOWMARGIN", "1").toInt());
		m_Doc->guidesPrefs().baselineGridShown = static_cast<bool>(dc.attribute("SHOWBASE", "0").toInt());
		m_Doc->guidesPrefs().showPic = static_cast<bool>(dc.attribute("SHOWPICT", "1").toInt());
		m_Doc->guidesPrefs().linkShown = static_cast<bool>(dc.attribute("SHOWLINK", "0").toInt());
		m_Doc->guidesPrefs().showControls = static_cast<bool>(dc.attribute("SHOWControl", "0").toInt());
		m_Doc->guidesPrefs().rulerMode = static_cast<bool>(dc.attribute("rulerMode", "1").toInt());
		m_Doc->guidesPrefs().rulersShown = static_cast<bool>(dc.attribute("showrulers", "1").toInt());
		m_Doc->rulerXoffset = ScCLocale::toDoubleC(dc.attribute("rulerXoffset"), 0.0);
		m_Doc->rulerYoffset = ScCLocale::toDoubleC(dc.attribute("rulerYoffset"), 0.0);
		m_Doc->SnapGuides = static_cast<bool>(dc.attribute("SnapToGuides", "0").toInt());
		m_Doc->useRaster = static_cast<bool>(dc.attribute("SnapToGrid", "0").toInt());
		m_Doc->itemToolPrefs().polyCorners = dc.attribute("POLYC", "4").toInt();
		m_Doc->itemToolPrefs().polyFactor = ScCLocale::toDoubleC(dc.attribute("POLYF"), 0.5);
		m_Doc->itemToolPrefs().polyRotation = ScCLocale::toDoubleC(dc.attribute("POLYR"), 0.0);
		m_Doc->itemToolPrefs().polyCurvature = 0.0;
		m_Doc->itemToolPrefs().polyFactorGuiVal = dc.attribute("POLYFD", "0").toInt();
		m_Doc->itemToolPrefs().polyUseFactor = static_cast<bool>(dc.attribute("POLYS", "0").toInt());
		m_Doc->setAutoSave(static_cast<bool>(dc.attribute("AutoSave", "0").toInt()));
		m_Doc->setAutoSaveTime(dc.attribute("AutoSaveTime", "600000").toInt());
		double leftScratch;
		// FIXME A typo in early 1.3cvs (MAR 05) means we must support loading of
		// FIXME 'ScatchLeft' for a while too. This can be removed in a few months.
		if (dc.hasAttribute("ScatchLeft"))
			leftScratch = ScCLocale::toDoubleC(dc.attribute("ScatchLeft"), 100.0);
		else
			leftScratch = ScCLocale::toDoubleC(dc.attribute("ScratchLeft"), 100.0);
		m_Doc->scratch()->set(ScCLocale::toDoubleC(dc.attribute("ScratchTop"), 20.0), leftScratch,
							  ScCLocale::toDoubleC(dc.attribute("ScratchBottom"), 20.0), ScCLocale::toDoubleC(dc.attribute("ScratchRight"), 100.0));
		m_Doc->itemToolPrefs().lineStartArrow = dc.attribute("StartArrow", "0").toInt();
		m_Doc->itemToolPrefs().lineEndArrow = dc.attribute("EndArrow", "0").toInt();
		m_Doc->itemToolPrefs().imageScaleX = ScCLocale::toDoubleC(dc.attribute("PICTSCX"), 1.0);
		m_Doc->itemToolPrefs().imageScaleY = ScCLocale::toDoubleC(dc.attribute("PICTSCY"), 1.0);
		m_Doc->itemToolPrefs().imageScaleType = static_cast<bool>(dc.attribute("PSCALE", "1").toInt());
		m_Doc->itemToolPrefs().imageAspectRatio = static_cast<bool>(dc.attribute("PASPECT", "0").toInt());
		m_Doc->itemToolPrefs().imageLowResType = dc.attribute("HalfRes", "1").toInt();
		m_Doc->itemToolPrefs().imageUseEmbeddedPath = static_cast<bool>(dc.attribute("EmbeddedPath", "0").toInt());
		if (dc.hasAttribute("PEN"))
			m_Doc->itemToolPrefs().shapeLineColor = dc.attribute("PEN");
		if (dc.hasAttribute("BRUSH"))
			m_Doc->itemToolPrefs().shapeFillColor = dc.attribute("BRUSH");
		if (dc.hasAttribute("PENLINE"))
			m_Doc->itemToolPrefs().lineColor = dc.attribute("PENLINE");
		if (dc.hasAttribute("PENTEXT"))
			m_Doc->itemToolPrefs().textColor = dc.attribute("PENTEXT");
		if (dc.hasAttribute("StrokeText"))
			m_Doc->itemToolPrefs().textStrokeColor = dc.attribute("StrokeText");
		m_Doc->itemToolPrefs().textFillColor = dc.attribute("TextBackGround", CommonStrings::None);
		m_Doc->itemToolPrefs().textLineColor = dc.attribute("TextLineColor", CommonStrings::None);
		m_Doc->itemToolPrefs().textFillColorShade = dc.attribute("TextBackGroundShade", "100").toInt();
		m_Doc->itemToolPrefs().textLineColorShade = dc.attribute("TextLineShade", "100").toInt();
		m_Doc->itemToolPrefs().textShade = dc.attribute("TextPenShade", "100").toInt();
		m_Doc->itemToolPrefs().textStrokeShade = dc.attribute("TextStrokeShade", "100").toInt();
		m_Doc->itemToolPrefs().shapeLineStyle = static_cast<Qt::PenStyle>(dc.attribute("STIL").toInt());
		m_Doc->itemToolPrefs().lineStyle = static_cast<Qt::PenStyle>(dc.attribute("STILLINE").toInt());
		m_Doc->itemToolPrefs().shapeLineWidth     = ScCLocale::toDoubleC(dc.attribute("WIDTH"), 1.0);
		m_Doc->itemToolPrefs().lineWidth = ScCLocale::toDoubleC(dc.attribute("WIDTHLINE"), 1.0);
		m_Doc->itemToolPrefs().shapeLineColorShade    = dc.attribute("PENSHADE", "100").toInt();
		m_Doc->itemToolPrefs().lineColorShade = dc.attribute("LINESHADE", "100").toInt();
		m_Doc->itemToolPrefs().shapeFillColorShade     = dc.attribute("BRUSHSHADE", "100").toInt();
		m_Doc->opToolPrefs().magMin     = dc.attribute("MAGMIN", "1").toInt();
		m_Doc->opToolPrefs().magMax     = dc.attribute("MAGMAX", "3200").toInt();
		m_Doc->opToolPrefs().magStep    = dc.attribute("MAGSTEP", "200").toInt();
		//CB Reset doc zoom step value to 200% instead of old values.
		if (m_Doc->opToolPrefs().magStep <= 100)
			m_Doc->opToolPrefs().magStep = 200;
		m_Doc->itemToolPrefs().textTabFillChar = dc.attribute("TabFill","");
		m_Doc->itemToolPrefs().textTabWidth   = ScCLocale::toDoubleC(dc.attribute("TabWidth"), 36.0);
		if (dc.hasAttribute("CPICT"))
			m_Doc->itemToolPrefs().imageFillColor = dc.attribute("CPICT");
		m_Doc->itemToolPrefs().imageFillColorShade = ScCLocale::toDoubleC(dc.attribute("PICTSHADE"), 100.0);
		if (dc.hasAttribute("PAGEC"))
			m_Doc->setPaperColor(QColor(dc.attribute("PAGEC")));
		if (dc.hasAttribute("MARGC"))
			m_Doc->guidesPrefs().marginColor = QColor(dc.attribute("MARGC"));
		if (dc.hasAttribute("MINORC"))
			m_Doc->guidesPrefs().minorGridColor = QColor(dc.attribute("MINORC"));
		if (dc.hasAttribute("MAJORC"))
			m_Doc->guidesPrefs().majorGridColor = QColor(dc.attribute("MAJORC"));
		if (dc.hasAttribute("GuideC"))
			m_Doc->guidesPrefs().guideColor = QColor(dc.attribute("GuideC"));
		if (dc.hasAttribute("BaseC"))
			m_Doc->guidesPrefs().baselineGridColor = QColor(dc.attribute("BaseC"));
		m_Doc->setMarginColored(static_cast<bool>(dc.attribute("RANDF", "0").toInt()));
		m_Doc->guidesPrefs().guidePlacement = static_cast<bool>(dc.attribute("BACKG", "1").toInt());
		m_Doc->guidesPrefs().guideRad = ScCLocale::toDoubleC(dc.attribute("GuideRad"), 10.0);
		m_Doc->guidesPrefs().grabRadius  = dc.attribute("GRAB", "4").toInt();
		if (dc.hasAttribute("currentProfile"))
		{
			m_Doc->clearCheckerProfiles();
			m_Doc->setCurCheckProfile(dc.attribute("currentProfile"));
		}
		m_Doc->LastAuto = 0;
		QDomNode PAGE=DOC.firstChild();
		counter = 0;
		while(!PAGE.isNull())
		{
			ObCount++;
			if (m_mwProgressBar!=0)
				m_mwProgressBar->setValue(ObCount);
			QDomElement pg=PAGE.toElement();
			if (pg.tagName()=="PageSets")
			{
				QDomNode PGS = PAGE.firstChild();
				m_Doc->clearPageSets();
				while(!PGS.isNull())
				{
					QDomElement PgsAttr = PGS.toElement();
					if(PgsAttr.tagName() == "Set")
					{
						struct PageSet pageS;
						pageS.Name = CommonStrings::untranslatePageSetString(PgsAttr.attribute("Name"));
						pageS.FirstPage = PgsAttr.attribute("FirstPage", "0").toInt();
						pageS.Rows = PgsAttr.attribute("Rows", "1").toInt();
						pageS.Columns = PgsAttr.attribute("Columns", "1").toInt();
				//		pageS.GapHorizontal = PgsAttr.attribute("GapHorizontal", "0").toDouble();
				//		pageS.GapVertical = PgsAttr.attribute("GapVertical", "0").toDouble();
				//		pageS.GapBelow = PgsAttr.attribute("GapBelow", "0").toDouble();
						pageS.pageNames.clear();
						QDomNode PGSN = PGS.firstChild();
						while(!PGSN.isNull())
						{
							QDomElement PgsAttrN = PGSN.toElement();
							if(PgsAttrN.tagName() == "PageNames")
								pageS.pageNames.append(CommonStrings::untranslatePageSetLocString(PgsAttrN.attribute("Name")));
							PGSN = PGSN.nextSibling();
						}
						//->Prefs m_Doc->pageSets.append(pageS);
						m_Doc->appendToPageSets(pageS);
						if (m_Doc->pageSets().count()-1 == m_Doc->currentPageLayout)
						{
							m_Doc->setPageGapHorizontal(ScCLocale::toDoubleC(PgsAttr.attribute("GapHorizontal"), 0.0));
							m_Doc->setPageGapVertical(ScCLocale::toDoubleC(PgsAttr.attribute("GapBelow"), 0.0));
						}
					}
					PGS = PGS.nextSibling();
				}
			}
			if (pg.tagName()=="CheckProfile")
			{
				struct CheckerPrefs checkerSettings;
				checkerSettings.ignoreErrors = static_cast<bool>(pg.attribute("ignoreErrors", "0").toInt());
				checkerSettings.autoCheck = static_cast<bool>(pg.attribute("autoCheck", "1").toInt());
				checkerSettings.checkGlyphs = static_cast<bool>(pg.attribute("checkGlyphs", "1").toInt());
				checkerSettings.checkOrphans = static_cast<bool>(pg.attribute("checkOrphans", "1").toInt());
				checkerSettings.checkOverflow = static_cast<bool>(pg.attribute("checkOverflow", "1").toInt());
				checkerSettings.checkPictures = static_cast<bool>(pg.attribute("checkPictures", "1").toInt());
				checkerSettings.checkResolution = static_cast<bool>(pg.attribute("checkResolution", "1").toInt());
				checkerSettings.checkTransparency = static_cast<bool>(pg.attribute("checkTransparency", "1").toInt());
				checkerSettings.minResolution = ScCLocale::toDoubleC(pg.attribute("minResolution"), 72.0);
				checkerSettings.maxResolution = ScCLocale::toDoubleC(pg.attribute("maxResolution"), 4800.0);
				checkerSettings.checkAnnotations = static_cast<bool>(pg.attribute("checkAnnotations", "0").toInt());
				checkerSettings.checkRasterPDF = static_cast<bool>(pg.attribute("checkRasterPDF", "1").toInt());
				checkerSettings.checkForGIF = static_cast<bool>(pg.attribute("checkForGIF", "1").toInt());
				checkerSettings.ignoreOffLayers = false;
				m_Doc->set1CheckerProfile(pg.attribute("Name"), checkerSettings);
			}
			// 10/25/2004 pv - None is "reserved" color. cannot be defined in any file...
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
				QString name = pg.attribute("NAME");
				m_Doc->PageColors.insert((name.isEmpty()) ? lf.name() : name, lf);
			}
			if(pg.tagName()=="STYLE")
			{
				readParagraphStyle(vg, pg, m_Doc);
				StyleSet<ParagraphStyle> temp;
				temp.create(vg);
				m_Doc->redefineStyles(temp, false);
				DoVorl[VorlC] = vg.name();
				++VorlC;
			}
			if(pg.tagName()=="JAVA")
				m_Doc->JavaScripts[pg.attribute("NAME")] = pg.attribute("SCRIPT");
			if(pg.tagName()=="LAYERS")
			{
				int lId   = pg.attribute("NUMMER").toInt();
				int level = pg.attribute("LEVEL").toInt();
				ScLayer la( pg.attribute("NAME"), level, lId);
				la.isViewable   = pg.attribute("SICHTBAR").toInt();
				la.isPrintable  = pg.attribute("DRUCKEN").toInt();
				la.isEditable   = pg.attribute("EDIT", "1").toInt();
				la.flowControl  = pg.attribute("FLOW", "1").toInt();
				la.transparency = ScCLocale::toDoubleC(pg.attribute("TRANS"), 1.0);
				la.blendMode    = pg.attribute("BLEND", "0").toInt();
				la.outlineMode  = pg.attribute("OUTL", "0").toInt();
				if (pg.hasAttribute("LAYERC"))
					la.markerColor =  QColor(pg.attribute("LAYERC","#000000"));
				m_Doc->Layers.append(la);
			}
/*			if(pg.tagName()=="Bookmark")
			{
				bok.Title = pg.attribute("Title");
				bok.Text = pg.attribute("Text");
				bok.Aktion = pg.attribute("Aktion");
				bok.ItemNr = pg.attribute("ItemNr").toInt();
				bok.Seite = pg.attribute("Seite").toInt();
				bok.Element = pg.attribute("Element").toInt();
				bok.First = pg.attribute("First").toInt();
				bok.Last = pg.attribute("Last").toInt();
				bok.Prev = pg.attribute("Prev").toInt();
				bok.Next = pg.attribute("Next").toInt();
				bok.Parent = pg.attribute("Parent").toInt();
				m_Doc->BookMarks.append(bok);
			} */
			if(pg.tagName()=="MultiLine")
			{
				multiLine ml;
				QDomNode MuLn = PAGE.firstChild();
				while(!MuLn.isNull())
				{
					QDomElement MuL = MuLn.toElement();
					struct SingleLine sl;
					sl.Color = MuL.attribute("Color");
					sl.Dash = MuL.attribute("Dash").toInt();
					sl.LineEnd = MuL.attribute("LineEnd").toInt();
					sl.LineJoin = MuL.attribute("LineJoin").toInt();
					sl.Shade = MuL.attribute("Shade").toInt();
					sl.Width = ScCLocale::toDoubleC(MuL.attribute("Width"));
					ml.push_back(sl);
					MuLn = MuLn.nextSibling();
				}
				m_Doc->MLineStyles.insert(pg.attribute("Name"), ml);
			}
			if(pg.tagName()=="Arrows")
			{
				struct ArrowDesc arrow;
				arrow.name = pg.attribute("Name");
				arrow.userArrow = true;
				double xa, ya;
				QString tmp = pg.attribute("Points");
				ScTextStream fp(&tmp, QIODevice::ReadOnly);
				for (uint cx = 0; cx < pg.attribute("NumPoints").toUInt(); ++cx)
				{
					fp >> xa;
					fp >> ya;
					arrow.points.addPoint(xa, ya);
				}
				m_Doc->appendToArrowStyles(arrow);
			}
			if(pg.tagName()=="PDF")
			{
				m_Doc->pdfOptions().Articles = static_cast<bool>(pg.attribute("Articles").toInt());
				m_Doc->pdfOptions().Thumbnails = static_cast<bool>(pg.attribute("Thumbnails").toInt());
				m_Doc->pdfOptions().Compress = static_cast<bool>(pg.attribute("Compress").toInt());
				m_Doc->pdfOptions().CompressMethod = (PDFOptions::PDFCompression) pg.attribute("CMethod", "0").toInt();
				m_Doc->pdfOptions().Quality = pg.attribute("Quality", "0").toInt();
				m_Doc->pdfOptions().RecalcPic = static_cast<bool>(pg.attribute("RecalcPic").toInt());
				m_Doc->pdfOptions().Bookmarks = static_cast<bool>(pg.attribute("Bookmarks").toInt());
				if (pg.hasAttribute("MirrorH"))
					m_Doc->pdfOptions().MirrorH = static_cast<bool>(pg.attribute("MirrorH").toInt());
				else
					m_Doc->pdfOptions().MirrorH = false;
				if (pg.hasAttribute("MirrorV"))
					m_Doc->pdfOptions().MirrorV = static_cast<bool>(pg.attribute("MirrorV").toInt());
				else
					m_Doc->pdfOptions().MirrorV = false;
				if (pg.hasAttribute("RotateDeg"))
					m_Doc->pdfOptions().RotateDeg = pg.attribute("RotateDeg", "0").toInt();
				else
					m_Doc->pdfOptions().RotateDeg = 0;
				if (pg.hasAttribute("Clip"))
					m_Doc->pdfOptions().doClip = static_cast<bool>(pg.attribute("Clip").toInt());
				else
					m_Doc->pdfOptions().doClip = false;
				m_Doc->pdfOptions().PresentMode = static_cast<bool>(pg.attribute("PresentMode").toInt());
				m_Doc->pdfOptions().PicRes = pg.attribute("PicRes").toInt();
				// Fixme: check input pdf version
				m_Doc->pdfOptions().Version = (PDFOptions::PDFVersion)pg.attribute("Version").toInt();
				m_Doc->pdfOptions().Resolution = pg.attribute("Resolution").toInt();
				m_Doc->pdfOptions().Binding = pg.attribute("Binding").toInt();
				m_Doc->pdfOptions().fileName = "";
				m_Doc->pdfOptions().isGrayscale = static_cast<bool>(pg.attribute("Grayscale", "0").toInt());
				m_Doc->pdfOptions().UseRGB = static_cast<bool>(pg.attribute("RGBMode", "0").toInt());
				m_Doc->pdfOptions().UseProfiles = static_cast<bool>(pg.attribute("UseProfiles", "0").toInt());
				m_Doc->pdfOptions().UseProfiles2 = static_cast<bool>(pg.attribute("UseProfiles2", "0").toInt());
				m_Doc->pdfOptions().Intent = pg.attribute("Intent", "1").toInt();
				m_Doc->pdfOptions().Intent2 = pg.attribute("Intent2", "1").toInt();
				m_Doc->pdfOptions().SolidProf = pg.attribute("SolidP", "");
				m_Doc->pdfOptions().ImageProf = pg.attribute("ImageP", "");
				m_Doc->pdfOptions().PrintProf = pg.attribute("PrintP", "");
				m_Doc->pdfOptions().Info = pg.attribute("InfoString", "");
				m_Doc->pdfOptions().bleeds.Top    = ScCLocale::toDoubleC(pg.attribute("BTop"), 0.0);
				m_Doc->pdfOptions().bleeds.Left   = ScCLocale::toDoubleC(pg.attribute("BLeft"), 0.0);
				m_Doc->pdfOptions().bleeds.Right  = ScCLocale::toDoubleC(pg.attribute("BRight"), 0.0);
				m_Doc->pdfOptions().bleeds.Bottom = ScCLocale::toDoubleC(pg.attribute("BBottom"), 0.0);
				m_Doc->pdfOptions().EmbeddedI = static_cast<bool>(pg.attribute("ImagePr", "0").toInt());
				m_Doc->pdfOptions().PassOwner = pg.attribute("PassOwner", "");
				m_Doc->pdfOptions().PassUser  = pg.attribute("PassUser", "");
				m_Doc->pdfOptions().Permissions = pg.attribute("Permissions", "-4").toInt();
				m_Doc->pdfOptions().Encrypt = static_cast<bool>(pg.attribute("Encrypt", "0").toInt());
				m_Doc->pdfOptions().useLayers = static_cast<bool>(pg.attribute("UseLayers", "0").toInt());
				m_Doc->pdfOptions().UseLPI = static_cast<bool>(pg.attribute("UseLpi", "0").toInt());
				m_Doc->pdfOptions().UseSpotColors = static_cast<bool>(pg.attribute("UseSpotColors", "1").toInt());
				m_Doc->pdfOptions().doMultiFile = static_cast<bool>(pg.attribute("doMultiFile", "0").toInt());
				m_Doc->pdfOptions().displayBookmarks = static_cast<bool>(pg.attribute("displayBookmarks", "0").toInt());
				m_Doc->pdfOptions().displayFullscreen = static_cast<bool>(pg.attribute("displayFullscreen", "0").toInt());
				m_Doc->pdfOptions().displayLayers = static_cast<bool>(pg.attribute("displayLayers", "0").toInt());
				m_Doc->pdfOptions().displayThumbs = static_cast<bool>(pg.attribute("displayThumbs", "0").toInt());
				m_Doc->pdfOptions().hideMenuBar = static_cast<bool>(pg.attribute("hideMenuBar", "0").toInt());
				m_Doc->pdfOptions().hideToolBar = static_cast<bool>(pg.attribute("hideToolBar", "0").toInt());
				m_Doc->pdfOptions().fitWindow = static_cast<bool>(pg.attribute("fitWindow", "0").toInt());
				m_Doc->pdfOptions().PageLayout = pg.attribute("PageLayout", "0").toInt();
				m_Doc->pdfOptions().openAction = pg.attribute("openAction", "");
				QDomNode PFO = PAGE.firstChild();
				while(!PFO.isNull())
				{
					QDomElement pdfF = PFO.toElement();
					if(pdfF.tagName() == "LPI")
					{
						struct LPIData lpo;
						lpo.Angle = pdfF.attribute("Angle").toInt();
						lpo.Frequency = pdfF.attribute("Frequency").toInt();
						lpo.SpotFunc = pdfF.attribute("SpotFunction").toInt();
						m_Doc->pdfOptions().LPISettings[pdfF.attribute("Color")] = lpo;
					}
					if(pdfF.tagName() == "Fonts")
					{
						if (!m_Doc->pdfOptions().EmbedList.contains(pdfF.attribute("Name")))
							m_Doc->pdfOptions().EmbedList.append(pdfF.attribute("Name"));
					}
					if(pdfF.tagName() == "Subset")
					{
						if (!m_Doc->pdfOptions().SubsetList.contains(pdfF.attribute("Name")))
							m_Doc->pdfOptions().SubsetList.append(pdfF.attribute("Name"));
					}
					if(pdfF.tagName() == "Effekte")
					{
						struct PDFPresentationData ef;
						ef.pageEffectDuration = pdfF.attribute("pageEffectDuration").toInt();
						ef.pageViewDuration = pdfF.attribute("pageViewDuration").toInt();
						ef.effectType = pdfF.attribute("effectType").toInt();
						ef.Dm = pdfF.attribute("Dm").toInt();
						ef.M = pdfF.attribute("M").toInt();
						ef.Di = pdfF.attribute("Di").toInt();
						m_Doc->pdfOptions().PresentVals.append(ef);
					}
					PFO = PFO.nextSibling();
				}
			}
			if(pg.tagName()=="DocItemAttributes")
			{
				QDomNode DIA = PAGE.firstChild();
				m_Doc->clearItemAttributes();
				while(!DIA.isNull())
				{
					QDomElement itemAttr = DIA.toElement();
					if(itemAttr.tagName() == "ItemAttribute")
					{
						ObjectAttribute objattr;
						objattr.name=itemAttr.attribute("Name");
						objattr.type=itemAttr.attribute("Type");
						objattr.value=itemAttr.attribute("Value");
						objattr.parameter=itemAttr.attribute("Parameter");
						objattr.relationship=itemAttr.attribute("Relationship");
						objattr.relationshipto=itemAttr.attribute("RelationshipTo");
						objattr.autoaddto=itemAttr.attribute("AutoAddTo");
						m_Doc->appendToItemAttributes(objattr);
					}
					DIA = DIA.nextSibling();
				}
			}
			if(pg.tagName()=="TablesOfContents")
			{
				QDomNode TOC = PAGE.firstChild();
				m_Doc->clearTocSetups();
				while(!TOC.isNull())
				{
					QDomElement tocElem = TOC.toElement();
					if(tocElem.tagName() == "TableOfContents")
					{
						ToCSetup tocsetup;
						tocsetup.name=tocElem.attribute("Name");
						tocsetup.itemAttrName=tocElem.attribute("ItemAttributeName");
						tocsetup.frameName=tocElem.attribute("FrameName");
						tocsetup.listNonPrintingFrames=QVariant(tocElem.attribute("ListNonPrinting")).toBool();
						tocsetup.textStyle=tocElem.attribute("Style");
						QString numberPlacement=tocElem.attribute("NumberPlacement");
						if (numberPlacement=="Beginning")
							tocsetup.pageLocation=Beginning;
						if (numberPlacement=="End")
							tocsetup.pageLocation=End;
						if (numberPlacement=="NotShown")
							tocsetup.pageLocation=NotShown;
						m_Doc->appendToTocSetups(tocsetup);
					}
					TOC = TOC.nextSibling();
				}
			}
			if(pg.tagName()=="Sections")
			{
				QDomNode Section = PAGE.firstChild();
				while(!Section.isNull())
				{
					QDomElement sectionElem = Section.toElement();
					if(sectionElem.tagName() == "Section")
					{
						struct DocumentSection newSection;
						newSection.number=sectionElem.attribute("Number").toInt();
						newSection.name=sectionElem.attribute("Name");
						newSection.fromindex=sectionElem.attribute("From").toInt();
						newSection.toindex=sectionElem.attribute("To").toInt();
						if (sectionElem.attribute("Type")=="Type_1_2_3")
							newSection.type=Type_1_2_3;
						if (sectionElem.attribute("Type")=="Type_i_ii_iii")
							newSection.type=Type_i_ii_iii;
						if (sectionElem.attribute("Type")=="Type_I_II_III")
							newSection.type=Type_I_II_III;
						if (sectionElem.attribute("Type")=="Type_a_b_c")
							newSection.type=Type_a_b_c;
						if (sectionElem.attribute("Type")=="Type_A_B_C")
							newSection.type=Type_A_B_C;
						newSection.sectionstartindex=sectionElem.attribute("Start").toInt();
						newSection.reversed=static_cast<bool>(sectionElem.attribute("Reversed").toInt());
						newSection.active=static_cast<bool>(sectionElem.attribute("Active").toInt());
						m_Doc->sections.insert(newSection.number, newSection);
					}
					Section = Section.nextSibling();
				}
			}
			if ((pg.tagName()=="PAGE") || (pg.tagName()=="MASTERPAGE"))
			{
				a = pg.attribute("NUM").toInt();
				PgNam = "";
				PgNam = pg.attribute("NAM", "");
				if (pg.tagName()=="MASTERPAGE" && PgNam.isEmpty())
				{
					qDebug() << "scribus13format: corrupted masterpage with empty name detected";
					PAGE=PAGE.nextSibling();
					continue;
				}
				//Pgc = m_Doc->pageCount;
				//AtFl = m_Doc->usesAutomaticTextFrames();
				if (PgNam.isEmpty())
				{
					//m_Doc->pageCount = Pgc;
					//m_Doc->Pages = &m_Doc->DocPages;
					//m_Doc->setUsesAutomaticTextFrames(AtFl);
					m_Doc->setMasterPageMode(false);
				}
				else
				{
					//m_Doc->pageCount = 0;
					//m_Doc->setUsesAutomaticTextFrames(false);
					//m_Doc->Pages = &m_Doc->MasterPages;
					m_Doc->setMasterPageMode(true);
				}
				//CB: Stop calling damn GUI code in loading docs! IT doesnt *look* like
				//this makes a difference apart from being faster, of course.
				//ScMW->slotNewPage(a);
				//Apage = m_Doc->Pages.at(a);
				if (PgNam.isEmpty())
				{
					Apage = m_Doc->addPage(a);
					//m_Doc->DocPages = m_Doc->Pages;
					//++m_Doc->pageCount;
				}
				else
				{
					Apage = m_Doc->addMasterPage(a, PgNam);
					//Apage->setPageName(PgNam);
					//m_Doc->MasterNames[PgNam] = a;
					//m_Doc->MasterPages = m_Doc->Pages;
					//m_Doc->pageCount = Pgc;
				}
				//m_Doc->setUsesAutomaticTextFrames(AtFl);
				Apage->LeftPg=pg.attribute("LEFT", "0").toInt();
				QString Mus = "";
				Mus = pg.attribute("MNAM","Normal");
				if (!m_Doc->masterPageMode())
					Apage->MPageNam = Mus;
				else
					Apage->MPageNam = "";
				if (pg.hasAttribute("Size"))
					Apage->m_pageSize = pg.attribute("Size");
				if (pg.hasAttribute("Orientation"))
					Apage->setOrientation(pg.attribute("Orientation").toInt());
				Apage->setXOffset( ScCLocale::toDoubleC(pg.attribute("PAGEXPOS")) );
				Apage->setYOffset( ScCLocale::toDoubleC(pg.attribute("PAGEYPOS")) );
				if (pg.hasAttribute("PAGEWIDTH"))
					Apage->setWidth( ScCLocale::toDoubleC(pg.attribute("PAGEWIDTH")) );
				else
					Apage->setWidth( ScCLocale::toDoubleC(pg.attribute("PAGEWITH")) );
				Apage->setHeight( ScCLocale::toDoubleC(pg.attribute("PAGEHEIGHT")) );
				Apage->setInitialHeight(Apage->height());
				Apage->setInitialWidth(Apage->width());
				Apage->initialMargins.Top    = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERTOP")));
				Apage->initialMargins.Bottom = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERBOTTOM")));
				Apage->initialMargins.Left   = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERLEFT")));
				Apage->initialMargins.Right  = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERRIGHT")));
				Apage->marginPreset = pg.attribute("PRESET", "0").toInt();
				Apage->Margins.Top = Apage->initialMargins.Top;
				Apage->Margins.Bottom = Apage->initialMargins.Bottom;
				m_Doc->setMasterPageMode(false);
				//m_Doc->Pages=&m_Doc->DocPages;
				// guides reading
				tmp = "";
				Apage->guides.setHorizontalAutoGap(0.0);
				Apage->guides.setVerticalAutoGap(0.0);
				Apage->guides.setHorizontalAutoCount(0);
				Apage->guides.setVerticalAutoCount(0);
				Apage->guides.setHorizontalAutoRefer(0);
				Apage->guides.setVerticalAutoRefer(0);
				GuideManagerIO::readVerticalGuides(pg.attribute("VerticalGuides"),
						Apage,
						GuideManagerCore::Standard,
						pg.hasAttribute("NumVGuides"));
				GuideManagerIO::readHorizontalGuides(pg.attribute("HorizontalGuides"),
						Apage,
						GuideManagerCore::Standard,
						pg.hasAttribute("NumHGuides"));
			}
			if ((pg.tagName()=="PAGEOBJECT") || (pg.tagName()=="MASTEROBJECT") || (pg.tagName()=="FRAMEOBJECT"))
			{
				if ((pg.tagName()=="PAGEOBJECT") || (pg.tagName()=="FRAMEOBJECT"))
				{
					//m_Doc->Items = m_Doc->DocItems;
					//m_Doc->Pages = &m_Doc->DocPages;
					m_Doc->setMasterPageMode(false);
				}
				else
				{
					//m_Doc->Items = m_Doc->MasterItems;
					//m_Doc->Pages = &m_Doc->MasterPages;
					m_Doc->setMasterPageMode(true);
				}
				//unused int docGc = m_Doc->GroupCounter,
				int pagenr = -1;
				if ((!pg.attribute("OnMasterPage").isEmpty()) && (pg.tagName()=="MASTEROBJECT"))
				{
					m_Doc->setCurrentPage(m_Doc->MasterPages.at(m_Doc->MasterNames[pg.attribute("OnMasterPage")]));
					pagenr = -2;
				}

				if (pg.tagName()=="PAGEOBJECT")
				{
					itemRemap[itemCount++] = m_Doc->Items->count();
					// member of linked chain?
					if ((pg.attribute("NEXTITEM").toInt() != -1) )
					{
						itemNext[m_Doc->Items->count()] = pg.attribute("NEXTITEM").toInt();
					}
				}
				
				/*m_Doc->GroupCounter = 0;*/
				Neu = PasteItem(&pg, m_Doc, fileDir, pagenr);
				Neu->setRedrawBounding();
				if (pg.tagName()=="MASTEROBJECT")
					Neu->OwnPage = m_Doc->OnPage(Neu);
				else
				{
					Neu->OwnPage = pg.attribute("OwnPage").toInt();
	/*				if (Neu->OwnPage != -1)
					{
						double pgX = m_Doc->DocPages.at(Neu->OwnPage)->xOffset();
						double pgY = m_Doc->DocPages.at(Neu->OwnPage)->yOffset();
					} */
				}
				if (pg.tagName()=="PAGEOBJECT")
					Neu->OnMasterPage = "";
				/*m_Doc->GroupCounter = docGc;*/
				QDomNode IT=pg.firstChild();
				LastStyles * last = new LastStyles();
				while(!IT.isNull())
				{
					QDomElement it=IT.toElement();
					if (it.tagName()=="CSTOP")
					{
						QString name = it.attribute("NAME");
						double ramp = ScCLocale::toDoubleC(it.attribute("RAMP"), 0.0);
						int shade   = it.attribute("SHADE", "100").toInt();
						double opa  = ScCLocale::toDoubleC(it.attribute("TRANS"), 1.0);
						handleOldColorShade(m_Doc, name, shade);
						Neu->fill_gradient.addStop(SetColor(m_Doc, name, shade), ramp, 0.5, opa, name, shade);
					}
					if (it.tagName()=="ITEXT")
						GetItemText(&it, m_Doc, Neu, last);

					//CB PageItemAttributes
					if(it.tagName()=="PageItemAttributes")
					{
						QDomNode PIA = it.firstChild();
						ObjAttrVector pageItemAttributes;
						while(!PIA.isNull())
						{
							QDomElement itemAttr = PIA.toElement();
							if(itemAttr.tagName() == "ItemAttribute")
							{
								ObjectAttribute objattr;
								objattr.name=itemAttr.attribute("Name");
								objattr.type=itemAttr.attribute("Type");
								objattr.value=itemAttr.attribute("Value");
								objattr.parameter=itemAttr.attribute("Parameter");
								objattr.relationship=itemAttr.attribute("Relationship");
								objattr.relationshipto=itemAttr.attribute("RelationshipTo");
								objattr.autoaddto=itemAttr.attribute("AutoAddTo");
								pageItemAttributes.append(objattr);
							}
							PIA = PIA.nextSibling();
						}
						Neu->setObjectAttributes(&pageItemAttributes);
					}
					IT=IT.nextSibling();
				}
				delete last;
				if (Neu->fill_gradient.Stops() == 0)
				{
					const ScColor& col1 = m_Doc->PageColors[m_Doc->itemToolPrefs().shapeFillColor];
					const ScColor& col2 = m_Doc->PageColors[m_Doc->itemToolPrefs().shapeLineColor];
					Neu->fill_gradient.addStop(ScColorEngine::getRGBColor(col1, m_Doc), 0.0, 0.5, 1.0, m_Doc->itemToolPrefs().shapeFillColor, 100);
					Neu->fill_gradient.addStop(ScColorEngine::getRGBColor(col2, m_Doc), 1.0, 0.5, 1.0, m_Doc->itemToolPrefs().shapeLineColor, 100);
				}
//				Neu->Language = ScMW->GetLang(pg.attribute("LANGUAGE", m_Doc->Language));
				Neu->isAutoText = static_cast<bool>(pg.attribute("AUTOTEXT").toInt());
				Neu->isEmbedded = static_cast<bool>(pg.attribute("isInline", "0").toInt());
				Neu->gXpos = ScCLocale::toDoubleC(pg.attribute("gXpos"), 0.0);
				Neu->gYpos = ScCLocale::toDoubleC(pg.attribute("gYpos"), 0.0);
				Neu->gWidth  = ScCLocale::toDoubleC(pg.attribute("gWidth"), Neu->width());
				Neu->gHeight = ScCLocale::toDoubleC(pg.attribute("gHeight"), Neu->height());
				if (Neu->isAutoText)
					m_Doc->LastAuto = Neu;
				if (pg.tagName()=="FRAMEOBJECT")
				{
					m_Doc->FrameItems.append(m_Doc->Items->takeAt(Neu->ItemNr));
					Neu->ItemNr = m_Doc->FrameItems.count()-1;
				}
				if (Neu->isTableItem)
				{
					if (pg.tagName()=="PAGEOBJECT")
					{
						TableItems.append(Neu);
						TableID.insert(pg.attribute("OwnLINK", "0").toInt(), Neu->ItemNr);
					}
					else if (pg.tagName()=="FRAMEOBJECT")
					{
						TableItemsF.append(Neu);
						TableIDF.insert(pg.attribute("OwnLINK", "0").toInt(), Neu->ItemNr);
					}
					else
					{
						TableItemsM.append(Neu);
						TableIDM.insert(pg.attribute("OwnLINK", "0").toInt(), Neu->ItemNr);
					}
				}
				/*
				if ((pg.tagName()=="PAGEOBJECT") || (pg.tagName()=="FRAMEOBJECT"))
				{
					//m_Doc->DocItems = m_Doc->Items;
					//m_Doc->DocPages = m_Doc->Pages;
				}
				else
				{
					//m_Doc->MasterItems = m_Doc->Items;
					//m_Doc->MasterPages = m_Doc->Pages;
				}
				*/
				m_Doc->setMasterPageMode(false);
				//m_Doc->Pages=&m_Doc->DocPages;
				counter++;
			}
			PAGE=PAGE.nextSibling();
		}
		PAGE=DOC.firstChild();
		while(!PAGE.isNull())
		{
			QDomElement pg=PAGE.toElement();
			if(pg.tagName()=="Bookmark")
			{
				int elem = pg.attribute("Element").toInt();
				if (elem < m_Doc->Items->count())
				{
					bok.Title = pg.attribute("Title");
					bok.Text = pg.attribute("Text");
					bok.Aktion = pg.attribute("Aktion");
					bok.ItemNr = pg.attribute("ItemNr").toInt();
					bok.PageObject = m_Doc->Items->at(elem);
					bok.First = pg.attribute("First").toInt();
					bok.Last = pg.attribute("Last").toInt();
					bok.Prev = pg.attribute("Prev").toInt();
					bok.Next = pg.attribute("Next").toInt();
					bok.Parent = pg.attribute("Parent").toInt();
					m_Doc->BookMarks.append(bok);
				}
			}
			PAGE=PAGE.nextSibling();
		}
		DOC=DOC.nextSibling();
	}
	if (TableItemsF.count() != 0)
	{
		for (int ttc = 0; ttc < TableItemsF.count(); ++ttc)
		{
			PageItem* ta = TableItemsF.at(ttc);
			if (ta->TopLinkID != -1)
				ta->TopLink = m_Doc->FrameItems.at(TableIDF[ta->TopLinkID]);
			else
				ta->TopLink = 0;
			if (ta->LeftLinkID != -1)
				ta->LeftLink = m_Doc->FrameItems.at(TableIDF[ta->LeftLinkID]);
			else
				ta->LeftLink = 0;
			if (ta->RightLinkID != -1)
				ta->RightLink = m_Doc->FrameItems.at(TableIDF[ta->RightLinkID]);
			else
				ta->RightLink = 0;
			if (ta->BottomLinkID != -1)
				ta->BottomLink = m_Doc->FrameItems.at(TableIDF[ta->BottomLinkID]);
			else
				ta->BottomLink = 0;
		}
	}
	if (TableItemsM.count() != 0)
	{
		for (int ttc = 0; ttc < TableItemsM.count(); ++ttc)
		{
			PageItem* ta = TableItemsM.at(ttc);
			if (ta->TopLinkID != -1)
				ta->TopLink = m_Doc->MasterItems.at(TableIDM[ta->TopLinkID]);
			else
				ta->TopLink = 0;
			if (ta->LeftLinkID != -1)
				ta->LeftLink = m_Doc->MasterItems.at(TableIDM[ta->LeftLinkID]);
			else
				ta->LeftLink = 0;
			if (ta->RightLinkID != -1)
				ta->RightLink = m_Doc->MasterItems.at(TableIDM[ta->RightLinkID]);
			else
				ta->RightLink = 0;
			if (ta->BottomLinkID != -1)
				ta->BottomLink = m_Doc->MasterItems.at(TableIDM[ta->BottomLinkID]);
			else
				ta->BottomLink = 0;
		}
	}
	if (TableItems.count() != 0)
	{
		for (int ttc = 0; ttc < TableItems.count(); ++ttc)
		{
			PageItem* ta = TableItems.at(ttc);
			if (ta->TopLinkID != -1)
				ta->TopLink = m_Doc->Items->at(TableID[ta->TopLinkID]);
			else
				ta->TopLink = 0;
			if (ta->LeftLinkID != -1)
				ta->LeftLink = m_Doc->Items->at(TableID[ta->LeftLinkID]);
			else
				ta->LeftLink = 0;
			if (ta->RightLinkID != -1)
				ta->RightLink = m_Doc->Items->at(TableID[ta->RightLinkID]);
			else
				ta->RightLink = 0;
			if (ta->BottomLinkID != -1)
				ta->BottomLink = m_Doc->Items->at(TableID[ta->BottomLinkID]);
			else
				ta->BottomLink = 0;
		}
	}
	m_Doc->setMasterPageMode(false);
	m_Doc->setLoading(false);
	m_Doc->reformPages(true);
	m_Doc->setLoading(true);

	handleOldLayerBehavior(m_Doc);
	if (m_Doc->Layers.count() == 0)
	{
		ScLayer* nl = m_Doc->Layers.newLayer( QObject::tr("Background") );
		nl->flowControl  = false;
		layerToSetActive = nl->ID;
	}
	m_Doc->setActiveLayer(layerToSetActive);
	
	// reestablish textframe links
	if (itemNext.count() != 0)
	{
		QMap<int,int>::Iterator lc;
		for (lc = itemNext.begin(); lc != itemNext.end(); ++lc)
		{
			if (itemRemap[lc.value()] >= 0)
			{
				PageItem * Its = m_Doc->Items->at(lc.key());
				PageItem * Itn = m_Doc->Items->at(itemRemap[lc.value()]);
				if (Itn->prevInChain() || Its->nextInChain()) 
				{
					qDebug("scribus13format: corruption in linked textframes detected");
					continue;
				}
				Its->link(Itn);
			}
		}
	}

	// reestablish first/lastAuto
	m_Doc->FirstAuto = m_Doc->LastAuto;
	if (m_Doc->LastAuto)
	{
		while (m_Doc->LastAuto->nextInChain())
			m_Doc->LastAuto = m_Doc->LastAuto->nextInChain();
		while (m_Doc->FirstAuto->prevInChain())
			m_Doc->FirstAuto = m_Doc->FirstAuto->prevInChain();
	}

	// start auto save timer if needed
	if (m_Doc->autoSave() && ScCore->usingGUI())
		m_Doc->autoSaveTimer->start(m_Doc->autoSaveTime());
	
	if (m_mwProgressBar!=0)
		m_mwProgressBar->setValue(DOC.childNodes().count());

	QMessageBox::warning(ScCore->primaryMainWindow(),
						  CommonStrings::trWarning,
						  tr("You have opened a file produced by Scribus 1.3.3.x.\n"
						     "If you save it in this version, it will no longer be readable by older Scribus versions."));

	return true;
// 	return false;
}

bool Scribus13Format::saveFile(const QString & fileName, const FileFormat & /* fmt */)
{
	QString text, tf, tf2, tc, tc2;
	QDomDocument docu("scribus");
	QString st="<SCRIBUSUTF8NEW></SCRIBUSUTF8NEW>";
	docu.setContent(st);
	QDomElement elem=docu.documentElement();
	elem.setAttribute("Version", QString(VERSION));
	QDomElement dc=docu.createElement("DOCUMENT");
	dc.setAttribute("ANZPAGES",m_Doc->DocPages.count());
	dc.setAttribute("PAGEWIDTH",m_Doc->pageWidth);
	dc.setAttribute("PAGEHEIGHT",m_Doc->pageHeight);
	dc.setAttribute("BORDERLEFT",m_Doc->pageMargins.Left);
	dc.setAttribute("BORDERRIGHT",m_Doc->pageMargins.Right);
	dc.setAttribute("BORDERTOP",m_Doc->pageMargins.Top);
	dc.setAttribute("BORDERBOTTOM",m_Doc->pageMargins.Bottom);
	dc.setAttribute("PRESET",m_Doc->marginPreset);
	dc.setAttribute("ORIENTATION",m_Doc->PageOri);
	dc.setAttribute("PAGESIZE",m_Doc->m_pageSize);
	dc.setAttribute("FIRSTNUM",m_Doc->FirstPnum);
	dc.setAttribute("BOOK", m_Doc->currentPageLayout);
	if(m_Doc->usesAutomaticTextFrames())
		dc.setAttribute("AUTOTEXT",1);
	dc.setAttribute("AUTOSPALTEN",m_Doc->PageSp);
	dc.setAttribute("ABSTSPALTEN",m_Doc->PageSpa);
	dc.setAttribute("UNITS",m_Doc->unitIndex());
	dc.setAttribute("DFONT",m_Doc->itemToolPrefs().textFont);
	dc.setAttribute("DSIZE",m_Doc->itemToolPrefs().textSize / 10.0);
	dc.setAttribute("DCOL",m_Doc->itemToolPrefs().textColumns);
	dc.setAttribute("DGAP",m_Doc->itemToolPrefs().textColumnGap);
	dc.setAttribute("TabFill",m_Doc->itemToolPrefs().textTabFillChar);
	dc.setAttribute("TabWidth",m_Doc->itemToolPrefs().textTabWidth);
	dc.setAttribute("AUTHOR",m_Doc->documentInfo.getAuthor());
	dc.setAttribute("COMMENTS",m_Doc->documentInfo.getComments());
	dc.setAttribute("KEYWORDS",m_Doc->documentInfo.getKeywords());
	dc.setAttribute("PUBLISHER",m_Doc->documentInfo.getPublisher());
	dc.setAttribute("DOCDATE",m_Doc->documentInfo.getDate());
	dc.setAttribute("DOCTYPE",m_Doc->documentInfo.getType());
	dc.setAttribute("DOCFORMAT",m_Doc->documentInfo.getFormat());
	dc.setAttribute("DOCIDENT",m_Doc->documentInfo.getIdent());
	dc.setAttribute("DOCSOURCE",m_Doc->documentInfo.getSource());
	dc.setAttribute("DOCLANGINFO",m_Doc->documentInfo.getLangInfo());
	dc.setAttribute("DOCRELATION",m_Doc->documentInfo.getRelation());
	dc.setAttribute("DOCCOVER",m_Doc->documentInfo.getCover());
	dc.setAttribute("DOCRIGHTS",m_Doc->documentInfo.getRights());
	dc.setAttribute("DOCCONTRIB",m_Doc->documentInfo.getContrib());
	dc.setAttribute("TITLE",m_Doc->documentInfo.getTitle());
	dc.setAttribute("VHOCH",m_Doc->typographicPrefs().valueSuperScript);
	dc.setAttribute("VHOCHSC",m_Doc->typographicPrefs().scalingSuperScript);
	dc.setAttribute("VTIEF",m_Doc->typographicPrefs().valueSubScript);
	dc.setAttribute("VTIEFSC",m_Doc->typographicPrefs().scalingSubScript);
	dc.setAttribute("VKAPIT",m_Doc->typographicPrefs().valueSmallCaps);
	dc.setAttribute("BASEGRID",m_Doc->guidesPrefs().valueBaselineGrid);
	dc.setAttribute("BASEO", m_Doc->guidesPrefs().offsetBaselineGrid);
	dc.setAttribute("AUTOL", m_Doc->typographicPrefs().autoLineSpacing);
	dc.setAttribute("UnderlinePos", m_Doc->typographicPrefs().valueUnderlinePos);
	dc.setAttribute("UnderlineWidth", m_Doc->typographicPrefs().valueUnderlineWidth);
	dc.setAttribute("StrikeThruPos", m_Doc->typographicPrefs().valueStrikeThruPos);
	dc.setAttribute("StrikeThruWidth", m_Doc->typographicPrefs().valueStrikeThruWidth);
	dc.setAttribute("GROUPC",m_Doc->GroupCounter);
	dc.setAttribute("HCMS", static_cast<int>(m_Doc->HasCMS));
	dc.setAttribute("DPSo", static_cast<int>(m_Doc->CMSSettings.SoftProofOn));
	dc.setAttribute("DPSFo", static_cast<int>(m_Doc->CMSSettings.SoftProofFullOn));
	dc.setAttribute("DPuse", static_cast<int>(m_Doc->CMSSettings.CMSinUse));
	dc.setAttribute("DPgam", static_cast<int>(m_Doc->CMSSettings.GamutCheck));
	dc.setAttribute("DPbla", static_cast<int>(m_Doc->CMSSettings.BlackPoint));
	dc.setAttribute("DPMo",m_Doc->CMSSettings.DefaultMonitorProfile);
	dc.setAttribute("DPPr",m_Doc->CMSSettings.DefaultPrinterProfile);
	dc.setAttribute("DPIn",m_Doc->CMSSettings.DefaultImageRGBProfile);
	dc.setAttribute("DPInCMYK",m_Doc->CMSSettings.DefaultImageCMYKProfile);
	dc.setAttribute("DPIn2",m_Doc->CMSSettings.DefaultSolidColorRGBProfile);
	dc.setAttribute("DPIn3",m_Doc->CMSSettings.DefaultSolidColorCMYKProfile);
	dc.setAttribute("DISc",m_Doc->CMSSettings.DefaultIntentColors);
	dc.setAttribute("DIIm",m_Doc->CMSSettings.DefaultIntentImages);
	dc.setAttribute("ALAYER", m_Doc->activeLayer());
	dc.setAttribute("LANGUAGE", m_Doc->hyphLanguage());
	dc.setAttribute("MINWORDLEN", m_Doc->hyphMinimumWordLength());
	dc.setAttribute("HYCOUNT", m_Doc->hyphConsecutiveLines());
	dc.setAttribute("AUTOMATIC", static_cast<int>(m_Doc->hyphAutomatic()));
	dc.setAttribute("AUTOCHECK", static_cast<int>(m_Doc->hyphAutoCheck()));
	dc.setAttribute("GUIDELOCK", static_cast<int>(m_Doc->GuideLock));
	dc.setAttribute("SnapToGuides", static_cast<int>(m_Doc->SnapGuides));
	dc.setAttribute("SnapToGrid", static_cast<int>(m_Doc->useRaster));
	dc.setAttribute("MINGRID", m_Doc->guidesPrefs().minorGridSpacing);
	dc.setAttribute("MAJGRID", m_Doc->guidesPrefs().majorGridSpacing);
	dc.setAttribute("SHOWGRID", static_cast<int>(m_Doc->guidesPrefs().gridShown));
	dc.setAttribute("SHOWGUIDES", static_cast<int>(m_Doc->guidesPrefs().guidesShown));
	dc.setAttribute("showcolborders", static_cast<int>(m_Doc->guidesPrefs().colBordersShown));
	dc.setAttribute("SHOWFRAME", static_cast<int>(m_Doc->guidesPrefs().framesShown));
	dc.setAttribute("SHOWLAYERM", static_cast<int>(m_Doc->guidesPrefs().layerMarkersShown));
	dc.setAttribute("SHOWMARGIN", static_cast<int>(m_Doc->guidesPrefs().marginsShown));
	dc.setAttribute("SHOWBASE", static_cast<int>(m_Doc->guidesPrefs().baselineGridShown));
	dc.setAttribute("SHOWPICT", static_cast<int>(m_Doc->guidesPrefs().showPic));
	dc.setAttribute("SHOWControl", static_cast<int>(m_Doc->guidesPrefs().showControls));
	dc.setAttribute("SHOWLINK", static_cast<int>(m_Doc->guidesPrefs().linkShown));
	dc.setAttribute("rulerMode", static_cast<int>(m_Doc->guidesPrefs().rulerMode));
	dc.setAttribute("showrulers", static_cast<int>(m_Doc->guidesPrefs().rulersShown));
	dc.setAttribute("rulerXoffset", m_Doc->rulerXoffset);
	dc.setAttribute("rulerYoffset", m_Doc->rulerYoffset);
	dc.setAttribute("GuideRad", m_Doc->guidesPrefs().guideRad);
	dc.setAttribute("GRAB",m_Doc->guidesPrefs().grabRadius);
	dc.setAttribute("POLYC", m_Doc->itemToolPrefs().polyCorners);
	dc.setAttribute("POLYF", m_Doc->itemToolPrefs().polyFactor);
	dc.setAttribute("POLYR", m_Doc->itemToolPrefs().polyRotation);
	dc.setAttribute("POLYFD", m_Doc->itemToolPrefs().polyFactorGuiVal);
	dc.setAttribute("POLYS", static_cast<int>(m_Doc->itemToolPrefs().polyUseFactor));
	dc.setAttribute("AutoSave", static_cast<int>(m_Doc->autoSave()));
	dc.setAttribute("AutoSaveTime", m_Doc->autoSaveTime());
	dc.setAttribute("ScratchBottom", m_Doc->scratch()->Bottom);
	dc.setAttribute("ScratchLeft", m_Doc->scratch()->Left);
	dc.setAttribute("ScratchRight", m_Doc->scratch()->Right);
	dc.setAttribute("ScratchTop", m_Doc->scratch()->Top);
	dc.setAttribute("StartArrow", m_Doc->itemToolPrefs().lineStartArrow);
	dc.setAttribute("EndArrow", m_Doc->itemToolPrefs().lineEndArrow);
	dc.setAttribute("PEN",m_Doc->itemToolPrefs().shapeLineColor);
	dc.setAttribute("BRUSH",m_Doc->itemToolPrefs().shapeFillColor);
	dc.setAttribute("PENLINE",m_Doc->itemToolPrefs().lineColor);
	dc.setAttribute("PENTEXT",m_Doc->itemToolPrefs().textColor);
	dc.setAttribute("StrokeText",m_Doc->itemToolPrefs().textStrokeColor);
	dc.setAttribute("TextBackGround", m_Doc->itemToolPrefs().textFillColor);
	dc.setAttribute("TextLineColor", m_Doc->itemToolPrefs().textLineColor);
	dc.setAttribute("TextBackGroundShade", m_Doc->itemToolPrefs().textFillColorShade);
	dc.setAttribute("TextLineShade", m_Doc->itemToolPrefs().textLineColorShade);
	dc.setAttribute("TextPenShade", m_Doc->itemToolPrefs().textShade);
	dc.setAttribute("TextStrokeShade", m_Doc->itemToolPrefs().textStrokeShade);
	dc.setAttribute("STIL",m_Doc->itemToolPrefs().shapeLineStyle);
	dc.setAttribute("STILLINE",m_Doc->itemToolPrefs().lineStyle);
	dc.setAttribute("WIDTH",m_Doc->itemToolPrefs().shapeLineWidth);
	dc.setAttribute("WIDTHLINE",m_Doc->itemToolPrefs().lineWidth);
	dc.setAttribute("PENSHADE",m_Doc->itemToolPrefs().shapeLineColorShade);
	dc.setAttribute("LINESHADE",m_Doc->itemToolPrefs().lineColorShade);
	dc.setAttribute("BRUSHSHADE",m_Doc->itemToolPrefs().shapeFillColorShade);
	dc.setAttribute("MAGMIN",m_Doc->opToolPrefs().magMin);
	dc.setAttribute("MAGMAX",m_Doc->opToolPrefs().magMax);
	dc.setAttribute("MAGSTEP",m_Doc->opToolPrefs().magStep);
	dc.setAttribute("CPICT",m_Doc->itemToolPrefs().imageFillColor);
	dc.setAttribute("PICTSHADE",m_Doc->itemToolPrefs().imageFillColorShade);
	dc.setAttribute("PICTSCX",m_Doc->itemToolPrefs().imageScaleX);
	dc.setAttribute("PICTSCY",m_Doc->itemToolPrefs().imageScaleY);
	dc.setAttribute("PSCALE", static_cast<int>(m_Doc->itemToolPrefs().imageScaleType));
	dc.setAttribute("PASPECT", static_cast<int>(m_Doc->itemToolPrefs().imageAspectRatio));
	dc.setAttribute("EmbeddedPath", static_cast<int>(m_Doc->itemToolPrefs().imageUseEmbeddedPath));
	dc.setAttribute("HalfRes", m_Doc->itemToolPrefs().imageLowResType);
	dc.setAttribute("MINORC",m_Doc->guidesPrefs().minorGridColor.name());
	dc.setAttribute("MAJORC",m_Doc->guidesPrefs().majorGridColor.name());
	dc.setAttribute("GuideC", m_Doc->guidesPrefs().guideColor.name());
	dc.setAttribute("BaseC", m_Doc->guidesPrefs().baselineGridColor.name());
	dc.setAttribute("GuideZ", m_Doc->guidesPrefs().guideRad);
	dc.setAttribute("BACKG", static_cast<int>(m_Doc->guidesPrefs().guidePlacement));
	dc.setAttribute("PAGEC",m_Doc->paperColor().name());
	dc.setAttribute("MARGC",m_Doc->guidesPrefs().marginColor.name());
	dc.setAttribute("RANDF", static_cast<int>(m_Doc->marginColored()));
	dc.setAttribute("currentProfile", m_Doc->curCheckProfile());
	CheckerPrefsList::Iterator itcp;
	CheckerPrefsList::Iterator itcpend=m_Doc->checkerProfiles().end();
	for (itcp = m_Doc->checkerProfiles().begin(); itcp != itcpend; ++itcp)
	{
		QDomElement dc79a=docu.createElement("CheckProfile");
		dc79a.setAttribute("Name",itcp.key());
		dc79a.setAttribute("ignoreErrors", static_cast<int>(itcp.value().ignoreErrors));
		dc79a.setAttribute("autoCheck", static_cast<int>(itcp.value().autoCheck));
		dc79a.setAttribute("checkGlyphs", static_cast<int>(itcp.value().checkGlyphs));
		dc79a.setAttribute("checkOrphans", static_cast<int>(itcp.value().checkOrphans));
		dc79a.setAttribute("checkOverflow", static_cast<int>(itcp.value().checkOverflow));
		dc79a.setAttribute("checkPictures", static_cast<int>(itcp.value().checkPictures));
		dc79a.setAttribute("checkResolution", static_cast<int>(itcp.value().checkResolution));
		dc79a.setAttribute("checkTransparency", static_cast<int>(itcp.value().checkTransparency));
		dc79a.setAttribute("minResolution",itcp.value().minResolution);
		dc79a.setAttribute("maxResolution",itcp.value().maxResolution);
		dc79a.setAttribute("checkAnnotations", static_cast<int>(itcp.value().checkAnnotations));
		dc79a.setAttribute("checkRasterPDF", static_cast<int>(itcp.value().checkRasterPDF));
		dc79a.setAttribute("checkForGIF", static_cast<int>(itcp.value().checkForGIF));
		dc.appendChild(dc79a);
	}
	QMap<QString,multiLine>::Iterator itMU;
	for (itMU = m_Doc->MLineStyles.begin(); itMU != m_Doc->MLineStyles.end(); ++itMU)
	{
		QDomElement MuL=docu.createElement("MultiLine");
		MuL.setAttribute("Name",itMU.key());
		multiLine ml = itMU.value();
		multiLine::iterator itMU2;
		for (itMU2 = ml.begin(); itMU2 != ml.end(); ++itMU2)
		{
			QDomElement SuL=docu.createElement("SubLine");
			SuL.setAttribute("Color", (*itMU2).Color);
			SuL.setAttribute("Shade", (*itMU2).Shade);
			SuL.setAttribute("Dash", (*itMU2).Dash);
			SuL.setAttribute("LineEnd", (*itMU2).LineEnd);
			SuL.setAttribute("LineJoin", (*itMU2).LineJoin);
			SuL.setAttribute("Width", (*itMU2).Width);
			MuL.appendChild(SuL);
		}
		dc.appendChild(MuL);
	}
	QList<ArrowDesc>::Iterator itar;
	for (itar = m_Doc->arrowStyles().begin(); itar != m_Doc->arrowStyles().end(); ++itar)
	{
		if ((*itar).userArrow)
		{
			QDomElement ar=docu.createElement("Arrows");
			ar.setAttribute("NumPoints", (*itar).points.size());
			QString arp = "";
			QString tmp, tmpy;
			double xa, ya;
			for (uint nxx = 0; nxx < (*itar).points.size(); ++nxx)
			{
				(*itar).points.point(nxx, &xa, &ya);
				arp += tmp.setNum(xa) + " " + tmpy.setNum(ya) + " ";
			}
			ar.setAttribute("Points", arp);
			ar.setAttribute("Name", (*itar).name);
			dc.appendChild(ar);
		}
	}
	QMap<QString,QString>::Iterator itja;
	for (itja = m_Doc->JavaScripts.begin(); itja != m_Doc->JavaScripts.end(); ++itja)
	{
		QDomElement jav=docu.createElement("JAVA");
		jav.setAttribute("NAME",itja.key());
		jav.setAttribute("SCRIPT",itja.value());
		dc.appendChild(jav);
	}
	QList<ScribusDoc::BookMa>::Iterator itbm;
	for (itbm = m_Doc->BookMarks.begin(); itbm != m_Doc->BookMarks.end(); ++itbm)
	{
		QDomElement fn=docu.createElement("Bookmark");
		fn.setAttribute("Title",(*itbm).Title);
		fn.setAttribute("Text",(*itbm).Text);
		fn.setAttribute("Aktion",(*itbm).Aktion);
		fn.setAttribute("ItemNr", (*itbm).ItemNr);
		fn.setAttribute("Element", (*itbm).PageObject->ItemNr);
		fn.setAttribute("First", (*itbm).First);
		fn.setAttribute("Last", (*itbm).Last);
		fn.setAttribute("Prev", (*itbm).Prev);
		fn.setAttribute("Next", (*itbm).Next);
		fn.setAttribute("Parent", (*itbm).Parent);
		dc.appendChild(fn);
	}
	ColorList::Iterator itc;
	for (itc = m_Doc->PageColors.begin(); itc != m_Doc->PageColors.end(); ++itc)
	{
		QDomElement co=docu.createElement("COLOR");
		co.setAttribute("NAME",itc.key());
		if (m_Doc->PageColors[itc.key()].getColorModel() == colorModelRGB)
			co.setAttribute("RGB",m_Doc->PageColors[itc.key()].nameRGB());
		else
			co.setAttribute("CMYK",m_Doc->PageColors[itc.key()].nameCMYK());
		co.setAttribute("Spot",static_cast<int>(m_Doc->PageColors[itc.key()].isSpotColor()));
		co.setAttribute("Register",static_cast<int>(m_Doc->PageColors[itc.key()].isRegistrationColor()));
		dc.appendChild(co);
	}
//	if (m_Doc->docParagraphStyles.count() > 5)
	{
		for (int ff = 0; ff < m_Doc->paragraphStyles().count(); ++ff)
		{
			QDomElement fo=docu.createElement("STYLE");
			fo.setAttribute("NAME",m_Doc->paragraphStyles()[ff].name());
			fo.setAttribute("ALIGN",m_Doc->paragraphStyles()[ff].alignment());
			fo.setAttribute("LINESPMode",m_Doc->paragraphStyles()[ff].lineSpacingMode());
			fo.setAttribute("LINESP",m_Doc->paragraphStyles()[ff].lineSpacing());
			fo.setAttribute("INDENT",m_Doc->paragraphStyles()[ff].leftMargin());
			fo.setAttribute("RMARGIN",m_Doc->paragraphStyles()[ff].rightMargin());
			fo.setAttribute("FIRST",m_Doc->paragraphStyles()[ff].firstIndent());
			fo.setAttribute("VOR",m_Doc->paragraphStyles()[ff].gapBefore());
			fo.setAttribute("NACH",m_Doc->paragraphStyles()[ff].gapAfter());
			fo.setAttribute("FONT",m_Doc->paragraphStyles()[ff].charStyle().font().scName());
			fo.setAttribute("FONTSIZE",m_Doc->paragraphStyles()[ff].charStyle().fontSize() / 10.0);
			fo.setAttribute("DROP", static_cast<int>(m_Doc->paragraphStyles()[ff].hasDropCap()));
			fo.setAttribute("DROPLIN", m_Doc->paragraphStyles()[ff].dropCapLines());
			fo.setAttribute("DROPDIST", m_Doc->paragraphStyles()[ff].dropCapOffset());
			fo.setAttribute("EFFECT", m_Doc->paragraphStyles()[ff].charStyle().effects());
			if (m_Doc->paragraphStyles()[ff].tabValues().count() != 0)
			{
				for (int a = 0; a < m_Doc->paragraphStyles()[ff].tabValues().count(); ++a)
				{
					QDomElement tabs = docu.createElement("Tabs");
					tabs.setAttribute("Type", (m_Doc->paragraphStyles()[ff].tabValues().at(a)).tabType);
					tabs.setAttribute("Pos", (m_Doc->paragraphStyles()[ff].tabValues().at(a)).tabPosition);
					QString tabCh = "";
					if (!(m_Doc->paragraphStyles()[ff].tabValues().at(a)).tabFillChar.isNull())
						tabCh = QString((m_Doc->paragraphStyles()[ff].tabValues().at(a)).tabFillChar);
					tabs.setAttribute("Fill", tabCh);
					fo.appendChild(tabs);
				}
			}
			fo.setAttribute("FCOLOR",m_Doc->paragraphStyles()[ff].charStyle().fillColor());
			fo.setAttribute("FSHADE",m_Doc->paragraphStyles()[ff].charStyle().fillShade());
			fo.setAttribute("SCOLOR",m_Doc->paragraphStyles()[ff].charStyle().strokeColor());
			fo.setAttribute("SSHADE",m_Doc->paragraphStyles()[ff].charStyle().strokeShade());
			fo.setAttribute("BASE", static_cast<int>(m_Doc->paragraphStyles()[ff].lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing));
			fo.setAttribute("TXTSHX",m_Doc->paragraphStyles()[ff].charStyle().shadowXOffset() / 10.0);
			fo.setAttribute("TXTSHY",m_Doc->paragraphStyles()[ff].charStyle().shadowYOffset() / 10.0);
			fo.setAttribute("TXTOUT",m_Doc->paragraphStyles()[ff].charStyle().outlineWidth() / 10.0);
			fo.setAttribute("TXTULP",m_Doc->paragraphStyles()[ff].charStyle().underlineOffset() / 10.0);
			fo.setAttribute("TXTULW",m_Doc->paragraphStyles()[ff].charStyle().underlineWidth() / 10.0);
			fo.setAttribute("TXTSTP",m_Doc->paragraphStyles()[ff].charStyle().strikethruOffset() / 10.0);
			fo.setAttribute("TXTSTW",m_Doc->paragraphStyles()[ff].charStyle().strikethruWidth() / 10.0);
			fo.setAttribute("SCALEH",m_Doc->paragraphStyles()[ff].charStyle().scaleH() / 10.0);
			fo.setAttribute("SCALEV",m_Doc->paragraphStyles()[ff].charStyle().scaleV() / 10.0);
			fo.setAttribute("BASEO",m_Doc->paragraphStyles()[ff].charStyle().baselineOffset() / 10.0);
			fo.setAttribute("KERN",m_Doc->paragraphStyles()[ff].charStyle().tracking() / 10.0);
			dc.appendChild(fo);
		}
	}
	uint layerCount=m_Doc->layerCount();
	for (uint lay = 0; lay < layerCount; ++lay)
	{
		QDomElement la = docu.createElement("LAYERS");
		la.setAttribute("NUMMER",m_Doc->Layers[lay].ID);
		la.setAttribute("LEVEL",m_Doc->Layers[lay].Level);
		la.setAttribute("NAME",m_Doc->Layers[lay].Name);
		la.setAttribute("SICHTBAR", static_cast<int>(m_Doc->Layers[lay].isViewable));
		la.setAttribute("DRUCKEN", static_cast<int>(m_Doc->Layers[lay].isPrintable));
		la.setAttribute("EDIT", static_cast<int>(m_Doc->Layers[lay].isEditable));
		la.setAttribute("FLOW", static_cast<int>(m_Doc->Layers[lay].flowControl));
		la.setAttribute("TRANS", m_Doc->Layers[lay].transparency);
		la.setAttribute("BLEND", m_Doc->Layers[lay].blendMode);
		la.setAttribute("OUTL", static_cast<int>(m_Doc->Layers[lay].outlineMode));
		la.setAttribute("LAYERC",m_Doc->Layers[lay].markerColor.name());
		dc.appendChild(la);
	}
	QDomElement pdf = docu.createElement("PDF");
	pdf.setAttribute("Thumbnails", static_cast<int>(m_Doc->pdfOptions().Thumbnails));
	pdf.setAttribute("Articles", static_cast<int>(m_Doc->pdfOptions().Articles));
	pdf.setAttribute("Bookmarks", static_cast<int>(m_Doc->pdfOptions().Bookmarks));
	pdf.setAttribute("Compress", static_cast<int>(m_Doc->pdfOptions().Compress));
	pdf.setAttribute("CMethod", m_Doc->pdfOptions().CompressMethod);
	pdf.setAttribute("Quality", m_Doc->pdfOptions().Quality);
	pdf.setAttribute("MirrorH", static_cast<int>(m_Doc->pdfOptions().MirrorH));
	pdf.setAttribute("MirrorV", static_cast<int>(m_Doc->pdfOptions().MirrorV));
	pdf.setAttribute("Clip", static_cast<int>(m_Doc->pdfOptions().doClip));
	pdf.setAttribute("RotateDeg", static_cast<int>(m_Doc->pdfOptions().RotateDeg));
	pdf.setAttribute("PresentMode", static_cast<int>(m_Doc->pdfOptions().PresentMode));
	pdf.setAttribute("RecalcPic", static_cast<int>(m_Doc->pdfOptions().RecalcPic));
	pdf.setAttribute("Grayscale", static_cast<int>(m_Doc->pdfOptions().isGrayscale));
	pdf.setAttribute("RGBMode", static_cast<int>(m_Doc->pdfOptions().UseRGB));
	pdf.setAttribute("UseProfiles", static_cast<int>(m_Doc->pdfOptions().UseProfiles));
	pdf.setAttribute("UseProfiles2", static_cast<int>(m_Doc->pdfOptions().UseProfiles2));
	pdf.setAttribute("Binding", m_Doc->pdfOptions().Binding);
	pdf.setAttribute("PicRes", m_Doc->pdfOptions().PicRes);
	pdf.setAttribute("Resolution", m_Doc->pdfOptions().Resolution);
	pdf.setAttribute("Version", m_Doc->pdfOptions().Version);
	pdf.setAttribute("Intent", m_Doc->pdfOptions().Intent);
	pdf.setAttribute("Intent2", m_Doc->pdfOptions().Intent2);
	pdf.setAttribute("SolidP", m_Doc->pdfOptions().SolidProf);
	pdf.setAttribute("ImageP", m_Doc->pdfOptions().ImageProf);
	pdf.setAttribute("PrintP", m_Doc->pdfOptions().PrintProf);
	pdf.setAttribute("InfoString", m_Doc->pdfOptions().Info);
	pdf.setAttribute("BTop", m_Doc->pdfOptions().bleeds.Top);
	pdf.setAttribute("BLeft", m_Doc->pdfOptions().bleeds.Left);
	pdf.setAttribute("BRight", m_Doc->pdfOptions().bleeds.Right);
	pdf.setAttribute("BBottom", m_Doc->pdfOptions().bleeds.Bottom);
	pdf.setAttribute("ImagePr", static_cast<int>(m_Doc->pdfOptions().EmbeddedI));
	pdf.setAttribute("PassOwner", m_Doc->pdfOptions().PassOwner);
	pdf.setAttribute("PassUser", m_Doc->pdfOptions().PassUser);
	pdf.setAttribute("Permissions", m_Doc->pdfOptions().Permissions);
	pdf.setAttribute("Encrypt", static_cast<int>(m_Doc->pdfOptions().Encrypt));
	pdf.setAttribute("UseLayers", static_cast<int>(m_Doc->pdfOptions().useLayers));
	pdf.setAttribute("UseLpi", static_cast<int>(m_Doc->pdfOptions().UseLPI));
	pdf.setAttribute("UseSpotColors", static_cast<int>(m_Doc->pdfOptions().UseSpotColors));
	pdf.setAttribute("doMultiFile", static_cast<int>(m_Doc->pdfOptions().doMultiFile));
	pdf.setAttribute("displayBookmarks", static_cast<int>(m_Doc->pdfOptions().displayBookmarks));
	pdf.setAttribute("displayFullscreen", static_cast<int>(m_Doc->pdfOptions().displayFullscreen));
	pdf.setAttribute("displayLayers", static_cast<int>(m_Doc->pdfOptions().displayLayers));
	pdf.setAttribute("displayThumbs", static_cast<int>(m_Doc->pdfOptions().displayThumbs));
	pdf.setAttribute("hideMenuBar", static_cast<int>(m_Doc->pdfOptions().hideMenuBar));
	pdf.setAttribute("hideToolBar", static_cast<int>(m_Doc->pdfOptions().hideToolBar));
	pdf.setAttribute("fitWindow", static_cast<int>(m_Doc->pdfOptions().fitWindow));
	pdf.setAttribute("PageLayout", m_Doc->pdfOptions().PageLayout);
	pdf.setAttribute("openAction", m_Doc->pdfOptions().openAction);
	for (int pdoF = 0; pdoF < m_Doc->pdfOptions().EmbedList.count(); ++pdoF)
	{
		QDomElement pdf2 = docu.createElement("Fonts");
		pdf2.setAttribute("Name", m_Doc->pdfOptions().EmbedList[pdoF]);
		pdf.appendChild(pdf2);
	}
	for (int pdoS = 0; pdoS < m_Doc->pdfOptions().SubsetList.count(); ++pdoS)
	{
		QDomElement pdf4 = docu.createElement("Subset");
		pdf4.setAttribute("Name", m_Doc->pdfOptions().SubsetList[pdoS]);
		pdf.appendChild(pdf4);
	}
	for (int pdoE = 0; pdoE < m_Doc->pdfOptions().PresentVals.count(); ++pdoE)
	{
		QDomElement pdf3 = docu.createElement("Effekte");
		pdf3.setAttribute("pageEffectDuration", m_Doc->pdfOptions().PresentVals[pdoE].pageEffectDuration);
		pdf3.setAttribute("pageViewDuration", m_Doc->pdfOptions().PresentVals[pdoE].pageViewDuration);
		pdf3.setAttribute("effectType", m_Doc->pdfOptions().PresentVals[pdoE].effectType);
		pdf3.setAttribute("Dm", m_Doc->pdfOptions().PresentVals[pdoE].Dm);
		pdf3.setAttribute("M", m_Doc->pdfOptions().PresentVals[pdoE].M);
		pdf3.setAttribute("Di", m_Doc->pdfOptions().PresentVals[pdoE].Di);
		pdf.appendChild(pdf3);
	}
	QMap<QString,LPIData>::Iterator itlp;
	for (itlp = m_Doc->pdfOptions().LPISettings.begin(); itlp != m_Doc->pdfOptions().LPISettings.end(); ++itlp)
	{
		QDomElement pdf4 = docu.createElement("LPI");
		pdf4.setAttribute("Color", itlp.key());
		pdf4.setAttribute("Frequency", itlp.value().Frequency);
		pdf4.setAttribute("Angle", itlp.value().Angle);
		pdf4.setAttribute("SpotFunction", itlp.value().SpotFunc);
		pdf.appendChild(pdf4);
	}
	dc.appendChild(pdf);
	QDomElement docItemAttrs = docu.createElement("DocItemAttributes");
	for(ObjAttrVector::Iterator objAttrIt = m_Doc->itemAttributes().begin() ; objAttrIt != m_Doc->itemAttributes().end(); ++objAttrIt )
	{
		QDomElement itemAttr = docu.createElement("ItemAttribute");
		itemAttr.setAttribute("Name", (*objAttrIt).name);
		itemAttr.setAttribute("Type", (*objAttrIt).type);
		itemAttr.setAttribute("Value", (*objAttrIt).value);
		itemAttr.setAttribute("Parameter", (*objAttrIt).parameter);
		itemAttr.setAttribute("Relationship", (*objAttrIt).relationship);
		itemAttr.setAttribute("RelationshipTo", (*objAttrIt).relationshipto);
		itemAttr.setAttribute("AutoAddTo", (*objAttrIt).autoaddto);
		docItemAttrs.appendChild(itemAttr);
	}
	dc.appendChild(docItemAttrs);
	QDomElement tocElem = docu.createElement("TablesOfContents");
	for(ToCSetupVector::Iterator tocSetupIt = m_Doc->tocSetups().begin() ; tocSetupIt != m_Doc->tocSetups().end(); ++tocSetupIt )
	{
		QDomElement tocsetup = docu.createElement("TableOfContents");
		tocsetup.setAttribute("Name", (*tocSetupIt).name);
		tocsetup.setAttribute("ItemAttributeName", (*tocSetupIt).itemAttrName);
		tocsetup.setAttribute("FrameName", (*tocSetupIt).frameName);
		tocsetup.setAttribute("ListNonPrinting", (*tocSetupIt).listNonPrintingFrames);
		tocsetup.setAttribute("Style", (*tocSetupIt).textStyle);
		switch ((*tocSetupIt).pageLocation)
		{
			case Beginning:
				tocsetup.setAttribute("NumberPlacement", "Beginning");
				break;
			case End:
				tocsetup.setAttribute("NumberPlacement", "End");
				break;
			case NotShown:
				tocsetup.setAttribute("NumberPlacement", "NotShown");
				break;
		}
		tocElem.appendChild(tocsetup);
	}
	dc.appendChild(tocElem);
	QDomElement sectionElem = docu.createElement("Sections");
	for(DocumentSectionMap::Iterator it = m_Doc->sections.begin() ; it != m_Doc->sections.end(); ++it )
	{
		QDomElement currsection = docu.createElement("Section");
		currsection.setAttribute("Number", (*it).number);
		currsection.setAttribute("Name", (*it).name);
		currsection.setAttribute("From", (*it).fromindex);
		currsection.setAttribute("To", (*it).toindex);
		switch ((*it).type)
		{
			case Type_1_2_3:
				currsection.setAttribute("Type", "Type_1_2_3");
				break;
			case Type_i_ii_iii:
				currsection.setAttribute("Type", "Type_i_ii_iii");
				break;
			case Type_I_II_III:
				currsection.setAttribute("Type", "Type_I_II_III");
				break;
			case Type_a_b_c:
				currsection.setAttribute("Type", "Type_a_b_c");
				break;
			case Type_A_B_C:
				currsection.setAttribute("Type", "Type_A_B_C");
				break;
			case Type_None:
				currsection.setAttribute("Type", "Type_None");
				break;
		}
		currsection.setAttribute("Start", (*it).sectionstartindex);
		currsection.setAttribute("Reversed", (*it).reversed);
		currsection.setAttribute("Active", (*it).active);
		sectionElem.appendChild(currsection);
	}
	dc.appendChild(sectionElem);

	QDomElement pageSetAttr = docu.createElement("PageSets");
	QList<PageSet>::Iterator itpgset;
	QList<PageSet> pageSet(m_Doc->pageSets());
	for(itpgset = pageSet.begin(); itpgset != pageSet.end(); ++itpgset )
	{
		QDomElement pgst = docu.createElement("Set");
		pgst.setAttribute("Name", (*itpgset).Name);
		pgst.setAttribute("FirstPage", (*itpgset).FirstPage);
		pgst.setAttribute("Rows", (*itpgset).Rows);
		pgst.setAttribute("Columns", (*itpgset).Columns);
//		pgst.setAttribute("GapHorizontal", (*itpgset).GapHorizontal);
//		pgst.setAttribute("GapVertical", (*itpgset).GapVertical);
//		pgst.setAttribute("GapBelow", (*itpgset).GapBelow);
		QStringList pNames = (*itpgset).pageNames;
		QStringList::Iterator itpgsetN;
		for(itpgsetN = pNames.begin(); itpgsetN != pNames.end(); ++itpgsetN )
		{
			QDomElement pgstN = docu.createElement("PageNames");
			pgstN.setAttribute("Name", (*itpgsetN));
			pgst.appendChild(pgstN);
		}
		pageSetAttr.appendChild(pgst);
	}
	dc.appendChild(pageSetAttr);
	if (m_mwProgressBar != 0)
	{
		m_mwProgressBar->setMaximum(m_Doc->DocPages.count()+m_Doc->MasterPages.count()+m_Doc->DocItems.count()+m_Doc->MasterItems.count()+m_Doc->FrameItems.count());
		m_mwProgressBar->setValue(0);
	}
	QString baseDir = QFileInfo(fileName).absolutePath();;
	WritePages(m_Doc, &docu, &dc, m_mwProgressBar, 0, true);
	WritePages(m_Doc, &docu, &dc, m_mwProgressBar, m_Doc->MasterPages.count(), false);
	WriteObjects(m_Doc, &docu, &dc, baseDir, m_mwProgressBar, m_Doc->MasterPages.count()+m_Doc->DocPages.count(), 2);
	WriteObjects(m_Doc, &docu, &dc, baseDir, m_mwProgressBar, m_Doc->MasterPages.count()+m_Doc->DocPages.count()+m_Doc->FrameItems.count(), 0);
	WriteObjects(m_Doc, &docu, &dc, baseDir, m_mwProgressBar, m_Doc->MasterPages.count()+m_Doc->DocPages.count()+m_Doc->MasterItems.count()+m_Doc->FrameItems.count(), 1);
	elem.appendChild(dc);
/**
 * changed to enable saving
 * of *.gz documents
 * 2.7.2002 C.Toepp
 * <c.toepp@gmx.de>
*/
	QByteArray cs = docu.toByteArray(); // UTF-8 QCString
	if(fileName.right(2) == "gz")
	{
		// zipped saving
		// XXX: latin1() should probably be local8Bit()
		if (!ScGzFile::writeToFile(fileName, cs))
			return false;
	}
	else
	{
		QFile f(fileName);
		if(!f.open(QIODevice::WriteOnly))
			return false;
		QDataStream s(&f);
		s.writeRawData(cs, cs.length());
		f.close();
	}
	return true;
}

// Low level plugin API
int scribus13format_getPluginAPIVersion()
{
	return PLUGIN_API_VERSION;
}

ScPlugin* scribus13format_getPlugin()
{
	Scribus13Format* plug = new Scribus13Format();
	Q_CHECK_PTR(plug);
	return plug;
}

void scribus13format_freePlugin(ScPlugin* plugin)
{
	Scribus13Format* plug = dynamic_cast<Scribus13Format*>(plugin);
	Q_ASSERT(plug);
	delete plug;
}

/*
const ScFace& Scribus13Format::findFont(ScribusDoc *doc, const QString& fontname)
{
	if (fontname.isEmpty())
		return ScFace::none();
	
	PrefsManager* prefsManager=PrefsManager::instance();
	if (!(*m_AvailableFonts).contains(fontname) || !(*m_AvailableFonts)[fontname].usable())
	{
		if ((!prefsManager->appPrefs.GFontSub.contains(fontname)) || (!(*m_AvailableFonts)[prefsManager->appPrefs.GFontSub[fontname]].usable()))
		{
			newReplacement = true;
			ReplacedFonts.insert(fontname, doc->itemToolPrefs().textFont);
		}
		else
			ReplacedFonts.insert(fontname, prefsManager->appPrefs.GFontSub[fontname]);
		ScFace dummy = (*m_AvailableFonts)[ReplacedFonts[fontname]].mkReplacementFor(fontname, doc->DocName);
		(*m_AvailableFonts).insert(fontname, dummy);
	}
	else if ( !doc->UsedFonts.contains(fontname) )
	{
		doc->AddFont(fontname, qRound(doc->itemToolPrefs().defSize / 10.0));
	}
	return (*m_AvailableFonts)[fontname];
}
*/
void Scribus13Format::GetItemText(QDomElement *it, ScribusDoc *doc, PageItem* obj, LastStyles* last, bool impo, bool VorLFound)
{
	ScFace dummy = ScFace::none();
	QString tmp2, tmpf;
	CharStyle newStyle;

	tmp2 = it->attribute("CH");
	tmp2.replace(QRegExp("\r"), QChar(13));
	tmp2.replace(QRegExp("\n"), QChar(13));
	tmp2.replace(QRegExp("\t"), QChar(9));
	tmp2.replace(SpecialChars::OLD_NBHYPHEN, SpecialChars::NBHYPHEN);
	tmp2.replace(SpecialChars::OLD_NBSPACE, SpecialChars::NBSPACE);
	tmpf = it->attribute("CFONT", "");

	if (! tmpf.isEmpty() )
		newStyle.setFont(m_AvailableFonts->findFont(tmpf, doc));

	if (it->hasAttribute("CSIZE"))
		newStyle.setFontSize(qRound(ScCLocale::toDoubleC(it->attribute("CSIZE")) * 10));
	
	if (it->hasAttribute("CCOLOR"))
		newStyle.setFillColor(it->attribute("CCOLOR"));

	if (it->hasAttribute("CSHADE"))
		newStyle.setFillShade(it->attribute("CSHADE").toInt());

	QString fColor = newStyle.fillColor();
	int fShade = qRound(newStyle.fillShade());
	handleOldColorShade(doc, fColor, fShade);
	newStyle.setFillColor(fColor);
	newStyle.setFillShade(fShade);
	
	if (it->hasAttribute("CEXTRA"))
	{
		double cv = ScCLocale::toDoubleC(it->attribute("CEXTRA"));
		double cs = ScCLocale::toDoubleC(it->attribute("CSIZE"));
		newStyle.setTracking(qRound(cv / cs * 1000.0));
	}
	else if (it->hasAttribute("CKERN"))
		newStyle.setTracking(it->attribute("CKERN").toInt());
	
	if (it->hasAttribute("CSTYLE"))
		newStyle.setFeatures(static_cast<StyleFlag>(it->attribute("CSTYLE").toInt()).featureList());

	QString pstylename = it->attribute("PSTYLE", "");
	int calign = it->attribute("CALIGN", "-1").toInt();		
	
	int ab = it->attribute("CAB", "-1").toInt();
	if (ab >= 5) {
		pstylename = DoVorl[ab];
		calign = -1;
	}
	else if (ab >= 0) {
		pstylename = "";
		calign = ab;
	}
	
	if (it->hasAttribute("CSTROKE"))
		newStyle.setStrokeColor(it->attribute("CSTROKE", CommonStrings::None));
	
	if (it->hasAttribute("CSHADE2"))
		newStyle.setStrokeShade(it->attribute("CSHADE2", "100").toInt());

	QString sColor = newStyle.strokeColor();
	int sShade = qRound(newStyle.strokeShade());
	handleOldColorShade(doc, sColor, sShade);
	newStyle.setStrokeColor(sColor);
	newStyle.setStrokeShade(sShade);
	
	if (it->hasAttribute("CSCALE"))
		newStyle.setScaleH(qMin(qMax(qRound(ScCLocale::toDoubleC(it->attribute("CSCALE"), 100.0) * 10), 100), 4000));
	
	if (it->hasAttribute("CSCALEV"))
		newStyle.setScaleV(qMin(qMax(qRound(ScCLocale::toDoubleC(it->attribute("CSCALEV"), 100.0) * 10), 100), 4000));
	
	if (it->hasAttribute("CBASE"))
		newStyle.setBaselineOffset(qRound(ScCLocale::toDoubleC(it->attribute("CBASE"), 0.0) * 10));

	if (it->hasAttribute("CSHX"))
		newStyle.setShadowXOffset(qRound(ScCLocale::toDoubleC(it->attribute("CSHX"), 5.0) * 10));

	if (it->hasAttribute("CSHY"))
		newStyle.setShadowYOffset(qRound(ScCLocale::toDoubleC(it->attribute("CSHY"), -5.0) * 10));
	
	if (it->hasAttribute("COUT"))
		newStyle.setOutlineWidth(qRound(ScCLocale::toDoubleC(it->attribute("COUT"), 1.0) * 10));

	if (it->hasAttribute("CULP"))
		newStyle.setUnderlineOffset(qRound(ScCLocale::toDoubleC(it->attribute("CULP"), -0.1) * 10));

	if (it->hasAttribute("CULW"))
		newStyle.setUnderlineWidth(qRound(ScCLocale::toDoubleC(it->attribute("CULW"), -0.1) * 10));

	
	if (it->hasAttribute("CSTP"))
		newStyle.setStrikethruOffset(qRound(ScCLocale::toDoubleC(it->attribute("CSTP"), -0.1) * 10));
	
	if (it->hasAttribute("CSTW"))
		newStyle.setStrikethruWidth(qRound(ScCLocale::toDoubleC(it->attribute("CSTW"), -0.1) * 10));

	int iobj = it->attribute("COBJ", "-1").toInt();
	for (int cxx=0; cxx<tmp2.length(); ++cxx)
	{
		QChar ch = tmp2.at(cxx);		
		{ // Legacy mode
			if (ch == QChar(5))
				ch = SpecialChars::PARSEP;
			if (ch == QChar(4))
				ch = SpecialChars::TAB;
		}
		
		if (impo && ab >= 0 && VorLFound)
			last->ParaStyle = DoVorl[ab];
		else
			last->ParaStyle = pstylename;

		int pos = obj->itemText.length();
		if (ch == SpecialChars::OBJECT) {
			if (iobj >= 0) {
				if (iobj < doc->FrameItems.count())
					obj->itemText.insertObject(pos, doc->FrameItems.at(iobj));
				else
					qDebug() << QString("scribus13format: invalid inline frame used in text object : %1").arg(iobj);
			}
		}
		else {
			obj->itemText.insertChars(pos, QString(ch));
		}
		if (newStyle != last->Style) {
//			qDebug() << QString("new style at %1: %2 -> %3").arg(pos).arg(last->Style.asString()).arg(newStyle.asString();
			obj->itemText.applyCharStyle(last->StyleStart, pos-last->StyleStart, last->Style);
			last->Style = newStyle;
			last->StyleStart = pos;
		}
		if (ch == SpecialChars::PARSEP) {
			ParagraphStyle pstyle;
			pstyle.setParent( last->ParaStyle );
			if (calign >= 0)
				pstyle.setAlignment(static_cast<ParagraphStyle::AlignmentType>(calign));
//			qDebug() << QString("par style at %1: %2/%3 (%4) calign %5").arg(pos).arg(pstyle.name()).arg(pstyle.parent()).arg(last->ParaStyle).arg(calign);
			obj->itemText.applyStyle(pos, pstyle);
		}
	}
	obj->itemText.applyCharStyle(last->StyleStart, obj->itemText.length()-last->StyleStart, last->Style);
	ParagraphStyle pstyle;
	pstyle.setParent( last->ParaStyle );
	if (calign >= 0)
		pstyle.setAlignment(static_cast<ParagraphStyle::AlignmentType>(calign));
//	qDebug() << QString("par style at end: %1/%2 (%3) calign %4").arg(pstyle.name()).arg(pstyle.parent()).arg(last->ParaStyle).arg(calign);
	obj->itemText.applyStyle(obj->itemText.length()-1, pstyle);
	//last->StyleStart = obj->itemText.length();
}


void Scribus13Format::readParagraphStyle(ParagraphStyle& vg, const QDomElement& pg, ScribusDoc *doc)
{
	vg.setName(pg.attribute("NAME"));
	vg.setLineSpacingMode(static_cast<ParagraphStyle::LineSpacingMode>(pg.attribute("LINESPMode", "0").toInt()));
	vg.setLineSpacing(ScCLocale::toDoubleC(pg.attribute("LINESP")));
	vg.setLeftMargin(ScCLocale::toDoubleC(pg.attribute("INDENT"), 0.0));
	if (pg.hasAttribute("RMARGIN"))
		vg.setRightMargin(ScCLocale::toDoubleC(pg.attribute("RMARGIN"), 0.0));
	else
		vg.setRightMargin(0);
	vg.setFirstIndent(ScCLocale::toDoubleC(pg.attribute("FIRST"), 0.0));
	vg.setAlignment(static_cast<ParagraphStyle::AlignmentType>(pg.attribute("ALIGN").toInt()));
	vg.setGapBefore(ScCLocale::toDoubleC(pg.attribute("VOR"), 0.0));
	vg.setGapAfter(ScCLocale::toDoubleC(pg.attribute("NACH"), 0.0));
	
	vg.charStyle().setFont(m_AvailableFonts->findFont(pg.attribute("FONT", doc->itemToolPrefs().textFont), doc));
	vg.charStyle().setFontSize(qRound(ScCLocale::toDoubleC(pg.attribute("FONTSIZE"), 12.0) * 10.0));
	vg.setHasDropCap(static_cast<bool>(pg.attribute("DROP", "0").toInt()));
	vg.setDropCapLines(pg.attribute("DROPLIN", "2").toInt());
	vg.setDropCapOffset(ScCLocale::toDoubleC(pg.attribute("DROPDIST"), 0.0));
	vg.charStyle().setFeatures(static_cast<StyleFlag>(pg.attribute("EFFECT", "0").toInt()).featureList());
	QString fColor = pg.attribute("FCOLOR", doc->itemToolPrefs().shapeFillColor);
	int fShade = pg.attribute("FSHADE", "100").toInt();
	handleOldColorShade(doc, fColor, fShade);
	QString sColor = pg.attribute("SCOLOR", doc->itemToolPrefs().shapeLineColor);
	int sShade = pg.attribute("SSHADE", "100").toInt();
	handleOldColorShade(doc, sColor, sShade);
	vg.charStyle().setFillColor(fColor);
	vg.charStyle().setFillShade(fShade);
	vg.charStyle().setStrokeColor(sColor);
	vg.charStyle().setStrokeShade(sShade);
	if (static_cast<bool>(pg.attribute("BASE", "0").toInt()))
		vg.setLineSpacingMode(ParagraphStyle::BaselineGridLineSpacing);
	vg.charStyle().setShadowXOffset(qRound(ScCLocale::toDoubleC(pg.attribute("TXTSHX"), 5.0) * 10));
	vg.charStyle().setShadowYOffset(qRound(ScCLocale::toDoubleC(pg.attribute("TXTSHY"), -5.0) * 10));
	vg.charStyle().setOutlineWidth(qRound(ScCLocale::toDoubleC(pg.attribute("TXTOUT"), 1.0) * 10));
	vg.charStyle().setUnderlineOffset(qRound(ScCLocale::toDoubleC(pg.attribute("TXTULP"), -0.1) * 10));
	vg.charStyle().setUnderlineWidth(qRound(ScCLocale::toDoubleC(pg.attribute("TXTULW"), -0.1) * 10));
	vg.charStyle().setStrikethruOffset(qRound(ScCLocale::toDoubleC(pg.attribute("TXTSTP"), -0.1) * 10));
	vg.charStyle().setStrikethruWidth(qRound(ScCLocale::toDoubleC(pg.attribute("TXTSTW"), -0.1) * 10));
	vg.charStyle().setScaleH(qRound(ScCLocale::toDoubleC(pg.attribute("SCALEH"), 100.0) * 10));
	vg.charStyle().setScaleV(qRound(ScCLocale::toDoubleC(pg.attribute("SCALEV"), 100.0) * 10));
	vg.charStyle().setBaselineOffset(qRound(ScCLocale::toDoubleC(pg.attribute("BASEO"), 0.0) * 10));
	vg.charStyle().setTracking(qRound(ScCLocale::toDoubleC(pg.attribute("KERN"), 0.0) * 10));
//		vg.tabValues().clear();
	if ((pg.hasAttribute("NUMTAB")) && (pg.attribute("NUMTAB", "0").toInt() != 0))
	{
		QList<ParagraphStyle::TabRecord> tbs;
		ParagraphStyle::TabRecord tb;
		QString tmp = pg.attribute("TABS");
		ScTextStream tgv(&tmp, QIODevice::ReadOnly);
		double xf, xf2;
		for (int cxv = 0; cxv < pg.attribute("NUMTAB", "0").toInt(); cxv += 2)
		{
			tgv >> xf;
			tgv >> xf2;
			tb.tabPosition = xf2;
			tb.tabType = static_cast<int>(xf);
			tb.tabFillChar =  QChar();
			tbs.append(tb);
		}
		vg.setTabValues(tbs);
		tmp = "";
	}
	else
	{
		QList<ParagraphStyle::TabRecord> tbs;
 		vg.setTabValues(tbs);
		QDomNode IT = pg.firstChild();
		while(!IT.isNull())
		{
			QDomElement it = IT.toElement();
			if (it.tagName()=="Tabs")
			{
				ParagraphStyle::TabRecord tb;
				tb.tabPosition = ScCLocale::toDoubleC(it.attribute("Pos"));
				tb.tabType = it.attribute("Type").toInt();
				QString tbCh = "";
				tbCh = it.attribute("Fill","");
				if (tbCh.isEmpty())
					tb.tabFillChar = QChar();
				else
					tb.tabFillChar = tbCh[0];
				tbs.append(tb);
			}
// 			vg.setTabValues(tbs);
			IT=IT.nextSibling();
		}
		if (tbs.count() > 0)
			vg.setTabValues(tbs);
	}
}

PageItem* Scribus13Format::PasteItem(QDomElement *obj, ScribusDoc *doc, const QString& baseDir, int pagenr)
{
	struct ImageLoadRequest loadingInfo;
	int z = 0;
	PageItem::ItemType pt = static_cast<PageItem::ItemType>(obj->attribute("PTYPE").toInt());
	double x  = ScCLocale::toDoubleC(obj->attribute("XPOS"));
	double y  = ScCLocale::toDoubleC(obj->attribute("YPOS"));
	double w  = ScCLocale::toDoubleC(obj->attribute("WIDTH"));
	double h  = ScCLocale::toDoubleC(obj->attribute("HEIGHT"));
	double pw = ScCLocale::toDoubleC(obj->attribute("PWIDTH"));
	double offsX = ScCLocale::toDoubleC(obj->attribute("LOCALX"));
	double offsY = ScCLocale::toDoubleC(obj->attribute("LOCALY"));
	double scx = ScCLocale::toDoubleC(obj->attribute("LOCALSCX"));
	double scy = ScCLocale::toDoubleC(obj->attribute("LOCALSCY"));
	double rot = ScCLocale::toDoubleC(obj->attribute("LOCALROT"));
	QString Pcolor = obj->attribute("PCOLOR");
	if (Pcolor.isEmpty())
		Pcolor = "None";
	QString Pcolor2 = obj->attribute("PCOLOR2");
	if (Pcolor2.isEmpty())
		Pcolor2 = "None";
	int Pshade = obj->attribute("SHADE").toInt();
	int Pshade2 = obj->attribute("SHADE2").toInt();
	handleOldColorShade(doc, Pcolor, Pshade);
	handleOldColorShade(doc, Pcolor2, Pshade2);
	QColor tmpc;
	PageItem *currItem=NULL;
	QString tmp;
	int xi;
	double xf, yf, xf2;
	QString clPath;
	QDomNode IT;
	switch (pt)
	{
	// OBSOLETE CR 2005-02-06
	case PageItem::ItemType1:
		z = doc->itemAdd(PageItem::Polygon, PageItem::Ellipse, x, y, w, h, pw, Pcolor, Pcolor2, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		break;
	//
	case PageItem::ImageFrame:
		z = doc->itemAdd(PageItem::ImageFrame, PageItem::Unspecified, x, y, w, h, 1, doc->itemToolPrefs().imageFillColor, CommonStrings::None, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		UndoManager::instance()->setUndoEnabled(false);
		currItem->ScaleType = obj->attribute("SCALETYPE", "1").toInt();
		currItem->AspectRatio = obj->attribute("RATIO", "0").toInt();
		currItem->setImageXYScale(scx, scy);
		currItem->setImageXYOffset(offsX, offsY);
		currItem->setImageRotation(rot);
		currItem->Pfile     = Relative2Path(obj->attribute("PFILE"), baseDir);
		currItem->IProfile  = obj->attribute("PRFILE","");
		currItem->EmProfile = obj->attribute("EPROF","");
		currItem->IRender   = (eRenderIntent) obj->attribute("IRENDER", "1").toInt();
		currItem->UseEmbedded = obj->attribute("EMBEDDED", "1").toInt();
		currItem->pixm.imgInfo.lowResType = obj->attribute("ImageRes", "1").toInt();
		IT = obj->firstChild();
		while(!IT.isNull())
		{
			QDomElement it = IT.toElement();
			if (it.tagName()=="ImageEffect")
			{
				struct ImageEffect ef;
				ef.effectParameters = it.attribute("Param");
				ef.effectCode = it.attribute("Code").toInt();
				currItem->effectsInUse.append(ef);
			}
			IT=IT.nextSibling();
		}
		if (!currItem->Pfile.isEmpty())
			doc->loadPict(currItem->Pfile, currItem, false);
		currItem->IProfile  = obj->attribute("PRFILE","");
		currItem->EmProfile = obj->attribute("EPROF","");
		currItem->IRender   = (eRenderIntent) obj->attribute("IRENDER", "1").toInt();
		currItem->UseEmbedded = obj->attribute("EMBEDDED", "1").toInt();
		currItem->setImageXYScale(scx, scy);
		clPath = obj->attribute("ImageClip", "");
		if (currItem->pixm.imgInfo.PDSpathData.contains(clPath))
		{
			currItem->imageClip = currItem->pixm.imgInfo.PDSpathData[clPath].copy();
			currItem->pixm.imgInfo.usedPath = clPath;
			QTransform cl;
			cl.translate(currItem->imageXOffset()*currItem->imageXScale(), currItem->imageYOffset()*currItem->imageYScale());
			cl.scale(currItem->imageXScale(), currItem->imageYScale());
			currItem->imageClip.map(cl);
		}
		currItem->setImageShown(obj->attribute("PICART").toInt());
/*		currItem->BBoxX = obj->attribute("BBOXX").toDouble();
		currItem->BBoxH = obj->attribute("BBOXH").toDouble(); */
		currItem->setLineWidth(pw);
		if (currItem->pixm.imgInfo.layerInfo.count() != 0)
		{
			bool found = false;
			IT = obj->firstChild();
			while(!IT.isNull())
			{
				QDomElement it = IT.toElement();
				if (it.tagName() == "PSDLayer")
				{
					found = true;
					loadingInfo.blend = it.attribute("Blend");
					loadingInfo.opacity = it.attribute("Opacity").toInt();
					loadingInfo.visible = static_cast<bool>(it.attribute("Visible").toInt());
					loadingInfo.useMask = static_cast<bool>(it.attribute("useMask", "1").toInt());
					currItem->pixm.imgInfo.RequestProps.insert(it.attribute("Layer").toInt(), loadingInfo);
				}
				IT=IT.nextSibling();
			}
			if (found)
			{
				currItem->pixm.imgInfo.isRequest = true;
				doc->loadPict(currItem->Pfile, currItem, true);
			}
		}
		UndoManager::instance()->setUndoEnabled(true);
		break;
	// OBSOLETE CR 2005-02-06
	case PageItem::ItemType3:
		z = doc->itemAdd(PageItem::Polygon, PageItem::Rectangle, x, y, w, h, pw, Pcolor, Pcolor2, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		break;
	//
	case PageItem::PathText:
		z = doc->itemAdd(PageItem::PathText, PageItem::Unspecified, x, y, w, h, pw, CommonStrings::None, Pcolor, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		UndoManager::instance()->setUndoEnabled(false);
		if ((obj->attribute("ANNOTATION", "0").toInt()) && (static_cast<bool>(obj->attribute("ANICON", "0").toInt())))
		{
			currItem->ScaleType = obj->attribute("SCALETYPE", "1").toInt();
			currItem->AspectRatio = obj->attribute("RATIO", "0").toInt();
			currItem->setImageXYScale(scx, scy);
			currItem->setImageXYOffset(offsX, offsY);
			currItem->setImageRotation(rot);
			currItem->Pfile  = Relative2Path(obj->attribute("PFILE" ,""), baseDir);
			currItem->Pfile2 = Relative2Path(obj->attribute("PFILE2",""), baseDir);
			currItem->Pfile3 = Relative2Path(obj->attribute("PFILE3",""), baseDir);
			currItem->IProfile  = obj->attribute("PRFILE","");
			currItem->EmProfile = obj->attribute("EPROF","");
			currItem->IRender   = (eRenderIntent) obj->attribute("IRENDER", "1").toInt();
			currItem->UseEmbedded = obj->attribute("EMBEDDED", "1").toInt();
			doc->LoadPict(currItem->Pfile, z);
			currItem->setImageXYScale(scx, scy);
			currItem->setImageShown(obj->attribute("PICART").toInt());
/*			currItem->BBoxX = obj->attribute("BBOXX").toDouble();
			currItem->BBoxH = obj->attribute("BBOXH").toDouble(); */
		}
		//currItem->convertTo(pt);
		UndoManager::instance()->setUndoEnabled(true);
		break;
	case PageItem::TextFrame:
		z = doc->itemAdd(PageItem::TextFrame, PageItem::Unspecified, x, y, w, h, pw, CommonStrings::None, Pcolor, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		UndoManager::instance()->setUndoEnabled(false);
		if ((obj->attribute("ANNOTATION", "0").toInt()) && (static_cast<bool>(obj->attribute("ANICON", "0").toInt())))
		{
			currItem->ScaleType = obj->attribute("SCALETYPE", "1").toInt();
			currItem->AspectRatio = obj->attribute("RATIO", "0").toInt();
			currItem->setImageXYScale(scx, scy);
			currItem->setImageXYOffset(offsX, offsY);
			currItem->setImageRotation(rot);
			currItem->Pfile  = Relative2Path(obj->attribute("PFILE" ,""), baseDir);
			currItem->Pfile2 = Relative2Path(obj->attribute("PFILE2",""), baseDir);
			currItem->Pfile3 = Relative2Path(obj->attribute("PFILE3",""), baseDir);
			currItem->IProfile  = obj->attribute("PRFILE","");
			currItem->EmProfile = obj->attribute("EPROF","");
			currItem->IRender   = (eRenderIntent) obj->attribute("IRENDER", "1").toInt();
			currItem->UseEmbedded = obj->attribute("EMBEDDED", "1").toInt();
			doc->LoadPict(currItem->Pfile, z);
			currItem->setImageXYScale(scx, scy);
			currItem->setImageShown(obj->attribute("PICART").toInt());
/*			currItem->BBoxX = obj->attribute("BBOXX").toDouble();
			currItem->BBoxH = obj->attribute("BBOXH").toDouble(); */
		}
		//currItem->convertTo(pt);
		UndoManager::instance()->setUndoEnabled(true);
		break;
	case PageItem::Line:
		z = doc->itemAdd(PageItem::Line, PageItem::Unspecified, x, y, w, h, pw, CommonStrings::None, Pcolor2, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		break;
	case PageItem::Polygon:
		z = doc->itemAdd(PageItem::Polygon, PageItem::Unspecified, x, y, w, h, pw, Pcolor, Pcolor2, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		break;
	case PageItem::PolyLine:
		z = doc->itemAdd(PageItem::PolyLine, PageItem::Unspecified, x, y, w, h, pw, Pcolor, Pcolor2, true);
		currItem = doc->Items->at(z);
		if (pagenr > -2) 
			currItem->OwnPage = pagenr;
		break;
	case PageItem::Multiple:
	default:
		assert(false);
		break;
	}

	UndoManager::instance()->setUndoEnabled(false);
	currItem->FrameType = obj->attribute("FRTYPE", "0").toInt();
	int startArrowIndex = obj->attribute("startArrowIndex", "0").toInt();
	if ((startArrowIndex < 0) || (startArrowIndex > static_cast<int>(doc->arrowStyles().size())))
	{
		qDebug() << QString("scribus13format: invalid arrow index: %").arg(startArrowIndex);
		startArrowIndex = 0;
	}
	currItem->setStartArrowIndex(startArrowIndex);
	int endArrowIndex = obj->attribute("endArrowIndex", "0").toInt();
	if ((endArrowIndex < 0) || (endArrowIndex > static_cast<int>(doc->arrowStyles().size())))
	{
		qDebug() << QString("scribus13format: invalid arrow index: %").arg(endArrowIndex);
		endArrowIndex = 0;
	}
	currItem->setEndArrowIndex(endArrowIndex);
	currItem->NamedLStyle = obj->attribute("NAMEDLST", "");
	currItem->isBookmark = obj->attribute("BOOKMARK").toInt();
	if ((currItem->isBookmark) && (doc->BookMarks.count() == 0))
		doc->OldBM = true;
	currItem->setImageFlippedH(obj->attribute("FLIPPEDH").toInt());
	currItem->setImageFlippedV(obj->attribute("FLIPPEDV").toInt());
	currItem->setCornerRadius(ScCLocale::toDoubleC(obj->attribute("RADRECT"), 0.0));
	currItem->ClipEdited = obj->attribute("CLIPEDIT", "0").toInt();
	currItem->setFillColor(Pcolor);
	if (currItem->lineWidth() == 0.0)
		currItem->setLineColor(CommonStrings::None);
	else
		currItem->setLineColor(Pcolor2);
	currItem->setFillShade(Pshade);
	currItem->setLineShade(Pshade2);
	ParagraphStyle pstyle;
	pstyle.setLineSpacing(ScCLocale::toDoubleC(obj->attribute("LINESP")));
	pstyle.setLineSpacingMode(static_cast<ParagraphStyle::LineSpacingMode>(obj->attribute("LINESPMode", "0").toInt()));
	int align = obj->attribute("ALIGN", "-1").toInt();
	if (align >= 5)
		pstyle.setParent(DoVorl[align-5]);
	else if (align >= 0)
		pstyle.setAlignment(static_cast<ParagraphStyle::AlignmentType>(align));
	pstyle.charStyle().setFont(m_AvailableFonts->findFont(obj->attribute("IFONT", m_Doc->itemToolPrefs().textFont), m_Doc));
	pstyle.charStyle().setFontSize(qRound(ScCLocale::toDoubleC(obj->attribute("ISIZE"), 12.0) * 10));
	pstyle.charStyle().setStrokeColor(obj->attribute("TXTSTROKE", CommonStrings::None));
	pstyle.charStyle().setFillColor(obj->attribute("TXTFILL", "Black"));
	pstyle.charStyle().setStrokeShade(obj->attribute("TXTSTRSH", "100").toInt());
	pstyle.charStyle().setFillShade(obj->attribute("TXTFILLSH", "100").toInt());
	pstyle.charStyle().setScaleH(qRound(ScCLocale::toDoubleC(obj->attribute("TXTSCALE"), 100.0) * 10));
	pstyle.charStyle().setScaleV(qRound(ScCLocale::toDoubleC(obj->attribute("TXTSCALEV"), 100.0) * 10));
	pstyle.charStyle().setBaselineOffset(qRound(ScCLocale::toDoubleC(obj->attribute("TXTBASE"), 0.0) * 10));
	pstyle.charStyle().setShadowXOffset(qRound(ScCLocale::toDoubleC(obj->attribute("TXTSHX"), 5.0) * 10));
	pstyle.charStyle().setShadowYOffset(qRound(ScCLocale::toDoubleC(obj->attribute("TXTSHY"), -5.0) * 10));
	pstyle.charStyle().setOutlineWidth(qRound(ScCLocale::toDoubleC(obj->attribute("TXTOUT"), 1.0) * 10));
	pstyle.charStyle().setUnderlineOffset(qRound(ScCLocale::toDoubleC(obj->attribute("TXTULP"), -0.1) * 10));
	pstyle.charStyle().setUnderlineWidth(qRound(ScCLocale::toDoubleC(obj->attribute("TXTULW"), -0.1) * 10));
	pstyle.charStyle().setStrikethruOffset(qRound(ScCLocale::toDoubleC(obj->attribute("TXTSTP"), -0.1) * 10));
	pstyle.charStyle().setStrikethruWidth(qRound(ScCLocale::toDoubleC(obj->attribute("TXTSTW"), -0.1) * 10));
	if (obj->hasAttribute("EXTRAV"))
	{
		double ev = ScCLocale::toDoubleC(obj->attribute("EXTRAV"), 0.0);
		double iv = ScCLocale::toDoubleC(obj->attribute("ISIZE"), 12.0);
		pstyle.charStyle().setTracking(qRound(ev / iv * 10000.0));
	}
	else 
		pstyle.charStyle().setTracking(qRound(ScCLocale::toDoubleC(obj->attribute("TXTKERN"), 0.0) * 10));
	pstyle.charStyle().setFeatures(static_cast<StyleFlag>(obj->attribute("TXTSTYLE", "0").toInt()).featureList());
	tmp = "";
	QList<ParagraphStyle::TabRecord> tbValues;
	if ((obj->hasAttribute("NUMTAB")) && (obj->attribute("NUMTAB", "0").toInt() != 0))
	{
		ParagraphStyle::TabRecord tb;
		tmp = obj->attribute("TABS");
		ScTextStream tgv(&tmp, QIODevice::ReadOnly);
		for (int cxv = 0; cxv < obj->attribute("NUMTAB", "0").toInt(); cxv += 2)
		{
			tgv >> xf;
			tgv >> xf2;
			tb.tabPosition = xf2;
			tb.tabType = static_cast<int>(xf);
			tb.tabFillChar = QChar();
			tbValues.append(tb);
		}
		tmp = "";
	}
	else
	{
		IT = obj->firstChild();
		while(!IT.isNull())
		{
			QDomElement it = IT.toElement();
			if (it.tagName()=="Tabs")
			{
				ParagraphStyle::TabRecord tb;
				tb.tabPosition = ScCLocale::toDoubleC(it.attribute("Pos"));
				tb.tabType = it.attribute("Type").toInt();
				QString tbCh = "";
				tbCh = it.attribute("Fill","");
				if (tbCh.isEmpty())
					tb.tabFillChar = QChar();
				else
					tb.tabFillChar = tbCh[0];
				tbValues.append(tb);
			}
			IT=IT.nextSibling();
		}
	}
	if (tbValues.size() > 0)
		pstyle.setTabValues(tbValues);
	//FIXME: what if linked frames have different styles?
	currItem->itemText.setDefaultStyle(pstyle);

	currItem->setRotation(ScCLocale::toDoubleC(obj->attribute("ROT")));
	currItem->setTextToFrameDist(ScCLocale::toDoubleC(obj->attribute("EXTRA")),
								ScCLocale::toDoubleC(obj->attribute("REXTRA"), 1.0),
								ScCLocale::toDoubleC(obj->attribute("TEXTRA"), 1.0),
								ScCLocale::toDoubleC(obj->attribute("BEXTRA"), 1.0));

	currItem->PLineArt = Qt::PenStyle(obj->attribute("PLINEART").toInt());
	currItem->PLineEnd = Qt::PenCapStyle(obj->attribute("PLINEEND", "0").toInt());
	currItem->PLineJoin = Qt::PenJoinStyle(obj->attribute("PLINEJOIN", "0").toInt());
	currItem->setPrintEnabled(obj->attribute("PRINTABLE").toInt());
	currItem->setIsAnnotation(obj->attribute("ANNOTATION", "0").toInt());
	currItem->annotation().setType(obj->attribute("ANTYPE", "0").toInt());
	QString AnName = obj->attribute("ANNAME","");
	if (!AnName.isEmpty())
	{
		if (currItem->itemName() == AnName)
			currItem->AutoName = true;
		else
		{
			currItem->setItemName(AnName);
			currItem->AutoName = false;
		}
	}
	currItem->annotation().setAction(obj->attribute("ANACTION",""));
	currItem->annotation().setE_act(obj->attribute("ANEACT",""));
	currItem->annotation().setX_act(obj->attribute("ANXACT",""));
	currItem->annotation().setD_act(obj->attribute("ANDACT",""));
	currItem->annotation().setFo_act(obj->attribute("ANFOACT",""));
	currItem->annotation().setBl_act(obj->attribute("ANBLACT",""));
	currItem->annotation().setK_act(obj->attribute("ANKACT",""));
	currItem->annotation().setF_act(obj->attribute("ANFACT",""));
	currItem->annotation().setV_act(obj->attribute("ANVACT",""));
	currItem->annotation().setC_act(obj->attribute("ANCACT",""));
	currItem->annotation().setActionType(obj->attribute("ANACTYP", "0").toInt());
	currItem->annotation().setExtern(obj->attribute("ANEXTERN",""));
	if ((!currItem->annotation().Extern().isEmpty()) && (currItem->annotation().ActionType() != 8))
	{
		QFileInfo efp(currItem->annotation().Extern());
		currItem->annotation().setExtern(efp.absoluteFilePath());
	}
	currItem->annotation().setZiel(obj->attribute("ANZIEL", "0").toInt());
	currItem->annotation().setToolTip(obj->attribute("ANTOOLTIP",""));
	currItem->annotation().setRollOver(obj->attribute("ANROLL",""));
	currItem->annotation().setDown(obj->attribute("ANDOWN",""));
	currItem->annotation().setBwid(obj->attribute("ANBWID", "1").toInt());
	currItem->annotation().setBsty(obj->attribute("ANBSTY", "0").toInt());
	currItem->annotation().setFeed(obj->attribute("ANFEED", "1").toInt());
	currItem->annotation().setFlag(obj->attribute("ANFLAG", "0").toInt());
	currItem->annotation().setFont(obj->attribute("ANFONT", "4").toInt());
	currItem->annotation().setFormat(obj->attribute("ANFORMAT", "0").toInt());
	currItem->annotation().setVis(obj->attribute("ANVIS", "0").toInt());
	currItem->annotation().setIsChk(static_cast<bool>(obj->attribute("ANCHK", "0").toInt()));
	currItem->annotation().setAAact(static_cast<bool>(obj->attribute("ANAA", "0").toInt()));
	currItem->annotation().setHTML(obj->attribute("ANHTML", "0").toInt());
	currItem->annotation().setUseIcons(static_cast<bool>(obj->attribute("ANICON", "0").toInt()));
	currItem->annotation().setChkStil(obj->attribute("ANCHKS", "0").toInt());
	currItem->annotation().setMaxChar(obj->attribute("ANMC", "-1").toInt());
	currItem->annotation().setBorderColor(obj->attribute("ANBCOL", CommonStrings::None));
	currItem->annotation().setIPlace(obj->attribute("ANPLACE", "1").toInt());
	currItem->annotation().setScaleW(obj->attribute("ANSCALE", "0").toInt());
	currItem->TopLine = static_cast<bool>(obj->attribute("TopLine", "0").toInt());
	currItem->LeftLine = static_cast<bool>(obj->attribute("LeftLine", "0").toInt());
	currItem->RightLine = static_cast<bool>(obj->attribute("RightLine", "0").toInt());
	currItem->BottomLine = static_cast<bool>(obj->attribute("BottomLine", "0").toInt());
	currItem->isTableItem = static_cast<bool>(obj->attribute("isTableItem", "0").toInt());
	currItem->TopLinkID =  obj->attribute("TopLINK", "-1").toInt();
	currItem->LeftLinkID =  obj->attribute("LeftLINK", "-1").toInt();
	currItem->RightLinkID =  obj->attribute("RightLINK", "-1").toInt();
	currItem->BottomLinkID =  obj->attribute("BottomLINK", "-1").toInt();
	currItem->PoShow   = obj->attribute("PLTSHOW", "0").toInt();
	currItem->BaseOffs = ScCLocale::toDoubleC(obj->attribute("BASEOF"), 0.0);
	if ( obj->hasAttribute("TEXTFLOWMODE") )
		currItem->setTextFlowMode((PageItem::TextFlowMode) obj->attribute("TEXTFLOWMODE", "0").toInt());
	else if ( obj->attribute("TEXTFLOW").toInt() )
	{
		if (obj->attribute("TEXTFLOW2", "0").toInt())
			currItem->setTextFlowMode(PageItem::TextFlowUsesBoundingBox);
		else if (obj->attribute("TEXTFLOW3", "0").toInt())
			currItem->setTextFlowMode(PageItem::TextFlowUsesContourLine);
		else
			currItem->setTextFlowMode(PageItem::TextFlowUsesFrameShape);	
	}
	else
		currItem->setTextFlowMode(PageItem::TextFlowDisabled);
	currItem->DashOffset = ScCLocale::toDoubleC(obj->attribute("DASHOFF"), 0.0);
	currItem->setReversed(static_cast<bool>(obj->attribute("REVERS", "0").toInt()));
	currItem->setLocked(static_cast<bool>(obj->attribute("LOCK", "0").toInt()));
	currItem->setSizeLocked(static_cast<bool>(obj->attribute("LOCKR", "0").toInt()));
	currItem->setFillTransparency(ScCLocale::toDoubleC(obj->attribute("TransValue"), 0.0));
	currItem->fillRule = static_cast<bool>(obj->attribute("fillRule", "1").toInt());
	currItem->doOverprint = static_cast<bool>(obj->attribute("doOverprint", "0").toInt());
	if (obj->hasAttribute("TransValueS"))
		currItem->setLineTransparency(ScCLocale::toDoubleC(obj->attribute("TransValueS"), 0.0));
	else
		currItem->setLineTransparency(ScCLocale::toDoubleC(obj->attribute("TransValue"), 0.0));
	currItem->setFillBlendmode(0);
	currItem->setLineBlendmode(0);
	if (obj->attribute("TRANSPARENT", "0").toInt() == 1)
		currItem->setFillColor(CommonStrings::None);
	currItem->Cols   = obj->attribute("COLUMNS", "1").toInt();
	currItem->ColGap = ScCLocale::toDoubleC(obj->attribute("COLGAP"), 0.0);
	if (obj->attribute("LAYER", "0").toInt() != -1)
		currItem->LayerID = obj->attribute("LAYER", "0").toInt();
	tmp = "";
	if ((obj->hasAttribute("GROUPS")) && (obj->attribute("NUMGROUP", "0").toInt() != 0))
	{
		int groupMax = doc->GroupCounter;
		QMap<int, int>::ConstIterator gIt;
		tmp = obj->attribute("GROUPS");
		ScTextStream fg(&tmp, QIODevice::ReadOnly);
		currItem->Groups.clear();
		for (int cx = 0; cx < obj->attribute("NUMGROUP", "0").toInt(); ++cx)
		{
			fg >> xi;
			gIt = groupRemap.find(xi);
			if (gIt != groupRemap.end())
				currItem->Groups.push(gIt.value());
			else
			{
				currItem->Groups.push(groupMax); 
				groupRemap.insert(xi, groupMax);
				++groupMax;
			}
		}
		doc->GroupCounter = groupMax;
		tmp = "";
	}
	else
		currItem->Groups.clear();
	if ((obj->hasAttribute("NUMDASH")) && (obj->attribute("NUMDASH", "0").toInt() != 0))
	{
		tmp = obj->attribute("DASHS");
		ScTextStream dgv(&tmp, QIODevice::ReadOnly);
		currItem->DashValues.clear();
		for (int cxv = 0; cxv < obj->attribute("NUMDASH", "0").toInt(); ++cxv)
		{
			dgv >> xf;
			currItem->DashValues.append(xf);
		}
		tmp = "";
	}
	else
		currItem->DashValues.clear();
	tmp = "";
	if (obj->hasAttribute("NUMPO"))
	{
		currItem->PoLine.resize(obj->attribute("NUMPO").toUInt());
		tmp = obj->attribute("POCOOR");
		ScTextStream fp(&tmp, QIODevice::ReadOnly);
		for (uint cx=0; cx<obj->attribute("NUMPO").toUInt(); ++cx)
		{
			fp >> xf;
			fp >> yf;
			currItem->PoLine.setPoint(cx, xf, yf);
		}
	}
	else
		currItem->PoLine.resize(0);
	tmp = "";
	if (obj->hasAttribute("NUMCO"))
	{
		currItem->ContourLine.resize(obj->attribute("NUMCO").toUInt());
		tmp = obj->attribute("COCOOR");
		ScTextStream fp(&tmp, QIODevice::ReadOnly);
		for (uint cx=0; cx<obj->attribute("NUMCO").toUInt(); ++cx)
		{
			fp >> xf;
			fp >> yf;
			currItem->ContourLine.setPoint(cx, xf, yf);
		}
	}
	else
		currItem->ContourLine = currItem->PoLine.copy();
	if (!currItem->asLine())
		currItem->Clip = FlattenPath(currItem->PoLine, currItem->Segments);
	else
	{
		int ph = static_cast<int>(qMax(1.0, currItem->lineWidth() / 2.0));
		currItem->Segments.clear();
		currItem->PoLine.resize(0);
		currItem->Clip.setPoints(4, -ph,-ph, static_cast<int>(currItem->width()+ph),-ph,
		                  static_cast<int>(currItem->width()+ph),static_cast<int>(currItem->height()+ph),
		                  -ph,static_cast<int>(currItem->height()+ph));
		currItem->setHeight(1.0);
	}
	if (currItem->asImageFrame())
		currItem->AdjustPictScale();
	if (currItem->asPathText())
	{
		currItem->updatePolyClip();
		currItem->Frame = true;
	}
	currItem->GrType = obj->attribute("GRTYP", "0").toInt();
	QString GrColor;
	QString GrColor2;
	int GrShade = 0;
	int GrShade2 = 0;
	if (currItem->GrType != 0)
	{
		currItem->GrStartX = ScCLocale::toDoubleC(obj->attribute("GRSTARTX"), 0.0);
		currItem->GrStartY = ScCLocale::toDoubleC(obj->attribute("GRSTARTY"), 0.0);
		currItem->GrEndX = ScCLocale::toDoubleC(obj->attribute("GRENDX"), 0.0);
		currItem->GrEndY = ScCLocale::toDoubleC(obj->attribute("GRENDY"), 0.0);
		GrColor = obj->attribute("GRCOLOR","");
		if (!GrColor.isEmpty())
		{
			GrColor2 = obj->attribute("GRCOLOR2","");
			GrShade = obj->attribute("GRSHADE", "100").toInt();
			GrShade2 = obj->attribute("GRSHADE2", "100").toInt();
		}
	}
	if (currItem->GrType != 0)
	{
		currItem->fill_gradient.clearStops();
		if ((!GrColor.isEmpty()) && (!GrColor2.isEmpty()))
		{
			if (currItem->GrType == 5)
			{
				handleOldColorShade(doc, GrColor, GrShade);
				if ((GrColor != CommonStrings::None) && (!GrColor.isEmpty()))
					currItem->SetQColor(&tmpc, GrColor, GrShade);
				currItem->fill_gradient.addStop(tmpc, 0.0, 0.5, 1.0, GrColor, GrShade);
				handleOldColorShade(doc, GrColor2, GrShade2);
				if ((GrColor2 != CommonStrings::None) && (!GrColor2.isEmpty()))
					currItem->SetQColor(&tmpc, GrColor2, GrShade2);
				currItem->fill_gradient.addStop(tmpc, 1.0, 0.5, 1.0, GrColor2, GrShade2);
			}
			else
			{
				handleOldColorShade(doc, GrColor2, GrShade2);
				if ((GrColor2 != CommonStrings::None) && (!GrColor2.isEmpty()))
					currItem->SetQColor(&tmpc, GrColor2, GrShade2);
				currItem->fill_gradient.addStop(tmpc, 0.0, 0.5, 1.0, GrColor2, GrShade2);
				handleOldColorShade(doc, GrColor, GrShade);
				if ((GrColor != CommonStrings::None) && (!GrColor.isEmpty()))
					currItem->SetQColor(&tmpc, GrColor, GrShade);
				currItem->fill_gradient.addStop(tmpc, 1.0, 0.5, 1.0, GrColor, GrShade);
			}
		}
//		currItem->updateGradientVectors();
	}
	switch (currItem->GrType)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			currItem->GrType = 6;
			break;
		case 5:
			currItem->GrType = 7;
			break;
		default:
			break;
	}
	//currItem->setRedrawBounding();
	//currItem->OwnPage = view->OnPage(currItem);
	UndoManager::instance()->setUndoEnabled(true);
	return currItem;
}

bool Scribus13Format::loadPage(const QString & fileName, int pageNumber, bool Mpage, QString renamedPageName)
{
// 	qDebug() << QString("loading page %2 from file '%1' from 1.3.3.x plugin").arg(fileName).arg(pageNumber);
	if (m_Doc==0 || m_AvailableFonts==0)
	{
		Q_ASSERT(m_Doc==0 || m_AvailableFonts==0);
		return false;
	}
	ParagraphStyle vg;
	struct ScribusDoc::BookMa bok;
	PageItem *Neu;
	Page* Apage = NULL;
	groupRemap.clear();
	itemRemap.clear();
	itemNext.clear();
	itemCount = 0;
	QString tmV, tmp, tmpf, tmp2, tmp3, tmp4, PgNam, Defont, tmf;
	QFont fo;
	ReplacedFonts.clear();
	newReplacement = false;
	QMap<int,int> TableID;
	QList<PageItem*> TableItems;
	int a, counter, baseobj;
	double pageX = 0, pageY = 0;
	bool newVersion = false;
	bool VorLFound = false;
	QMap<int,int> layerTrans;
	int maxLayer = 0;
	int maxLevel = 0;
	layerTrans.clear();
	uint layerCount=m_Doc->layerCount();
	for (uint la2 = 0; la2 < layerCount; ++la2)
	{
		maxLayer = qMax(m_Doc->Layers[la2].ID, maxLayer);
		maxLevel = qMax(m_Doc->Layers[la2].Level, maxLevel);
	}
	DoVorl.clear();
	DoVorl[0] = "";
	DoVorl[1] = "";
	DoVorl[2] = "";
	DoVorl[3] = "";
	DoVorl[4] = "";
	VorlC = 5;
	QDomDocument docu("scridoc");
 	QString f(readSLA(fileName));
	if (f.isEmpty())
	{
		setFileReadError();
		return false;
	}
	QString errorMsg;
	int errorLine, errorColumn;
	if (!docu.setContent(f, &errorMsg, &errorLine, &errorColumn))
	{
		setDomParsingError(errorMsg, errorLine, errorColumn);
		return false;
	}
	QString fileDir = QFileInfo(fileName).absolutePath();
	ScColor lf = ScColor();
	QDomElement elem=docu.documentElement();
	if (elem.tagName() != "SCRIBUSUTF8NEW")
		return false;
	if (elem.hasAttribute("Version"))
		newVersion = true;
	QDomNode DOC=elem.firstChild();
	counter = m_Doc->Items->count();
	baseobj = counter;
	while(!DOC.isNull())
	{
		QDomElement dc=DOC.toElement();
		QDomNode PAGE=DOC.firstChild();
		while(!PAGE.isNull())
		{
			QDomElement pg=PAGE.toElement();
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
				QString name = pg.attribute("NAME");
				m_Doc->PageColors.insert((name.isEmpty()) ? lf.name() : name, lf);
			}
			if(pg.tagName()=="STYLE")
			{
				GetStyle(&pg, &vg, NULL, m_Doc, true);
				VorLFound = true;
			}
			if(pg.tagName()=="JAVA")
				m_Doc->JavaScripts[pg.attribute("NAME")] = pg.attribute("SCRIPT");
			if(pg.tagName()=="LAYERS")
			{
				int lId   = pg.attribute("NUMMER").toInt();
				int level = pg.attribute("LEVEL").toInt();
				ScLayer la( pg.attribute("NAME"), level, lId );
				la.isViewable   = pg.attribute("SICHTBAR").toInt();
				la.isPrintable  = pg.attribute("DRUCKEN").toInt();
				la.isEditable   = pg.attribute("EDIT", "1").toInt();
				la.flowControl  = pg.attribute("FLOW", "1").toInt();
				la.transparency = ScCLocale::toDoubleC(pg.attribute("TRANS"), 1.0);
				la.blendMode    = pg.attribute("BLEND", "0").toInt();
				la.outlineMode  = pg.attribute("OUTL", "0").toInt();
				if (pg.hasAttribute("LAYERC"))
					la.markerColor =  QColor(pg.attribute("LAYERC","#000000"));
				const ScLayer* la2 = m_Doc->Layers.layerByName(la.Name);
				if (la2)
					layerTrans.insert(la.ID, la2->ID);
				else
				{
					maxLayer++;
					maxLevel++;
					layerTrans.insert(la.ID, maxLayer);
					la.ID = maxLayer;
					la.Level = maxLevel;
					m_Doc->Layers.append(la);
				}
			}
			if(pg.tagName()=="MultiLine")
			{
				multiLine ml;
				QDomNode MuLn = PAGE.firstChild();
				while(!MuLn.isNull())
				{
					QDomElement MuL = MuLn.toElement();
					struct SingleLine sl;
					sl.Color = MuL.attribute("Color");
					sl.Dash = MuL.attribute("Dash").toInt();
					sl.LineEnd = MuL.attribute("LineEnd").toInt();
					sl.LineJoin = MuL.attribute("LineJoin").toInt();
					sl.Shade = MuL.attribute("Shade").toInt();
					sl.Width = ScCLocale::toDoubleC(MuL.attribute("Width"));
					ml.push_back(sl);
					MuLn = MuLn.nextSibling();
				}
				QString Nam = pg.attribute("Name");
				QString Nam2 = Nam;
				int copyC = 1;
				QMap<QString,multiLine>::ConstIterator mlit = m_Doc->MLineStyles.find(Nam2);
				if (mlit != m_Doc->MLineStyles.end() && ml != mlit.value())
				{
					while (m_Doc->MLineStyles.contains(Nam2))
					{
						Nam2 = QObject::tr("Copy #%1 of ").arg(copyC)+Nam;
						copyC++;
					}
				}
				m_Doc->MLineStyles.insert(Nam2, ml);
			}
			if(pg.tagName()=="Arrows")
			{
				struct ArrowDesc arrow;
				arrow.name = pg.attribute("Name");
				arrow.userArrow = true;
				double xa, ya;
				QString tmp = pg.attribute("Points");
				ScTextStream fp(&tmp, QIODevice::ReadOnly);
				for (uint cx = 0; cx < pg.attribute("NumPoints").toUInt(); ++cx)
				{
					fp >> xa;
					fp >> ya;
					arrow.points.addPoint(xa, ya);
				}
				m_Doc->appendToArrowStyles(arrow);
			}
			if (((pg.tagName()=="PAGE") || (pg.tagName()=="MASTERPAGE")) && (pg.attribute("NUM").toInt() == pageNumber))
			{
				a = m_Doc->currentPage()->pageNr();
				Apage = m_Doc->Pages->at(a);
				if ((pg.tagName()!="MASTERPAGE") && (Mpage))
				{
					PAGE=PAGE.nextSibling();
					continue;
				}
				if (Mpage)
				{
					Apage->LeftPg=pg.attribute("LEFT", "0").toInt();
					
					if (!renamedPageName.isEmpty())
						Apage->setPageName(renamedPageName);
					else
						Apage->setPageName(pg.attribute("NAM",""));
				}
				if (pg.hasAttribute("Size"))
					Apage->m_pageSize = pg.attribute("Size");
				if (pg.hasAttribute("Orientation"))
					Apage->setOrientation(pg.attribute("Orientation").toInt());
				if (pg.hasAttribute("PAGEWIDTH"))
					Apage->setWidth(ScCLocale::toDoubleC(pg.attribute("PAGEWIDTH")));
				else
					Apage->setWidth(ScCLocale::toDoubleC(pg.attribute("PAGEWITH")));
				Apage->setHeight(ScCLocale::toDoubleC(pg.attribute("PAGEHEIGHT")));
				Apage->setInitialHeight(Apage->height());
				Apage->setInitialWidth(Apage->width());
				Apage->initialMargins.Top    = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERTOP")));
				Apage->initialMargins.Bottom = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERBOTTOM")));
				Apage->initialMargins.Left   = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERLEFT")));
				Apage->initialMargins.Right  = qMax(0.0, ScCLocale::toDoubleC(pg.attribute("BORDERRIGHT")));
				Apage->marginPreset = pg.attribute("PRESET", "0").toInt();
				Apage->Margins.Top = Apage->initialMargins.Top;
				Apage->Margins.Bottom = Apage->initialMargins.Bottom;
				pageX = ScCLocale::toDoubleC(pg.attribute("PAGEXPOS"));
				pageY = ScCLocale::toDoubleC(pg.attribute("PAGEYPOS"));
				// guides reading
				tmp = "";
				GuideManagerIO::readVerticalGuides(pg.attribute("VerticalGuides"),
												Apage,
												GuideManagerCore::Standard,
												pg.hasAttribute("NumVGuides"));
				GuideManagerIO::readHorizontalGuides(pg.attribute("HorizontalGuides"),
												Apage,
												GuideManagerCore::Standard,
												pg.hasAttribute("NumHGuides"));
			}
			if ((pg.tagName()=="PAGEOBJECT") || (pg.tagName()=="MASTEROBJECT") || (pg.tagName()=="FRAMEOBJECT"))
			{
				if (Mpage)
				{
					if (pg.tagName() != "MASTEROBJECT")
					{
						PAGE=PAGE.nextSibling();
						continue;
					}
				}
				else
				{
					if (pg.tagName() == "MASTEROBJECT")
					{
						PAGE=PAGE.nextSibling();
						continue;
					}
				}
				
				if (pg.attribute("OwnPage").toInt() != pageNumber)
				{			
					if (pg.tagName()=="PAGEOBJECT")
						itemRemap[itemCount++] = -1;
				}
				else
				{
					// first of linked chain?
					if (pg.tagName()=="PAGEOBJECT")
					{
						itemRemap[itemCount++] = m_Doc->Items->count();
						if (pg.attribute("NEXTITEM").toInt() != -1)
						{
							itemNext[m_Doc->Items->count()] = pg.attribute("NEXTITEM").toInt();
						}
					}
					/*int docGc = m_Doc->GroupCounter;
					m_Doc->GroupCounter = 0;*/
					Neu = PasteItem(&pg, m_Doc, fileDir);
					Neu->moveBy(-pageX + Apage->xOffset(), - pageY + Apage->yOffset());
					Neu->setRedrawBounding();
					//CB Must run onpage as we cant use pagetoload if the page has been renamed. 
					//CB TODO Make this accept a page to place onto.
					//Neu->OwnPage = m_Doc->OnPage(Neu);
					//Neu->OwnPage = PageToLoad;
					Neu->OwnPage = m_Doc->currentPageNumber();
					if (pg.tagName()=="PAGEOBJECT")
						Neu->OnMasterPage = "";
					/*m_Doc->GroupCounter = docGc;*/
					QDomNode IT=pg.firstChild();
					LastStyles * last = new LastStyles();
					while(!IT.isNull())
					{
						QDomElement it=IT.toElement();
						if (it.tagName()=="CSTOP")
						{
							QString name = it.attribute("NAME");
							double ramp  = ScCLocale::toDoubleC(it.attribute("RAMP"), 0.0);
							int shade  = it.attribute("SHADE", "100").toInt();
							double opa = ScCLocale::toDoubleC(it.attribute("TRANS"), 1.0);
							handleOldColorShade(m_Doc, name, shade);
							Neu->fill_gradient.addStop(SetColor(m_Doc, name, shade), ramp, 0.5, opa, name, shade);
						}
						if (it.tagName()=="ITEXT")
							GetItemText(&it, m_Doc, Neu, last, true, VorLFound);
						if(it.tagName()=="PageItemAttributes")
						{
							QDomNode PIA = it.firstChild();
							ObjAttrVector pageItemAttributes;
							while(!PIA.isNull())
							{
								QDomElement itemAttr = PIA.toElement();
								if(itemAttr.tagName() == "ItemAttribute")
								{
									ObjectAttribute objattr;
									objattr.name=itemAttr.attribute("Name");
									objattr.type=itemAttr.attribute("Type");
									objattr.value=itemAttr.attribute("Value");
									objattr.parameter=itemAttr.attribute("Parameter");
									objattr.relationship=itemAttr.attribute("Relationship");
									objattr.relationshipto=itemAttr.attribute("RelationshipTo");
									objattr.autoaddto=itemAttr.attribute("AutoAddTo");
									pageItemAttributes.append(objattr);
								}
								PIA = PIA.nextSibling();
							}
							Neu->setObjectAttributes(&pageItemAttributes);
						}
						IT=IT.nextSibling();
					}
					delete last;
					if (Neu->fill_gradient.Stops() == 0)
					{
						const ScColor& col1 = m_Doc->PageColors[m_Doc->itemToolPrefs().shapeFillColor];
						const ScColor& col2 = m_Doc->PageColors[m_Doc->itemToolPrefs().shapeLineColor];
						Neu->fill_gradient.addStop(ScColorEngine::getRGBColor(col1, m_Doc), 0.0, 0.5, 1.0, m_Doc->itemToolPrefs().shapeFillColor, 100);
						Neu->fill_gradient.addStop(ScColorEngine::getRGBColor(col2, m_Doc), 1.0, 0.5, 1.0, m_Doc->itemToolPrefs().shapeLineColor, 100);
					}
//					Neu->Language = ScMW->GetLang(pg.attribute("LANGUAGE", m_Doc->Language));
//					Neu->Language = m_Doc->Language;
					Neu->isAutoText = static_cast<bool>(pg.attribute("AUTOTEXT").toInt());
					Neu->isEmbedded = static_cast<bool>(pg.attribute("isInline", "0").toInt());
					Neu->gXpos = ScCLocale::toDoubleC(pg.attribute("gXpos"), 0.0);
					Neu->gYpos = ScCLocale::toDoubleC(pg.attribute("gYpos"), 0.0);
					Neu->gWidth  = ScCLocale::toDoubleC(pg.attribute("gWidth"), Neu->width());
					Neu->gHeight = ScCLocale::toDoubleC(pg.attribute("gHeight"),Neu->height());
					if (Neu->isAutoText)
						m_Doc->LastAuto = Neu;
					if (Neu->isTableItem)
					{
						TableItems.append(Neu);
						TableID.insert(pg.attribute("OwnLINK", "0").toInt(), Neu->ItemNr);
					}
					if (pg.tagName()=="FRAMEOBJECT")
					{
						m_Doc->FrameItems.append(m_Doc->Items->takeAt(Neu->ItemNr));
						Neu->ItemNr = m_Doc->FrameItems.count()-1;
					}
				}
				counter++;
			}
			PAGE=PAGE.nextSibling();
		}
		PAGE=DOC.firstChild();
		while(!PAGE.isNull())
		{
			QDomElement pg=PAGE.toElement();
			if(pg.tagName()=="Bookmark")
			{
				int elem = pg.attribute("Element").toInt();
				if (elem < m_Doc->Items->count())
				{
					bok.Title = pg.attribute("Title");
					bok.Text = pg.attribute("Text");
					bok.Aktion = pg.attribute("Aktion");
					bok.ItemNr = pg.attribute("ItemNr").toInt();
					bok.PageObject = m_Doc->Items->at(elem);
					bok.First = pg.attribute("First").toInt();
					bok.Last = pg.attribute("Last").toInt();
					bok.Prev = pg.attribute("Prev").toInt();
					bok.Next = pg.attribute("Next").toInt();
					bok.Parent = pg.attribute("Parent").toInt();
					m_Doc->BookMarks.append(bok);
				}
			}
			PAGE=PAGE.nextSibling();
		}
		DOC=DOC.nextSibling();
	}
	if (TableItems.count() != 0)
	{
		for (int ttc = 0; ttc < TableItems.count(); ++ttc)
		{
			PageItem* ta = TableItems.at(ttc);
			if (ta->TopLinkID != -1)
				ta->TopLink = m_Doc->Items->at(TableID[ta->TopLinkID]);
			else
				ta->TopLink = 0;
			if (ta->LeftLinkID != -1)
				ta->LeftLink = m_Doc->Items->at(TableID[ta->LeftLinkID]);
			else
				ta->LeftLink = 0;
			if (ta->RightLinkID != -1)
				ta->RightLink = m_Doc->Items->at(TableID[ta->RightLinkID]);
			else
				ta->RightLink = 0;
			if (ta->BottomLinkID != -1)
				ta->BottomLink = m_Doc->Items->at(TableID[ta->BottomLinkID]);
			else
				ta->BottomLink = 0;
		}
	}
	// reestablish textframe links
	if (itemNext.count() != 0)
	{
		QMap<int,int>::Iterator lc;
		for (lc = itemNext.begin(); lc != itemNext.end(); ++lc)
		{
			if (itemRemap[lc.value()] >= 0)
			{
				if ((lc.key() < m_Doc->Items->count()) && (itemRemap[lc.value()] < m_Doc->Items->count()))
				{
					PageItem * Its = m_Doc->Items->at(lc.key());
					PageItem * Itn = m_Doc->Items->at(itemRemap[lc.value()]);
					if (Itn->prevInChain() || Its->nextInChain()) 
					{
						qDebug("scribus13format: corruption in linked textframes detected");
						continue;
					}
					Its->link(Itn);
				}
			}
		}
	}	
	
	// reestablish first/lastAuto
	m_Doc->FirstAuto = m_Doc->LastAuto;
	if (m_Doc->LastAuto)
	{
		while (m_Doc->LastAuto->nextInChain())
			m_Doc->LastAuto = m_Doc->LastAuto->nextInChain();
		while (m_Doc->FirstAuto->prevInChain())
			m_Doc->FirstAuto = m_Doc->FirstAuto->prevInChain();
	}
	
	return true;
}

void Scribus13Format::GetStyle(QDomElement *pg, ParagraphStyle *vg, StyleSet<ParagraphStyle> *tempParagraphStyles, ScribusDoc* doc, bool fl)
{
	bool fou;
	QString tmpf, tmf, tmV;
	fou = false;
	readParagraphStyle(*vg, *pg, doc);
	const StyleSet<ParagraphStyle> & docParagraphStyles(tempParagraphStyles? *tempParagraphStyles : doc->paragraphStyles());
	for (int xx=0; xx<docParagraphStyles.count(); ++xx)
	{
		if (vg->name() == docParagraphStyles[xx].name())
		{
			if (vg->equiv(docParagraphStyles[xx]))
			{
				if (fl)
				{
					DoVorl[VorlC] = vg->name();
					++VorlC;
				}
				fou = true;
			}
			else
			{
				vg->setName("Copy of "+docParagraphStyles[xx].name());
				fou = false;
			}
			break;
		}
	}
	if (!fou)
	{
		for (int xx=0; xx< docParagraphStyles.count(); ++xx)
		{
			if (vg->equiv(docParagraphStyles[xx]))
			{
				vg->setName(docParagraphStyles[xx].name());
				fou = true;
				if (fl)
				{
					DoVorl[VorlC] = vg->name();
					++VorlC;
				}
				break;
			}
		}
	}
	if (!fou)
	{
		if (tempParagraphStyles)
			tempParagraphStyles->create(*vg);
		else {
			StyleSet<ParagraphStyle> temp;
			temp.create(*vg);
			doc->redefineStyles(temp, false);
		}
		if (fl)
		{
			DoVorl[VorlC] = vg->name();
			++VorlC;
		}
	}
}

QString Scribus13Format::AskForFont(QString fStr, ScribusDoc *doc)
{
	PrefsManager *prefsManager=PrefsManager::instance();
//	QFont fo;
	QString tmpf = fStr;
	if ((!(*m_AvailableFonts).contains(tmpf)) || (!(*m_AvailableFonts)[tmpf].usable()))
	{
		if ((!prefsManager->appPrefs.fontPrefs.GFontSub.contains(tmpf)) || (!(*m_AvailableFonts)[prefsManager->appPrefs.fontPrefs.GFontSub[tmpf]].usable()))
		{
			qApp->changeOverrideCursor(QCursor(Qt::ArrowCursor));
			MissingFont *dia = new MissingFont(0, tmpf, doc);
			dia->exec();
			tmpf = dia->getReplacementFont();
			delete dia;
			qApp->changeOverrideCursor(QCursor(Qt::WaitCursor));
			prefsManager->appPrefs.fontPrefs.GFontSub[fStr] = tmpf;
		}
		else
			tmpf = prefsManager->appPrefs.fontPrefs.GFontSub[tmpf];
		ReplacedFonts[fStr] = tmpf;
	}
	if (!doc->UsedFonts.contains(tmpf))
	{
		doc->AddFont(tmpf);
	}
// 	DoFonts[fStr] = tmpf;
	return tmpf;
}

bool Scribus13Format::readStyles(const QString& fileName, ScribusDoc* doc, StyleSet<ParagraphStyle> &docParagraphStyles)
{
	ParagraphStyle pstyle;
	QDomDocument docu("scridoc");
	QString f (readSLA(fileName));
	if (f.isEmpty())
		return false;
	if(!docu.setContent(f))
		return false;
	QDomElement elem=docu.documentElement();
	if (elem.tagName() != "SCRIBUSUTF8NEW")
		return false;
	QDomNode DOC=elem.firstChild();
	while(!DOC.isNull())
	{
		QDomElement dc=DOC.toElement();
		QDomNode PAGE=DOC.firstChild();
		while(!PAGE.isNull())
		{
			QDomElement pg=PAGE.toElement();
			if(pg.tagName()=="STYLE")
			{
				pstyle.erase();
				GetStyle(&pg, &pstyle, &docParagraphStyles, doc, false);
			}
			PAGE=PAGE.nextSibling();
		}
		DOC=DOC.nextSibling();
	}
	return true;
}

bool Scribus13Format::readLineStyles(const QString& fileName, QMap<QString,multiLine> *Sty)
{
	QDomDocument docu("scridoc");
	QString f(readSLA(fileName));
	if (f.isEmpty())
		return false;
	if(!docu.setContent(f))
		return false;
	QDomElement elem=docu.documentElement();
	if (elem.tagName() != "SCRIBUSUTF8NEW")
		return false;
	QDomNode DOC=elem.firstChild();
	while(!DOC.isNull())
	{
		QDomElement dc=DOC.toElement();
		QDomNode PAGE=DOC.firstChild();
		while(!PAGE.isNull())
		{
			QDomElement pg=PAGE.toElement();
			if(pg.tagName()=="MultiLine")
			{
				multiLine ml;
				QDomNode MuLn = PAGE.firstChild();
				while(!MuLn.isNull())
				{
					QDomElement MuL = MuLn.toElement();
					struct SingleLine sl;
					sl.Color = MuL.attribute("Color");
					sl.Dash = MuL.attribute("Dash").toInt();
					sl.LineEnd = MuL.attribute("LineEnd").toInt();
					sl.LineJoin = MuL.attribute("LineJoin").toInt();
					sl.Shade = MuL.attribute("Shade").toInt();
					sl.Width = ScCLocale::toDoubleC(MuL.attribute("Width"));
					ml.push_back(sl);
					MuLn = MuLn.nextSibling();
				}
				QString Nam = pg.attribute("Name");
				QString Nam2 = Nam;
				int copyC = 1;
				QMap<QString,multiLine>::ConstIterator mlit = Sty->find(Nam2);
				if (mlit != Sty->end() && ml != mlit.value())
				{
					while (Sty->contains(Nam2))
					{
						Nam2 = tr("Copy #%1 of ").arg(copyC)+Nam;
						copyC++;
					}
				}
				Sty->insert(Nam2, ml);
			}
			PAGE=PAGE.nextSibling();
		}
		DOC=DOC.nextSibling();
	}
	return true;
}

bool Scribus13Format::readColors(const QString& fileName, ColorList & colors)
{
	QString f(readSLA(fileName));
	if (f.isEmpty())
		return false;
	QDomDocument docu("scridoc");
	if(!docu.setContent(f))
		return false;
	ScColor lf = ScColor();
	colors.clear();
	QDomElement elem=docu.documentElement();
	if (elem.tagName() != "SCRIBUSUTF8NEW")
		return false;
	QDomNode DOC=elem.firstChild();
	while(!DOC.isNull())
	{
		QDomElement dc=DOC.toElement();
		QDomNode PAGE=DOC.firstChild();
		while(!PAGE.isNull())
		{
			QDomElement pg=PAGE.toElement();
			// 10/25/2004 pv - None is "reserved" color. cannot be defined in any file...
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
				QString name = pg.attribute("NAME");
				colors.insert((name.isEmpty()) ? lf.name() : name, lf);
			}
			PAGE=PAGE.nextSibling();
		}
		DOC=DOC.nextSibling();
	}
	return true;
}

bool Scribus13Format::readPageCount(const QString& fileName, int *num1, int *num2, QStringList & masterPageNames)
{
	QString PgNam;
	int counter = 0;
	int counter2 = 0;
	QDomDocument docu("scridoc");
	QString f(readSLA(fileName));
	if (f.isEmpty())
		return false;
	if(!docu.setContent(f))
		return false;
	QDomElement elem=docu.documentElement();
	if (elem.tagName() != "SCRIBUSUTF8NEW")
		return false;
	QDomNode DOC=elem.firstChild();
	while(!DOC.isNull())
	{
		QDomNode PAGE=DOC.firstChild();
		while(!PAGE.isNull())
		{
			QDomElement pg=PAGE.toElement();
			PgNam = pg.attribute("NAM", "");
			if(pg.tagName()=="PAGE")
				counter++;
			if(pg.tagName()=="MASTERPAGE")
			{
				counter2++;
				masterPageNames.append(PgNam);
			}
			PAGE=PAGE.nextSibling();
		}
		DOC=DOC.nextSibling();
	}
	*num1 = counter;
	*num2 = counter2;
	return true;
}

void Scribus13Format::WritePages(ScribusDoc *doc, QDomDocument *docu, QDomElement *dc, QProgressBar *dia2, uint maxC, bool master)
{
	uint ObCount = maxC;
	Page *page;
	uint pages;
	QDomElement pg;
	QString tmp;
	if (master)
		pages = doc->MasterPages.count();
	else
		pages = doc->DocPages.count();
	for(uint i = 0; i < pages; ++i)
	{
		ObCount++;
		if (dia2 != 0)
			dia2->setValue(ObCount);
		if (master)
		{
			pg = docu->createElement("MASTERPAGE");
			page = doc->MasterPages.at(i);
		}
		else
		{
			pg = docu->createElement("PAGE");
			page = doc->DocPages.at(i);
		}
		pg.setAttribute("PAGEXPOS",page->xOffset());
		pg.setAttribute("PAGEYPOS",page->yOffset());
		pg.setAttribute("PAGEWIDTH",page->width());
		pg.setAttribute("PAGEHEIGHT",page->height());
		pg.setAttribute("BORDERLEFT",page->initialMargins.Left);
		pg.setAttribute("BORDERRIGHT",page->initialMargins.Right);
		pg.setAttribute("BORDERTOP",page->initialMargins.Top);
		pg.setAttribute("BORDERBOTTOM",page->initialMargins.Bottom);
		pg.setAttribute("NUM",page->pageNr());
		pg.setAttribute("NAM",page->pageName());
		pg.setAttribute("MNAM",page->MPageNam);
		pg.setAttribute("Size", page->m_pageSize);
		pg.setAttribute("Orientation", page->orientation());
		pg.setAttribute("LEFT", page->LeftPg);
		pg.setAttribute("PRESET", page->marginPreset);
		pg.setAttribute("VerticalGuides", GuideManagerIO::writeVerticalGuides(
													page, GuideManagerCore::Standard));
		pg.setAttribute("HorizontalGuides", GuideManagerIO::writeHorizontalGuides(
													page, GuideManagerCore::Standard));
		dc->appendChild(pg);
	}
}

void Scribus13Format::WriteObjects(ScribusDoc *doc, QDomDocument *docu, QDomElement *dc, const QString& baseDir, 
								   QProgressBar *dia2, uint maxC, int master)
{
	int tst, tst2, tsb, tsb2, tobj, tobj2;
	QString text, tf, tf2, tc, tc2, tcs, tcs2, tmp, tmpy, Ndir;
	double ts, ts2, tsc, tsc2, tscv, tscv2, tb, tb2, tsx, tsx2, tsy, tsy2, tout, tout2, tulp, tulp2, tulw, tulw2, tstp, tstp2, tstw, tstw2;
	double te, te2, tsh, tsh2, tshs, tshs2;
	uint ObCount = maxC;
	PageItem *item = NULL;
	QDomElement ob;
	uint objects = 0;
	switch (master)
	{
		case 0:
			objects = doc->MasterItems.count();
			break;
		case 1:
			objects = doc->DocItems.count();
			break;
		case 2:
			objects = doc->FrameItems.count();
			break;
	}
	for(uint j = 0; j < objects;++j)
	{
		ObCount++;
		if (dia2 != 0)
			dia2->setValue(ObCount);
		switch (master)
		{
			case 0:
				item = doc->MasterItems.at(j);
				ob = docu->createElement("MASTEROBJECT");
				break;
			case 1:
				item = doc->DocItems.at(j);
				ob = docu->createElement("PAGEOBJECT");
				break;
			case 2:
				item = doc->FrameItems.at(j);
				ob = docu->createElement("FRAMEOBJECT");
				break;
		}
		SetItemProps(&ob, item, baseDir, true);
		ob.setAttribute("OnMasterPage", item->OnMasterPage);
		ob.setAttribute("ImageClip", item->pixm.imgInfo.usedPath);
		ob.setAttribute("ImageRes", item->pixm.imgInfo.lowResType);
		ob.setAttribute("isInline", static_cast<int>(item->isEmbedded));
		ob.setAttribute("fillRule", static_cast<int>(item->fillRule));
		ob.setAttribute("doOverprint", static_cast<int>(item->doOverprint));
		ob.setAttribute("gXpos", item->gXpos);
		ob.setAttribute("gYpos", item->gYpos);
		ob.setAttribute("gWidth", item->gWidth);
		ob.setAttribute("gHeight", item->gHeight);
		if (item->GrType != 0)
		{
			QList<VColorStop*> cstops = item->fill_gradient.colorStops();
			for (uint cst = 0; cst < item->fill_gradient.Stops(); ++cst)
			{
				QDomElement itcl = docu->createElement("CSTOP");
				itcl.setAttribute("RAMP", cstops.at(cst)->rampPoint);
				itcl.setAttribute("NAME", cstops.at(cst)->name);
				itcl.setAttribute("SHADE", cstops.at(cst)->shade);
				itcl.setAttribute("TRANS", cstops.at(cst)->opacity);
				ob.appendChild(itcl);
			}
			ob.setAttribute("GRSTARTX", item->GrStartX);
			ob.setAttribute("GRSTARTY", item->GrStartY);
			ob.setAttribute("GRENDX", item->GrEndX);
			ob.setAttribute("GRENDY", item->GrEndY);
		}
		if (item->effectsInUse.count() != 0)
		{
			for (int a = 0; a < item->effectsInUse.count(); ++a)
			{
				QDomElement imeff = docu->createElement("ImageEffect");
				imeff.setAttribute("Code", item->effectsInUse.at(a).effectCode);
				imeff.setAttribute("Param", item->effectsInUse.at(a).effectParameters);
				ob.appendChild(imeff);
			}
		}
/*
 if (item->TabValues.count() != 0)
		{
			for (uint a = 0; a < item->TabValues.count(); ++a)
			{
				QDomElement tabs = docu->createElement("Tabs");
				tabs.setAttribute("Type", (*item->TabValues.at(a)).tabType);
				tabs.setAttribute("Pos", (*item->TabValues.at(a)).tabPosition);
				QString tabCh = "";
				if (!(*item->TabValues.at(a)).tabFillChar.isNull())
					tabCh = QString((*item->TabValues.at(a)).tabFillChar);
				tabs.setAttribute("Fill", tabCh);
				ob.appendChild(tabs);
			}
		}
*/
		if (((item->asImageFrame()) || (item->asTextFrame())) && (!item->Pfile.isEmpty()) && (item->pixm.imgInfo.layerInfo.count() != 0) && (item->pixm.imgInfo.isRequest))
		{
			QMap<int, ImageLoadRequest>::iterator it2;
			for (it2 = item->pixm.imgInfo.RequestProps.begin(); it2 != item->pixm.imgInfo.RequestProps.end(); ++it2)
			{
				QDomElement psd = docu->createElement("PSDLayer");
				psd.setAttribute("Layer",it2.key());
				psd.setAttribute("Visible", static_cast<int>(it2.value().visible));
				psd.setAttribute("useMask", static_cast<int>(it2.value().useMask));
				psd.setAttribute("Opacity", it2.value().opacity);
				psd.setAttribute("Blend", it2.value().blend);
				ob.appendChild(psd);
			}
		}
		ob.setAttribute("ALIGN", findParagraphStyle(doc, item->itemText.defaultStyle()));
		ob.setAttribute("BOOKMARK", item->isBookmark ? 1 : 0);
		for(int k = 0; k < item->itemText.length(); ++k)
		{
			const CharStyle& style1(item->itemText.charStyle(k));
			QChar ch = item->itemText.text(k);
			QDomElement it=docu->createElement("ITEXT");
			ts = style1.fontSize() / 10.0;
			tf = style1.font().scName();
			tc = style1.fillColor();
			te = style1.tracking();
			tsh = style1.fillShade();
			tst = style1.effects() & ScStyle_UserStyles;
#ifndef NLS_PROTO
			tsb = findParagraphStyle(doc, item->itemText.paragraphStyle(k));
#else
			tsb = 0;
#endif
			tcs = style1.strokeColor();
			tshs = style1.strokeShade();
			tsc = style1.scaleH() / 10.0;
			tscv = style1.scaleV() / 10.0;
			tb = style1.baselineOffset() / 10.0;
			tsx = style1.shadowXOffset() / 10.0;
			tsy = style1.shadowYOffset() / 10.0;
			tout = style1.outlineWidth() / 10.0;
			tulp = style1.underlineOffset() / 10.0;
			tulw = style1.underlineWidth() / 10.0;
			tstp = style1.strikethruOffset() / 10.0;
			tstw = style1.strikethruWidth() / 10.0;
#ifndef NLS_PROTO
			if ((ch == SpecialChars::OBJECT) && (item->itemText.item(k)->embedded.hasItem()))
				tobj = item->itemText.item(k)->embedded.getItem()->ItemNr;
			else
#endif
				tobj = -1;
			if (ch == SpecialChars::PARSEP)
				text = QChar(5);
			else if (ch == SpecialChars::TAB)
				text = QChar(4);
			else
				text = ch;
			++k;
			if (k == item->itemText.length())
			{
				it.setAttribute("CH",text);
				it.setAttribute("CSIZE",ts);
				it.setAttribute("CFONT",tf);
				it.setAttribute("CCOLOR",tc);
				it.setAttribute("CKERN",te);
				it.setAttribute("CSHADE",tsh);
				it.setAttribute("CSTYLE",tst);
				it.setAttribute("CAB",tsb);
				it.setAttribute("CSTROKE",tcs);
				it.setAttribute("CSHADE2",tshs);
				it.setAttribute("CSCALE",tsc);
				it.setAttribute("CSCALEV",tscv);
				it.setAttribute("CBASE",tb);
				it.setAttribute("CSHX",tsx);
				it.setAttribute("CSHY",tsy);
				it.setAttribute("COUT",tout);
				it.setAttribute("CULP",tulp);
				it.setAttribute("CULW",tulw);
				it.setAttribute("CSTP",tstp);
				it.setAttribute("CSTW",tstw);
				if (tobj != -1)
					it.setAttribute("COBJ", tobj);
				ob.appendChild(it);
				break;
			}
			const CharStyle& style2(item->itemText.charStyle(k));
			ch = item->itemText.text(k);
			ts2 = style2.fontSize() / 10.0;
			tf2 = style2.font().scName();
			tc2 = style2.fillColor();
			te2 = style2.tracking();
			tsh2 = style2.fillShade();
			tst2 = style2.effects() & ScStyle_UserStyles;
#ifndef NLS_PROTO
			tsb2 = findParagraphStyle(doc, item->itemText.paragraphStyle(k));
#else
			tsb2 = 0;
#endif
			tcs2 = style2.strokeColor();
			tshs2 = style2.strokeShade();
			tsc2 = style2.scaleH() / 10.0;
			tscv2 = style2.scaleV() / 10.0;
			tb2 = style2.baselineOffset() / 10.0;
			tsx2 = style2.shadowXOffset() / 10.0;
			tsy2 = style2.shadowYOffset() / 10.0;
			tout2 = style2.outlineWidth() / 10.0;
			tulp2 = style2.underlineOffset() / 10.0;
			tulw2 = style2.underlineWidth() / 10.0;
			tstp2 = style2.strikethruOffset() / 10.0;
			tstw2 = style2.strikethruWidth() / 10.0;
#ifndef NLS_PROTO
			if ((ch == SpecialChars::OBJECT) && (item->itemText.item(k)->embedded.hasItem()))
				tobj2 = item->itemText.item(k)->embedded.getItem()->ItemNr;
			else
#endif
				tobj2 = -1;
			while ((ts2 == ts)
						&& (tsb2 == tsb)
						&& (tf2 == tf)
						&& (tc2 == tc)
						&& (te2 == te)
						&& (tsh2 == tsh)
						&& (tshs2 == tshs)
						&& (tsc2 == tsc)
						&& (tscv2 == tscv)
						&& (tcs2 == tcs)
						&& (tb2 == tb)
						&& (tsx2 == tsx)
						&& (tsy2 == tsy)
						&& (tout2 == tout)
						&& (tulp2 == tulp)
						&& (tulw2 == tulw)
						&& (tstp2 == tstp)
						&& (tstw2 == tstw)
						&& (tobj2 == tobj)
						&& (tst2 == tst))
			{
				if (ch == SpecialChars::PARSEP)
					text += QChar(5);
				else if (ch == SpecialChars::TAB)
					text += QChar(4);
				else
					text += ch;
				++k;
				if (k == item->itemText.length())
					break;
				const CharStyle& style3(item->itemText.charStyle(k));
				ch = item->itemText.text(k);
				ts2 = style3.fontSize() / 10.0;
				tf2 = style3.font().scName();
				tc2 = style3.fillColor();
				te2 = style3.tracking();
				tsh2 = style3.fillShade();
				tst2 = style3.effects() & ScStyle_UserStyles;
#ifndef NLS_PROTO
				tsb2 = findParagraphStyle(doc, item->itemText.paragraphStyle(k));
#else
				tsb2 = 0;
#endif
				tcs2 = style3.strokeColor();
				tshs2 = style3.strokeShade();
				tsc2 = style3.scaleH() / 10.0;
				tscv2 = style3.scaleV() / 10.0;
				tb2 = style3.baselineOffset() / 10.0;
				tsx2 = style3.shadowXOffset() / 10.0;
				tsy2 = style3.shadowYOffset() / 10.0;
				tout2 = style3.outlineWidth() / 10.0;
				tulp2 = style3.underlineOffset() / 10.0;
				tulw2 = style3.underlineWidth() / 10.0;
				tstp2 = style3.strikethruOffset() / 10.0;
				tstw2 = style3.strikethruWidth() / 10.0;
#ifndef NLS_PROTO
				if ((ch == SpecialChars::OBJECT) && (item->itemText.item(k)->embedded.hasItem()))
					tobj2 = item->itemText.item(k)->embedded.getItem()->ItemNr;
				else
#endif
					tobj2 = -1;
			}
			it.setAttribute("CH",text);
			it.setAttribute("CSIZE",ts);
			it.setAttribute("CFONT",tf);
			it.setAttribute("CCOLOR",tc);
			it.setAttribute("CKERN",te);
			it.setAttribute("CSHADE",tsh);
			it.setAttribute("CSTYLE",tst);
			it.setAttribute("CAB",tsb);
			it.setAttribute("CSTROKE",tcs);
			it.setAttribute("CSHADE2",tshs);
			it.setAttribute("CSCALE",tsc);
			it.setAttribute("CSCALEV",tscv);
			it.setAttribute("CBASE",tb);
			it.setAttribute("CSHX",tsx);
			it.setAttribute("CSHY",tsy);
			it.setAttribute("COUT",tout);
			it.setAttribute("CULP",tulp);
			it.setAttribute("CULW",tulw);
			it.setAttribute("CSTP",tstp);
			it.setAttribute("CSTW",tstw);
			if (tobj != -1)
				it.setAttribute("COBJ", tobj);
			k--;
			ob.appendChild(it);
		}
		if (item->prevInChain() != 0)
			ob.setAttribute("BACKITEM", item->prevInChain()->ItemNr);
		else
			ob.setAttribute("BACKITEM", -1);
		if (item->nextInChain() != 0)
			ob.setAttribute("NEXTITEM", item->nextInChain()->ItemNr);
		else
			ob.setAttribute("NEXTITEM", -1);
		ob.setAttribute("LAYER", item->LayerID);

		//CB PageItemAttributes
		QDomElement docItemAttrs = docu->createElement("PageItemAttributes");
		ObjAttrVector *attributes=item->getObjectAttributes();
		for(ObjAttrVector::Iterator objAttrIt = attributes->begin() ; objAttrIt != attributes->end(); ++objAttrIt )
		{
			QDomElement itemAttr = docu->createElement("ItemAttribute");
			itemAttr.setAttribute("Name", (*objAttrIt).name);
			itemAttr.setAttribute("Type", (*objAttrIt).type);
			itemAttr.setAttribute("Value", (*objAttrIt).value);
			itemAttr.setAttribute("Parameter", (*objAttrIt).parameter);
			itemAttr.setAttribute("Relationship", (*objAttrIt).relationship);
			itemAttr.setAttribute("RelationshipTo", (*objAttrIt).relationshipto);
			itemAttr.setAttribute("AutoAddTo", (*objAttrIt).autoaddto);
			docItemAttrs.appendChild(itemAttr);
		}
		ob.appendChild(docItemAttrs);

		dc->appendChild(ob);
	}
}

void Scribus13Format::SetItemProps(QDomElement *ob, PageItem* item, const QString& baseDir, bool newFormat)
{
	double xf, yf;
	QString tmp, tmpy;
	if (newFormat)
		ob->setAttribute("OwnPage", item->OwnPage);
	ob->setAttribute("PTYPE",item->itemType());
	ob->setAttribute("XPOS",item->xPos());
	ob->setAttribute("YPOS",item->yPos());
	ob->setAttribute("WIDTH",item->width());
	ob->setAttribute("HEIGHT",item->height());
	ob->setAttribute("RADRECT",item->cornerRadius());
	ob->setAttribute("FRTYPE", item->FrameType);
	ob->setAttribute("CLIPEDIT", item->ClipEdited ? 1 : 0);
	ob->setAttribute("PWIDTH",item->lineWidth());
	ob->setAttribute("PCOLOR",item->fillColor());
	ob->setAttribute("PCOLOR2",item->lineColor());
	ob->setAttribute("TXTFILL",item->itemText.defaultStyle().charStyle().fillColor());
	ob->setAttribute("TXTSTROKE",item->itemText.defaultStyle().charStyle().strokeColor());
	ob->setAttribute("TXTSTRSH",item->itemText.defaultStyle().charStyle().strokeShade());
	ob->setAttribute("TXTFILLSH",item->itemText.defaultStyle().charStyle().fillShade());
	ob->setAttribute("TXTSCALE",item->itemText.defaultStyle().charStyle().scaleH() / 10.0);
	ob->setAttribute("TXTSCALEV",item->itemText.defaultStyle().charStyle().scaleV() / 10.0);
	ob->setAttribute("TXTBASE",item->itemText.defaultStyle().charStyle().baselineOffset() / 10.0);
	ob->setAttribute("TXTSHX",item->itemText.defaultStyle().charStyle().shadowXOffset() / 10.0);
	ob->setAttribute("TXTSHY",item->itemText.defaultStyle().charStyle().shadowYOffset() / 10.0);
	ob->setAttribute("TXTOUT",item->itemText.defaultStyle().charStyle().outlineWidth() / 10.0);
	ob->setAttribute("TXTULP",item->itemText.defaultStyle().charStyle().underlineOffset() / 10.0);
	ob->setAttribute("TXTULW",item->itemText.defaultStyle().charStyle().underlineWidth() / 10.0);
	ob->setAttribute("TXTSTP",item->itemText.defaultStyle().charStyle().strikethruOffset() / 10.0);
	ob->setAttribute("TXTSTW",item->itemText.defaultStyle().charStyle().strikethruWidth() / 10.0);
	ob->setAttribute("TXTSTYLE",item->itemText.defaultStyle().charStyle().effects());
	ob->setAttribute("COLUMNS", item->columns());
	ob->setAttribute("COLGAP", item->columnGap());
	ob->setAttribute("NAMEDLST",item->NamedLStyle);
	ob->setAttribute("SHADE",item->fillShade());
	ob->setAttribute("SHADE2",item->lineShade());
	ob->setAttribute("GRTYP",item->GrType);
	ob->setAttribute("ROT",item->rotation());
	ob->setAttribute("PLINEART",item->PLineArt);
	ob->setAttribute("PLINEEND", item->PLineEnd);
	ob->setAttribute("PLINEJOIN", item->PLineJoin);
	ob->setAttribute("LINESP",item->itemText.defaultStyle().lineSpacing());
	ob->setAttribute("LINESPMode", item->itemText.defaultStyle().lineSpacingMode());
	ob->setAttribute("TXTKERN",item->itemText.defaultStyle().charStyle().tracking());
	ob->setAttribute("LOCALSCX",item->imageXScale());
	ob->setAttribute("LOCALSCY",item->imageYScale());
	ob->setAttribute("LOCALX",item->imageXOffset());
	ob->setAttribute("LOCALY",item->imageYOffset());
	ob->setAttribute("LOCALROT", item->imageRotation());
	ob->setAttribute("PICART", item->imageShown() ? 1 : 0);
	ob->setAttribute("PLTSHOW", item->PoShow ? 1 : 0);
	ob->setAttribute("BASEOF", item->BaseOffs);
	ob->setAttribute("FLIPPEDH", item->imageFlippedH());
	ob->setAttribute("FLIPPEDV", item->imageFlippedV());
/*	ob->setAttribute("BBOXX",item->BBoxX);
	ob->setAttribute("BBOXH",item->BBoxH); */
	ob->setAttribute("IFONT",item->itemText.defaultStyle().charStyle().font().scName());
	ob->setAttribute("ISIZE",item->itemText.defaultStyle().charStyle().fontSize() / 10.0 );
	ob->setAttribute("SCALETYPE", item->ScaleType ? 1 : 0);
	ob->setAttribute("RATIO", item->AspectRatio ? 1 : 0);
	ob->setAttribute("PRINTABLE", item->printEnabled() ? 1 : 0);
	if(item->isAnnotation())
	{
		ob->setAttribute("ANNOTATION",1);
		ob->setAttribute("ANTYPE", item->annotation().Type());
		ob->setAttribute("ANACTION", item->annotation().Action());
		ob->setAttribute("ANEACT", item->annotation().E_act());
		ob->setAttribute("ANXACT", item->annotation().X_act());
		ob->setAttribute("ANDACT", item->annotation().D_act());
		ob->setAttribute("ANFOACT", item->annotation().Fo_act());
		ob->setAttribute("ANBLACT", item->annotation().Bl_act());
		ob->setAttribute("ANKACT", item->annotation().K_act());
		ob->setAttribute("ANFACT", item->annotation().F_act());
		ob->setAttribute("ANVACT", item->annotation().V_act());
		ob->setAttribute("ANCACT", item->annotation().C_act());
		if (item->annotation().ActionType() == 8)
			ob->setAttribute("ANEXTERN", item->annotation().Extern());
		else
			ob->setAttribute("ANEXTERN", Path2Relative(item->annotation().Extern(), baseDir));
		ob->setAttribute("ANZIEL", item->annotation().Ziel());
		ob->setAttribute("ANACTYP", item->annotation().ActionType());
		ob->setAttribute("ANTOOLTIP", item->annotation().ToolTip());
		ob->setAttribute("ANBWID", item->annotation().Bwid());
		ob->setAttribute("ANBSTY", item->annotation().Bsty());
		ob->setAttribute("ANFEED", item->annotation().Feed());
		ob->setAttribute("ANFLAG", item->annotation().Flag());
		ob->setAttribute("ANFONT", item->annotation().Font());
		ob->setAttribute("ANFORMAT", item->annotation().Format());
		ob->setAttribute("ANROLL", item->annotation().RollOver());
		ob->setAttribute("ANDOWN", item->annotation().Down());
		ob->setAttribute("ANVIS", item->annotation().Vis());
		ob->setAttribute("ANMC", item->annotation().MaxChar());
		ob->setAttribute("ANCHK", item->annotation().IsChk());
		ob->setAttribute("ANAA", item->annotation().AAact());
		ob->setAttribute("ANCHKS", item->annotation().ChkStil());
		ob->setAttribute("ANBCOL", item->annotation().borderColor());
		ob->setAttribute("ANHTML", item->annotation().HTML());
		ob->setAttribute("ANICON", item->annotation().UseIcons());
		ob->setAttribute("ANPLACE", item->annotation().IPlace());
		ob->setAttribute("ANSCALE", item->annotation().ScaleW());
	}
	else
		ob->setAttribute("ANNOTATION",0);
	ob->setAttribute("ANNAME", !item->AutoName ? item->itemName() : QString(""));
	// "TEXTFLOWMODE" succeed to "TEXTFLOW" "TEXTFLOW2" and "TEXTFLOW3" attributes
	ob->setAttribute("TEXTFLOWMODE", (int) item->textFlowMode() );
	// Set "TEXTFLOW" "TEXTFLOW2" and "TEXTFLOW3" attributes for compatibility
	// with versions prior to 1.3.4
	ob->setAttribute("TEXTFLOW" , item->textFlowAroundObject() ? 1 : 0);
	ob->setAttribute("TEXTFLOW2", item->textFlowUsesBoundingBox() ? 1 : 0);
	ob->setAttribute("TEXTFLOW3", item->textFlowUsesContourLine() ? 1 : 0);
	ob->setAttribute("AUTOTEXT", item->isAutoText ? 1 : 0);
	ob->setAttribute("EXTRA",item->textToFrameDistLeft());
	ob->setAttribute("TEXTRA",item->textToFrameDistTop());
	ob->setAttribute("BEXTRA",item->textToFrameDistBottom());
	ob->setAttribute("REXTRA",item->textToFrameDistRight());
	if (((item->asImageFrame()) || (item->asTextFrame())) && (!item->Pfile.isEmpty()))
		ob->setAttribute("PFILE",Path2Relative(item->Pfile, baseDir));
	else
		ob->setAttribute("PFILE","");
	if (!item->Pfile2.isEmpty())
		ob->setAttribute("PFILE2",Path2Relative(item->Pfile2, baseDir));
	else
		ob->setAttribute("PFILE2","");
	if (!item->Pfile3.isEmpty())
		ob->setAttribute("PFILE3",Path2Relative(item->Pfile3, baseDir));
	else
		ob->setAttribute("PFILE3","");
	ob->setAttribute("PRFILE",item->IProfile);
	ob->setAttribute("EPROF", item->EmProfile);
	ob->setAttribute("IRENDER",item->IRender);
	ob->setAttribute("EMBEDDED", item->UseEmbedded ? 1 : 0);
	ob->setAttribute("LOCK", item->locked() ? 1 : 0);
	ob->setAttribute("LOCKR", item->sizeLocked() ? 1 : 0);
	ob->setAttribute("REVERS", item->reversed() ? 1 : 0);
	ob->setAttribute("TransValue", item->fillTransparency());
	ob->setAttribute("TransValueS", item->lineTransparency());
	ob->setAttribute("isTableItem", static_cast<int>(item->isTableItem));
	ob->setAttribute("TopLine", static_cast<int>(item->TopLine));
	ob->setAttribute("LeftLine", static_cast<int>(item->LeftLine));
	ob->setAttribute("RightLine", static_cast<int>(item->RightLine));
	ob->setAttribute("BottomLine", static_cast<int>(item->BottomLine));
	if (item->isTableItem)
	{
		if (item->TopLink != 0)
			ob->setAttribute("TopLINK", item->TopLink->ItemNr);
		else
			ob->setAttribute("TopLINK", -1);
		if (item->LeftLink != 0)
			ob->setAttribute("LeftLINK", item->LeftLink->ItemNr);
		else
			ob->setAttribute("LeftLINK", -1);
		if (item->RightLink != 0)
			ob->setAttribute("RightLINK", item->RightLink->ItemNr);
		else
			ob->setAttribute("RightLINK", -1);
		if (item->BottomLink != 0)
			ob->setAttribute("BottomLINK", item->BottomLink->ItemNr);
		else
			ob->setAttribute("BottomLINK", -1);
		ob->setAttribute("OwnLINK", item->ItemNr);
	}
	ob->setAttribute("NUMDASH", static_cast<int>(item->DashValues.count()));
	QString dlp = "";
	QVector<double>::Iterator dax;
	for (dax = item->DashValues.begin(); dax != item->DashValues.end(); ++dax)
		dlp += tmp.setNum((*dax)) + " ";
	ob->setAttribute("DASHS", dlp);
	ob->setAttribute("DASHOFF", item->DashOffset);
	ob->setAttribute("NUMPO",item->PoLine.size());
	QString polp = "";
	for (uint nxx=0; nxx<item->PoLine.size(); ++nxx)
	{
		item->PoLine.point(nxx, &xf, &yf);
		polp += tmp.setNum(xf) + " " + tmpy.setNum(yf) + " ";
	}
	ob->setAttribute("POCOOR", polp);
	ob->setAttribute("NUMCO",item->ContourLine.size());
	QString colp = "";
	for (uint nxx=0; nxx<item->ContourLine.size(); ++nxx)
	{
		item->ContourLine.point(nxx, &xf, &yf);
		colp += tmp.setNum(xf) + " " + tmpy.setNum(yf) + " ";
	}
	ob->setAttribute("COCOOR", colp);
	ob->setAttribute("NUMGROUP", static_cast<int>(item->Groups.count()));
	QString glp = "";
	QStack<int>::Iterator nx;
	for (nx = item->Groups.begin(); nx != item->Groups.end(); ++nx)
		glp += tmp.setNum((*nx)) + " ";
	ob->setAttribute("GROUPS", glp);
	ob->setAttribute("LANGUAGE", item->itemText.defaultStyle().charStyle().language());
	ob->setAttribute("startArrowIndex", item->startArrowIndex());
	ob->setAttribute("endArrowIndex", item->endArrowIndex());
}
