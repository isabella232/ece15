/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          pageitem.h  -  description
                             -------------------
    begin                : Sat Apr 7 2001
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

#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QObject>
#include <QWidget>
#include <QPolygon>
#include <QStack>
#include <QList>
#include <QKeyEvent>
#include <QMenu>
#include <QRect>
#include <QRectF>
#include <QVector>
#include <QTemporaryFile>

#include "scribusapi.h"
#include "annotation.h"
#include "colormgmt/sccolormgmtstructs.h"
#include "desaxe/saxio.h"
//#include "notesset.h"
#include "observable.h"
#include "pagestructs.h"
#include "scimage.h"
#include "sctextstruct.h"
#include "text/nlsconfig.h"
#include "text/storytext.h"
#include "undoobject.h"
#include "vgradient.h"
#include "mesh.h"
#ifdef HAVE_CONFIG_H
#include "scconfig.h"
#endif

class ScPainter;
class ScribusDoc;
class SimpleState;
class UndoManager;
class UndoState;
class ResourceCollection;
class QFrame;
class QGridLayout;

class PageItem_Arc;
class PageItem_Group;
class PageItem_ImageFrame;
class PageItem_Line;
class PageItem_OSGFrame;
class PageItem_Polygon;
class PageItem_PolyLine;
class PageItem_RegularPolygon;
class PageItem_Table;
class PageItem_TextFrame;
class PageItem_NoteFrame;
class PageItem_PathText;
class PageItem_LatexFrame;
class PageItem_Spiral;
class PageItem_Symbol;
/**
  *@author Franz Schmid
  */

#if defined(_MSC_VER)
#define _unlink unlink
#endif

class SCRIBUS_API PageItem : public QObject, public UndoObject, public SaxIO, public SingleObservable<PageItem>
{
	Q_OBJECT

	// Properties - see http://doc.trolltech.com/3.3/properties.html
	// See the accessors of these properties for details on their use.
	Q_PROPERTY(QString itemName READ itemName WRITE setItemName DESIGNABLE false)
	Q_PROPERTY(QString fillColor READ fillColor WRITE setFillColor DESIGNABLE false)
	Q_PROPERTY(QString lineColor READ lineColor WRITE setLineColor DESIGNABLE false)
	Q_PROPERTY(double fillShade READ fillShade WRITE setFillShade DESIGNABLE false)
	Q_PROPERTY(double lineShade READ lineShade WRITE setLineShade DESIGNABLE false)
	Q_PROPERTY(double fillTransparency READ fillTransparency WRITE setFillTransparency DESIGNABLE false)
	Q_PROPERTY(double lineTransparency READ lineTransparency WRITE setLineTransparency DESIGNABLE false)
	Q_PROPERTY(bool m_Locked READ locked WRITE setLocked DESIGNABLE false)
	Q_PROPERTY(bool m_SizeLocked READ sizeLocked WRITE setSizeLocked DESIGNABLE false)
	//used for notes frames
	Q_PROPERTY(bool m_SizeHLocked READ sizeHLocked WRITE setSizeHLocked DESIGNABLE false)
	Q_PROPERTY(bool m_SizeVLocked READ sizeVLocked WRITE setSizeVLocked DESIGNABLE false)
	Q_PROPERTY(bool m_ImageIsFlippedV READ imageFlippedV WRITE setImageFlippedV DESIGNABLE false)
	Q_PROPERTY(bool m_ImageIsFlippedH READ imageFlippedH WRITE setImageFlippedH DESIGNABLE false)
	Q_PROPERTY(double lineWidth READ lineWidth WRITE setLineWidth DESIGNABLE false)
	Q_PROPERTY(QString customLineStyle READ customLineStyle WRITE setCustomLineStyle DESIGNABLE false)
	Q_PROPERTY(int startArrowIndex READ startArrowIndex WRITE setStartArrowIndex DESIGNABLE false)
	Q_PROPERTY(int endArrowIndex READ endArrowIndex WRITE setEndArrowIndex DESIGNABLE false)

	Q_PROPERTY(bool m_PrintEnabled READ printEnabled WRITE setPrintEnabled DESIGNABLE false)
	Q_PROPERTY(double xPos READ xPos WRITE setXPos DESIGNABLE false)
	Q_PROPERTY(double yPos READ yPos WRITE setYPos DESIGNABLE false)
	Q_PROPERTY(double width READ width WRITE setWidth DESIGNABLE false)
	Q_PROPERTY(double height READ height WRITE setHeight DESIGNABLE false)
	Q_PROPERTY(double rotation READ rotation WRITE setRotation DESIGNABLE false)
	Q_PROPERTY(double imageXScale READ imageXScale WRITE setImageXScale DESIGNABLE false)
	Q_PROPERTY(double imageYScale READ imageYScale WRITE setImageYScale DESIGNABLE false)
	Q_PROPERTY(double imageXOffset READ imageXOffset WRITE setImageXOffset DESIGNABLE false)
	Q_PROPERTY(double imageYOffset READ imageYOffset WRITE setImageYOffset DESIGNABLE false)
	Q_PROPERTY(bool reversed READ reversed WRITE setReversed DESIGNABLE false)
	Q_PROPERTY(double cornerRadius READ cornerRadius WRITE setCornerRadius DESIGNABLE false)
	Q_PROPERTY(double textToFrameDistLeft READ textToFrameDistLeft WRITE setTextToFrameDistLeft DESIGNABLE false)
	Q_PROPERTY(double textToFrameDistRight READ textToFrameDistRight WRITE setTextToFrameDistRight DESIGNABLE false)
	Q_PROPERTY(double textToFrameDistTop READ textToFrameDistTop WRITE setTextToFrameDistTop DESIGNABLE false)
	Q_PROPERTY(double textToFrameDistBottom READ textToFrameDistBottom WRITE setTextToFrameDistBottom DESIGNABLE false)
	Q_PROPERTY(double ColGap READ columnGap WRITE setColumnGap DESIGNABLE false)
	Q_PROPERTY(int Cols READ columns WRITE setColumns DESIGNABLE false)
	Q_ENUMS(FirstLineOffsetPolicy)
	Q_PROPERTY(FirstLineOffsetPolicy firstLineOffset READ firstLineOffset WRITE setFirstLineOffset DESIGNABLE false)
	// FIXME: QMetaProperty can't translate these to/from enumerator names, probably because the
	// properties aren't moc'd in the Qt sources. They work fine in their
	// current state as plain integer properties.
//  	Q_ENUMS(PenStyle)
// 	Q_PROPERTY(PenStyle lineStyle READ lineStyle WRITE setLineStyle DESIGNABLE false)
// 	Q_ENUMS(PenCapStyle)
// 	Q_PROPERTY(PenCapStyle lineEnd READ lineEnd WRITE setLineEnd DESIGNABLE false)
// 	Q_ENUMS(PenJoinStyle)
// 	Q_PROPERTY(PenJoinStyle lineJoin READ lineJoin WRITE setLineJoin DESIGNABLE false)

	// This property may not hang around for too long, but should be useful
	// when testing out the pageitem refactoring work.  Setting it is unlikely
	// to currently have the desired effect.
	/**
	 * @brief Item type.
	 * @warning Do not set this property except for testing and debug purposes.
	 */
	Q_ENUMS(ItemType)
	Q_PROPERTY(ItemType itemType READ itemType WRITE convertTo DESIGNABLE false)

public:
	// Enumerator definitions

