/***************************************************************************
                          scribus.cpp  -  description
                             -------------------
    begin                : Fre Apr  6 21:09:31 CEST 2001
    copyright            : (C) 2001 by Franz Schmid
    email                : Franz.Schmid@altmuehlnet.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qaccel.h>
#include <qapplication.h>
#include <qcolordialog.h>
#include <qcolor.h>
#include <qiconset.h>
#include <qtextstream.h>
#include <qstylefactory.h>
#include <qregexp.h>
#include <qtextcodec.h>
#include <qcursor.h>
#include <qvbox.h>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <string>
#include "scribus.h"
#include "scribus.moc"
#include "newfile.h"
#include "page.h"
#include "query.h"
#include "mdup.h"
#include "docinfo.h"
#include "reformdoc.h"
#include "serializer.h"
#include "align.h"
#include "fmitem.h"
#include "fontprefs.h"
#include "libprefs/prefs.h"
#include "pdfopts.h"
#include "inspage.h"
#include "delpages.h"
#include "movepage.h"
#include "helpbrowser.h"
#include "scribusXml.h"
#include "libabout/about.h"
#include "druck.h"
#include "editformats.h"
#include "muster.h"
#include "applytemplate.h"
#include "picstatus.h"
#include "customfdialog.h"
#include "cmsprefs.h"
#include "annot.h"
#include "annota.h"
#include "javadocs.h"
#include "colorm.h"

#if (_MSC_VER >= 1200)
 #include "win-config.h"
#else
 #include "config.h"
#endif

#include "fpoint.h"
#include "fpointarray.h"
#include "hysettings.h"
#include "guidemanager.h"
#include "mergedoc.h"
#include "lineformats.h"
#include "story.h"
#include "autoform.h"
#include "tabmanager.h"
#include "search.h"
#include "fontcombo.h"

#include <unistd.h>

extern QPixmap loadIcon(QString nam);
extern bool overwrite(QWidget *parent, QString filename);
extern void CopyPageItem(struct CLBuf *Buffer, PageItem *b);

using namespace std;

#ifdef HAVE_CMS
cmsHPROFILE CMSoutputProf;
cmsHPROFILE CMSprinterProf;
cmsHTRANSFORM stdTrans;
cmsHTRANSFORM stdProof;
cmsHTRANSFORM stdTransImg;
cmsHTRANSFORM stdProofImg;    
bool SoftProofing;
bool Gamut;
bool CMSuse;
int IntentMonitor;
int IntentPrinter;
#endif
bool CMSavail;
ProfilesL InputProfiles;
int PolyC;
int PolyFd;
double PolyF;
bool PolyS;
double PolyR;
double UmReFaktor;
QString DocDir;
ScribusApp* ScApp;

ScribusApp::ScribusApp(SplashScreen *splash)
{
	ScApp = this;
  setCaption( tr("Scribus " VERSION));
	setKeyCompression(false);
  setIcon(loadIcon("AppIcon.png"));
  initMenuBar();
  initStatusBar();
  WerkTools2 = new QToolBar( tr("File"), this);
  DatNeu = new QToolButton(loadIcon("DateiNeu.xpm"), tr("Creates a new Document"), QString::null, this, SLOT(slotFileNew()), WerkTools2);
  DatOpe = new QToolButton(loadIcon("DateiOpen.xpm"), tr("Opens a Document"), QString::null, this, SLOT(slotDocOpen()), WerkTools2);
  DatSav = new QToolButton(loadIcon("DateiSave.xpm"), tr("Saves the Current Document"), QString::null, this, SLOT(slotFileSave()), WerkTools2);
  DatClo = new QToolButton(loadIcon("DateiClos.xpm"), tr("Closes the Current Document"), QString::null, this, SLOT(slotFileClose()), WerkTools2);
  DatPri = new QToolButton(loadIcon("DateiPrint.xpm"), tr("Prints the Current Document"), QString::null, this, SLOT(slotFilePrint()), WerkTools2);
  DatPDF = new QToolButton(loadIcon("acrobat.png"), tr("Saves the Current Document as PDF"), QString::null, this, SLOT(SaveAsPDF()), WerkTools2);
  DatSav->setEnabled(false);
  DatClo->setEnabled(false);
  DatPri->setEnabled(false);
  DatPDF->setEnabled(false);
  DatOpe->setPopup(recentMenu);
  WerkTools = new WerkToolB(this);
  setDockEnabled(WerkTools, DockLeft, false);
  setDockEnabled(WerkTools, DockRight, false);
  WerkTools->Sichtbar = true;
  WerkTools->setEnabled(false);
  WerkToolsP = new WerkToolBP(this);
  setDockEnabled(WerkToolsP, DockLeft, false);
  setDockEnabled(WerkToolsP, DockRight, false);
  WerkToolsP->setEnabled(false);
  WerkToolsP->Sichtbar = true;
  QString Pff = QString(getenv("HOME"))+"/.scribus";
  QFileInfo Pffi = QFileInfo(Pff);
  if (Pffi.exists())
  	{
    if (Pffi.isDir())
      PrefsPfad = Pff;
        else
      PrefsPfad = QString(getenv("HOME"));
  	}
  else
  	{
  	QDir di = QDir();
    di.mkdir(Pff);
    PrefsPfad = Pff;
    QString OldPR = QString(getenv("HOME"))+"/.scribus.rc";
    QFileInfo OldPi = QFileInfo(OldPR);
    if (OldPi.exists())
    	{
			system("mv " + OldPR + " " + Pff+"/scribus.rc");
			}
		QString OldPR2 = QString(getenv("HOME"))+"/.scribusfont.rc";
		QFileInfo OldPi2 = QFileInfo(OldPR2);
		if (OldPi2.exists())
			{
			system("mv " + OldPR2 + " " + Pff+"/scribusfont.rc");
			}
		QString OldPR3 = QString(getenv("HOME"))+"/.scribusscrap.scs";
		QFileInfo OldPi3 = QFileInfo(OldPR3);
		if (OldPi3.exists())
			{
			system("mv " + OldPR3 + " " + Pff+"/scrap.scs");
			}
		}
	/** Erstelle Fontliste */
  NoFonts = false;
	BuFromApp = false;
	splash->setStatus( tr("Searching for Fonts"));
  GetAllFonts();
  if (NoFonts)
  	{
		QString mess = tr("There are no Postscript-Fonts on your System");
		mess += "\n" + tr("Exiting now");
		QMessageBox::critical(this, tr("Fatal Error"), mess, 1, 0, 0);
  	}
  else
  	{
  	HaveDoc = 0;
		singleClose = false;
		ScriptRunning = false;
		view = NULL;
		doc = NULL;
  	BuildFontMenu();
		SCFontsIterator it(Prefs.AvailFonts);
		Prefs.DefFont = it.currentKey();
  	Prefs.DefSize = 120;
  	Prefs.AppFontSize = qApp->font().pointSize();
  	/** Default Farbenliste */
  	Prefs.DColors.clear();
  	QString pfadC = PREL;
  	QString pfadC2 = pfadC + "/lib/scribus/rgbscribus.txt";
  	QFile fiC(pfadC2);
  	if (!fiC.exists())
			{
	  	Prefs.DColors.insert("White", CMYKColor(0, 0, 0, 0));
  		Prefs.DColors.insert("Black", CMYKColor(0, 0, 0, 255));
			Prefs.DColors.insert("Blue", CMYKColor(255, 255, 0, 0));
			Prefs.DColors.insert("Cyan", CMYKColor(255, 0, 0, 0));
			Prefs.DColors.insert("Green", CMYKColor(255, 0, 255, 0));
			Prefs.DColors.insert("Red", CMYKColor(0, 255, 255, 0));
			Prefs.DColors.insert("Yellow", CMYKColor(0, 0, 255, 0));
			Prefs.DColors.insert("Magenta", CMYKColor(0, 255, 0, 0));
			}
		else
			{
			if (fiC.open(IO_ReadOnly))
				{
				QString ColorEn, Cname;
				int Rval, Gval, Bval;
				QTextStream tsC(&fiC);
				ColorEn = tsC.readLine();
				while (!tsC.atEnd())
					{
					ColorEn = tsC.readLine();
					QTextStream CoE(&ColorEn, IO_ReadOnly);
					CoE >> Rval;
					CoE >> Gval;
					CoE >> Bval;
					CoE >> Cname;
					CMYKColor tmp;
					tmp.setColorRGB(Rval, Gval, Bval);
					Prefs.DColors.insert(Cname, tmp);
					}
				fiC.close();
				}
			}
		DispX = 10;
		DispY = 10;
		Prefs.Wheelval = 40;
		Prefs.GrabRad = 4;
		Prefs.GuideRad = 10;
		Prefs.DminGrid = 20;
	  Prefs.DmajGrid = 100;
	  DocNr = 1;
	  Prefs.DminColor = QColor(green);
	  Prefs.DmajColor = QColor(green);
	  Prefs.DpapColor = QColor(white);
	  Prefs.DmargColor = QColor(blue);
		Prefs.guideColor = QColor(darkBlue);
	  Prefs.DVHoch = 33;
	  Prefs.DVHochSc = 100;
	  Prefs.DVTief = 33;
	  Prefs.DVTiefSc = 100;
	  Prefs.DVKapit = 75;
	  Prefs.GUI = "Default";
	  Prefs.Dpen = "Black";
	  Prefs.Dbrush = "Black";
	  Prefs.Dshade = 100;
	  Prefs.Dshade2 = 100;
	  Prefs.DLineArt = SolidLine;
	  Prefs.Dwidth = 1;
	  Prefs.DpenLine = "Black";
	  Prefs.DpenText = "Black";
		Prefs.DCols = 1;
		Prefs.DGap = 0.0;
	  Prefs.DshadeLine = 100;
	  Prefs.DLstyleLine = SolidLine;
	  Prefs.DwidthLine = 1;
	  Prefs.MagMin = 10;
	  Prefs.MagMax = 800;
	  Prefs.MagStep = 25;
	  Prefs.DbrushPict = "White";
	  Prefs.ShadePict = 100;
	  Prefs.ScaleX = 1;
	  Prefs.ScaleY = 1;
	  Prefs.Before = true;
	  Prefs.Einheit = 0;
		UmReFaktor = 1.0;
		PolyC = 4;
		PolyF = 0.5;
		PolyS = false;
		PolyFd = 0;
		PolyR = 0;
		Prefs.PolyC = PolyC;
		Prefs.PolyF = PolyF;
		Prefs.PolyFd = PolyFd;
		Prefs.PolyS = PolyS;
		Prefs.PolyR = PolyR;
	  Prefs.Werkv = true;
	  Prefs.WerkvP = true;
	  Prefs.Mpalv = false;
	  Prefs.Tpalv = false;
	  Prefs.SCpalv = false;
	  Prefs.Lpalv = false;
		Prefs.Bopalv = false;
	  Prefs.Mpalx = 0;
	  Prefs.Mpaly = 0;
		Prefs.Tpalx = 0;
		Prefs.Tpaly = 0;
		Prefs.SCpalx = 0;
		Prefs.SCpaly = 0;
		Prefs.SCpalw = 100;
		Prefs.SCpalh = 200;
		Prefs.Sepalx = 0;
		Prefs.Sepaly = 0;
		Prefs.Bopalx = 0;
		Prefs.Bopaly = 0;
		Prefs.Lpalx = 0;
		Prefs.Lpaly = 0;
	  Prefs.PSize = 40;
	  Prefs.SaveAtQ = true;
	  Prefs.ShFrames = true;
	  Prefs.PagesSbS = true;
	  Prefs.RecentDocs.clear();
	  Prefs.RecentDCount = 5;
	  Prefs.RandFarbig = false;
	  Prefs.AutoLine = 20;
		Prefs.PageFormat = 4;
		Prefs.Ausrichtung = 0;
		Prefs.PageBreite = 595;
		Prefs.PageHoehe = 842;
		Prefs.RandOben = 9;
		Prefs.RandUnten = 40;
		Prefs.RandLinks = 9;
		Prefs.RandRechts = 9;
		Prefs.DoppelSeiten = false;
		Prefs.ErsteLinks = false;
		Prefs.ScaleType = true;
		Prefs.AspectRatio = true;
		Prefs.MinWordLen = 3;
		Prefs.Language = "";
		Prefs.Automatic = true;
		Prefs.AutoCheck = false;
		Prefs.PDFTransparency = false;
		Prefs.AutoSave = false;
		Prefs.AutoSaveTime = 600000;
		Prefs.DisScale = 1.0;
		Prefs.DocDir = QString(getenv("HOME"));
		Prefs.ProfileDir = "";
		Prefs.ScriptDir = "";
		Prefs.DColorSet = "Scribus-Small";
		Prefs.CustomColorSets.clear();
		PDef.Pname = "";
		PDef.Dname = "";
		PDef.Command = "";
	  PrinterUsed = false;
		resize(610, 600);
    QVBox* vb = new QVBox( this );
    vb->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
    wsp = new QWorkspace( vb );
    setCentralWidget( vb );
		connect(wsp, SIGNAL(windowActivated(QWidget *)), this, SLOT(newActWin(QWidget *)));
		Tpal = new Tree(this, 0);
		Mpal = new Mpalette(this, &Prefs);
		Mpal->Cpal->SetColors(Prefs.DColors);
		Npal = new NodePalette(this);
		Lpal = new LayerPalette(this);
		ScBook = new Biblio(this, &Prefs);
		Sepal = new SeitenPal(this);
		BookPal = new BookPalette(this);
		CMSavail = false;
		keyrep = false;
		Prefs.DCMSset.DefaultMonitorProfile = "";
		Prefs.DCMSset.DefaultPrinterProfile = "";
		Prefs.DCMSset.DefaultInputProfile = "";
		Prefs.DCMSset.DefaultInputProfile2 = "";
		Prefs.DCMSset.CMSinUse = false;
		Prefs.DCMSset.SoftProofOn = false;
		Prefs.DCMSset.GamutCheck = false;
		Prefs.DCMSset.BlackPoint = true;
		Prefs.DCMSset.DefaultIntentMonitor = 1;
		Prefs.DCMSset.DefaultIntentMonitor2 = 1;
		Prefs.DCMSset.DefaultIntentPrinter = 0;
		Prefs.GFontSub.clear();
		SetKeyEntry(56, tr("Smart Hyphen"), 0, ALT+Key_Minus);
		SetKeyEntry(57, tr("Align Left"), 0, CTRL+Key_L);
		SetKeyEntry(58, tr("Align Right"), 0, CTRL+Key_R);
		SetKeyEntry(59, tr("Align Center"), 0, CTRL+Key_E);
		SetKeyEntry(60, tr("Insert Page Number"), 0, ALT+Key_NumberSign);
		SetKeyEntry(61, tr("Attach Text to Path"), PfadT, 0);
		SetKeyEntry(62, tr("Show Layers"), viewLpal, 0);
		SetKeyEntry(63, tr("Javascripts..."), jman, 0);
		SetKeyEntry(64, tr("Undo"), edUndo, CTRL+Key_Z);
		SetKeyEntry(65, tr("Show Page Palette"), viewSepal, 0);
		SetKeyEntry(66, tr("Lock/Unlock"), LockOb, CTRL+Key_H);
		SetKeyEntry(67, tr("Non Breaking Space"), 0, CTRL+Key_Space);
		splash->setStatus( tr("Reading Preferences"));
		ReadPrefs();
		if (Prefs.DefFont == "")
			Prefs.DefFont = it.currentKey();
		splash->setStatus( tr("Getting ICC-Profiles"));
		GetCMSProfiles();
		splash->setStatus( tr("Init Hyphenator"));
		InitHyphenator();
		Mpal->Cpal->UseTrans(Prefs.PDFTransparency);
		Mpal->Fonts->RebuildList(&Prefs);
		Mpal->fillLangCombo(Sprachen);
		DocDir = Prefs.DocDir;
		splash->setStatus( tr(""));
		splash->setStatus( tr("Setting up Shortcuts"));
		SetShortCut();
		if (CMSavail)
			{
			hymen->insertItem( tr("Color Management..."), this , SLOT(SetCMSPrefs()));
			ProfilesL::Iterator ip;
			if ((Prefs.DCMSset.DefaultInputProfile == "") || (!InputProfiles.contains(Prefs.DCMSset.DefaultInputProfile)))
				{
				ip = InputProfiles.begin();
				Prefs.DCMSset.DefaultInputProfile = ip.key();
				}
			if ((Prefs.DCMSset.DefaultInputProfile2 == "") || (!InputProfiles.contains(Prefs.DCMSset.DefaultInputProfile2)))
				{
				ip = InputProfiles.begin();
				Prefs.DCMSset.DefaultInputProfile2 = ip.key();
				}
			if ((Prefs.DCMSset.DefaultMonitorProfile == "") || (!MonitorProfiles.contains(Prefs.DCMSset.DefaultMonitorProfile)))
				{
				ip = MonitorProfiles.begin();
				Prefs.DCMSset.DefaultMonitorProfile = ip.key();
				}
			if ((Prefs.DCMSset.DefaultPrinterProfile == "") || (!PrinterProfiles.contains(Prefs.DCMSset.DefaultPrinterProfile)))
				{
				ip = PrinterProfiles.begin();
				Prefs.DCMSset.DefaultPrinterProfile = ip.key();
				}
#ifdef HAVE_CMS
			SoftProofing = Prefs.DCMSset.SoftProofOn;
			CMSuse = false;
			IntentPrinter = Prefs.DCMSset.DefaultIntentPrinter;
			IntentMonitor = Prefs.DCMSset.DefaultIntentMonitor;
#endif
			}
		splash->setStatus( tr("Reading Scrapbook"));
		QString SCf = PrefsPfad+"/scrap.scs";
		QFileInfo SCfi = QFileInfo(SCf);
		if (SCfi.exists())
			{
			ScBook->BibWin->ReadContents(SCf);
			ScBook->ScFilename = SCf;
			}
		ScBook->AdjustMenu();
		HaveGS = system("gs -h > /dev/null 2>&1");
		splash->setStatus( tr("Initializing Plugins"));
		InitPlugs(splash);
		ClipB = QApplication::clipboard();
		connect(WerkTools, SIGNAL(NewMode(int)), this, SLOT(ModeFromTB(int)));
		connect(WerkTools, SIGNAL(Schliessen()), this, SLOT(ToggleTools()));
		connect(WerkToolsP, SIGNAL(NewMode(int)), this, SLOT(ModeFromTB(int)));
		connect(WerkToolsP, SIGNAL(Schliessen()), this, SLOT(TogglePDFTools()));
		connect(Mpal, SIGNAL(DocChanged()), this, SLOT(slotDocCh()));
		connect(Mpal, SIGNAL(NewAbStyle(int)), this, SLOT(setNewAbStyle(int)));
		connect(Mpal, SIGNAL(BackHome()), this, SLOT(Aktiv()));
		connect(Mpal, SIGNAL(Stellung(int)), this, SLOT(setItemHoch(int)));
		connect(Mpal, SIGNAL(Schliessen()), this, SLOT(ToggleMpal()));
		connect(Mpal, SIGNAL(EditCL()), this, SLOT(ToggleFrameEdit()));
		connect(Mpal, SIGNAL(NewTF(QString)), this, SLOT(SetNewFont(QString)));
		connect(Mpal, SIGNAL(UpdtGui(int)), this, SLOT(HaveNewSel(int)));
		connect(Mpal->Cpal, SIGNAL(NewPen(QString)), this, SLOT(setPenFarbe(QString)));
		connect(Mpal->Cpal, SIGNAL(NewBrush(QString)), this, SLOT(setBrushFarbe(QString)));
		connect(Mpal->Cpal, SIGNAL(NewPenShade(int)), this, SLOT(setPenShade(int)));
		connect(Mpal->Cpal, SIGNAL(NewBrushShade(int)), this, SLOT(setBrushShade(int)));
		connect(Mpal->Cpal, SIGNAL(NewTrans(double)), this, SLOT(SetTranspar(double)));
		connect(Mpal->Cpal, SIGNAL(NewTransS(double)), this, SLOT(SetTransparS(double)));
		connect(Mpal->Cpal, SIGNAL(NewGradient(int, QString, int, QString, int)), this, SLOT(setGradFill(int, QString, int, QString, int)));
		connect(Mpal->Cpal, SIGNAL(QueryItem()), this, SLOT(GetBrushPen()));
		connect(Tpal, SIGNAL(Schliessen()), this, SLOT(ToggleTpal()));
		connect(Tpal, SIGNAL(SelectElement(int, int)), this, SLOT(SelectFromOutl(int, int)));
		connect(Tpal, SIGNAL(SelectSeite(int)), this, SLOT(SelectFromOutlS(int)));
		connect(Mpal->Spal, SIGNAL(NewStyle(int)), this, SLOT(setNewAbStyle(int)));
		connect(Mpal->Spal, SIGNAL(EditSt()), this, SLOT(slotEditStyles()));
		connect(Mpal, SIGNAL(EditLSt()), this, SLOT(slotEditLineStyles()));
		connect(Npal, SIGNAL(Schliessen()), this, SLOT(NoFrameEdit()));
		connect(Lpal, SIGNAL(LayerActivated(int)), this, SLOT(changeLayer(int)));
		connect(Lpal, SIGNAL(LayerRemoved(int)), this, SLOT(LayerRemove(int)));
		connect(Lpal, SIGNAL(LayerChanged()), this, SLOT(showLayer()));
		connect(Lpal, SIGNAL(Schliessen()), this, SLOT(ToggleLpal()));
		connect(Sepal, SIGNAL(Schliessen()), this, SLOT(ToggleSepal()));
		connect(ScBook, SIGNAL(Schliessen()), this, SLOT(ToggleBpal()));
		connect(Sepal, SIGNAL(EditTemp(QString)), this, SLOT(ManageTemp(QString)));
		connect(Sepal->PageView, SIGNAL(UseTemp(QString, int)), this, SLOT(Apply_Temp(QString, int)));
		connect(Sepal->PageView, SIGNAL(NewPage(int, QString)), this, SLOT(slotNewPageP(int, QString)));
		connect(Sepal->Trash, SIGNAL(DelPage(int)), this, SLOT(DeletePage2(int)));
		connect(Sepal, SIGNAL(GotoSeite(int)), this, SLOT(SelectFromOutlS(int)));
		connect(BookPal->BView, SIGNAL(MarkMoved()), this, SLOT(StoreBookmarks()));
		connect(BookPal->BView, SIGNAL(ChangeBMNr(int, int, int)), this, SLOT(ChBookmarks(int, int, int)));
		connect(BookPal, SIGNAL(Schliessen()), this, SLOT(ToggleBookpal()));
		connect(recentMenu, SIGNAL(activated(int)), this, SLOT(LoadRecent(int)));
		connect(ColorMenC, SIGNAL(activated(int)), this, SLOT(setItemFarbe(int)));
	  connect(ShadeMenu, SIGNAL(activated(int)), this, SLOT(setItemShade(int)));
	  connect(FontMenu, SIGNAL(activated(int)), this, SLOT(setItemFont(int)));
	  connect(SizeTMenu, SIGNAL(activated(int)), this, SLOT(setItemFSize(int)));
	  connect(TypeStyleMenu, SIGNAL(activated(int)), this, SLOT(setItemTypeStyle(int)));
	  connect(AliMenu, SIGNAL(activated(int)), this, SLOT(setItemTextAli(int)));
		connect(this, SIGNAL(TextIFont(QString)), this, SLOT(AdjustFontMenu(QString)));
		connect(this, SIGNAL(TextISize(int)), this, SLOT(setFSizeMenu(int)));
		connect(this, SIGNAL(TextISize(int)), Mpal, SLOT(setSize(int)));
		connect(this, SIGNAL(TextUSval(double)), Mpal, SLOT(setExtra(double)));
		connect(this, SIGNAL(TextStil(int)), Mpal, SLOT(setStil(int)));
		connect(this, SIGNAL(TextScale(int)), Mpal, SLOT(setTScale(int)));
		connect(this, SIGNAL(TextFarben(QString, QString, int, int)), Mpal, SLOT(setActFarben(QString, QString, int, int)));
		connect(ClipB, SIGNAL(dataChanged()), this, SLOT(ClipChange()));
	  typedef void (*HandlerType)(int);
		HandlerType handler	= 0;
		handler = ScribusApp::defaultCrashHandler;
	  if (!handler)
	    handler = SIG_DFL;
	  sigset_t mask;
	  sigemptyset(&mask);
#ifdef SIGSEGV
	  signal (SIGSEGV, handler);
	  sigaddset(&mask, SIGSEGV);
#endif
#ifdef SIGFPE
	  signal (SIGFPE, handler);
	  sigaddset(&mask, SIGFPE);
#endif
#ifdef SIGILL
	  signal (SIGILL, handler);
	  sigaddset(&mask, SIGILL);
#endif
#ifdef SIGABRT
	  signal (SIGABRT, handler);
	  sigaddset(&mask, SIGABRT);
#endif
	  sigprocmask(SIG_UNBLOCK, &mask, 0);
	}
}

