/***************************************************************************
                          page.cpp  -  description
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

#include "page.h"
#include "scribus.h"
#include "undomanager.h"
#include "undostate.h"

extern QPixmap loadIcon(QString nam);
extern ScribusApp *ScApp;

Page::Page(double x, double y, double b, double h) : UndoObject(QObject::tr("Page"))
{
	Xoffset = x;
	Yoffset = y;
	Width = b;
	Height = h;
	Margins.Top = 9;
	Margins.Left = 9;
	Margins.Right = 9;
	Margins.Bottom = 40;
	LeftPg = false;
	PageNam = "";
	XGuides.clear();
	YGuides.clear();
	FromMaster.clear();
	undoManager = UndoManager::instance();
}

void Page::setPageNr(int pageNr)
{
	PageNr = pageNr;
	setUName(QString(QObject::tr("Page") + " %1").arg(ScApp->doc->FirstPnum + PageNr));
}

uint Page::getPageNr()
{
	return PageNr;
}

void Page::addXGuide(double position)
{
	XGuides.append(position);
	qHeapSort(XGuides);
	if (UndoManager::undoEnabled())
	{
		SimpleState* ss = new SimpleState(Um::AddVGuide, 0, Um::IGuides);
		ss->set("ADD_V", position);
		undoManager->action(this, ss);
	}
}

void Page::addYGuide(double position)
{
	YGuides.append(position);
	qHeapSort(YGuides);
	if (UndoManager::undoEnabled())
	{
		SimpleState* ss = new SimpleState(Um::AddHGuide, 0, Um::IGuides);
		ss->set("ADD_H", position);
		undoManager->action(this, ss);
	}
}

void Page::addXGuides(QValueList<double>& guides)
{
	QValueList<double> toBeRemoved;
	for (uint i = 0; i < XGuides.size(); ++i)
		if (guides.find(XGuides[i]) == guides.end())
			toBeRemoved.push_back(XGuides[i]);

	for (uint i = 0; i < toBeRemoved.size(); ++i)
		removeXGuide(toBeRemoved[i]);

	for (uint i = 0; i < guides.size(); ++i)
		if (XGuides.find(guides[i]) == XGuides.end())
			addXGuide(guides[i]);
}

void Page::addYGuides(QValueList<double>& guides)
{
	QValueList<double> toBeRemoved;
	for (uint i = 0; i < YGuides.size(); ++i)
		if (guides.find(YGuides[i]) == guides.end())
			toBeRemoved.push_back(YGuides[i]);

	for (uint i = 0; i < toBeRemoved.size(); ++i)
		removeYGuide(toBeRemoved[i]);

	for (uint i = 0; i < guides.size(); ++i)
		if (YGuides.find(guides[i]) == YGuides.end())
			addYGuide(guides[i]);
}

void Page::removeXGuide(double position)
{
	XGuides.remove(XGuides.find(position));
	if (UndoManager::undoEnabled())
	{
		SimpleState* ss = new SimpleState(Um::DelVGuide, 0, Um::IGuides);
		ss->set("REMOVE_V", position);
		undoManager->action(this, ss);
	}
}

void Page::removeXGuide(int index)
{
	double position = XGuides[index];
	removeXGuide(position);
}

void Page::removeYGuide(double position)
{
	YGuides.remove(YGuides.find(position));
	if (UndoManager::undoEnabled())
	{
		SimpleState* ss = new SimpleState(Um::DelHGuide, 0, Um::IGuides);
		ss->set("REMOVE_H", position);
		undoManager->action(this, ss);
	}
}

void Page::removeYGuide(int index)
{
	double position = YGuides[index];
	removeYGuide(position);
}

void Page::moveXGuide(int fromIndex, double to)
{
	double from = XGuides[fromIndex];
	bool tmpUndoEnabled = UndoManager::undoEnabled();
	undoManager->setUndoEnabled(false);
	removeXGuide(from);
	addXGuide(to);
	undoManager->setUndoEnabled(tmpUndoEnabled);
	if (UndoManager::undoEnabled())
	{
		SimpleState* ss = new SimpleState(Um::MoveVGuide, 0, Um::IGuides);
		ss->set("MOVE_V_FROM", from);
		ss->set("MOVE_V_TO", to);
		undoManager->action(this, ss);
	}
}

void Page::moveYGuide(int fromIndex, double to)
{
	double from = YGuides[fromIndex];
	bool tmpUndoEnabled = UndoManager::undoEnabled();
	undoManager->setUndoEnabled(false); // only want to store move action not remove/add actions related to it
	removeYGuide(from);
	addYGuide(to);
	undoManager->setUndoEnabled(tmpUndoEnabled);
	if (UndoManager::undoEnabled())
	{
		SimpleState* ss = new SimpleState(Um::MoveHGuide, 0, Um::IGuides);
		ss->set("MOVE_H_FROM", from);
		ss->set("MOVE_H_TO", to);
		undoManager->action(this, ss);
	}
}

void Page::restore(UndoState* state, bool isUndo)
{
	SimpleState* ss = dynamic_cast<SimpleState*>(state);
	if (ss)
	{
		if (ss->contains("ADD_V"))
		{
			double position = ss->getDouble("ADD_V");
			if (isUndo)
				removeXGuide(position);
			else
				addXGuide(position);
		}
		else if (ss->contains("ADD_H"))
		{
			double position = ss->getDouble("ADD_H");
			if (isUndo)
				removeYGuide(position);
			else
				addYGuide(position);
		}
		else if (ss->contains("REMOVE_V"))
		{
			double position = ss->getDouble("REMOVE_V");
			if (isUndo)
				addXGuide(position);
			else
				removeXGuide(position);
		}
		else if (ss->contains("REMOVE_H"))
		{
			double position = ss->getDouble("REMOVE_H");
			if (isUndo)
				addYGuide(position);
			else
				removeYGuide(position);
		}
		else if (ss->contains("MOVE_V_FROM"))
		{
			double from = ss->getDouble("MOVE_V_FROM");
			double to   = ss->getDouble("MOVE_V_TO");
			if (isUndo)
			{
				removeXGuide(to);
				addXGuide(from);
			}
			else
			{
				removeXGuide(from);
				addXGuide(to);
			}
		}
		else if (ss->contains("MOVE_H_FROM"))
		{
			double from = ss->getDouble("MOVE_H_FROM");
			double to   = ss->getDouble("MOVE_H_TO");
			if (isUndo)
			{
				removeYGuide(to);
				addYGuide(from);
			}
			else
			{
				removeYGuide(from);
				addYGuide(to);
			}
		}
	}
}