	/** @brief Item Type
	 *
	 * Soon, item type will probably go away in favour of using
	 * subclasses and checking types using more conventional methods
	 * and using Qt's MetaObject introspection.
	 * Multiple is used for checking in @sa Selection for all same type of items
	 */
	enum ItemType {
		ItemType1		= 1,
		ImageFrame		= 2,
		ItemType3		= 3,
		TextFrame		= 4,
		Line			= 5,
		Polygon			= 6,
		PolyLine		= 7,
		PathText		= 8,
		LatexFrame  	= 9,
		OSGFrame    	= 10,
		Symbol			= 11,
		Group			= 12,
		RegularPolygon	= 13,
		Arc				= 14,
		Spiral			= 15,
		Table			= 16,
		Multiple		= 99
	};

	/** @brief Text flow mode
	 *
	 * Describe if and how text flow around object
	 */
	enum TextFlowMode {
		TextFlowDisabled = 0,
		TextFlowUsesFrameShape  = 1,
		TextFlowUsesBoundingBox = 2,
		TextFlowUsesContourLine = 3,
		TextFlowUsesImageClipping = 4
	};

	/* these do essentially the same as a dynamic cast but might be more readable */
	virtual PageItem_ImageFrame * asImageFrame() { return NULL; }
	virtual PageItem_Line * asLine() { return NULL; }
	virtual PageItem_PathText * asPathText() { return NULL; }
	virtual PageItem_Polygon * asPolygon() { return NULL; }
	virtual PageItem_PolyLine * asPolyLine() { return NULL; }
	virtual PageItem_TextFrame * asTextFrame() { return NULL; }
	virtual PageItem_NoteFrame * asNoteFrame() { return NULL; }
	virtual PageItem_LatexFrame * asLatexFrame() { return NULL; }

	virtual PageItem_OSGFrame * asOSGFrame() { return NULL; }
	virtual PageItem_Symbol * asSymbolFrame() { return NULL; }
	virtual PageItem_Group * asGroupFrame() { return NULL; }
	virtual PageItem_RegularPolygon * asRegularPolygon() { return NULL; }
	virtual PageItem_Arc * asArc() { return NULL; }
	virtual PageItem_Spiral * asSpiral() { return NULL; }
	virtual PageItem_Table * asTable() { return NULL; }

	virtual bool isImageFrame()		const { return false; }
	virtual bool isLine()			const { return false; }
	virtual bool isPathText()		const { return false; }
	virtual bool isPolygon()		const { return false; }
	virtual bool isPolyLine()		const { return false; }
	virtual bool isTextFrame()		const { return false; }
	virtual bool isLatexFrame()		const { return false; }
	virtual bool isOSGFrame()		const { return false; }
	virtual bool isSymbol()			const { return false; }
	virtual bool isGroup()			const { return false; }
	virtual bool isRegularPolygon()	const { return false; }
	virtual bool isArc()			const { return false; }
	virtual bool isSpiral()			const { return false; }
	virtual bool isTable()			const { return false; }
	virtual bool isNoteFrame()		const { return false; }

	/** @brief Frame Type
	 *
	 * 
	 */
	enum ItemFrameType {
		Unspecified =-1,
		Rectangle	= 0,
		Ellipse		= 1,
		Round		= 2,
		Other		= 3
	};

protected:
	PageItem(const PageItem & other);
	
public:
	PageItem(ScribusDoc *pa, ItemType newType, double x, double y, double w, double h, double w2, QString fill, QString outline);
	~PageItem();

	// Get item level relative to its parent doc or group
	int level();

	void saxx(SaxHandler& handler, const Xml_string& elemtag) const {}
	void saxx(SaxHandler& handler) const {}
	
	/**
	 * @brief Clear the contents of a frame.
	 * WARNING: Currently *they* do not check if the user wants this.
	 * The view does when these are called.
	 */	
	virtual void clearContents() {}
	
	/**
	 * @brief Adjust the picture scale, moved from the view, no view code here
	 * FIXME: Move to PageItem_TextFrame
	 */
	void AdjustPictScale();
	
	/**
	 * @brief Set or get the redraw bounding box of the item, moved from the View
	 */
	QRect getRedrawBounding(const double);
	void setRedrawBounding();
			
	/**
	 * @brief Update the gradient vectors, moved from the View
	 */		
	void updateGradientVectors();
	/**
	 * @brief Move the image within the frame
	 * Old ScribusView::MoveItemI
	 * @todo Move to PageItem_ImageFrame
	 */
	void moveImageInFrame(double newX, double newY);

	ObjAttrVector* getObjectAttributes();
	/*!
	 * brief Returns a list of attributes with specified name
	 */
	QList<ObjectAttribute> getObjectAttributes(QString attributeName) const;
	/*!
	 * brief Returns a complete ObjectAttribute struct if 1 is found, or ObjectAttribute.name will be QString::null if 0 or >1 are found
	 */
	ObjectAttribute getObjectAttribute(QString) const;
	void setObjectAttributes(ObjAttrVector*);
	
	virtual bool createInfoGroup(QFrame *, QGridLayout *) {return false;}
	
  /** Zeichnet das Item */
	void DrawObj(ScPainter *p, QRectF e);
	void DrawObj_Pre(ScPainter *p);
	virtual void DrawObj_Post(ScPainter *p);
	virtual void DrawObj_Decoration(ScPainter *p);
	virtual void DrawObj_Item(ScPainter *p, QRectF e) = 0;
	QImage DrawObj_toImage(double maxSize);
	QImage DrawObj_toImage(QList<PageItem*> &emG, double scaling);
	
	virtual void applicableActions(QStringList& actionList) = 0;
	virtual QString infoDescription();
			
protected:
	void DrawObj_ImageFrame(ScPainter *p, double sc);
	void DrawObj_Polygon(ScPainter *p);
	void DrawObj_PolyLine(ScPainter *p);
	void DrawObj_PathText(ScPainter *p, double sc);
public:
	void DrawObj_Embedded(ScPainter *p, QRectF e, const CharStyle& style, PageItem* cembedded);
	void DrawStrokePattern(ScPainter *p, QPainterPath &path);
	void SetFrameShape(int count, double *vals);
	void SetRectFrame();
	void SetOvalFrame();
	void SetFrameRound();
	void setPolyClip(int up, int down = 0);
	void updatePolyClip();
	//added switch for not updating welded items - used by notes frames with automatic size adjusted
	void updateClip(bool updateWelded = true);
	void convertClip();
	void getBoundingRect(double *x1, double *y1, double *x2, double *y2) const;
	void getVisualBoundingRect(double *x1, double *y1, double *x2, double *y2) const;
	QRectF getBoundingRect() const;
	QRectF getCurrentBoundingRect(double moreSpace = 0.0) const;
	QRectF getVisualBoundingRect() const;
	QTransform getGroupTransform() const;
	void getTransform(QTransform& mat) const;
	QTransform getTransform() const;
	QTransform getCombinedTransform() const;
	/**
	 * @brief Check if a QPoint is within the items boundaries
	 * No coordinates transformation is performed
	 * @param x X position
		@param y Y position
	 * @return bool true if x, i in the item
	 */
	bool pointWithinItem(const int x, const int y) const;
	/**
	 * @brief Check if the mouse is within the items boundaries
	 * This method performs necessary page to device transformations
		@param x X position
		@param y Y position
		@param scale scale of the vport
	 * @return bool true if the x, y is in the bounds 
	 */
	bool mouseWithinItem(const int x, const int y, double scale) const;
	
	virtual void handleModeEditKey(QKeyEvent *k, bool &keyRepeat);
	