void ScribusApp::initMenuBar()
{
	int a;
	int MenID;
	QFont tmp;
	recentMenu = new QPopupMenu();
	RecentDocs.clear();
	fileMenu=new QPopupMenu();
	fid12 = fileMenu->insertItem(loadIcon("DateiNeu16.png"), tr("New"), this, SLOT(slotFileNew()), CTRL+Key_N);
	fid13 = fileMenu->insertItem(loadIcon("DateiOpen16.png"), tr("Open..."), this, SLOT(slotDocOpen()), CTRL+Key_O);
	fid14 = fileMenu->insertItem( tr("Recent Documents"), recentMenu);
	SetKeyEntry(0, tr("New"), fid12, CTRL+Key_N);
	SetKeyEntry(1, tr("Open..."), fid13, CTRL+Key_O);
	fileMenu->insertSeparator();
	fid1 = fileMenu->insertItem(loadIcon("DateiClos16.png"), tr("Close"), this, SLOT(slotFileClose()), CTRL+Key_W);
	SetKeyEntry(2, tr("Close"), fid1, CTRL+Key_W);
	fileMenu->setItemEnabled(fid1, 0);
	fid4 = fileMenu->insertItem(loadIcon("DateiSave16.png"), tr("Save"), this, SLOT(slotFileSave()), CTRL+Key_S);
	SetKeyEntry(3, tr("Save"), fid4, CTRL+Key_S);
	fileMenu->setItemEnabled(fid4, 0);
	fid5 = fileMenu->insertItem( tr("Save as..."), this, SLOT(slotFileSaveAs()));
	SetKeyEntry(4, tr("Save as..."), fid5, 0);
	fileMenu->setItemEnabled(fid5, 0);
	fid52 = fileMenu->insertItem( tr("Revert to Saved"), this, SLOT(slotFileRevert()));
	fileMenu->setItemEnabled(fid52, 0);
	fid51 = fileMenu->insertItem( tr("Collect for Output..."), this, SLOT(Collect()));
	fileMenu->setItemEnabled(fid51, 0);
	fileMenu->insertSeparator();
	importMenu = new QPopupMenu();
	fid2 = importMenu->insertItem( tr("Get Text/Picture..."), this, SLOT(slotFileOpen()));
	importMenu->setItemEnabled(fid2, 0);
	fid2a = importMenu->insertItem( tr("Insert Page..."), this, SLOT(slotDocMerge()));
	importMenu->setItemEnabled(fid2a, 0);
	fileMenu->insertItem( tr("Import..."), importMenu);
	exportMenu = new QPopupMenu();
	fid3 = exportMenu->insertItem( tr("Save Text..."), this, SLOT(SaveText()));
	exportMenu->setItemEnabled(fid3, 0);
	fid8 = exportMenu->insertItem( tr("Save Page as EPS..."), this, SLOT(SaveAsEps()));
	exportMenu->setItemEnabled(fid8, 0);
	fid10 = exportMenu->insertItem( tr("Save as PDF..."), this, SLOT(SaveAsPDF()));
	exportMenu->setItemEnabled(fid10, 0);
	fid11 = fileMenu->insertItem( tr("Export..."), exportMenu);
	fileMenu->setItemEnabled(fid11, 0);
	fileMenu->insertSeparator();
	fid6 = fileMenu->insertItem( tr("Document Info..."), this, SLOT(InfoDoc()), CTRL+Key_I);
	fileMenu->setItemEnabled(fid6, 0);
	SetKeyEntry(5, tr("Document Info..."), fid6, CTRL+Key_I);
	fid7 = fileMenu->insertItem( tr("Document Setup..."), this, SLOT(SetupDoc()));
	fileMenu->setItemEnabled(fid7, 0);
	SetKeyEntry(6, tr("Document Setup..."), fid7, 0);
	fid9 = fileMenu->insertItem(loadIcon("DateiPrint16.png"), tr("Print..."), this, SLOT(slotFilePrint()), CTRL+Key_P);
	fileMenu->setItemEnabled(fid9, 0);
	SetKeyEntry(7, tr("Print..."), fid9, CTRL+Key_P);
	fileMenu->insertSeparator();
	MenID = fileMenu->insertItem(loadIcon("exit.png"), tr("Quit"), this, SLOT(slotFileQuit()), CTRL+Key_Q);
	SetKeyEntry(8, tr("Quit"), MenID, CTRL+Key_Q);
	editMenu = new QPopupMenu();
	edUndo = editMenu->insertItem( tr("Undo"), this, SLOT(UnDoAction()), CTRL+Key_Z);
	editMenu->insertSeparator();
	edid1 = editMenu->insertItem(loadIcon("editcut.png"), tr("Cut"), this , SLOT(slotEditCut()), CTRL+Key_X);
	edid2 = editMenu->insertItem(loadIcon("editcopy.png"), tr("Copy"), this , SLOT(slotEditCopy()), CTRL+Key_C);
	edid3 = editMenu->insertItem(loadIcon("editpaste.png"), tr("Paste"), this , SLOT(slotEditPaste()), CTRL+Key_V);
	edid4 = editMenu->insertItem(loadIcon("editdelete.png"), tr("Clear"), this, SLOT(DeleteText()));
	edid5 = editMenu->insertItem( tr("Select all"), this, SLOT(SelectAll()), CTRL+Key_A);
	SetKeyEntry(9, tr("Cut"), edid1, CTRL+Key_X);
	SetKeyEntry(10, tr("Copy"), edid2, CTRL+Key_C);
	SetKeyEntry(11, tr("Paste"), edid3, CTRL+Key_V);
	SetKeyEntry(12, tr("Clear"), edid4, 0);
	SetKeyEntry(13, tr("Select all"), edid5, CTRL+Key_A);
	editMenu->insertSeparator();
	Sear = editMenu->insertItem( tr("Search/Replace..."), this, SLOT(SearchText()));
	editMenu->insertSeparator();
	MenID = editMenu->insertItem( tr("Colors..."), this , SLOT(slotEditColors()));
	SetKeyEntry(14, tr("Colors..."), MenID, 0);
	edid6 = editMenu->insertItem( tr("Paragraph Styles..."), this , SLOT(slotEditStyles()));
	edid6a = editMenu->insertItem( tr("Line Styles..."), this , SLOT(slotEditLineStyles()));
	SetKeyEntry(15, tr("Styles..."), edid6, 0);
	tman = editMenu->insertItem( tr("Templates..."), this, SLOT(ManageTemp()));
	SetKeyEntry(16, tr("Templates..."), tman, 0);
	jman = editMenu->insertItem( tr("Javascripts..."), this, SLOT(ManageJava()));
	hymen = new QPopupMenu();
	MenID = hymen->insertItem( tr("General..."), this , SLOT(slotPrefsOrg()));
	SetKeyEntry(18, tr("Preferences..."), MenID, 0);
	MenID = hymen->insertItem( tr("Fonts..."), this , SLOT(slotFontOrg()));
	SetKeyEntry(17, tr("Fonts..."), MenID, 0);
	hymen->insertItem( tr("Hyphenator..."), this, SLOT(configHyphenator()));
	editMenu->insertItem( tr("Preferences"), hymen);
	editMenu->setItemEnabled(edUndo, 0);
	editMenu->setItemEnabled(edid1, 0);
	editMenu->setItemEnabled(edid2, 0);
	editMenu->setItemEnabled(edid3, 0);
	editMenu->setItemEnabled(edid4, 0);
	editMenu->setItemEnabled(edid5, 0);
	editMenu->setItemEnabled(edid6, 0);
	editMenu->setItemEnabled(edid6a, 0);
	editMenu->setItemEnabled(Sear, 0);
	editMenu->setItemEnabled(tman, 0);
	editMenu->setItemEnabled(jman, 0);
	StilMenu = new QPopupMenu();
	ObjMenu = new QPopupMenu();
	SetKeyEntry(19, tr("Select New Font"), 0, 0);
	MenID = ObjMenu->insertItem( tr("Duplicate"), this, SLOT(ObjektDup()), CTRL+Key_D);
	SetKeyEntry(20, tr("Duplicate"), MenID, CTRL+Key_D);
	MenID = ObjMenu->insertItem( tr("Multiple Duplicate"), this, SLOT(ObjektDupM()));
	SetKeyEntry(21, tr("Multiple Duplicate"), MenID, 0);
	Loesch = ObjMenu->insertItem( tr("Delete"), this, SLOT(DeleteObjekt()), CTRL+Key_K);
	SetKeyEntry(22, tr("Delete"), Loesch, CTRL+Key_K);
	ObjMenu->insertSeparator();
	Gr = ObjMenu->insertItem( tr("Group"), this, SLOT(GroupObj()), CTRL+Key_G);
	SetKeyEntry(23, tr("Group"), Gr, CTRL+Key_G);
	UnGr = ObjMenu->insertItem( tr("Un-group"), this, SLOT(UnGroupObj()),CTRL+Key_U);
	SetKeyEntry(24, tr("Un-group"), UnGr, CTRL+Key_U);
	LockOb = ObjMenu->insertItem( tr("Lock"), this, SLOT(ToggleObjLock()), CTRL+Key_H);
	ObjMenu->insertSeparator();
	OBack = ObjMenu->insertItem( tr("Send to Back"), this, SLOT(Objekt2Back()));
	SetKeyEntry(25, tr("Send to Back"), OBack, 0);
	OFront = ObjMenu->insertItem( tr("Bring to Front"), this, SLOT(Objekt2Front()));
	SetKeyEntry(26, tr("Bring to Front"), OFront, 0);
	OLower = ObjMenu->insertItem( tr("Lower"), this, SLOT(ObjektLower()));
	SetKeyEntry(27, tr("Lower"), OLower, 0);
	ORaise = ObjMenu->insertItem( tr("Raise"), this, SLOT(ObjektRaise()));
	SetKeyEntry(28, tr("Raise"), ORaise, 0);
	DistM = ObjMenu->insertItem( tr("Distribute/Align..."), this, SLOT(ObjektAlign()));
	SetKeyEntry(29, tr("Distribute/Align..."), DistM, 0);
	ObjMenu->insertSeparator();
	ShapeMenu = new QPopupMenu();
	SCustom = new Autoforms(0);
	ShapeMenu->insertItem(SCustom);
    connect(SCustom, SIGNAL(FormSel(int, int, double *)), this, SLOT(MakeFrame(int, int, double *)));
	ShapeEdit = ShapeMenu->insertItem( tr("Edit Frame"), this, SLOT(ToggleFrameEdit()));
	ShapeM = ObjMenu->insertItem( tr("Shape"), ShapeMenu);
	PfadT = ObjMenu->insertItem( tr("Attach Text to Path"), this, SLOT(Pfadtext()));
	PfadDT = ObjMenu->insertItem( tr("Detach Text from Path"), this, SLOT(noPfadtext()));
	PfadV = ObjMenu->insertItem( tr("Combine Polygons"), this, SLOT(UniteOb()));
	PfadS = ObjMenu->insertItem( tr("Split Polygons"), this, SLOT(SplitUniteOb()));
	PfadTP = ObjMenu->insertItem( tr("Convert to Outlines"), this, SLOT(TraceText()));
	ObjMenu->setItemEnabled(ShapeM, 0);
	ObjMenu->setItemEnabled(DistM, 0);
	ObjMenu->setItemEnabled(Gr, 0);
	ObjMenu->setItemEnabled(UnGr, 0);
	ObjMenu->setItemEnabled(PfadT, 0);
	ObjMenu->setItemEnabled(PfadDT, 0);
	ObjMenu->setItemEnabled(PfadV, 0);
	ObjMenu->setItemEnabled(PfadS, 0);
	ObjMenu->setItemEnabled(LockOb, 0);
	ObjMenu->setItemEnabled(PfadTP, 0);
	pageMenu = new QPopupMenu();
	MenID = pageMenu->insertItem( tr("Insert..."), this, SLOT(slotNewPageM()));
	SetKeyEntry(30, tr("Insert..."), MenID, 0);
	pgmd = pageMenu->insertItem( tr("Delete..."), this, SLOT(DeletePage()));
	SetKeyEntry(31, tr("Delete..."), pgmd, 0);
	MenID = pageMenu->insertItem( tr("Copy")+"...", this, SLOT(CopyPage()));
	SetKeyEntry(61, tr("Copy")+"...", MenID, 0);
	pgmv = pageMenu->insertItem( tr("Move..."), this, SLOT(MovePage()));
	SetKeyEntry(32, tr("Move..."), pgmv, 0);
	MenID = pageMenu->insertItem( tr("Apply Template..."), this, SLOT(ApplyTemp()));
	SetKeyEntry(33, tr("Apply Template..."), MenID, 0);
	MenID = pageMenu->insertItem( tr("Manage Guides..."), this, SLOT(ManageGuides()));
	SetKeyEntry(49, tr("Manage Guides..."), MenID, 0);
	pageMenu->setItemEnabled(pgmd, 0);
	pageMenu->setItemEnabled(pgmv, 0);
	viewMenu=new QPopupMenu();
	MenID = viewMenu->insertItem( tr("Fit in Window"), this, SLOT(slotZoomFit()), CTRL+Key_0);
	SetKeyEntry(34, tr("Fit in Window"), MenID, CTRL+Key_0);
	MenID = viewMenu->insertItem("50%", this, SLOT(slotZoom50()));
	SetKeyEntry(35, tr("50%"), MenID, 0);
	MenID = viewMenu->insertItem("75%", this, SLOT(slotZoom75()));
	SetKeyEntry(36, tr("75%"), MenID, 0);
	MenID = viewMenu->insertItem( tr("Actual Size"), this, SLOT(slotZoom100()), CTRL+Key_1);
	SetKeyEntry(37, tr("Actual Size"), MenID, CTRL+Key_1);
	MenID = viewMenu->insertItem("200%", this, SLOT(slotZoom200()));
	SetKeyEntry(38, tr("200%"), MenID, 0);
	MenID = viewMenu->insertItem( tr("Thumbnails"), this, SLOT(slotZoom20()));
	SetKeyEntry(39, tr("Thumbnails"), MenID, 0);
	viewMenu->insertSeparator();
	Markers = viewMenu->insertItem( tr("Hide Margins"), this, SLOT(ToggleMarks()));
	SetKeyEntry(40, tr("Hide Margins"), Markers, 0);
	FrameDr = viewMenu->insertItem( tr("Hide Frames"), this, SLOT(ToggleFrames()));
	SetKeyEntry(41, tr("Hide Frames"), FrameDr, 0);
	Bilder = viewMenu->insertItem( tr("Hide Images"), this, SLOT(TogglePics()));
	SetKeyEntry(42, tr("Hide Images"), Bilder, 0);
	Ras = viewMenu->insertItem( tr("Show Grid"), this, SLOT(ToggleRaster()));
	SetKeyEntry(43, tr("Show Grid"), Ras, 0);
	uRas = viewMenu->insertItem( tr("Snap to Grid"), this, SLOT(ToggleURaster()));
	SetKeyEntry(44, tr("Snap to Grid"), uRas, 0);
	Guide = viewMenu->insertItem( tr("Hide Guides"), this, SLOT(ToggleGuides()));
	uGuide = viewMenu->insertItem( tr("Snap to Guides"), this, SLOT(ToggleUGuides()));
	for (a=0; a<6; ++a)
		{
		viewMenu->setItemEnabled(viewMenu->idAt(a), 0);
		}
	viewMenu->setItemEnabled(Markers, 0);
	viewMenu->setItemEnabled(FrameDr, 0);
	viewMenu->setItemEnabled(Bilder, 0);
	viewMenu->setItemEnabled(Ras, 0);
	viewMenu->setItemEnabled(uRas, 0);
	viewMenu->setItemEnabled(Guide, 0);
	viewMenu->setItemEnabled(uGuide, 0);
	toolMenu=new QPopupMenu();
	viewTools = toolMenu->insertItem( tr("Tools"), this, SLOT(ToggleTools()));
	SetKeyEntry(45, tr("Tools"), viewTools, 0);
	viewToolsP = toolMenu->insertItem( tr("PDF-Tools"), this, SLOT(TogglePDFTools()));
	viewMpal = toolMenu->insertItem( tr("Properties"), this, SLOT(ToggleMpal()));
	SetKeyEntry(46, tr("Properties"), viewMpal, 0);
	viewTpal = toolMenu->insertItem( tr("Outline"), this, SLOT(ToggleTpal()));
	SetKeyEntry(47, tr("Outline"), viewTpal, 0);
	viewBpal = toolMenu->insertItem( tr("Scrapbook"), this, SLOT(ToggleBpal()));
	SetKeyEntry(48, tr("Scrapbook"), viewBpal, 0);
	viewLpal = toolMenu->insertItem( tr("Layers"), this, SLOT(ToggleLpal()));
	viewSepal = toolMenu->insertItem( tr("Page Palette"), this, SLOT(ToggleSepal()));
	viewBopal = toolMenu->insertItem( tr("Bookmarks"), this, SLOT(ToggleBookpal()));
	extraMenu=new QPopupMenu();
	MenID = extraMenu->insertItem( tr("Manage Pictures"), this, SLOT(StatusPic()));
	SetKeyEntry(51, tr("Manage Pictures"), MenID, 0);
	hyph = extraMenu->insertItem( tr("Hyphenate Text"), this, SLOT(doHyphenate()));
	extraMenu->setItemEnabled(hyph, 0);
	SetKeyEntry(50, tr("Hyphenate Text"), hyph, 0);
	windowsMenu = new QPopupMenu();
	windowsMenu->setCheckable( true );
	connect(windowsMenu, SIGNAL(aboutToShow()), this, SLOT(windowsMenuAboutToShow()));
	helpMenu=new QPopupMenu();
	MenID = helpMenu->insertItem( tr("About Scribus"), this, SLOT(slotHelpAbout()));
	SetKeyEntry(52, tr("About Scribus"), MenID, 0);
	MenID = helpMenu->insertItem( tr("About Qt"), this, SLOT(slotHelpAboutQt()));
	SetKeyEntry(53, tr("About Qt"), MenID, 0);
	helpMenu->insertSeparator();
	MenID = helpMenu->insertItem( tr("Online-Help..."), this, SLOT(slotOnlineHelp()));
	SetKeyEntry(54, tr("Online-Help..."), MenID, 0);
	tip = helpMenu->insertItem( tr("Tool-Tips"), this, SLOT(ToggleTips()));
	SetKeyEntry(55, tr("Tool-Tips"), tip, 0);
  tipsOn = true;
  helpMenu->setItemChecked(tip, tipsOn);
//	editMenu->insertItem( tr("Test"), this, SLOT(slotTest()));
//	helpMenu->insertItem( tr("Test2"), this, SLOT(slotTest2()));
	menuBar()->insertItem( tr("File"), fileMenu);
	menuBar()->insertItem( tr("Edit"), editMenu);
	Stm = menuBar()->insertItem( tr("Style"), StilMenu);
	Obm = menuBar()->insertItem( tr("Item"), ObjMenu);
	pgmm = menuBar()->insertItem( tr("Page"), pageMenu);
	menuBar()->setItemEnabled(Stm, 0);
	menuBar()->setItemEnabled(Obm, 0);
	menuBar()->setItemEnabled(pgmm, 0);
	menuBar()->insertItem( tr("View"), viewMenu);
	menuBar()->insertItem( tr("Tools"), toolMenu);
	exmn = menuBar()->insertItem( tr("Extras"), extraMenu);
	menuBar()->setItemEnabled(exmn, 0);
	menuBar()->insertItem( tr("Windows"), windowsMenu );
	menuBar()->insertSeparator();
	menuBar()->insertItem( tr("Help"), helpMenu);
	AliMenu = new QPopupMenu();
	AliMenu->insertItem( tr("Left"));
	AliMenu->insertItem( tr("Center"));
	AliMenu->insertItem( tr("Right"));
	AliMenu->insertItem( tr("Block"));
	AliMenu->insertItem( tr("Forced"));
	ColorMenu = new QPopupMenu();
	ColorMenC = new QComboBox(false);
	ColorMenC->setEditable(false);
	ColorMenu->insertItem(ColorMenC);
	SizeTMenu = new QPopupMenu();
	SizeTMenu->insertItem( tr("Other..."));
	SizeTMenu->insertItem(" 7 pt");
	SizeTMenu->insertItem(" 9 pt");
	SizeTMenu->insertItem("10 pt");
	SizeTMenu->insertItem("12 pt");
	SizeTMenu->insertItem("14 pt");
	SizeTMenu->insertItem("18 pt");
	SizeTMenu->insertItem("24 pt");
	SizeTMenu->insertItem("36 pt");
	SizeTMenu->insertItem("48 pt");
	SizeTMenu->insertItem("60 pt");
	SizeTMenu->insertItem("72 pt");
	ShadeMenu = new QPopupMenu();
	ShadeMenu->insertItem( tr("Other..."));
	ShadeMenu->insertItem("0 %");
	ShadeMenu->insertItem("10 %");
	ShadeMenu->insertItem("20 %");
	ShadeMenu->insertItem("30 %");
	ShadeMenu->insertItem("40 %");
	ShadeMenu->insertItem("50 %");
	ShadeMenu->insertItem("60 %");
	ShadeMenu->insertItem("70 %");
	ShadeMenu->insertItem("80 %");
	ShadeMenu->insertItem("90 %");
	ShadeMenu->insertItem("100 %");
	FontMenu = new QPopupMenu();
	TypeStyleMenu = new QPopupMenu();
	TypeStyleMenu->insertItem( tr("Normal"));
	tmp = qApp->font();
	tmp = qApp->font();
	tmp.setUnderline(true);
	TypeStyleMenu->insertItem(new FmItem( tr("Underline"), tmp));
	tmp = qApp->font();
	tmp.setStrikeOut(true);
	TypeStyleMenu->insertItem(new FmItem( tr("Strikethru"), tmp));
	TypeStyleMenu->insertItem( tr("Small Caps"));
	TypeStyleMenu->insertItem( tr("Superscript"));
	TypeStyleMenu->insertItem( tr("Subscript"));
	TypeStyleMenu->insertItem( tr("Outlined"));
}

void ScribusApp::initStatusBar()
{
	FMess = new QLabel(statusBar(), "ft");
	FMess->setText("           ");
	statusBar()->addWidget(FMess, 3, true);
	FProg = new QProgressBar(statusBar(), "p");
  FProg->setCenterIndicator(true);
	FProg->setFixedWidth( 100 );
	statusBar()->addWidget(FProg, 0, true);
	FProg->reset();
	XMess = new QLabel(statusBar(), "xt");
	XMess->setText( tr("X-Pos:"));
	statusBar()->addWidget(XMess, 0, true);
	XDat = new QLabel(statusBar(), "dt");
	statusBar()->addWidget(XDat, 1, true);
	XDat->setText("         ");
	YMess = new QLabel(statusBar(), "yt");
	YMess->setText( tr("Y-Pos:"));
	statusBar()->addWidget(YMess, 0, true);
	YDat = new QLabel(statusBar(), "ydt");
	statusBar()->addWidget(YDat, 1, true);
	YDat->setText("         ");
}

void ScribusApp::ReportMP(double xp, double yp)
{
	QString tmp, tmp2;
	int multiplier, precision;
	double divisor;
	switch (doc->Einheit)
		{
		case 0:
			tmp2 = " pt";
			multiplier = 100;
			divisor = 100.0;
			precision = 2;
			break;
		case 1:
			tmp2 = " mm";
			multiplier = 1000;
			divisor = 1000.0;
			precision = 3;
			break;
		case 2:
			tmp2 = " in";
			multiplier = 10000;
			divisor = 10000.0;
			precision = 4;
			break;
		case 3:
			tmp2 = " p";
			multiplier = 100;
			divisor = 100.0;
			precision = 2;
			break;
		}
	XDat->setText(tmp.setNum(qRound(xp*UmReFaktor * multiplier) / divisor, 'f', precision)+tmp2);
	YDat->setText(tmp.setNum(qRound(yp*UmReFaktor * multiplier) / divisor, 'f', precision)+tmp2);
}

void ScribusApp::SetKeyEntry(int Nr, QString text, int Men, int KeyC)
{
	Keys ke;
	ke.Name = text;
	ke.MenuID = Men;
	ke.KeyID = KeyC;
	Prefs.KeyActions.insert(Nr, ke);
}

void ScribusApp::DeleteSel(PageItem *b)
{
	Pti *it;
 	for (it = b->Ptext.first(); it != 0; it = b->Ptext.next())
 		{
 		if (it->cselect)
 			{
 			b->Ptext.remove();
 			it = b->Ptext.prev();
 			if (it == 0)
 				{
 				it = b->Ptext.first();
 				}
 			}
 		}
	if (b->Ptext.count() != 0)
		{
 		if (b->Ptext.first()->cselect)
 			{
 			b->Ptext.remove();
			b->CPos = 0;
 			}
		else
 			b->CPos = QMIN(b->CPos, doc->ActPage->oldCp);
		}
	else
		b->CPos = 0;
 	b->HasSel = false;
 	DisableTxEdit();
}

void ScribusApp::setTBvals(PageItem *b)
{
	if (b->Ptext.count() != 0)
		{
 		doc->CurrentStyle = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cstyle & 127;
 		doc->CurrentABStil = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cab;
 		setAbsValue(doc->CurrentABStil);
 		Mpal->setAli(doc->CurrentABStil);
 		doc->CurrFont = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cfont;
 		doc->CurrFontSize = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->csize;
		doc->CurrTextFill = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->ccolor;
		doc->CurrTextFillSh = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cshade;
		doc->CurrTextStroke = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cstroke;
		doc->CurrTextStrokeSh = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cshade2;
		doc->CurrTextScale = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cscale;
		emit TextFarben(doc->CurrTextStroke, doc->CurrTextFill, doc->CurrTextStrokeSh, doc->CurrTextFillSh);
		emit TextIFont(doc->CurrFont);
 		emit TextISize(doc->CurrFontSize);
 		emit TextUSval(b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cextra);
 		emit TextStil(doc->CurrentStyle);
		emit TextScale(doc->CurrTextScale);
 		}
}

void ScribusApp::wheelEvent(QWheelEvent *w)
{
	if (HaveDoc)
		{
		if (w->delta() < 0)
			view->scrollBy(0, Prefs.Wheelval);
		else
			view->scrollBy(0, -Prefs.Wheelval);
		w->accept();
		}
}

void ScribusApp::keyPressEvent(QKeyEvent *k)
{
	QWidgetList windows;
	QWidget* w;
	struct Pti *hg;
	int kk = k->key();
	int as = k->ascii();
	double altx, alty;
	QString uc = k->text();
	QString cr, Tcha, Twort;
	uint Tcoun;
	if (keyrep)
		return;
	keyrep = true;
	switch (k->state())
		{
		case ShiftButton:
			KeyMod = 0x00200000;
			break;
		case AltButton:
			KeyMod = 0x00800000;
			break;
		case ControlButton:
			KeyMod = 0x00400000;
			break;
		default:
			KeyMod = 0;
			break;
		}
 	if ((HaveDoc) && (!view->LE->hasFocus()))
 		{
		if (doc->AppMode != 7)
			{
	 		switch (kk)
	 			{
	 			case Key_Prior:
	 				view->scrollBy(0, -Prefs.Wheelval);
					keyrep = false;
	 				return;
	 				break;
	 			case Key_Next:
	 				view->scrollBy(0, Prefs.Wheelval);
					keyrep = false;
	 				return;
	 				break;
				case Key_Tab:
					keyrep = false;
					windows = wsp->windowList();
					if (windows.count() > 1)
						{
						for (int i = 0; i < static_cast<int>(windows.count()); ++i)
							{
							if (wsp->activeWindow() == windows.at(i))
								{
								if (i == static_cast<int>(windows.count()-1))
									w = windows.at(0);
								else
									w = windows.at(i+1);
								break;
								}
							}
						doc->OpenNodes = Tpal->buildReopenVals();
						if ( w )
							w->showNormal();
						newActWin(w);
						}
	 				return;
	 				break;
				}
 			}
 		if (doc->ActPage->SelItem.count() != 0)
 			{
 			PageItem *b = doc->ActPage->SelItem.at(0);
 			switch (doc->AppMode)
 				{
 				case 1:
 					switch (kk)
 						{
 						case Key_Delete:
 							if (!doc->EditClip)
								{
								if (!b->Locked)
 									doc->ActPage->DeleteItem();
								}
 							break;
 						case Key_Left:
							if (!k->isAutoRepeat())
								{
								doc->ActPage->storeUndoInf(b);
								doc->UnData.UnCode = 1;
								doc->UnDoValid = true;
								CanUndo();
								}
							if (!b->Locked)
 								doc->ActPage->moveGroup(-1, 0);
 							break;
 						case Key_Right:
							if (!k->isAutoRepeat())
								{
								doc->ActPage->storeUndoInf(b);
								doc->UnData.UnCode = 1;
								doc->UnDoValid = true;
								CanUndo();
								}
							if (!b->Locked)
 								doc->ActPage->moveGroup(1, 0);
 							break;
 						case Key_Up:
							if (!k->isAutoRepeat())
								{
								doc->ActPage->storeUndoInf(b);
								doc->UnData.UnCode = 1;
								doc->UnDoValid = true;
								CanUndo();
								}
							if (!b->Locked)
 								doc->ActPage->moveGroup(0, -1);
 							break;
 						case Key_Down:
							if (!k->isAutoRepeat())
								{
								doc->ActPage->storeUndoInf(b);
								doc->UnData.UnCode = 1;
								doc->UnDoValid = true;
								CanUndo();
								}
							if (!b->Locked)
 								doc->ActPage->moveGroup(0, 1);
 						default:
 							if (b->PType == 4)
 								{
 								if ((kk + KeyMod) == Prefs.KeyActions[59].KeyID)
 									{
									setNewAbStyle(1);
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									}
 								if ((kk + KeyMod) == Prefs.KeyActions[58].KeyID)
 									{
									setNewAbStyle(2);
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									}
 								if ((kk + KeyMod) == Prefs.KeyActions[57].KeyID)
 									{
									setNewAbStyle(0);
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									}
 								}
 							break;
 						}
 					slotDocCh();
 					break;
 				case 7:
 					if (b->PType == 4)
 						{
 						doc->ActPage->slotDoCurs(false);
 						switch (kk)
 							{
 							case Key_Down:
 								if (b->CPos != static_cast<int>(b->Ptext.count()))
 									{
 									alty = b->Ptext.at(b->CPos)->yp;
 									altx = b->Ptext.at(b->CPos)->xp;
 									do
 										{
 										b->CPos += 1;
 										if (b->CPos == static_cast<int>(b->Ptext.count()))
 											break;
 										if (b->Ptext.at(b->CPos)->yp > alty)
 											{
 											if (b->Ptext.at(b->CPos)->xp >= altx)
 												break;
 											}
 										}
 									while (b->CPos < static_cast<int>(b->Ptext.count()));
 									if (b->CPos == static_cast<int>(b->Ptext.count()))
 										if (b->NextBox != 0)
 											{
 											if (b->NextBox->Ptext.count() != 0)
 												{
												b->OwnPage->Deselect(true);
												b->NextBox->CPos = 0;
												doc->ActPage = b->NextBox->OwnPage;
												b->NextBox->OwnPage->SelectItemNr(b->NextBox->ItemNr);
												b = b->NextBox;
												}
 											}
 									}
 								else
 									{
 									if (b->NextBox != 0)
 										{
 										if (b->NextBox->Ptext.count() != 0)
 											{
											b->OwnPage->Deselect(true);
											b->NextBox->CPos = 0;
											doc->ActPage = b->NextBox->OwnPage;
											b->NextBox->OwnPage->SelectItemNr(b->NextBox->ItemNr);
											b = b->NextBox;
											}
 										}
 									}
 								setTBvals(b);
 								break;
 							case Key_Up:
 								if (b->CPos > 0)
 									{
 									if (b->CPos == static_cast<int>(b->Ptext.count()))
 										b->CPos -= 1;
 									alty = b->Ptext.at(b->CPos)->yp;
 									altx = b->Ptext.at(b->CPos)->xp;
									if (b->CPos > 0)
										{
 										do
 											{
 											b->CPos -= 1;
 											if (b->CPos == 0)
 												break;
 											if (b->Ptext.at(b->CPos)->yp < alty)
 												{
 												if (b->Ptext.at(b->CPos)->xp <= altx)
 													break;
 												}
 											}
 										while (b->CPos > 0);
										}
 									if (b->CPos == 0)
 										{
 										if (b->BackBox != 0)
 											{
											b->OwnPage->Deselect(true);
											b->BackBox->CPos = b->BackBox->Ptext.count();
											doc->ActPage = b->BackBox->OwnPage;
											b->BackBox->OwnPage->SelectItemNr(b->BackBox->ItemNr);
											b = b->BackBox;
 											}
 										}
 									}
 								else
 									{
 									b->CPos = 0;
 									if (b->BackBox != 0)
 										{
										b->OwnPage->Deselect(true);
										b->BackBox->CPos = b->BackBox->Ptext.count();
										doc->ActPage = b->BackBox->OwnPage;
										b->BackBox->OwnPage->SelectItemNr(b->BackBox->ItemNr);
										b = b->BackBox;
 										}
 									}
 								setTBvals(b);
 								break;
							case Key_Home:
 								b->CPos = 0;
 								setTBvals(b);
 								break;
							case Key_End:
 								b->CPos = static_cast<int>(b->Ptext.count());
 								setTBvals(b);
 								break;
 							case Key_Left:
 								b->CPos -= 1;
 								if (b->CPos < 0)
 									{
 									b->CPos = 0;
 									if (b->BackBox != 0)
 										{
										b->OwnPage->Deselect(true);
										b->BackBox->CPos = b->BackBox->Ptext.count();
										doc->ActPage = b->BackBox->OwnPage;
										b->BackBox->OwnPage->SelectItemNr(b->BackBox->ItemNr);
										b = b->BackBox;
 										}
 									}
 								setTBvals(b);
 								break;
 							case Key_Right:
 								b->CPos += 1;
 								if (b->CPos > static_cast<int>(b->Ptext.count()))
 									{
 									b->CPos -= 1;
 									if (b->NextBox != 0)
 										{
 										if (b->NextBox->Ptext.count() != 0)
 											{
											b->OwnPage->Deselect(true);
											b->NextBox->CPos = 0;
											doc->ActPage = b->NextBox->OwnPage;
											b->NextBox->OwnPage->SelectItemNr(b->NextBox->ItemNr);
											b = b->NextBox;
											}
 										}
 									}
 								setTBvals(b);
 								break;
 							case Key_Delete:
 								if (b->CPos == static_cast<int>(b->Ptext.count()))
									{
									keyrep = false;
									return;
									}
 								if (b->Ptext.count() == 0)
									{
									keyrep = false;
									return;
									}
 								cr = b->Ptext.at(b->CPos)->ch;
 								if (b->HasSel)
 									DeleteSel(b);
 								else
 									b->Ptext.remove(b->CPos);
 								b->Tinput = false;
 								if ((cr == QChar(13)) && (b->Ptext.count() != 0))
 									{
 									doc->ActPage->chAbStyle(b, b->Ptext.at(QMAX(b->CPos-1,0))->cab);
 									b->Tinput = false;
 									}
 								setTBvals(b);
 								b->Dirty = true;
								doc->ActPage->RefreshItem(b);
 								break;
 							case Key_Backspace:
 								if (b->CPos == 0)
									{
									keyrep = false;
 									return;
									}
 								if (b->Ptext.count() == 0)
									{
									keyrep = false;
									return;
									}
 								cr = b->Ptext.at(QMAX(b->CPos-1,0))->ch;
 								if (b->HasSel)
 									DeleteSel(b);
 								else
 									b->CPos -= 1;
 									b->Ptext.remove(b->CPos);
 								b->Tinput = false;
 								if ((cr == QChar(13)) && (b->Ptext.count() != 0))
 									{
 									doc->ActPage->chAbStyle(b, b->Ptext.at(QMAX(b->CPos-1,0))->cab);
 									b->Tinput = false;
 									}
 								setTBvals(b);
 								b->Dirty = true;
								doc->ActPage->RefreshItem(b);
 								break;
 							default:
 								if ((b->HasSel) && (kk < 0x1000))
 									{
 									DeleteSel(b);
 									b->Dirty = true;
									doc->ActPage->RefreshItem(b);
 									}
 								if ((kk == Key_Tab) || ((kk + KeyMod) == Prefs.KeyActions[60].KeyID) || ((kk + KeyMod) == Prefs.KeyActions[67].KeyID))
 									{
 									hg = new Pti;
									if ((kk + KeyMod) == Prefs.KeyActions[60].KeyID)
 										hg->ch = QString(QChar(30));
									else if (kk == Key_Tab)
										hg->ch = QString(QChar(9));
									else
 										hg->ch = QString(QChar(29));
 									hg->cfont = doc->CurrFont;
 									hg->csize = doc->CurrFontSize;
									hg->ccolor = doc->CurrTextFill;
									hg->cshade = doc->CurrTextFillSh;
									hg->cstroke = doc->CurrTextStroke;
									hg->cshade2 = doc->CurrTextStrokeSh;
									hg->cscale = doc->CurrTextScale;
 									hg->cselect = false;
 									hg->cstyle = doc->CurrentStyle;
 									hg->cab = doc->CurrentABStil;
									if (doc->Vorlagen[doc->CurrentABStil].Font != "")
										{
										hg->cfont = doc->Vorlagen[doc->CurrentABStil].Font;
										hg->csize = doc->Vorlagen[doc->CurrentABStil].FontSize;
										}
 									hg->cextra = 0;
 									hg->xp = 0;
 									hg->yp = 0;
									hg->PRot = 0;
									hg->PtransX = 0;
									hg->PtransY = 0;
 									b->Ptext.insert(b->CPos, hg);
 									b->CPos += 1;
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									break;
 									}
 								if ((kk + KeyMod) == Prefs.KeyActions[56].KeyID)
 									{
 									b->Ptext.at(QMAX(b->CPos-1,0))->cstyle ^= 128;
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									break;
 									}
 								if ((kk + KeyMod) == Prefs.KeyActions[59].KeyID)
 									{
									setNewAbStyle(1);
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									break;
 									}
 								if ((kk + KeyMod) == Prefs.KeyActions[57].KeyID)
 									{
									setNewAbStyle(0);
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									break;
 									}
 								if ((kk + KeyMod) == Prefs.KeyActions[58].KeyID)
 									{
									setNewAbStyle(2);
 									b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b);
 									break;
 									}
								if (((uc[0] > QChar(31)) || (as == 13) || (as == 30)) && ((*doc->AllFonts)[doc->CurrFont]->CharWidth.contains(uc[0].unicode())))
 									{
 									hg = new Pti;
 									hg->ch = uc;
 									hg->cfont = doc->CurrFont;
									hg->ccolor = doc->CurrTextFill;
									hg->cshade = doc->CurrTextFillSh;
									hg->cstroke = doc->CurrTextStroke;
									hg->cshade2 = doc->CurrTextStrokeSh;
									hg->cscale = doc->CurrTextScale;
 									hg->csize = doc->CurrFontSize;
 									hg->cextra = 0;
 									hg->cselect = false;
 									hg->cstyle = doc->CurrentStyle;
 									hg->cab = doc->CurrentABStil;
									if (doc->Vorlagen[doc->CurrentABStil].Font != "")
										{
										hg->cfont = doc->Vorlagen[doc->CurrentABStil].Font;
										hg->csize = doc->Vorlagen[doc->CurrentABStil].FontSize;
										}
 									hg->xp = 0;
 									hg->yp = 0;
									hg->PRot = 0;
									hg->PtransX = 0;
									hg->PtransY = 0;
 									b->Ptext.insert(b->CPos, hg);
 									b->CPos += 1;
									if ((doc->Trenner->AutoCheck) && (b->CPos > 1))
										{
										Twort = "";
										Tcoun = 0;
										for (int hych = b->CPos-1; hych > -1; hych--)
											{
											Tcha = b->Ptext.at(hych)->ch;
											if (Tcha == " ")
												{
												Tcoun = hych+1;
												break;
												}
											Twort.prepend(Tcha);
											}
										if (Twort != "")
											{
											if (doc->Trenner->Language != b->Language)
												doc->Trenner->slotNewDict(b->Language);
											doc->Trenner->slotHyphenateWord(b, Twort, Tcoun);
 											b->Dirty = true;
											}
										}
 									if ((b->CPos < static_cast<int>(b->Ptext.count())) || (as == 30))
 										b->Dirty = true;
 									b->Tinput = true;
									doc->ActPage->RefreshItem(b, true);
 									}
 								break;
 							}
 						if (b->Ptext.count() != 0)
 							if (b->Ptext.at(QMAX(b->CPos-1, 0))->yp != 0)
 								doc->ActPage->slotDoCurs(true);
 						if ((kk == Key_Left) || (kk == Key_Right) || (kk == Key_Up) || (kk == Key_Down))
							{
							keyrep = false;
 							return;
							}
 						}
 					slotDocCh(false);
 					break;
 				}
 			}
 		}
	keyrep = false;
}

