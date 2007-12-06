/*
 For general Scribus (>=1.3.2) copyright and licensing information please refer
 to the COPYING file provided with the program. Following this notice may exist
 a copyright and/or license notice that predates the release of Scribus 1.3.2
 for which a new license (GPL+exception) is in place.
 */
/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/



#ifndef CANVAS_GESTURE_RULERMOVE_H
#define CANVAS_GESTURE_RULERMOVE_H

#include <QPoint>

#include "scribusapi.h"
#include "canvas.h"
#include "canvasgesture.h"
#include "canvasmode.h"

class QCursor;
class QDragEnterEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;
class QEvent;
class QInputMethodEvent;
class QMouseEvent;
class QKeyEvent;
class QPainter;

/**
  This class realizes the moving of guides and the moving of the ruler origin
 */
class SCRIBUS_API RulerGesture : public CanvasGesture
{
public:
	enum Mode { HORIZONTAL, VERTICAL, ORIGIN };
	RulerGesture (CanvasMode* parent, Mode mode, int index = -1) : 
		CanvasGesture(parent), m_mode(mode), m_index(index), m_cursor(0), m_xy(0,0) {};

	virtual void drawControls(QPainter* p);
	virtual void activate(bool);
	virtual void deactivate(bool);
	virtual void mouseReleaseEvent(QMouseEvent *m);
	virtual void mouseMoveEvent(QMouseEvent *m);
	/**
	  This method should be called when the mousebutton is pressed near a guide.
	 */
	virtual void mousePressEvent(QMouseEvent *m);
	
	Mode getMode();
	bool mouseHitsGuide(FPoint mousePointDoc);
private:
	Mode m_mode;
	int m_index;
	int m_page;
	QCursor* m_cursor;
	QPoint m_xy;
	void movePoint(QMouseEvent *m);
};


#endif