	/// invalidates current layout information
	virtual void invalidateLayout() { invalid = true; }
	/// creates valid layout information
	virtual void layout() {}
	/// returns frame where is text end
	PageItem * frameTextEnd();
	int maxCharsInFrame();
	/// returns true if text overflows
	bool frameOverflows() const;
	bool frameUnderflows() const;
	int frameOverflowCount() const;
	/// Draws the overflow marker.
	void drawOverflowMarker(ScPainter *p);
	/// returns index of first char displayed in this frame, used to be 0
	int firstInFrame() const;
	/// returns index of last char displayed in this frame, used to be MaxChars-1
	int lastInFrame() const;
	/// tests if a character is displayed by this frame
	bool frameDisplays(int textpos) const;
	/// returns the style at the current charpos
	const ParagraphStyle& currentStyle() const;
	/// returns the style at the current charpos
	ParagraphStyle& changeCurrentStyle();
	/// returns the style at the current charpos
	const CharStyle& currentCharStyle() const;
	/// Return current text properties (current char + paragraph properties)
	void currentTextProps(ParagraphStyle& parStyle) const;
	// deprecated:
	double layoutGlyphs(const CharStyle& style, const QString& chars, GlyphLayout& layout);
	void SetQColor(QColor *tmp, QString farbe, double shad);
	void drawGlyphs(ScPainter *p, const CharStyle& style, GlyphLayout& glyphs );
	void DrawPolyL(QPainter *p, QPolygon pts);
	QString ExpandToken(uint base);
	
	bool AutoName;	
	double gXpos;
	double gYpos;
	double gWidth;
	double gHeight;
	int GrType;			// used values 6 = linear, 7 = radial, 8 = pattern, 9 = 4 color gradient, 10 = diamond, 11 = mesh gradient
	double GrStartX;
	double GrStartY;
	double GrEndX;
	double GrEndY;
	double GrFocalX;
	double GrFocalY;
	double GrScale;
	double GrSkew;
	FPoint GrControl1;
	FPoint GrControl2;
	FPoint GrControl3;
	FPoint GrControl4;
	FPoint GrControl5;
	QString GrColorP1;
	QString GrColorP2;
	QString GrColorP3;
	QString GrColorP4;
	double GrCol1transp;
	double GrCol2transp;
	double GrCol3transp;
	double GrCol4transp;
	int GrCol1Shade;
	int GrCol2Shade;
	int GrCol3Shade;
	int GrCol4Shade;
	QList<meshGradientPatch> meshGradientPatches;
	QList<QList<meshPoint> > meshGradientArray;
	int selectedMeshPointX;
	int selectedMeshPointY;
	int selectedMeshControlPoint;
	bool snapToPatchGrid;
	int Cols;
	double ColGap;
	double gridOffset_;
	double gridValue_;

	/** Linestyle */
	Qt::PenStyle PLineArt;
	Qt::PenCapStyle PLineEnd;
	Qt::PenJoinStyle PLineJoin;
	QString NamedLStyle;
  /** Defines clipping region of the elements; */
	QPolygon Clip;
	
	FPointArray PoLine;
	const FPointArray shape() const { return PoLine; }
	void setShape(FPointArray val) { PoLine = val; }
	
	FPointArray ContourLine;
	const FPointArray contour() const { return ContourLine; }
	void setContour(FPointArray val) { ContourLine = val; }
	
	FPointArray imageClip;
	QList<uint> Segments;
	ScImageEffectList effectsInUse;
	bool PoShow;
	double BaseOffs;
	int textPathType;
	bool textPathFlipped;
	bool flipPathText() const { return textPathFlipped; }
	void setFlipPathText(bool val) { textPathFlipped = val; }
	int pathTextType() const { return textPathType; }
	void setPathTextType(int val) { textPathType = val; }
	double pathTextBaseOffset() const { return BaseOffs; }
	void setPathTextBaseOffset(double val) { BaseOffs = val; }
	bool pathTextShowFrame() const { return PoShow; }
	void setPathTextShowFrame(bool val) { PoShow = val; }
	
	bool useEmbeddedImageProfile() const { return UseEmbedded; }
	void setUseEmbeddedImageProfile(bool val) { UseEmbedded = val; }
	QString embeddedImageProfile() const { return EmProfile; }
	void setEmbeddedImageProfile(QString val) { EmProfile = val; }

	
	bool ClipEdited;
	// Don't know exactly what this is, but it's not the same as itemType
	int FrameType;
  /** Internal unique Item-Number, used for the undo system */
	uint uniqueNr;
  /** Hat Element Rahmen? FIXME: still used? - in DrawObject_Post */
	bool Frame;
  /** page this element belongs to */
	int OwnPage;
	/** @brief Old page number tracked for the move undo action */
	int oldOwnPage;
	int savedOwnPage;
  /** Darzustellendes Bild */
	ScImage pixm;
  /** Dateiname des Bildes */
	QString Pfile;
	QString Pfile2;
	QString Pfile3;
	QString externalFile() const { return Pfile; }
	void setExternalFile(QString val);
	void setImagePagenumber(int num) { pixm.imgInfo.actualPageNumber = num; }
	
	//FIXME: maybe these should go into annotation?
	QString fileIconPressed() const { return Pfile2; }
	void setFileIconPressed(QString val);
	QString fileIconRollover() const { return Pfile3; }
	void setFileIconRollover(QString val);
	
	QString IProfile;
	bool UseEmbedded;
	QString EmProfile;
	eRenderIntent IRender;
	// some accessor methods:
	int  cmsRenderingIntent() const { return IRender; }
	void setCmsRenderingIntent(eRenderIntent val) { IRender = val; }
	QString cmsProfile() const { return IProfile; }
	void setCmsProfile(QString val) { IProfile = val; }
	bool OverrideCompressionMethod;
	int CompressionMethodIndex;
	bool OverrideCompressionQuality;
	int CompressionQualityIndex;
	void setOverrideCompressionMethod(bool val) { OverrideCompressionMethod = val; }
	void setCompressionMethodIndex(int val) { CompressionMethodIndex = val; }
	void setOverrideCompressionQuality(bool val) { OverrideCompressionQuality = val; }
	void setCompressionQualityIndex(int val) { CompressionQualityIndex = val; }
	
	/*! Flag to hiold image file availability */
	bool PictureIsAvailable;
	int OrigW;
	int OrigH;
  /** BoundigBox-X */
	double BBoxX;
  /** BoundingBox-H */
	double BBoxH;
  /** Zeichen X-Position */
	double CurX;
  /** Zeichen Y-Position */
	double CurY;
  /** Text des Elements */
	StoryText itemText;
  /** Flag fuer PDF-Bookmark */
	bool isBookmark;
  /** Flag for redraw in EditMode */
	bool Dirty;
	/** Flag indicates that layout has changed (eg. for textlayout) */
	bool invalid;
  /** Flag fuer Auswahl */
	bool HasSel;
	/** avoid artefacts while moving */
	bool FrameOnly;
	bool isAutoText;
	PageItem* prevInChain() { return BackBox; }
	PageItem* nextInChain() { return NextBox; }
	const PageItem* prevInChain() const { return BackBox; }
	const PageItem* nextInChain() const { return NextBox; }
	//you can change all code for search first or last item in chain
	PageItem* firstInChain();
	PageItem* lastInChain();
	PageItem *Parent;

	bool testLinkCandidate(PageItem* nextFrame);
	void unlink();
	void link(PageItem* nextFrame);
	void dropLinks();
	void unlinkWithText(bool);

protected:
	PageItem *BackBox;
	PageItem *NextBox;
	uint firstChar;
	uint MaxChars;
public:
	bool inPdfArticle;
	bool isRaster;
	double OldB;
	double OldH;
	double OldB2;
	double OldH2;
	bool Sizing;
//	bool toPixmap;
	int  LayerID;
	bool ScaleType;
	bool AspectRatio;
	QVector<double> DashValues;
	double DashOffset;
	const QVector<double>& dashes() const { return DashValues; }
	QVector<double>& dashes() { return DashValues; }
	void setDashes(QVector<double> val) { DashValues = val; }
	double dashOffset() const { return DashOffset; }
	void setDashOffset(double val) { DashOffset = val; }
	VGradient fill_gradient;
	bool fillRule;
	bool doOverprint;

/* Additions for Table Support */
/* now deprecated with the new PageItem_Table */
	PageItem* LeftLink;
	PageItem* RightLink;
	PageItem* TopLink;
	PageItem* BottomLink;
	int LeftLinkID;
	int RightLinkID;
	int TopLinkID;
	int BottomLinkID;
	bool LeftLine;
	bool RightLine;
	bool TopLine;
	bool BottomLine;
	bool isTableItem;
/* end deprecated vars */

