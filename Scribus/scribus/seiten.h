/****************************************************************************
** Form interface generated from reading ui file 'Seiten2.ui'
**
** Created: Mon Apr 1 12:07:27 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef SEITENPAL_H
#define SEITENPAL_H

#include <qdialog.h>
#include <qtable.h>
#include <qlabel.h>
#include <qlistbox.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qdragobject.h>
#include <qevent.h>
#include <qsplitter.h>
#include "scrpalettebase.h"
#include "scribusview.h"

class SeDrag : public QStoredDrag
{
public:
    SeDrag( QString s, QWidget * parent = 0, const char * name = 0 );
    ~SeDrag() {};

    static bool canDecode( QDragMoveEvent* e );
    static bool decode( QDropEvent* e, QString& s );
};

class SeItem : public QTableItem
{
public:
	SeItem(QTable* parent, QString text, QPixmap Pix, bool ss);
    ~SeItem() {};
	virtual void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);
	bool Side;
};

class SeList : public QListBox
{
    Q_OBJECT

public:
    SeList(QWidget* parent);
    ~SeList() {};
    QPoint Mpos;
	QListBoxItem *CurItem;
    bool Mpressed;
	bool Thumb;

private slots:
	void ToggleTh();

signals:
	void ThumbChanged();

protected:
	void mouseReleaseEvent(QMouseEvent *m);
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
};

class SeView : public QTable
{
    Q_OBJECT

public:
    SeView(QWidget* parent);
    ~SeView() {};
	void ClearPix();
	int GetPage(int r, int c);
    QPoint Mpos;
    bool Mpressed;
	bool Doppel;
	bool Links;
	bool Namen;
	int MaxC;
	QPixmap pix;

public slots:
	void ToggleNam();

signals:
	void UseTemp(QString, int);
	void NewPage(int, QString);
	void MovePage(int, int);
	void Click(int, int, int);

protected:
	virtual void contentsDropEvent(QDropEvent * e);
	virtual void contentsDragEnterEvent(QDragEnterEvent *e);
	virtual void contentsDragLeaveEvent(QDragLeaveEvent *e);
	virtual void contentsDragMoveEvent(QDragMoveEvent *e);
	virtual void contentsMouseReleaseEvent(QMouseEvent *m);
	virtual void contentsMousePressEvent(QMouseEvent* e);
	virtual void contentsMouseMoveEvent(QMouseEvent* e);
};

class TrashBin : public QLabel
{
    Q_OBJECT

public:
	TrashBin( QWidget * parent );
	~TrashBin() {};
	QPixmap Normal;
	QPixmap Offen;
	void dragEnterEvent( QDragEnterEvent *e );
	void dragLeaveEvent( QDragLeaveEvent * );
	void dropEvent( QDropEvent * e );

signals:
	void DelPage(int);
	void DelMaster(QString);
};

class SeitenPal : public ScrPaletteBase
{ 
    Q_OBJECT

public:
    SeitenPal(QWidget* parent);
    ~SeitenPal() {};
	//void keyPressEvent(QKeyEvent *k);
    //void closeEvent(QCloseEvent *ce);

    QSplitter* Splitter1;
    TrashBin* Trash;
	QLabel* TextLabel1;
	QLabel* TextLabel2;
    SeList* masterPageList;
    SeView* PageView;
	QCheckBox* facingPagesChk;
	QCheckBox* firstPageLeftChk;
	ScribusView *Vie;
	QPixmap pix;

public slots:
	void SetView(ScribusView *view);
	void DelMPage(QString tmp);
	void MPage(int r, int c);
	void GotoPage(int r, int c, int b);
	void DisablePal();
	void EnablePal();
	void handleFacingPagesChk();
	void handleFirstPageLeftChk();
	void RebuildTemp();
	void RebuildPage();
	void Rebuild();
	void selMasterPage();
	QPixmap CreateIcon(int nr, QPixmap ret);
	void languageChange();

signals:
	//void ToggleAllPalettes();
	void EditTemp(QString);
	void GotoSeite(int);
	//void Schliessen();

protected:
    QVBoxLayout* SeitenPalLayout;
    QHBoxLayout* Layout1;
    QVBoxLayout* Layout2;
    QVBoxLayout* Layout3;
    QVBoxLayout* Layout4;

protected slots:
	//virtual void reject();
};

#endif // SEITENPAL_H