void ScribusApp::closeEvent(QCloseEvent *ce)
{
	QWidgetList windows = wsp->windowList();
	ScribusWin* tw;
	if (!windows.isEmpty())
		{
		singleClose = true;
		for ( int i = 0; i < static_cast<int>(windows.count()); ++i )
			{
			newActWin(windows.at(i));
	 		tw = ActWin;
			ActWin->close();
			if (tw == ActWin)
				{
				ce->ignore();
				singleClose = false;
				return;
				}
			}
		SavePrefs();
		if ((Prefs.SaveAtQ) && (ScBook->Changed == true))
			{
			if (ScBook->ScFilename.isEmpty())
				ScBook->ScFilename = PrefsPfad+"/scrap.scs";
			ScBook->Save();
			}
		if (ScBook->BibWin->Objekte.count() == 0)
			system("rm -f " + PrefsPfad+"/scrap.scs");
		Prefs.AvailFonts.~SCFonts();
		FinalizePlugs();
		exit(0);
		}
	else
		{
		SavePrefs();
		if ((Prefs.SaveAtQ) && (ScBook->Changed == true))
			{
			if (ScBook->ScFilename.isEmpty())
				ScBook->ScFilename = PrefsPfad+"/scrap.scs";
			ScBook->Save();
			}
		if (ScBook->BibWin->Objekte.count() == 0)
			system("rm -f " + PrefsPfad+"/scrap.scs");
		qApp->setOverrideCursor(QCursor(ArrowCursor), true);
		Prefs.AvailFonts.~SCFonts();
		FinalizePlugs();
		exit(0);
		}
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////
double ScribusApp::mm2pts(int mm)
{
	return mm / 25.4 * 72;
}

double ScribusApp::pts2mm(double pts)
{
	return pts / 72 * 25.4;
}

bool ScribusApp::slotFileNew()
{
	double b, h, tpr, lr, rr, br, sp, ab;
	bool fp, atf, ret;
	NewDoc* dia = new NewDoc(this, &Prefs);
	if (dia->exec())
		{
		tpr = dia->Top;
		lr = dia->Left;
		rr = dia->Right;
		br = dia->Bottom;
		ab = dia->Dist;
		b = dia->Pagebr;
		h = dia->Pageho;
		sp = dia->SpinBox10->value();
		atf = dia->AutoFrame->isChecked();
		fp = dia->Doppelseiten->isChecked();
		if (dia->ComboBox3->currentItem() == 1)
			{
			b = mm2pts(qRound(pts2mm(dia->Pagebr)));
			h = mm2pts(qRound(pts2mm(dia->Pageho)));
			}
		ret = doFileNew(b, h, tpr, lr, rr, br, ab, sp, atf, fp, dia->ComboBox3->currentItem(),
										dia->ErsteSeite->isChecked(), dia->Orient, dia->PgNr->value());
  	FMess->setText( tr("Ready"));
		}
	else
		ret = false;
	delete dia;
	return ret;
}

bool ScribusApp::doFileNew(double b, double h, double tpr, double lr, double rr, double br, double ab, double sp,
													 bool atf, bool fp, int einh, bool firstleft, int Ori, int SNr)
{
	QString cc;
	if (HaveDoc)
		doc->OpenNodes = Tpal->buildReopenVals();
	doc = new ScribusDoc();
	doc->Einheit = einh;
	if (fp)
		doc->FirstPageLeft = firstleft;
	doc->PageOri = Ori;
	doc->FirstPnum = SNr;
	doc->AllFonts = &Prefs.AvailFonts;
	doc->AddFont(Prefs.DefFont, Prefs.AvailFonts[Prefs.DefFont]->Font);
	doc->Dfont = Prefs.DefFont;
	doc->Dsize = Prefs.DefSize;
	doc->GrabRad = Prefs.GrabRad;
	doc->GuideRad = Prefs.GuideRad;
	doc->minorGrid = Prefs.DminGrid;
	doc->majorGrid = Prefs.DmajGrid;
	doc->minorColor = Prefs.DminColor;
	doc->majorColor = Prefs.DmajColor;
	doc->papColor = Prefs.DpapColor;
	doc->margColor = Prefs.DmargColor;
	doc->guideColor = Prefs.guideColor;
	doc->VHoch = Prefs.DVHoch;
	doc->VHochSc = Prefs.DVHochSc;
	doc->VTief = Prefs.DVTief;
	doc->VTiefSc = Prefs.DVTiefSc;
	doc->VKapit = Prefs.DVKapit;
 	doc->Dpen = Prefs.Dpen;
 	doc->DpenText = Prefs.DpenText;
 	doc->Dbrush = Prefs.Dbrush;
 	doc->Dshade = Prefs.Dshade;
 	doc->Dshade2 = Prefs.Dshade2;
	doc->DCols = Prefs.DCols;
	doc->DGap = Prefs.DGap;
 	doc->DLineArt = PenStyle(Prefs.DLineArt);
 	doc->Dwidth = Prefs.Dwidth;
 	doc->DpenLine = Prefs.DpenLine;
 	doc->DshadeLine = Prefs.DshadeLine;
 	doc->DLstyleLine = PenStyle(Prefs.DLstyleLine);
 	doc->DwidthLine = Prefs.DwidthLine;
 	doc->MagMin = Prefs.MagMin;
 	doc->MagMax = Prefs.MagMax;
 	doc->MagStep = Prefs.MagStep;
 	doc->DbrushPict = Prefs.DbrushPict;
	doc->ShadePict = Prefs.ShadePict;
	doc->ScaleX = Prefs.ScaleX;
	doc->ScaleY = Prefs.ScaleY;
	doc->ScaleType = Prefs.ScaleType;
	doc->AspectRatio = Prefs.AspectRatio;
	doc->Before = Prefs.Before;
	doc->PagesSbS = Prefs.PagesSbS;
	doc->ShFrames = Prefs.ShFrames;
	doc->RandFarbig = Prefs.RandFarbig;
	doc->AutoLine = Prefs.AutoLine;
	doc->DocName = doc->DocName+cc.setNum(DocNr);
	doc->HasCMS = true;
	doc->CMSSettings.DefaultInputProfile = Prefs.DCMSset.DefaultInputProfile;
	doc->CMSSettings.DefaultInputProfile2 = Prefs.DCMSset.DefaultInputProfile2;
	doc->CMSSettings.DefaultMonitorProfile = Prefs.DCMSset.DefaultMonitorProfile;
	doc->CMSSettings.DefaultPrinterProfile = Prefs.DCMSset.DefaultPrinterProfile;
	doc->CMSSettings.DefaultIntentPrinter = Prefs.DCMSset.DefaultIntentPrinter;
	doc->CMSSettings.DefaultIntentMonitor = Prefs.DCMSset.DefaultIntentMonitor;
	doc->CMSSettings.DefaultIntentMonitor2 = Prefs.DCMSset.DefaultIntentMonitor2;
	doc->CMSSettings.SoftProofOn = Prefs.DCMSset.SoftProofOn;
	doc->CMSSettings.GamutCheck = Prefs.DCMSset.GamutCheck;
	doc->CMSSettings.BlackPoint = Prefs.DCMSset.BlackPoint;
	doc->CMSSettings.CMSinUse = Prefs.DCMSset.CMSinUse;
	doc->PDF_Optionen.SolidProf = doc->CMSSettings.DefaultInputProfile2;
	doc->PDF_Optionen.ImageProf = doc->CMSSettings.DefaultInputProfile;
	doc->PDF_Optionen.PrintProf = doc->CMSSettings.DefaultPrinterProfile;
	doc->PDF_Optionen.Intent = doc->CMSSettings.DefaultIntentMonitor;
	doc->PDF_Optionen.Intent2 = doc->CMSSettings.DefaultIntentMonitor2;
	doc->ActiveLayer = 0;
	HaveDoc++;
	DocNr++;
	doc->Scale = 1.0*Prefs.DisScale;
	doc->AppMode = 1;
	doc->Language = Prefs.Language;
	doc->MinWordLen = Prefs.MinWordLen;
	doc->Automatic = Prefs.Automatic;
	doc->AutoCheck = Prefs.AutoCheck;
	doc->PageColors = Prefs.DColors;
	doc->loading = true;
	ScribusWin* w = new ScribusWin(wsp, doc);
	view = new ScribusView(w, doc, &Prefs);
	w->setView(view);
	ActWin = w;
	doc->WinHan = w;
	w->setCentralWidget(view);
	connect(w, SIGNAL(Schliessen()), this, SLOT(DoFileClose()));
	connect(w, SIGNAL(SaveAndClose()), this, SLOT(DoSaveClose()));
	if (CMSavail)
		{
#ifdef HAVE_CMS
		w->SoftProofing = Prefs.DCMSset.SoftProofOn;
		w->Gamut = Prefs.DCMSset.GamutCheck;
		CMSuse = Prefs.DCMSset.CMSinUse;
		w->IntentPrinter = Prefs.DCMSset.DefaultIntentPrinter;
		w->IntentMonitor = Prefs.DCMSset.DefaultIntentMonitor;
		SoftProofing = Prefs.DCMSset.SoftProofOn;
		Gamut = Prefs.DCMSset.GamutCheck;
		IntentPrinter = Prefs.DCMSset.DefaultIntentPrinter;
		IntentMonitor = Prefs.DCMSset.DefaultIntentMonitor;
		w->OpenCMSProfiles(InputProfiles, MonitorProfiles, PrinterProfiles);
		stdProof = w->stdProof;
		stdTrans = w->stdTrans;
		stdProofImg = w->stdProofImg;
		stdTransImg = w->stdTransImg;
		CMSoutputProf = doc->DocOutputProf;
		CMSprinterProf = doc->DocPrinterProf;
		if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigRgbData)
			doc->CMSSettings.ComponentsInput2 = 3;
		if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigCmykData)
			doc->CMSSettings.ComponentsInput2 = 4;
		if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigCmyData)
			doc->CMSSettings.ComponentsInput2 = 3;
		if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigRgbData)
			doc->CMSSettings.ComponentsPrinter = 3;
		if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigCmykData)
			doc->CMSSettings.ComponentsPrinter = 4;
		if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigCmyData)
			doc->CMSSettings.ComponentsPrinter = 3;
		doc->PDF_Optionen.SComp = doc->CMSSettings.ComponentsInput2;
#endif
		if (Prefs.DCMSset.CMSinUse)
			RecalcColors();
		}
	doc->setPage(b, h, tpr, lr, rr, br, sp, ab, atf, fp);
	doc->loading = false;
	slotNewPage(0);
	doc->loading = true;
	HaveNewDoc();
	view->Pages.at(0)->parentWidget()->hide();
	view->DocPages = view->Pages;
	view->Pages = view->MasterPages;
	doc->PageC = view->MasterPages.count();
	bool atfb = doc->PageAT;
	doc->PageAT = false;
	slotNewPage(0);
	doc->PageAT = atfb;
	view->MasterNames["Normal"] = 0;
	view->Pages.at(0)->PageNam = "Normal";
	view->Pages.at(0)->parentWidget()->hide();
	view->MasterPages = view->Pages;
	doc->PageC = view->DocPages.count();
	view->Pages = view->DocPages;
	doc->MasterP = false;
	view->Pages.at(0)->MPageNam = "Normal";
	view->Pages.at(0)->parentWidget()->show();
	doc->setUnModified();
	doc->loading = false;
	doc->ActPage = view->Pages.at(0);
	doc->OpenNodes.clear();
	Tpal->BuildTree(view);
	Sepal->Rebuild();
	BookPal->BView->clear();
	if ( wsp->windowList().isEmpty() )
		w->showMaximized();
	else
		w->show();
	view->show();
	connect(doc->ASaveTimer, SIGNAL(timeout()), w, SLOT(slotAutoSave()));
	connect(w, SIGNAL(AutoSaved()), this, SLOT(slotAutoSaved()));
	doc->AutoSave = Prefs.AutoSave;
	if (doc->AutoSave)
		doc->ASaveTimer->start(Prefs.AutoSaveTime);
	DatSav->setEnabled(false);
	fileMenu->setItemEnabled(fid4, 0);
	return true;
}

void ScribusApp::DoSaveClose()
{
	slotFileSaveAs();
	DoFileClose();
}

void ScribusApp::windowsMenuAboutToShow()
{
	windowsMenu->clear();
	int cascadeId = windowsMenu->insertItem( tr("Cascade"), wsp, SLOT(cascade() ) );
	int tileId = windowsMenu->insertItem( tr("Tile"), wsp, SLOT(tile() ) );
	if ( wsp->windowList().isEmpty() )
		{
		windowsMenu->setItemEnabled( cascadeId, false );
		windowsMenu->setItemEnabled( tileId, false );
		}
	windowsMenu->insertSeparator();
	QWidgetList windows = wsp->windowList();
	for ( int i = 0; i < static_cast<int>(windows.count()); ++i )
		{
		int id = windowsMenu->insertItem(windows.at(i)->caption(), this, SLOT(windowsMenuActivated(int)));
		windowsMenu->setItemParameter( id, i );
		windowsMenu->setItemChecked( id, wsp->activeWindow() == windows.at(i) );
		}
}

void ScribusApp::newActWin(QWidget *w)
{
	ScribusWin* swin;
	if (w == NULL)
		{
		ActWin = NULL;
		return;
		}
	ActWin = (ScribusWin*)w;
	if (doc != NULL)
		{
		if ((HaveDoc) && (doc != ActWin->doc))
			doc->OpenNodes = Tpal->buildReopenVals();
		}
	doc = ActWin->doc;
	view = ActWin->view;
	Sepal->SetView(view);
	if (!doc->loading)
		{
		SwitchWin();
		QWidgetList windows = wsp->windowList();
		for ( int i = 0; i < static_cast<int>(windows.count()); ++i )
			{
			swin = (ScribusWin*)windows.at(i);
			if (swin->muster != NULL)
				swin->muster->hide();
			}
		if (doc->TemplateMode)
			ActWin->muster->show();
		setAppMode(doc->AppMode);
		}
	w->setFocus();
	if (w->isMaximized())
		wsp->setScrollBarsEnabled(false);
	else
		wsp->setScrollBarsEnabled(true);
	Sepal->Rebuild();
	Tpal->BuildTree(view);
	Tpal->reopenTree(doc->OpenNodes);
	BookPal->BView->NrItems = ActWin->NrItems;
	BookPal->BView->First = ActWin->First;
	BookPal->BView->Last = ActWin->Last;
	RestoreBookMarks();
	if (!doc->loading)
		{
		if (doc->ActPage->SelItem.count() != 0)
			HaveNewSel(doc->ActPage->SelItem.at(0)->PType);
		else
			HaveNewSel(-1);
		}
}

void ScribusApp::windowsMenuActivated( int id )
{
	if (HaveDoc)
		doc->OpenNodes = Tpal->buildReopenVals();
	QWidget* w = wsp->windowList().at( id );
	if ( w )
		w->showNormal();
	newActWin(w);
}

bool ScribusApp::SetupDoc()
{
	double tpr = doc->PageM.Top;
	double lr = doc->PageM.Left;
	double rr = doc->PageM.Right;
	double br = doc->PageM.Bottom;
	bool fp = doc->PageFP;
	bool fpe = doc->FirstPageLeft;
	double tpr2, lr2, rr2, br2;
	bool ret = false;
	ReformDoc* dia = new ReformDoc(this, tpr, lr, rr, br, doc->PageB, doc->PageH, fp, fpe, doc->Einheit);
	if (dia->exec())
		{
		tpr2 = dia->TopR->value() / UmReFaktor;
		lr2 = dia->LeftR->value() / UmReFaktor;
		rr2 = dia->RightR->value() / UmReFaktor;
		br2 = dia->BottomR->value() / UmReFaktor;
		fp = dia->Doppelseiten->isChecked();
		if (fp)
			doc->FirstPageLeft = dia->ErsteSeite->isChecked();
		doc->resetPage(tpr2, lr2, rr2, br2, fp);
		view->reformPages();
		doc->setModified();
		view->GotoPage(doc->ActPage->PageNr);
		view->DrawNew();
		Sepal->RebuildPage();
		ret = true;
		doc->PDF_Optionen.BleedBottom = doc->PageM.Bottom;
		doc->PDF_Optionen.BleedTop = doc->PageM.Top;
		doc->PDF_Optionen.BleedLeft = doc->PageM.Left;
		doc->PDF_Optionen.BleedRight = doc->PageM.Right;
		}
	delete dia;
	return ret;
}

void ScribusApp::SwitchWin()
{
	int a;
	CListe::Iterator it;
	QPixmap pm = QPixmap(15, 15);
	a = 0;
	ColorMenC->clear();
	ColorMenC->insertItem( tr("None"));
	for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
		{
		pm.fill(doc->PageColors[it.key()].getRGBColor());
		ColorMenC->insertItem(pm, it.key());
		if (it.key() == doc->Dbrush)
			ColorMenC->setCurrentItem(a);
		a++;
		}
	BuildFontMenu();
#ifdef HAVE_CMS
	SoftProofing = ActWin->SoftProofing;
	Gamut = ActWin->Gamut;
	IntentPrinter = ActWin->IntentPrinter;
	IntentMonitor = ActWin->IntentMonitor;
	stdProof = ActWin->stdProof;
	stdTrans = ActWin->stdTrans;
	stdProofImg = ActWin->stdProofImg;
	stdTransImg = ActWin->stdTransImg;
	CMSoutputProf = doc->DocOutputProf;
	CMSprinterProf = doc->DocPrinterProf;
#endif
	Mpal->Cpal->SetColors(doc->PageColors);
	Mpal->Cpal->ChooseGrad(0);
	ActWin->setCaption( tr(doc->DocName));
	ShadeMenu->setItemChecked(ShadeMenu->idAt(11), true);
	Mpal->SetDoc(doc);
	Mpal->updateCList();
	Sepal->SetView(view);
	Mpal->Spal->SetFormats(doc);
	Mpal->SetLineFormats(doc);
	Lpal->setLayers(&doc->Layers, &doc->ActiveLayer);
	view->LaMenu();
	view->setLayMenTxt(doc->ActiveLayer);
	doc->CurrentABStil = 0;
	slotChangeUnit(doc->Einheit, false);
	if (doc->EditClip)
		{
		doc->EditClip = !doc->EditClip;
		ToggleFrameEdit();
		}
	if (doc->ShFrames)
		viewMenu->changeItem(FrameDr, tr("Hide Frames"));
	else
		viewMenu->changeItem(FrameDr, tr("Show Frames"));
	DatClo->setEnabled(true);
	if (doc->TemplateMode)
		{
		menuBar()->setItemEnabled(pgmm, 0);
		editMenu->setItemEnabled(tman, 0);
		DatNeu->setEnabled(false);
		DatSav->setEnabled(false);
		DatOpe->setEnabled(false);
		DatClo->setEnabled(false);
		fileMenu->setItemEnabled(fid1, 0);
		fileMenu->setItemEnabled(fid4, 0);
		fileMenu->setItemEnabled(fid5, 0);
		fileMenu->setItemEnabled(fid51, 0);
		fileMenu->setItemEnabled(fid52, 0);
		fileMenu->setItemEnabled(fid12, 0);
		fileMenu->setItemEnabled(fid13, 0);
		fileMenu->setItemEnabled(fid14, 0);
		Sepal->DisablePal();
		}
	else
		{
		menuBar()->setItemEnabled(pgmm, 1);
		editMenu->setItemEnabled(tman, 1);
		DatNeu->setEnabled(true);
		DatOpe->setEnabled(true);
		DatClo->setEnabled(true);
		DatSav->setEnabled(doc->isModified());
		fileMenu->setItemEnabled(fid1, 1);
		fileMenu->setItemEnabled(fid4, ActWin->MenuStat[2]);
		fileMenu->setItemEnabled(fid5, ActWin->MenuStat[3]);
		fileMenu->setItemEnabled(fid51, ActWin->MenuStat[3]);
		fileMenu->setItemEnabled(fid52, 0);
		fileMenu->setItemEnabled(fid12, 1);
		fileMenu->setItemEnabled(fid13, 1);
		fileMenu->setItemEnabled(fid14, 1);
		if (view->Pages.count() > 1)
			{
			pageMenu->setItemEnabled(pgmd, 1);
			pageMenu->setItemEnabled(pgmv, 1);
			}
		else
			{
			pageMenu->setItemEnabled(pgmd, 0);
			pageMenu->setItemEnabled(pgmv, 0);
			}
		if (doc->isModified())
			slotDocCh(false);
		fileMenu->setItemEnabled(fid5, 1);
		fileMenu->setItemEnabled(fid51, 1);
		Sepal->EnablePal();
		}
}

void ScribusApp::HaveNewDoc()
{
	int a;
	DatPri->setEnabled(true);
	DatPDF->setEnabled(true);
	DatSav->setEnabled(false);
	fileMenu->setItemEnabled(fid1, 1);
	fileMenu->setItemEnabled(fid4, 0);
	fileMenu->setItemEnabled(fid5, 1);
	fileMenu->setItemEnabled(fid51, 1);
	fileMenu->setItemEnabled(fid52, 0);
	fileMenu->setItemEnabled(fid6, 1);
	fileMenu->setItemEnabled(fid7, 1);
	exportMenu->setItemEnabled(fid8, 1);
	importMenu->setItemEnabled(fid2a, 1);
	fileMenu->setItemEnabled(fid9, 1);
	exportMenu->setItemEnabled(fid10, 1);
	fileMenu->setItemEnabled(fid11, 1);
	editMenu->setItemEnabled(edid1, 0);
	editMenu->setItemEnabled(edid2, 0);
	editMenu->setItemEnabled(edid3, 0);
	editMenu->setItemEnabled(edid6, 1);
	editMenu->setItemEnabled(edid6a, 1);
	for (a=0; a<6; ++a)
		{
		viewMenu->setItemEnabled(viewMenu->idAt(a), 1);
		}
	viewMenu->setItemEnabled(Markers, 1);
	viewMenu->setItemEnabled(FrameDr, 1);
	viewMenu->setItemEnabled(Bilder, 1);
	viewMenu->setItemEnabled(Ras, 1);
	viewMenu->setItemEnabled(uRas, 1);
	viewMenu->setItemChecked(uRas, doc->useRaster);
	viewMenu->setItemEnabled(Guide, 1);
	viewMenu->setItemEnabled(uGuide, 1);
	viewMenu->setItemChecked(uGuide, doc->SnapGuides);
	menuBar()->setItemEnabled(pgmm, 1);
	menuBar()->setItemEnabled(exmn, 1);
	WerkTools->setEnabled(true);
	WerkToolsP->setEnabled(true);
	int setter = 0;
	if (view->Pages.count() > 1)
		setter = 1;
	pageMenu->setItemEnabled(pgmd, setter);
	pageMenu->setItemEnabled(pgmv, setter);
	editMenu->setItemEnabled(tman, 1);
	editMenu->setItemEnabled(jman, 1);
	CListe::Iterator it;
	QPixmap pm = QPixmap(15, 15);
	a = 0;
	ColorMenC->clear();
	ColorMenC->insertItem( tr("None"));
	for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
		{
		pm.fill(doc->PageColors[it.key()].getRGBColor());
		ColorMenC->insertItem(pm, it.key());
		if (it.key() == doc->Dbrush)
			ColorMenC->setCurrentItem(a);
		a++;
		}
	Mpal->Cpal->SetColors(doc->PageColors);
	Mpal->Cpal->ChooseGrad(0);
	ActWin->setCaption( tr(doc->DocName));
	ShadeMenu->setItemChecked(ShadeMenu->idAt(11), true);
	Mpal->SetDoc(doc);
	Mpal->updateCList();
	Sepal->SetView(view);
	Mpal->Spal->SetFormats(doc);
	Mpal->SetLineFormats(doc);
	Lpal->setLayers(&doc->Layers, &doc->ActiveLayer);
	view->LaMenu();
	view->setLayMenTxt(doc->ActiveLayer);
	doc->CurrentABStil = 0;
	slotChangeUnit(doc->Einheit);
	doc->Trenner = new Hyphenator(this, doc, this);
  BuildFontMenu();
	connect(view, SIGNAL(changeUN(int)), this, SLOT(slotChangeUnit(int)));
	connect(view, SIGNAL(changeLA(int)), Lpal, SLOT(MarkActiveLayer(int)));
	doc->PDF_Optionen.BleedBottom = doc->PageM.Bottom;
	doc->PDF_Optionen.BleedTop = doc->PageM.Top;
	doc->PDF_Optionen.BleedLeft = doc->PageM.Left;
	doc->PDF_Optionen.BleedRight = doc->PageM.Right;
}

void ScribusApp::HaveNewSel(int Nr)
{
	PageItem *b;
	if (Nr != -1)
		b = doc->ActPage->SelItem.at(0);
	ObjMenu->setItemEnabled(PfadDT, 0);
	switch (Nr)
		{
		case -1:
			importMenu->changeItem(fid2, tr("Get Text/Picture..."));
			importMenu->setItemEnabled(fid2, 0);
			exportMenu->setItemEnabled(fid3, 0);
			menuBar()->setItemEnabled(Stm, 0);
			menuBar()->setItemEnabled(Obm, 0);
			ObjMenu->setItemEnabled(ShapeM, 0);
			ObjMenu->setItemEnabled(PfadTP, 0);
			ObjMenu->setItemEnabled(LockOb, 0);
			editMenu->setItemEnabled(edid1, 0);
			editMenu->setItemEnabled(edid2, 0);
			editMenu->setItemEnabled(edid4, 0);
			editMenu->setItemEnabled(edid5, 0);
			editMenu->setItemEnabled(Sear, 0);
			extraMenu->setItemEnabled(hyph, 0);
			StilMenu->clear();
			WerkTools->KetteAus->setEnabled(false);
			WerkTools->KetteEin->setEnabled(false);
			WerkTools->Textedit->setEnabled(false);
			WerkTools->Textedit2->setEnabled(false);
			WerkTools->Rotiere->setEnabled(false);
			Mpal->Cpal->GradCombo->setCurrentItem(0);
			Tpal->slotShowSelect(doc->ActPage->PageNr, -1);
			break;
		case 2:
			importMenu->changeItem(fid2, tr("Get Picture..."));
			importMenu->setItemEnabled(fid2, 1);
			editMenu->setItemEnabled(edid1, 1);
			editMenu->setItemEnabled(edid2, 1);
			editMenu->setItemEnabled(edid4, 0);
			editMenu->setItemEnabled(edid5, 0);
			editMenu->setItemEnabled(Sear, 0);
			extraMenu->setItemEnabled(hyph, 0);
			menuBar()->setItemEnabled(Stm, 1);
			menuBar()->setItemEnabled(Obm, 1);
			ObjMenu->setItemEnabled(ShapeM, 1);
			ObjMenu->setItemEnabled(PfadTP, 0);
			StilMenu->clear();
			StilMenu->insertItem( tr("Color"), ColorMenu);
			if (b->isRaster)
				StilMenu->insertItem( tr("Invert"), this, SLOT(InvertPict()));
			WerkTools->KetteAus->setEnabled(false);
			WerkTools->KetteEin->setEnabled(false);
			WerkTools->Textedit->setEnabled(b->ScaleType);
			WerkTools->Textedit2->setEnabled(false);
			WerkTools->Rotiere->setEnabled(true);
			break;
		case 4:
			importMenu->changeItem(fid2, tr("Get Text..."));
			importMenu->setItemEnabled(fid2, 1);
			exportMenu->setItemEnabled(fid3, 1);
			editMenu->setItemEnabled(edid1, 1);
			editMenu->setItemEnabled(edid2, 1);
			editMenu->setItemEnabled(edid4, 0);
			editMenu->setItemEnabled(edid5, 0);
			editMenu->setItemEnabled(Sear, 1);
			extraMenu->setItemEnabled(hyph, 1);
			menuBar()->setItemEnabled(Stm, 1);
			menuBar()->setItemEnabled(Obm, 1);
			ObjMenu->setItemEnabled(ShapeM, 1);
			ObjMenu->setItemEnabled(PfadTP, 1);
			StilMenu->clear();
			StilMenu->insertItem( tr("Font"), FontMenu);
			StilMenu->insertItem( tr("Size"), SizeTMenu);
			StilMenu->insertItem( tr("Effects"), TypeStyleMenu);
			StilMenu->insertItem( tr("Tabulators..."), this, SLOT(EditTabs()));
			StilMenu->insertItem( tr("Alignment"), AliMenu);
			StilMenu->insertItem( tr("Color"), ColorMenu);
			StilMenu->insertItem( tr("Shade"), ShadeMenu);
			WerkTools->Rotiere->setEnabled(true);
			WerkTools->Textedit2->setEnabled(true);
			if ((b->NextBox != 0) || (b->BackBox != 0))
				{
				WerkTools->KetteAus->setEnabled(true);
				if ((b->BackBox != 0) && (b->Ptext.count() == 0))
					WerkTools->Textedit->setEnabled(false);
				else
					WerkTools->Textedit->setEnabled(true);
				}
			else
				WerkTools->Textedit->setEnabled(true);
			if (b->NextBox == 0)
				WerkTools->KetteEin->setEnabled(true);
			if (doc->MasterP)
				WerkTools->KetteEin->setEnabled(false);
			if (doc->AppMode == 7)
				setTBvals(b);
			else
				{
				doc->CurrFont = b->IFont;
				doc->CurrFontSize = b->ISize;
				doc->CurrTextFill = b->TxtFill;
				doc->CurrTextStroke = b->TxtStroke;
				doc->CurrTextStrokeSh = b->ShTxtStroke;
				doc->CurrTextFillSh = b->ShTxtFill;
				doc->CurrTextScale = b->TxtScale;
				emit TextFarben(doc->CurrTextStroke, doc->CurrTextFill, doc->CurrTextStrokeSh, doc->CurrTextFillSh);
				doc->CurrentStyle = b->TxTStyle;
 				emit TextStil(doc->CurrentStyle);
				emit TextScale(doc->CurrTextScale);
				setStilvalue(doc->CurrentStyle);
				}
			doc->Vorlagen[0].LineSpa = b->LineSp;
			doc->Vorlagen[0].Ausri = b->Ausrich;
			break;
		case 8:
			importMenu->changeItem(fid2, tr("Get Text..."));
			importMenu->setItemEnabled(fid2, 1);
			exportMenu->setItemEnabled(fid3, 1);
			editMenu->setItemEnabled(edid1, 1);
			editMenu->setItemEnabled(edid2, 1);
			editMenu->setItemEnabled(edid4, 0);
			editMenu->setItemEnabled(edid5, 0);
			editMenu->setItemEnabled(Sear, 0);
			extraMenu->setItemEnabled(hyph, 0);
			menuBar()->setItemEnabled(Stm, 1);
			menuBar()->setItemEnabled(Obm, 1);
			ObjMenu->setItemEnabled(ShapeM, 0);
			ObjMenu->setItemEnabled(PfadDT, 1);
			ObjMenu->setItemEnabled(PfadTP, 0);
			StilMenu->clear();
			StilMenu->insertItem( tr("Font"), FontMenu);
			StilMenu->insertItem( tr("Size"), SizeTMenu);
			StilMenu->insertItem( tr("Style"), TypeStyleMenu);
			StilMenu->insertItem( tr("Color"), ColorMenu);
			StilMenu->insertItem( tr("Shade"), ShadeMenu);
			WerkTools->Rotiere->setEnabled(true);
			WerkTools->Textedit->setEnabled(false);
			WerkTools->Textedit2->setEnabled(true);
			WerkTools->KetteEin->setEnabled(false);
			WerkTools->KetteAus->setEnabled(false);
			if (doc->AppMode == 7)
				setTBvals(b);
			else
				{
				doc->CurrFont = b->IFont;
				doc->CurrFontSize = b->ISize;
				doc->CurrTextFill = b->TxtFill;
				doc->CurrTextStroke = b->TxtStroke;
				doc->CurrTextStrokeSh = b->ShTxtStroke;
				doc->CurrTextFillSh = b->ShTxtFill;
				doc->CurrTextScale = b->TxtScale;
				emit TextFarben(doc->CurrTextStroke, doc->CurrTextFill, doc->CurrTextStrokeSh, doc->CurrTextFillSh);
				doc->CurrentStyle = b->TxTStyle;
 				emit TextStil(doc->CurrentStyle);
				emit TextScale(doc->CurrTextScale);
				setStilvalue(doc->CurrentStyle);
				}
			break;
		default:
			importMenu->changeItem(fid2, tr("Get Text/Picture..."));
			importMenu->setItemEnabled(fid2, 0);
			exportMenu->setItemEnabled(fid3, 0);
			editMenu->setItemEnabled(edid1, 1);
			editMenu->setItemEnabled(edid2, 1);
			editMenu->setItemEnabled(edid4, 0);
			editMenu->setItemEnabled(edid5, 0);
			editMenu->setItemEnabled(Sear, 0);
			extraMenu->setItemEnabled(hyph, 0);
			menuBar()->setItemEnabled(Stm, 1);
			menuBar()->setItemEnabled(Obm, 1);
			StilMenu->clear();
			StilMenu->insertItem( tr("Color"), ColorMenu);
			StilMenu->insertItem( tr("Shade"), ShadeMenu);
			if (Nr == 6)
				ObjMenu->setItemEnabled(ShapeM, 1);
			WerkTools->KetteAus->setEnabled(false);
			WerkTools->KetteEin->setEnabled(false);
			if (Nr != 5)
				WerkTools->Rotiere->setEnabled(true);
			else
				WerkTools->Rotiere->setEnabled(false);
			break;
		}
	doc->CurrentSel = Nr;
	Mpal->RotationGroup->setButton(doc->RotMode);
	if (doc->ActPage->SelItem.count() > 1)
		{
		ObjMenu->setItemEnabled(DistM, 1);
		ObjMenu->setItemEnabled(Gr, 1);
		ObjMenu->setItemEnabled(PfadTP, 0);
		bool hPoly = true;
		for (uint bx=0; bx<doc->ActPage->SelItem.count(); ++bx)
			{
			if (doc->ActPage->SelItem.at(bx)->PType != 6)
				hPoly = false;
			}
		ObjMenu->setItemEnabled(PfadV, hPoly);
		if (doc->ActPage->SelItem.count() == 2)
			{
			if (((b->PType == 4) || (doc->ActPage->SelItem.at(1)->PType == 4)) && ((b->PType == 7) || (doc->ActPage->SelItem.at(1)->PType == 7)))
				{
				PageItem* bx = doc->ActPage->SelItem.at(1);
				if ((b->NextBox == 0) && (b->BackBox == 0) && (bx->NextBox == 0) && (bx->BackBox == 0))
					ObjMenu->setItemEnabled(PfadT, 1);
				}
			}
		}
	else
		{
		ObjMenu->setItemEnabled(DistM, 0);
		ObjMenu->setItemEnabled(Gr, 0);
		ObjMenu->setItemEnabled(PfadT, 0);
		ObjMenu->setItemEnabled(PfadV, 0);
		}
	if (doc->ActPage->SelItem.count() != 0)
		{
		Mpal->Textflow->setChecked(b->Textflow);
		ObjMenu->setItemEnabled(LockOb, 1);
		if (b->Groups.count() != 0)
			ObjMenu->setItemEnabled(UnGr, 1);
		else
			{
			ObjMenu->setItemEnabled(UnGr, 0);
			if ((b->PType == 6) && (b->Segments.count() != 0))
				ObjMenu->setItemEnabled(PfadS, 1);
			else
				ObjMenu->setItemEnabled(PfadS, 0);
			}
		if (b->Locked)
			{
			ObjMenu->setItemEnabled(DistM, 0);
			ObjMenu->setItemEnabled(ShapeM, 0);
			ObjMenu->setItemEnabled(PfadTP, 0);
			ObjMenu->setItemEnabled(PfadS, 0);
			ObjMenu->setItemEnabled(PfadT, 0);
			ObjMenu->setItemEnabled(PfadDT, 0);
			ObjMenu->setItemEnabled(PfadV, 0);
			ObjMenu->setItemEnabled(Loesch, 0);
			ObjMenu->setItemEnabled(OBack, 0);
			ObjMenu->setItemEnabled(OFront, 0);
			ObjMenu->setItemEnabled(ORaise, 0);
			ObjMenu->setItemEnabled(OLower, 0);
			editMenu->setItemEnabled(edid1, 0);
			editMenu->setItemEnabled(edid4, 0);
			WerkTools->Rotiere->setEnabled(false);
			ObjMenu->changeItem(LockOb, tr("Unlock"));
			}
		else
			{
			ObjMenu->changeItem(LockOb, tr("Lock"));
			ObjMenu->setItemEnabled(OBack, 1);
			ObjMenu->setItemEnabled(OFront, 1);
			ObjMenu->setItemEnabled(ORaise, 1);
			ObjMenu->setItemEnabled(OLower, 1);
			}
		}
	Mpal->NewSel(Nr);
	if (Nr != -1)
		{
 		Mpal->SetCurItem(b);
		Tpal->slotShowSelect(b->OwnPage->PageNr, b->ItemNr);
		}
}

void ScribusApp::slotDocCh(bool reb)
{
	if ((reb) && (!doc->TemplateMode) && (doc->ActPage->SelItem.count() != 0))
		Tpal->slotUpdateElement(doc->ActPage->PageNr, doc->ActPage->SelItem.at(0)->ItemNr);
	if (!doc->isModified())
		doc->setModified();
	ActWin->setCaption( tr(doc->DocName) + "*");
	if (!doc->TemplateMode)
		{
		fileMenu->setItemEnabled(fid4, 1);
		DatSav->setEnabled(true);
		DatClo->setEnabled(true);
		fileMenu->setItemEnabled(fid5, 1);
		fileMenu->setItemEnabled(fid51, 1);
		if (doc->hasName)
			fileMenu->setItemEnabled(fid52, 1);
		}
	ActWin->MenuStat[0] = DatSav->isEnabled();
	ActWin->MenuStat[1] = fileMenu->isItemEnabled(fid1);
	ActWin->MenuStat[2] = fileMenu->isItemEnabled(fid4);
	ActWin->MenuStat[3] = fileMenu->isItemEnabled(fid5);
}

void ScribusApp::UpdateRecent(QString fn)
{
	recentMenu->clear();
	if (RecentDocs.findIndex(fn) == -1)
		RecentDocs.prepend(fn);
	else
		{
		RecentDocs.remove(fn);
		RecentDocs.prepend(fn);
		}
	uint max = QMIN(Prefs.RecentDCount, RecentDocs.count());
	for (uint m = 0; m < max; ++m)
		{
		recentMenu->insertItem(RecentDocs[m]);
		}
}

void ScribusApp::LoadRecent(int id)
{
	QString fn = recentMenu->text(id);
	QFileInfo fd(fn);
	if (!fd.exists())
		{
		RecentDocs.remove(fn);
		recentMenu->clear();
		uint max = QMIN(Prefs.RecentDCount, RecentDocs.count());
		for (uint m = 0; m < max; ++m)
			{
			recentMenu->insertItem(RecentDocs[m]);
			}
		return;
		}
  qApp->setOverrideCursor(QCursor(waitCursor), true);
	LadeDoc(recentMenu->text(id));
  qApp->setOverrideCursor(QCursor(arrowCursor), true);
}

