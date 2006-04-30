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

#include <qobject.h>
#include <qwidget.h>
#include <qpointarray.h>
#include <qptrlist.h>
#include <qpixmap.h>
#include <qvaluestack.h>
#include <qvaluelist.h>

#include "scribusapi.h"
#include "annotation.h"
#include "pagestructs.h"
#include "scimage.h"
#include "sctextstruct.h"
#include "undoobject.h"
#include "vgradient.h"
#include "text/nlsconfig.h"
#include "text/storytext.h"

class ScPainter;
class ScribusDoc;
class UndoManager;
class UndoState;
class Foi;

class PageItem_ImageFrame;
class PageItem_Line;
class PageItem_Polygon;
class PageItem_PolyLine;
class PageItem_TextFrame;
class PageItem_PathText;

struct CopyPasteBuffer;
/**
  *@author Franz Schmid
  */

class SCRIBUS_API PageItem : public QObject, public UndoObject
{
	Q_OBJECT

	// Properties - see http://doc.trolltech.com/3.3/properties.html
	// See the accessors of these properties for details on their use.
	Q_PROPERTY(QString itemName READ itemName WRITE setItemName DESIGNABLE false)
	Q_PROPERTY(QString fillColor READ fillColor WRITE setFillColor DESIGNABLE false)
	Q_PROPERTY(QString lineColor READ lineColor WRITE setLineColor DESIGNABLE false)
	Q_PROPERTY(int fillShade READ fillShade WRITE setFillShade DESIGNABLE false)
	Q_PROPERTY(int lineShade READ lineShade WRITE setLineShade DESIGNABLE false)
	Q_PROPERTY(double fillTransparency READ fillTransparency WRITE setFillTransparency DESIGNABLE false)
	Q_PROPERTY(double lineTransparency READ lineTransparency WRITE setLineTransparency DESIGNABLE false)
	Q_PROPERTY(bool m_Locked READ locked WRITE setLocked DESIGNABLE false)
	Q_PROPERTY(bool m_SizeLocked READ sizeLocked WRITE setSizeLocked DESIGNABLE false)
	Q_PROPERTY(bool m_ImageIsFlippedV READ imageFlippedV WRITE setImageFlippedV DESIGNABLE false)
	Q_PROPERTY(bool m_ImageIsFlippedH READ imageFlippedH WRITE setImageFlippedH DESIGNABLE false)
	Q_PROPERTY(double lineWidth READ lineWidth WRITE setLineWidth DESIGNABLE false)
	Q_PROPERTY(QString customLineStyle READ customLineStyle WRITE setCustomLineStyle DESIGNABLE false)
	Q_PROPERTY(int startArrowIndex READ startArrowIndex WRITE setStartArrowIndex DESIGNABLE false)
	Q_PROPERTY(int endArrowIndex READ endArrowIndex WRITE setEndArrowIndex DESIGNABLE false)
	Q_PROPERTY(QString font READ font WRITE setFont DESIGNABLE false)
	Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize DESIGNABLE false)
	Q_PROPERTY(int fontWidth READ fontWidth WRITE setFontWidth DESIGNABLE false)
	Q_PROPERTY(QString fontFillColor READ fontFillColor WRITE setFontFillColor DESIGNABLE false)
	Q_PROPERTY(int fontFillShade READ fontFillShade WRITE setFontFillShade DESIGNABLE false)
	Q_PROPERTY(QString fontStrokeColor READ fontStrokeColor WRITE setFontStrokeColor DESIGNABLE false)
	Q_PROPERTY(int fontStrokeShade READ fontStrokeShade WRITE setFontStrokeShade DESIGNABLE false)
	Q_PROPERTY(int fontEffects READ fontEffects WRITE setFontEffects DESIGNABLE false)
	Q_PROPERTY(int kerning READ kerning WRITE setKerning  DESIGNABLE false)
	Q_PROPERTY(double lineSpacing READ lineSpacing WRITE setLineSpacing DESIGNABLE false)
	Q_PROPERTY(QString language READ language WRITE setLanguage DESIGNABLE false)
	Q_PROPERTY(bool textFlowsAroundFrame READ textFlowsAroundFrame WRITE setTextFlowsAroundFrame DESIGNABLE false)
	Q_PROPERTY(bool textFlowUsesBoundingBox READ textFlowUsesBoundingBox WRITE setTextFlowUsesBoundingBox DESIGNABLE false)
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

	// FIXME: QMetaProperty can't translate these to/from enumerator names, probably because the
	// properties aren't moc'd in the Qt sources. They work fine in their
	// current state as plain integer properties.
	Q_ENUMS(PenStyle)
	Q_PROPERTY(PenStyle lineStyle READ lineStyle WRITE setLineStyle DESIGNABLE false)
	Q_ENUMS(PenCapStyle)
	Q_PROPERTY(PenCapStyle lineEnd READ lineEnd WRITE setLineEnd DESIGNABLE false)
	Q_ENUMS(PenJoinStyle)
	Q_PROPERTY(PenJoinStyle lineJoin READ lineJoin WRITE setLineJoin DESIGNABLE false)

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
	 */
	enum ItemType {
		ItemType1	= 1,
		ImageFrame	= 2,
		ItemType3	= 3,
		TextFrame	= 4,
		Line		= 5,
		Polygon		= 6,
		PolyLine	= 7,
		PathText	= 8
	};

	/* these do essentially the same as a dynamic cast but might be more readable */
	virtual PageItem_ImageFrame * asImageFrame() { return NULL; }
	virtual PageItem_Line * asLine() { return NULL; }
	virtual PageItem_PathText * asPathText() { return NULL; }
	virtual PageItem_Polygon * asPolygon() { return NULL; }
	virtual PageItem_PolyLine * asPolyLine() { return NULL; }
	virtual PageItem_TextFrame * asTextFrame() { return NULL; }


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
	~PageItem() {};
	struct ZZ {
				double xco;
				double yco;
				double wide;
				double kern;
				int Siz;
				int realSiz;
				int Style;
				int scale;
				int scalev;
				int shade;
				int shade2;
				int shadowX;
				int shadowY;
				int outline;
				int base;
				int underpos;
				int underwidth;
				int strikepos;
				int strikewidth;
				bool Sele;
				QString Zeich;
				QString Farb;
				QString Farb2;
				Foi* ZFo;
				PageItem* embedded;
			};
	/**
	 * @brief Clear the contents of a frame.
	 * WARNING: Currently *they* do not check if the user wants this.
	 * The view does when these are called.
	 */	
	virtual void clearContents() {};
	
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
	 * brief Returns a complete ObjectAttribute struct if 1 is found, or ObjectAttribute.name will be QString::null if 0 or >1 are found
	 */
	ObjectAttribute getObjectAttribute(QString);
	void setObjectAttributes(ObjAttrVector*);
  /** Zeichnet das Item */
	void paintObj(QRect e=QRect(), QPixmap *ppX = 0);
	void DrawObj(ScPainter *p, QRect e);
	void DrawObj_Pre(ScPainter *p, double &sc);
	virtual void DrawObj_Post(ScPainter *p);
	virtual void DrawObj_Item(ScPainter *p, QRect e, double sc) = 0;
