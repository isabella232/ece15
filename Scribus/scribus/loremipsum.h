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

#ifndef _LOREMIPSUM_H_
#define _LOREMIPSUM_H_

#include <qvariant.h>
#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>

#include "scribusapi.h"

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class Q3ListView;
class Q3ListViewItem;
class QLabel;
class QSpinBox;
class QCheckBox;
class QPushButton;
class QString;
class QStringList;

class ScribusDoc;
class LanguageManager;


/*! \brief XML parser for Lorem Ipsum file.
This helper class reads one file
\author Petr Vanek <petr@yarpen.cz>
 */
class SCRIBUS_API LoremParser
{
	public:
		/*! parse a XML file with given name
		\param filename string fith the file name with full/relative path */
		LoremParser(QString filename);
		~LoremParser(){};

		//! Is the LI correct?
		bool correct;
		//! Name to display
		QString name;
		//! Author of the LI
		QString author;
		//! Website of the LI
		QString url;
		//! Paragraphs of the LI
		QStringList loremIpsum;

		/*! Construct a LI
		\param parCount count of the paragraphs */
		QString createLorem(uint parCount);
};

/*! \brief This module provides simple interface to the various Lorem Ipsum variants.
Scribus LI are stored in the set of XML files.
The file has followind structure:
\<?xml version="1.0" encoding="utf8"?\>
\<lorem\>
\<name\>name to display\</name\>
\<author\>person name\</author\>
\<url\>web interface\</url\>
\<p\>text\</p\>
\<p\>...\</p\>
\</lorem\>
Files are in UTF8 encoding.
\author Petr Vanek <petr@yarpen.cz>
*/
class SCRIBUS_API LoremManager : public QDialog
{
	Q_OBJECT

	public:
		/*! Reads all XML files in cfg directory. */
		LoremManager(ScribusDoc* doc, QWidget* parent = 0, const char* name = 0, bool modal = true, Qt::WFlags fl = 0);
		~LoremManager();

		//! all lorems with Public Name -> filename structure
		QMap<QString,QString> availableLorems;

		/*! Apply created LI into a frame
		\param name filename of the selected LI
		\param paraCount count of the paragraphs
		*/
		void insertLoremIpsum(QString name, int paraCount);

	public slots:
		virtual void okButton_clicked();
		virtual void cancelButton_clicked();

	protected:
		ScribusDoc* m_Doc;
		Q3ListView* loremList;
		QLabel* paraLabel;
		QSpinBox* paraBox;
		QPushButton* okButton;
		QPushButton* cancelButton;

		Q3GridLayout* LoremManagerLayout;
		Q3VBoxLayout* layout3;
		Q3HBoxLayout* layout2;
		QSpacerItem* paraSpacer;
		Q3HBoxLayout* layout1;
		QSpacerItem* buttonSpacer;
		LanguageManager* langmgr;
		QString standardloremtext;

	protected slots:
		virtual void languageChange();

};

#endif
