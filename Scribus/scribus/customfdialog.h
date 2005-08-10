/***************************************************************************
                          customfdialog.h  -  description
                             -------------------
    begin                : Fri Nov 30 2001
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

#ifndef CUSTOMFDIALOG_H
#define CUSTOMFDIALOG_H

#include <qfiledialog.h>
#include <qurl.h>
#include <qlabel.h>
#include <qdir.h>
#include <qpixmap.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qframe.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qstring.h>

#include "scribusapi.h"

/**
  *@author Franz Schmid
  */
class SCRIBUS_API ImIconProvider : public QFileIconProvider
{
    Q_OBJECT
    QStringList fmts;
    QPixmap imagepm;
    QPixmap docpm;
    QPixmap pspm;
    QPixmap pdfpm;
    QPixmap txtpm;
    QPixmap oosxdpm;
    QPixmap oosxwpm;
    QPixmap vectorpm;
public:
    ImIconProvider(QWidget *pa);
    ~ImIconProvider() {};

    const QPixmap * pixmap(const QFileInfo &fi);
};

class SCRIBUS_API FDialogPreview : public QLabel, public QFilePreview
{
    Q_OBJECT
public:
	FDialogPreview(QWidget *pa);
	~FDialogPreview() {};
	void updtPix();
	void GenPreview(QString name);
	virtual void previewUrl(const QUrl &url);
};

class SCRIBUS_API CustomFDialog : public QFileDialog
{
    Q_OBJECT
public: 
	CustomFDialog(QWidget *pa, QString wDir, QString cap = "", QString filter = "", 
	              bool Pre = false, bool mod = true, bool comp = false, bool cod = false,
	              bool dirOnly = false);
	~CustomFDialog();
	QDir cDir;
	QCheckBox* SaveZip;
	QCheckBox* WFonts;
	QFrame* Layout;
	QToolButton* HomeB;
	QFrame* LayoutC;
	QComboBox *TxCodeM;
	QLabel *TxCodeT;
private slots:
	void slotHome();
	void HandleComp();
protected:
	QHBoxLayout* Layout1;
	QHBoxLayout* Layout1C;
};

#endif
