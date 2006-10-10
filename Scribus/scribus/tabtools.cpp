/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "tabtools.h"
#include "tabtools.moc"
#include <qtooltip.h>
#include <qspinbox.h>
#include <qgroupbox.h>

#include "sccombobox.h"
#include "colorcombo.h"
#include "units.h"
#include "mspinbox.h"
#include "linecombo.h"
#include "fontcombo.h"
#include "polygonwidget.h"
#include "arrowchooser.h"
#include "linkbutton.h"
#include "scribusstructs.h"
#include "scribus.h"
#include "util.h"
#include "prefsmanager.h"
#include "scfonts.h"
#include "sampleitem.h"
#include "commonstrings.h"
#include "colorm.h"


TabTools::TabTools( QWidget* parent, struct toolPrefs *prefsData, int unitIndex, ScribusDoc* doc) : QWidget( parent, "tabtools", 0 )
{
	docu = doc;
	fontPreview = false;

	tabToolsLayout = new QHBoxLayout( this, 0, 5, "tabToolsLayout");
	buttonGroupTools = new QButtonGroup( this, "buttonGroupTools" );
	buttonGroupTools->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, buttonGroupTools->sizePolicy().hasHeightForWidth() ) );
	buttonGroupTools->setExclusive( true );
	buttonGroupTools->setRadioButtonExclusive( true );
	buttonGroupTools->setColumnLayout(0, Qt::Vertical );
	buttonGroupTools->layout()->setSpacing( 5 );
	buttonGroupTools->layout()->setMargin( 5 );
	buttonGroupTools->setTitle( QString::null );
	buttonGroupToolsLayout = new QVBoxLayout( buttonGroupTools->layout() );
	buttonGroupToolsLayout->setAlignment( Qt::AlignTop );
	toolText = new QToolButton( buttonGroupTools, "toolText" );
	toolText->setToggleButton( true );
	toolText->setText( QString::null );
	toolText->setIconSet( QIconSet( loadIcon("16/insert-text-frame.png") ) );
	buttonGroupToolsLayout->addWidget( toolText );
	toolImage = new QToolButton( buttonGroupTools, "toolImage" );
	toolImage->setToggleButton( true );
	toolImage->setText( QString::null );
	toolImage->setIconSet( QIconSet( loadIcon("16/insert-image.png") ) );
	buttonGroupToolsLayout->addWidget( toolImage );
	toolShape = new QToolButton( buttonGroupTools, "toolShape" );
	toolShape->setToggleButton( true );
	toolShape->setText( QString::null );
	toolShape->setIconSet( QIconSet( loadIcon("16/draw-rectangle.png") ) );
	buttonGroupToolsLayout->addWidget( toolShape);
	toolPoly = new QToolButton( buttonGroupTools, "toolPoly" );
	toolPoly->setToggleButton( true );
	toolPoly->setText( QString::null );
	toolPoly->setIconSet( QIconSet( loadIcon("16/draw-polygon.png") ) );
	buttonGroupToolsLayout->addWidget( toolPoly );
	toolLine = new QToolButton( buttonGroupTools, "toolLine" );
	toolLine->setToggleButton( true );
	toolLine->setText( QString::null );
	toolLine->setIconSet( QIconSet( loadIcon("Stift.xpm") ) );
	buttonGroupToolsLayout->addWidget( toolLine );
	toolZoom = new QToolButton( buttonGroupTools, "toolZoom" );
	toolZoom->setToggleButton( true );
	toolZoom->setText( QString::null );
	toolZoom->setIconSet( QIconSet( loadIcon("16/zoom.png") ) );
	buttonGroupToolsLayout->addWidget( toolZoom );
	toolMisc = new QToolButton( buttonGroupTools, "toolMisc" );
	toolMisc->setToggleButton( true );
	toolMisc->setText( QString::null );
	toolMisc->setIconSet( QIconSet( loadIcon("configure.png") ) );
	buttonGroupToolsLayout->addWidget( toolMisc );
	tabToolsLayout->addWidget( buttonGroupTools );
	subStackTools = new QWidgetStack( this, "subStackTools" );
	subStackTools->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, subStackTools->sizePolicy().hasHeightForWidth() ) );
	subStackTools->setFrameShape( QWidgetStack::GroupBoxPanel );
	subStackTools->setFrameShadow( QWidgetStack::Sunken );
	QFont f(this->font());
	f.setPointSize(f.pointSize()+3);
	f.setBold(true);

	subTabText = new QWidget( subStackTools, "subTabText" );
	subTabTextLayout = new QGridLayout( subTabText, 1, 1, 11, 6, "subTabTextLayout");
	subTabTextLayout->setAlignment( Qt::AlignTop );
	textHeadLine = new QLabel( tr( "Text" ), subTabText, "textHeadLine" );
	textHeadLine->setFont(f);
	subTabTextLayout->addMultiCellWidget( textHeadLine, 0, 0, 0, 3, Qt::AlignHCenter | Qt::AlignTop );
	fontComboText = new FontCombo(subTabText);
	subTabTextLayout->addMultiCellWidget( fontComboText, 1, 1, 1, 3, Qt::AlignLeft );
	textLabel1b = new QLabel( fontComboText, tr( "Font:" ), subTabText, "textLabel1b" );
	subTabTextLayout->addWidget( textLabel1b, 1, 0 );
	sizeComboText = new ScComboBox( false, subTabText, "SizeCombo" );

	subTabTextLayout->addMultiCellWidget( sizeComboText, 2, 2, 1, 3, Qt::AlignLeft );
	textLabel2b = new QLabel(sizeComboText, tr( "Size:" ), subTabText, "textLabel2b" );
	subTabTextLayout->addWidget( textLabel2b, 2, 0 );

	colorComboText = new ColorCombo( false, subTabText, "colorComboText" );

	subTabTextLayout->addWidget( colorComboText, 3, 1 );
	textLabel3b = new QLabel(colorComboText, tr( "Text Color:" ), subTabText, "textLabel3b" );
	subTabTextLayout->addWidget( textLabel3b, 3, 0 );
	shadingText = new QSpinBox( subTabText, "shadingText" );
	shadingText->setMaxValue( 100 );
	shadingText->setSuffix( tr( " %" ) );
	shadingText->setMinValue( 0 );
	subTabTextLayout->addWidget( shadingText, 3, 3, Qt::AlignLeft );
	textLabelTS = new QLabel( shadingText, tr( "Shading:" ), subTabText, "textLabelTS" );
	subTabTextLayout->addWidget( textLabelTS, 3, 2 );

	colorComboStrokeText = new ColorCombo( false, subTabText, "colorComboStrokeText" );

	subTabTextLayout->addWidget( colorComboStrokeText, 4, 1 );
	textLabel3b2 = new QLabel(colorComboStrokeText, tr( "Text Stroke:" ), subTabText, "textLabel3b2" );
	subTabTextLayout->addWidget( textLabel3b2, 4, 0 );
	shadingTextStroke = new QSpinBox( subTabText, "shadingTextStroke" );
	shadingTextStroke->setMaxValue( 100 );
	shadingTextStroke->setSuffix( tr( " %" ) );
	shadingTextStroke->setMinValue( 0 );

	subTabTextLayout->addWidget( shadingTextStroke, 4, 3, Qt::AlignLeft );
	textLabelTSS = new QLabel( shadingTextStroke, tr( "Shading:" ), subTabText, "textLabelTS" );
	subTabTextLayout->addWidget( textLabelTSS, 4, 2 );

	colorComboTextBackground = new ColorCombo( false, subTabText, "colorComboTextBackground" );

	subTabTextLayout->addWidget( colorComboTextBackground, 5, 1 );
	textLabel3bT = new QLabel(colorComboTextBackground, tr( "Fill Color:" ), subTabText, "textLabel3b" );
	subTabTextLayout->addWidget( textLabel3bT, 5, 0 );
	shadingTextBack = new QSpinBox( subTabText, "shadingTextBack" );
	shadingTextBack->setMaxValue( 100 );
	shadingTextBack->setSuffix( tr( " %" ) );
	shadingTextBack->setMinValue( 0 );

	subTabTextLayout->addWidget( shadingTextBack, 5, 3, Qt::AlignLeft );
	textLabelTSB = new QLabel( shadingTextBack, tr( "Shading:" ), subTabText, "textLabelTSS" );
	subTabTextLayout->addWidget( textLabelTSB, 5, 2 );

	colorComboTextLine = new ColorCombo( false, subTabText, "colorComboTextLine" );

	subTabTextLayout->addWidget( colorComboTextLine, 6, 1 );
	textLabel3bTL = new QLabel(colorComboTextLine, tr( "Stroke Color:" ), subTabText, "textLabel3b2" );
	subTabTextLayout->addWidget( textLabel3bTL, 6, 0 );
	shadingTextLine = new QSpinBox( subTabText, "shadingTextStroke" );
	shadingTextLine->setMaxValue( 100 );
	shadingTextLine->setSuffix( tr( " %" ) );
	shadingTextLine->setMinValue( 0 );

	subTabTextLayout->addWidget( shadingTextLine, 6, 3, Qt::AlignLeft );
	textLabelTSL = new QLabel( shadingTextLine, tr( "Shading:" ), subTabText, "textLabelTSL" );
	subTabTextLayout->addWidget( textLabelTSL, 6, 2 );

	tabFillCombo = new ScComboBox( false, subTabText, "tabFillCombo" );

	subTabTextLayout->addWidget( tabFillCombo, 7, 1, Qt::AlignLeft );
	textLabel3b2t = new QLabel(tabFillCombo, tr( "Tab Fill Character:" ), subTabText, "textLabel3b2t" );
	subTabTextLayout->addWidget( textLabel3b2t, 7, 0 );
	gapTab = new MSpinBox( 1, 200, subTabText, precision );

	subTabTextLayout->addWidget( gapTab, 7, 3, Qt::AlignLeft );
	textLabel3b2t2 = new QLabel(gapTab, tr( "Tab Width:" ), subTabText, "textLabel3b2t2" );
	subTabTextLayout->addWidget( textLabel3b2t2, 7, 2 );
	columnsText = new QSpinBox( subTabText, "columnsText" );
	columnsText->setMinValue( 1 );
	columnsText->setMaxValue(100);

	subTabTextLayout->addWidget( columnsText, 8, 1, Qt::AlignLeft );
	textLabel4b = new QLabel(columnsText, tr("Colu&mns:"), subTabText, "TextCol");
	subTabTextLayout->addWidget( textLabel4b, 8, 0 );
	gapText = new MSpinBox( 0, 200, subTabText, precision );

	subTabTextLayout->addWidget( gapText, 8, 3, Qt::AlignLeft );
	textLabel5b = new QLabel(gapText, tr("&Gap:"), subTabText, "TextCol");
	subTabTextLayout->addWidget( textLabel5b, 8, 2 );
	previewText = new QLabel( tr( "Woven silk pyjamas exchanged for blue quartz" ), subTabText, "previewText" );
	previewText->setMinimumSize(QSize(400, 170));
	previewText->setMaximumSize(QSize(400, 170));
	previewText->setFrameShape(QFrame::Box);
	previewText->setAlignment( static_cast<int>( QLabel::AlignTop | QLabel::AlignLeft ) );
	subTabTextLayout->addMultiCellWidget( previewText, 9, 9, 0, 3 );
	subStackTools->addWidget( subTabText, 0 );

	subTabShape = new QWidget( subStackTools, "subTabShape" );
	subTabShapeLayout = new QGridLayout( subTabShape, 1, 1, 11, 6, "subTabShapeLayout");
	subTabShapeLayout->setAlignment( Qt::AlignTop );
	shapeHeadLine = new QLabel( tr( "Shapes" ), subTabShape, "shapeHeadLine" );
	shapeHeadLine->setFont(f);
	subTabShapeLayout->addMultiCellWidget( shapeHeadLine, 0, 0, 0, 1, Qt::AlignHCenter | Qt::AlignTop );
	colorComboLineShape = new ColorCombo( false, subTabShape, "colorComboLineShape" );

	subTabShapeLayout->addWidget( colorComboLineShape, 1, 1, Qt::AlignLeft );
	textLabel7b = new QLabel( colorComboLineShape, tr( "&Line Color:" ), subTabShape, "textLabel7b" );
	subTabShapeLayout->addWidget( textLabel7b, 1, 0 );
	shadingLineShape = new QSpinBox( subTabShape, "shadingLineShape" );
	shadingLineShape->setMaxValue( 100 );
	shadingLineShape->setSuffix( tr( " %" ) );
	shadingLineShape->setMinValue( 0 );

	subTabShapeLayout->addWidget( shadingLineShape, 2, 1, Qt::AlignLeft );
	textLabel8b = new QLabel( shadingLineShape, tr( "&Shading:" ), subTabShape, "textLabel8b" );
	subTabShapeLayout->addWidget( textLabel8b, 2, 0 );
	comboFillShape = new ColorCombo( false, subTabShape, "comboFillShape" );

	subTabShapeLayout->addWidget( comboFillShape, 3, 1, Qt::AlignLeft );
	textLabel9b = new QLabel( comboFillShape, tr( "&Fill Color:" ), subTabShape, "textLabel9b" );
	subTabShapeLayout->addWidget( textLabel9b, 3, 0 );
	shadingFillShape = new QSpinBox( subTabShape, "shadingFillShape" );
	shadingFillShape->setMaxValue( 100 );
	shadingFillShape->setSuffix( tr( " %" ) );
	shadingFillShape->setMinValue( 0 );

	subTabShapeLayout->addWidget( shadingFillShape, 4, 1, Qt::AlignLeft );
	textLabel10b = new QLabel( shadingFillShape, tr( "S&hading:" ), subTabShape, "textLabel10b" );
	subTabShapeLayout->addWidget( textLabel10b, 4, 0 );
	comboStyleShape = new LineCombo(subTabShape);
	comboStyleShape->setEditable(false);

	subTabShapeLayout->addWidget( comboStyleShape, 5, 1, Qt::AlignLeft );
	textLabel11b = new QLabel( comboStyleShape, tr( "Line Style:" ), subTabShape, "textLabel11b" );
	subTabShapeLayout->addWidget( textLabel11b, 5, 0 );
	lineWidthShape = new MSpinBox( 0, 36, subTabShape, 1 );
	lineWidthShape->setSuffix( tr( " pt" ) );

	subTabShapeLayout->addWidget( lineWidthShape, 6, 1, Qt::AlignLeft );
	textLabel12b = new QLabel( lineWidthShape, tr( "Line &Width:" ), subTabShape, "TextLabel2_3_4" );
	subTabShapeLayout->addWidget( textLabel12b, 6, 0 );
	subStackTools->addWidget( subTabShape, 1 );

	subTabLine = new QWidget( subStackTools, "subTabLine" );
	subTabLineLayout = new QGridLayout( subTabLine, 1, 1, 11, 6, "subTabLineLayout");
	subTabLineLayout->setAlignment( Qt::AlignTop );
	lineHeadLine = new QLabel( tr( "Lines" ), subTabLine, "lineHeadLine" );
	lineHeadLine->setFont(f);
	subTabLineLayout->addMultiCellWidget( lineHeadLine, 0, 0, 0, 2, Qt::AlignHCenter | Qt::AlignTop );
	colorComboLine = new ColorCombo( false, subTabLine, "colorComboLine" );

	subTabLineLayout->addMultiCellWidget( colorComboLine, 1, 1, 1, 2, Qt::AlignLeft );
	textLabel13b = new QLabel(colorComboLine, tr("&Line Color:"), subTabLine, "textLabel13b" );
	subTabLineLayout->addWidget( textLabel13b, 1, 0 );
	shadingLine = new QSpinBox( subTabLine, "shadingLine" );
	shadingLine->setMaxValue( 100 );

	shadingLine->setSuffix( tr( " %" ) );
	subTabLineLayout->addMultiCellWidget( shadingLine, 2, 2, 1, 2, Qt::AlignLeft );
	textLabel14b = new QLabel(shadingLine, tr("&Shading:"), subTabLine, "textLabel14b" );
	subTabLineLayout->addWidget( textLabel14b, 2, 0 );
	comboStyleLine = new LineCombo(subTabLine);
	comboStyleLine->setEditable(false);

	subTabLineLayout->addMultiCellWidget( comboStyleLine, 3, 3, 1, 2, Qt::AlignLeft );
	textLabel15b = new QLabel(subTabLine, tr("Line S&tyle:"), subTabLine, "textLabel15b" );
	subTabLineLayout->addWidget( textLabel15b, 3, 0 );
	startArrow = new ArrowChooser(subTabLine, true);
	subTabLineLayout->addWidget( startArrow, 5, 1 );
	endArrow = new ArrowChooser(subTabLine, false);
	subTabLineLayout->addWidget( endArrow, 5, 2 );

	arrowText = new QLabel( tr( "Arrows:" ), subTabLine, "arrowText" );
	subTabLineLayout->addMultiCellWidget( arrowText, 4, 5, 0, 0 );
	startArrowText = new QLabel( startArrow, tr( "Start:" ), subTabLine, "startArrowText" );
	subTabLineLayout->addWidget( startArrowText, 4, 1 );
	endArrowText = new QLabel( endArrow, tr( "End:" ), subTabLine, "endArrowText" );
	subTabLineLayout->addWidget( endArrowText, 4, 2 );
	lineWidthLine = new MSpinBox( 1, 36, subTabLine, 1 );
	lineWidthLine->setSuffix( tr( " pt" ) );

	subTabLineLayout->addMultiCellWidget( lineWidthLine, 6, 6, 1, 2, Qt::AlignLeft );
	textLabel16b = new QLabel(lineWidthLine, tr("Line &Width:"), subTabLine, "textLabel16b" );
	subTabLineLayout->addWidget( textLabel16b, 6, 0 );
	subStackTools->addWidget( subTabLine, 2 );

	subTabImage = new QWidget( subStackTools, "subTabImage" );
	subTabImageLayout = new QGridLayout( subTabImage, 1, 1, 11, 6, "subTabImageLayout");
	subTabImageLayout->setAlignment( Qt::AlignTop );
	imageHeadLine = new QLabel( tr( "Images" ), subTabImage, "imageHeadLine" );
	imageHeadLine->setFont(f);
	subTabImageLayout->addMultiCellWidget( imageHeadLine, 0, 0, 0, 1, Qt::AlignHCenter | Qt::AlignTop );
	buttonGroup3 = new QButtonGroup( subTabImage, "buttonGroup3" );
	buttonGroup3->setCheckable( true );

	buttonGroup3->setColumnLayout(0, Qt::Vertical );
	buttonGroup3->layout()->setSpacing( 6 );
	buttonGroup3->layout()->setMargin( 11 );
	buttonGroup3->setTitle( tr( "&Free Scaling" ) );
	buttonGroup3Layout = new QGridLayout( buttonGroup3->layout() );
	buttonGroup3Layout->setAlignment( Qt::AlignTop );
	scalingHorizontal = new QSpinBox( buttonGroup3, "scalingHorizontal" );
	scalingHorizontal->setMaxValue( 1000 );
	scalingHorizontal->setMinValue( 1 );

	scalingHorizontal->setSuffix( tr( " %" ) );
	buttonGroup3Layout->addWidget( scalingHorizontal, 0, 1, Qt::AlignRight );
	textLabel17b = new QLabel(scalingHorizontal, tr("&Horizontal Scaling:"), buttonGroup3, "textLabel17b" );
	buttonGroup3Layout->addWidget( textLabel17b, 0, 0 );
	scalingVertical = new QSpinBox( buttonGroup3, "scalingVertical" );
	scalingVertical->setMaxValue( 1000 );
	scalingVertical->setMinValue( 1 );
	scalingVertical->setSuffix( tr( " %" ) );

	buttonGroup3Layout->addWidget( scalingVertical, 1, 1, Qt::AlignRight );
	textLabel18b = new QLabel(scalingVertical, tr( "&Vertical Scaling:" ), buttonGroup3, "textLabel18b" );
	buttonGroup3Layout->addWidget( textLabel18b, 1, 0 );
	chainButton = new LinkButton( buttonGroup3 );
	chainButton->setToggleButton( true );
	chainButton->setAutoRaise(true);
	buttonGroup3Layout->addMultiCellWidget( chainButton, 0, 1, 2, 2, Qt::AlignLeft );
	subTabImageLayout->addMultiCellWidget( buttonGroup3, 1, 1, 0, 1 );
	buttonGroup5 = new QButtonGroup( subTabImage, "buttonGroup5" );
	buttonGroup5->setCheckable( true );

	buttonGroup5->setColumnLayout(0, Qt::Vertical );
	buttonGroup5->layout()->setSpacing( 6 );
	buttonGroup5->layout()->setMargin( 11 );
	buttonGroup5->setTitle( tr( "&Scale Picture to Frame Size" ) );
	buttonGroup5Layout = new QHBoxLayout( buttonGroup5->layout() );
	buttonGroup5Layout->setAlignment( Qt::AlignTop );
	checkRatioImage = new QCheckBox( buttonGroup5, "checkRatioImage" );
	checkRatioImage->setText( tr( "Keep Aspect &Ratio" ) );

	buttonGroup5Layout->addWidget( checkRatioImage );
	subTabImageLayout->addMultiCellWidget( buttonGroup5, 2, 2, 0, 1 );
	comboFillImage = new ColorCombo( false, subTabImage, "comboFillImage" );

	subTabImageLayout->addWidget( comboFillImage, 3, 1, Qt::AlignLeft );
	textLabel19b = new QLabel(comboFillImage, tr( "F&ill Color:" ), subTabImage, "textLabel19b" );
	subTabImageLayout->addWidget( textLabel19b, 3, 0 );
	shadingFillImage = new QSpinBox( subTabImage, "shadingFillImage" );
	shadingFillImage->setMaxValue( 100 );

	shadingFillImage->setSuffix( tr( " %" ) );
	subTabImageLayout->addWidget( shadingFillImage, 4, 1, Qt::AlignLeft );
	textLabel20b = new QLabel(shadingFillImage, tr( "S&hading:" ), subTabImage, "textLabel20b" );
	subTabImageLayout->addWidget( textLabel20b, 4, 0 );
	embeddedPath = new QCheckBox( subTabImage, "embeddedPath" );
	embeddedPath->setText( tr( "Use embedded Clipping Path" ) );

	subTabImageLayout->addMultiCellWidget( embeddedPath, 5, 5, 0, 1 );
	buttonGroupRes = new QButtonGroup( subTabImage, "buttonGroup3" );
	buttonGroupRes->setColumnLayout(0, Qt::Vertical );
	buttonGroupRes->layout()->setSpacing( 6 );
	buttonGroupRes->layout()->setMargin( 11 );
	buttonGroupRes->setExclusive( true );
	buttonGroupRes->setTitle( tr( "On Screen Preview" ) );
	buttonGroupResLayout = new QVBoxLayout( buttonGroupRes->layout() );
	buttonGroupResLayout->setAlignment( Qt::AlignTop );
	checkFullRes = new QRadioButton( buttonGroupRes, "checkFullRes" );
	checkFullRes->setText( tr( "Full Resolution Preview" ) );
	buttonGroupResLayout->addWidget( checkFullRes );
	checkNormalRes = new QRadioButton( buttonGroupRes, "checkNormalRes" );
	checkNormalRes->setText( tr( "Normal Resolution Preview" ) );
	buttonGroupResLayout->addWidget( checkNormalRes );
	checkHalfRes = new QRadioButton( buttonGroupRes, "checkHalfRes" );
	checkHalfRes->setText( tr( "Low Resolution Preview" ) );
	buttonGroupResLayout->addWidget( checkHalfRes );

	subTabImageLayout->addMultiCellWidget( buttonGroupRes, 6, 6, 0, 1 );
	subStackTools->addWidget( subTabImage, 3 );

	subTabPolygon = new QWidget( subStackTools, "subTabPolygon" );
	subTabPolygonLayout = new QGridLayout( subTabPolygon, 1, 1, 11, 6, "subTabZoomLayout");
	subTabPolygonLayout->setAlignment( Qt::AlignTop );
	polygonHeadLine = new QLabel( tr( "Regular Polygons" ), subTabPolygon, "imageHeadLine" );
	polygonHeadLine->setFont(f);
	subTabPolygonLayout->addMultiCellWidget( polygonHeadLine, 0, 0, 0, 0, Qt::AlignHCenter | Qt::AlignTop );
	polyWidget = new PolygonWidget(subTabPolygon, prefsData->polyC, prefsData->polyFd, prefsData->polyF, prefsData->polyS, prefsData->polyR);
	subTabPolygonLayout->addWidget( polyWidget, 1, 0 );
	subStackTools->addWidget( subTabPolygon, 4 );

	subTabZoom = new QWidget( subStackTools, "subTabZoom" );
	subTabZoomLayout = new QGridLayout( subTabZoom, 1, 1, 11, 6, "subTabZoomLayout");
	subTabZoomLayout->setAlignment( Qt::AlignTop );
	zoomHeadLine = new QLabel( tr( "Zoom" ), subTabZoom, "zoomHeadLine" );
	zoomHeadLine->setFont(f);
	subTabZoomLayout->addMultiCellWidget( zoomHeadLine, 0, 0, 0, 1, Qt::AlignHCenter | Qt::AlignTop );
	minimumZoom = new QSpinBox( subTabZoom, "minimumZoom" );
	minimumZoom->setMaxValue( 3200 );
	minimumZoom->setMinValue( 10 );
	minimumZoom->setSuffix( tr( " %" ) );
	subTabZoomLayout->addWidget( minimumZoom, 1, 1, Qt::AlignLeft );
	textLabel21b = new QLabel( minimumZoom, tr( "Mi&nimum:" ), subTabZoom, "textLabel21b" );
	subTabZoomLayout->addWidget( textLabel21b, 1, 0);

	maximumZoom = new QSpinBox( subTabZoom, "maximumZoom" );
	maximumZoom->setMaxValue( 3200 );
	maximumZoom->setMinValue( 10 );
	maximumZoom->setSuffix( tr( " %" ) );
	subTabZoomLayout->addWidget( maximumZoom, 2, 1, Qt::AlignLeft );
	textLabel22b = new QLabel( maximumZoom, tr( "Ma&ximum:" ), subTabZoom, "textLabel22b" );
	subTabZoomLayout->addWidget( textLabel22b, 2, 0 );
	
	zoomStep = new QSpinBox( 101, 500, 1, subTabZoom, "zoomStep" );
	zoomStep->setSuffix( tr( " %" ) );
	subTabZoomLayout->addWidget( zoomStep, 3, 1, Qt::AlignLeft );
	textLabel23b = new QLabel( zoomStep, tr( "&Stepping:" ), subTabZoom, "textLabel23b" );
	subTabZoomLayout->addWidget( textLabel23b, 3, 0 );
	subStackTools->addWidget( subTabZoom, 5 );

	subTabGeneral = new QWidget( subStackTools, "subTabGeneral" );
	subTabGeneralLayout = new QGridLayout( subTabGeneral, 1, 1, 11, 6, "subTabGeneralLayout");
	subTabGeneralLayout->setAlignment( Qt::AlignTop );
	generalHeadLine = new QLabel( tr( "Misc. Settings" ), subTabGeneral, "generalHeadLine" );
	generalHeadLine->setFont(f);
	subTabGeneralLayout->addMultiCellWidget( generalHeadLine, 0, 0, 0, 1, Qt::AlignHCenter | Qt::AlignTop );

	genDispBox = new QGroupBox( subTabGeneral, "genDispBox" );
	genDispBox->setTitle( tr( "Object Duplicate" ) );
	genDispBox->setColumnLayout(0, Qt::Vertical );
	genDispBox->layout()->setSpacing( 5 );
	genDispBox->layout()->setMargin( 10 );
	subTabGeneralLayout2 = new QGridLayout( genDispBox->layout() );

	genDispX = new MSpinBox( -1000, 1000, genDispBox, 1 );
	genDispX->setSuffix( tr( " pt" ) );
	subTabGeneralLayout2->addWidget( genDispX, 0, 1, Qt::AlignLeft );
	genText1 = new QLabel( genDispX, tr( "X-Displacement" ), genDispBox, "genText1" );
	subTabGeneralLayout2->addWidget( genText1, 0, 0);

	genDispY = new MSpinBox( -1000, 1000, genDispBox, 1 );
	genDispY->setSuffix( tr( " pt" ) );
	subTabGeneralLayout2->addWidget( genDispY, 1, 1, Qt::AlignLeft );
	genText2 = new QLabel( genDispY, tr( "Y-Displacement" ), genDispBox, "genText2" );
	subTabGeneralLayout2->addWidget( genText2, 1, 0);
	subTabGeneralLayout->addMultiCellWidget( genDispBox, 1, 1, 0, 1, Qt::AlignHCenter | Qt::AlignTop );
	subStackTools->addWidget( subTabGeneral, 6 );

	tabToolsLayout->addWidget( subStackTools );
	toolText->setOn(true);

	// Neccessary for document prefs
	//restoreDefaults(prefsData, unitIndex);

	QToolTip::add( toolText, tr( "Text Frame Properties" ) );
	QToolTip::add( toolImage, tr( "Picture Frame Properties" ) );
	QToolTip::add( toolShape, tr( "Shape Drawing Properties" ) );
	QToolTip::add( toolZoom, tr( "Magnification Level Defaults" ) );
	QToolTip::add( toolLine, tr( "Line Drawing Properties" ) );
	QToolTip::add( toolPoly, tr( "Polygon Drawing Properties" ) );
	QToolTip::add( toolMisc, tr( "Other Properties" ) );
	QToolTip::add( fontComboText, tr( "Font for new text frames" ) );
	QToolTip::add( sizeComboText, tr( "Size of font for new text frames" ) );
	QToolTip::add( colorComboText, tr( "Color of font" ) );
	QToolTip::add( columnsText, tr( "Number of columns in a text frame" ) );
	QToolTip::add( gapText, tr( "Gap between text frame columns" ) );
	QToolTip::add( previewText, tr( "Sample of your font" ) );
	QToolTip::add( buttonGroup3, tr( "Picture frames allow pictures to scale to any size" ) );
	QToolTip::add( scalingHorizontal, tr( "Horizontal scaling of images" ) );
	QToolTip::add( scalingVertical, tr( "Vertical scaling of images" ) );
	QToolTip::add( chainButton, tr( "Keep horizontal and vertical scaling the same" ) );
	QToolTip::add( buttonGroup5, tr( "Pictures in picture frames are scaled to the size of the frame" ) );
	QToolTip::add( checkRatioImage, tr( "Automatically scaled pictures keep their original proportions" ) );
	QToolTip::add( comboFillImage, tr( "Fill color of picture frames" ) );
	QToolTip::add( shadingFillImage, tr( "Saturation of color of fill" ) );
	QToolTip::add( colorComboLineShape, tr( "Line color of shapes" ) );
	QToolTip::add( shadingLineShape, tr( "Saturation of color of lines" ) );
	QToolTip::add( comboFillShape, tr( "Fill color of shapes" ) );
	QToolTip::add( shadingFillShape, tr( "Saturation of color of fill" ) );
	QToolTip::add( comboStyleShape, tr( "Line style of shapes" ) );
	QToolTip::add( lineWidthShape, tr( "Line width of shapes" ) );
	QToolTip::add( minimumZoom, tr( "Minimum magnification allowed" ) );
	QToolTip::add( maximumZoom, tr( "Maximum magnification allowed" ) );
	QToolTip::add( zoomStep, tr( "Change in magnification for each zoom operation" ) );
	QToolTip::add( colorComboLine, tr( "Color of lines" ) );
	QToolTip::add( shadingLine, tr( "Saturation of color" ) );
	QToolTip::add( comboStyleLine, tr( "Style of lines" ) );
	QToolTip::add( lineWidthLine, tr( "Width of lines" ) );
	QToolTip::add( genDispX, tr( "Horizontal displacement of objects") );
	QToolTip::add( genDispY, tr( "Vertical displacement of objects" ) );
	//enableSignals(true);
}

