/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
    begin                : Jun 2007
    copyright            : (C) 2007 by Mateusz Haligowski
    email                : halish@kofeina.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef IMPOSITION_UI_H
#define IMPOSITION_UI_H

#include "ui_impositionbase.h"
#include <QTabWidget>
#include <QGroupBox>
#include <QFrame>
#include <QLabel>
#include <QSpinBox>

#include "scribusstructs.h"
#include "scribuscore.h"
#include "scribuswin.h"
#include "scribusapi.h"


class ScribusDoc;

class Imposition : public QDialog,Ui::ImpositionBase
{
  Q_OBJECT

	public:
		Imposition(QWidget* parent = 0, ScribusDoc* doc = 0);
		~Imposition();
		
		double unitRatio;
		QString unitSuffix;
		int unitIndex;

	private:
		QWidget* parent;
		ScribusDoc* srcDoc;
		ScribusDoc* targetDoc;
		ScribusWin* w;
		ScribusView* view;
// 			
	protected slots:
		virtual void languageChange();
		void setPageSize(const QString &);
		void customizeSize();
		void change2SidesBox(int);
		virtual void accepted();
		
		void changePage();
		void changeDocGrid();
		void changeDocBooklet();
		void changeDocFold();
		void changeTab(int);
};

#endif //IMPOSITION_UI_H
