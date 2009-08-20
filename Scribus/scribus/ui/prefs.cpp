/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#include <QList>
#include <QPixmap>
#include <QStackedWidget>

#include "ui/arrowchooser.h"
#include "ui/cmsprefs.h"
#include "ui/colorcombo.h"
#include "commonstrings.h"
#include "ui/docitemattrprefs.h"
#include "ui/fontcombo.h"
#include "ui/fontprefs.h"
#include "hyphenator.h"
#include "ui/hysettings.h"
#include "langmgr.h"
#include "ui/linecombo.h"
#include "ui/marginwidget.h"
#include "pagelayout.h"
#include "pagesize.h"
#include "pagestructs.h"
#include "pluginmanager.h"
#include "ui/pluginmanagerprefsgui.h"
#include "ui/polygonwidget.h"
#include "prefs.h"
#include "prefsfile.h"
#include "prefsmanager.h"
#include "sccombobox.h"
#include "scpaths.h"
#include "scplugin.h"
#include "scribusapp.h"
#include "scribuscore.h"
#include "scribusdoc.h"
#include "scribusstructs.h"
#include "ui/tabcheckdoc.h"
#include "ui/tabdisplay.h"
#include "ui/tabdocument.h"
#include "ui/tabexternaltoolswidget.h"
#include "ui/tabgeneral.h"
#include "ui/tabguides.h"
#include "ui/tabkeyboardshortcutswidget.h"
#include "ui/tabmiscellaneous.h"
#include "ui/tabpdfoptions.h"
#include "ui/tabprinter.h"
#include "ui/tabscrapbook.h"
#include "ui/tabtools.h"
#include "ui/tabtypography.h"
#include "ui/tocindexprefs.h"
#include "undomanager.h"
#include "units.h"
#include "units.h"
#include "util_icon.h"

using namespace std;

extern ScribusQApp* ScQApp;