	bool isSingleSel;
	QList<PageItem*> groupItemList;
	virtual QList<PageItem*> getItemList();
	double groupWidth;
	double groupHeight;
	double BoundingX;
	double BoundingY;
	double BoundingW;
	double BoundingH;
	bool ChangedMasterItem;
	QString OnMasterPage;
	bool isEmbedded;
	int inlineCharID;
	
	//Position
	double xPos() const { return Xpos; }
	double yPos() const { return Ypos; }
	double visualXPos() const;
	double visualYPos() const;
	FPoint xyPos() const { return FPoint(Xpos, Ypos); }
	void setXPos(const double, bool drawingOnly=false);
	void setYPos(const double, bool drawingOnly=false);
	void setXYPos(const double, const double, bool drawingOnly=false);
	void moveBy(const double, const double, bool drawingOnly=false);
	//Size
	double width() const { return Width; }
	double height() const { return Height; }
	double visualWidth() const;
	double visualHeight() const;
	double visualLineWidth();
	void setWidth(const double);
	void setHeight(const double);
	void setWidthHeight(const double, const double, bool drawingOnly);
	void setWidthHeight(const double, const double);
	void resizeBy(const double, const double);
	//Rotation
	double rotation() const { return Rot; }
	void setRotation(const double, bool drawingOnly);
	void setRotation(const double r) { setRotation(r, false); }  // needed for deSaXe
	void rotateBy(const double);
	//Selection
	bool isSelected() const { return Select; }
	void setSelected(const bool);
	//Image Data
	double imageXScale() const { return LocalScX; }
	double imageYScale() const { return LocalScY; }
	void setImageXScale(const double);
	void setImageYScale(const double);
	void setImageXYScale(const double, const double);
	double imageXOffset() const { return LocalX; }
	double imageYOffset() const { return LocalY; }
	void setImageXOffset(const double);
	void setImageYOffset(const double);
	void moveImageXYOffsetBy(const double, const double);
	void setImageXYOffset(const double, const double);
	double imageRotation() const { return LocalRot; }
	void setImageRotation(const double newRotation);
	//Reverse
	bool reversed() const { return Reverse; }
	void setReversed(bool);
	//Rounded Corners
	double cornerRadius() const { return RadRect; }
	void setCornerRadius(double);
	// PDF bookmark
	bool isPDFBookmark() const { return isBookmark; }
	void setIsPDFBookmark(bool val) { isBookmark = val; }
	// 0=none, 1,2,3,4=linear, 5=radial, 6=free linear, 7=free radial, 8=pattern 
	int gradientType() const { return GrType; }
	void setGradientType(int val) { GrType = val; }
	void set4ColorGeometry(FPoint c1, FPoint c2, FPoint c3, FPoint c4);
	void set4ColorTransparency(double t1, double t2, double t3, double t4);
	void set4ColorShade(int t1, int t2, int t3, int t4);
	void set4ColorColors(QString col1, QString col2, QString col3, QString col4);
	void get4ColorGeometry(FPoint &c1, FPoint &c2, FPoint &c3, FPoint &c4);
	void setDiamondGeometry(FPoint c1, FPoint c2, FPoint c3, FPoint c4, FPoint c5);
	void get4ColorTransparency(double &t1, double &t2, double &t3, double &t4);
	void get4ColorColors(QString &col1, QString &col2, QString &col3, QString &col4);
	void setMeshPointColor(int x, int y, QString color, int shade, double transparency, bool forPatch = false);
	void createGradientMesh(int rows, int cols);
	void resetGradientMesh();
	void meshToShape();
	void createConicalMesh();
	VColorStop computeInBetweenStop(VColorStop* last, VColorStop* actual, double t);
	void gradientVector(double& startX, double& startY, double& endX, double& endY, double &focalX, double &focalY, double &scale, double &skew) const;
	void setGradientVector(double startX, double startY, double endX, double endY, double focalX, double focalY, double scale, double skew);

	int strokeGradientType() const { return GrTypeStroke; }
	void setStrokeGradientType(int val) { GrTypeStroke = val; }
	void strokeGradientVector(double& startX, double& startY, double& endX, double& endY, double &focalX, double &focalY, double &scale, double &skew) const;
	void setStrokeGradientVector(double startX, double startY, double endX, double endY, double focalX, double focalY, double scale, double skew);

	int maskType() const { return GrMask; }
	void setMaskType(int val) { GrMask = val; }
	void setGradientMask(const QString &newMask);
	void setPatternMask(const QString &newMask);
	QString gradientMask() const { return gradientMaskVal; }
	QString patternMask() const { return patternMaskVal; }
	void maskVector(double& startX, double& startY, double& endX, double& endY, double &focalX, double &focalY, double &scale, double &skew) const;
	void setMaskVector(double startX, double startY, double endX, double endY, double focalX, double focalY, double scale, double skew);
	void maskTransform(double &scaleX, double &scaleY, double &offsetX, double &offsetY, double &rotation, double &skewX, double &skewY) const;
	void setMaskTransform(double scaleX, double scaleY, double offsetX, double offsetY, double rotation, double skewX, double skewY);
	void setMaskFlip(bool flipX, bool flipY);
	void maskFlip(bool &flipX, bool &flipY);
	// 
	bool fillEvenOdd() const { return fillRule; }
	void setFillEvenOdd(bool val) { fillRule = val; }
	//
	bool overprint() const { return doOverprint; }
	void setOverprint(bool val) { doOverprint = val; }
	// rect / oval / round / other
	int frameType() const { return FrameType; }
	void setFrameType(int val) { FrameType = val; }
	//
	bool hasDefaultShape() const { return !ClipEdited; }
	void setHasDefaultShape(bool val) { ClipEdited = !val; }
	//
	bool isAutoFrame() const { return isAutoText; }
	void setIsAutoFrame(bool val) { isAutoText = val; }
	//
	bool keepAspectRatio() const { return AspectRatio; }
	void setKeepAspectRatio(bool val) { AspectRatio = val; }
	//
	bool fitImageToFrame() const { return !ScaleType; }
	void setFitImageToFrame(bool val) { ScaleType = !val; }
	bool isImageInline() const { return isInlineImage; }
	void setImageInline(bool val) { isInlineImage = val; }
	QString inlineExt;
	void setInlineExt(QString val) { inlineExt = val; }
	void setInlineData(QString data);
	void makeImageInline();
	void makeImageExternal(QString path);
	
	//Text Data - Move to PageItem_TextFrame at some point? --- no, to FrameStyle, av
	double textToFrameDistLeft() const { return Extra; }
	double textToFrameDistRight() const { return RExtra; }
	double textToFrameDistTop() const { return TExtra; }
	double textToFrameDistBottom() const { return BExtra; }
	int columns() const { return Cols; }
	double columnGap() const { return ColGap; }
	double gridOffset() const;
	double gridDistance() const;
	void setTextToFrameDistLeft(double);
	void setTextToFrameDistRight(double);
	void setTextToFrameDistTop(double);
	void setTextToFrameDistBottom(double);
	void setColumns(int);
	void setColumnGap(double);
	void setGridOffset(double);
	void setGridDistance(double);
	FirstLineOffsetPolicy firstLineOffset()const;
	void setFirstLineOffset(FirstLineOffsetPolicy);
	/**
	 * \brief Set the text to frame distances all at once
	 * @param newLeft left distance
	 * @param newRight right distance
	 * @param newTop top distance
	 * @param newBottom bottom distance
	 */
	void setTextToFrameDist(double newLeft, double newRight, double newTop, double newBottom);