bool ScribusApp::slotDocOpen()
{
	bool ret = false;
#ifdef HAVE_LIBZ
	QString fileName = CFileDialog( tr("Open"), tr("Documents (*.sla *.sla.gz *.scd *.scd.gz);;All Files (*)"));
#else
	QString fileName = CFileDialog( tr("Open"), tr("Documents (*.sla *.scd);;All Files (*)"));
#endif
  qApp->setOverrideCursor(QCursor(waitCursor), true);
	ret = LadeDoc(fileName);
  qApp->setOverrideCursor(QCursor(arrowCursor), true);
	return ret;
}

bool ScribusApp::slotDocMerge()
{
	bool ret = false;
	MergeDoc *dia = new MergeDoc(this, false);
	if (dia->exec())
		{
		qApp->setOverrideCursor(QCursor(waitCursor), true);
		ret = LadeSeite(dia->Filename->text(), dia->PageNr->value()-1, false);
		qApp->setOverrideCursor(QCursor(arrowCursor), true);
		ret = true;
		}
	delete dia;
	return ret;
}

bool ScribusApp::LadeSeite(QString fileName, int Nr, bool Mpa)
{
	bool ret = false;
  if (!fileName.isEmpty())
  	{
		if (!Mpa)
			doc->OpenNodes = Tpal->buildReopenVals();
		doc->loading = true;
  	ScriXmlDoc *ss = new ScriXmlDoc();
  	if(!ss->ReadPage(fileName, Prefs.AvailFonts, doc, view, Nr, Mpa))
  		{
  		delete ss;
			doc->loading = false;
  		return false;
  		}
  	delete ss;
		if (CMSavail)
			{
			if (doc->CMSSettings.CMSinUse)
				{
				RecalcColors();
				view->RecalcPictures(&InputProfiles);
				}
			}
		for (uint azz = 0; azz < doc->ActPage->Items.count(); ++azz)
			{
			PageItem *ite = doc->ActPage->Items.at(azz);
			if ((ite->PType == 4) && (ite->isBookmark))
				BookPal->BView->AddPageItem(ite);
			}
		Mpal->Cpal->SetColors(doc->PageColors);
		Mpal->updateCList();
		Mpal->Spal->SetFormats(doc);
		Mpal->SetLineFormats(doc);
		if (!Mpa)
			{
			Tpal->BuildTree(view);
			Tpal->reopenTree(doc->OpenNodes);
			}
		slotDocCh();
		doc->loading = false;
		ret = true;
		}
	Sepal->Rebuild();
  doc->ActPage->update();
	return ret;
}

bool ScribusApp::LadeDoc(QString fileName)
{
	if (HaveDoc)
		doc->OpenNodes = Tpal->buildReopenVals();
	bool ret = false;
  if (!fileName.isEmpty())
  	{
  	QFileInfo fi(fileName);
  	QDir::setCurrent(fi.dirPath(true));
		doc=new ScribusDoc();
		doc->AllFonts = &Prefs.AvailFonts;
		doc->AddFont(Prefs.DefFont, Prefs.AvailFonts[Prefs.DefFont]->Font);
		doc->Dfont = Prefs.DefFont;
		doc->Dsize = Prefs.DefSize;
		doc->GrabRad = Prefs.GrabRad;
		doc->GuideRad = Prefs.GuideRad;
		doc->minorGrid = Prefs.DminGrid;
		doc->majorGrid = Prefs.DmajGrid;
		doc->minorColor = Prefs.DminColor;
		doc->majorColor = Prefs.DmajColor;
		doc->papColor = Prefs.DpapColor;
		doc->margColor = Prefs.DmargColor;
		doc->guideColor = Prefs.guideColor;
  	doc->Dpen = Prefs.Dpen;
  	doc->DpenText = Prefs.DpenText;
  	doc->Dbrush = Prefs.Dbrush;
  	doc->Dshade = Prefs.Dshade;
  	doc->Dshade2 = Prefs.Dshade2;
		doc->DCols = Prefs.DCols;
		doc->DGap = Prefs.DGap;
  	doc->DLineArt = PenStyle(Prefs.DLineArt);
  	doc->Dwidth = Prefs.Dwidth;
  	doc->DpenLine = Prefs.DpenLine;
  	doc->DshadeLine = Prefs.DshadeLine;
  	doc->DLstyleLine = PenStyle(Prefs.DLstyleLine);
  	doc->DwidthLine = Prefs.DwidthLine;
  	doc->MagMin = Prefs.MagMin;
  	doc->MagMax = Prefs.MagMax;
  	doc->MagStep = Prefs.MagStep;
  	doc->DbrushPict = Prefs.DbrushPict;
		doc->ShadePict = Prefs.ShadePict;
		doc->ScaleX = Prefs.ScaleX;
		doc->ScaleY = Prefs.ScaleY;
		doc->ScaleType = Prefs.ScaleType;
		doc->AspectRatio = Prefs.AspectRatio;
		doc->Before = Prefs.Before;
		doc->Einheit = Prefs.Einheit;
		doc->PagesSbS = Prefs.PagesSbS;
		doc->ShFrames = Prefs.ShFrames;
		doc->RandFarbig = Prefs.RandFarbig;
		doc->AutoLine = Prefs.AutoLine;
		doc->Scale = 1.0*Prefs.DisScale;
		doc->AppMode = 1;
		doc->HasCMS = false;
		doc->ActiveLayer = 0;
		doc->Language = Prefs.Language;
		doc->MinWordLen = Prefs.MinWordLen;
		doc->Automatic = Prefs.Automatic;
		doc->AutoCheck = Prefs.AutoCheck;
		doc->OpenNodes.clear();
		doc->loading = true;
		FMess->setText( tr("Loading..."));
		FProg->reset();
		ScribusWin* w = new ScribusWin(wsp, doc);
		view = new ScribusView(w, doc, &Prefs);
		w->setView(view);
		ActWin = w;
		doc->WinHan = w;
		w->setCentralWidget(view);
  	ScriXmlDoc *ss = new ScriXmlDoc();
  	connect(ss, SIGNAL(NewPage(int)), this, SLOT(slotNewPage(int)));
#ifdef HAVE_CMS
		w->SoftProofing = false;
		w->Gamut = false;
		bool cmsu = CMSuse;
		CMSuse = false;
#endif
  	if(!ss->ReadDoc(fi.fileName(), Prefs.AvailFonts, doc, view, FProg))
  		{
  		view->close();
  		disconnect(ss, SIGNAL(NewPage(int)), this, SLOT(slotNewPage(int)));
  		delete ss;
  		delete view;
  		delete doc;
			delete w;
			FMess->setText("");
			FProg->reset();
			ActWin = NULL;
  		return false;
  		}
  	delete ss;
		FMess->setText("");
		FProg->reset();
#ifdef HAVE_CMS
		CMSuse = cmsu;
#endif
		HaveDoc++;
		connect(w, SIGNAL(Schliessen()), this, SLOT(DoFileClose()));
		connect(w, SIGNAL(SaveAndClose()), this, SLOT(DoSaveClose()));
		if (!doc->HasCMS)
			{
			doc->CMSSettings.DefaultInputProfile = Prefs.DCMSset.DefaultInputProfile;
			doc->CMSSettings.DefaultInputProfile2 = Prefs.DCMSset.DefaultInputProfile2;
			doc->CMSSettings.DefaultMonitorProfile = Prefs.DCMSset.DefaultMonitorProfile;
			doc->CMSSettings.DefaultPrinterProfile = Prefs.DCMSset.DefaultPrinterProfile;
			doc->CMSSettings.DefaultIntentPrinter = Prefs.DCMSset.DefaultIntentPrinter;
			doc->CMSSettings.DefaultIntentMonitor = Prefs.DCMSset.DefaultIntentMonitor;
			doc->CMSSettings.DefaultIntentMonitor2 = Prefs.DCMSset.DefaultIntentMonitor2;
			doc->CMSSettings.SoftProofOn = Prefs.DCMSset.SoftProofOn;
			doc->CMSSettings.GamutCheck = Prefs.DCMSset.GamutCheck;
			doc->CMSSettings.BlackPoint = Prefs.DCMSset.BlackPoint;
			doc->CMSSettings.CMSinUse = false;
			}
		if (CMSavail)
			{
			if (!InputProfiles.contains(doc->CMSSettings.DefaultInputProfile))
				doc->CMSSettings.DefaultInputProfile = Prefs.DCMSset.DefaultInputProfile;
			if (!InputProfiles.contains(doc->CMSSettings.DefaultInputProfile2))
				doc->CMSSettings.DefaultInputProfile2 = Prefs.DCMSset.DefaultInputProfile2;
			if (!MonitorProfiles.contains(doc->CMSSettings.DefaultMonitorProfile))
				doc->CMSSettings.DefaultMonitorProfile = Prefs.DCMSset.DefaultMonitorProfile;
			if (!PrinterProfiles.contains(doc->CMSSettings.DefaultPrinterProfile))
				doc->CMSSettings.DefaultPrinterProfile = Prefs.DCMSset.DefaultPrinterProfile;
			if (!PrinterProfiles.contains(doc->PDF_Optionen.PrintProf))
				doc->PDF_Optionen.PrintProf = doc->CMSSettings.DefaultPrinterProfile;
			if (!InputProfiles.contains(doc->PDF_Optionen.ImageProf))
				doc->PDF_Optionen.ImageProf = doc->CMSSettings.DefaultInputProfile;
			if (!InputProfiles.contains(doc->PDF_Optionen.SolidProf))
				doc->PDF_Optionen.SolidProf = doc->CMSSettings.DefaultInputProfile2;
#ifdef HAVE_CMS
			w->SoftProofing = doc->CMSSettings.SoftProofOn;
			w->Gamut = doc->CMSSettings.GamutCheck;
			CMSuse = doc->CMSSettings.CMSinUse;
			w->IntentPrinter = doc->CMSSettings.DefaultIntentPrinter;
			w->IntentMonitor = doc->CMSSettings.DefaultIntentMonitor;
			SoftProofing = doc->CMSSettings.SoftProofOn;
			Gamut = doc->CMSSettings.GamutCheck;
			IntentPrinter = doc->CMSSettings.DefaultIntentPrinter;
			IntentMonitor = doc->CMSSettings.DefaultIntentMonitor;
			w->OpenCMSProfiles(InputProfiles, MonitorProfiles, PrinterProfiles);
			CMSuse = doc->CMSSettings.CMSinUse;
			stdProof = w->stdProof;
			stdTrans = w->stdTrans;
			stdProofImg = w->stdProofImg;
			stdTransImg = w->stdTransImg;
			CMSoutputProf = doc->DocOutputProf;
			CMSprinterProf = doc->DocPrinterProf;
			if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigRgbData)
				doc->CMSSettings.ComponentsInput2 = 3;
			if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigCmykData)
				doc->CMSSettings.ComponentsInput2 = 4;
			if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigCmyData)
				doc->CMSSettings.ComponentsInput2 = 3;
			if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigRgbData)
				doc->CMSSettings.ComponentsPrinter = 3;
			if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigCmykData)
				doc->CMSSettings.ComponentsPrinter = 4;
			if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigCmyData)
				doc->CMSSettings.ComponentsPrinter = 3;
			doc->PDF_Optionen.SComp = doc->CMSSettings.ComponentsInput2;
#endif
			if (doc->CMSSettings.CMSinUse)
				{
				RecalcColors();
				view->RecalcPictures(&InputProfiles);
				}
			}
		Mpal->Cpal->SetColors(doc->PageColors);
		Mpal->Cpal->ChooseGrad(0);
		doc->DocName = fileName;
		doc->MasterP = false;
		HaveNewDoc();
		Mpal->updateCList();
		doc->hasName = true;
		if (view->MasterPages.count() == 0)
			{
			for (uint ax=0; ax<view->Pages.count(); ++ax)
				{
				view->Pages.at(ax)->parentWidget()->hide();
				}
			view->DocPages = view->Pages;
			view->Pages = view->MasterPages;
			doc->PageC = view->MasterPages.count();
			bool atf = doc->PageAT;
			doc->PageAT = false;
			slotNewPage(0);
			doc->PageAT = atf;
			view->MasterNames["Normal"] = 0;
			view->Pages.at(0)->PageNam = "Normal";
			view->Pages.at(0)->parentWidget()->hide();
			view->MasterPages = view->Pages;
			doc->PageC = view->DocPages.count();
			view->Pages = view->DocPages;
			doc->MasterP = false;
			for (uint ay=0; ay<view->Pages.count(); ++ay)
				{
				view->Pages.at(ay)->parentWidget()->show();
				}
			}
		doc->setUnModified();
		doc->loading = false;
		view->GotoPage(0);
		doc->RePos = true;
		QPixmap pgPix(10, 10);
		QRect rd = QRect(0,0,9,9);
		ScPainter *painter = new ScPainter(&pgPix, pgPix.width(), pgPix.height());
		for (uint az=0; az<view->MasterPages.count(); az++)
			{
			for (uint azz=0; azz<view->MasterPages.at(az)->Items.count(); ++azz)
				{
				PageItem *ite = view->MasterPages.at(az)->Items.at(azz);
				if (ite->PType == 4)
					ite->DrawObj(painter, rd);
				}
			}
		RestoreBookMarks();
		for (uint az=0; az<view->Pages.count(); az++)
			{
			for (uint azz=0; azz<view->Pages.at(az)->Items.count(); ++azz)
				{
				PageItem *ite = view->Pages.at(az)->Items.at(azz);
				if (ite->PType == 4)
					ite->DrawObj(painter, rd);
				if (doc->OldBM)
					{
					if ((ite->PType == 4) && (ite->isBookmark))
						BookPal->BView->AddPageItem(ite);
					}
				else
					{
					if ((ite->PType == 4) && (ite->isBookmark))
						BookPal->BView->ChangeItem(ite->BMnr, ite->ItemNr);
					}
				}
			}
		delete painter;
		if (doc->OldBM)
			StoreBookmarks();
		ActWin->NrItems = BookPal->BView->NrItems;
		ActWin->First = BookPal->BView->First;
		ActWin->Last = BookPal->BView->Last;
		doc->RePos = false;
		UpdateRecent(fileName);
  	FMess->setText( tr("Ready"));
		ret = true;
		if ((wsp->windowList().isEmpty()) || (wsp->windowList().count() == 1))
			w->showMaximized();
		else
			w->show();
		view->show();
		newActWin(w);
		connect(doc->ASaveTimer, SIGNAL(timeout()), w, SLOT(slotAutoSave()));
		connect(w, SIGNAL(AutoSaved()), this, SLOT(slotAutoSaved()));
		doc->AutoSave = Prefs.AutoSave;
		if (doc->AutoSave)
			doc->ASaveTimer->start(Prefs.AutoSaveTime);
  	}
	else
		{
		Sepal->Vie = 0;
		}
	Sepal->Rebuild();
	return ret;
}

void ScribusApp::slotFileOpen()
{
  if (doc->ActPage->SelItem.count() != 0)
  	{
 		PageItem *b = doc->ActPage->SelItem.at(0);
  	if (b->PType == 2)
  		{
			QString formats = "";
			QString form1 = "";
			QString form2 = "";
			for ( uint i = 0; i < QImageIO::inputFormats().count(); ++i )
				{
				form1 = QString(QImageIO::inputFormats().at(i)).lower();
				form2 = QString(QImageIO::inputFormats().at(i)).upper();
				if (form1 == "jpeg")
					{
					form1 = "jpg";
					form2 = "JPG";
					}
				if ((form1 == "jpg") || (form1 == "png") || (form1 == "xpm") || (form1 == "gif"))
        	formats += form2 + " (*."+form1+" *."+form2+");;";
				}
#ifdef HAVE_TIFF
			formats += "TIFF (*.tif *.TIF);;";
#endif
			formats += "EPS (*.eps *.EPS);;PDF (*.pdf *.PDF);;" + tr("All Files (*)");
  		QString fileName = CFileDialog( tr("Open"), formats, "", true);
    	if (!fileName.isEmpty())
    		{
     		b->EmProfile = "";
      	b->UseEmbedded = true;
  			b->IProfile = doc->CMSSettings.DefaultInputProfile;
				b->IRender = doc->CMSSettings.DefaultIntentMonitor2;
    		doc->ActPage->LoadPict(fileName, b->ItemNr);
    		doc->ActPage->AdjustPictScale(b);
    		doc->ActPage->AdjustPreview(b);
    		doc->ActPage->update();
				Mpal->Cpal->SetColors(doc->PageColors);
				Mpal->updateCList();
				Mpal->ShowCMS();
				slotDocCh();
  			}
  		}
  	if (b->PType == 4)
  		{
			LoadEnc = "";
  		QString fileName = CFileDialog( tr("Open"), tr("Text Files (*.txt);;All Files(*)"), "", false, true, false, true);
    if (!fileName.isEmpty())
  			{
  			Serializer *ss = new Serializer(fileName);
  			if (ss->Read(LoadEnc))
  				{
					int st = doc->CurrentABStil;
  				ss->GetText(b, st, doc->Vorlagen[st].Font, doc->Vorlagen[st].FontSize);
  				}
  			delete ss;
				if (doc->Trenner->AutoCheck)
					doc->Trenner->slotHyphenate(b);
    		doc->ActPage->update();
				slotDocCh();
  			}
  		}
  	}
}

void ScribusApp::slotFileRevert()
{
  if ((doc->hasName) && (doc->isModified()) && (!doc->TemplateMode))
  	{
		QString fn = doc->DocName;
  	QFileInfo fi(fn);
  	QDir::setCurrent(fi.dirPath(true));
		doc->setUnModified();
		slotFileClose();
		qApp->processEvents();
  	qApp->setOverrideCursor(QCursor(waitCursor), true);
		LadeDoc(fn);
  	qApp->setOverrideCursor(QCursor(arrowCursor), true);
		}
}

void ScribusApp::slotAutoSaved()
{
	if (ActWin == sender())
		{
		fileMenu->setItemEnabled(fid4, 0);
		DatSav->setEnabled(false);
		ActWin->setCaption(doc->DocName);
		}
}

void ScribusApp::slotFileSave()
{
	if (doc->hasName)
		{
  	QString fn = doc->DocName;
		if (!DoFileSave(fn))
			QMessageBox::warning(this, tr("Warning"), tr("Can't write the File: \n%1").arg(fn), tr("OK"));
		}
	else
		slotFileSaveAs();
}

void ScribusApp::slotFileSaveAs()
{
	QString fna;
  if (doc->hasName)
  	{
  	QFileInfo fi(doc->DocName);
  	fna = fi.dirPath()+"/"+fi.baseName()+".sla";
  	}
  else
  	{
  	QDir di = QDir();
  	fna = di.currentDirPath()+"/"+doc->DocName+".sla";
  	}
#ifdef HAVE_LIBZ
  QString fn = CFileDialog( tr("Save as"), tr("Documents (*.sla *.sla.gz *.scd *scd.gz);;All Files (*)"), fna, false, false, true);
#else
  QString fn = CFileDialog( tr("Save as"), tr("Documents (*.sla *.scd);;All Files (*)"), fna, false, false, false);
#endif
  if (!fn.isEmpty())
  	{
		if (overwrite(this, fn))
			{
			if (!DoFileSave(fn))
				QMessageBox::warning(this, tr("Warning"), tr("Can't write the File: \n%1").arg(fn), tr("OK"));
			}
  	}
  FMess->setText( tr("Ready"));
}

bool ScribusApp::DoFileSave(QString fn)
{
	bool ret = true;
	ReorgFonts();
	FMess->setText( tr("Saving..."));
	FProg->reset();
  QFileInfo fi(fn);
  QDir::setCurrent(fi.dirPath(true));
 	ScriXmlDoc *ss = new ScriXmlDoc();
	qApp->processEvents();
 	ret = ss->WriteDoc(fn, doc, view, FProg);
 	delete ss;
	if (ret)
		{
		doc->setUnModified();
		ActWin->setCaption(fn);
		doc->DocName = fn;
		fileMenu->setItemEnabled(fid4, 0);
		fileMenu->setItemEnabled(fid52, 0);
		DatSav->setEnabled(false);
		UpdateRecent(fn);
		doc->hasName = true;
		}
	FMess->setText("");
	FProg->reset();
	return ret;
}

bool ScribusApp::slotFileClose()
{
	ScribusWin* tw = ActWin;
	singleClose = false;
	ActWin->close();
	if (tw == ActWin)
		return false;
	else
		return true;
}

bool ScribusApp::DoFileClose()
{
  uint a;
	setAppMode(1);
  doc->ASaveTimer->stop();
	disconnect(doc->ASaveTimer, SIGNAL(timeout()), doc->WinHan, SLOT(slotAutoSave()));
	disconnect(doc->WinHan, SIGNAL(AutoSaved()), this, SLOT(slotAutoSaved()));
	if ((doc->UnData.UnCode == 0) && (doc->UnDoValid))
		delete doc->UnData.Item;
  if (CMSavail)
  	ActWin->CloseCMSProfiles();
	Mpal->NewSel(-1);
  Mpal->UnsetDoc();
	Sepal->Vie = 0;
	Sepal->Rebuild();
  Mpal->Spal->SetFormats(0);
	Mpal->SetLineFormats(0);
	if (doc->EditClip)
		Npal->doc = 0;
	BookPal->BView->clear();
	BookPal->BView->NrItems = 0;
	BookPal->BView->First = 1;
	BookPal->BView->Last = 0;
	if ((wsp->windowList().isEmpty()) || (wsp->windowList().count() == 1))
		{
		fileMenu->setItemEnabled(fid1, 0);
		importMenu->setItemEnabled(fid2, 0);
		exportMenu->setItemEnabled(fid3, 0);
		fileMenu->setItemEnabled(fid4, 0);
		fileMenu->setItemEnabled(fid5, 0);
		fileMenu->setItemEnabled(fid51, 0);
		fileMenu->setItemEnabled(fid52, 0);
		fileMenu->setItemEnabled(fid6, 0);
		fileMenu->setItemEnabled(fid7, 0);
		exportMenu->setItemEnabled(fid8, 0);
		importMenu->setItemEnabled(fid2a, 0);
		fileMenu->setItemEnabled(fid9, 0);
		exportMenu->setItemEnabled(fid10, 0);
		fileMenu->setItemEnabled(fid11, 0);
		editMenu->setItemEnabled(edUndo, 0);
		editMenu->setItemEnabled(edid1, 0);
		editMenu->setItemEnabled(edid2, 0);
		editMenu->setItemEnabled(edid3, 0);
		editMenu->setItemEnabled(edid4, 0);
		editMenu->setItemEnabled(edid5, 0);
		editMenu->setItemEnabled(edid6, 0);
		editMenu->setItemEnabled(edid6a, 0);
		editMenu->setItemEnabled(Sear, 0);
		extraMenu->setItemEnabled(hyph, 0);
		for (int a=0; a<6; ++a)
			{
			viewMenu->setItemEnabled(viewMenu->idAt(a), 0);
			}
		viewMenu->setItemEnabled(Markers, 0);
		viewMenu->setItemEnabled(FrameDr, 0);
		viewMenu->setItemEnabled(Bilder, 0);
		viewMenu->setItemEnabled(Ras, 0);
		viewMenu->setItemEnabled(uRas, 0);
		viewMenu->setItemChecked(uRas, false);
		viewMenu->setItemEnabled(Guide, 0);
		viewMenu->setItemEnabled(uGuide, 0);
		viewMenu->setItemChecked(uGuide, false);
		viewMenu->changeItem(Markers, tr("Hide Margins"));
		viewMenu->changeItem(FrameDr, tr("Hide Frames"));
		viewMenu->changeItem(Bilder, tr("Hide Images"));
		viewMenu->changeItem(Ras, tr("Show Grid"));
		viewMenu->changeItem(Guide, tr("Hide Guides"));
		editMenu->setItemEnabled(tman, 0);
		editMenu->setItemEnabled(jman, 0);
		menuBar()->setItemEnabled(pgmm, 0);
		menuBar()->setItemEnabled(exmn, 0);
		menuBar()->setItemEnabled(Stm, 0);
		menuBar()->setItemEnabled(Obm, 0);
		WerkTools->setEnabled(false);
		WerkToolsP->setEnabled(false);
		ColorMenC->clear();
		Mpal->Cpal->SetColors(Prefs.DColors);
		Mpal->Cpal->ChooseGrad(0);
	  FMess->setText( tr("Ready"));
		Tpal->PageObj.clear();
		Tpal->Seiten.clear();
	  Tpal->ListView1->clear();
		Lpal->ClearInhalt();
		DatPri->setEnabled(false);
		DatPDF->setEnabled(false);
		DatSav->setEnabled(false);
		DatClo->setEnabled(false);
	  PrinterUsed = false;
#ifdef HAVE_CMS
		CMSuse = false;
		SoftProofing = Prefs.DCMSset.SoftProofOn;
		IntentPrinter = Prefs.DCMSset.DefaultIntentPrinter;
		IntentMonitor = Prefs.DCMSset.DefaultIntentMonitor;
#endif
		}
  view->close();
  for (a = 0; a<view->Pages.count(); ++a)
  	{
  	delete view->Pages.at(a);
  	}
  HaveDoc--;
	view = NULL;
	delete doc;
	doc = NULL;
	ActWin = NULL;
	return true;
}

void ScribusApp::slotFilePrint()
{
  QString fna, prn, cmd, scmd, cc, data, SepNam;
  int Anf, Ende, Nr;
  bool fil, sep, farbe, PSfile, mirrorH, mirrorV, useICC;
	PSfile = false;
  FMess->setText( tr("Printing..."));
  if (PrinterUsed)
  	{
  	prn = PDef.Pname;
  	fna = PDef.Dname;
  	}
  else
  	{
  	prn = "";
  	if (!doc->DocName.startsWith( tr("Document")))
  		{
  		QFileInfo fi(doc->DocName);
  		fna = fi.dirPath()+"/"+fi.baseName()+".ps";
  		}
  	else
  		{
  		QDir di = QDir();
  		fna = di.currentDirPath()+"/"+doc->DocName+".ps";
  		}
  	}
	scmd = PDef.Command;
  Druck *printer = new Druck(this, fna, prn, scmd);
  printer->setMinMax(1, view->Pages.count());
  printer->setFromTo(1, view->Pages.count());
  if (printer->exec())
  	{
  	qApp->setOverrideCursor(QCursor(waitCursor), true);
  	prn = printer->printerName();
  	fna = printer->outputFileName();
  	fil = printer->outputToFile();
  	Anf = printer->fromPage();
  	Ende = printer->toPage();
  	Nr = printer->numCopies();
  	sep = printer->outputSeparations();
  	SepNam = printer->separationName();
  	farbe = printer->color();
    mirrorH = printer->MirrorH;
    mirrorV = printer->MirrorV;
    useICC = printer->ICCinUse;
  	PDef.Pname = prn;
  	PDef.Dname = fna;
		if (printer->OtherCom->isChecked())
			PDef.Command = printer->Command->text();
  	PrinterUsed = true;
		QMap<QString,QFont> ReallyUsed;
		ReallyUsed.clear();
		GetUsedFonts(&ReallyUsed);
		PSLib *dd = getPSDriver(true, Prefs.AvailFonts, ReallyUsed, doc->PageColors, false);
		if (dd != NULL)
			{
			if (fil)
				PSfile = dd->PS_set_file(fna);
			else
				PSfile = dd->PS_set_file(PrefsPfad+"/tmp.ps");
			if (PSfile)
				{
 				if (printer->pageOrder() == 0)
					view->CreatePS(dd, Anf-1, Ende, 1, sep, SepNam, farbe, mirrorH, mirrorV, useICC);
				else
					view->CreatePS(dd, Ende-1, Anf-2, -1, sep, SepNam, farbe, mirrorH, mirrorV, useICC);
				if (!fil)
					{
					if (printer->OtherCom->isChecked())
						{
						cmd = printer->Command->text()+ " "+PrefsPfad+"/tmp.ps";
						system(cmd);
						}
					else
						{
						cmd = "lpr -P" + prn;
						if (Nr > 1)
							cmd += " -#" + cc.setNum(Nr);
#ifdef HAVE_CUPS
						cmd += printer->PrinterOpts;
#endif
						cmd += " "+PrefsPfad+"/tmp.ps";
						system(cmd);
						}
					system("rm -f "+PrefsPfad+"/tmp.ps");
					}
				}
			else
				QMessageBox::warning(this, tr("Warning"), tr("Printing failed!"), tr("OK"));
			delete dd;
			closePSDriver();
 			qApp->setOverrideCursor(QCursor(arrowCursor), true);
 			}
  	}
  delete printer;
	FMess->setText( tr("Ready"));
}

void ScribusApp::slotFileQuit()
{
	Mpal->UnsetDoc();
	close();
}

void ScribusApp::slotEditCut()
{
	uint a;
	NoFrameEdit();
	QString BufferI = "";
	if ((HaveDoc) && (doc->ActPage->SelItem.count() != 0))
		{
		Buffer2 = "<SCRIBUSTEXT>";
		PageItem *b = doc->ActPage->SelItem.at(0);
		if (doc->AppMode == 7)
			{
			if ((b->Ptext.count() == 0) || (!b->HasSel))
				return;
			PageItem *nb = b;
			while (nb != 0)
				{
				if (nb->BackBox != 0)
					nb = nb->BackBox;
				else
					break;
				}
			while (nb != 0)
				{
				for (a = 0; a < nb->Ptext.count(); ++a)
					{
					if (nb->Ptext.at(a)->cselect)
						{
						if (nb->Ptext.at(a)->ch == QChar(13))
							{
							Buffer2 += QChar(5);
							BufferI += QChar(10);
							}
						else if (nb->Ptext.at(a)->ch == QChar(9))
							{
							Buffer2 += QChar(4);
							BufferI += QChar(9);
							}
						else
							{
							Buffer2 += nb->Ptext.at(a)->ch;
							BufferI += nb->Ptext.at(a)->ch;
							}
						Buffer2 += "\t";
						Buffer2 += nb->Ptext.at(a)->cfont+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->csize)+"\t";
						Buffer2 += nb->Ptext.at(a)->ccolor+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cextra)+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cshade)+'\t';
						Buffer2 += QString::number(nb->Ptext.at(a)->cstyle)+'\t';
						Buffer2 += QString::number(nb->Ptext.at(a)->cab)+'\t';
						Buffer2 += nb->Ptext.at(a)->cstroke+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cshade2)+'\t';
						Buffer2 += QString::number(nb->Ptext.at(a)->cscale)+'\n';
						}
					}
				DeleteSel(nb);
				nb->Dirty = true;
				nb = nb->NextBox;
				}
			doc->ActPage->RefreshItem(b);
			}
		else
			{
  		ScriXmlDoc *ss = new ScriXmlDoc();
			BufferI = ss->WriteElem(&doc->ActPage->SelItem, doc);
			Buffer2 = BufferI;
			doc->ActPage->DeleteItem();
			}
		slotDocCh();
		BuFromApp = true;
		ClipB->setText(BufferI);
		editMenu->setItemEnabled(edid3, 1);
		}
}

void ScribusApp::slotEditCopy()
{
	uint a;
	NoFrameEdit();
	QString BufferI = "";
	if ((HaveDoc) && (doc->ActPage->SelItem.count() != 0))
		{
		Buffer2 = "<SCRIBUSTEXT>";
		PageItem *b = doc->ActPage->SelItem.at(0);
		if ((doc->AppMode == 7) && (b->HasSel))
			{
			Buffer2 += "";
			PageItem *nb = b;
			while (nb != 0)
				{
				if (nb->BackBox != 0)
					nb = nb->BackBox;
				else
					break;
				}
			while (nb != 0)
				{
				for (a = 0; a < nb->Ptext.count(); ++a)
					{
					if (nb->Ptext.at(a)->cselect)
						{
						if (nb->Ptext.at(a)->ch == QChar(13))
							{
							Buffer2 += QChar(5);
							BufferI += QChar(10);
							}
						else if (nb->Ptext.at(a)->ch == QChar(9))
							{
							Buffer2 += QChar(4);
							BufferI += QChar(9);
							}
						else
							{
							Buffer2 += nb->Ptext.at(a)->ch;
							BufferI += nb->Ptext.at(a)->ch;
							}
						Buffer2 += "\t";
						Buffer2 += nb->Ptext.at(a)->cfont+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->csize)+"\t";
						Buffer2 += nb->Ptext.at(a)->ccolor+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cextra)+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cshade)+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cstyle)+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cab)+"\t";
						Buffer2 += nb->Ptext.at(a)->cstroke+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cshade2)+"\t";
						Buffer2 += QString::number(nb->Ptext.at(a)->cscale)+"\n";
						}
					}
				nb = nb->NextBox;
				}
			}
		else
			{
  		ScriXmlDoc *ss = new ScriXmlDoc();
			BufferI = ss->WriteElem(&doc->ActPage->SelItem, doc);
			Buffer2 = BufferI;
			delete ss;
			}
		BuFromApp = true;
		ClipB->setText(BufferI);
		editMenu->setItemEnabled(edid3, 1);
		}
}

void ScribusApp::slotEditPaste()
{
	struct Pti *hg;
	NoFrameEdit();
	if (HaveDoc)
		{
		if (Buffer2.isNull())
			return;
		if (doc->AppMode == 7)
			{
			PageItem *b = doc->ActPage->SelItem.at(0);
			if (Buffer2.startsWith("<SCRIBUSTEXT>"))
				{
				QString Buf = Buffer2.mid(13);
				QTextStream t(&Buf, IO_ReadOnly);
				QString cc;
				while (!t.atEnd())
					{
					cc = t.readLine();
					QStringList wt;
					QStringList::Iterator it;
					wt = QStringList::split("\t", cc);
					it = wt.begin();
					hg = new Pti;
					hg->ch = (*it);
					if (hg->ch == QChar(5))
						hg->ch = QChar(13);
					if (hg->ch == QChar(4))
						hg->ch = QChar(9);
					it++;
					hg->cfont = *it;
					it++;
					hg->csize = (*it).toInt();
					it++;
					hg->ccolor = *it;
					it++;
					hg->cextra = (*it).toInt();
					it++;
					hg->cshade = (*it).toInt();
					hg->cselect = false;
					it++;
					hg->cstyle = (*it).toInt();
					it++;
					hg->cab = (*it).toInt();
					it++;
					if (it == NULL)
						hg->cstroke = "None";
					else
						hg->cstroke = *it;
					it++;
					if (it == NULL)
						hg->cshade2 = 100;
					else
						hg->cshade2 = (*it).toInt();
					it++;
					if (it == NULL)
						hg->cscale = 100;
					else
						hg->cscale = (*it).toInt();
					b->Ptext.insert(b->CPos, hg);
					b->CPos += 1;
					hg->PRot = 0;
					hg->PtransX = 0;
					hg->PtransY = 0;
					}
				}
			else
				{
  			Serializer *ss = new Serializer("");
  			ss->Objekt = Buffer2;
				int st = doc->CurrentABStil;
  			ss->GetText(b, st, doc->Vorlagen[st].Font, doc->Vorlagen[st].FontSize, true);
  			delete ss;
				if (doc->Trenner->AutoCheck)
					doc->Trenner->slotHyphenate(b);
				}
 			if (b->CPos < static_cast<int>(b->Ptext.count())) { b->Dirty = true; }
			doc->ActPage->RefreshItem(b);
			}
		else
			{
			if (Buffer2.startsWith("<SCRIBUSELEM"))
				{
				doc->ActPage->Deselect(true);
				uint ac = doc->ActPage->Items.count();
				slotElemRead(Buffer2, 0, 0, false, true, doc);
				for (uint as = ac; as < doc->ActPage->Items.count(); ++as)
					{
					doc->ActPage->SelectItemNr(as);
					}
				}
			}
		slotDocCh(false);
		}
}

