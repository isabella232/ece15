/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
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
#include "selection.h"
#include "undomanager.h"
#include "undostate.h"
#include "guidemanagercore.h"
#include "frameedit.h"

extern QPixmap loadIcon(QString nam);


Page::Page(const double x, const double y, const double b, const double h) :
	UndoObject(QObject::tr("Page")),
	Margins(40,40,40,40),
	initialMargins(40,40,40,40),
	LeftPg(0),
	MPageNam(""),
	//XGuides(),
	//YGuides(),
	FromMaster(),
	undoManager(UndoManager::instance()),
	m_xOffset(x),
	m_yOffset(y),
	m_width(b),
	m_height(h),
	m_initialWidth(b),
	m_initialHeight(h),
	m_PageName(""),
	m_Doc(NULL)
{
	guides.setPage(this);
}

Page::~Page()
{
	// Clean up any modified template items (unused)
	for (PageItem *currItem = FromMaster.first(); currItem; currItem = FromMaster.next())
	{
		if (currItem->ChangedMasterItem)
		{
			FromMaster.remove(currItem);
			delete currItem;
		}
	}
	FromMaster.clear();
}

void Page::setDocument(ScribusDoc *doc)
{
	m_Doc=doc;
}

void Page::setPageNr(int pageNr)
{
	m_pageNr = pageNr;
	if (m_PageName.isEmpty())
		setUName(QString(QObject::tr("Page") + " %1").arg(m_Doc->FirstPnum + m_pageNr));
	else
		setUName(m_PageName);
}

/* PV
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
	undoManager->setUndoEnabled(false);
	removeXGuide(from);
	addXGuide(to);
	undoManager->setUndoEnabled(true);
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
	undoManager->setUndoEnabled(false); // only want to store move action not remove/add actions related to it
	removeYGuide(from);
	addYGuide(to);
	undoManager->setUndoEnabled(true);
	if (UndoManager::undoEnabled())
	{
		SimpleState* ss = new SimpleState(Um::MoveHGuide, 0, Um::IGuides);
		ss->set("MOVE_H_FROM", from);
		ss->set("MOVE_H_TO", to);
		undoManager->action(this, ss);
	}
}
*/

void Page::setPageName(const QString& newName)
{
	m_PageName = newName;
	if (!newName.isEmpty())
		setUName(QObject::tr("Master Page ") + newName);
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
				guides.deleteVertical(position, GuideManagerCore::Standard);//removeXGuide(position);
			else
				guides.addVertical(position, GuideManagerCore::Standard);//addXGuide(position);
		}
		else if (ss->contains("ADD_H"))
		{
			double position = ss->getDouble("ADD_H");
			if (isUndo)
				guides.deleteHorizontal(position, GuideManagerCore::Standard);//removeYGuide(position);
			else
				guides.addHorizontal(position, GuideManagerCore::Standard);//addYGuide(position);
		}
		else if (ss->contains("REMOVE_V"))
		{
			double position = ss->getDouble("REMOVE_V");
			if (isUndo)
				guides.addVertical(position, GuideManagerCore::Standard);//addXGuide(position);
			else
				guides.deleteVertical(position, GuideManagerCore::Standard);//removeXGuide(position);
		}
		else if (ss->contains("REMOVE_H"))
		{
			double position = ss->getDouble("REMOVE_H");
			if (isUndo)
				guides.addHorizontal(position, GuideManagerCore::Standard);//addYGuide(position);
			else
				guides.deleteHorizontal(position, GuideManagerCore::Standard);//removeYGuide(position);
		}
		else if (ss->contains("MOVE_H_FROM"))
		{
			double from = ss->getDouble("MOVE_H_FROM");
			double to   = ss->getDouble("MOVE_H_TO");
			if (isUndo)
			{
				guides.deleteHorizontal(to, GuideManagerCore::Standard);//removeYGuide(position);
				guides.addHorizontal(from, GuideManagerCore::Standard);//addYGuide(position);
			}
			else
			{
				guides.deleteHorizontal(from, GuideManagerCore::Standard);//removeYGuide(position);
				guides.addHorizontal(to, GuideManagerCore::Standard);//addYGuide(position);
			}
		}
		else if (ss->contains("MOVE_V_FROM"))
		{
			double from = ss->getDouble("MOVE_V_FROM");
			double to   = ss->getDouble("MOVE_V_TO");
			if (isUndo)
			{
				guides.deleteVertical(to, GuideManagerCore::Standard);//removeXGuide(position);
				guides.addVertical(from, GuideManagerCore::Standard);//removeXGuide(position);
			}
			else
			{
				guides.deleteVertical(from, GuideManagerCore::Standard);//removeXGuide(position);
				guides.addVertical(to, GuideManagerCore::Standard);//removeXGuide(position);
			}
		}
		else if (ss->contains("CREATE_ITEM"))
			restorePageItemCreation(dynamic_cast<ItemState<PageItem*>*>(ss), isUndo);
		else if (ss->contains("DELETE_ITEM"))
			restorePageItemDeletion(dynamic_cast<ItemState<PageItem*>*>(ss), isUndo);
		else if (ss->contains("CONVERT_ITEM"))
			restorePageItemConversion(dynamic_cast<ItemState<std::pair<PageItem*, PageItem*> >*>(ss), isUndo);
	}
}

