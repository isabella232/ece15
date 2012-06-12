/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          pageitem_polyline.h  -  description
                             -------------------
    copyright            : Scribus Team
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PAGEITEM_POLYLINE_H
#define PAGEITEM_POLYLINE_H

#include <QString>
#include <QRectF>

#include "scribusapi.h"
#include "pageitem.h"
class ScPainter;
class ScribusDoc;

class SCRIBUS_API PageItem_PolyLine : public PageItem
{
	Q_OBJECT

public:
	PageItem_PolyLine(ScribusDoc *pa, double x, double y, double w, double h, double w2, QString fill, QString outline);
	PageItem_PolyLine(const PageItem & p) : PageItem(p) {}
	~PageItem_PolyLine() {};
	
	virtual PageItem_PolyLine * asPolyLine() { return this; }
	virtual bool isPolyLine() const { return true; }
	
	virtual void applicableActions(QStringList& actionList);
	virtual QString infoDescription();

protected:
	virtual void DrawObj_Item(ScPainter *p, QRectF e);

};

#endif
