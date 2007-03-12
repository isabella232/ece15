/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          scribuswin.cpp  -  description
                             -------------------
    begin                : Mit Nov 6 2002
    copyright            : (C) 2002 by Franz Schmid
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
#include <qfileinfo.h>
#include <qdir.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3Frame>
#include <QCloseEvent>
#include "scribuswin.h"
#include "pageselector.h"
#include "scmessagebox.h"
//#include "scribuswin.moc"
#include "fileloader.h"
#include "scribus.h"
#include "story.h"
#include "util.h"
#include "commonstrings.h"



ScribusWin::ScribusWin(QWidget* parent, ScribusDoc* doc) : Q3MainWindow(parent, "", Qt::WDestructiveClose)
{
	setIcon(loadIcon("AppIcon2.png"));
	m_Doc = doc;
	m_masterPagesPalette = NULL;
	currentDir = QDir::currentDirPath();
}

void ScribusWin::setMainWindow(ScribusMainWindow *mw)
{
	m_MainWindow=mw;
}

void ScribusWin::setView(ScribusView* newView)
{
	m_View = newView;
	++m_Doc->viewCount;
	winIndex = ++m_Doc->viewID;
	QPoint point(0,0);
	statusFrame = new Q3Frame(this, "newDocFrame");
	statusFrameLayout = new Q3HBoxLayout( statusFrame, 0, 0, "statusFrame");
	m_View->unitSwitcher->reparent(statusFrame, point);
	m_View->layerMenu->reparent(statusFrame, point);
	m_View->zoomOutToolbarButton->reparent(statusFrame, point);
	m_View->zoomDefaultToolbarButton->reparent(statusFrame, point);
	m_View->zoomInToolbarButton->reparent(statusFrame, point);
	m_View->pageSelector->reparent(statusFrame, point);
	m_View->zoomSpinBox->reparent(statusFrame, point);
	m_View->cmsToolbarButton->reparent(statusFrame, point);
	m_View->previewToolbarButton->reparent(statusFrame, point);
	m_View->visualMenu->reparent(statusFrame, point);
	statusFrameLayout->addWidget(m_View->unitSwitcher);
	statusFrameLayout->addWidget(m_View->zoomSpinBox);
	statusFrameLayout->addWidget(m_View->zoomOutToolbarButton);
	statusFrameLayout->addWidget(m_View->zoomDefaultToolbarButton);
	statusFrameLayout->addWidget(m_View->zoomInToolbarButton);
	statusFrameLayout->addWidget(m_View->pageSelector);
	statusFrameLayout->addWidget(m_View->layerMenu);
	QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	statusFrameLayout->addItem( spacer );
	statusFrameLayout->addWidget(m_View->cmsToolbarButton);
	statusFrameLayout->addWidget(m_View->previewToolbarButton);
	statusFrameLayout->addWidget(m_View->visualMenu);
#ifndef HAVE_CAIRO
	m_View->previewToolbarButton->hide();
	m_View->visualMenu->hide();
#endif
	statusBar()->addWidget(statusFrame, 4, true);
	currentDir = QDir::currentDirPath();
}

void ScribusWin::slotAutoSave()
{
	if ((m_Doc->hasName) && (m_Doc->isModified()))
	{
		moveFile(m_Doc->DocName, m_Doc->DocName+".bak");
		QFileInfo fi(m_Doc->DocName);
		QDir::setCurrent(fi.dirPath(true));
		FileLoader fl(m_Doc->DocName);
		if (fl.SaveFile(m_Doc->DocName, m_Doc, 0))
		{
			m_Doc->setModified(false);
			setCaption(QDir::convertSeparators(m_Doc->DocName));
			qApp->processEvents();
			emit AutoSaved();
		}
	}
}

void ScribusWin::closeEvent(QCloseEvent *ce)
{
	if (m_Doc->isModified() && (m_Doc->viewCount == 1))
	{
		qApp->setOverrideCursor(QCursor(arrowCursor), true);
		int exit=ScMessageBox::information(m_MainWindow, CommonStrings::trWarning, tr("Document:")+" "+
											QDir::convertSeparators(m_Doc->DocName)+"\n"+
											tr("has been changed since the last save."),
											CommonStrings::tr_Save, tr("&Discard"),
											CommonStrings::tr_Cancel, 2, 2);
		if (exit==2)
			return;
		if (exit==0)
		{
			if (m_MainWindow->slotFileSave())
			{
				if (m_Doc==m_MainWindow->storyEditor->currentDocument())
					m_MainWindow->storyEditor->close();
			}
			else
				return;
		}
	}
	m_MainWindow->DoFileClose();
	ce->accept();
}

void ScribusWin::setMasterPagesPaletteShown(bool isShown) const
{
	if (m_masterPagesPalette==NULL)
		return;
	if (isShown)
		m_masterPagesPalette->show();
	else
		m_masterPagesPalette->hide();
}

void ScribusWin::windowActivationChange ( bool oldActive )
{
	if( isActiveWindow() )
		QDir::setCurrent( currentDir );
	else
		currentDir = QDir::currentDirPath();
	Q3MainWindow::windowActivationChange( oldActive );
}