void TabTools::enableSignals(bool on)
{
	if (on)
	{
		connect(toolShape, SIGNAL(clicked()), this, SLOT(setTool()));
		connect(toolPoly, SIGNAL(clicked()), this, SLOT(setTool()));
		connect(toolImage, SIGNAL(clicked()), this, SLOT(setTool()));
		connect(toolText, SIGNAL(clicked()), this, SLOT(setTool()));
		connect(toolLine, SIGNAL(clicked()), this, SLOT(setTool()));
		connect(toolZoom, SIGNAL(clicked()), this, SLOT(setTool()));
		connect(toolMisc, SIGNAL(clicked()), this, SLOT(setTool()));
		connect(fontComboText, SIGNAL(activated(int)), this, SLOT(setSample()));
		connect(sizeComboText, SIGNAL(activated(int)), this, SLOT(setSample()));
		connect(colorComboText, SIGNAL(activated(int)), this, SLOT(setSample()));
		connect(colorComboTextBackground, SIGNAL(activated(int)), this, SLOT(setSample()));
		connect(shadingTextBack, SIGNAL(valueChanged(int)), this, SLOT(setSample()));
		connect(shadingText, SIGNAL(valueChanged(int)), this, SLOT(setSample()));
		connect(buttonGroup3, SIGNAL(clicked(int)), this, SLOT(changeImageScalingFree(int)));
		connect(buttonGroup5, SIGNAL(clicked(int)), this, SLOT(changeImageScalingRatio(int)));
		connect(chainButton, SIGNAL(clicked()), this, SLOT(toggleChain()));
		connect(scalingHorizontal, SIGNAL(valueChanged(int)), this, SLOT(hChange()));
		connect(scalingVertical, SIGNAL(valueChanged(int)), this, SLOT(vChange()));
		connect(tabFillCombo, SIGNAL(activated(int)), this, SLOT(setFillChar(int)));
	}
	else
	{
		disconnect(toolShape, SIGNAL(clicked()), this, SLOT(setTool()));
		disconnect(toolPoly, SIGNAL(clicked()), this, SLOT(setTool()));
		disconnect(toolImage, SIGNAL(clicked()), this, SLOT(setTool()));
		disconnect(toolText, SIGNAL(clicked()), this, SLOT(setTool()));
		disconnect(toolLine, SIGNAL(clicked()), this, SLOT(setTool()));
		disconnect(toolZoom, SIGNAL(clicked()), this, SLOT(setTool()));
		disconnect(toolMisc, SIGNAL(clicked()), this, SLOT(setTool()));
		disconnect(fontComboText, SIGNAL(activated(int)), this, SLOT(setSample()));
		disconnect(sizeComboText, SIGNAL(activated(int)), this, SLOT(setSample()));
		disconnect(colorComboText, SIGNAL(activated(int)), this, SLOT(setSample()));
		disconnect(colorComboTextBackground, SIGNAL(activated(int)), this, SLOT(setSample()));
		disconnect(shadingTextBack, SIGNAL(valueChanged(int)), this, SLOT(setSample()));
		disconnect(shadingText, SIGNAL(valueChanged(int)), this, SLOT(setSample()));
		disconnect(buttonGroup3, SIGNAL(clicked(int)), this, SLOT(changeImageScalingFree(int)));
		disconnect(buttonGroup5, SIGNAL(clicked(int)), this, SLOT(changeImageScalingRatio(int)));
		disconnect(chainButton, SIGNAL(clicked()), this, SLOT(toggleChain()));
		disconnect(scalingHorizontal, SIGNAL(valueChanged(int)), this, SLOT(hChange()));
		disconnect(scalingVertical, SIGNAL(valueChanged(int)), this, SLOT(vChange()));
		disconnect(tabFillCombo, SIGNAL(activated(int)), this, SLOT(setFillChar(int)));
	}
}

