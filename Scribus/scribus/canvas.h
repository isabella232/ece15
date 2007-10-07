/*
 For general Scribus (>=1.3.2) copyright and licensing information please refer
 to the COPYING file provided with the program. Following this notice may exist
 a copyright and/or license notice that predates the release of Scribus 1.3.2
 for which a new license (GPL+exception) is in place.
 */
/***************************************************************************
scribusview.h  -  description
-------------------
    begin                : Fre Apr  6 21:47:55 CEST 2001
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

#ifndef CANVAS_H
#define CANVAS_H

#include <QApplication>
#include <QDebug>
#include <QPolygon>
#include <QRect>
#include <QWidget>

#include "scribusapi.h"

#include "commonstrings.h"
#include "fpoint.h"
#include "fpointarray.h"


class Page;
class PageItem;
class ScPainter;
class ScribusDoc;

struct CanvasViewMode
{
	void init();
	
	double scale;

	bool previewMode;
	bool viewAsPreview;
	int previewVisual;

	bool m_MouseButtonPressed;
	bool operItemMoving;
	bool operItemResizing;
	bool operItemResizeInEditMode;
	QPolygon redrawPolygon;
	QList<PageItem*> linkedFramesToShow;
	
	/** if true, selected objects will not be drawn by drawContents() */
	bool drawSelectedItemsWithControls;
	/** if true, drawContents() will draw framelinks even if View->Show Framelinks is false */
	bool drawFramelinksWithContents;
	
	// used for buffering:
	bool specialRendering;
	bool firstSpecial;
	QPixmap m_buffer;
	QRect m_bufferRect;
	FPoint oldMinCanvasCoordinate;
};


class SCRIBUS_API Canvas : public QWidget
{
	Q_OBJECT
	
	static const uint moveWithFullOutlinesThreshold = 21;
	static const uint moveWithBoxesOnlyThreshold = 41;

public:	
	Canvas(ScribusDoc* doc, QWidget* parent);
	
	friend class ScribusView; // for now...
	friend class LegacyMode;
	friend class CanvasMode_NodeEdit;
	
	/* Dont rely on these codes!
	 * 283
	 * 7 6
	 * 451
	 * But always OUTSIDE < 0, INSIDE >= 0 and any specific handle > 0.
	 */
	enum FrameHandle { 
		OUTSIDE = -1,
		INSIDE = 0,
		NORTHWEST = 2,
		NORTH = 8,
		NORTHEAST = 3,
		EAST = 6,
		SOUTHEAST = 1,
		SOUTH = 5,
		SOUTHWEST = 4,
		WEST = 7
	};
	
	
	void resetRenderMode() { m_viewMode.specialRendering = false; m_viewMode.firstSpecial = true; }
	void setRenderModeFillBuffer() { m_viewMode.specialRendering = true; m_viewMode.firstSpecial = true; }
	void setRenderModeUseBuffer(bool use) { m_viewMode.specialRendering = use; }

	double scale() const { return m_viewMode.scale; }
	void setScale(double scale) { m_viewMode.scale = scale; repaint(); }
	QPoint canvasToLocal(FPoint p) const;
	QPoint canvasToGlobal(FPoint p) const;
	QPoint canvasToLocal(QPointF p) const;
	QPoint canvasToGlobal(QPointF p) const;
	FPoint localToCanvas(QPoint p) const;
	FPoint globalToCanvas(QPoint p) const;
	QRectF globalToCanvas(QRect p) const;
	bool hitsCanvasPoint(QPoint globalPoint, FPoint canvasPoint) const;
	bool hitsCanvasPoint(QPoint globalPoint, QPointF canvasPoint) const;
	/** Returns the framehandle or INSIDE if the position falls into the frame. */
	FrameHandle frameHitTest(QPointF canvasPoint, PageItem* frame) const;
	FrameHandle frameHitTest(QPointF point, QRectF frame) const;
	/**
		Returns the item under the cursor or NULL if none found.
	 Does *not* change the selection.
	 If itemAbove is given, it will look for an item under itemAbove, allowing select under.
	 The flag 'allowInGroup' controls if single items within a group or only whole groups are considered.
	 The flag 'allowMasterItems' controls if items from a masterpage are considered.
	 (this flag is ignored in masterpage mode, since all items are masterpage items then).
	 */
	PageItem* itemUnderCursor(QPoint globalPos, PageItem* itemAbove=NULL, bool allowInGroup=false, bool allowMasterItems=false) const;
	const QPolygon& redrawPolygon() const { return m_viewMode.redrawPolygon; }
	QPolygon& newRedrawPolygon() 
	{
		m_viewMode.redrawPolygon.clear();
		return m_viewMode.redrawPolygon;
	}
	void setPreviewMode(bool on) { m_viewMode.previewMode = on; }
	bool isPreviewMode() const { return m_viewMode.previewMode || m_viewMode.viewAsPreview; }
	bool usePreviewVisual() const { return m_viewMode.viewAsPreview && m_viewMode.previewVisual != 0; }
	int previewVisual() const { return m_viewMode.previewVisual; }
	void setPreviewVisual(int mode) { m_viewMode.previewVisual = qMax(0, mode); m_viewMode.viewAsPreview = (mode >= 0); }
	
	void DrawMasterItems(ScPainter *painter, Page *page, QRect clip);
	void DrawPageItems(ScPainter *painter, QRect clip);
	virtual void paintEvent ( QPaintEvent * p );
	
private:
	void DrawPageMarks(ScPainter *p, Page* page, QRect clip);
	void drawLinkFrameLine(ScPainter* painter, FPoint &start, FPoint &end);
	void paintGroupRect(bool norm = true);
	void PaintSizeRect(QRect neu);
	void PaintSizeRect(QPolygon neu);
	void MarkClip(QPainter *p, PageItem *currItem, FPointArray cli, bool once = false);
	void Transform(PageItem *currItem, QPainter *p);
	void Transform(PageItem *currItem, QMatrix& m);
	void TransformM(PageItem *currItem, QPainter *p);
	void getGroupRectScreen(double *x, double *y, double *w, double *h);

	void drawContents(QPainter *p, int clipx, int clipy, int clipw, int cliph);
	void drawBackgroundMasterpage(ScPainter* painter, int clipx, int clipy, int clipw, int cliph);
	void drawBackgroundPageOutlines(ScPainter* painter, int clipx, int clipy, int clipw, int cliph);
	void drawGuides(ScPainter* painter, int clipx, int clipy, int clipw, int cliph);
	void drawFrameLinks(ScPainter* painter);
	void drawControls(QPainter* p);
	void drawControlsMovingItemsRect(QPainter* pp);
	void drawControlsHighlightRect(QPainter* pp);
	void drawControlsGradientVectors(QPainter* psx, PageItem *currItem);
	void drawControlsBezierCurve(QPainter* pp, PageItem* currItem);
	void drawControlsNodeEditPoints(QPainter* pp, PageItem* currItem);
	void drawControlsMeasurementLine(QPainter* pp);
	void drawControlsDrawLine(QPainter* pp);
	void drawControlsFreehandLine(QPainter* pp);
	void drawControlsSelection(QPainter* pp, PageItem *currItem);
	void drawControlsSelectionSpecial(QPainter* pp, PageItem *currItem);
	virtual void drawContentsOld(QPainter *p, int clipx, int clipy, int clipw, int cliph);
	void getClipPathForPages(FPointArray* PoLine);
		
private:
	ScribusDoc* m_doc;
	CanvasViewMode m_viewMode;
};


#endif

