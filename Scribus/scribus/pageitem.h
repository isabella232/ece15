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
#include <qimage.h>
#include <qpixmap.h>
#include <qvaluestack.h>
#include <qvaluelist.h>
#include "scpainter.h"
#include "undoobject.h"
class ScribusDoc;
class UndoManager;
class UndoState;
/**
  *@author Franz Schmid
  */
							
class PageItem : public QObject, public UndoObject
{
	Q_OBJECT
	// Properties - see http://doc.trolltech.com/3.3/properties.html
	// See the getters and setters of these properties for details on their use.
	Q_PROPERTY(QString itemName READ itemName WRITE setItemName DESIGNABLE false)
	Q_PROPERTY(QString fillColor READ fillColor WRITE setFillColor DESIGNABLE false)
	Q_PROPERTY(int fillShade READ fillShade WRITE setFillShade DESIGNABLE false)
	Q_PROPERTY(double fillTransparency READ fillTransparency WRITE setFillTransparency DESIGNABLE false)
	Q_PROPERTY(QString lineColor READ lineColor WRITE setLineColor DESIGNABLE false)
	Q_PROPERTY(int lineShade READ lineShade WRITE setLineShade DESIGNABLE false)
	Q_PROPERTY(double lineTransparency READ lineTransparency WRITE setLineTransparency DESIGNABLE false)
	Q_PROPERTY(bool locked READ locked WRITE setLocked DESIGNABLE false)
	Q_PROPERTY(bool sizeLocked READ sizeLocked WRITE setSizeLocked DESIGNABLE false)
public: 
	PageItem(ScribusDoc *pa, int art, double x, double y, double w, double h, double w2, QString fill, QString outline);
	~PageItem() {};
	struct ZZ { 
				double xco;
				double yco;
				double wide;
				double kern;
				int Siz;
				int Style;
				int scale;
				int shade;
				int shade2;
				bool Sele;
				QString Zeich;
				QString Farb;
				QString Farb2;
				QString ZFo;
			  };
  /** Zeichnet das Item */
	void paintObj(QRect e=QRect(), QPixmap *ppX = 0);
	void DrawObj(ScPainter *p, QRect e);
	double SetZeichAttr(struct ScText *hl, int *chs, QString *chx);
	void SetFarbe(QColor *tmp, QString farbe, int shad);
	void DrawZeichenS(ScPainter *p, struct ZZ *hl);
	void DrawPolyL(QPainter *p, QPointArray pts);
	QString ExpandToken(uint base);
	bool Locked;
	bool LockRes;
	bool Reverse;
  /** X-Position auf der Seite */
	double Xpos;
	/** @brief Stores the old X-position for undo action. Is used to detect move actions.*/
	double oldXpos;
  /** Y-Position auf der Seite */
	double Ypos;
	/** @brief Stores the old Y-position for undo action. Is used to detect move actions. */
	double oldYpos;
  /** Breite des Elements */
	double Width;
	/** @brief Stores the old width for undo action. Is used to detect resize actions. */
	double oldWidth;
  /** Hoehe des Elements */
	double Height;
	/** @brief Stores the old height for undo action. Is used to detect resize actions. */
	double oldHeight;
  /** Eckrundung von Rechtecken */
	double RadRect;
  /** Art des Items */
	int PType;
  /** Winkel um den das Item gedreht wird */
	double Rot;
	/** @brief Stores the old rotation value for undo action. Is used to detect rotation actions. */
	double oldRot;
  /** Enthaelt das Dokument */
	ScribusDoc *Doc;
	int GrType;
	double GrStartX;
	double GrStartY;
	double GrEndX;
	double GrEndY;
  /** Fuellfarbe */
	QString Pcolor;
  /** Abstufung fuer Fllfarbe */
	int Shade;
  /** Zeichenfarbe fuer Elemente */
	QString Pcolor2;
  /** Abstufung fuer Zeichenfarbe */
	int Shade2;
	QString TxtStroke;
	QString TxtFill;
	int ShTxtStroke;
	int ShTxtFill;
	int TxtScale;
	int TxTStyle;
	int Cols;
	double ColGap;
  /** Strichstaerke */
	double Pwidth;
	double OldPwidth;
  /** Linienart */
	PenStyle PLineArt;
	PenCapStyle PLineEnd;
	PenJoinStyle PLineJoin;
	QString NamedLStyle;
  /** Element selektiert Ja/Nein */
	bool Select;
  /** Definiert die Clipping-Region des Elements; */
	QPointArray Clip;
	FPointArray PoLine;
	bool UseContour;
	FPointArray ContourLine;
	QValueList<uint> Segments;
	bool PoShow;
	double BaseOffs;
	bool ClipEdited;
	int FrameType;
  /** Interne Item-Nummer */
	uint ItemNr;
  /** Hat Element Rahmen? */
	bool Frame;
  /** Seite zu der das Element gehoert */
	int OwnPage;
	/** @brief Old page number tracked for the move undo action */
	int oldOwnPage;
  /** Darzustellendes Bild */
	QImage pixm;
	QImage pixmOrg;
  /** Dateiname des Bildes */
	QString Pfile;
	QString Pfile2;
	QString Pfile3;
	QString IProfile;
	bool UseEmbedded;
	QString EmProfile;
	int IRender;
  /** Darstellungsart Bild/Titel */
	bool PicArt;
  /** Bild verfuegbar */
	bool PicAvail;
  /** Lokales Scaling x*/
	double LocalScX;
	double LocalViewX;
  /** Lokales Scaling y*/
	double LocalScY;
	double LocalViewY;
  /** Lokales X */
	double LocalX;
  /** Lokales Y */
	double LocalY;
	int OrigW;
	int OrigH;
	double dpiX;
	double dpiY;
  /** Anzahl horizontaler Spiegelungen */
	int flippedH;
  /** Anzahl vertikaler Spiegelungen */
	int flippedV;
  /** BoundigBox-X */
	double BBoxX;
  /** BoundingBox-H */
	double BBoxH;
  /** Extra Abstand vom Rand */
	double Extra;
	double TExtra;
	double BExtra;
	double RExtra;
  /** Linespacing */
	double LineSp;
  /** Zeichen X-Position */
	double CurX;
  /** Zeichen Y-Position */
	double CurY;
  /** Cursorposition */
	int CPos;
  /** Text des Elements */
	QPtrList<ScText> itemText;
  /** Flag ob Element gedruckt wird */
	bool isPrintable;
  /** Flag fuer PDF-Bookmark */
	bool isBookmark;
	int BMnr;
  /** Flag fuer PDF-Annotation */
	bool isAnnotation;
	int AnType;
	int AnActType;
	QString AnAction;
	QString An_E_act;
	QString An_X_act;
	QString An_D_act;
	QString An_Fo_act;
	QString An_Bl_act;
	QString An_K_act;
	QString An_F_act;
	QString An_V_act;
	QString An_C_act;
	bool AutoName;
	QString AnToolTip;
	QString AnRollOver;
	QString AnDown;
	QString AnBColor;
	QString An_Extern;
	int AnBsty;
	int AnBwid;
	int AnFeed;
	int AnZiel;
	int AnFlag;
	int AnMaxChar;
	int AnVis;
	int AnChkStil;
	int AnFont;
	bool AnIsChk;
	bool AnAAact;
	bool AnHTML;
	bool AnUseIcons;
	int AnIPlace;
	int AnScaleW;
	int AnFormat;
  /** Flag fuer neuzeichnen im EditMode */
	bool Dirty;
  /** Item Font */
	QString IFont;
  /** Item Fontgroesse */
	int ISize;
  /** Flag fuer Auswahl */
	bool HasSel;
  /** Flag fuer Textfluss */
	bool Textflow;
	bool Textflow2;
	bool FrameOnly;
	PageItem *BackBox;
	PageItem *NextBox;
	int NextIt;
	int NextPg;
	bool Tinput;
	bool isAutoText;
	int textAlignment;
	uint MaxChars;
	bool Redrawn;
	double ExtraV;
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
	double Transparency;
	double TranspStroke;
	QValueStack<int> Groups;
	bool InvPict;
	QValueList<double> DashValues;
	QValueList<double> TabValues;
	double DashOffset;
	VGradient fill_gradient;
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
	int startArrowIndex;
	int endArrowIndex;