void TabTools::restoreDefaults(struct toolPrefs *prefsData, int unitIndex)
{
	enableSignals(false);

	PrefsManager* prefsManager=PrefsManager::instance();
	unit = unitGetSuffixFromIndex(unitIndex);
	precision = unitGetPrecisionFromIndex(unitIndex);
	unitRatio = unitGetRatioFromIndex(unitIndex);

	for (int fc=0; fc<fontComboText->count(); ++fc)
	{
		if (fontComboText->text(fc) == prefsData->defFont)
		{
			fontComboText->setCurrentItem(fc);
			break;
		}
	}
	QString ar_sizes[] = {" 7", " 9", "10", "11", "12", "14", "18", "24", "36", "48", "60", "72"};
	size_t f_size = sizeof(ar_sizes) / sizeof(*ar_sizes);
	sizeComboText->clear();
	for (uint s = 0; s < f_size; ++s)
		sizeComboText->insertItem(ar_sizes[s] + tr(" pt"));
	for (int a = 0; a < sizeComboText->count(); ++a)
	{
		if (sizeComboText->text(a).left(2).toInt() == prefsData->defSize / 10)
		{
			sizeComboText->setCurrentItem(a);
			break;
		}
	}

	ColorList::Iterator itc;
	colorComboText->clear();
	colorComboText->insertItem(CommonStrings::NoneColor);
	if (prefsData->dPenText == CommonStrings::None)
		colorComboText->setCurrentItem(colorComboText->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			colorComboText->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dPenText)
				colorComboText->setCurrentItem(colorComboText->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			colorComboText->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dPenText)
				colorComboText->setCurrentItem(colorComboText->count()-1);
		}
	}

	shadingText->setValue(prefsData->dTextPenShade);

	colorComboStrokeText->clear();
	colorComboStrokeText->insertItem(CommonStrings::NoneColor);
	if (prefsData->dStrokeText == CommonStrings::None)
		colorComboStrokeText->setCurrentItem(colorComboStrokeText->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			colorComboStrokeText->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dStrokeText)
				colorComboStrokeText->setCurrentItem(colorComboStrokeText->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			colorComboStrokeText->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dStrokeText)
				colorComboStrokeText->setCurrentItem(colorComboStrokeText->count()-1);
		}
	}
	shadingTextStroke->setValue(prefsData->dTextStrokeShade);

	colorComboTextBackground->clear();
	colorComboTextBackground->insertItem(CommonStrings::NoneColor);
	if (prefsData->dTextBackGround == CommonStrings::None)
		colorComboTextBackground->setCurrentItem(colorComboTextBackground->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			colorComboTextBackground->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dTextBackGround)
				colorComboTextBackground->setCurrentItem(colorComboTextBackground->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			colorComboTextBackground->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dTextBackGround)
				colorComboTextBackground->setCurrentItem(colorComboTextBackground->count()-1);
		}
	}
	shadingTextBack->setValue(prefsData->dTextBackGroundShade);

	colorComboTextLine->clear();
	colorComboTextLine->insertItem(CommonStrings::NoneColor);
	if (prefsData->dTextLineColor == CommonStrings::None)
		colorComboTextLine->setCurrentItem(colorComboTextLine->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			colorComboTextLine->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dTextLineColor)
				colorComboTextLine->setCurrentItem(colorComboTextLine->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			colorComboTextLine->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dTextLineColor)
				colorComboTextLine->setCurrentItem(colorComboTextLine->count()-1);
		}
	}
	shadingTextLine->setValue(prefsData->dTextLineShade);

	tabFillCombo->clear();
	tabFillCombo->insertItem( tr("None", "tab fill" ));
	tabFillCombo->insertItem( tr("Dot"));
	tabFillCombo->insertItem( tr("Hyphen"));
	tabFillCombo->insertItem( tr("Underscore"));
	tabFillCombo->insertItem( tr("Custom"));
	if (prefsData->tabFillChar.isEmpty())
	{
		tabFillCombo->setCurrentItem(0);
	}
	else if (prefsData->tabFillChar == ".")
	{
		tabFillCombo->setCurrentItem(1);
	}
	else if (prefsData->tabFillChar == "-")
	{
		tabFillCombo->setCurrentItem(2);
	}
	else if (prefsData->tabFillChar == "_")
	{
		tabFillCombo->setCurrentItem(3);
	}
	else
	{
		tabFillCombo->setCurrentItem(4);
		tabFillCombo->setEditable(true);
		tabFillCombo->setEditText( tr("Custom: "+prefsData->tabFillChar));
	}
	gapTab->setSuffix( unit );
	gapTab->setValue(prefsData->dTabWidth * unitRatio);
	columnsText->setValue(prefsData->dCols);
	gapText->setSuffix( unit );
	gapText->setValue(prefsData->dGap * unitRatio);

	colorComboLineShape->clear();
	colorComboLineShape->insertItem(CommonStrings::NoneColor);
	if (prefsData->dPen == CommonStrings::None)
		colorComboLineShape->setCurrentItem(colorComboLineShape->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			colorComboLineShape->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dPen)
				colorComboLineShape->setCurrentItem(colorComboLineShape->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			colorComboLineShape->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dPen)
				colorComboLineShape->setCurrentItem(colorComboLineShape->count()-1);
		}
	}
	shadingLineShape->setValue(prefsData->dShade2);

	comboFillShape->clear();
	comboFillShape->insertItem( tr("None"), "fill shape");
	if (prefsData->dBrush == CommonStrings::None)
		comboFillShape->setCurrentItem(comboFillShape->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			comboFillShape->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dBrush)
				comboFillShape->setCurrentItem(comboFillShape->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			comboFillShape->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dBrush)
				comboFillShape->setCurrentItem(comboFillShape->count()-1);
		}
	}

	shadingFillShape->setValue(prefsData->dShade);
	switch (prefsData->dLineArt)
	{
		case SolidLine:
			comboStyleShape->setCurrentItem(0);
			break;
		case DashLine:
			comboStyleShape->setCurrentItem(1);
			break;
		case DotLine:
			comboStyleShape->setCurrentItem(2);
			break;
		case DashDotLine:
			comboStyleShape->setCurrentItem(3);
			break;
		case DashDotDotLine:
			comboStyleShape->setCurrentItem(4);
			break;
		default:
			comboStyleShape->setCurrentItem(0);
			break;
	}

	lineWidthShape->setValue(prefsData->dWidth);

	colorComboLine->clear();
	colorComboLine->insertItem(CommonStrings::NoneColor);
	if (prefsData->dPenLine == CommonStrings::None)
		colorComboLine->setCurrentItem(colorComboLine->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			colorComboLine->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dPenLine)
				colorComboLine->setCurrentItem(colorComboLine->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			colorComboLine->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dPenLine)
				colorComboLine->setCurrentItem(colorComboLine->count()-1);
		}
	}

	shadingLine->setValue(prefsData->dShadeLine);

	switch (prefsData->dLstyleLine)
	{
		case SolidLine:
			comboStyleLine->setCurrentItem(0);
			break;
		case DashLine:
			comboStyleLine->setCurrentItem(1);
			break;
		case DotLine:
			comboStyleLine->setCurrentItem(2);
			break;
		case DashDotLine:
			comboStyleLine->setCurrentItem(3);
			break;
		case DashDotDotLine:
			comboStyleLine->setCurrentItem(4);
			break;
		default:
			comboStyleLine->setCurrentItem(0);
			break;
	}

	if (docu != 0)
	{
		startArrow->rebuildList(&docu->arrowStyles);
		endArrow->rebuildList(&docu->arrowStyles);
	}
	else
	{
		startArrow->rebuildList(&prefsManager->appPrefs.arrowStyles);
		endArrow->rebuildList(&prefsManager->appPrefs.arrowStyles);
	}
	startArrow->setCurrentItem(prefsData->dStartArrow);
	endArrow->setCurrentItem(prefsData->dEndArrow);
	lineWidthLine->setValue(prefsData->dWidthLine);

	buttonGroup3->setChecked( prefsData->scaleType );
	scalingHorizontal->setValue(qRound(prefsData->scaleX * 100));
	scalingVertical->setValue(qRound(prefsData->scaleY * 100));
	buttonGroup5->setChecked( !prefsData->scaleType );
	checkRatioImage->setChecked(prefsData->aspectRatio);

	comboFillImage->clear();
	comboFillImage->insertItem(CommonStrings::NoneColor);
	if (prefsData->dBrushPict == CommonStrings::None)
		comboFillImage->setCurrentItem(comboFillImage->count()-1);
	if (docu != 0)
	{
		for (itc = docu->PageColors.begin(); itc != docu->PageColors.end(); ++itc)
		{
			comboFillImage->insertSmallItem( docu->PageColors[itc.key()], itc.key() );
			if (itc.key() == prefsData->dBrushPict)
				comboFillImage->setCurrentItem(comboFillImage->count()-1);
		}
	}
	else
	{
		ColorList* colorList=prefsManager->colorSetPtr();
		ColorList::Iterator endOfColorList=colorList->end();
		for (itc = colorList->begin(); itc != endOfColorList; ++itc)
		{
			comboFillImage->insertSmallItem( (*colorList)[itc.key()], itc.key() );
			if (itc.key() == prefsData->dBrushPict)
				comboFillImage->setCurrentItem(comboFillImage->count()-1);
		}
	}

	shadingFillImage->setValue( prefsData->shadePict );
	embeddedPath->setChecked(prefsData->useEmbeddedPath);
	switch (prefsData->lowResType)
	{
		case 0:
			checkFullRes->setChecked(true);
			break;
		case 1:
			checkNormalRes->setChecked(true);
			break;
		case 2:
			checkHalfRes->setChecked(true);
			break;
	}

	minimumZoom->setValue(prefsData->magMin);
	maximumZoom->setValue(prefsData->magMax);
	zoomStep->setValue( prefsData->magStep );

	genDispX->setValue(prefsData->dispX);
	genDispY->setValue(prefsData->dispY);

	setSample();

	enableSignals(true);
}