Preferences::Preferences( QWidget* parent) : PrefsDialogBase( parent )
{
	setObjectName(QString::fromLocal8Bit("PreferencesWindow"));
	prefsManager=PrefsManager::instance();
	ApplicationPrefs* prefsData=&(prefsManager->appPrefs);
	ap = (ScribusMainWindow*)parent;
	docUnitIndex = prefsData->docSetupPrefs.docUnitIndex;
	unitRatio = unitGetRatioFromIndex(docUnitIndex);


	setWindowTitle( tr( "Preferences" ) );

	tabGeneral = new TabGeneral( prefsWidgets, "tabGeneral" );
	addItem( tr("General"), loadIcon("scribus.png"), tabGeneral);

	tabDocument = new TabDocument( prefsWidgets, "tabDocument" );
	addItem( tr("Document"), loadIcon("scribusdoc.png"), tabDocument);

	tabGuides = new TabGuides(prefsWidgets, &prefsData->guidesPrefs, &prefsData->typographicSettings, docUnitIndex);
	addItem( tr("Guides"), loadIcon("guides.png"), tabGuides);

	tabTypo = new TabTypograpy(prefsWidgets, &prefsData->typographicSettings);
	addItem( tr("Typography"), loadIcon("typography.png"), tabTypo);

	tabTools = new TabTools(prefsWidgets, &prefsData->toolSettings, docUnitIndex, ap->doc);
	addItem( tr("Tools"), loadIcon("tools.png"), tabTools);

	tabHyphenator = new HySettings(prefsWidgets/*, &ap->LangTransl*/);
	addItem( tr("Hyphenator"), loadIcon("hyphenate.png"), tabHyphenator);

	tabFonts = new FontPrefs(prefsWidgets, false, prefsManager->preferencesLocation(), ap->doc);
	addItem( tr("Fonts"), loadIcon("font.png"), tabFonts);

	tabPrinter = new TabPrinter(prefsWidgets, "tabPrinter");
	addItem( tr("Printer"), loadIcon("printer.png"), tabPrinter);

	tabDocChecker = new TabCheckDoc(prefsWidgets, prefsData->checkerProfiles, prefsData->curCheckProfile);
	addItem( tr("Preflight Verifier"), loadIcon("checkdoc.png"), tabDocChecker);

	if (ScCore->haveCMS())
	{
		tabColorManagement = new CMSPrefs(prefsWidgets, &prefsData->DCMSset, &ScCore->InputProfiles, &ScCore->InputProfilesCMYK, &ScCore->PrinterProfiles, &ScCore->MonitorProfiles);
		addItem( tr("Color Management"), loadIcon("blend.png"), tabColorManagement);
	}

	QMap<QString, int> DocFonts;
	DocFonts.clear();
	tabPDF = new TabPDFOptions( prefsWidgets,
								prefsData->PDF_Options,
								prefsData->AvailFonts,
								ScCore->PDFXProfiles,
								DocFonts,
								prefsData->PDF_Options.PresentVals,
								docUnitIndex,
								prefsData->docSetupPrefs.pageHeight,
								prefsData->docSetupPrefs.pageWidth,
								0 );
	addItem( tr("PDF Export"), loadIcon("acroread32.png"), tabPDF);

	tabDefaultItemAttributes = new DocumentItemAttributes(prefsWidgets);
	QStringList defaultAttributesList=tabDefaultItemAttributes->getDocAttributesNames();
	tabDefaultItemAttributes->setup(&prefsData->defaultItemAttributes);
	addItem( tr("Document Item Attributes"), loadIcon("docattributes.png"), tabDefaultItemAttributes);

	tabDefaultTOCIndexPrefs = new TOCIndexPrefs(prefsWidgets );
	tabDefaultTOCIndexPrefs->setupItemAttrs( defaultAttributesList );
	tabDefaultTOCIndexPrefs->setup(&prefsData->defaultToCSetups, NULL);
	addItem( tr("Table of Contents and Indexes"), loadIcon("tabtocindex.png"), tabDefaultTOCIndexPrefs);

	tabKeyboardShortcuts = new TabKeyboardShortcutsWidget(prefsData->KeyActions, prefsWidgets);
	addItem( tr("Keyboard Shortcuts"), loadIcon("key_bindings.png"), tabKeyboardShortcuts);

	tabScrapbook = new TabScrapbook( prefsWidgets );
	addItem(  tr("Scrapbook"), loadIcon("scrap.png"), tabScrapbook);

	tabView = new TabDisplay(prefsWidgets, "tabView");
	addItem( tr("Display"), loadIcon("screen.png"), tabView);

	tabExtTools = new TabExternalToolsWidget( prefsData, prefsWidgets );
	addItem(  tr("External Tools"), loadIcon("externaltools.png"), tabExtTools);

	tabMiscellaneous = new TabMiscellaneous(prefsWidgets);
	addItem(  tr("Miscellaneous"), loadIcon("misc.png"), tabMiscellaneous);

	// plugin manager. pv.
	pluginManagerPrefsGui = new PluginManagerPrefsGui(prefsWidgets, ap);
	addItem( tr("Plugins"), loadIcon("plugins.png"), pluginManagerPrefsGui );

	setupGui();
	addPlugins();

	setDS(prefsData->docSetupPrefs.pagePositioning);

	resize( minimumSizeHint() );
	prefsSelection->arrangeIcons();
	prefsSelection->item(0)->setSelected(true);
	itemSelected(prefsSelection->item(0));
}

void Preferences::enableSignals(bool on)
{
	if (on)
	{
		connect(tabDocument->unitCombo, SIGNAL(activated(int)), this, SLOT(unitChange()));
 		connect(tabDocument->docLayout, SIGNAL( selectedLayout(int) ), this, SLOT( setDS(int) ) );
		connect(buttonOk, SIGNAL(clicked()), this, SLOT(setActionHistoryLength()));
		if (ScCore->haveCMS())
			connect(tabColorManagement, SIGNAL(cmsOn(bool )), this, SLOT(switchCMS(bool )));
		connect(applyChangesButton, SIGNAL(clicked()), this, SLOT(applyChangesButton_clicked()));
		connect(backToDefaults, SIGNAL(clicked()), this, SLOT(backToDefaults_clicked()));
		connect(this, SIGNAL(aboutToShow(QWidget *)), this, SLOT(showWidgetInStack(QWidget *)));
		connect(this, SIGNAL(accepted()), pluginManagerPrefsGui, SLOT(apply()));
	}
	else
	{
		disconnect(tabDocument->unitCombo, SIGNAL(activated(int)), this, SLOT(unitChange()));
		disconnect(tabDocument->docLayout, SIGNAL( selectedLayout(int) ), this, SLOT( setDS(int) ) );
		disconnect(buttonOk, SIGNAL(clicked()), this, SLOT(setActionHistoryLength()));
		if (ScCore->haveCMS())
			disconnect(tabColorManagement, SIGNAL(cmsOn(bool )), this, SLOT(switchCMS(bool )));
		disconnect(applyChangesButton, SIGNAL(clicked()), this, SLOT(applyChangesButton_clicked()));
		disconnect(backToDefaults, SIGNAL(clicked()), this, SLOT(backToDefaults_clicked()));
		disconnect(this, SIGNAL(aboutToShow(QWidget *)), this, SLOT(showWidgetInStack(QWidget *)));
		disconnect(this, SIGNAL(accepted()), pluginManagerPrefsGui, SLOT(apply()));
	}
}