	/**  @brief Get name of the item
	 *
	 * This is unrelated to QObject::name(); the pageItem's name is independent
	 * of its Qt name.
	 * See also PageItem::setItemName()
	 */
	QString itemName() const { return AnName; }
	/**
	 * @brief Set name of the item
	 * @param newName name for the item
	 * @author Riku Leino
	 *
	 * Note that this is unrelated to QObject::setName()
	 * See also PageItem::itemName()
	 */
	void setItemName(const QString& newName);

	/** @brief Get the name of the gradient of the object */
	QString gradient() const { return gradientVal; }

	/**
	 * @brief Set the fill gradient of the object.
	 * @param newGradient fill gradient for the object
	 */
	void setGradient(const QString &newGradient);

	/** @brief Get the name of the stroke gradient of the object */
	QString strokeGradient() const { return gradientStrokeVal; }

	/**
	 * @brief Set the stroke gradient of the object.
	 * @param newGradient stroke gradient for the object
	 */
	void setStrokeGradient(const QString &newGradient);

	/** @brief Get the name of the pattern of the object */
	QString pattern() const { return patternVal; }

	/** @brief Get the pattern transformation matrix of the object */
	void patternTransform(double &scaleX, double &scaleY, double &offsetX, double &offsetY, double &rotation, double &skewX, double &skewY) const;

	/**
	 * @brief Set the fill pattern of the object.
	 * @param newPattern fill pattern for the object
	 */
	void setPattern(const QString &newPattern);
	
	/**
	 * @brief Set the fill pattern transformation of the object.
	 */
	void setPatternTransform(double scaleX, double scaleY, double offsetX, double offsetY, double rotation, double skewX, double skewY);
	void setPatternFlip(bool flipX, bool flipY);
	void patternFlip(bool &flipX, bool &flipY);

	/** @brief Get the (name of the) fill color of the object */
	QString fillColor() const { return fillColorVal; }
	/**
	 * @brief Set the fill color of the object.
	 * @param newColor fill color for the object
	 */
	void setFillColor(const QString &newColor);

	/** @brief Get the shade of the fill color */
	double fillShade() const { return fillShadeVal; }
	/**
	 * @brief Set the fill color shade.
	 * @param newShade shade for the fill color
	 */
	void setFillShade(double newShade);

	/** @brief Get the transparency of the fill color */
	double fillTransparency() const { return fillTransparencyVal; }
	/**
	 * @brief Set the transparency of the fill color.
	 * @param newTransparency transparency of the fill color
	 */
	void setFillTransparency(double newTransparency);

	/** @brief Get the blendmode of the fill color */
	int fillBlendmode() const { return fillBlendmodeVal; }
	/**
	 * @brief Set the blendmode of the fill color.
	 * @param newBlendmode blendmode of the fill color
	 */
	void setFillBlendmode(int newBlendmode);

	/** @brief Get the blendmode of the stroke color */
	int lineBlendmode() const { return lineBlendmodeVal; }
	/**
	 * @brief Set the blendmode of the stroke color.
	 * @param newBlendmode blendmode of the stroke color
	 */
	void setLineBlendmode(int newBlendmode);

	/** @brief Get the line color of the object */
	QString lineColor() const { return lineColorVal; }
	/**
	 * @brief Set the line color of the object.
	 * @param newColor line color for the object
	 */
	void setLineColor(const QString &newColor);

	/** @brief Get the line color shade */
	double lineShade() const { return lineShadeVal; }
	/**
	 * @brief Set the line color shade.
	 * @param newShade shade for the line color
	 */
	void setLineShade(double newShade);

	/** @brief Get the line transparency */
	double lineTransparency() const { return lineTransparencyVal; }
	/**
	 * @brief Set the transparency of the line color.
	 * @param newTransparency transparency of the line color
	 */
	void setLineTransparency(double newTransparency);

	/** @brief Get the name of the stroke pattern of the object */
	QString strokePattern() const { return patternStrokeVal; }

	/** @brief Get the stroke pattern transformation matrix of the object */
	void strokePatternTransform(double &scaleX, double &scaleY, double &offsetX, double &offsetY, double &rotation, double &skewX, double &skewY, double &space) const;

	/**
	 * @brief Set the stroke pattern of the object.
	 * @param newPattern stroke pattern for the object
	 */
	void setStrokePattern(const QString &newPattern);
	
	/**
	 * @brief Set the stroke pattern transformation of the object.
	 */
	void setStrokePatternTransform(double scaleX, double scaleY, double offsetX, double offsetY, double rotation, double skewX, double skewY, double space);
	void setStrokePatternFlip(bool flipX, bool flipY);
	void strokePatternFlip(bool &flipX, bool &flipY);
	void setStrokePatternToPath(bool enable);
	bool isStrokePatternToPath();

	/** @brief Set the QColor for the line */
	void setLineQColor();
	/** @brief Set the QColor for the fill */
	void setFillQColor();

	/** @brief Get the style of line */
	Qt::PenStyle lineStyle() const { return PLineArt; }
	/**
	 * @brief Set the style of line.
	 * @param newStyle style of line
	 * @sa Qt::PenStyle
	 */
	void setLineStyle(Qt::PenStyle newStyle);

	/** @brief Get the width of the line */
	double lineWidth() const { return m_lineWidth; }
	/**
	 * @brief Set the width of line
	 * @param newWidth width of line
	 */
	void setLineWidth(double newWidth);

	/** @brief Get the end cap style of the line */
	Qt::PenCapStyle lineEnd() const { return PLineEnd; }
	/**
	 * @brief Set the end style of line
	 * @param newStyle end style of line
	 * @sa Qt::PenCapStyle
	 */
	void setLineEnd(Qt::PenCapStyle newStyle);

	/** @brief Get the join style of multi-segment lines */
	Qt::PenJoinStyle lineJoin() const { return PLineJoin; }
	/**
	 * @brief Set the join style of line
	 * @param newStyle join style of line
	 * @sa Qt::PenJoinStyle
	 */
	void setLineJoin(Qt::PenJoinStyle newStyle);

	/** @brief Get name of active custom line style */
	QString customLineStyle() const { return NamedLStyle; }
	/**
	 * @brief Set custom line style
	 * @param newStyle name of the custom style
	 */
	void setCustomLineStyle(const QString& newStyle);

	/** @brief Get start arrow index
	 * @sa PageItem::endArrowIndex(), PageItem::setStartArrowIndex()
	 */
	int startArrowIndex() const { return m_startArrowIndex; }
	/**
	 * @brief Set start arrow index
	 * @param newIndex index for start arrow
	 */
	void setStartArrowIndex(int newIndex);

	/** @brief Get end arrow index
	 * @sa PageItem::startArrowIndex(), PageItem::setEndArrowIndex()
	 */
	int endArrowIndex() const { return m_endArrowIndex; }
	/**
	 * @brief Set end arrow index
	 * @param newIndex index for end arrow
	 */
	void setEndArrowIndex(int newIndex);

	/** @brief Get start arrow scale
	 * @sa PageItem::endArrowIndex(), PageItem::setStartArrowIndex()
	 */
	int startArrowScale() const { return m_startArrowScale; }
	/**
	 * @brief Set start arrow scale
	 * @param newIndex scale for start arrow
	 */
	void setStartArrowScale(int newScale);