void TabTools::setCustomFillChar(const QString &txt)
{
	if (txt == tr("Custom:"))
		return;
	disconnect(tabFillCombo, SIGNAL(textChanged(const QString &)), this, SLOT(setCustomFillChar(const QString &)));
	disconnect(tabFillCombo, SIGNAL(activated(int)), this, SLOT(setFillChar(int)));
	QString ret = txt.right(1);
	if (tabFillCombo->editable())
	{
		tabFillCombo->setCurrentItem(4);
		tabFillCombo->setEditText( tr("Custom: ")+ret);
		tabFillCombo->changeItem( tr("Custom: ")+ret, 4);
	}
	connect(tabFillCombo, SIGNAL(textChanged(const QString &)), this, SLOT(setCustomFillChar(const QString &)));
	connect(tabFillCombo, SIGNAL(activated(int)), this, SLOT(setFillChar(int)));
}

void TabTools::setFillChar(int act)
{
	disconnect(tabFillCombo, SIGNAL(textChanged(const QString &)), this, SLOT(setCustomFillChar(const QString &)));
	disconnect(tabFillCombo, SIGNAL(activated(int)), this, SLOT(setFillChar(int)));
	switch (act)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			tabFillCombo->setCurrentItem(act);
			tabFillCombo->setEditable(false);
			break;
		case 4:
			tabFillCombo->setEditable(true);
			tabFillCombo->setEditText( tr("Custom: "));
			tabFillCombo->changeItem( tr("Custom: "), 4);
			tabFillCombo->lineEdit()->setFocus();
			tabFillCombo->lineEdit()->setCursorPosition( tr("Custom: ").length());
			connect(tabFillCombo, SIGNAL(textChanged(const QString &)), this, SLOT(setCustomFillChar(const QString &)));
			break;
	}
	connect(tabFillCombo, SIGNAL(activated(int)), this, SLOT(setFillChar(int)));
}

