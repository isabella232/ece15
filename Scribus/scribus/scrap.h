/****************************************************************************
** Form interface generated from reading ui file 'Bib.ui'
**
** Created: Sun Oct 14 19:47:43 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef BIBLIO_H
#define BIBLIO_H

#include <qdialog.h>
#include <qiconview.h>
#include <qframe.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qdragobject.h>
#include "scribusdoc.h"

class BibView : public QIconView
{
    Q_OBJECT

public:
    BibView( QWidget* parent, SCFonts &avail, preV *prefs);
    ~BibView() {};
    void AddObj(QString name, QString daten, QPixmap Bild);
    void SaveContents(QString name);
    void ReadContents(QString name);
    void RebuildView();
    QPixmap createPreview(QString data);
		void SetFarbe(QColor *tmp, QString farbe, int shad);
		void DrawPoly(QPainter *p, QPointArray pts, QColor BackF, struct CLBuf *OB);
		void DrawPolyL(QPainter *p, QPointArray pts, struct CLBuf *OB, float sca);

    struct Elem {QString Data;
    						 QPixmap Preview;
    						};
    QMap<QString,Elem> Objekte;
		QMap<QString,CMYKColor> Farben;
		QMap<QString,multiLine> MLineStyles;
		QValueList<uint> Segments;
    SCFonts EFonts;
  	preV *Prefs;

protected:
    virtual QDragObject *dragObject();
};

class Biblio : public QDialog
{ 
    Q_OBJECT

public:
    Biblio( QWidget* parent, SCFonts &avail, preV *prefs);
    ~Biblio() {};
    void closeEvent(QCloseEvent *ce);
    void AdjustMenu();
		void ObjFromMenu(QString text);

    QPopupMenu* pmenu;
    QPopupMenu* fmenu;
    QPopupMenu* vmenu;
    QMenuBar* menuBar;
    QFrame* Frame3;
    BibView* BibWin;
  	preV *Prefs;
    QString ScFilename;
    int fSave;
    int vS;
    int vM;
    int vB;

public slots:
    void Save();

private slots:
		void HandleMouse(QIconViewItem *ite);
		void DeleteObj(QString name, QIconViewItem *ite);
    void DropOn(QDropEvent *e);
    void SaveAs();
    void Load();
    void CloseWin();
    void NewLib();
    void SetPreview(int id);

protected:
    QVBoxLayout* BiblioLayout;
    QVBoxLayout* Frame3Layout;

signals:
		void Schliessen();
};

#endif // BIBLIO_H