protected:
	void DrawObj_ImageFrame(ScPainter *p, double sc);
	//void DrawObj_TextFrame(ScPainter *p, QRect e, double sc);
	//void DrawObj_Line(ScPainter *p);
	void DrawObj_Polygon(ScPainter *p);
	void DrawObj_PolyLine(ScPainter *p);
	void DrawObj_PathText(ScPainter *p, double sc);
public:
	void DrawObj_Embedded(ScPainter *p, QRect e, struct ZZ *hl);
	void SetFrameShape(int count, double *vals);
	void SetRectFrame();
	void SetOvalFrame();
	void SetFrameRound();
	void setPolyClip(int up);
	void updatePolyClip();
	void updateClip();
	void convertClip();
	//QRect getRedrawBounding(const double);
	//void setRedrawBounding();
	void getBoundingRect(double *x1, double *y1, double *x2, double *y2);
	/**
	 * @brief Check if a QPoint is within the items boundaries
	 * No coordinates transformation is performed
	 * @param x X position
		@param y Y position
	 * @return bool true if x, i in the item
	 */
	bool pointWithinItem(const int x, const int y);
	/**
	 * @brief Check if the mouse is within the items boundaries
	 * This method performs necessary page to device transformations
	 * @param vport a view port
		@param x X position
		@param y Y position
		@param scale scale of the vport
	 * @return bool true if the x, y is in the bounds 
	 */
	bool mouseWithinItem(QWidget* vport, const int x, const int y, double scale);
	void copyToCopyPasteBuffer(struct CopyPasteBuffer *Buffer);
	
	virtual void handleModeEditKey(QKeyEvent *k, bool &keyRepeat);
	
	
	double SetZeichAttr(const CharStyle& hl, int *chs, QString *chx);
	void SetFarbe(QColor *tmp, QString farbe, int shad);
	void DrawZeichenS(ScPainter *p, struct ZZ *hl);
	void DrawPolyL(QPainter *p, QPointArray pts);
	QString ExpandToken(uint base);
	
	bool AutoName;	
	double gXpos;
	double gYpos;
	double gWidth;
	double gHeight;
	int GrType;
	double GrStartX;
	double GrStartY;
	double GrEndX;
	double GrEndY;
	QString TxtStroke;
	QString TxtFill;
	int ShTxtStroke;
	int ShTxtFill;
	int TxtScale;
	int TxtScaleV;
	int TxTStyle;
	int TxtBase;
	int TxtShadowX;
	int TxtShadowY;
	int TxtOutline;
	int TxtUnderPos;
	int TxtUnderWidth;
	int TxtStrikePos;
	int TxtStrikeWidth;
	int Cols;
	double ColGap;
  /** Linienart */
	PenStyle PLineArt;
	PenCapStyle PLineEnd;
	PenJoinStyle PLineJoin;
	QString NamedLStyle;
  /** Definiert die Clipping-Region des Elements; */
	QPointArray Clip;
	FPointArray PoLine;
	FPointArray ContourLine;
	FPointArray imageClip;
	QValueList<uint> Segments;
	QValueList<ScImage::imageEffect> effectsInUse;
	bool PoShow;
	double BaseOffs;
	bool ClipEdited;
	// Don't know exactly what this is, but it's not the same as itemType
	int FrameType;
  /** Interne Item-Nummer */
	uint ItemNr;
  /** Hat Element Rahmen? */
	bool Frame;
  /** Seite zu der das Element gehoert */
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
	QString IProfile;
	bool UseEmbedded;
	QString EmProfile;
	int IRender;
  /** Bild verfuegbar */
	bool PicAvail;
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
  /** Cursorposition */
	int CPos;
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
  /** Flag fuer Textfluss */
	bool FrameOnly;
	PageItem *BackBox;
	PageItem *NextBox;
	int NextIt;
	int NextPg;
	bool Tinput;
	bool isAutoText;
	int textAlignment;
