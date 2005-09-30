/***************************************************************************
                          dynamictip.h  -  description
                             -------------------
    begin                : Wed Aug 31 2005
    copyright            : (C) 2005 by Franz Schmid
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

#ifndef DYNAMICTIP_H
#define DYNAMICTIP_H

#include <qtooltip.h>
#include <qlistbox.h>
#include <qtable.h>
#include "scribusapi.h"
#include "scribusstructs.h"

class SCRIBUS_API DynamicTip : public QToolTip
{
public:
	enum TipType {
		ColorListBox,
		Table
	};

	DynamicTip( QListBox* parent, ColorList* pale );
	DynamicTip( QTable* parent );
protected:
	void maybeTip( const QPoint & );
	ColorList* colorList;
	QListBox* listB;
	QTable* table;
	TipType kind;
};

#endif