void ScribusApp::SelectAll()
{
	PageItem *b = doc->ActPage->SelItem.at(0);
	PageItem *nb = b;
	while (nb != 0)
		{
		if (nb->BackBox != 0)
			nb = nb->BackBox;
		else
			break;
		}
	while (nb != 0)
		{
//		bool sel = nb->Select;
//		nb->Select = true;
		for (uint a = 0; a < nb->Ptext.count(); ++a)
			{
			nb->Ptext.at(a)->cselect = true;
			nb->HasSel = true;
			nb->Dirty = true;
			}
//		nb->OwnPage->RefreshItem(nb);
//		nb->Select = sel;
		nb = nb->NextBox;
		}
	view->DrawNew();
	EnableTxEdit();
}

void ScribusApp::ClipChange()
{
	QString cc;
#if QT_VERSION  >= 0x030100
	cc = ClipB->text(QClipboard::Clipboard);
	if (cc.isNull())
		cc = ClipB->text(QClipboard::Selection);
#else
	cc = ClipB->text();
#endif
	editMenu->setItemEnabled(edid3, 0);
	if (!cc.isNull())
		{
		if (!BuFromApp)
			Buffer2 = cc;
		BuFromApp = false;
		if (HaveDoc)
			{
			if (cc.startsWith("<SCRIBUSELEM"))
				{
				if (doc->AppMode != 7)
					editMenu->setItemEnabled(edid3, 1);
				}
			else
				{
				if (doc->AppMode == 7)
					editMenu->setItemEnabled(edid3, 1);
				}
			}
		}
}

void ScribusApp::DeleteText()
{
	PageItem *b = doc->ActPage->SelItem.at(0);
	PageItem *nb = b;
	while (nb != 0)
		{
		if (nb->BackBox != 0)
			nb = nb->BackBox;
		else
			break;
		}
	while (nb != 0)
		{
		for (uint a = 0; a < nb->Ptext.count(); ++a)
			{
			DeleteSel(nb);
			nb->Dirty = true;
			nb->CPos = 0;
			}
		nb = nb->NextBox;
		}
//	doc->ActPage->RefreshItem(b);
	view->DrawNew();
	slotDocCh();
}

void ScribusApp::EnableTxEdit()
{
	editMenu->setItemEnabled(edid1, 1);
	editMenu->setItemEnabled(edid2, 1);
	editMenu->setItemEnabled(edid4, 1);
}

void ScribusApp::DisableTxEdit()
{
	editMenu->setItemEnabled(edid1, 0);
	editMenu->setItemEnabled(edid2, 0);
	editMenu->setItemEnabled(edid4, 0);
}

void ScribusApp::slotHelpAbout()
{
	void *mo;
	const char *error;
	typedef About* (*sdem)(QWidget *d);
	sdem demo;
	QString pfad = PREL;
#if defined(__hpux)
  pfad += "/lib/scribus/libs/libabout.sl";
#else
	pfad += "/lib/scribus/libs/libabout.so";
#endif
	mo = dlopen(pfad, RTLD_LAZY);
	if (!mo)
		{
		std::cout << "Can't find Plug-in" << endl;
		return;
		}
	dlerror();
	demo = (sdem)dlsym(mo, "Run");
	if ((error = dlerror()) != NULL)
		{
		std::cout << "Can't find Symbol" << endl;
		dlclose(mo);
		return;
		}
	About* dia = (*demo)(this);
	dia->exec();
	delete dia;
	dlclose(mo);
}

void ScribusApp::slotHelpAboutQt()
{
  QMessageBox::aboutQt(this, tr("About Qt"));
}

void ScribusApp::slotOnlineHelp()
{
	HelpBrowser *dia = new HelpBrowser(this, tr("Scribus Manual"));
	dia->show();
}

void ScribusApp::ToggleTips()
{
  tipsOn = !tipsOn;
  helpMenu->setItemChecked(tip, tipsOn);
  QToolTip::setEnabled(tipsOn);
}

void ScribusApp::SaveText()
{
	LoadEnc = "";
  QString fn = CFileDialog( tr("Save as"), tr("Text Files (*.txt);;All Files(*)"), "", false, false, false, true);
if (!fn.isEmpty())
  	{
    Serializer *se = new Serializer(fn);
    se->PutText(doc->ActPage->SelItem.at(0));
    se->Write(LoadEnc);
    delete se;
  	}
}

void ScribusApp::applyNewMaster(QString name)
{
	Apply_Temp(name, doc->ActPage->PageNr);
	view->DrawNew();
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
	Sepal->Rebuild();
}

void ScribusApp::slotNewPageP(int wo, QString templ)
{
	NoFrameEdit();
	doc->ActPage->Deselect(true);
	doc->UnDoValid = false;
	CanUndo();
	slotNewPage(wo);
	applyNewMaster(templ);
	Sepal->RebuildPage();
}

/** Erzeugt eine neue Seite */
void ScribusApp::slotNewPageM()
{
	int wo, cc;
	NoFrameEdit();
	doc->ActPage->Deselect(true);
	InsPage *dia = new InsPage(this, view, doc->ActPage->PageNr, view->Pages.count(), doc->PageFP);
	if (dia->exec())
		{
		doc->UnDoValid = false;
		CanUndo();
		wo = dia->ActualPage->value();
		switch (dia->Where->currentItem())
			{
			case 0:
				wo -= 1;
				for (cc = 0; cc < dia->NumPages->value(); ++cc)
					{
					slotNewPage(wo);
					if (doc->PageFP)
						{
 						if ((doc->ActPage->PageNr % 2 == 0) && (doc->FirstPageLeft))
							applyNewMaster(dia->Based->currentText());
 						if ((doc->ActPage->PageNr % 2 == 1) && (doc->FirstPageLeft))
							applyNewMaster(dia->Based2->currentText());
 						if ((doc->ActPage->PageNr % 2 == 0) && (!doc->FirstPageLeft))
							applyNewMaster(dia->Based2->currentText());
 						if ((doc->ActPage->PageNr % 2 == 1) && (!doc->FirstPageLeft))
							applyNewMaster(dia->Based->currentText());
						}
					else
						applyNewMaster(dia->Based->currentText());
					wo ++;
					}
				break;
			case 1:
				for (cc = 0; cc < dia->NumPages->value(); ++cc)
					{
					slotNewPage(wo);
					if (doc->PageFP)
						{
 						if ((doc->ActPage->PageNr % 2 == 0) && (doc->FirstPageLeft))
							applyNewMaster(dia->Based->currentText());
 						if ((doc->ActPage->PageNr % 2 == 1) && (doc->FirstPageLeft))
							applyNewMaster(dia->Based2->currentText());
 						if ((doc->ActPage->PageNr % 2 == 0) && (!doc->FirstPageLeft))
							applyNewMaster(dia->Based2->currentText());
 						if ((doc->ActPage->PageNr % 2 == 1) && (!doc->FirstPageLeft))
							applyNewMaster(dia->Based->currentText());
						}
					else
						applyNewMaster(dia->Based->currentText());
					wo ++;
					}
				break;
			case 2:
				for (cc = 0; cc < dia->NumPages->value(); ++cc)
					{
					slotNewPage(view->Pages.count());
					if (doc->PageFP)
						{
 						if ((doc->ActPage->PageNr % 2 == 0) && (doc->FirstPageLeft))
							applyNewMaster(dia->Based->currentText());
 						if ((doc->ActPage->PageNr % 2 == 1) && (doc->FirstPageLeft))
							applyNewMaster(dia->Based2->currentText());
 						if ((doc->ActPage->PageNr % 2 == 0) && (!doc->FirstPageLeft))
							applyNewMaster(dia->Based2->currentText());
 						if ((doc->ActPage->PageNr % 2 == 1) && (!doc->FirstPageLeft))
							applyNewMaster(dia->Based->currentText());
						}
					else
						applyNewMaster(dia->Based->currentText());
					}
				break;
			}
		Sepal->RebuildPage();
		}
	delete dia;
}

void ScribusApp::slotNewPageT(int w)
{
	if (doc->TemplateMode)
		slotNewPage(w);
}

void ScribusApp::slotNewPage(int w)
{
	if ((!doc->loading) && (!doc->TemplateMode))
		Tpal->slotAddPage(w);
	view->addPage(w);
	if (view->Pages.count() > 1)
		{
		pageMenu->setItemEnabled(pgmd, 1);
		pageMenu->setItemEnabled(pgmv, 1);
		}
	if ((!doc->loading) && (!doc->TemplateMode))
		{
		AdjustBM();
		if ((doc->PageAT) && (doc->PageC != 1))
			Tpal->slotAddElement(w, 0);
		}
	connect(doc->ActPage, SIGNAL(Amode(int)), this, SLOT(setAppMode(int)));
	connect(doc->ActPage, SIGNAL(PaintingDone()), this, SLOT(slotSelect()));
	connect(doc->ActPage, SIGNAL(HaveSel(int)), this, SLOT(HaveNewSel(int)));
	connect(doc->ActPage, SIGNAL(DocChanged()), this, SLOT(slotDocCh()));
	connect(doc->ActPage, SIGNAL(ClipPo(double, double)), Npal, SLOT(SetXY(double, double)));
	connect(doc->ActPage, SIGNAL(HavePoint(bool, bool)), Npal, SLOT(HaveNode(bool, bool)));
	connect(doc->ActPage, SIGNAL(PolyOpen()), Npal, SLOT(IsOpen()));
	connect(doc->ActPage, SIGNAL(PStatus(int, uint)), Npal, SLOT(PolyStatus(int, uint)));
	connect(doc->ActPage, SIGNAL(MousePos(double, double)), this, SLOT(ReportMP(double, double)));
	connect(doc->ActPage, SIGNAL(ItemPos(double, double)), Mpal, SLOT(setXY(double, double)));
	connect(doc->ActPage, SIGNAL(ItemGeom(double, double)), Mpal, SLOT(setBH(double, double)));
	connect(doc->ActPage, SIGNAL(SetAngle(double)), Mpal, SLOT(setR(double)));
	connect(doc->ActPage, SIGNAL(ItemRadius(double)), Mpal, SLOT(setRR(double)));
	connect(doc->ActPage, SIGNAL(ItemTextAttr(double)), Mpal, SLOT(setLsp(double)));
	connect(doc->ActPage, SIGNAL(ItemTextCols(int, double)), Mpal, SLOT(setCols(int, double)));
	connect(doc->ActPage, SIGNAL(ItemTextSize(int)), Mpal, SLOT(setSize(int)));
	connect(doc->ActPage, SIGNAL(ItemTextUSval(double)), Mpal, SLOT(setExtra(double)));
	connect(doc->ActPage, SIGNAL(SetLocalValues(double, double, double, double)), Mpal, SLOT(setLvalue(double, double, double, double)));
	connect(doc->ActPage, SIGNAL(SetSizeValue(double)), Mpal, SLOT(setSvalue(double)));
	connect(doc->ActPage, SIGNAL(ItemTextStil(int)), Mpal, SLOT(setStil(int)));
	connect(doc->ActPage, SIGNAL(ItemTextSca(int)), Mpal, SLOT(setTScale(int)));
	connect(doc->ActPage, SIGNAL(ItemTextAbs(int)), Mpal, SLOT(setAli(int)));
	connect(doc->ActPage, SIGNAL(SetLineArt(PenStyle, PenCapStyle, PenJoinStyle)), Mpal, SLOT( setLIvalue(PenStyle, PenCapStyle, PenJoinStyle)));
	connect(doc->ActPage, SIGNAL(ItemFarben(QString, QString, int, int)), this, SLOT(setCSMenu(QString, QString, int, int)));
	connect(doc->ActPage, SIGNAL(ItemFarben(QString, QString, int, int)), Mpal->Cpal, SLOT(setActFarben(QString, QString, int, int)));
	connect(doc->ActPage, SIGNAL(ItemGradient(QString, QString, int, int, int)), Mpal->Cpal, SLOT(setActGradient(QString, QString, int, int, int)));
	connect(doc->ActPage, SIGNAL(ItemTrans(double, double)), Mpal->Cpal, SLOT(setActTrans(double, double)));
	connect(doc->ActPage, SIGNAL(ItemTextFont(QString)), this, SLOT(AdjustFontMenu(QString)));
	connect(doc->ActPage, SIGNAL(ItemTextSize(int)), this, SLOT(setFSizeMenu(int)));
	connect(doc->ActPage, SIGNAL(ItemTextStil(int)), this, SLOT(setStilvalue(int)));
	connect(doc->ActPage, SIGNAL(ItemTextAbs(int)), this, SLOT(setAbsValue(int)));
	connect(doc->ActPage, SIGNAL(ItemTextFarben(QString, QString, int, int)), Mpal, SLOT(setActFarben(QString, QString, int, int)));
	connect(doc->ActPage, SIGNAL(HasTextSel()), this, SLOT(EnableTxEdit()));
	connect(doc->ActPage, SIGNAL(HasNoTextSel()), this, SLOT(DisableTxEdit()));
	connect(doc->ActPage, SIGNAL(CopyItem()), this, SLOT(slotEditCopy()));
	connect(doc->ActPage, SIGNAL(CutItem()), this, SLOT(slotEditCut()));
	connect(doc->ActPage, SIGNAL(LoadPic()), this, SLOT(slotFileOpen()));
	connect(doc->ActPage, SIGNAL(AnnotProps()), this, SLOT(ModifyAnnot()));
	connect(doc->ActPage, SIGNAL(ToScrap(QString)), this, SLOT(PutScrap(QString)));
	connect(doc->ActPage, SIGNAL(UndoAvail()), this, SLOT(CanUndo()));
	connect(doc->ActPage, SIGNAL(EditGuides()), this, SLOT(ManageGuides()));
	connect(doc->ActPage, SIGNAL(LoadElem(QString, int ,int, bool, bool, ScribusDoc *)), this, SLOT(slotElemRead(QString, int, int, bool, bool, ScribusDoc *)));
	connect(doc->ActPage, SIGNAL(AddBM(PageItem *)), this, SLOT(AddBookMark(PageItem *)));
	connect(doc->ActPage, SIGNAL(DelBM(PageItem *)), this, SLOT(DelBookMark(PageItem *)));
	connect(doc->ActPage, SIGNAL(ChBMText(PageItem *)), this, SLOT(BookMarkTxT(PageItem *)));
	connect(doc->ActPage, SIGNAL(NewBMNr(int, int)), BookPal->BView, SLOT(ChangeItem(int, int)));
	connect(doc->ActPage, SIGNAL(RasterPic(bool)), this, SLOT(HaveRaster(bool)));
	connect(doc->ActPage, SIGNAL(EditText()), this, SLOT(slotStoryEditor()));
	connect(doc->ActPage, SIGNAL(DoGroup()), this, SLOT(GroupObj()));
	connect(doc->ActPage, SIGNAL(DoUnGroup()), this, SLOT(UnGroupObj()));
	if (!doc->TemplateMode)
		{
		connect(doc->ActPage, SIGNAL(DelObj(uint, uint)), Tpal, SLOT(slotRemoveElement(uint, uint)));
		connect(doc->ActPage, SIGNAL(AddObj(uint, uint)), Tpal, SLOT(slotAddElement(uint, uint)));
		connect(doc->ActPage, SIGNAL(UpdtObj(uint, uint)), Tpal, SLOT(slotUpdateElement(uint, uint)));
		connect(doc->ActPage, SIGNAL(MoveObj(uint, uint, uint)), Tpal, SLOT(slotMoveElement(uint, uint, uint)));
		}
	slotDocCh(!doc->loading);
}

/** Ansicht absolut zoomen */
void ScribusApp::slotZoomAbs(double z)
{
	doc->Scale = z;
	view->slotDoZoom();
}

void ScribusApp::slotZoomFit()
{
	double dx = (view->width()-50) / (doc->PageB+30);
	double dy = (view->height()-70) / (doc->PageH+30);
	if (dx > dy)
		slotZoomAbs(dy);
	else
		slotZoomAbs(dx);
}

/** Ansicht 20 % */
void ScribusApp::slotZoom20()
{
	slotZoomAbs(0.2*Prefs.DisScale);
}

/** Ansicht 50 % */
void ScribusApp::slotZoom50()
{
	slotZoomAbs(0.5*Prefs.DisScale);
}

/** Ansicht 75 % */
void ScribusApp::slotZoom75()
{
	slotZoomAbs(0.75*Prefs.DisScale);
}

/** Ansicht 100 % */
void ScribusApp::slotZoom100()
{
	slotZoomAbs(1.0*Prefs.DisScale);
}

/** Ansicht 200 % */
void ScribusApp::slotZoom200()
{
	slotZoomAbs(2.0*Prefs.DisScale);
}

void ScribusApp::ToggleMarks()
{
	if (doc->Marks)
	{
		doc->Marks = false;
		viewMenu->changeItem(Markers, tr("Show Margins"));
	}
	else
	{
		doc->Marks = true;
		viewMenu->changeItem(Markers, tr("Hide Margins"));
	}
	view->DrawNew();
}

void ScribusApp::ToggleFrames()
{
	if (doc->ShFrames)
	{
		doc->ShFrames = false;
		viewMenu->changeItem(FrameDr, tr("Show Frames"));
	}
	else
	{
		doc->ShFrames = true;
		viewMenu->changeItem(FrameDr, tr("Hide Frames"));
	}
	view->DrawNew();
}

void ScribusApp::setMpal(bool visible)
{
	if (visible)
		{
 		Mpal->show();
 		Mpal->TabStack->raiseWidget(0);
		}
	else
		{
		Prefs.Mpalx = Mpal->pos().x();
		Prefs.Mpaly = Mpal->pos().y();
 		Mpal->hide();
  	}
 	toolMenu->setItemChecked(viewMpal, visible);
}

void ScribusApp::ToggleMpal()
{
	setMpal(!Mpal->isVisible());
}

void ScribusApp::setTpal(bool visible)
{
	if (visible)
 		Tpal->show();
	else
		{
 		Prefs.Tpalx = Tpal->pos().x();
 		Prefs.Tpaly = Tpal->pos().y();
 		Tpal->close();
  	}
 	toolMenu->setItemChecked(viewTpal, visible);
  }

void ScribusApp::ToggleTpal()
{
 	setTpal(!Tpal->isVisible());
}

void ScribusApp::setBpal(bool visible)
{
	if (visible)
		ScBook->show();
	else
		{
 		Prefs.SCpalx = ScBook->pos().x();
 		Prefs.SCpaly = ScBook->pos().y();
 		Prefs.SCpalw = ScBook->size().width();
 		Prefs.SCpalh = ScBook->size().height();
 		ScBook->close();
	 	}
 	toolMenu->setItemChecked(viewBpal, visible);
}

void ScribusApp::ToggleBpal()
{
	setBpal(!ScBook->isVisible());
}

void ScribusApp::setLpal(bool visible)
{
	if (visible)
		{
 		if (HaveDoc)
 			Lpal->setLayers(&doc->Layers, &doc->ActiveLayer);
 		Lpal->show();
	 	}
	else
		{
 		Prefs.Lpalx = Lpal->pos().x();
 		Prefs.Lpaly = Lpal->pos().y();
 		Lpal->close();
	 	}
 	toolMenu->setItemChecked(viewLpal, visible);
}

void ScribusApp::ToggleLpal()
{
	setLpal(!Lpal->isVisible());
}

void ScribusApp::setSepal(bool visible)
{
	if (visible)
		Sepal->show();
	else
		{
 		Prefs.Sepalx = Sepal->pos().x();
 		Prefs.Sepaly = Sepal->pos().y();
 		Prefs.SepalT = Sepal->TemplList->Thumb;
 		Prefs.SepalN = Sepal->PageView->Namen;
 		Sepal->close();
	 	}
	toolMenu->setItemChecked(viewSepal, visible);
}

void ScribusApp::ToggleSepal()
{
	setSepal(!Sepal->isVisible());
}

void ScribusApp::setBookpal(bool visible)
{
	if (visible)
		BookPal->show();
	else
		{
 		Prefs.Bopalx = BookPal->pos().x();
 		Prefs.Bopaly = BookPal->pos().y();
 		BookPal->hide();
		}
	toolMenu->setItemChecked(viewBopal, visible);
}

void ScribusApp::ToggleBookpal()
{
	setBookpal(!BookPal->isVisible());
}

void ScribusApp::setTools(bool visible)
{
	if (visible)
		{
 		WerkTools->show();
 		WerkTools->Sichtbar = true;
		}
	else
		{
 		WerkTools->hide();
 		WerkTools->Sichtbar = false;
		}
	toolMenu->setItemChecked(viewTools, visible);
}

void ScribusApp::ToggleTools()
{
	setTools(!WerkTools->Sichtbar);
}

void ScribusApp::setPDFTools(bool visible)
{
	if (visible)
		{
 		WerkToolsP->show();
 		WerkToolsP->Sichtbar = true;
		}
	else
		{
 		WerkToolsP->hide();
 		WerkToolsP->Sichtbar = false;
		}
	toolMenu->setItemChecked(viewToolsP, visible);
}

void ScribusApp::TogglePDFTools()
{
	setPDFTools(!WerkToolsP->Sichtbar);
}

void ScribusApp::TogglePics()
{
	uint a, b;
	if (doc->ShowPic)
		{
		viewMenu->changeItem(Bilder, tr("Show Images"));
		doc->ShowPic = false;
		}
	else
		{
		viewMenu->changeItem(Bilder, tr("Hide Images"));
		doc->ShowPic = true;
		}
	for (a=0; a<view->Pages.count(); ++a)
		{
		for (b=0; b<view->Pages.at(a)->Items.count(); ++b)
			{
			if (view->Pages.at(a)->Items.at(b)->PType == 2)
				{
				view->Pages.at(a)->Items.at(b)->PicArt = doc->ShowPic;
				}
			}
		view->Pages.at(a)->update();
		}
}

void ScribusApp::ToggleRaster()
{
	uint a;
	if (doc->Raster)
		{
		viewMenu->changeItem(Ras, tr("Show Grid"));
		doc->Raster = false;
		}
	else
		{
		viewMenu->changeItem(Ras, tr("Hide Grid"));
		doc->Raster = true;
		}
	for (a=0; a<view->Pages.count(); ++a)
		{
		view->Pages.at(a)->update();
		}
}

void ScribusApp::ToggleURaster()
{
	doc->useRaster = !doc->useRaster;
	viewMenu->setItemChecked(uRas, doc->useRaster);
}

void ScribusApp::ToggleGuides()
{
	uint a;
	if (doc->Guides)
		{
		viewMenu->changeItem(Guide, tr("Show Guides"));
		doc->Guides = false;
		}
	else
		{
		viewMenu->changeItem(Guide, tr("Hide Guides"));
		doc->Guides = true;
		}
	for (a=0; a<view->Pages.count(); ++a)
		{
		view->Pages.at(a)->update();
		}
}

void ScribusApp::ToggleUGuides()
{
	doc->SnapGuides = !doc->SnapGuides;
	viewMenu->setItemChecked(uGuide, doc->SnapGuides);
}

void ScribusApp::ToggleFrameEdit()
{
	if (doc->EditClip)
		{
		NoFrameEdit();
		}
	else
		{
		Npal->setDoc(doc);
		Npal->MoveN();
		Npal->HaveNode(false, false);
		Npal->MoveNode->setOn(true);
		Npal->show();
		doc->EditClipMode = 0;
		doc->EditClip = true;
		WerkTools->Select->setEnabled(false);
		WerkTools->Rotiere->setEnabled(false);
		WerkTools->Textedit->setEnabled(false);
		WerkTools->Textedit2->setEnabled(false);
		WerkTools->Zoom->setEnabled(false);
		WerkTools->Texte->setEnabled(false);
		WerkTools->BildB->setEnabled(false);
		WerkTools->Rechteck->setEnabled(false);
		WerkTools->Linien->setEnabled(false);
		WerkTools->Polygon->setEnabled(false);
		WerkTools->KetteEin->setEnabled(false);
		WerkTools->KetteAus->setEnabled(false);
		WerkToolsP->PDFTool->setEnabled(false);
		WerkToolsP->PDFaTool->setEnabled(false);
		ObjMenu->setItemEnabled(Loesch, false);
		if (doc->ActPage->SelItem.count() != 0)
			{
			doc->ActPage->MarkClip(doc->ActPage->SelItem.at(0));
			Npal->PolyStatus(doc->ActPage->SelItem.at(0)->PType, doc->ActPage->SelItem.at(0)->PoLine.size());
			}
		}
	ShapeMenu->setItemChecked(ShapeEdit, doc->EditClip);
}

void ScribusApp::NoFrameEdit()
{
  Prefs.Npalx = Npal->pos().x();
  Prefs.Npaly = Npal->pos().y();
	Npal->hide();
	WerkTools->Select->setEnabled(true);
	WerkTools->Select->setOn(true);
	WerkTools->Zoom->setEnabled(true);
	WerkTools->Texte->setEnabled(true);
	WerkTools->BildB->setEnabled(true);
	WerkTools->Rechteck->setEnabled(true);
	WerkTools->Linien->setEnabled(true);
	WerkTools->Polygon->setEnabled(true);
	WerkToolsP->PDFTool->setEnabled(true);
	WerkToolsP->PDFaTool->setEnabled(true);
	WerkTools->Textedit->setOn(false);
	WerkTools->Textedit2->setOn(false);
	ObjMenu->setItemEnabled(Loesch, true);
	ShapeMenu->setItemChecked(ShapeEdit, false);
	if (HaveDoc)
		{
		doc->EditClip = false;
		if (doc->ActPage->SelItem.count() != 0)
			{
			HaveNewSel(doc->ActPage->SelItem.at(0)->PType);
			doc->ActPage->update();
			}
		else
			HaveNewSel(-1);
		}
}

void ScribusApp::slotSelect()
{
  WerkTools->Select->setOn(true);
	WerkTools->Rotiere->setOn(false);
	WerkTools->Textedit->setOn(false);
	WerkTools->Textedit2->setOn(false);
	WerkTools->Zoom->setOn(false);
	WerkTools->Texte->setOn(false);
	WerkTools->BildB->setOn(false);
	WerkTools->Rechteck->setOn(false);
	WerkTools->Linien->setOn(false);
	WerkTools->Polygon->setOn(false);
	WerkTools->KetteEin->setOn(false);
	WerkTools->KetteAus->setOn(false);
	WerkToolsP->PDFTool->setOn(false);
	WerkToolsP->PDFaTool->setOn(false);
  setAppMode(1);
}

void ScribusApp::ModeFromTB(int m)
{
	if (m == 3)
		{
		slotStoryEditor();
		slotSelect();
		return;
		}
	if (m == 10)
		doc->ElemToLink = doc->ActPage->SelItem.at(0);
	if (doc->AppMode == 13)
		return;
	setAppMode(m);
}

void ScribusApp::setAppMode(int mode)
{
	PageItem *b;
	setActiveWindow();
	if (HaveDoc)
		{
		if (doc->ActPage->SelItem.count() != 0)
			b = doc->ActPage->SelItem.at(0);
		else
			b = 0;
		int oldMode = doc->AppMode;
		doc->AppMode = mode;
		if (oldMode == 7)
			{
			disconnect(doc->CurTimer, SIGNAL(timeout()), doc->ActPage, SLOT(BlinkCurs()));
			doc->CurTimer->stop();
			delete doc->CurTimer;
			editMenu->setItemEnabled(edid4, 0);
			editMenu->setItemEnabled(edid5, 0);
			doc->ActPage->slotDoCurs(false);
			if (b != 0)
				{
				doc->ActPage->RefreshItem(b);
				menuBar()->setItemEnabled(Stm, 1);
				menuBar()->setItemEnabled(Obm, 1);
				}
			}
		if (mode == 7)
			{
			if (b != 0)
				{
				if ((b->PType == 6) || (b->PType == 7) || (b->PType == 8))
					{
					doc->AppMode = 1;
					ToggleFrameEdit();
					return;
					}
				}
			editMenu->setItemEnabled(edid3, 0);
			if (!Buffer2.isNull())
				{
				if (!Buffer2.startsWith("<SCRIBUSELEM"))
					{
					BuFromApp = false;
					editMenu->setItemEnabled(edid3, 1);
					}
				}
  		WerkTools->Select->setOn(false);
			WerkTools->Textedit->setOn(true);
			WerkTools->Textedit2->setOn(false);
			doc->ActPage->slotDoCurs(true);
			menuBar()->setItemEnabled(Obm, 0);
			menuBar()->setItemEnabled(Stm, 0);
			doc->CurTimer = new QTimer(doc->ActPage);
			connect(doc->CurTimer, SIGNAL(timeout()), doc->ActPage, SLOT(BlinkCurs()));
			doc->CurTimer->start(500);
			if (b != 0)
				{
				if (b->HasSel)
					{
					editMenu->setItemEnabled(edid1, 1);
					editMenu->setItemEnabled(edid2, 1);
					editMenu->setItemEnabled(edid4, 1);
					}
				else
					{
					editMenu->setItemEnabled(edid1, 0);
					editMenu->setItemEnabled(edid2, 0);
					editMenu->setItemEnabled(edid4, 0);
					}
				editMenu->setItemEnabled(edid5, 1);
				editMenu->setItemEnabled(Sear, 1);
				doc->ActPage->RefreshItem(b);
				}
			}
		if (mode == 13)
			{
			if (doc->ActPage->SelItem.count() != 0)
				doc->ActPage->Deselect(true);
			}
		if (mode == 6)
			qApp->setOverrideCursor(QCursor(loadIcon("LupeZ.xpm")), true);
		else
			qApp->setOverrideCursor(QCursor(ArrowCursor), true);
		if (mode == 2)
			{
			doc->SubMode = WerkTools->SubMode;
			doc->ShapeValues = WerkTools->ShapeVals;
			doc->ValCount = WerkTools->ValCount;
			}
		else
			doc->SubMode = -1;
		if (mode == 1)
			{
		  WerkTools->Select->setOn(true);
			WerkTools->Rotiere->setOn(false);
			WerkTools->Textedit->setOn(false);
			WerkTools->Textedit2->setOn(false);
			WerkTools->Zoom->setOn(false);
			WerkTools->Texte->setOn(false);
			WerkTools->BildB->setOn(false);
			WerkTools->Rechteck->setOn(false);
			WerkTools->Linien->setOn(false);
			WerkTools->Polygon->setOn(false);
			WerkTools->KetteEin->setOn(false);
			WerkTools->KetteAus->setOn(false);
			WerkToolsP->PDFTool->setOn(false);
			WerkToolsP->PDFaTool->setOn(false);
			}
		}
}

void ScribusApp::Aktiv()
{
	setActiveWindow();
	raise();
}

void ScribusApp::setItemTypeStyle(int id)
{
	int b = 0;
	int a = TypeStyleMenu->indexOf(id);
	TypeStyleMenu->setItemChecked(id, !TypeStyleMenu->isItemChecked(id));
	if (a > 0)
		{
		if (a == 4)
			{
			if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(4)))
				TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(5), false);
			}
		if (a == 5)
			{
			if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(5)))
				TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(4), false);
			}
		if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(0)))
			b = 0;
		if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(1)))
			b |= 8;
		if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(2)))
			b |= 16;
		if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(3)))
			b |= 64;
		if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(4)))
			b |= 1;
		if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(5)))
			b |= 2;
		if (TypeStyleMenu->isItemChecked(TypeStyleMenu->idAt(6)))
			b |= 4;
		}
	setItemHoch(b);
}

void ScribusApp::setStilvalue(int s)
{
	uint a;
	int c = s & 127;
	doc->CurrentStyle = c;
	for (a = 0; a < TypeStyleMenu->count(); ++a)
		{
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(a), false);
		}
	if (c == 0)
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(0), true);
	if (c & 8)
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(1), true);
	if (c & 16)
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(2), true);
	if (c & 64)
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(3), true);
	if (c & 1)
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(4), true);
	if (c & 2)
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(5), true);
	if (c & 4)
		TypeStyleMenu->setItemChecked(TypeStyleMenu->idAt(6), true);
	emit TextStil(s);
}

void ScribusApp::setItemHoch(int h)
{
	if (doc->ActPage->SelItem.count() != 0)
		{
		setActiveWindow();
		doc->CurrentStyle = h;
		setStilvalue(doc->CurrentStyle);
		doc->ActPage->chTyStyle(h);
		slotDocCh();
		}
}

void ScribusApp::AdjustBM()
{
	for (uint a = 0; a < view->Pages.count(); ++a)
		{
		for (uint b = 0; b < view->Pages.at(a)->Items.count(); ++b)
			{
			PageItem* bb = view->Pages.at(a)->Items.at(b);
			if (bb->isBookmark)
				{
				int it = bb->BMnr;
				QListViewItemIterator itn(BookPal->BView);
				for ( ; itn.current(); ++itn)
					{
					BookMItem *ite = (BookMItem*)itn.current();
					if (ite->ItemNr == it)
						{
						ite->Seite = a;
						break;
						}
					}
				}
			}
		}
	StoreBookmarks();
}

void ScribusApp::DeletePage2(int pg)
{
	PageItem* ite;
	NoFrameEdit();
	if (view->Pages.count() == 1)
		return;
	if (!doc->TemplateMode)
		disconnect(doc->ActPage, SIGNAL(DelObj(uint, uint)), Tpal, SLOT(slotRemoveElement(uint, uint)));
	view->Pages.at(pg)->SelItem.clear();
	for (uint d = 0; d < view->Pages.at(pg)->Items.count(); ++d)
		{
		ite = view->Pages.at(pg)->Items.at(d);
		if (ite->isBookmark)
			DelBookMark(ite);
		if (ite->PType == 4)
			view->Pages.at(pg)->SelItem.append(ite);
		}
	if (view->Pages.at(pg)->SelItem.count() != 0)
		view->Pages.at(pg)->DeleteItem();
	view->delPage(pg);
	AdjustBM();
	if (!doc->TemplateMode)
		connect(doc->ActPage, SIGNAL(DelObj(uint, uint)), Tpal, SLOT(slotRemoveElement(uint, uint)));
	view->reformPages();
	doc->OpenNodes.clear();
	Tpal->BuildTree(view);
	if (view->Pages.count() == 1)
		{
		pageMenu->setItemEnabled(pgmd, 0);
		pageMenu->setItemEnabled(pgmv, 0);
		}
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
	Sepal->RebuildPage();
}