#ifndef NLS_PROTO
	uint MaxChars;
#endif
	bool inPdfArticle;
	int ExtraV;
	bool isRaster;
	double OldB;
	double OldH;
	double OldB2;
	double OldH2;
	bool Sizing;
	bool toPixmap;
	int LayerNr;
	bool ScaleType;
	bool AspectRatio;
	QValueStack<int> Groups;
	QValueList<double> DashValues;
	QValueList<ParagraphStyle::TabRecord> TabValues;
	double DashOffset;
	VGradient fill_gradient;
	bool fillRule;
	bool doOverprint;
	QString Language;
/* Additions for Table Support */
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
	bool isSingleSel;
	double BoundingX;
	double BoundingY;
	double BoundingW;
	double BoundingH;
	bool ChangedMasterItem;
	QString OnMasterPage;
	bool isEmbedded;
	
	//Position
	double xPos() const { return Xpos; }
	double yPos() const { return Ypos; }
	FPoint xyPos() const { return FPoint(Xpos, Ypos); }
	void setXPos(const double, bool drawingOnly=false);
	void setYPos(const double, bool drawingOnly=false);
	void setXYPos(const double, const double, bool drawingOnly=false);
	void moveBy(const double, const double, bool drawingOnly=false);
	//Size
	double width() const { return Width; }
	double height() const { return Height; }
	void setWidth(const double);
	void setHeight(const double);
	void setWidthHeight(const double, const double);
	void resizeBy(const double, const double);
	//Rotation
	double rotation() const { return Rot; }
	void setRotation(const double, bool drawingOnly=false);
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
	//Reverse
	bool reversed() const { return Reverse; }
	void setReversed(bool);
	//Rounded Corners
	double cornerRadius() const { return RadRect; }
	void setCornerRadius(double);


	//Text Data - Move to PageItem_TextFrame at some point?
	double textToFrameDistLeft() const { return Extra; }
	double textToFrameDistRight() const { return RExtra; }
	double textToFrameDistTop() const { return TExtra; }
	double textToFrameDistBottom() const { return BExtra; }
	void setTextToFrameDistLeft(double);
	void setTextToFrameDistRight(double);
	void setTextToFrameDistTop(double);
	void setTextToFrameDistBottom(double);
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

	/** @brief Get the (name of the) fill color of the object */
	QString fillColor() const { return fillColorVal; }
	/**
	 * @brief Set the fill color of the object.
	 * @param newColor fill color for the object
	 */
	void setFillColor(const QString &newColor);

	/** @brief Get the shade of the fill color */
	int fillShade() const { return fillShadeVal; }
	/**
	 * @brief Set the fill color shade.
	 * @param newShade shade for the fill color
	 */
	void setFillShade(int newShade);

	/** @brief Get the transparency of the fill color */
	double fillTransparency() const { return fillTransparencyVal; }
	/**
	 * @brief Set the transparency of the fill color.
	 * @param newTransparency transparency of the fill color
	 */
	void setFillTransparency(double newTransparency);

	/** @brief Get the line color of the object */
	QString lineColor() const { return lineColorVal; }
	/**
	 * @brief Set the line color of the object.
	 * @param newColor line color for the object
	 */
	void setLineColor(const QString &newColor);

	/** @brief Get the line color shade */
	int lineShade() const { return lineShadeVal; }
	/**
	 * @brief Set the line color shade.
	 * @param newShade shade for the line color
	 */
	void setLineShade(int newShade);

	/** @brief Get the line transparency */
	double lineTransparency() const { return lineTransparencyVal; }
	/**
	 * @brief Set the transparency of the line color.
	 * @param newTransparency transparency of the line color
	 */
	void setLineTransparency(double newTransparency);

	/** @brief Set the QColor for the line */
	void setLineQColor();
	/** @brief Set the QColor for the fill */
	void setFillQColor();

	/** @brief Get the style of line */
	PenStyle lineStyle() const { return PLineArt; }
	/**
	 * @brief Set the style of line.
	 * @param newStyle style of line
	 * @sa Qt::PenStyle
	 */
	void setLineStyle(PenStyle newStyle);

	/** @brief Get the width of the line */
	double lineWidth() const { return m_lineWidth; }
	/**
	 * @brief Set the width of line
	 * @param newWidth width of line
	 */
	void setLineWidth(double newWidth);

	/** @brief Get the end cap style of the line */
	PenCapStyle lineEnd() const { return PLineEnd; }
	/**
	 * @brief Set the end style of line
	 * @param newStyle end style of line
	 * @sa Qt::PenCapStyle
	 */
	void setLineEnd(PenCapStyle newStyle);

	/** @brief Get the join style of multi-segment lines */
	PenJoinStyle lineJoin() const { return PLineJoin; }
	/**
	 * @brief Set the join style of line
	 * @param newStyle join style of line
	 * @sa Qt::PenJoinStyle
	 */
	void setLineJoin(PenJoinStyle newStyle);

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
	/** @brief set lock for resizing */
	void setSizeLocked(bool isLocked);

	/** @brief Get the PageItem-wide font name */
	QString font() const { return m_Font; }
	/**
	 * @brief Set font for the PageItem.
	 * @param newFont name of the font
	 */
	void setFont(const QString& newFont);

	/** @brief Get the PageItem-wide font size */
	int fontSize() const { return m_FontSize; }
	/**
	 * @brief Set the font size of the frame
	 * @param newSize font size
	 */
	void setFontSize(int newSize);

	/** @brief Get the PageItem-wide character height scaling percentage */
	int fontHeight() const { return TxtScaleV; }
	/**
	 * @brief Set scaling height of character
	 * @param newHeight height of character
	 */
	void setFontHeight(int newHeight);

	/** @brief Get the PageItem-wide character width scaling percentage */
	int fontWidth() const { return TxtScale; }
	/**
	 * @brief Set scaling width of character
	 * @param newWidth width of character
	 */
	void setFontWidth(int newWidth);

	/** @brief Get the name of the PageItem-wide font fill color */
	QString fontFillColor() const { return TxtFill; }
	/**
	 * @brief Set font fill color
	 * @param newColor font fill color
	 */
	void setFontFillColor(const QString& newColor);

	/** @brief Get the PageItem-wide font fill shade */
	int fontFillShade() const { return ShTxtFill; }
	/**
	 * @brief Set the shade of font fill color
	 * @param newShade shade of font fill color
	 */
	void setFontFillShade(int newShade);

	/** @brief Get the PageItem-wide font stroke color */
	QString fontStrokeColor() const { return TxtStroke; }
	/**
	 * @brief Set the color of font stroke
	 * @param newColor color of font stroke
	 */
	void setFontStrokeColor(const QString& newColor);

	/** @brief Get the PageItem-wide font stroke shade */
	int fontStrokeShade() const { return ShTxtStroke; }
	/**
	 * @brief Set the shade of font stroke color
	 * @param newShade shade of font stroke color
	 */
	void setFontStrokeShade(int newShade);

	/** @brief Get the PageItem-wide font effects flags
	 *
	 * TODO This should probably be an enum set
	 */
	int fontEffects() const { return TxTStyle; }
	/**
	 * @brief Set font effects
	 * @param newEffects font effects
	 */
	void setFontEffects(int newEffects);

	/** @brief Get PageItem-wide text kerning */
	int kerning() const { return ExtraV; }
	/**
	 * @brief Set kerning for the text
	 * @param newKerning kerning for the text
	 */
	void setKerning(int newKerning);

	/** @brief Get the PageItem-wide line spacing */
	double lineSpacing() const { return LineSp; }
	/**
	 * @brief Set a line spacing for the frame
	 * @param newSpacing line spacing for the frame
	 */
	void setLineSpacing(double newSpacing);

	/** @brief Get the PageItem-wide line spacing mode */
	int lineSpacingMode() const { return LineSpMode; }
	/**
	 * @brief Set a line spacing for the frame
	 * @param newLineSpacingMode line spacing for the frame
	 */
	void setLineSpacingMode(int newLineSpacingMode);
	
	/** @brief Get the hyphenation language for the frame */
	QString language() const { return Language; }
	/**
	 * @brief Set the hyphenation language for the frame
	 * @param newLanguage hyphenation language for the frame
	 */
	void setLanguage(const QString& newLanguage);

	/**
	 * @brief Does text flow around this object
	 * @sa setTextFlowsAroundFrame()
	 */
	bool textFlowsAroundFrame() const { return textFlowsAroundFrameVal; }
	/**
	 * @brief Enable/disable text flowing around this item
	 * @param isFlowing true if text is wanted to flow around this object or false if not
	 * @sa textFlowsAroundFrame()
	 */
	void setTextFlowsAroundFrame(bool isFlowing);

	/**
	 * @brief Should text flow around the object's bounding box if text flow is enabled?
	 * @sa PageItem::setTextFlowUsesBoundingBox()
	 */
	bool textFlowUsesBoundingBox() const { return textFlowUsesBoundingBoxVal; }
	/**
	 * @brief Tells if the text flow should follow the square frame border if <code>useBounding</code>
	 * @brief is true, if it is set false text fill flow around the object border rather than frame.
	 *
	 * Setting this to true will unset contour line to false. Bounding box and contour line cannot
	 * be used at the same time.
	 * @param useBounding true if text should flow around the frame border false if it should follow
	 * the actual shape of the object.
	 * @sa setTextFlowsAroundFrame()
	 * @sa setTextFlowUsesContourLine()
	 * @sa textFlowUsesBoundingBox()
	 */
	void setTextFlowUsesBoundingBox(bool useBounding);

	/**
	 * @brief Should text flow around the contour line of the frame?
	 * @sa setTextFlowUsesContourLine()
	 */
	bool textFlowUsesContourLine() const { return textFlowUsesContourLineVal; }
	/**
	 * @brief Tells if the text flow should follow the contour line of the frame.
	 *
	 * Setting this to true will unset bounding box to false. Contour line and bounding box cannot
	 * be used at the same time.
	 * @param useContour true if text should flow around the contour line of the frame false if
	 * it should flow around the actual shap of the object.
	 * @sa setTextFlowsAroundFrame()
	 * @sa setTextFlowUsesBoundingBox()
	 * @sa textFlowUsesContourLine()
	 */
	void setTextFlowUsesContourLine(bool useContour);

	/** @brief Get the frame type
	 *
	 * @attention The whole concept of frame types is due for some radical
	 *            re-working, so don't rely on this interface staying stable.
	 *            It's here as an interim step to eliminate direct member access
	 *            on PageItems.
	 */
	ItemType itemType() const { return m_ItemType; }
	/**
	 * @brief Convert this PageItem to PageItem type <code>newType</code>
	 * @param newType PageItem type for conversion
	 */
	void convertTo(ItemType newType);

	/**
	* Set the layer for the item
	* @param layerId layer where this item is moved
	*/
	void setLayer(int layerId);

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

	/**
	 * @brief Return a variant of `originalName' that is guaranteed to be unique
	 *        in the same document as this PageItem.  If the passed name is not
	 *        in use it is returned unchanged.
	 * @author Craig Ringer
	 *
	 * Usually of the form 'Copy of [name]' or 'Copy of [name] (n)'
	 */
	QString generateUniqueCopyName(const QString originalName) const;
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
	bool loadImage(const QString& filename, const bool reload, const int gsResolution=-1);
	
	
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
	ScribusDoc* document();
	
	bool isAnnotation() const { return m_isAnnotation; }
	void setIsAnnotation(bool);
	void setAnnotation(const Annotation& ad);
	Annotation& annotation() { return m_annotation; }
	
	bool imageShown() const { return PicArt; }
	void setImageShown(bool);
	
	void updateConstants();
	