	/** @brief Get end arrow scale
	 * @sa PageItem::startArrowIndex(), PageItem::setEndArrowIndex()
	 */
	int endArrowScale() const { return m_endArrowScale; }
	/**
	 * @brief Set end arrow scale
	 * @param newIndex scale for end arrow
	 */
	void setEndArrowScale(int newScale);

	/** @brief Is the image flipped horizontally? */
	bool imageFlippedH() const { return m_ImageIsFlippedH; }
	/** @brief Horizontally flip / unflip the image */
	void setImageFlippedH(bool flipped);
	/** @brief Flip an image horizontally. */
	void flipImageH();

	/** @brief Is the image flipped vertically? */
	bool imageFlippedV() const { return m_ImageIsFlippedV; }
	/** @brief Vertically flip / unflip the image */
	void setImageFlippedV(bool flipped);
	/** @brief Flip an image vertically */
	void flipImageV();

	/**
	 * @brief Set the image scaling mode.
	 * @param freeScale is the scaling free (not forced to frame size)
	 * @param keepRatio should the image's aspect ratio be respected
	 */
	void setImageScalingMode(bool freeScale, bool keepRatio);

	/** @brief Lock or unlock this pageitem. */
	void toggleLock();
	/** @brief is the item locked ? */
	bool locked() const { return m_Locked; }
	/** @brief Lock or unlock this pageitem */
	void setLocked(bool isLocked);

	/** @brief Toggle lock for resizing */
	void toggleSizeLock();
	/** @brief Is the item's size locked? */
	bool sizeLocked() const { return m_SizeLocked; }
	bool sizeHLocked() const { return m_SizeHLocked || m_SizeLocked; }
	bool sizeVLocked() const { return m_SizeVLocked || m_SizeLocked; }
	/** @brief set lock for resizing */
	void setSizeLocked(bool isLocked);
	void setSizeHLocked(bool isLocked) { m_SizeHLocked = isLocked; }
	void setSizeVLocked(bool isLocked) { m_SizeVLocked = isLocked; }

	/**
	 * @brief Does text flow around this object and how
	 * @sa setTextFlowMode()
	 */
	TextFlowMode textFlowMode() const { return textFlowModeVal; }

	/**
	 * @brief Changes the way text flows around this item
	 * @param mode true if text is wanted to flow around this object or false if not
	 * @sa textFlowMode()
	 */
	void setTextFlowMode(TextFlowMode mode);

	/**
	 * @brief If text should flow around object frame
	 * @sa PageItem::setTextFlowMode()
	 */
	bool textFlowAroundObject() const { return (textFlowModeVal != TextFlowDisabled); }

	/**
	 * @brief If text should flow around object frame
	 * @sa PageItem::setTextFlowMode()
	 */
	bool textFlowUsesFrameShape() const { return (textFlowModeVal == TextFlowUsesFrameShape); }

	/**
	 * @brief If text should flow around bounding box
	 * @sa PageItem::setTextFlowMode()
	 */
	bool textFlowUsesBoundingBox() const { return (textFlowModeVal == TextFlowUsesBoundingBox); }

	/**
	 * @brief If text should flow around contour line
	 * @sa PageItem::setTextFlowMode()
	 */
	bool textFlowUsesContourLine() const { return (textFlowModeVal == TextFlowUsesContourLine); }

	/**
	 * @brief If text should flow around image clipping path
	 * @sa PageItem::setTextFlowMode()
	 */
	bool textFlowUsesImageClipping() const { return (textFlowModeVal == TextFlowUsesImageClipping); }
	
	/**
	 * @brief To be called carefully because it eventually triggers a relayout of long text frames strings, but necesarily when you change the document.
	 * @param allItems While you generally want to check for items below, it can happen that you want to update full range of text frames (e.g. when shuffle items order). Default to false.
	 */
	void checkTextFlowInteractions(bool allItems = false);
	
	/** @brief Get the frame type
	 *
	 * @attention The whole concept of frame types is due for some radical
	 *            re-working, so don't rely on this interface staying stable.
	 *            It's here as an interim step to eliminate direct member access
	 *            on PageItems.
	 */
	ItemType itemType() const { return m_ItemType; }
	/** @brief Get the subclass item type
	 *
	 * This function should be used everywhere, where a itemType is required, but
	 * no C++ type informations is available. e.g. when saving files, etc.
	 * It returns the same type as itemType() for the standard classes, but 
	 * subclasses override it.
	 */
	virtual ItemType realItemType() const { return m_ItemType; }
	/**
	 * @brief Convert this PageItem to PageItem type <code>newType</code>
	 * @param newType PageItem type for conversion
	 */
	void convertTo(ItemType newType);

	/**
	* Set the layer for the item
	* @param layerId layer where this item is moved
	*/
	virtual void setLayer(int layerId);

	/**
	 * @brief Check the changes to the item and add undo actions for them.
	 * @param force Force the check. Do not care if mouse button or arrow key is down
	 * check anyway.
	 * @author Riku Leino
	 */
	void checkChanges(bool force = false);
	/**
	 * @name Store undo actions
	 * @brief Add an undo action to the undo guis
	 * @author Riku Leino
	 */
	/*@{*/
	void moveUndoAction();
	void resizeUndoAction();
	void rotateUndoAction();
	void changeImageOffsetUndoAction();
	void changeImageScaleUndoAction();
	/*@}*/
	/** @brief Required by the UndoObject */
	void restore(UndoState *state, bool isUndo);

	virtual void getNamedResources(ResourceCollection& lists) const;
	virtual void replaceNamedResources(ResourceCollection& newNames);

	/**
	 * @brief Return a variant of `originalName' that is guaranteed to be unique
	 *        in the same document as this PageItem.  If the passed name is not
	 *        in use it is returned unchanged.
	 * @author Craig Ringer
	 *
	 * Usually of the form 'Copy of [name]' or 'Copy of [name] (n)'
	 * cezaryece: if prependCopy is false then form '[name] (n)' is generated
	 */
	QString generateUniqueCopyName(const QString originalName, bool prependCopy = true) const;
	/**
	 * @brief Is this item printed?
	 * @sa setPrintEnabled()
	 */
	bool printEnabled() const { return m_PrintEnabled; }
	/**
	 * @brief Tells if the frame is set to be printed or not
	 * @sa printable()
	 */
	void setPrintEnabled(bool toPrint);
	
	/** @brief Toggle printable
	 * @sa setPrintable()
	 */
	void togglePrintEnabled();
	
	/**
	 * @brief Tells if the frame is tagged or not
	 * @sa isTagged()
	 */
	bool isTagged() const { return tagged; }
	/**
	 * @brief Set the tagged member for use when deleting items, instead of reselecting them.
	 * @sa setTagged()
	 */
	void setTagged(bool);

	/**
	 * @brief Load an image into an image frame, moved from ScribusView
	 * @return True if load succeeded
	 */
	bool loadImage(const QString& filename, const bool reload, const int gsResolution=-1, bool showMsg = false);
	
	
	/**
	 * @brief Connect the item's signals to the GUI, primarily the Properties palette, also some to ScMW
	 * @return 
	 */
	bool connectToGUI();
	bool disconnectFromGUI();
	/**
	 * @brief Emit the items properties to the GUI in one go
	 */
	void emitAllToGUI();
	
	/**
	 * @brief Get the document that this item belongs to
	 */
	ScribusDoc* doc() const { return m_Doc; }
	
	bool isAnnotation() const { return m_isAnnotation; }
	void setIsAnnotation(bool);
	void setAnnotation(const Annotation& ad);
	Annotation& annotation() { return m_annotation; }
	const Annotation& annotation() const { return m_annotation; }
	