void Page::restorePageItemCreation(ItemState<PageItem*> *state, bool isUndo)
{
	if (!state)
		return;
	PageItem *ite = state->getItem();
	bool oldMPMode=m_Doc->masterPageMode();
	m_Doc->setMasterPageMode(!ite->OnMasterPage.isEmpty());
	if (m_Doc->EditClip) // switch off from edit shape
		m_Doc->scMW()->nodePalette->EndEdit();
	if (isUndo)
	{
		if (m_Doc->m_Selection->findItem(ite)!=-1)
		{
			if (m_Doc->appMode == modeEdit)
				m_Doc->scMW()->setAppMode(modeNormal);
			m_Doc->m_Selection->removeItem(ite);
		}
		Selection tempSelection(m_Doc, false);
		tempSelection.addItem(ite);
		m_Doc->itemSelection_DeleteItem(&tempSelection, false);
		/*
		m_Doc->m_Selection->clear();
		m_Doc->m_Selection->addItem(ite, true);
		m_Doc->itemSelection_DeleteItem();
		m_Doc->m_Selection->clear();
		*/
	}
	else
	{
		m_Doc->Items->append(ite);
		ite->ItemNr = m_Doc->Items->count()-1;
		m_Doc->view()->updateContents();
	}
	m_Doc->setMasterPageMode(oldMPMode);
}

void Page::restorePageItemDeletion(ItemState<PageItem*> *state, bool isUndo)
{
	if (!state)
		return;
	PageItem *ite = state->getItem();
	bool oldMPMode=m_Doc->masterPageMode();
	m_Doc->setMasterPageMode(!ite->OnMasterPage.isEmpty());
	if (m_Doc->EditClip) // switch off from edit shape
		m_Doc->scMW()->nodePalette->EndEdit();
	if (isUndo)
	{
		m_Doc->Items->append(ite);
		ite->ItemNr = m_Doc->Items->count()-1;
		m_Doc->view()->updateContents();
	}
	else
	{
		if (m_Doc->m_Selection->findItem(ite)!=-1)
		{
			if (m_Doc->appMode == modeEdit)
				m_Doc->scMW()->setAppMode(modeNormal);
			m_Doc->m_Selection->removeItem(ite);
		}
		Selection tempSelection(m_Doc, false);
		tempSelection.addItem(ite);
		m_Doc->itemSelection_DeleteItem(&tempSelection);
		/*
		m_Doc->m_Selection->clear();
		m_Doc->m_Selection->addItem(ite, true);
		m_Doc->itemSelection_DeleteItem();
		m_Doc->m_Selection->clear();
		*/
	}
	m_Doc->setMasterPageMode(oldMPMode);
}

void Page::restorePageItemConversion(ItemState<std::pair<PageItem*, PageItem*> >*state, bool isUndo)
{
	if (!state)
		return;

	PageItem *oldItem=state->getItem().first;
	PageItem *newItem=state->getItem().second;
	bool oldMPMode=m_Doc->masterPageMode();
	m_Doc->setMasterPageMode(!oldItem->OnMasterPage.isEmpty());
	if (isUndo)
	{
		m_Doc->Items->take(newItem->ItemNr);
		m_Doc->Items->append(oldItem);
		oldItem->ItemNr = m_Doc->Items->count()-1;
		oldItem->updatePolyClip();
		m_Doc->view()->AdjustItemSize(oldItem);
	}
	else
	{
		m_Doc->Items->take(oldItem->ItemNr);
		m_Doc->Items->append(newItem);
		newItem->ItemNr = m_Doc->Items->count()-1;
	}
	m_Doc->setMasterPageMode(oldMPMode);
}

void Page::setXOffset(const double newCanvasXOffset)
{
	m_xOffset = newCanvasXOffset;
}

void Page::setYOffset(const double newCanvasYOffset)
{
	m_yOffset = newCanvasYOffset;
}

void Page::setWidth(const double newWidth)
{
	m_width = newWidth;
}

void Page::setHeight(const double newHeight)
{
	m_height = newHeight;
}

void Page::setInitialWidth(const double newInitialWidth)
{
	m_initialWidth = newInitialWidth;
}

void Page::setInitialHeight(const double newInitialHeight)
{
	m_initialHeight = newInitialHeight;
}

void Page::setPageSectionNumber(const QString& newPageSectionNumber)
{
	m_pageSectionNumber=newPageSectionNumber;
}

void Page::copySizingProperties(Page* sourcePage, const MarginStruct& pageMargins)
{
	if (sourcePage==NULL)
		return;
	m_pageSize = sourcePage->m_pageSize;
	PageOri = sourcePage->PageOri;
	m_width=sourcePage->m_width;
	m_height=sourcePage->m_height;
	m_initialWidth = sourcePage->m_initialWidth;
	m_initialHeight = sourcePage->m_initialHeight;

	Margins.Top = pageMargins.Top;
	Margins.Bottom = pageMargins.Bottom;
	Margins.Left = pageMargins.Left;//todo fix for layouts
	Margins.Right = pageMargins.Right;
	initialMargins.Top = pageMargins.Top;
	initialMargins.Bottom = pageMargins.Bottom;
	initialMargins.Left = pageMargins.Left;
	initialMargins.Right = pageMargins.Right;
}