protected:

	void drawLockedMarker(ScPainter *p);
	
	/** @brief Manages undostack and is where all undo actions/states are sent. */
	UndoManager * const undoManager;
	/**
	 * @name Restore helper methods
	 * Split the restore method for easier handling.
	 * @author Riku Leino
	 */
	/*@{*/
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
	void restoreFont(SimpleState *state, bool isUndo);
	void restoreFontSize(SimpleState *state, bool isUndo);
	void restoreFontWidth(SimpleState *state, bool isUndo);
	void restoreFontFill(SimpleState *state, bool isUndo);
	void restoreFontStroke(SimpleState *state, bool isUndo);
	void restoreFontFillShade(SimpleState *state, bool isUndo);
	void restoreFontStrokeShade(SimpleState *state, bool isUndo);
	void restoreKerning(SimpleState *state, bool isUndo);
	void restoreLineSpacing(SimpleState *state, bool isUndo);
	void restoreLanguage(SimpleState *state, bool isUndo);
	void restorePStyle(SimpleState *state, bool isUndo);
	void restoreFontEffect(SimpleState *state, bool isUndo);
	void restoreType(SimpleState *state, bool isUndo);
	void restoreTextFlowing(SimpleState *state, bool isUndo);
	void restoreImageScaleType(SimpleState *state, bool isUndo);
	void restoreImageScaleChange(SimpleState *state, bool isUndo);
	void restoreImageOffsetChange(SimpleState *state, bool isUndo);
	void restorePoly(SimpleState *state, bool isUndo, bool isContour);
	void restoreContourLine(SimpleState *state, bool isUndo);
	void restoreLayer(SimpleState *state, bool isUndo);
	void restoreGetImage(SimpleState *state, bool isUndo);
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
	int lineShadeVal;

	/**
	 * @brief Fill shade
	 * @sa PageItem::fillShade, PageItem::setFillShade()
	 */
	int fillShadeVal;

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
	 * @brief Should text flow around the item
	 * @sa PageItem::textFlowsAroundFrame(), PateItem::setTextFlowsAroundFrame()
	 */
	bool textFlowsAroundFrameVal;

	/**
	 * @brief Should text flow around the item's bounding box?
	 * @sa PageItem::textFlowUsesBoundingBox(), PageItem::setTextFlowUsesBoundingBox()
	 */
	bool textFlowUsesBoundingBoxVal;

	/**
	 * @brief Should text flow around the item's contour line?
	 * @sa PageItem::textFlowUsesContourLine(), PageItem::setTextFlowUsesContourLine()
	 */
	bool textFlowUsesContourLineVal;

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
	
	QColor fillQColor;
	QColor strokeQColor;
	
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
	/** If the frame is reversed */
	bool Reverse;

	int m_startArrowIndex;
	int m_endArrowIndex;
	
  	/** Left, Top, Bottom, Right distances of text from the frame */
	double Extra;
	double TExtra;
	double BExtra;
	double RExtra;
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
	
	/** Item Font */
	QString m_Font;
	/** Item Fontsize */
	int m_FontSize;

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