void ScribusApp::DeletePage()
{
	int a, pg;
	PageItem* ite;
	NoFrameEdit();
	DelPages *dia = new DelPages(this, doc->ActPage->PageNr+1, view->Pages.count());
	if (dia->exec())
		{
		if (!doc->TemplateMode)
			disconnect(doc->ActPage, SIGNAL(DelObj(uint, uint)), Tpal, SLOT(slotRemoveElement(uint, uint)));
		pg = dia->FromPage->value()-1;
		for (a = pg; a < dia->ToPage->value(); ++a)
			{
			view->Pages.at(pg)->SelItem.clear();
			for (uint d = 0; d < view->Pages.at(pg)->Items.count(); ++d)
				{
				ite = view->Pages.at(pg)->Items.at(d);
				if (ite->isBookmark)
					DelBookMark(ite);
				if (ite->PType == 4)
					view->Pages.at(pg)->SelItem.append(ite);
				}
			if (view->Pages.at(pg)->SelItem.count() != 0)
				view->Pages.at(pg)->DeleteItem();
			view->delPage(pg);
			AdjustBM();
			}
		if (!doc->TemplateMode)
			connect(doc->ActPage, SIGNAL(DelObj(uint, uint)), Tpal, SLOT(slotRemoveElement(uint, uint)));
		view->reformPages();
		doc->OpenNodes.clear();
		Tpal->BuildTree(view);
		if (view->Pages.count() == 1)
			{
			pageMenu->setItemEnabled(pgmd, 0);
			pageMenu->setItemEnabled(pgmv, 0);
			}
		slotDocCh();
		doc->UnDoValid = false;
		CanUndo();
		Sepal->RebuildPage();
		}
	delete dia;
}

void ScribusApp::MovePage()
{
	NoFrameEdit();
	MovePages *dia = new MovePages(this, doc->ActPage->PageNr+1, view->Pages.count(), true);
	if (dia->exec())
		{
		doc->OpenNodes = Tpal->buildReopenVals();
		int from = dia->FromPage->value();
		int to = dia->ToPage->value();
		int wie = dia->Where->currentItem();
		int wo = dia->ActualPage->value();
		if (from != wo)
			view->movePage(from-1, to, wo-1, wie);
		slotDocCh();
		doc->UnDoValid = false;
		CanUndo();
		AdjustBM();
		Sepal->RebuildPage();
		Tpal->BuildTree(view);
		Tpal->reopenTree(doc->OpenNodes);
		}
	delete dia;
}

void ScribusApp::CopyPage()
{
	NoFrameEdit();
	MovePages *dia = new MovePages(this, doc->ActPage->PageNr+1, view->Pages.count(), false);
	if (dia->exec())
		{
		doc->loading = true;
		Page* from = view->Pages.at(dia->FromPage->value()-1);
		int wo = dia->ActualPage->value();
		switch (dia->Where->currentItem())
			{
			case 0:
				slotNewPage(wo-1);
				break;
			case 1:
				slotNewPage(wo);
				break;
			case 2:
				slotNewPage(view->Pages.count());
				break;
			}
		Page* Ziel = doc->ActPage;
		for (uint ite = 0; ite < from->Items.count(); ++ite)
			{
			CopyPageItem(&Buffer, from->Items.at(ite));
			Ziel->PasteItem(&Buffer, true, true);
			if (from->Items.at(ite)->isBookmark)
				AddBookMark(Ziel->Items.at(Ziel->Items.count()-1));
			}
		Ziel->MPageNam = from->MPageNam;
		Ziel->Deselect(true);
		doc->loading = false;
		view->DrawNew();
		slotDocCh();
		doc->UnDoValid = false;
		CanUndo();
		Sepal->RebuildPage();
		Tpal->BuildTree(view);
		AdjustBM();
		}
	delete dia;
}

void ScribusApp::setItemFont2(int id)
{
	disconnect(FontMenu, SIGNAL(activated(int)), this, SLOT(setItemFont(int)));
	SetNewFont(FontSub->text(id));
	connect(FontMenu, SIGNAL(activated(int)), this, SLOT(setItemFont(int)));
}

void ScribusApp::setItemFont(int id)
{
	QString nf;
	int a = FontMenu->indexOf(id);
	if (a == 1)
		return;
	disconnect(FontMenu, SIGNAL(activated(int)), this, SLOT(setItemFont(int)));
	nf = FontID[id];
	SetNewFont(nf);
	connect(FontMenu, SIGNAL(activated(int)), this, SLOT(setItemFont(int)));
}

void ScribusApp::SetNewFont(QString nf)
{
	Aktiv();
	int a;
	if (!doc->UsedFonts.contains(nf))
		{
		doc->AddFont(nf, Prefs.AvailFonts[nf]->Font);
		a = FontMenu->insertItem(new FmItem(nf, Prefs.AvailFonts[nf]->Font));
		FontID.insert(a, Prefs.AvailFonts[nf]->SCName);
		}
	AdjustFontMenu(nf);
	doc->ActPage->ItemFont(nf);
	doc->CurrFont = nf;
	slotDocCh();
}

void ScribusApp::AdjustFontMenu(QString nf)
{
	QString df;
	FontSub->setCurrentText(nf);
	Mpal->Fonts->setCurrentText(nf);
	for (uint a = 2; a < FontMenu->count(); ++a)
		{
		df = FontID[FontMenu->idAt(a)];
		if (df == nf)
			FontMenu->setItemChecked(FontMenu->idAt(a), true);
		else
			FontMenu->setItemChecked(FontMenu->idAt(a), false);
		}
}

void ScribusApp::setItemFSize(int id)
{
	int c = SizeTMenu->indexOf(id);
	bool ok = false;
	if (c > 0)
		{
		c = SizeTMenu->text(id).left(2).toInt() * 10;
		doc->ActPage->chFSize(c);
		}
	else
		{
    Query* dia = new Query(this, "New", 1, 0, tr("Size:"), tr("Size"));
    if (dia->exec())
    	{
			c = qRound(dia->Answer->text().toDouble(&ok) * 10);
			if ((ok) && (c < 10250) && (c > 0))
				doc->ActPage->chFSize(c);
			delete dia;
     	}
		}
	Mpal->setSize(c);
	slotDocCh();
}

void ScribusApp::setFSizeMenu(int size)
{
	for (uint a = 0; a < SizeTMenu->count(); ++a)
		{
		SizeTMenu->setItemChecked(SizeTMenu->idAt(a), false);
		if (SizeTMenu->text(SizeTMenu->idAt(a)).left(2).toInt() == size / 10)
			{
			SizeTMenu->setItemChecked(SizeTMenu->idAt(a), true);
			}
		}
}

void ScribusApp::setItemFarbe(int id)
{
 	if (doc->ActPage->SelItem.count() != 0)
		{
 		PageItem *b = doc->ActPage->SelItem.at(0);
		if ((b->PType == 4) || (b->PType == 8))
			doc->ActPage->ItemTextBrush(ColorMenC->text(id));
		else
			doc->ActPage->ItemBrush(ColorMenC->text(id));
		}
	slotDocCh();
}

void ScribusApp::setItemShade(int id)
{
	int c = ShadeMenu->indexOf(id);
	uint a;
	bool ok = false;
	for (a = 0; a < ShadeMenu->count(); ++a)
		{
		ShadeMenu->setItemChecked(ShadeMenu->idAt(a), false);
		}
	ShadeMenu->setItemChecked(id, true);
 	if (doc->ActPage->SelItem.count() != 0)
		{
 		PageItem *b = doc->ActPage->SelItem.at(0);
		if (c > 0)
			{
			if ((b->PType == 4) || (b->PType == 8))
				doc->ActPage->ItemTextBrushS((c-1) * 10);
			else
				doc->ActPage->ItemBrushShade((c-1) * 10);
			}
		else
			{
    	Query* dia = new Query(this, "New", 1, 0, tr("Shade:"), tr("Shade"));
    	if (dia->exec())
    		{
				c = dia->Answer->text().toInt(&ok);
				if (ok)
					{
					if ((b->PType == 4) || (b->PType == 8))
						doc->ActPage->ItemTextBrushS(c);
					else
						doc->ActPage->ItemBrushShade(c);
					}
				delete dia;
     		}
			}
		}
	slotDocCh();
}

void ScribusApp::setCSMenu(QString k, QString l, int lk , int ls)
{
	uint a;
	QString la;
	int lb;
	PageItem *b;
	if (doc->ActPage->SelItem.count() != 0)
		{
		b = doc->ActPage->SelItem.at(0);
		if ((b->PType == 4) || (b->PType == 8))
			{
			if ((doc->AppMode == 7) && (b->Ptext.count() != 0))
				{
				la = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->ccolor;
				lb = b->Ptext.at(QMIN(b->CPos, static_cast<int>(b->Ptext.count()-1)))->cshade;
				}
			else
				{
				la = b->TxtFill;
				lb = b->ShTxtFill;
				}
			}
		else
			{
			la = l;
			lb = ls;
			}
		}
	else
		{
		la = l;
		lb = ls;
		}
	if (la == "None")
		la = tr("None");
	for (a = 0; a < static_cast<uint>(ColorMenC->count()); ++a)
		{
		if (ColorMenC->text(a) == la)
			ColorMenC->setCurrentItem(a);
		}
	for (a = 0; a < ShadeMenu->count(); ++a)
		{
		ShadeMenu->setItemChecked(ShadeMenu->idAt(a), false);
		}
	ShadeMenu->setItemChecked(ShadeMenu->idAt(lb/10+1), true);
}

void ScribusApp::slotEditLineStyles()
{
	PageItem* ite;
	if (HaveDoc)
		{
		LineFormate *dia = new LineFormate(this, doc);
		if (dia->exec())
			{
			doc->MLineStyles = dia->TempStyles;
			for (uint c = 0; c < view->DocPages.count(); ++c)
				{
				for (uint d = 0; d < view->DocPages.at(c)->Items.count(); ++d)
					{
					ite = view->DocPages.at(c)->Items.at(d);
					if (!doc->MLineStyles.contains(ite->NamedLStyle))
						ite->NamedLStyle = "";
					}
				}
			for (uint c1 = 0; c1 < view->MasterPages.count(); ++c1)
				{
				for (uint d1 = 0; d1 < view->MasterPages.at(c1)->Items.count(); ++d1)
					{
					ite = view->MasterPages.at(c1)->Items.at(d1);
					if (!doc->MLineStyles.contains(ite->NamedLStyle))
						ite->NamedLStyle = "";
					}
				}
			Mpal->SetLineFormats(doc);
			view->DrawNew();
			}
		delete dia;
		}
}

void ScribusApp::slotEditStyles()
{
	QValueList<uint> ers;
	QString nn;
	PageItem* ite;
	bool ff;
	uint nr;
	ers.clear();
	if (HaveDoc)
		{
		StilFormate *dia = new StilFormate(this, doc, &Prefs);
		if (dia->exec())
			{
			for (uint a=0; a<doc->Vorlagen.count(); ++a)
				{
				ff = false;
				nn = doc->Vorlagen[a].Vname;
				for (uint b=0; b<dia->TempVorl.count(); ++b)
					{
					if (nn == dia->TempVorl[b].Vname)
						{
						nr = b;
						ff = true;
						break;
						}
					}
				if (ff)
					ers.append(nr);
				else
					ers.append(0);
				}
			doc->Vorlagen = dia->TempVorl;
			for (uint c=0; c<view->DocPages.count(); ++c)
				{
				for (uint d=0; d<view->DocPages.at(c)->Items.count(); ++d)
					{
					ite = view->DocPages.at(c)->Items.at(d);
					if (ite->PType == 4)
						{
						for (uint e=0; e<ite->Ptext.count(); ++e)
							{
							if (ite->Ptext.at(e)->cab > 4)
								ite->Ptext.at(e)->cab = ers[ite->Ptext.at(e)->cab];
							if (doc->Vorlagen[ite->Ptext.at(e)->cab].Font != "")
								{
								ite->Ptext.at(e)->cfont = doc->Vorlagen[ite->Ptext.at(e)->cab].Font;
								ite->Ptext.at(e)->csize = doc->Vorlagen[ite->Ptext.at(e)->cab].FontSize;
								ite->Ptext.at(e)->cstyle &= ~127;
								ite->Ptext.at(e)->cstyle |= doc->Vorlagen[ite->Ptext.at(e)->cab].FontEffect;
								ite->Ptext.at(e)->ccolor = doc->Vorlagen[ite->Ptext.at(e)->cab].FColor;
								ite->Ptext.at(e)->cshade = doc->Vorlagen[ite->Ptext.at(e)->cab].FShade;
								ite->Ptext.at(e)->cstroke = doc->Vorlagen[ite->Ptext.at(e)->cab].SColor;
								ite->Ptext.at(e)->cshade2 = doc->Vorlagen[ite->Ptext.at(e)->cab].SShade;
								}
							else
								{
								ite->Ptext.at(e)->ccolor = ite->TxtFill;
								ite->Ptext.at(e)->cshade = ite->ShTxtFill;
								ite->Ptext.at(e)->cstroke = ite->TxtStroke;
								ite->Ptext.at(e)->cshade2 = ite->ShTxtStroke;
								ite->Ptext.at(e)->csize = ite->ISize;
								ite->Ptext.at(e)->cstyle &= ~127;
								ite->Ptext.at(e)->cstyle |= doc->CurrentStyle;
								}
							}
						}
					}
				}
			for (uint c=0; c<view->MasterPages.count(); ++c)
				{
				for (uint d=0; d<view->MasterPages.at(c)->Items.count(); ++d)
					{
					ite = view->MasterPages.at(c)->Items.at(d);
					if (ite->PType == 4)
						{
						for (uint e=0; e<ite->Ptext.count(); ++e)
							{
							if (ite->Ptext.at(e)->cab > 4)
								ite->Ptext.at(e)->cab = ers[ite->Ptext.at(e)->cab];
							if (doc->Vorlagen[ite->Ptext.at(e)->cab].Font != "")
								{
								ite->Ptext.at(e)->cfont = doc->Vorlagen[ite->Ptext.at(e)->cab].Font;
								ite->Ptext.at(e)->csize = doc->Vorlagen[ite->Ptext.at(e)->cab].FontSize;
								ite->Ptext.at(e)->cstyle &= ~127;
								ite->Ptext.at(e)->cstyle |= doc->Vorlagen[ite->Ptext.at(e)->cab].FontEffect;
								ite->Ptext.at(e)->ccolor = doc->Vorlagen[ite->Ptext.at(e)->cab].FColor;
								ite->Ptext.at(e)->cshade = doc->Vorlagen[ite->Ptext.at(e)->cab].FShade;
								ite->Ptext.at(e)->cstroke = doc->Vorlagen[ite->Ptext.at(e)->cab].SColor;
								ite->Ptext.at(e)->cshade2 = doc->Vorlagen[ite->Ptext.at(e)->cab].SShade;
								}
							else
								{
								ite->Ptext.at(e)->ccolor = ite->TxtFill;
								ite->Ptext.at(e)->cshade = ite->ShTxtFill;
								ite->Ptext.at(e)->cstroke = ite->TxtStroke;
								ite->Ptext.at(e)->cshade2 = ite->ShTxtStroke;
								ite->Ptext.at(e)->csize = ite->ISize;
								ite->Ptext.at(e)->cstyle &= ~127;
								ite->Ptext.at(e)->cstyle |= doc->CurrentStyle;
								}
							}
						}
					}
				}
			for (uint a=0; a<doc->Vorlagen.count(); ++a)
				{
				if (doc->Vorlagen[a].Font != "")
					{
					QString nf = doc->Vorlagen[a].Font;
					if (!doc->UsedFonts.contains(nf))
						{
						doc->AddFont(nf, Prefs.AvailFonts[nf]->Font);
						int ff = FontMenu->insertItem(new FmItem(nf, Prefs.AvailFonts[nf]->Font));
						FontID.insert(ff, Prefs.AvailFonts[nf]->SCName);
						}
					}
				}
			Mpal->Spal->updateFList();
			view->DrawNew();
			slotDocCh();
			}
		delete dia;
		}
}

void ScribusApp::setItemTextAli(int id)
{
	int a = AliMenu->indexOf(id);
	setNewAbStyle(a);
}

void ScribusApp::setNewAbStyle(int a)
{
	setActiveWindow();
	if (HaveDoc)
		{
		doc->ActPage->SetAbStyle(a);
		doc->CurrentABStil = a;
		Mpal->setAli(a);
		slotDocCh();
		}
}

void ScribusApp::setAbsValue(int a)
{
	doc->CurrentABStil = a;
	Mpal->setAli(a);
	for (int b = 0; b < 5; ++b)
		{
		AliMenu->setItemChecked(AliMenu->idAt(b), false);
		}
	if (a < 5)
		{
		Mpal->Spal->setCurrentItem(0);
		AliMenu->setItemChecked(AliMenu->idAt(a), true);
		}
	else
		Mpal->Spal->setCurrentItem(a-4);
}

void ScribusApp::slotEditColors()
{
	int a;
	uint b, c, d;
	CListe edc;
	QMap<QString,QString> ers;
	PageItem *ite;
	if (HaveDoc)
		{
		edc = doc->PageColors;
		}
	else
		{
		edc = Prefs.DColors;
		}
	Farbmanager* dia = new Farbmanager(this, edc, HaveDoc, Prefs.DColorSet, Prefs.CustomColorSets);
	if (dia->exec())
		{
		if (HaveDoc)
			{
			slotDocCh();
			doc->PageColors = dia->EditColors;
			Mpal->Cpal->SetColors(doc->PageColors);
			Mpal->updateCList();
			CListe::Iterator it;
			ColorMenC->clear();
			QPixmap pm = QPixmap(15, 15);
			a = 0;
			ColorMenC->insertItem( tr("None"));
			for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
				{
				pm.fill(doc->PageColors[it.key()].getRGBColor());
				ColorMenC->insertItem(pm, it.key());
				if (it.key() == doc->Dbrush)
					ColorMenC->setCurrentItem(a);
				a++;
				}
			ers = dia->Ersatzliste;
			if (!ers.isEmpty())
				{
				if (!ers.isEmpty())
					{
					QMap<QString,QString>::Iterator it;
					for (it = ers.begin(); it != ers.end(); ++it)
						{
						if (it.key() == doc->CurrTextFill)
							doc->CurrTextFill = it.data();
						if (it.key() == doc->CurrTextStroke)
							doc->CurrTextStroke = it.data();
						for (b=0; b<view->DocPages.count(); ++b)
							{
							for (c=0; c<view->DocPages.at(b)->Items.count(); ++c)
								{
								ite = view->DocPages.at(b)->Items.at(c);
								if ((ite->PType == 4) || (ite->PType == 8))
									{
									for (d=0; d<ite->Ptext.count(); ++d)
										{
										if (it.key() == ite->Ptext.at(d)->ccolor)
											ite->Ptext.at(d)->ccolor = it.data();
										if (it.key() == ite->Ptext.at(d)->cstroke)
											ite->Ptext.at(d)->cstroke = it.data();
										}
									}
								if (it.key() == ite->Pcolor)
									ite->Pcolor = it.data();
								if (it.key() == ite->Pcolor2)
									ite->Pcolor2 = it.data();
								if (it.key() == ite->GrColor)
									ite->GrColor = it.data();
								if (it.key() == ite->GrColor2)
									ite->GrColor2 = it.data();
								view->DocPages.at(b)->AdjItemGradient(ite, ite->GrType, ite->GrColor2, ite->GrShade2, ite->GrColor, ite->GrShade);
								}
							}
						}
					for (it = ers.begin(); it != ers.end(); ++it)
						{
						for (b=0; b<view->MasterPages.count(); ++b)
							{
							for (c=0; c<view->MasterPages.at(b)->Items.count(); ++c)
								{
								ite = view->MasterPages.at(b)->Items.at(c);
								if ((ite->PType == 4) || (ite->PType == 8))
									{
									for (d=0; d<ite->Ptext.count(); ++d)
										{
										if (it.key() == ite->Ptext.at(d)->ccolor)
											ite->Ptext.at(d)->ccolor = it.data();
										if (it.key() == ite->Ptext.at(d)->cstroke)
											ite->Ptext.at(d)->cstroke = it.data();
										}
									}
								if (it.key() == ite->Pcolor)
									ite->Pcolor = it.data();
								if (it.key() == ite->Pcolor2)
									ite->Pcolor2 = it.data();
								if (it.key() == ite->GrColor)
									ite->GrColor = it.data();
								if (it.key() == ite->GrColor2)
									ite->GrColor2 = it.data();
								view->MasterPages.at(b)->AdjItemGradient(ite, ite->GrType, ite->GrColor2, ite->GrShade2, ite->GrColor, ite->GrShade);
								}
							}
						}
					}
				}
			view->DrawNew();
			}
		else
			{
			Prefs.DColors = dia->EditColors;
			Prefs.DColorSet = dia->LoadColSet->text();
			Prefs.CustomColorSets = dia->CColSet;
			Mpal->Cpal->SetColors(Prefs.DColors);
			}
		}
	delete dia;
}

void ScribusApp::setPenFarbe(QString farbe)
{
	setActiveWindow();
	if (HaveDoc)
		{
		doc->ActPage->ItemPen(farbe);
		slotDocCh();
		}
}

void ScribusApp::setPenShade(int sh)
{
	setActiveWindow();
	if (HaveDoc)
		{
		doc->ActPage->ItemPenShade(sh);
		slotDocCh();
		}
}

void ScribusApp::setBrushFarbe(QString farbe)
{
	setActiveWindow();
	if (HaveDoc)
		{
		doc->ActPage->ItemBrush(farbe);
		slotDocCh();
		}
}

void ScribusApp::setBrushShade(int sh)
{
	setActiveWindow();
	if (HaveDoc)
		{
		doc->ActPage->ItemBrushShade(sh);
		slotDocCh();
		}
}

void ScribusApp::setGradFill(int typ, QString col1, int sh1, QString col2, int sh2)
{
	setActiveWindow();
	if (HaveDoc)
		{
		doc->ActPage->ItemGradFill(typ, col1, sh1, col2, sh2);
		slotDocCh();
		}
}

void ScribusApp::GetBrushPen()
{
	setActiveWindow();
	if (HaveDoc)
		{
		doc->ActPage->QueryFarben();
		slotDocCh();
		}
}