void Preferences::restoreDefaults()
{
	prefsManager->initDefaults();
	setupGui();
}

void Preferences::setupGui()
{
	enableSignals(false);
	ApplicationPrefs* prefsData=&(prefsManager->appPrefs);

	tabGeneral->restoreDefaults(prefsData);
	tabDocument->restoreDefaults(prefsData);
	tabPrinter->restoreDefaults(prefsData);
	tabView->restoreDefaults(prefsData, prefsData->guidesPrefs, prefsData->pageSets, prefsData->docSetupPrefs.pagePositioning, prefsData->scratch);
	tabView->gapHorizontal->setValue(prefsData->GapHorizontal); // * unitRatio);
	tabView->gapVertical->setValue(prefsData->GapVertical); // * unitRatio);
	tabScrapbook->restoreDefaults(prefsData);
	tabHyphenator->restoreDefaults(prefsData);
	tabGuides->restoreDefaults(&prefsData->guidesPrefs, &prefsData->typographicSettings, docUnitIndex);
	tabTypo->restoreDefaults(&prefsData->typographicSettings);
	tabTools->restoreDefaults(&prefsData->toolSettings, docUnitIndex);
	// main performance issue in availFonts->GetFonts(HomeP)!
	// no prefsData here
	tabFonts->restoreDefaults();
	tabDocChecker->restoreDefaults(&prefsData->checkerProfiles, prefsData->curCheckProfile);

	QMap<QString, int> DocFonts;
	DocFonts.clear();
	tabPDF->restoreDefaults(prefsData->PDF_Options,
							prefsData->AvailFonts,
							ScCore->PDFXProfiles,
							DocFonts,
							prefsData->PDF_Options.PresentVals,
							docUnitIndex,
							prefsData->docSetupPrefs.pageHeight,
							prefsData->docSetupPrefs.pageWidth,
							0, false);

	if (ScCore->haveCMS())
		tabColorManagement->restoreDefaults(&prefsData->DCMSset, &ScCore->InputProfiles,
										 &ScCore->InputProfilesCMYK,
										 &ScCore->PrinterProfiles, &ScCore->MonitorProfiles);
	QStringList defaultAttributesList=tabDefaultItemAttributes->getDocAttributesNames();
	tabDefaultItemAttributes->setup(&prefsData->defaultItemAttributes);
	tabDefaultTOCIndexPrefs->setupItemAttrs( defaultAttributesList );
	tabDefaultTOCIndexPrefs->setup(&prefsData->defaultToCSetups, NULL);
	tabKeyboardShortcuts->restoreDefaults();
	tabExtTools->restoreDefaults(prefsData);
	tabMiscellaneous->restoreDefaults(prefsData);
	enableSignals(true);
	unitChange();
}

void Preferences::addPlugins()
{
	// Scan for plugins that provide a prefs widget, and add it to the
	// prefs dialog.
	// For each plugin, enabled or not:
	ScPlugin* plugin = 0;
	PrefsPanel* panel = 0;
	QString panelCaption;
	QPixmap panelIcon;

	PluginManager& pluginManager = PluginManager::instance();
	QStringList pluginNames(pluginManager.pluginNames(true));

	foreach (QString pName, pluginManager.pluginNames(true))
	{
		// Ask the plugin manager for a plugin (skipping disabled plugins).
		plugin = pluginManager.getPlugin(pName, false);
		// If we got a plugin (which we know is enabled):
		if (plugin)
		{
			// Ask the plugin for a prefs widget
			bool wantPanel = plugin->newPrefsPanelWidget(prefsWidgets, panel, panelCaption, panelIcon);
			// If it gave us one...
			if (wantPanel)
			{
				// Ensure that we got sane return values
				Q_ASSERT(panel);
				Q_ASSERT(!panelIcon.isNull());
				Q_ASSERT(!panelCaption.isNull());
				// plug it in to the dialog,
				addItem(panelCaption, panelIcon, panel);
				// and connect a signal to tell it to save its
				// settings.
				connect(this, SIGNAL(accepted()), panel, SLOT(apply()));
			}
		}
	}
}

void Preferences::accept()
{
	emit accepted();
	return PrefsDialogBase::accept();
}