	bool imageShown() const { return PicArt; }
	void setImageShown(bool);
	
	void updateConstants();
	
private:
	/**
	 * @brief Helper method to create a modifier string from the current image effects list.
	 * @sa loadImage()
	 */
	QString getImageEffectsModifier() const;

protected:

	void drawLockedMarker(ScPainter *p);
	void drawArrow(ScPainter *p, QTransform &arrowTrans, int arrowIndex);
	
	/** @brief Manages undostack and is where all undo actions/states are sent. */
	UndoManager * const undoManager;
	/**
	 * @name Restore helper methods
	 * Split the restore method for easier handling.
	 * @author Riku Leino
	 */
	/*@{*/
	void restorePasteInline(SimpleState *state, bool isUndo);
	void restorePasteText(SimpleState *state, bool isUndo);
	void restoreFirstLineOffset(SimpleState *state, bool isUndo);
	void restoreParagraphStyle(SimpleState *state, bool isUndo);
	void restoreDefaultParagraphStyle(SimpleState *state, bool isUndo);
	void restoreCharStyle(SimpleState *state, bool isUndo);
	void restoreLeftTextFrameDist(SimpleState *state, bool isUndo);
	void restoreRightTextFrameDist(SimpleState *state, bool isUndo);
	void restoreTopTextFrameDist(SimpleState *state, bool isUndo);
	void restoreBottomTextFrameDist(SimpleState *state, bool isUndo);
	void restoreSetCharStyle(SimpleState *state, bool isUndo);
	void restoreColumns(SimpleState *state, bool isUndo);
	void restoreColumnsGap(SimpleState *state, bool isUndo);
	void restoreSetParagraphStyle(SimpleState *state, bool isUndo);
	void restoreLoremIpsum(SimpleState *state, bool isUndo);
	void restoreDeleteFrameText(SimpleState *state, bool isUndo);
	void restoreInsertFrameText(SimpleState *state, bool isUndo);
	void restoreMove(SimpleState *state, bool isUndo);
	void restoreResize(SimpleState *state, bool isUndo);
	void restoreRotate(SimpleState *state, bool isUndo);
	void restoreFill(SimpleState *state, bool isUndo);
	void restoreShade(SimpleState *state, bool isUndo);
	void restoreLineColor(SimpleState *state, bool isUndo);
	void restoreLineShade(SimpleState *state, bool isUndo);
	void restoreName(SimpleState *state, bool isUndo);
	void restoreFillTP(SimpleState *state, bool isUndo);
	void restoreLineTP(SimpleState *state, bool isUndo);
	void restoreLineStyle(SimpleState *state, bool isUndo);
	void restoreLineEnd(SimpleState *state, bool isUndo);
	void restoreLineJoin(SimpleState *state, bool isUndo);
	void restoreLineWidth(SimpleState *state, bool isUndo);
	void restoreCustomLineStyle(SimpleState *state, bool isUndo);
	void restoreArrow(SimpleState *state, bool isUndo, bool isStart);

	void restorePStyle(SimpleState *state, bool isUndo);

	void restoreType(SimpleState *state, bool isUndo);
	void restoreTextFlowing(SimpleState *state, bool isUndo);
	void restoreImageScaleMode(SimpleState *state, bool isUndo);
	void restoreImageScaleChange(SimpleState *state, bool isUndo);
	void restoreImageOffsetChange(SimpleState *state, bool isUndo);
	void restoreClearImage(UndoState *state, bool isUndo);
	void restoreGetImage(UndoState *state, bool isUndo);
	void restorePoly(SimpleState *state, bool isUndo, bool isContour);
	void restoreUniteItem(SimpleState *state, bool isUndo);
	void restoreSplitItem(SimpleState *state, bool isUndo);
	void restoreContourLine(SimpleState *state, bool isUndo);
	void restoreShapeType(SimpleState *state, bool isUndo);
	void restoreLayer(SimpleState *state, bool isUndo);

	void restoreShapeContour(UndoState *state, bool isUndo);
	void restoreImageEffects(UndoState *state, bool isUndo);
	void restoreLinkTextFrame(UndoState *state, bool isUndo);
	void restoreUnlinkTextFrame(UndoState *state, bool isUndo);
	void restoreReverseText(UndoState *state, bool isUndo);
	void restorePathOperation(UndoState *state, bool isUndo);
	/*@}*/

	/**
	 * @brief Returns true if the actions should be sent to the UndoManager.
	 *
	 * Checks the state of the arrow keys and mouse buttons. If a key or a
	 * mouse button is down PageItem is under some action which should only be
	 * stored after the action has been finished (to get a single undo action).
	 * @return true if the actions should be sent to the UndoManager based on the
	 * state of arrow keys and mouse buttons else returns false.
	 */
	bool shouldCheck();
	/** @brief Clears the current selection and selects this PageItem. */
	void select();

	// Protected members

	/**
	 * @brief Frame Type, eg line, text frame, etc.
	 *
	 * This will probably go away when pageitem is split into
	 * subclasses.
	 */
	ItemType m_ItemType;

	/**
	 * @brief Item name. Unicode. User visible (outline, property palette, etc).
	 * @todo This is Annotation Name.. not item name, needs splitting up.
	 * @sa PageItem::itemName(), PageItem::setItemName()
	 */
	QString AnName; 

	/**
	 * @brief Fill gradient name
	 * @sa PageItem::gradient(), PageItem::setGradient()
	 */
	QString gradientVal;

	/**
	 * @brief Fill pattern name
	 * @sa PageItem::pattern(), PageItem::setPattern()
	 */
	QString patternVal;
	/**
	 * @brief Fill pattern transformation matrix
	 */
	double patternScaleX;
	double patternScaleY;
	double patternOffsetX;
	double patternOffsetY;
	double patternRotation;
	double patternSkewX;
	double patternSkewY;
	bool patternMirrorX;
	bool patternMirrorY;

	/**
	 * @brief Fill color name
	 * @sa PageItem::fillColor(), PageItem::setFillColor()
	 */
	QString fillColorVal;

	/**
	 * @brief Line color name
	 * @sa PageItem::lineColor(), PageItem::setLineColor()
	 */
	QString lineColorVal;

	/**
	 * @brief Line shade
	 * @sa PageItem::lineShade, PageItem::setLineShade()
	 */
	double lineShadeVal;

	/**
	 * @brief Fill shade
	 * @sa PageItem::fillShade, PageItem::setFillShade()
	 */
	double fillShadeVal;

	/**
	 * @brief Fill transparency
	 * @sa PageItem::fillTransparency(), PageItem::setFillTransparency()
	 */
	double fillTransparencyVal;

	/**
	 * @brief Line stroke transparency.
	 * @sa PageItem::lineTransparency(), PageItem::setLineTransparency()
	 */
	double lineTransparencyVal;

	/**
	 * @brief Fill transparency blendmode
	 * @sa PageItem::fillBlendmode(), PageItem::setFillBlendmode()
	 */
	int fillBlendmodeVal;

	/**
	 * @brief Line stroke transparency blendmode.
	 * @sa PageItem::lineBlendmode(), PageItem::setLineBlendmode()
	 */
	int lineBlendmodeVal;

	/**
	 * @brief Is the image in this image item flipped horizontally?
	 * @sa PageItem::isImageFlippedH(), PageItem::setImageFlippedH(),
	 *     PageItem::flipImageH(), PageItem::flippedV
	 */
	bool m_ImageIsFlippedH;

	/**
	 * @brief Is the image in this image item flipped vertically?
	 * @sa PageItem::isImageFlippedV(), PageItem::setImageFlippedV(),
	 *     PageItem::flipImageV(), PageItem::flippedH
	 */
	bool m_ImageIsFlippedV;