/** Linespacing */
	double LineSp;
	int LineSpMode;
	
signals:
	//Frame signals
	void myself(PageItem *);
	void frameType(int);
	void position(double, double); //X,Y
	void widthAndHeight(double, double); //W,H
	void rotation(double); //Degrees rotation	
	void colors(QString, QString, int, int); //lineColor, fillColor, lineShade, fillShade
	void gradientType(int); //Normal, horizontal, vertical, etc.
	void gradientColorUpdate(double, double, double, double, double, double); //Cpal updatespecialgradient
	void transparency(double, double); //fillTransparency, lineTransparency
	void frameLocked(bool); //Frame lock
	void frameSizeLocked(bool); //Frame size lock
	void frameFlippedH(bool); //Frame flipped horizontally
	void frameFlippedV(bool); //Frame flipped vertically
	void printEnabled(bool); //Frame is set to print or not
	//Shape signals
	void columns(int, double); //Number, gap
	void cornerRadius(double); //Corner radius of the shape
	//Line signals
	void lineWidth(double);
	void lineStyleCapJoin(Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle);
	//Frame text signals
	void lineSpacing(double);
	void textToFrameDistances(double, double, double, double); //left, top, bottom, right: Extra, TExtra, BExtra, RExtra
	void textKerning(int); //ExtraV
	void textStyle(int); //Style setting
	void textFont(QString); //Text font
	void textSize(int); //Text size
	void textWidthScale(int); //Scaling width of text, ChScale in mpalette
	void textHeightScale(int); //Scaling height of text, ChScaleV in mpalette
	void textBaseLineOffset(int); //Offset from baseline to text
	void textOutline(int); //Outline
	void textShadow(int, int); //Shadow
	void textUnderline(int, int); //Underline
	void textStrike(int, int); //Strikethrough
	void textColor(QString, QString, int, int); //itemText.at(i)-> cstroke, ccolor, cshade2, cshade
	void textFormatting(int); //Underline, subscript, etc
	//Frame image signals
	void imageOffsetScale(double, double, double, double);
};

#endif