void Preferences::setDS(int layout)
{
	tabDocument->marginGroup->setFacingPages(!(layout == singlePage));
	tabDocument->choosenLayout = layout;
	tabDocument->docLayout->firstPage->setCurrentIndex(prefsManager->appPrefs.pageSets[tabDocument->choosenLayout].FirstPage);
//	tabView->gapHorizontal->setValue(prefsManager->appPrefs.pageSets[tabDocument->choosenLayout].GapHorizontal * unitRatio);
//	tabView->gapVertical->setValue(prefsManager->appPrefs.pageSets[tabDocument->choosenLayout].GapBelow * unitRatio);
//	tabView->gapHorizontal->setValue(prefsManager->appPrefs.GapHorizontal * unitRatio);
//	tabView->gapVertical->setValue(prefsManager->appPrefs.GapVertical * unitRatio);
}

void Preferences::unitChange()
{
	double oldUnitRatio = unitRatio;
	docUnitIndex = tabDocument->unitCombo->currentIndex();
	unitRatio = unitGetRatioFromIndex(docUnitIndex);
	QString suffix = unitGetSuffixFromIndex(docUnitIndex);
	double invUnitConversion = 1.0 / oldUnitRatio * unitRatio;
	
	tabDocument->unitChange();
	tabGuides->unitChange(suffix, docUnitIndex, invUnitConversion);
	tabView->unitChange(docUnitIndex);
	tabTools->unitChange(docUnitIndex);
	tabPDF->unitChange(suffix, docUnitIndex, invUnitConversion);
	tabPrinter->unitChange(suffix, docUnitIndex, invUnitConversion);
}


void Preferences::setActionHistoryLength()
{
	PrefsContext *undoPrefs = PrefsManager::instance()->prefsFile->getContext("undo");
	bool isEnabled = tabDocument->urGroup->isChecked();
	if (!isEnabled)
		UndoManager::instance()->clearStack();
	UndoManager::instance()->setUndoEnabled(isEnabled);
	undoPrefs->set("enabled", isEnabled);
	UndoManager::instance()->setAllHistoryLengths(tabDocument->urSpinBox->value());
}

void Preferences::switchCMS(bool enable)
{
	tabPDF->enableCMS(enable);
}

void Preferences::showWidgetInStack(QWidget *widgetToShow)
{
	//Update the attributes list in TOC setup
	if (widgetToShow==tabDefaultTOCIndexPrefs)
		tabDefaultTOCIndexPrefs->setupItemAttrs( tabDefaultItemAttributes->getDocAttributesNames() );
	if (widgetToShow == tabTools)
		tabTools->enableFontPreview(true);
}