	/**
	 * @brief Is the item locked (cannot be moved, resized, etc)?
	 * @sa PageItem::locked(), PageItem::setLocked(), PageItem::toggleLock()
	 */
	bool m_Locked;

	/**
	 * @brief Is the item's size locked?
	 * @sa PageItem::sizeLocked(), PageItem::setSizeLocked(), PageItem::toggleSizeLock()
	 */
	bool m_SizeLocked;

	/**
	 * @for notes frames - locking horizontal or vertical size
	**/
	bool m_SizeHLocked;
	bool m_SizeVLocked;
	/**
	 * @brief Should text flow around the item
	 * @sa PageItem::textFlowMode(), PateItem::setTextFlowMode()
	 */
	TextFlowMode textFlowModeVal;

	/**
	 * @brief Stores the attributes of the pageitem (NOT properties, the user defined ATTRIBUTES)
	 * @sa
	 */
	ObjAttrVector pageItemAttributes;

	/**
	 * @brief Is this item set to be printed/exported
	 * @sa PageItem::printable(), PageItem::setPrintable()
	 */
	bool m_PrintEnabled;
	
	/**
	 * @brief Is this item set to have an action done to it, eg deleted
	 * @sa PageItem::isTagged(), PageItem::setTagged()
	 */
	bool tagged;

	bool no_fill;
	bool no_stroke;
	
	QColor fillQColor;
	QColor strokeQColor;
	QColor GrColorP1QColor;
	QColor GrColorP2QColor;
	QColor GrColorP3QColor;
	QColor GrColorP4QColor;
	
	/** X position on the page */
	double Xpos;
	/** Y position on the page */
	double Ypos;
	/** Width of the item */
	double Width;
	/** Height of the item */
	double Height;
	/** Rotation of the item */
	double Rot;
	/** Element selected? */
	bool Select;
	/** Scaling X Factor for images */
	double LocalScX;
	/** Scaling Y Factor for images*/
	double LocalScY;
	/** Image X Offset to frame */
	double LocalX;
	/** Image Y Offset to frame */
	double LocalY;
	/** Image rotation in frame */
	double LocalRot;
	/** If the frame is reversed */
	bool Reverse;

	int m_startArrowIndex;
	int m_endArrowIndex;
	int m_startArrowScale;
	int m_endArrowScale;

protected:
  	/** Left, Top, Bottom, Right distances of text from the frame */
	double Extra;
	double TExtra;
	double BExtra;
	double RExtra;
	
	FirstLineOffsetPolicy firstLineOffsetP;
	
public:
	/** Radius of rounded corners */
	double RadRect;
	
	//Undo Data
	/** @brief Stores the old X-position for undo action. Is used to detect move actions.*/
	double oldXpos;
	/** @brief Stores the old Y-position for undo action. Is used to detect move actions. */
	double oldYpos;
	/** @brief Stores the old width for undo action. Is used to detect resize actions. */
	double oldWidth;
	/** @brief Stores the old height for undo action. Is used to detect resize actions. */
	double oldHeight;
	/** @brief Stores the old rotation value for undo action. Is used to detect rotation actions. */
	double oldRot;
	/** @brief Stores the old LocalScX value for undo action. Is used to detect image scale actions. */
	double oldLocalScX;
	/** @brief Stores the old LocalScY value for undo action. Is used to detect image scale actions. */
	double oldLocalScY;
	/** @brief Stores the old LocalX value for undo action. Is used to detect image offset actions. */
	double oldLocalX;
	/** @brief Stores the old LocalY value for undo action. Is used to detect image offset actions. */
	double oldLocalY;
	
	/** Document this item belongs to */
	ScribusDoc *m_Doc;
	
	/** Flags and data for PDF Annotations */
	bool m_isAnnotation;
	Annotation m_annotation;
	
	/** Darstellungsart Bild/Titel */
	bool PicArt;
	
	 /** Line width */
	double m_lineWidth;
	double Oldm_lineWidth;

	/**
	 * @brief Stroke pattern name
	 * @sa PageItem::strokePattern(), PageItem::setStrokePattern()
	 */
	QString patternStrokeVal;
	/**
	 * @brief Stroke pattern transformation matrix
	 */
	double patternStrokeScaleX;
	double patternStrokeScaleY;
	double patternStrokeOffsetX;
	double patternStrokeOffsetY;
	double patternStrokeRotation;
	double patternStrokeSkewX;
	double patternStrokeSkewY;
	double patternStrokeSpace;
	bool patternStrokeMirrorX;
	bool patternStrokeMirrorY;
	bool patternStrokePath;
	

	/**
	 * @brief Stroke gradient name
	 * @sa PageItem::strokeGradient(), PageItem::setStrokeGradient()
	 */
	QString gradientStrokeVal;
	VGradient stroke_gradient;

	/** 
	* @brief Stroke gradient variables
	*/
	int GrTypeStroke;
	double GrStrokeStartX;
	double GrStrokeStartY;
	double GrStrokeEndX;
	double GrStrokeEndY;
	double GrStrokeFocalX;
	double GrStrokeFocalY;
	double GrStrokeScale;
	double GrStrokeSkew;

	/** 
	* @brief Mask gradient variables
	*/
	int GrMask;
	double GrMaskStartX;
	double GrMaskStartY;
	double GrMaskEndX;
	double GrMaskEndY;
	double GrMaskFocalX;
	double GrMaskFocalY;
	double GrMaskScale;
	double GrMaskSkew;
	double patternMaskScaleX;
	double patternMaskScaleY;
	double patternMaskOffsetX;
	double patternMaskOffsetY;
	double patternMaskRotation;
	double patternMaskSkewX;
	double patternMaskSkewY;
	bool patternMaskMirrorX;
	bool patternMaskMirrorY;
	QString patternMaskVal;
	QString gradientMaskVal;
	VGradient mask_gradient;
	
	/** Inline Image */
	bool isInlineImage;
	QTemporaryFile *tempImageFile;
	
signals:
	//Frame signals
	void myself(PageItem *);
	void frameType(int);   // not related to Frametype but to m_itemIype :-/
	//void frameLocked(bool); //Frame lock
	//void frameSizeLocked(bool); //Frame size lock
	//Shape signals
	//void cornerRadius(double); //Corner radius of the shape
	//Frame text signals
	//void lineSpacing(double);
	//void textKerning(double);
	void textStyle(int);
	//void textFont(const QString&);
	//void textSize(double);
	//void textToFrameDistances(double, double, double, double); //left, top, bottom, right: Extra, TExtra, BExtra, RExtra
	//FIXME: columns, grid ?
	
public:
	//items welding (item follows while item moves which they are connected with)
	struct weldingInfo
	{
		PageItem *weldItem;
		FPoint weldPoint;
		int weldID;
	};
	QList<weldingInfo> weldList;
	bool isWelded()  {return !weldList.isEmpty(); }  //true if to this item some other items are welded (weldList is list of these items)
	void weldTo(PageItem* pIt);
	QList<PageItem*> itemsWeldedTo(PageItem* except = NULL);
	void unWeld();
	void addWelded(PageItem* iPt);
	void moveWelded(double DX, double DY, int weld);
	void moveWelded(double DX, double DY, PageItem* except = NULL);
	void rotateWelded(double dR, double oldRot);
	//added for autowelding feature of notes frames
	//setting welding point with given pItem to given coords
	void setWeldPoint(double DX, double DY, PageItem *pItem);
	//used by notes frames to get content of notes from itemText
	QString getItemTextSaxed(int selStart, int selLength);
};

Q_DECLARE_METATYPE(PageItem*)

#endif