	/** @brief Manages undostack and is where all undo actions/states are sent. */
	UndoManager *undoManager;
	/**  @brief Get name of the item
	 *
	 * This is unrelated to QObject::name(); the pageItem's name is independent
	 * of its Qt name.
	 * See also PageItem::setItemName()
	 */
	QString itemName() const;
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
	QString fillColor() const;
	/**
	 * @brief Set the fill color of the object.
	 * @param newColor fill color for the object
	 */
	void setFillColor(const QString &newColor);

	/** @brief Get the shade of the fill color */
	int fillShade() const;
	/**
	 * @brief Set the fill color shade.
	 * @param newShade shade for the fill color
	 */
	void setFillShade(int newShade);

	/** @brief Get the transparency of the fill color */
	double fillTransparency() const;
	/**
	 * @brief Set the transparency of the fill color.
	 * @param newTransparency transparency of the fill color
	 */
	void setFillTransparency(double newTransparency);

	/** @brief Get the line color of the object */
	QString lineColor() const;
	/**
	 * @brief Set the line color of the object.
	 * @param newFill line color for the object
	 */
	void setLineColor(const QString &newColor);

	/** @brief Get the line color shade */
	int lineShade() const;
	/**
	 * @brief Set the line color shade.
	 * @param newColor shade for the line color
	 */
	void setLineShade(int newShade);