void Preferences::updatePreferences()
{
	double prefsUnitRatio = unitGetRatioFromIndex(tabDocument->unitCombo->currentIndex());

	prefsManager->appPrefs.uiPrefs.applicationFontSize = tabGeneral->GFsize->value();
	prefsManager->appPrefs.uiPrefs.paletteFontSize = tabGeneral->GTFsize->value();
	ScQApp->neverSplash(!tabGeneral->showSplashCheckBox->isChecked());
	prefsManager->appPrefs.uiPrefs.showStartupDialog = tabGeneral->startUpDialog->isChecked();
	prefsManager->appPrefs.uiPrefs.wheelJump = tabGeneral->wheelJumpSpin->value();
	prefsManager->appPrefs.uiPrefs.mouseMoveTimeout = tabGeneral->spinTimeout->value();
	prefsManager->appPrefs.uiPrefs.recentDocCount = tabGeneral->recentDocs->value();
	prefsManager->appPrefs.pathPrefs.documents = QDir::fromNativeSeparators( tabGeneral->Docs->text() );
	prefsManager->appPrefs.pathPrefs.colorProfiles = QDir::fromNativeSeparators( tabGeneral->ProPfad->text() );
	prefsManager->appPrefs.pathPrefs.scripts = QDir::fromNativeSeparators( tabGeneral->ScriptPfad->text() );
	prefsManager->appPrefs.pathPrefs.documentTemplates = QDir::fromNativeSeparators( tabGeneral->DocumentTemplateDir->text() );
	prefsManager->appPrefs.uiPrefs.language=tabGeneral->selectedGUILang;
	prefsManager->appPrefs.uiPrefs.style = tabGeneral->GUICombo->currentText();
	prefsManager->appPrefs.uiPrefs.useSmallWidgets = tabGeneral->useSmallWidgetsCheck->isChecked();

	prefsManager->appPrefs.GapHorizontal = tabView->gapHorizontal->value() / prefsUnitRatio;
	prefsManager->appPrefs.GapVertical = tabView->gapVertical->value() / prefsUnitRatio;
	prefsManager->appPrefs.marginColored = tabView->checkUnprintable->isChecked();
	prefsManager->appPrefs.scratch.Bottom = tabView->bottomScratch->value() / prefsUnitRatio;
	prefsManager->appPrefs.scratch.Left = tabView->leftScratch->value() / prefsUnitRatio;
	prefsManager->appPrefs.scratch.Right = tabView->rightScratch->value() / prefsUnitRatio;
	prefsManager->appPrefs.scratch.Top = tabView->topScratch->value() / prefsUnitRatio;
	// GUI colors
	prefsManager->appPrefs.showPageShadow = tabView->checkShowPageShadow->isChecked();
	prefsManager->appPrefs.DpapColor = tabView->colorPaper;
	prefsManager->appPrefs.DFrameColor = tabView->colorFrame;
	prefsManager->appPrefs.DFrameNormColor = tabView->colorFrameNorm;
	prefsManager->appPrefs.DFrameGroupColor = tabView->colorFrameGroup;
	prefsManager->appPrefs.DFrameLockColor = tabView->colorFrameLocked;
	prefsManager->appPrefs.DFrameLinkColor = tabView->colorFrameLinked;
	prefsManager->appPrefs.DFrameAnnotationColor = tabView->colorFrameAnnotation;
	prefsManager->appPrefs.DPageBorderColor = tabView->colorPageBorder;
	prefsManager->appPrefs.DControlCharColor = tabView->colorControlChars;
	// Guides

	prefsManager->appPrefs.guidesPrefs.framesShown = tabView->checkFrame->isChecked();
	prefsManager->appPrefs.guidesPrefs.showBleed = tabView->checkBleed->isChecked();
	prefsManager->appPrefs.guidesPrefs.layerMarkersShown = tabView->checkLayerM->isChecked();
	prefsManager->appPrefs.guidesPrefs.rulerMode = tabView->checkRuler->isChecked();
	prefsManager->appPrefs.guidesPrefs.showPic = tabView->checkPictures->isChecked();
	prefsManager->appPrefs.guidesPrefs.linkShown = tabView->checkLink->isChecked();
	prefsManager->appPrefs.guidesPrefs.showControls = tabView->checkControl->isChecked();
	prefsManager->appPrefs.DisScale = tabView->DisScale;

	prefsManager->appPrefs.doCopyToScrapbook = tabScrapbook->useScrapBookasExtension->isChecked();
	prefsManager->appPrefs.persistentScrapbook = tabScrapbook->persistentScrapbook->isChecked();
	prefsManager->appPrefs.numScrapbookCopies = tabScrapbook->numScrapCopies->value();

	tabTools->polyWidget->getValues(&prefsManager->appPrefs.toolSettings.polyC,
									&prefsManager->appPrefs.toolSettings.polyFd,
									&prefsManager->appPrefs.toolSettings.polyF,
									&prefsManager->appPrefs.toolSettings.polyS,
									&prefsManager->appPrefs.toolSettings.polyR,
									&prefsManager->appPrefs.toolSettings.polyCurvature);

	prefsManager->appPrefs.docSetupPrefs.pageSize = tabDocument->prefsPageSizeName;
	prefsManager->appPrefs.docSetupPrefs.pageOrientation = tabDocument->pageOrientationComboBox->currentIndex();
	prefsManager->appPrefs.docSetupPrefs.pageWidth = tabDocument->pageW;
	prefsManager->appPrefs.docSetupPrefs.pageHeight = tabDocument->pageH;

	prefsManager->appPrefs.docSetupPrefs.margins.Top = tabDocument->marginGroup->top();
	prefsManager->appPrefs.docSetupPrefs.margins.Bottom = tabDocument->marginGroup->bottom();
	prefsManager->appPrefs.docSetupPrefs.margins.Left = tabDocument->marginGroup->left();
	prefsManager->appPrefs.docSetupPrefs.margins.Right = tabDocument->marginGroup->right();
	prefsManager->appPrefs.docSetupPrefs.marginPreset = tabDocument->marginGroup->getMarginPreset();
	prefsManager->appPrefs.docSetupPrefs.pagePositioning  = tabDocument->choosenLayout;
	prefsManager->appPrefs.docSetupPrefs.bleeds.Bottom = tabDocument->marginGroup->bottomBleed();
	prefsManager->appPrefs.docSetupPrefs.bleeds.Top = tabDocument->marginGroup->topBleed();
	prefsManager->appPrefs.docSetupPrefs.bleeds.Left = tabDocument->marginGroup->leftBleed();
	prefsManager->appPrefs.docSetupPrefs.bleeds.Right = tabDocument->marginGroup->rightBleed();
	prefsManager->appPrefs.pageSets[tabDocument->choosenLayout].FirstPage = tabDocument->docLayout->firstPage->currentIndex();

	prefsManager->setImageEditorExecutable(tabExtTools->newImageTool());
	prefsManager->setExtBrowserExecutable(tabExtTools->newExtBrowserTool());
	prefsManager->appPrefs.gs_AntiAliasGraphics = tabExtTools->newAntialiasGraphics();
	prefsManager->appPrefs.gs_AntiAliasText = tabExtTools->newAntialiasText();
	prefsManager->setGhostscriptExecutable(tabExtTools->newPSTool());
	prefsManager->appPrefs.gs_Resolution = tabExtTools->newPSToolResolution();
	
	prefsManager->appPrefs.latexResolution = tabExtTools->newLatexToolResolution();
	prefsManager->appPrefs.latexForceDpi = tabExtTools->newLatexForceDpi();
	prefsManager->appPrefs.latexStartWithEmptyFrames = tabExtTools->newLatexStartWithEmptyFrames();
	prefsManager->setLatexConfigs(tabExtTools->newLatexConfigs());
	prefsManager->setLatexCommands(tabExtTools->newLatexCommands());
	prefsManager->setLatexEditorExecutable(tabExtTools->newLatexEditor());

	prefsManager->appPrefs.guidesPrefs.guidePlacement = tabGuides->inBackground->isChecked();
	
	prefsManager->appPrefs.askBeforeSubstituite = tabMiscellaneous->AskForSubs->isChecked();
	prefsManager->appPrefs.haveStylePreview = tabMiscellaneous->stylePreview->isChecked();
	// lorem ipsum
	prefsManager->appPrefs.useStandardLI = tabMiscellaneous->useStandardLI->isChecked();
	prefsManager->appPrefs.paragraphsLI = tabMiscellaneous->paragraphsLI->value();

	prefsManager->appPrefs.docSetupPrefs.docUnitIndex = tabDocument->unitCombo->currentIndex();

	prefsManager->appPrefs.toolSettings.defFont = tabTools->fontComboText->currentText();
	prefsManager->appPrefs.toolSettings.defSize = tabTools->sizeComboText->currentText().left(2).toInt() * 10;

	prefsManager->appPrefs.guidesPrefs.marginsShown = tabGuides->marginBox->isChecked();
	prefsManager->appPrefs.guidesPrefs.gridShown = tabGuides->checkGrid->isChecked();
	prefsManager->appPrefs.guidesPrefs.guidesShown = tabGuides->guideBox->isChecked();
	prefsManager->appPrefs.guidesPrefs.baselineGridShown = tabGuides->baselineBox->isChecked();
	prefsManager->appPrefs.guidesPrefs.grabRadius = tabGuides->grabDistance->value();
	prefsManager->appPrefs.guidesPrefs.guideRad = tabGuides->snapDistance->value();
	prefsManager->appPrefs.guidesPrefs.minorGridSpacing = tabGuides->minorSpace->value() / prefsUnitRatio;
	prefsManager->appPrefs.guidesPrefs.majorGridSpacing = tabGuides->majorSpace->value() / prefsUnitRatio;
	prefsManager->appPrefs.guidesPrefs.minorGridColor = tabGuides->colorMinorGrid;
	prefsManager->appPrefs.guidesPrefs.majorGridColor = tabGuides->colorMajorGrid;
	prefsManager->appPrefs.guidesPrefs.marginColor = tabGuides->colorMargin;
	prefsManager->appPrefs.guidesPrefs.guideColor = tabGuides->colorGuides;
	prefsManager->appPrefs.guidesPrefs.baselineGridColor = tabGuides->colorBaselineGrid;
	prefsManager->appPrefs.checkerProfiles = tabDocChecker->checkerProfile;
	prefsManager->appPrefs.curCheckProfile = tabDocChecker->curCheckProfile->currentText();
	prefsManager->appPrefs.typographicSettings.valueSuperScript = tabTypo->superDisplacement->value();
	prefsManager->appPrefs.typographicSettings.scalingSuperScript = tabTypo->superScaling->value();
	prefsManager->appPrefs.typographicSettings.valueSubScript = tabTypo->subDisplacement->value();
	prefsManager->appPrefs.typographicSettings.scalingSubScript = tabTypo->subScaling->value();
	prefsManager->appPrefs.typographicSettings.valueSmallCaps = tabTypo->capsScaling->value();
	prefsManager->appPrefs.typographicSettings.autoLineSpacing = tabTypo->autoLine->value();
	prefsManager->appPrefs.guidesPrefs.valueBaselineGrid = tabGuides->baseGrid->value(); // / prefsUnitRatio;
	prefsManager->appPrefs.guidesPrefs.offsetBaselineGrid = tabGuides->baseOffset->value(); // / prefsUnitRatio;
	prefsManager->appPrefs.typographicSettings.valueUnderlinePos = qRound(tabTypo->underlinePos->value() * 10);
	prefsManager->appPrefs.typographicSettings.valueUnderlineWidth = qRound(tabTypo->underlineWidth->value() * 10);
	prefsManager->appPrefs.typographicSettings.valueStrikeThruPos = qRound(tabTypo->strikethruPos->value() * 10);
	prefsManager->appPrefs.typographicSettings.valueStrikeThruWidth = qRound(tabTypo->strikethruWidth->value() * 10);
	prefsManager->appPrefs.toolSettings.dTextBackGround = tabTools->colorComboTextBackground->currentText();
	if (prefsManager->appPrefs.toolSettings.dTextBackGround == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dTextBackGround = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.dTextLineColor = tabTools->colorComboTextLine->currentText();
	if (prefsManager->appPrefs.toolSettings.dTextLineColor == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dTextLineColor = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.dTextBackGroundShade = tabTools->shadingTextBack->value();
	prefsManager->appPrefs.toolSettings.dTextLineShade = tabTools->shadingTextLine->value();
	prefsManager->appPrefs.toolSettings.dTextPenShade = tabTools->shadingText->value();
	prefsManager->appPrefs.toolSettings.dTextStrokeShade = tabTools->shadingTextStroke->value();
	prefsManager->appPrefs.toolSettings.dPen = tabTools->colorComboLineShape->currentText();
	if (prefsManager->appPrefs.toolSettings.dPen == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dPen = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.dPenText = tabTools->colorComboText->currentText();
	if (prefsManager->appPrefs.toolSettings.dPenText == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dPenText = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.dStrokeText = tabTools->colorComboStrokeText->currentText();
	if (prefsManager->appPrefs.toolSettings.dStrokeText == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dStrokeText = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.dCols = tabTools->columnsText->value();
	prefsManager->appPrefs.toolSettings.dGap = tabTools->gapText->value() / prefsUnitRatio;
	prefsManager->appPrefs.toolSettings.dTabWidth = tabTools->gapTab->value() / prefsUnitRatio;
	prefsManager->appPrefs.toolSettings.dBrush = tabTools->comboFillShape->currentText();
	if (prefsManager->appPrefs.toolSettings.dBrush == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dBrush = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.dShade = tabTools->shadingFillShape->value();
	prefsManager->appPrefs.toolSettings.dShade2 = tabTools->shadingLineShape->value();
	switch (tabTools->tabFillCombo->currentIndex())
	{
		case 0:
			prefsManager->appPrefs.toolSettings.tabFillChar = "";
			break;
		case 1:
			prefsManager->appPrefs.toolSettings.tabFillChar = ".";
			break;
		case 2:
			prefsManager->appPrefs.toolSettings.tabFillChar = "-";
			break;
		case 3:
			prefsManager->appPrefs.toolSettings.tabFillChar = "_";
			break;
		case 4:
			prefsManager->appPrefs.toolSettings.tabFillChar = tabTools->tabFillCombo->currentText().right(1);
			break;
	}
	prefsManager->appPrefs.toolSettings.dLineArt = static_cast<Qt::PenStyle>(tabTools->comboStyleShape->currentIndex()) + 1;
	prefsManager->appPrefs.toolSettings.dWidth = tabTools->lineWidthShape->value();
	prefsManager->appPrefs.toolSettings.dPenLine = tabTools->colorComboLine->currentText();
	if (prefsManager->appPrefs.toolSettings.dPenLine == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dPenLine = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.dShadeLine = tabTools->shadingLine->value();
	prefsManager->appPrefs.toolSettings.dLstyleLine = static_cast<Qt::PenStyle>(tabTools->comboStyleLine->currentIndex()) + 1;
	prefsManager->appPrefs.toolSettings.dWidthLine = tabTools->lineWidthLine->value();
	prefsManager->appPrefs.toolSettings.dStartArrow = tabTools->startArrow->currentIndex();
	prefsManager->appPrefs.toolSettings.dEndArrow = tabTools->endArrow->currentIndex();
	prefsManager->appPrefs.toolSettings.magMin = tabTools->minimumZoom->value();
	prefsManager->appPrefs.toolSettings.magMax = tabTools->maximumZoom->value();
	prefsManager->appPrefs.toolSettings.magStep = tabTools->zoomStep->value();
	prefsManager->appPrefs.toolSettings.dBrushPict = tabTools->comboFillImage->currentText();
	if (prefsManager->appPrefs.toolSettings.dBrushPict == CommonStrings::tr_NoneColor)
		prefsManager->appPrefs.toolSettings.dBrushPict = CommonStrings::None;
	prefsManager->appPrefs.toolSettings.shadePict = tabTools->shadingFillImage->value();
	prefsManager->appPrefs.toolSettings.scaleX = static_cast<double>(tabTools->scalingHorizontal->value()) / 100.0;
	prefsManager->appPrefs.toolSettings.scaleY = static_cast<double>(tabTools->scalingVertical->value()) / 100.0;
	prefsManager->appPrefs.toolSettings.scaleType = tabTools->buttonGroup3->isChecked();
	prefsManager->appPrefs.toolSettings.aspectRatio = tabTools->checkRatioImage->isChecked();
	prefsManager->appPrefs.toolSettings.useEmbeddedPath = tabTools->embeddedPath->isChecked();
	int haRes = 0;
	if (tabTools->checkFullRes->isChecked())
		haRes = 0;
	if (tabTools->checkNormalRes->isChecked())
		haRes = 1;
	if (tabTools->checkHalfRes->isChecked())
		haRes = 2;
	prefsManager->appPrefs.toolSettings.lowResType = haRes;
	prefsManager->appPrefs.toolSettings.dispX = tabTools->genDispX->value();
	prefsManager->appPrefs.toolSettings.dispY = tabTools->genDispY->value();
	prefsManager->appPrefs.toolSettings.constrain = tabTools->genRot->value();
	prefsManager->appPrefs.AutoSave = tabDocument->GroupAS->isChecked();
	prefsManager->appPrefs.AutoSaveTime = tabDocument->ASTime->value() * 60 * 1000;
	prefsManager->appPrefs.MinWordLen = tabHyphenator->getWordLen();
	prefsManager->appPrefs.Language = ScCore->primaryMainWindow()->GetLang(tabHyphenator->getLanguage());
	prefsManager->appPrefs.Automatic = !tabHyphenator->getVerbose();
	prefsManager->appPrefs.AutoCheck = tabHyphenator->getInput();
	prefsManager->appPrefs.HyCount = tabHyphenator->getMaxCount();
	prefsManager->appPrefs.ignoredWords = tabHyphenator->getIgnoreList();
	prefsManager->appPrefs.specialWords = tabHyphenator->getExceptionList();
	if (ScCore->haveCMS())
		tabColorManagement->setValues();
	// not required propably as it's done already in the dialog prefsManager->appPrefs.AvailFonts == get fonts from fontprefs
	uint a = 0;
	QMap<QString,QString>::Iterator itfsuend=tabFonts->RList.end();
	prefsManager->appPrefs.GFontSub.clear();
	for (QMap<QString,QString>::Iterator itfsu = tabFonts->RList.begin(); itfsu != itfsuend; ++itfsu)
		prefsManager->appPrefs.GFontSub[itfsu.key()] = tabFonts->FlagsRepl.at(a++)->currentText();
	
	prefsManager->appPrefs.defaultItemAttributes = *(tabDefaultItemAttributes->getNewAttributes());
	prefsManager->appPrefs.defaultToCSetups = *(tabDefaultTOCIndexPrefs->getNewToCs());
// 	prefsManager->appPrefs.KeyActions = tabKeys->getNewKeyMap();
	prefsManager->appPrefs.KeyActions = tabKeyboardShortcuts->getNewKeyMap();
	tabPDF->storeValues(prefsManager->appPrefs.PDF_Options);
	tabPrinter->storeValues();
}

void Preferences::applyChangesButton_clicked()
{
	ScCore->primaryMainWindow()->prefsOrg(this);
}

void Preferences::backToDefaults_clicked()
{
	prefsManager->initDefaults();
	restoreDefaults();
}
