/***************************************************************************
    begin                : Jan 2005
    copyright            : (C) 2005 by Craig Bradney
    email                : cbradney@zip.com.au
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <qpopupmenu.h>
#include <qiconset.h>
#include "scraction.h"
#include "scraction.moc"


ScrAction::ScrAction( QObject * parent, const char * name ) : QAction( parent, name )
{
	menuType=ScrAction::Normal;
}

ScrAction::ScrAction( const QString & menuText, QKeySequence accel, QObject * parent, const char * name ) : QAction( menuText, accel, parent, name )
{
	menuType=ScrAction::Normal;
}

ScrAction::ScrAction( MenuType mType, const QIconSet & icon, const QString & menuText, QKeySequence accel, QObject * parent, const char * name, int extraInt, double extraDouble, QString extraQString ) : QAction( icon, menuText, accel, parent, name )
{
	setIconSizes();
	menuType=mType;
	switch (mType)
	{
		case DataInt:
			_dataInt=extraInt;
			connect (this, SIGNAL(activated()), this, SLOT(activatedToActivatedData()));
			break;
		case DataDouble:
			_dataDouble=extraDouble;
			connect (this, SIGNAL(activated()), this, SLOT(activatedToActivatedData()));
			break;
		case DataQString:
			_dataQString=extraQString;
			connect (this, SIGNAL(activated()), this, SLOT(activatedToActivatedData()));
			break;
		case RecentFile:
			connect (this, SIGNAL(activated()), this, SLOT(activatedToActivatedData()));
			break;
		case DLL:
			pluginID=extraInt;
			connect (this, SIGNAL(activated()), this, SLOT(activatedToActivatedData()));
			break;
		case Window:
			windowID=extraInt;
			connect (this, SIGNAL(activated()), this, SLOT(activatedToActivatedData()));
			break;
		case RecentScript:
			connect (this, SIGNAL(activated()), this, SLOT(activatedToActivatedData()));
			break;			
		case Normal:
		default:
			break;
	}
}

ScrAction::ScrAction( const QIconSet & icon, const QString & menuText, QKeySequence accel, QObject * parent, const char * name ) : QAction( icon, menuText, accel, parent, name )
{
	menuType=ScrAction::Normal;
	setIconSizes();
}

ScrAction::~ScrAction()
{
}

void ScrAction::setIconSizes()
{
	QIconSet iconset=iconSet();
	if (!iconset.isNull())
	{
		iconset.setIconSize(QIconSet::Small, QSize(16,16));
		iconset.setIconSize(QIconSet::Large, QSize(22,22));
	}
}

void ScrAction::activatedToActivatedData()
{
	if (menuType==ScrAction::DataInt)
		emit activatedData(_dataInt);
	if (menuType==ScrAction::DataDouble)
		emit activatedData(_dataDouble);
	if (menuType==ScrAction::DataQString)
		emit activatedData(_dataQString);
	if (menuType==ScrAction::DLL)
		emit activatedData(pluginID);
	if (menuType==ScrAction::Window)
		emit activatedData(windowID);
	if (menuType==ScrAction::RecentFile)
		emit activatedData(menuText());
	if (menuType==ScrAction::RecentScript)
		emit activatedData(menuText());
}

void ScrAction::toggledToToggledData()
{
	if (isToggleAction())
	{
		if (menuType==ScrAction::DataInt)
			emit toggledData(isOn(), _dataInt);
		if (menuType==ScrAction::DataDouble)
			emit toggledData(isOn(), _dataDouble);
		if (menuType==ScrAction::DataQString)
			emit toggledData(isOn(), _dataQString);
		if (menuType==ScrAction::DLL)
			emit toggledData(isOn(), pluginID);
		if (menuType==ScrAction::Window)
			emit toggledData(isOn(), windowID);
		if (menuType==ScrAction::RecentFile)
			emit toggledData(isOn(), menuText());
		if (menuType==ScrAction::RecentScript)
			emit toggledData(isOn(), menuText());
	}
}

void ScrAction::addedTo ( int index, QPopupMenu * menu )
{
	menuIndex=index;
	popupMenuAddedTo=menu;
}


void ScrAction::addedTo( QWidget * actionWidget, QWidget * container )
{
	if (widgetAddedTo)
		widgetAddedTo = actionWidget;
	if (containerWidgetAddedTo)
		containerWidgetAddedTo = container;
}


QWidget* ScrAction::getWidgetAddedTo()
{
	return widgetAddedTo;
}

QString ScrAction::cleanMenuText()
{
	return menuText().remove('&');
}

const int ScrAction::getMenuIndex()
{
	return menuIndex;
}

bool ScrAction::addTo ( QWidget * w )
{
	widgetAddedTo=w;
	return (QAction::addTo(w));
}

const bool ScrAction::isDLLAction()
{
	return menuType==ScrAction::DLL;
}

const int ScrAction::dllID()
{
	if (menuType==ScrAction::DLL)
		return pluginID;
	return -1;
}