void TabTools::toggleChain()
{
	if (chainButton->isOn())
		scalingVertical->setValue(scalingHorizontal->value());
}

void TabTools::hChange()
{
	if (chainButton->isOn())
		scalingVertical->setValue(scalingHorizontal->value());
}

void TabTools::vChange()
{
	if (chainButton->isOn())
		scalingHorizontal->setValue(scalingVertical->value());
}

void TabTools::changeImageScalingFree(int)
{
	if (buttonGroup3->isChecked())
		buttonGroup5->setChecked(false);
	else
		buttonGroup5->setChecked(true);
}

void TabTools::changeImageScalingRatio(int)
{
	if (buttonGroup5->isChecked())
		buttonGroup3->setChecked(false);
	else
		buttonGroup3->setChecked(true);
}

void TabTools::setSample()
{
	if (!fontPreview)
		return;

	SampleItem *si = new SampleItem(docu);
	si->setText( tr("Woven silk pyjamas exchanged for blue quartz"));
	if (colorComboTextBackground->currentText() != CommonStrings::NoneColor)
	{
		if (docu != 0)
		{
			si->setBgColor(docu->PageColors[colorComboTextBackground->currentText()].getRawRGBColor());
			si->setBgShade(shadingTextBack->value());
		}
		else
		{
			PrefsManager* prefsManager=PrefsManager::instance();
			ColorList* colorList=prefsManager->colorSetPtr();
			si->setBgColor((*colorList)[colorComboTextBackground->currentText()].getRawRGBColor());
			si->setBgShade(shadingTextBack->value());
		}
	}
	else
		si->setBgColor(paletteBackgroundColor());

	if (colorComboText->currentText() != CommonStrings::NoneColor)
	{
		if (docu != 0)
		{
			si->setTxColor(docu->PageColors[colorComboText->currentText()].getRawRGBColor());
			si->setTxShade(shadingText->value());
		}
		else
		{
			PrefsManager* prefsManager=PrefsManager::instance();
			ColorList* colorList=prefsManager->colorSetPtr();
			si->setTxColor((*colorList)[colorComboText->currentText()].getRawRGBColor());
			si->setTxShade(shadingText->value());
		}
	}
	else
		si->setTxColor(paletteBackgroundColor());
	si->setFont(fontComboText->currentText());
	si->setFontSize(sizeComboText->currentText().left(2).toInt() * 10, true);
	previewText->setPixmap(si->getSample(previewText->width(), previewText->height()));
	delete si;
}