void ScribusApp::MakeFrame(int f, int c, double *vals)
{
	PageItem *b = doc->ActPage->SelItem.at(0);
	switch (f)
		{
		case 0:
			doc->ActPage->SetRectFrame(b);
			break;
		case 1:
			doc->ActPage->SetOvalFrame(b);
			break;
		default:
			doc->ActPage->SetFrameShape(b, c, vals);
			break;
		}
	doc->ActPage->RefreshItem(b);
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::DeleteObjekt()
{
	if (!doc->EditClip)
		doc->ActPage->DeleteItem();
}

void ScribusApp::Objekt2Back()
{
	doc->ActPage->ToBack();
}

void ScribusApp::Objekt2Front()
{
	doc->ActPage->ToFront();
}

void ScribusApp::ObjektRaise()
{
	doc->ActPage->RaiseItem();
}

void ScribusApp::ObjektLower()
{
	doc->ActPage->LowerItem();
}

void ScribusApp::ObjektDup()
{
	slotEditCopy();
	doc->ActPage->Deselect(true);
	slotEditPaste();
	for (uint b=0; b<doc->ActPage->SelItem.count(); ++b)
		{
		doc->ActPage->SelItem.at(b)->Locked = false;
		doc->ActPage->MoveItem(DispX, DispY, doc->ActPage->SelItem.at(b));
		}
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::ObjektDupM()
{
	NoFrameEdit();
	Mdup *dia = new Mdup(this, DispX * UmReFaktor, DispY * UmReFaktor, doc->Einheit);
	if (dia->exec())
		{
		int anz = dia->Ncopies->value();
		double dH = dia->ShiftH->value() / UmReFaktor;
		double dV = dia->ShiftV->value() / UmReFaktor;
		double dH2 = dH;
		double dV2 = dV;
		int a;
		if (anz>0)
			{
			slotEditCopy();
			doc->ActPage->Deselect(true);
			for (a=0; a<anz; ++a)
				{
				slotEditPaste();
				for (uint b=0; b<doc->ActPage->SelItem.count(); ++b)
					{
					doc->ActPage->SelItem.at(b)->Locked = false;
					doc->ActPage->MoveItem(dH2, dV2, doc->ActPage->SelItem.at(b));
					}
				dH2 += dH;
				dV2 += dV;
				}
			DispX = dH;
			DispY = dV;
			slotDocCh();
			doc->UnDoValid = false;
			CanUndo();
			doc->ActPage->Deselect(true);
			}
		}
	delete dia;
}

void ScribusApp::SelectFromOutl(int Page, int Item)
{
	NoFrameEdit();
	setActiveWindow();
	doc->ActPage->Deselect(true);
	view->GotoPage(Page);
	doc->ActPage->SelectItemNr(Item);
	if (doc->ActPage->SelItem.count() != 0)
		{
		PageItem *b = doc->ActPage->SelItem.at(0);
		view->SetCCPo(static_cast<int>(b->Xpos + b->Width/2), static_cast<int>(b->Ypos + b->Height/2));
		}
}

void ScribusApp::SelectFromOutlS(int Page)
{
	NoFrameEdit();
	setActiveWindow();
	doc->ActPage->Deselect(true);
	view->GotoPage(Page);
}

void ScribusApp::InfoDoc()
{
	DocInfos *dia = new DocInfos(this, doc->DocAutor, doc->DocTitel, doc->DocComments, doc->DocKeyWords);
	if (dia->exec())
		{
		doc->DocAutor = dia->AutorInfo->text();
		doc->DocTitel = dia->TitelInfo->text();
		doc->DocComments = dia->MultiLineEdit1->text();
		doc->DocKeyWords = dia->MultiLineEdit2->text();
		slotDocCh();
		}
	delete dia;
}

void ScribusApp::ObjektAlign()
{
	double xdp, ydp;
	bool xa, ya, Vth, Vtv;
	int xart, yart, ein;
	if (HaveDoc)
		ein = doc->Einheit;
	else
		ein = Prefs.Einheit;
	NoFrameEdit();
	Align *dia = new Align(this, doc->ActPage->SelItem.count(), ein);
	connect(dia, SIGNAL(ApplyDist(bool, bool, bool, bool, double, double, int, int)),
	        this, SLOT(DoAlign(bool, bool, bool, bool, double, double, int, int)));
	if (dia->exec())
		{
		xdp = dia->AHor->value() / UmReFaktor;
		xa = (dia->CheckH->isChecked() || dia->VerteilenH->isChecked());
		ydp = dia->AVert->value() / UmReFaktor;
		ya = (dia->CheckV->isChecked() || dia->VerteilenV->isChecked());
		xart = dia->VartH->currentItem();
		yart = dia->VartV->currentItem();
		Vth = dia->VerteilenH->isChecked();
		Vtv = dia->VerteilenV->isChecked();
		doc->ActPage->AlignObj(xa, ya, Vth, Vtv, xdp, ydp, xart, yart);
		slotDocCh();
		doc->UnDoValid = false;
		CanUndo();
		}
	delete dia;
}

void ScribusApp::DoAlign(bool xa, bool ya, bool Vth, bool Vtv, double xdp, double ydp, int xart, int yart)
{
	doc->ActPage->AlignObj(xa, ya, Vth, Vtv, xdp, ydp, xart, yart);
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::BuildFontMenu()
{
	FontID.clear();
	FontMenu->clear();
	int a;
	QString b = " ";
	SCFontsIterator it(Prefs.AvailFonts);
    FontSub = new FontCombo(0, &Prefs);
	FontMenu->insertItem(FontSub);
    connect(FontSub, SIGNAL(activated(int)), this, SLOT(setItemFont2(int)));
	FontMenu->insertSeparator();
	if (!HaveDoc)
		{
		it.toFirst();
		a = FontMenu->insertItem(new FmItem(it.currentKey(), it.current()->Font));
		FontMenu->setItemChecked(a, true);
		FontID.insert(a, it.current()->SCName);
		}
	else
		{
		QMap<QString,QFont>::Iterator it3;
		for (it3 = doc->UsedFonts.begin(); it3 != doc->UsedFonts.end(); ++it3)
			{
			a = FontMenu->insertItem(new FmItem(it3.key(), it3.data()));
			if (it3.key() == doc->Dfont)
				FontMenu->setItemChecked(a, true);
			FontID.insert(a, it3.key());
			}
		}
	connect(FontMenu, SIGNAL(activated(int)), this, SLOT(setItemFont(int)));
}

void ScribusApp::GetAllFonts()
{
	Prefs.AvailFonts.GetFonts(PrefsPfad);
	if (Prefs.AvailFonts.isEmpty())
		NoFonts = true;
}

void ScribusApp::slotFontOrg()
{
	uint a;
	FontPrefs *dia = new FontPrefs(this, Prefs.AvailFonts, HaveDoc, &Prefs, PrefsPfad);
	connect(dia, SIGNAL(ReReadPrefs()), this, SLOT(ReadPrefs()));
	if (dia->exec())
		{
		a = 0;
		SCFontsIterator it(Prefs.AvailFonts);
		for ( ; it.current() ; ++it)
			{
			it.current()->EmbedPS = dia->FlagsPS.at(a)->isChecked();
			it.current()->UseFont = dia->FlagsUse.at(a)->isChecked();
			it.current()->Subset = dia->FlagsSub.at(a)->isChecked();
			a++;
			}
		a = 0;
		QMap<QString,QString>::Iterator itfsu;
		Prefs.GFontSub.clear();
		for (itfsu = dia->RList.begin(); itfsu != dia->RList.end(); ++itfsu)
			{
			Prefs.GFontSub[itfsu.key()] = dia->FlagsRepl.at(a)->currentText();
			a++;
			}
		}
	FontSub->RebuildList(&Prefs);
	Mpal->Fonts->RebuildList(&Prefs);
	disconnect(dia, SIGNAL(ReReadPrefs()), this, SLOT(ReadPrefs()));
	delete dia;
}

void ScribusApp::slotPrefsOrg()
{
	void *mo;
	char *error;
	bool zChange = false;
	typedef Preferences* (*sdem)(QWidget *d, preV *Vor);
	sdem demo;
	QString pfad = PREL;
#if defined(__hpux)
	pfad += "/lib/scribus/libs/libpreferences.sl";
#else
	pfad += "/lib/scribus/libs/libpreferences.so";
#endif
	mo = dlopen(pfad, RTLD_LAZY);
	if (!mo)
		{
		std::cout << "Can't find Plug-in" << endl;
		return;
		}
	dlerror();
	demo = (sdem)dlsym(mo, "Run");
	if ((error = dlerror()) != NULL)
		{
		std::cout << "Can't find Symbol" << endl;
		dlclose(mo);
		return;
		}
	Preferences *dia = (*demo)(this, &Prefs);
	if (dia->exec())
		{
		Prefs.KeyActions = dia->KKC;
		SetShortCut();
		Prefs.AppFontSize = dia->GFsize->value();
		Prefs.Wheelval = dia->SpinBox3->value();
		Prefs.RecentDCount = dia->Recen->value();
		Prefs.DocDir = dia->Docs->text();
		DocDir = Prefs.DocDir;
		Prefs.ProfileDir = dia->ProPfad->text();
		Prefs.ScriptDir = dia->ScriptPfad->text();
		GetCMSProfiles();
		switch (dia->PreviewSize->currentItem())
			{
			case 0:
				Prefs.PSize = 40;
				break;
			case 1:
				Prefs.PSize = 60;
				break;
			case 2:
				Prefs.PSize = 80;
				break;
			}
		Prefs.SaveAtQ = dia->SaveAtQuit->isChecked();
		ScBook->BibWin->RebuildView();
		ScBook->AdjustMenu();
		if (Prefs.GUI != dia->GUICombo->currentText())
			{
			Prefs.GUI = dia->GUICombo->currentText();
    	qApp->setStyle(QStyleFactory::create(Prefs.GUI));
			}
		QFont apf = qApp->font();
		apf.setPointSize(Prefs.AppFontSize);
		qApp->setFont(apf,true);
		PolyC = dia->T6_Ecken->value();
		PolyF = dia->PFactor;
		PolyR = dia->T6_Faktor2->value();
		PolyS = dia->T6_Konvex->isChecked();
		PolyFd = dia->T6_Slider1->value();
		Prefs.PolyC = PolyC;
		Prefs.PolyF = PolyF;
		Prefs.PolyFd = PolyFd;
		Prefs.PolyS = PolyS;
		Prefs.PolyR = PolyR;
		Prefs.PageFormat = dia->GZComboF->currentItem();
		Prefs.Ausrichtung = dia->GZComboO->currentItem();
		Prefs.PageBreite = dia->Pagebr;
		Prefs.PageHoehe = dia->Pageho;
		Prefs.RandOben = dia->RandT;
		Prefs.RandUnten = dia->RandB;
		Prefs.RandLinks = dia->RandL;
		Prefs.RandRechts = dia->RandR;
		Prefs.DoppelSeiten = dia->Doppelseiten->isChecked();
		Prefs.ErsteLinks = dia->Linkszuerst->isChecked();
		Prefs.PDFTransparency = dia->UsePDFTrans->isChecked();
		if (Prefs.DisScale != dia->DisScale)
			{
			Prefs.DisScale = dia->DisScale;
			zChange = true;
			}
		Mpal->Cpal->UseTrans(Prefs.PDFTransparency);
		if (HaveDoc)
			{
			slotChangeUnit(dia->UnitCombo->currentItem(), false);
			if (zChange)
				slotZoomAbs(doc->Scale*Prefs.DisScale);
			doc->GrabRad = dia->SpinBox3_2->value();
			doc->GuideRad = dia->SpinBox2g->value() / UmReFaktor;
			doc->Dfont = dia->FontComb->currentText();
			doc->Dsize = dia->SizeCombo->currentText().left(2).toInt() * 10;
			doc->minorGrid = dia->SpinBox1->value() / UmReFaktor;
			doc->majorGrid = dia->SpinBox2->value() / UmReFaktor;
			doc->minorColor = dia->Cmin;
			doc->majorColor = dia->Cmax;
			doc->papColor = dia->Cpaper;
			doc->margColor = dia->Crand;
			doc->guideColor = dia->Cgui;
			doc->VHoch = dia->VHochW->value();
			doc->VHochSc = dia->VHochWSc->value();
			doc->VTief = dia->VTiefW->value();
			doc->VTiefSc = dia->VTiefWSc->value();
			doc->VKapit = dia->SmallCaps->value();
  		doc->Dpen = dia->Foreground->currentText();
			if (doc->Dpen == tr("None"))
				doc->Dpen = "None";
  		doc->DpenText = dia->ForegroundT->currentText();
			if (doc->DpenText == tr("None"))
				doc->DpenText = "None";
  		doc->Dbrush = dia->Background->currentText();
			if (doc->Dbrush == tr("None"))
				doc->Dbrush = "None";
  		doc->Dshade = dia->Shade->value();
  		doc->Dshade2 = dia->Shade2->value();
			switch (dia->Linestyle->currentItem())
				{
				case 0:
					doc->DLineArt = SolidLine;
					break;
				case 1:
					doc->DLineArt = DashLine;
					break;
				case 2:
					doc->DLineArt = DotLine;
					break;
				case 3:
					doc->DLineArt = DashDotLine;
					break;
				case 4:
					doc->DLineArt = DashDotDotLine;
					break;
				}
  		doc->Dwidth = dia->LineW->value();
  		doc->DpenLine = dia->Foreground2->currentText();
			if (doc->DpenLine == tr("None"))
				doc->DpenLine = "None";
  		doc->DshadeLine = dia->Shade22->value();
			doc->DCols = dia->TextColVal->value();
			doc->DGap = dia->TextGapVal->value() / UmReFaktor;
			switch (dia->Linestyle2->currentItem())
				{
				case 0:
					doc->DLstyleLine = SolidLine;
					break;
				case 1:
					doc->DLstyleLine = DashLine;
					break;
				case 2:
					doc->DLstyleLine = DotLine;
					break;
				case 3:
					doc->DLstyleLine = DashDotLine;
					break;
				case 4:
					doc->DLstyleLine = DashDotDotLine;
					break;
				}
  		doc->DwidthLine = dia->LineW2->value();
  		doc->MagMin = dia->MinMag->value();
  		doc->MagMax = dia->MaxMag->value();
  		doc->MagStep = dia->StepMag->value();
  		doc->DbrushPict = dia->BackgroundP->currentText();
			if (doc->DbrushPict == tr("None"))
				doc->DbrushPict = "None";
			doc->ShadePict = dia->ShadeP->value();
			doc->ScaleX = static_cast<double>(dia->XScale->value()) / 100.0;
			doc->ScaleY = static_cast<double>(dia->YScale->value()) / 100.0;
			doc->ScaleType = dia->FreeScale->isChecked();
			doc->AspectRatio = dia->Aspect->isChecked();
			doc->Before = dia->RadioButton6->isChecked();
			doc->PagesSbS = dia->SidebySide->isChecked();
			doc->ShFrames = dia->FramesVisible->isChecked();
			doc->RandFarbig = dia->RandFarb->isChecked();
			doc->AutoLine = dia->AutoLineV->value();
			doc->AutoSave = dia->ASon->isChecked();
			if (doc->AutoSave)
				{
				doc->ASaveTimer->stop();
				doc->ASaveTimer->start(dia->ASTime->value() * 60 * 1000);
				}
			view->reformPages();
			view->DrawNew();
			}
		else
			{
			Prefs.Einheit = dia->UnitCombo->currentItem();
			switch (Prefs.Einheit)
				{
				case 0:
					UmReFaktor = 1.0;
					break;
				case 1:
					UmReFaktor = 1.0 / 72.0 * 25.4;
					break;
				case 2:
					UmReFaktor = 1.0 / 72.0;
					break;
				case 3:
					UmReFaktor = 1.0 / 12.0;
					break;
				}
			Prefs.GrabRad = dia->SpinBox3_2->value();
			Prefs.GuideRad = dia->SpinBox2g->value() / UmReFaktor;
			Prefs.DefFont = dia->FontComb->currentText();
			Prefs.DefSize = dia->SizeCombo->currentText().left(2).toInt() * 10;
			Prefs.DminGrid = dia->SpinBox1->value() / UmReFaktor;
			Prefs.DmajGrid = dia->SpinBox2->value() / UmReFaktor;
			Prefs.DminColor = dia->Cmin;
			Prefs.DmajColor = dia->Cmax;
			Prefs.DpapColor = dia->Cpaper;
			Prefs.DmargColor = dia->Crand;
			Prefs.guideColor = dia->Cgui;
			Prefs.DVHoch = dia->VHochW->value();
			Prefs.DVHochSc = dia->VHochWSc->value();
			Prefs.DVTief = dia->VTiefW->value();
			Prefs.DVTiefSc = dia->VTiefWSc->value();
			Prefs.DVKapit = dia->SmallCaps->value();
  		Prefs.Dpen = dia->Foreground->currentText();
			if (Prefs.Dpen == tr("None"))
				Prefs.Dpen = "None";
  		Prefs.DpenText = dia->ForegroundT->currentText();
			if (Prefs.DpenText == tr("None"))
				Prefs.DpenText = "None";
			Prefs.DCols = dia->TextColVal->value();
			Prefs.DGap = dia->TextGapVal->value() / UmReFaktor;
  		Prefs.Dbrush = dia->Background->currentText();
			if (Prefs.Dbrush == tr("None"))
				Prefs.Dbrush = "None";
  		Prefs.Dshade = dia->Shade->value();
  		Prefs.Dshade2 = dia->Shade2->value();
			switch (dia->Linestyle->currentItem())
				{
				case 0:
					Prefs.DLineArt = SolidLine;
					break;
				case 1:
					Prefs.DLineArt = DashLine;
					break;
				case 2:
					Prefs.DLineArt = DotLine;
					break;
				case 3:
					Prefs.DLineArt = DashDotLine;
					break;
				case 4:
					Prefs.DLineArt = DashDotDotLine;
					break;
				}
  		Prefs.Dwidth = dia->LineW->value();
  		Prefs.DpenLine = dia->Foreground2->currentText();
			if (Prefs.DpenLine == tr("None"))
				Prefs.DpenLine = "None";
  		Prefs.DshadeLine = dia->Shade22->value();
			switch (dia->Linestyle2->currentItem())
				{
				case 0:
					Prefs.DLstyleLine = SolidLine;
					break;
				case 1:
					Prefs.DLstyleLine = DashLine;
					break;
				case 2:
					Prefs.DLstyleLine = DotLine;
					break;
				case 3:
					Prefs.DLstyleLine = DashDotLine;
					break;
				case 4:
					Prefs.DLstyleLine = DashDotDotLine;
					break;
				}
  		Prefs.DwidthLine = dia->LineW2->value();
  		Prefs.MagMin = dia->MinMag->value();
  		Prefs.MagMax = dia->MaxMag->value();
  		Prefs.MagStep = dia->StepMag->value();
  		Prefs.DbrushPict = dia->BackgroundP->currentText();
			if (Prefs.DbrushPict == tr("None"))
				Prefs.DbrushPict = "None";
			Prefs.ShadePict = dia->ShadeP->value();
			Prefs.ScaleX = static_cast<double>(dia->XScale->value()) / 100.0;
			Prefs.ScaleY = static_cast<double>(dia->YScale->value()) / 100.0;
			Prefs.ScaleType = dia->FreeScale->isChecked();
			Prefs.AspectRatio = dia->Aspect->isChecked();
			Prefs.Before = dia->RadioButton6->isChecked();
			Prefs.PagesSbS = dia->SidebySide->isChecked();
			Prefs.ShFrames = dia->FramesVisible->isChecked();
			Prefs.RandFarbig = dia->RandFarb->isChecked();
			Prefs.AutoLine = dia->AutoLineV->value();
			Prefs.AutoSave = dia->ASon->isChecked();
			Prefs.AutoSaveTime = dia->ASTime->value() * 60 * 1000;
			}
		SavePrefs();
		}
	delete dia;
	dlclose(mo);
}

void ScribusApp::SavePrefs()
{
  Prefs.MainX = abs(pos().x());
  Prefs.MainY = abs(pos().y());
  Prefs.MainW = size().width();
  Prefs.MainH = size().height();
  Prefs.Werkv = WerkTools->isVisible();
  Prefs.WerkvP = WerkToolsP->isVisible();
  Prefs.Mpalv = Mpal->isVisible();
  Prefs.Tpalv = Tpal->isVisible();
  Prefs.SCpalv = ScBook->isVisible();
  Prefs.Lpalv = Lpal->isVisible();
  Prefs.Sepalv = Sepal->isVisible();
	Prefs.Bopalv = BookPal->isVisible();
  if (Mpal->isVisible())
  	{
	  Prefs.Mpalx = abs(Mpal->pos().x());
	  Prefs.Mpaly = abs(Mpal->pos().y());
	  }
	if (Tpal->isVisible())
		{
		Prefs.Tpalx = abs(Tpal->pos().x());
		Prefs.Tpaly = abs(Tpal->pos().y());
		}
	if (ScBook->isVisible())
		{
		Prefs.SCpalx = abs(ScBook->pos().x());
		Prefs.SCpaly = abs(ScBook->pos().y());
		Prefs.SCpalw = abs(ScBook->size().width());
		Prefs.SCpalh = abs(ScBook->size().height());
		}
	if (Sepal->isVisible())
		{
		Prefs.Sepalx = abs(Sepal->pos().x());
		Prefs.Sepaly = abs(Sepal->pos().y());
		}
	if (BookPal->isVisible())
		{
		Prefs.Bopalx = abs(BookPal->pos().x());
		Prefs.Bopaly = abs(BookPal->pos().y());
		}
	if (Lpal->isVisible())
		{
		Prefs.Lpalx = abs(Lpal->pos().x());
		Prefs.Lpaly = abs(Lpal->pos().y());
		}
  Prefs.RecentDocs.clear();
	uint max = QMIN(Prefs.RecentDCount, RecentDocs.count());
	for (uint m = 0; m < max; ++m)
		{
		Prefs.RecentDocs.append(RecentDocs[m]);
		}
	Prefs.PrinterName = PDef.Pname;
	Prefs.PrinterFile = PDef.Dname;
	Prefs.PrinterCommand = PDef.Command;
  ScriXmlDoc *ss = new ScriXmlDoc();
  ss->WritePref(&Prefs, PrefsPfad+"/scribus.rc");
  delete ss;
}

void ScribusApp::ReadPrefs()
{
  ScriXmlDoc *ss = new ScriXmlDoc();
  bool erg = ss->ReadPref(&Prefs, PrefsPfad+"/scribus.rc");
  delete ss;
  if (!erg)
  	return;
	PDef.Pname = Prefs.PrinterName;
	PDef.Dname = Prefs.PrinterFile;
	PDef.Command = Prefs.PrinterCommand;
	PolyC = Prefs.PolyC;
	PolyF = Prefs.PolyF;
	PolyFd = Prefs.PolyFd;
	PolyS = Prefs.PolyS;
	PolyR = Prefs.PolyR;
  recentMenu->clear();
	uint max = QMIN(Prefs.RecentDCount, Prefs.RecentDocs.count());
	for (uint m = 0; m < max; ++m)
		{
		QFileInfo fd(Prefs.RecentDocs[m]);
		if (fd.exists())
			{
			RecentDocs.append(Prefs.RecentDocs[m]);
			recentMenu->insertItem(Prefs.RecentDocs[m]);
			}
		}
	Mpal->move(Prefs.Mpalx, Prefs.Mpaly);
	Tpal->move(Prefs.Tpalx, Prefs.Tpaly);
	Lpal->move(Prefs.Lpalx, Prefs.Lpaly);
	Sepal->move(Prefs.Sepalx, Prefs.Sepaly);
	BookPal->move(Prefs.Bopalx, Prefs.Bopaly);
	ScBook->move(Prefs.SCpalx, Prefs.SCpaly);
	ScBook->resize(Prefs.SCpalw, Prefs.SCpalh);
	Npal->move(Prefs.Npalx, Prefs.Npaly);
	move(Prefs.MainX, Prefs.MainY);
	resize(Prefs.MainW, Prefs.MainH);
}

void ScribusApp::ShowSubs()
{
	QString mess;
	if (HaveGS != 0)
		{
		mess = tr("The following Programs are missing:")+"\n\n";
		if (HaveGS != 0)
			mess += tr("Ghostscript : You cannot use EPS-Images")+"\n\n";
    QMessageBox::warning(this, tr("Warning"), mess, 1, 0, 0);
    }
	setTools(Prefs.Werkv);
 	setPDFTools(Prefs.WerkvP);
	setMpal(Prefs.Mpalv);
	setTpal(Prefs.Tpalv);
	setBpal(Prefs.SCpalv);
	setLpal(Prefs.Lpalv);
	setSepal(Prefs.Sepalv);
	setBookpal(Prefs.Bopalv);
	setActiveWindow();
	raise();
}

PSLib* ScribusApp::getPSDriver(bool psart, SCFonts &AllFonts, QMap<QString,QFont> DocFonts, CListe DocColors, bool pdf)
{
	const char *error;
	typedef PSLib* (*sdem)(bool psart, SCFonts &AllFonts, QMap<QString,QFont> DocFonts, CListe DocColors, bool pdf);
	sdem demo;
	QString pfad = PREL;
#if defined(__hpux)
	pfad += "/lib/scribus/libs/libpostscript.sl";
#else
	pfad += "/lib/scribus/libs/libpostscript.so";
#endif
	PSDriver = dlopen(pfad, RTLD_LAZY);
	if (!PSDriver)
		{
		std::cout << "Can't find Plugin" << endl;
		return NULL;
		}
	dlerror();
	demo = (sdem)dlsym(PSDriver, "Run");
	if ((error = dlerror()) != NULL)
		{
		std::cout << "Can't find Symbol" << endl;
		dlclose(PSDriver);
		return NULL;
		}
	PSLib *dia = (*demo)(psart, AllFonts, DocFonts, DocColors, pdf);
	return dia;
}

void ScribusApp::closePSDriver()
{
	dlclose(PSDriver);
}

bool ScribusApp::getPDFDriver(QString fn, QString nam, int Components, int frPa, int toPa, QMap<int,QPixmap> thumbs)
{
	bool ret = false;
	char *error;
	void *PDFDriver;
	typedef bool (*sdem)(ScribusApp *plug, QString fn, QString nam, int Components, int frPa, int toPa, QMap<int,QPixmap> thumbs);
	sdem demo;
	QString pfad = PREL;
#if defined(__hpux)
  pfad += "/lib/scribus/libs/libpdf.sl";
#else
	pfad += "/lib/scribus/libs/libpdf.so";
#endif
	PDFDriver = dlopen(pfad, RTLD_NOW);
	if (!PDFDriver)
		{
		std::cout << "Can't find Plugin" << endl;
		return false;
		}
	dlerror();
	demo = (sdem)dlsym(PDFDriver, "Run");
	if ((error = dlerror()) != NULL)
		{
		std::cout << "Can't find Symbol" << endl;
		dlclose(PDFDriver);
		return false;
		}
	ret = (*demo)(this, fn, nam, Components, frPa, toPa, thumbs);
	dlclose(PDFDriver);
	return ret;
}

bool ScribusApp::DoSaveAsEps(QString fn)
{
	bool return_value = true;
	qApp->setOverrideCursor(QCursor(waitCursor), true);
	QMap<QString,QFont> ReallyUsed;
	ReallyUsed.clear();
	GetUsedFonts(&ReallyUsed);
	PSLib *dd = getPSDriver(false, Prefs.AvailFonts, ReallyUsed, doc->PageColors, false);
	if (dd != NULL)
		{
		if (dd->PS_set_file(fn))
			view->CreatePS(dd, doc->ActPage->PageNr, doc->ActPage->PageNr+1, 1, false, tr("All"), true, false, false, false);
   	else
			return_value = false;
		delete dd;
		closePSDriver();
		qApp->setOverrideCursor(QCursor(arrowCursor), true);
		}
	return return_value;
}

void ScribusApp::SaveAsEps()
{
	QString fna;
  if (!doc->DocName.startsWith( tr("Document")))
  	{
  	QFileInfo fi(doc->DocName);
  	fna = fi.dirPath()+"/"+fi.baseName()+".eps";
  	}
  else
  	{
  	QDir di = QDir();
  	fna = di.currentDirPath()+"/"+doc->DocName+".eps";
  	}
  QString fn = CFileDialog( tr("Save as"), tr("EPS-Files (*.eps);;All Files (*)"), "", false, false);
  if (!fn.isEmpty())
  	{
		if (overwrite(this, fn))
			{
			if (!DoSaveAsEps(fn))
				QMessageBox::warning(this, tr("Warning"), tr("Can't write the File: \n%1").arg(fn), tr("OK"));
			}
  	}
}

void ScribusApp::SaveAsPDF()
{
	QString fn;
	uint frPa, toPa;
	int Components;
	QString nam = "";
	if (BookPal->BView->childCount() == 0)
		doc->PDF_Optionen.Bookmarks = false;
	QMap<QString,QFont> ReallyUsed;
	ReallyUsed.clear();
	GetUsedFonts(&ReallyUsed);
  PDF_Opts *dia = new PDF_Opts(this, doc->DocName, ReallyUsed, view, &doc->PDF_Optionen, doc->PDF_Optionen.PresentVals, &PDFXProfiles, Prefs.AvailFonts);
  if (dia->exec())
  	{
  	qApp->setOverrideCursor(QCursor(waitCursor), true);
  	fn = dia->Datei->text();
		doc->PDF_Optionen.Datei = fn;
		doc->PDF_Optionen.Thumbnails = dia->CheckBox1->isChecked();
		doc->PDF_Optionen.Compress = dia->Compression->isChecked();
		doc->PDF_Optionen.Resolution = dia->Resolution->value();
		doc->PDF_Optionen.EmbedList = dia->FontsToEmbed;
		doc->PDF_Optionen.RecalcPic = dia->DSColor->isChecked();
		doc->PDF_Optionen.PicRes = dia->ValC->value();
		doc->PDF_Optionen.Bookmarks = dia->CheckBM->isChecked();
		doc->PDF_Optionen.Binding = dia->ComboBind->currentItem();
		doc->PDF_Optionen.PresentMode = dia->CheckBox10->isChecked();
		doc->PDF_Optionen.PresentVals = dia->EffVal;
		doc->PDF_Optionen.Articles = dia->Article->isChecked();
		doc->PDF_Optionen.Encrypt = dia->Encry->isChecked();
		if (dia->Encry->isChecked())
			{
			int Perm = -64;
			if (dia->ComboBox1->currentItem() == 1)
	  		Perm &= ~0x00240000;
			if (dia->PrintSec->isChecked())
				Perm += 4;
			if (dia->ModifySec->isChecked())
				Perm += 8;
			if (dia->CopySec->isChecked())
				Perm += 16;
			if (dia->AddSec->isChecked())
				Perm += 32;
			doc->PDF_Optionen.Permissions = Perm;
			doc->PDF_Optionen.PassOwner = dia->PassOwner->text();
			doc->PDF_Optionen.PassUser = dia->PassUser->text();
			}
		if (dia->ComboBox1->currentItem() == 0)
			doc->PDF_Optionen.Version = 13;
		if (dia->ComboBox1->currentItem() == 1)
			doc->PDF_Optionen.Version = 14;
		if (dia->ComboBox1->currentItem() == 2)
			doc->PDF_Optionen.Version = 12;
		if (dia->OutCombo->currentItem() == 0)
			{
			doc->PDF_Optionen.UseRGB = true;
			doc->PDF_Optionen.UseProfiles = false;
			doc->PDF_Optionen.UseProfiles2 = false;
			}
		else
			{
			doc->PDF_Optionen.UseRGB = false;
#ifdef HAVE_CMS
			doc->PDF_Optionen.UseProfiles = dia->EmbedProfs->isChecked();
			doc->PDF_Optionen.UseProfiles2 = dia->EmbedProfs2->isChecked();
			doc->PDF_Optionen.Intent = dia->IntendS->currentItem();
			doc->PDF_Optionen.Intent2 = dia->IntendI->currentItem();
			doc->PDF_Optionen.EmbeddedI = dia->NoEmbedded->isChecked();
			doc->PDF_Optionen.SolidProf = dia->SolidPr->currentText();
			doc->PDF_Optionen.ImageProf = dia->ImageP->currentText();
			doc->PDF_Optionen.PrintProf = dia->PrintProfC->currentText();
			if (doc->PDF_Optionen.Version == 12)
				{
				const char *Descriptor;
				cmsHPROFILE hIn;
				hIn = cmsOpenProfileFromFile(PrinterProfiles[doc->PDF_Optionen.PrintProf], "r");
  			Descriptor = cmsTakeProductDesc(hIn);
				nam = QString(Descriptor);
				if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigRgbData)
					Components = 3;
				if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigCmykData)
					Components = 4;
				if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigCmyData)
					Components = 3;
				cmsCloseProfile(hIn);
				doc->PDF_Optionen.Info = dia->InfoString->text();
				doc->PDF_Optionen.BleedTop = dia->BleedTop->value()/UmReFaktor;
				doc->PDF_Optionen.BleedLeft = dia->BleedLeft->value()/UmReFaktor;
				doc->PDF_Optionen.BleedRight = dia->BleedRight->value()/UmReFaktor;
				doc->PDF_Optionen.BleedBottom = dia->BleedBottom->value()/UmReFaktor;
				doc->PDF_Optionen.Encrypt = false;
				doc->PDF_Optionen.PresentMode = false;
				doc->PDF_Optionen.Encrypt = false;
				}
#else
			doc->PDF_Optionen.UseProfiles = false;
			doc->PDF_Optionen.UseProfiles2 = false;
#endif
			}
		frPa = dia->AllPages->isChecked() ? 0 : static_cast<unsigned int>(dia->FirstPage->value() - 1);
		toPa = dia->AllPages->isChecked() ? view->Pages.count() : static_cast<unsigned int>(dia->LastPage->value());
		QMap<int,QPixmap> thumbs;
		view->RecalcTextPos();
		for (uint ap = frPa; ap < toPa; ++ap)
			{
			QPixmap pm(10,10);
			if (doc->PDF_Optionen.Thumbnails)
				pm = view->PageToPixmap(ap, 100);
			thumbs.insert(ap, pm);
			}
		if (!getPDFDriver(fn, nam, Components, frPa, toPa, thumbs))
			QMessageBox::warning(this, tr("Warning"), tr("Can't write the File: \n%1").arg(fn), tr("OK"));
 		qApp->setOverrideCursor(QCursor(arrowCursor), true);
		}
  delete dia;
}

void ScribusApp::AddBookMark(PageItem *ite)
{
	BookPal->BView->AddPageItem(ite);
	StoreBookmarks();
}

void ScribusApp::DelBookMark(PageItem *ite)
{
	BookPal->BView->DeleteItem(ite->BMnr);
	StoreBookmarks();
}

void ScribusApp::BookMarkTxT(PageItem *ite)
{
	BookPal->BView->ChangeText(ite);
	StoreBookmarks();
}

void ScribusApp::ChBookmarks(int s, int e, int n)
{
	view->Pages.at(s)->Items.at(e)->BMnr = n;
}

void ScribusApp::RestoreBookMarks()
{
	QValueList<ScribusDoc::BookMa>::Iterator it2 = doc->BookMarks.begin();
	BookPal->BView->clear();
	if (doc->BookMarks.count() == 0)
		return;
	BookMItem* ip;
	BookMItem* ip2;
	BookMItem* ip3;
	BookMItem *ite = new BookMItem(BookPal->BView, &(*it2));
	++it2;
	for( ; it2 != doc->BookMarks.end(); ++it2 )
		{
		if ((*it2).Parent == 0)
			ite = new BookMItem(BookPal->BView, ite, &(*it2));
		else
			{
			QListViewItemIterator it3(BookPal->BView);
			for ( ; it3.current(); ++it3)
				{
				ip = (BookMItem*)it3.current();
				if ((*it2).Parent == ip->ItemNr)
					{
					ip2 = ip;
					break;
					}
				}
			if ((*it2).Prev == 0)
				(void) new BookMItem(ip2, &(*it2));
			else
				{
				QListViewItemIterator it4(BookPal->BView);
				for ( ; it4.current(); ++it4)
					{
					ip = (BookMItem*)it4.current();
					if ((*it2).Prev == ip->ItemNr)
						{
						ip3 = ip;
						break;
						}
					}
				(void) new BookMItem(ip2, ip3, &(*it2));
				}
			}
		}
}

void ScribusApp::StoreBookmarks()
{
	doc->BookMarks.clear();
	BookMItem* ip;
	QListViewItemIterator it(BookPal->BView);
	struct ScribusDoc::BookMa Boma;
	for ( ; it.current(); ++it)
		{
		ip = (BookMItem*)it.current();
		Boma.Title = ip->Titel;
		Boma.Text = ip->text(0);
		Boma.Aktion = ip->Action;
		Boma.ItemNr = ip->ItemNr;
		Boma.Seite = ip->Seite;
		Boma.Element = ip->Element;
		Boma.Parent = ip->Pare;
		Boma.First = ip->First;
		Boma.Prev = ip->Prev;
		Boma.Next = ip->Next;
		Boma.Last = ip->Last;
		doc->BookMarks.append(Boma);
		}
	ActWin->NrItems = BookPal->BView->NrItems;
	ActWin->First = BookPal->BView->First;
	ActWin->Last = BookPal->BView->Last;
}

void ScribusApp::slotElemRead(QString Name, int x, int y, bool art, bool loca, ScribusDoc* docc)
{
	if (doc == docc)
		NoFrameEdit();
  ScriXmlDoc *ss = new ScriXmlDoc();
  if(ss->ReadElem(Name, Prefs.AvailFonts, docc, x, y, art, loca, Prefs.GFontSub, &Prefs))
  	{
  	docc->ActPage->update();
		docc->UnDoValid = false;
		if (doc == docc)
			{
  		BuildFontMenu();
			Mpal->Spal->updateFList();
			Mpal->SetLineFormats(docc);
  		slotDocCh();
			CanUndo();
			}
  	}
  delete ss;
}

void ScribusApp::slotChangeUnit(int art, bool draw)
{
	doc->Einheit = art;
	switch (art)
		{
		case 0:
			UmReFaktor = 1.0;
			view->UN->setText("pt");
			break;
		case 1:
			UmReFaktor = 0.3527777;
			view->UN->setText("mm");
			break;
		case 2:
			UmReFaktor = 1.0 / 72.0;
			view->UN->setText("in");
			break;
		case 3:
			UmReFaktor = 1.0 / 12.0;
			view->UN->setText("p");
			break;
		}
	Mpal->UnitChange();
	if (draw)
		view->DrawNew();
}

void ScribusApp::ManageJava()
{
	JavaDocs *dia = new JavaDocs(this, doc, view);
	dia->exec();
	delete dia;
}

void ScribusApp::ManageTemp(QString temp)
{
	MusterSeiten *dia = new MusterSeiten(this, doc, view, temp);
	connect(dia, SIGNAL(CreateNew(int)), this, SLOT(slotNewPageT(int)));
	connect(dia, SIGNAL(LoadPage(QString, int, bool)), this, SLOT(LadeSeite(QString, int, bool)));
	connect(dia, SIGNAL(Fertig()), this, SLOT(ManTempEnd()));
	for (uint a=0; a<5; ++a)
		{
		pageMenu->setItemEnabled(pageMenu->idAt(a), 0);
		}
	editMenu->setItemEnabled(tman, 0);
	ActWin->MenuStat[0] = DatSav->isEnabled();
	ActWin->MenuStat[1] = fileMenu->isItemEnabled(fid1);
	ActWin->MenuStat[2] = fileMenu->isItemEnabled(fid4);
	ActWin->MenuStat[3] = fileMenu->isItemEnabled(fid5);
	DatNeu->setEnabled(false);
	DatSav->setEnabled(false);
	DatOpe->setEnabled(false);
	DatClo->setEnabled(false);
	fileMenu->setEnabled(false);
	doc->TemplateMode = true;
	Sepal->DisablePal();
	doc->UnDoValid = false;
	CanUndo();
	dia->show();
	ActWin->muster = dia;
}

void ScribusApp::ManTempEnd()
{
	view->HideTemplate();
	editMenu->setItemEnabled(tman, 1);
	pageMenu->setItemEnabled(pageMenu->idAt(0), 1);
	pageMenu->setItemEnabled(pageMenu->idAt(2), 1);
	pageMenu->setItemEnabled(pageMenu->idAt(4), 1);
	DatNeu->setEnabled(true);
	DatSav->setEnabled(ActWin->MenuStat[0]);
	DatOpe->setEnabled(true);
	DatClo->setEnabled(true);
	fileMenu->setEnabled(true);
	int setter = view->Pages.count() > 1 ? 1 : 0;
	pageMenu->setItemEnabled(pgmd, setter);
	pageMenu->setItemEnabled(pgmv, setter);
	if (doc->isModified())
		slotDocCh();
	for (uint c=0; c<view->Pages.count(); ++c)
		{
		Apply_Temp(view->Pages.at(c)->MPageNam, c, false);
		}
	doc->TemplateMode = false;
	Sepal->EnablePal();
	Sepal->RebuildTemp();
	ActWin->muster = NULL;
	view->DrawNew();
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
	Sepal->Rebuild();
}

void ScribusApp::ApplyTemp()
{
	QString mna;
	ApplyT *dia = new ApplyT(this, view, doc->ActPage->MPageNam);
	if (dia->exec())
		{
		mna = dia->Templ->currentText();
		if (dia->SinglePage->isChecked())
			Apply_Temp(mna, doc->ActPage->PageNr, false);
		else
			{
			int from = dia->FromPage->value()-1;
			int to = dia->ToPage->value();
			for (int a = from; a < to; ++a)
				{
				Apply_Temp(mna, a, false);
				}
			}
		}
	view->DrawNew();
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
	Sepal->Rebuild();
	delete dia;
}

void ScribusApp::Apply_Temp(QString in, int Snr, bool reb)
{
	QString mna = in;
	if (mna == tr("Normal"))
		mna = "Normal";
	Page* Ap = view->Pages.at(Snr);
	Ap->MPageNam = mna;
	Page* Mp = view->MasterPages.at(view->MasterNames[mna]);
	if (Mp->YGuides.count() != 0)
		{
		for (uint y = 0; y < Mp->YGuides.count(); ++y)
      {
			if (Ap->YGuides.contains(Mp->YGuides[y]) == 0)
				Ap->YGuides.append(Mp->YGuides[y]);
			}
		qHeapSort(Ap->YGuides);
		}
	if (Mp->XGuides.count() != 0)
		{
		for (uint x = 0; x < Mp->XGuides.count(); ++x)
      {
			if (Ap->XGuides.contains(Mp->XGuides[x]) == 0)
				Ap->XGuides.append(Mp->XGuides[x]);
			}
		qHeapSort(Ap->XGuides);
		}
	if (reb)
		{
		view->DrawNew();
		slotDocCh();
		doc->UnDoValid = false;
		CanUndo();
		Sepal->Rebuild();
		}
}

void ScribusApp::GroupObj()
{
	PageItem* b;
	double x, y, w, h;
	for (uint a=0; a<doc->ActPage->SelItem.count(); ++a)
		{
		b = doc->ActPage->SelItem.at(a);
		b->Groups.push(doc->GroupCounter);
		}
	doc->GroupCounter++;
	doc->ActPage->getGroupRect(&x, &y, &w, &h);
	doc->ActPage->repaint(QRect(static_cast<int>(x-5), static_cast<int>(y-5), static_cast<int>(w+10), static_cast<int>(h+10)));
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::UnGroupObj()
{
	PageItem* b;
	for (uint a=0; a<doc->ActPage->SelItem.count(); ++a)
		{
		b = doc->ActPage->SelItem.at(a);
		b->Groups.pop();
		}
	doc->ActPage->Deselect(true);
	slotDocCh();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::StatusPic()
{
	if (HaveDoc)
		{
		PicStatus *dia = new PicStatus(this, doc, view);
		connect(dia, SIGNAL(GotoSeite(int)), this, SLOT(SelectFromOutlS(int)));
		dia->exec();
		delete dia;
		}
}

QString ScribusApp::CFileDialog(QString caption, QString filter, QString defNa, bool Pre, bool mod, bool comp, bool cod)
{
	CustomFDialog dia(this, caption, filter, Pre, mod, comp, cod);
	if (defNa != "")
		dia.setSelection(defNa);
	if (dia.exec() == QDialog::Accepted)
		{
			LoadEnc = cod ? dia.TxCodeM->currentText() : "";
			return dia.selectedFile();
		}
	return "";
}

void ScribusApp::RunPlug(int id)
{
	int a = extraMenu->indexOf(id);
	if (a > 2)
		CallDLL(extraMenu->text(id));
}

void ScribusApp::RunImportPlug(int id)
{
	int a = importMenu->indexOf(id);
	if (a > 1)
		{
		if (HaveDoc)
			doc->OpenNodes = Tpal->buildReopenVals();
		CallDLL(importMenu->text(id));
		if (HaveDoc)
			{
			Tpal->BuildTree(view);
			Tpal->reopenTree(doc->OpenNodes);
			}
		}
}

void ScribusApp::RunExportPlug(int id)
{
	int a = exportMenu->indexOf(id);
	if (a > 2)
		CallDLL(exportMenu->text(id));
}

void ScribusApp::RunHelpPlug(int id)
{
	int a = helpMenu->indexOf(id);
	if (a > 4)
		CallDLL(helpMenu->text(id));
}

void ScribusApp::FinalizePlugs()
{
	const char *error;
	QMap<QString, PlugData>::Iterator it;
	struct PlugData pda;
	typedef void (*sdem2)();
	sdem2 demo2;
	for (it = PluginMap.begin(); it != PluginMap.end(); ++it)
		{
		if (it.data().Typ == 4)
			{
			dlerror();
			demo2 = (sdem2)dlsym(it.data().Zeiger, "CleanUpPlug");
			if ((error = dlerror()) != NULL)
				{
				dlclose(it.data().Zeiger);
				continue;
				}
			else
				{
				(*demo2)();
				}
			}
		}
}

void ScribusApp::InitPlugs(SplashScreen *spl)
{
	QString pfad = PREL;
	QString nam = "";
	int ty = 0;
	struct PlugData pda;
	pfad += "/lib/scribus/plugins/";
#if defined(__hpux)
	QDir d(pfad, "*.sl*", QDir::Name, QDir::Files | QDir::Executable | QDir::NoSymLinks);
#else
	QDir d(pfad, "*.so*", QDir::Name, QDir::Files | QDir::Executable | QDir::NoSymLinks);
#endif
	if ((d.exists()) && (d.count() != 0))
		{
		extraMenu->insertSeparator();
		for (uint dc = 0; dc < d.count(); ++dc)
			{
			pda.Zeiger = 0;
			pda.Datei = "";
			pda.Typ = 0;
			if (DLLName(d[dc], &nam, &ty, &pda.Zeiger))
				{
				if (ty == 1)
					extraMenu->insertItem(nam);
				if (ty == 2)
					importMenu->insertItem(nam);
				if (ty == 3)
					exportMenu->insertItem(nam);
				if (ty == 4)
					helpMenu->insertItem(nam);
				pda.Datei = d[dc];
				pda.Typ = ty;
				PluginMap.insert(nam, pda);
				spl->setStatus( tr("Loading:")+" "+nam);
				}
			}
	 	connect(extraMenu, SIGNAL(activated(int)), this, SLOT(RunPlug(int)));
	 	connect(importMenu, SIGNAL(activated(int)), this, SLOT(RunImportPlug(int)));
	 	connect(exportMenu, SIGNAL(activated(int)), this, SLOT(RunExportPlug(int)));
	 	connect(helpMenu, SIGNAL(activated(int)), this, SLOT(RunHelpPlug(int)));
	 	}
}

void ScribusApp::CallDLL(QString name)
{
	void *mo;
	const char *error;
	struct PlugData pda;
	pda = PluginMap[name];
	typedef void (*sdem)(QWidget *d, ScribusApp *plug);
	sdem demo;
	QString pfad = PREL;
	if (pda.Typ != 4)
		{
		pfad += "/lib/scribus/plugins/" + pda.Datei;
		mo = dlopen(pfad, RTLD_LAZY | RTLD_GLOBAL);
		if (!mo)
			{
			std::cout << "Can't find Plug-in" << endl;
			return;
			}
		}
	else
		mo = pda.Zeiger;
	dlerror();
	demo = (sdem)dlsym(mo, "Run");
	if ((error = dlerror()) != NULL)
		{
		std::cout << "Can't find Symbol" << endl;
		dlclose(mo);
		return;
		}
	(*demo)(this, this);
	if (pda.Typ != 4)
		dlclose(mo);
	if (HaveDoc)
  	doc->ActPage->update();
}

bool ScribusApp::DLLName(QString name, QString *PName, int *typ, void **Zeig)
{
	void *mo;
	const char *error;
	typedef QString (*sdem0)();
	typedef int (*sdem1)();
	typedef void (*sdem2)(QWidget *d, ScribusApp *plug);
	sdem0 demo;
	sdem1 demo1;
	sdem2 demo2;
	QString pfad = PREL;
	pfad += "/lib/scribus/plugins/" + name;
	mo = dlopen(pfad, RTLD_LAZY | RTLD_GLOBAL);
	if (!mo)
		return false;
	dlerror();
	demo = (sdem0)dlsym(mo, "Name");
	if ((error = dlerror()) != NULL)
		{
		dlclose(mo);
		return false;
		}
	*PName = (*demo)();
	dlerror();
	demo1 = (sdem1)dlsym(mo, "Type");
	if ((error = dlerror()) != NULL)
		{
		dlclose(mo);
		return false;
		}
	*typ = (*demo1)();
	*Zeig = mo;
	if (*typ != 4)
		dlclose(mo);
	else
		{
		dlerror();
		demo2 = (sdem2)dlsym(mo, "InitPlug");
		if ((error = dlerror()) != NULL)
			{
			dlclose(mo);
			return false;
			}
		(*demo2)(this, this);
		}
	return true;
}

void ScribusApp::GetCMSProfiles()
{
	MonitorProfiles.clear();
	PrinterProfiles.clear();
	InputProfiles.clear();
	QString pfad = PREL;
	pfad += "/lib/scribus/profiles/";
	GetCMSProfilesDir(pfad);
	if (Prefs.ProfileDir != "")
		{
		if(Prefs.ProfileDir.right(1) != "/")
	  	Prefs.ProfileDir += "/";
		GetCMSProfilesDir(Prefs.ProfileDir);
		}
	if ((!PrinterProfiles.isEmpty()) && (!InputProfiles.isEmpty()) && (!MonitorProfiles.isEmpty()))
		CMSavail = true;
	else
		CMSavail = false;
}

void ScribusApp::GetCMSProfilesDir(QString pfad)
{
#ifdef HAVE_CMS
	QString nam = "";
	const char *Descriptor;
	cmsHPROFILE hIn;
	QDir d(pfad, "*.*", QDir::Name, QDir::Files | QDir::NoSymLinks);
	if ((d.exists()) && (d.count() != 0))
		{
		for (uint dc = 0; dc < d.count(); ++dc)
			{
			QFileInfo fi(pfad + d[dc]);
			QString ext = fi.extension(false).lower();
			if ((ext == "icm") || (ext == "icc"))
				{
				hIn = cmsOpenProfileFromFile(pfad + d[dc], "r");
				if (hIn == NULL)
					continue;
  			Descriptor = cmsTakeProductDesc(hIn);
				nam = QString(Descriptor);
				switch (static_cast<int>(cmsGetDeviceClass(hIn)))
					{
					case icSigInputClass:
						if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigRgbData)
							InputProfiles[nam] = pfad + d[dc];
						break;
					case icSigColorSpaceClass:
						if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigRgbData)
							InputProfiles[nam] = pfad + d[dc];
						break;
					case icSigDisplayClass:
						MonitorProfiles[nam] = pfad + d[dc];
						InputProfiles[nam] = pfad + d[dc];
						break;
					case icSigOutputClass:
						PrinterProfiles[nam] = pfad + d[dc];
						if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigCmykData)
							PDFXProfiles[nam] = pfad + d[dc];
						break;
					}
				cmsCloseProfile(hIn);
				}
			}
		}