	/** @brief Get the line transparency */
	double lineTransparency() const;
	/**
	 * @brief Set the transparency of the line color.
	 * @param newTransparency transparency of the line color
	 */
	void setLineTransparency(double newTransparency);
	/**
	 * @brief Set the style of line.
	 * @param newStyle style of line
	 * @sa Qt::PenStyle
	 */
	void setLineStyle(PenStyle newStyle);
	/**
	 * @brief Set the width of line
	 * @param newWidth width of line
	 */
	void setLineWidth(double newWidth);
	/**
	 * @brief Set the end style of line
	 * @param newStyle end style of line
	 * @sa Qt::PenCapStyle
	 */
	void setLineEnd(PenCapStyle newStyle);
	/**
	 * @brief Set the join style of line
	 * @param newStyle join style of line
	 * @sa Qt::PenJoinStyle
	 */
	void setLineJoin(PenJoinStyle newStyle);
	/** 
	 * @brief Set custom line style
	 * @param newStyle name of the custom style
	 */
	void setCustomLineStyle(const QString& newStyle);
	/** @brief Flip an image horizontally. */
	void flipImageH();
	/** @brief Flip an image vertically */
	void flipImageV();

	/** @brief Lock or unlock this pageitem. */
	void toggleLock();
	/** @brief is the item locked ? */
	bool locked() const;
	/** @brief Lock or unlock this pageitem */
	void setLocked(bool isLocked);

	/** @brief Toggle lock for resizing */
	void toggleSizeLock();
	/** @brief Is the item's size locked? */
	bool sizeLocked() const;
	/** @brief set lock for resizing */
	void setSizeLocked(bool isLocked);

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
	/*@}*/
	/** @brief Required by the UndoObject */
	void restore(UndoState *state, bool isUndo);

protected:
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
	 * @brief Item name. Unicode. User visible (outline, property palette, etc).
	 *
	 * See PageItem::itemName(), PageItem::setItemName()
	 * */
	QString AnName;
};

#endif