void TabTools::setTool()
{
	if (toolText == sender())
		subStackTools->raiseWidget(0);
	if (toolShape == sender())
		subStackTools->raiseWidget(1);
	if (toolLine == sender())
		subStackTools->raiseWidget(2);
	if (toolImage == sender())
		subStackTools->raiseWidget(3);
	if (toolPoly == sender())
		subStackTools->raiseWidget(4);
	if (toolZoom == sender())
		subStackTools->raiseWidget(5);
	if (toolMisc == sender())
		subStackTools->raiseWidget(6);
}

void TabTools::enableFontPreview(bool state)
{
	fontPreview = state;
	setSample();
}

void TabTools::unitChange(QString unit, int docUnitIndex, int decimals, double invUnitConversion)
{
	double oldMin, oldMax, val;
	int decimalsOld;

	gapText->setSuffix(unit);
	gapText->getValues(&oldMin, &oldMax, &decimalsOld, &val);
	gapText->setValues(oldMin * invUnitConversion, oldMax * invUnitConversion, decimals, val * invUnitConversion);
	gapTab->getValues(&oldMin, &oldMax, &decimalsOld, &val);
	gapTab->setValues(oldMin * invUnitConversion, oldMax * invUnitConversion, decimals, val * invUnitConversion);
	genDispX->getValues(&oldMin, &oldMax, &decimalsOld, &val);
	genDispX->setValues(oldMin * invUnitConversion, oldMax * invUnitConversion, decimals, val * invUnitConversion);
	genDispY->getValues(&oldMin, &oldMax, &decimalsOld, &val);
	genDispY->setValues(oldMin * invUnitConversion, oldMax * invUnitConversion, decimals, val * invUnitConversion);
}