#endif
}

void ScribusApp::SetCMSPrefs()
{
	struct CMSset *CM;
	if (CMSavail)
		{
		if (HaveDoc)
			CM = &doc->CMSSettings;
		else
			CM = &Prefs.DCMSset;
		CMSPrefs *dia = new CMSPrefs(this, CM, &InputProfiles, &PrinterProfiles, &MonitorProfiles);
		if(dia->exec())
			{
			int cc = Prefs.DColors.count();
			FMess->setText( tr("Adjusting Colors"));
			FProg->reset();
			if (HaveDoc)
				{
				if (dia->Changed)
					{
  				cc = doc->PageColors.count() + view->CountElements();
					FProg->setTotalSteps(cc);
					slotDocCh();
#ifdef HAVE_CMS
					doc->HasCMS = doc->CMSSettings.CMSinUse;
					ActWin->SoftProofing = doc->CMSSettings.SoftProofOn;
					ActWin->Gamut = doc->CMSSettings.GamutCheck;
					CMSuse = doc->CMSSettings.CMSinUse;
					ActWin->IntentPrinter = doc->CMSSettings.DefaultIntentPrinter;
					ActWin->IntentMonitor = doc->CMSSettings.DefaultIntentMonitor;
					SoftProofing = doc->CMSSettings.SoftProofOn;
					Gamut = doc->CMSSettings.GamutCheck;
					IntentPrinter = doc->CMSSettings.DefaultIntentPrinter;
					IntentMonitor = doc->CMSSettings.DefaultIntentMonitor;
  				qApp->setOverrideCursor(QCursor(waitCursor), true);
  				ActWin->CloseCMSProfiles();
  				ActWin->OpenCMSProfiles(InputProfiles, MonitorProfiles, PrinterProfiles);
					stdProof = ActWin->stdProof;
					stdTrans = ActWin->stdTrans;
					stdProofImg = ActWin->stdProofImg;
					stdTransImg = ActWin->stdTransImg;
					CMSoutputProf = doc->DocOutputProf;
					CMSprinterProf = doc->DocPrinterProf;
					if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigRgbData)
						doc->CMSSettings.ComponentsInput2 = 3;
					if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigCmykData)
						doc->CMSSettings.ComponentsInput2 = 4;
					if (static_cast<int>(cmsGetColorSpace(doc->DocInputProf)) == icSigCmyData)
						doc->CMSSettings.ComponentsInput2 = 3;
					if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigRgbData)
						doc->CMSSettings.ComponentsPrinter = 3;
					if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigCmykData)
						doc->CMSSettings.ComponentsPrinter = 4;
					if (static_cast<int>(cmsGetColorSpace(doc->DocPrinterProf)) == icSigCmyData)
						doc->CMSSettings.ComponentsPrinter = 3;
					doc->PDF_Optionen.SComp = doc->CMSSettings.ComponentsInput2;
					doc->PDF_Optionen.SolidProf = doc->CMSSettings.DefaultInputProfile2;
					doc->PDF_Optionen.ImageProf = doc->CMSSettings.DefaultInputProfile;
					doc->PDF_Optionen.PrintProf = doc->CMSSettings.DefaultPrinterProfile;
					doc->PDF_Optionen.Intent = doc->CMSSettings.DefaultIntentMonitor;
					RecalcColors(FProg);
					view->RecalcPictures(&InputProfiles, FProg);
#endif
					view->DrawNew();
					Mpal->ShowCMS();
					FProg->setProgress(cc);
 					qApp->setOverrideCursor(QCursor(arrowCursor), true);
 					}
				}
			FMess->setText("");
			FProg->reset();
			}
		delete dia;
		}
}

void ScribusApp::RecalcColors(QProgressBar *dia)
{
	CListe::Iterator it;
	if (HaveDoc)
		{
		ColorMenC->clear();
		QPixmap pm = QPixmap(15, 15);
		int a = 0;
		ColorMenC->insertItem( tr("None"));
		CMYKColor tmp;
		tmp.fromQColor(doc->papColor);
		tmp.RecalcRGB();
		doc->papColor = tmp.getRGBColor();
		for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
			{
			doc->PageColors[it.key()].RecalcRGB();
			pm.fill(doc->PageColors[it.key()].getRGBColor());
			ColorMenC->insertItem(pm, it.key());
			if (it.key() == doc->Dbrush)
				ColorMenC->setCurrentItem(a);
			a++;
			if (dia != NULL)
				dia->setProgress(a);
			}
		Mpal->Cpal->SetColors(doc->PageColors);
		Mpal->updateCList();
		}
}

void ScribusApp::ModifyAnnot()
{
	PageItem *b;
  if (doc->ActPage->SelItem.count() != 0)
  	{
  	b = doc->ActPage->SelItem.at(0);
		if ((b->AnType == 0) || (b->AnType == 1) || (b->AnType > 9))
			{
			int AnType = b->AnType;
			int AnActType = b->AnActType;
			QString AnAction = b->AnAction;
			QString An_Extern = b->An_Extern;
  		Annota *dia = new Annota(this, b, doc->PageC, static_cast<int>(doc->PageB), static_cast<int>(doc->PageH), doc->PageColors, view);
  		if (dia->exec())
				slotDocCh();
			else
				{
				b->AnType = AnType;
				b->AnActType = AnActType;
				b->AnAction = AnAction;
				b->An_Extern = An_Extern;
				}
  		delete dia;
			}
		else
			{
  		Annot *dia = new Annot(this, b, doc->PageC, static_cast<int>(doc->PageB), static_cast<int>(doc->PageH), doc->PageColors, view);
  		if (dia->exec())
				slotDocCh();
  		delete dia;
			}
  	}
}

void ScribusApp::SetShortCut()
{
	uint a;
	for (a = 0; a < 9; ++a)
		{
		fileMenu->setAccel(Prefs.KeyActions[a].KeyID, Prefs.KeyActions[a].MenuID);
		}
	for (a = 9; a < 19; ++a)
		{
		editMenu->setAccel(Prefs.KeyActions[a].KeyID, Prefs.KeyActions[a].MenuID);
		}
	for (a = 20; a < 30; ++a)
		{
		ObjMenu->setAccel(Prefs.KeyActions[a].KeyID, Prefs.KeyActions[a].MenuID);
		}
	for (a = 30; a < 34; ++a)
		{
		pageMenu->setAccel(Prefs.KeyActions[a].KeyID, Prefs.KeyActions[a].MenuID);
		}
	pageMenu->setAccel(Prefs.KeyActions[61].KeyID, Prefs.KeyActions[61].MenuID);
	for (a = 34; a < 45; ++a)
		{
		viewMenu->setAccel(Prefs.KeyActions[a].KeyID, Prefs.KeyActions[a].MenuID);
		}
	for (a = 45; a < 49; ++a)
		{
		toolMenu->setAccel(Prefs.KeyActions[a].KeyID, Prefs.KeyActions[a].MenuID);
		}
	pageMenu->setAccel(Prefs.KeyActions[49].KeyID, Prefs.KeyActions[49].MenuID);
	extraMenu->setAccel(Prefs.KeyActions[50].KeyID, Prefs.KeyActions[50].MenuID);
	extraMenu->setAccel(Prefs.KeyActions[51].KeyID, Prefs.KeyActions[51].MenuID);
	for (a = 52; a < 56; ++a)
		{
		helpMenu->setAccel(Prefs.KeyActions[a].KeyID, Prefs.KeyActions[a].MenuID);
		}
	ObjMenu->setAccel(Prefs.KeyActions[61].KeyID, Prefs.KeyActions[61].MenuID);
	toolMenu->setAccel(Prefs.KeyActions[62].KeyID, Prefs.KeyActions[62].MenuID);
	editMenu->setAccel(Prefs.KeyActions[63].KeyID, Prefs.KeyActions[63].MenuID);
	editMenu->setAccel(Prefs.KeyActions[64].KeyID, Prefs.KeyActions[64].MenuID);
	toolMenu->setAccel(Prefs.KeyActions[65].KeyID, Prefs.KeyActions[65].MenuID);
	ObjMenu->setAccel(Prefs.KeyActions[66].KeyID, Prefs.KeyActions[66].MenuID);
	ObjMenu->setAccel(Prefs.KeyActions[67].KeyID, Prefs.KeyActions[67].MenuID);
}

void ScribusApp::PutScrap(QString t)
{
	ScBook->ObjFromMenu(t);
}

void ScribusApp::UniteOb()
{
	doc->ActPage->UniteObj();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::SplitUniteOb()
{
	doc->ActPage->SplitObj();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::TraceText()
{
	NoFrameEdit();
	doc->ActPage->TextToPath();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::Pfadtext()
{
	doc->ActPage->ToPathText();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::noPfadtext()
{
	doc->ActPage->FromPathText();
	doc->UnDoValid = false;
	CanUndo();
}

void ScribusApp::changeLayer(int l)
{
	doc->ActPage->Deselect(true);
	view->setLayMenTxt(l);
	view->LaMenu();
	view->DrawNew();
}

void ScribusApp::showLayer()
{
	view->DrawNew();
}

void ScribusApp::LayerRemove(int l)
{
	for (uint a = 0; a < view->MasterPages.count(); ++a)
		{
		for (uint b = 0; b < view->MasterPages.at(a)->Items.count(); ++b)
			{
			if (view->MasterPages.at(a)->Items.at(b)->LayerNr == l)
				view->MasterPages.at(a)->Items.at(b)->LayerNr = 0;
			}
		}
	for (uint a = 0; a < view->DocPages.count(); ++a)
		{
		for (uint b = 0; b < view->DocPages.at(a)->Items.count(); ++b)
			{
			if (view->DocPages.at(a)->Items.at(b)->LayerNr == l)
				view->DocPages.at(a)->Items.at(b)->LayerNr = 0;
			}
		}
	view->LaMenu();
}

void ScribusApp::UnDoAction()
{
	PageItem* b;
	uint a;
	bool mp = false;
	if (doc->UnDoValid)
		{
		doc->ActPage->Deselect(true);
		b = doc->UnData.Item;
		b->Select = false;
		view->Pages.at(doc->UnData.PageNr)->Deselect(true);
		switch (doc->UnData.UnCode)
			{
			case 0:
				b->NextBox = 0;
				b->BackBox = 0;
				b->isAutoText = false;
				view->Pages.at(doc->UnData.PageNr)->Items.insert(b->ItemNr, b);
				Tpal->slotAddElement(doc->UnData.PageNr, b->ItemNr);
				for (a = 0; a < view->Pages.at(doc->UnData.PageNr)->Items.count(); ++a)
					{
					view->Pages.at(doc->UnData.PageNr)->Items.at(a)->ItemNr = a;
					}
				Tpal->slotUpdateElement(doc->UnData.PageNr, b->ItemNr);
				break;
			case 1:
				b->Xpos = doc->UnData.Xpos;
				b->Ypos = doc->UnData.Ypos;
				Tpal->slotUpdateElement(doc->UnData.PageNr, b->ItemNr);
				break;
			case 2:
				b->Xpos = doc->UnData.Xpos;
				b->Ypos = doc->UnData.Ypos;
				b->Rot = doc->UnData.Rot;
				if (b->PType == 5)
					mp = true;
				view->Pages.at(doc->UnData.PageNr)->SizeItem(doc->UnData.Width, doc->UnData.Height, b->ItemNr, mp);
				Tpal->slotUpdateElement(doc->UnData.PageNr, b->ItemNr);
				break;
			case 3:
				b->Rot = doc->UnData.Rot;
				break;
			case 4:
				view->Pages.at(doc->UnData.PageNr)->Items.take(b->ItemNr);
				view->Pages.at(doc->UnData.PageNr)->Items.insert(doc->UnData.ItemNr, b);
				Tpal->slotMoveElement(doc->UnData.PageNr, b->ItemNr, doc->UnData.ItemNr);
				for (a = 0; a < view->Pages.at(doc->UnData.PageNr)->Items.count(); ++a)
					{
					view->Pages.at(doc->UnData.PageNr)->Items.at(a)->ItemNr = a;
					}
				break;
				Tpal->slotUpdateElement(doc->UnData.PageNr, b->ItemNr);
			}
		view->DrawNew();
		doc->UnDoValid = false;
		editMenu->setItemEnabled(edUndo, 0);
		slotDocCh();
		}
}

void ScribusApp::CanUndo()
{
	switch (doc->UnData.UnCode)
		{
		case 0:
			editMenu->changeItem(edUndo, tr("Undo Delete Object"));
			break;
		case 1:
		case 4:
			editMenu->changeItem(edUndo, tr("Undo Object Move"));
			break;
		case 2:
		case 3:
			editMenu->changeItem(edUndo, tr("Undo Object Change"));
			break;
		}
	editMenu->setItemEnabled(edUndo, doc->UnDoValid ? 1 : 0);
}

void ScribusApp::InitHyphenator()
{
	QString datein = "";
	QString	lang = QString(QTextCodec::locale()).left(2);
	QString pfad = PREL;
	Prefs.Language = tr("English");
	pfad += "/lib/scribus/dicts/";
	QDir d(pfad, "*.dic", QDir::Name, QDir::Files | QDir::NoSymLinks);
	if ((d.exists()) && (d.count() != 0))
		{
		for (uint dc = 0; dc < d.count(); ++dc)
			{
			if (d[dc] == "hyph_en.dic")
				datein = tr("English");
			if (d[dc] == "hyph_de.dic")
				datein = tr("German");
			if (d[dc] == "hyph_es.dic")
				datein = tr("Spanish");
			if (d[dc] == "hyph_it.dic")
				datein = tr("Italian");
			if (d[dc] == "hyph_fr.dic")
				datein = tr("French");
			if (d[dc] == "hyph_ru.dic")
				datein = tr("Russian");
			if (d[dc] == "hyph_da.dic")
				datein = tr("Danish");
			if (d[dc] == "hyph_sk.dic")
				datein = tr("Slovak");
			if (d[dc] == "hyph_hu.dic")
				datein = tr("Hungarian");
			if (d[dc] == "hyph_cs.dic")
				datein = tr("Czech");
			if (d[dc] == "hyph_nl.dic")
				datein = tr("Dutch");
			if (d[dc] == "hyph_pt.dic")
				datein = tr("Portuguese");
			if (d[dc] == "hyph_uk.dic")
				datein = tr("Ukrainian");
			if (d[dc] == "hyph_pl.dic")
				datein = tr("Polish");
			if (d[dc] == "hyph_el.dic")
				datein = tr("Greek");
			if (d[dc] == "hyph_ca.dic")
				datein = tr("Catalan");
			if (d[dc] == "hyph_fi.dic")
				datein = tr("Finnish");
			Sprachen.insert(datein, d[dc]);
			if (d[dc] == "hyph_"+lang+".dic")
				Prefs.Language = datein;
			}
		if (datein == "")
			Prefs.Language = tr("English");
		}
}

void ScribusApp::configHyphenator()
{
	HySettings *dia = new HySettings(this, &Sprachen);
	if (HaveDoc)
		{
		dia->Verbose->setChecked(doc->Trenner->Automatic);
		dia->Input->setChecked(doc->Trenner->AutoCheck);
		dia->Language->setCurrentText(doc->Trenner->Language);
		dia->WordLen->setValue(doc->Trenner->MinWordLen);
		}
	else
		{
		dia->Verbose->setChecked(Prefs.Automatic);
		dia->Input->setChecked(Prefs.AutoCheck);
		dia->Language->setCurrentText(Prefs.Language);
		dia->WordLen->setValue(Prefs.MinWordLen);
		}
	if (dia->exec())
		{
		if (HaveDoc)
			{
			doc->Trenner->slotNewDict(dia->Language->currentText());
			doc->Trenner->slotNewSettings(dia->WordLen->value(), dia->Verbose->isChecked(), dia->Input->isChecked());
			}
		else
			{
			Prefs.MinWordLen = dia->WordLen->value();
			Prefs.Language = dia->Language->currentText();
			Prefs.Automatic = dia->Verbose->isChecked();
			Prefs.AutoCheck = dia->Input->isChecked();
			}
		}
	delete dia;
}

void ScribusApp::doHyphenate()
{
	PageItem *b;
	if (HaveDoc)
		{
  	if (doc->ActPage->SelItem.count() != 0)
  		{
  		b = doc->ActPage->SelItem.at(0);
			if (doc->Trenner->Language != b->Language)
				doc->Trenner->slotNewDict(b->Language);
			doc->Trenner->slotHyphenate(b);
			}
		}
}

void ScribusApp::ToggleObjLock()
{
	if (HaveDoc)
		{
  	if (doc->ActPage->SelItem.count() != 0)
  		doc->ActPage->ToggleLock();
		}
}

void ScribusApp::ManageGuides()
{
	if (HaveDoc)
		{
		GuideManager *dia = new GuideManager(this, doc->ActPage, doc->Einheit);
		dia->exec();
		delete dia;
		}
}

void ScribusApp::SetTranspar(double t)
{
	PageItem *b;
	if (HaveDoc)
		{
  	if (doc->ActPage->SelItem.count() != 0)
			{
  		b = doc->ActPage->SelItem.at(0);
			b->Transparency = t;
			view->DrawNew();
			slotDocCh();
			}
		}
}

void ScribusApp::SetTransparS(double t)
{
	PageItem *b;
	if (HaveDoc)
		{
  	if (doc->ActPage->SelItem.count() != 0)
			{
  		b = doc->ActPage->SelItem.at(0);
			b->TranspStroke = t;
			view->DrawNew();
			slotDocCh();
			}
		}
}

void ScribusApp::InvertPict()
{
	PageItem *b;
	if (HaveDoc)
		{
  	if (doc->ActPage->SelItem.count() != 0)
			{
  		b = doc->ActPage->SelItem.at(0);
			b->InvPict = !b->InvPict;
			view->DrawNew();
			slotDocCh();
			}
		}
}

void ScribusApp::Collect()
{
	QString CurDirP = QDir::currentDirPath();
	QString s = QFileDialog::getExistingDirectory(QDir::currentDirPath(), this, "d", tr("Choose a Directory"), true);
	if (s != "")
		{
		if(s.right(1) != "/")
	  	s += "/";
		QFileInfo fi = QFileInfo(s);
		if (fi.exists())
			{
			if (fi.isDir() && fi.isWritable())
				{
				for (uint a = 0; a < view->MasterPages.count(); ++a)
					{
					for (uint b = 0; b < view->MasterPages.at(a)->Items.count(); ++b)
						{
						PageItem* ite = view->MasterPages.at(a)->Items.at(b);
						if (ite->PType == 2)
							{
							QFileInfo itf = QFileInfo(ite->Pfile);
							if (itf.exists())
								{
								QString cmd = "cp \"" + ite->Pfile + "\" \"" + s + itf.fileName()+"\"";
								system(cmd);
								ite->Pfile = s + itf.fileName();
								}
							}
						if (ite->PType == 4)
							{
							if (ite->isAnnotation)
								{
								QString cmd = "";
								QFileInfo itf;
								if (ite->Pfile != "")
									{
									itf = QFileInfo(ite->Pfile);
									if (itf.exists())
										{
										cmd = "cp \"" + ite->Pfile + "\" \"" + s + itf.fileName()+"\"";
										system(cmd);
										ite->Pfile = s + itf.fileName();
										}
									}
								if (ite->Pfile2 != "")
									{
									itf = QFileInfo(ite->Pfile2);
									if (itf.exists())
										{
										cmd = "cp \"" + ite->Pfile2 + "\" \"" + s + itf.fileName()+"\"";
										system(cmd);
										ite->Pfile2 = s + itf.fileName();
										}
									}
								if (ite->Pfile3 != "")
									{
									itf = QFileInfo(ite->Pfile3);
									if (itf.exists())
										{
										cmd = "cp \"" + ite->Pfile3 + "\" \"" + s + itf.fileName()+"\"";
										system(cmd);
										ite->Pfile3 = s + itf.fileName();
										}
									}
								}
							}
						}
					}
				for (uint a = 0; a < view->DocPages.count(); ++a)
					{
					for (uint b = 0; b < view->DocPages.at(a)->Items.count(); ++b)
						{
						PageItem* ite = view->DocPages.at(a)->Items.at(b);
						if (ite->PType == 2)
							{
							QFileInfo itf = QFileInfo(ite->Pfile);
							if (itf.exists())
								{
								QString	cmd = "cp \"" + ite->Pfile + "\" \"" + s + itf.fileName()+"\"";
								system(cmd);
								ite->Pfile = s + itf.fileName();
								}
							}
						if (ite->PType == 4)
							{
							if (ite->isAnnotation)
								{
								QString cmd = "";
								QFileInfo itf;
								if (ite->Pfile != "")
									{
									itf = QFileInfo(ite->Pfile);
									if (itf.exists())
										{
										cmd = "cp \"" + ite->Pfile + "\" \"" + s + itf.fileName()+"\"";
										system(cmd);
										ite->Pfile = s + itf.fileName();
										}
									}
								if (ite->Pfile2 != "")
									{
									itf = QFileInfo(ite->Pfile2);
									if (itf.exists())
										{
										cmd = "cp \"" + ite->Pfile2 + "\" \"" + s + itf.fileName()+"\"";
										system(cmd);
										ite->Pfile2 = s + itf.fileName();
										}
									}
								if (ite->Pfile3 != "")
									{
									itf = QFileInfo(ite->Pfile3);
									if (itf.exists())
										{
										cmd = "cp \"" + ite->Pfile3 + "\" \"" + s + itf.fileName()+"\"";
										system(cmd);
										ite->Pfile3 = s + itf.fileName();
										}
									}
								}
							}
						}
					}
				QString fn;
				if (doc->hasName)
					{
  				QFileInfo fis(doc->DocName);
  				fn = s + fis.fileName();
					}
				else
					fn = s + doc->DocName+".sla";
				if (!DoFileSave(fn))
					QMessageBox::warning(this, tr("Warning"), tr("Can't write the File: \n%1").arg(fn), tr("OK"));
				}
			}
		}
	QDir::setCurrent(CurDirP);
}

void ScribusApp::ReorgFonts()
{
	Page* pg;
	PageItem* it;
	QMap<QString,QFont> Really;
	QMap<QString,QFont> DocF;
	DocF = doc->UsedFonts;
	for (uint c = 0; c < view->MasterPages.count(); ++c)
		{
		pg = view->MasterPages.at(c);
		for (uint d = 0; d < pg->Items.count(); ++d)
			{
			it = pg->Items.at(d);
			Really.insert(it->IFont, doc->UsedFonts[it->IFont]);
			if ((it->PType == 4) || (it->PType == 8))
				{
				for (uint e = 0; e < it->Ptext.count(); ++e)
					{
					Really.insert(it->Ptext.at(e)->cfont, doc->UsedFonts[it->Ptext.at(e)->cfont]);
					}
				}
			}
		}
	for (uint c = 0; c < view->Pages.count(); ++c)
		{
		pg = view->Pages.at(c);
		for (uint d = 0; d < pg->Items.count(); ++d)
			{
			it = pg->Items.at(d);
			Really.insert(it->IFont, doc->UsedFonts[it->IFont]);
			if ((it->PType == 4) || (it->PType == 8))
				{
				for (uint e = 0; e < it->Ptext.count(); ++e)
					{
					Really.insert(it->Ptext.at(e)->cfont, doc->UsedFonts[it->Ptext.at(e)->cfont]);
					}
				}
			}
		}
	QMap<QString,QFont>::Iterator itfo;
	for (itfo = doc->UsedFonts.begin(); itfo != doc->UsedFonts.end(); ++itfo)
		{
		if (!Really.contains(itfo.key()))
			{
			FT_Done_Face(doc->FFonts[itfo.key()]);
			doc->FFonts.remove(itfo.key());
			doc->UsedFonts.remove(itfo);
			}
		}
	doc->AddFont(Prefs.DefFont, Prefs.AvailFonts[Prefs.DefFont]->Font);
	doc->AddFont(doc->Dfont, Prefs.AvailFonts[doc->Dfont]->Font);
	BuildFontMenu();
}

void ScribusApp::GetUsedFonts(QMap<QString,QFont> *Really)
{
	Page* pg;
	PageItem* it;
	FPointArray gly;
	QString chx;
	for (uint c = 0; c < view->MasterPages.count(); ++c)
		{
		pg = view->MasterPages.at(c);
		for (uint d = 0; d < pg->Items.count(); ++d)
			{
			it = pg->Items.at(d);
			if ((it->PType == 4) || (it->PType == 8))
				{
				for (uint e = 0; e < it->Ptext.count(); ++e)
					{
					Really->insert(it->Ptext.at(e)->cfont, doc->UsedFonts[it->Ptext.at(e)->cfont]);
					uint chr = it->Ptext.at(e)->ch[0].unicode();
					if ((chr == 13) || (chr == 32))
						continue;
					if (it->Ptext.at(e)->cstyle & 64)
						{
						chx = it->Ptext.at(e)->ch;
						if (chx.upper() != it->Ptext.at(e)->ch)
							chx = chx.upper();
						chr = chx[0].unicode();
						}
					if ((*doc->AllFonts)[it->Ptext.at(e)->cfont]->CharWidth.contains(chr))
						{
						gly = (*doc->AllFonts)[it->Ptext.at(e)->cfont]->GlyphArray[chr].Outlines.copy();
						(*doc->AllFonts)[it->Ptext.at(e)->cfont]->RealGlyphs.insert(chr, gly);
						}
					}
				}
			}
		}
	for (uint c = 0; c < view->Pages.count(); ++c)
		{
		pg = view->Pages.at(c);
		for (uint d = 0; d < pg->Items.count(); ++d)
			{
			it = pg->Items.at(d);
			if ((it->PType == 4) || (it->PType == 8))
				{
				for (uint e = 0; e < it->Ptext.count(); ++e)
					{
					Really->insert(it->Ptext.at(e)->cfont, doc->UsedFonts[it->Ptext.at(e)->cfont]);
					uint chr = it->Ptext.at(e)->ch[0].unicode();
					if ((chr == 13) || (chr == 32))
						continue;
					if (it->Ptext.at(e)->cstyle & 64)
						{
						chx = it->Ptext.at(e)->ch;
						if (chx.upper() != it->Ptext.at(e)->ch)
							chx = chx.upper();
						chr = chx[0].unicode();
						}
					if ((*doc->AllFonts)[it->Ptext.at(e)->cfont]->CharWidth.contains(chr))
						{
						gly = (*doc->AllFonts)[it->Ptext.at(e)->cfont]->GlyphArray[chr].Outlines.copy();
						(*doc->AllFonts)[it->Ptext.at(e)->cfont]->RealGlyphs.insert(chr, gly);
						}
					}
				}
			}
		}
}

void ScribusApp::HaveRaster(bool art)
{
 	if (doc->ActPage->SelItem.count() != 0)
		{
 		PageItem *b = doc->ActPage->SelItem.at(0);
		if ((b->PType == 2) && (art))
			{
			StilMenu->clear();
			StilMenu->insertItem( tr("Color"), ColorMenu);
			StilMenu->insertItem( tr("Invert"), this, SLOT(InvertPict()));
			}
		}
}

void ScribusApp::slotStoryEditor()
{
 	if (doc->ActPage->SelItem.count() != 0)
		{
 		PageItem *b = doc->ActPage->SelItem.at(0);
		StoryEditor* dia = new StoryEditor(this, doc, b);
		connect(dia, SIGNAL(DocChanged()), this, SLOT(slotDocCh()));
		connect(dia, SIGNAL(EditSt()), this, SLOT(slotEditStyles()));
		if (dia->exec())
			{
			if (dia->TextChanged)
				dia->updateTextFrame();
			}
		delete dia;
		}
}

void ScribusApp::defaultCrashHandler (int sig)
{
  static int crashRecursionCounter = 0;
  crashRecursionCounter++;
  signal(SIGALRM, SIG_DFL);
  if (crashRecursionCounter < 2)
		{
  	crashRecursionCounter++;
		QMessageBox::critical(ScApp, tr("Scribus Crash"), tr("Scribus crashes due to Signal #%1").arg(sig), tr("OK"));
  	alarm(300);
		ScApp->emergencySave();
		}
  exit(255);
}

void ScribusApp::emergencySave()
{
	std::cout << "Calling Emergency Save" << std::endl;
	QWidgetList windows = ScApp->wsp->windowList();
	if (!windows.isEmpty())
		{
		for ( int i = 0; i < static_cast<int>(windows.count()); ++i )
			{
			ActWin = (ScribusWin*)windows.at(i);
			doc = ActWin->doc;
			view = ActWin->view;
			doc->setUnModified();
			if (doc->hasName)
				{
				std::cout << "Saving: " << doc->DocName+".emergency" << std::endl;
  			doc->ASaveTimer->stop();
				disconnect(ActWin, SIGNAL(Schliessen()), ScApp, SLOT(DoFileClose()));
				disconnect(ActWin, SIGNAL(SaveAndClose()), ScApp, SLOT(DoSaveClose()));
 				ScriXmlDoc *ss = new ScriXmlDoc();
 				ss->WriteDoc(doc->DocName+".emergency", doc, view, 0);
 				delete ss;
				}
  		view->close();
  		for (uint a = 0; a<view->Pages.count(); ++a)
  			{
  			delete view->Pages.at(a);
  			}
			delete doc;
			ActWin->close();
			}
		}
}

void ScribusApp::EditTabs()
{
	if (HaveDoc)
		{
  	if (doc->ActPage->SelItem.count() != 0)
			{
			PageItem *b = doc->ActPage->SelItem.at(0);
			TabManager *dia = new TabManager(this, doc->Einheit, b->TabValues);
			if (dia->exec())
				{
				b->TabValues = dia->tmpTab;
				doc->ActPage->RefreshItem(b);
				slotDocCh();
				}
			delete dia;
			}
		}
}

void ScribusApp::SearchText()
{
	PageItem *b = doc->ActPage->SelItem.at(0);
	setAppMode(7);
	b->CPos = 0;
	SearchReplace* dia = new SearchReplace(this, doc, &Prefs, b);
	connect(dia, SIGNAL(NewFont(QString)), this, SLOT(SetNewFont(QString)));
	connect(dia, SIGNAL(NewAbs(int)), this, SLOT(setAbsValue(int)));
	dia->exec();
	disconnect(dia, SIGNAL(NewFont(QString)), this, SLOT(SetNewFont(QString)));
	disconnect(dia, SIGNAL(NewAbs(int)), this, SLOT(setAbsValue(int)));
	delete dia;
	slotSelect();
}

void ScribusApp::slotTest()
{
}

void ScribusApp::slotTest2()
{
}
