/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef PRVIEW_H
#define PRVIEW_H

#include <qdialog.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qscrollview.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include "scribusapi.h"

class PageSelector;
class ScribusDoc;
class ScribusView;
class ScImage;
class ScColor;
class QSpinBox;
class PrefsManager;

class QImage;
class QTable;


//! \brief Print Preview dialog
class SCRIBUS_API PPreview : public QDialog
{
	Q_OBJECT

public:
	/*!
	\author Franz Schmid
	\brief Create the Print Preview window
	\param parent QWidget *
	\param vin ScribusView *
	\param docu ScribusDoc *
	\param tiffSep tiff separations
	\param printer printer name
	\param pngAlpha int
	*/
	PPreview( QWidget* parent, ScribusView *vin, ScribusDoc *docu, int pngAlpha, int tiffSep, QString printer = "" );
	~PPreview() {};
	/*!
	\author Franz Schmid
	\brief Renders the Preview to a file on Disk
	\param Seite int page number
	\param Res int
	\retval int Flag indicating error
	*/
	int RenderPreview(int Seite, int Res);
	int RenderPreviewSep(int Seite, int Res);
	void blendImages(QImage &target, ScImage &source, ScColor col);
	static bool usePostscriptPreview(QString printerName);
	/*!
	\author Franz Schmid
	\brief Creates the Preview of the Actual Page
	\param Seite int page number
	\param Res int
	\retval Bild QPixmap print preview
	*/
	QPixmap CreatePreview(int Seite, int Res);
	PageSelector *PGSel;
	QCheckBox* AntiAlias;
	QCheckBox* AliasTr;
	QCheckBox* EnableCMYK;
	QCheckBox* EnableCMYK_C;
	QCheckBox* EnableCMYK_M;
	QCheckBox* EnableCMYK_Y;
	QCheckBox* EnableCMYK_K;
	QCheckBox* EnableGCR;
	QCheckBox* EnableOverprint;
	QScrollView* Anzeige;
	QLabel* Anz;
	QPushButton *closeButton;
	QPushButton *printButton;
	/*! scaling GUI */
	QLabel* scaleLabel;
	QComboBox* scaleBox;
	ScribusView *view;
	ScribusDoc *doc;
	int HavePngAlpha;
	int HaveTiffSep;
	int APage;
	int MPage;
	int SMode;
	int GsMajor;
	int GsMinor;
	bool CMode;
	bool GsAl;
	bool Trans;
	bool GMode;
	bool OMode;
	bool postscriptPreview;
	QMap<QString, int> sepsToFileNum;
	QMap<QString, QCheckBox*> flagsVisible;
	QTable* Table;

public slots:
	/*!
	\author Franz Schmid
	\brief Jump to newly selected page and create the new preview
	\param num int Page Number
	*/
	void ToSeite(int num);
	/*!
	\author Franz Schmid
	\brief Toggle anti-aliasing and create the new preview
	*/
	void ToggleAA();
	/*!
	\author Franz Schmid
	\brief Toggle transparency and create the new preview
	*/
	void ToggleTr();
	/*!
	\author Franz Schmid
	\brief Toggle overprint mode and create the new preview
	*/
	void ToggleOv();
	/*!
	\author Craig Bradney
	\brief When CMYK preview is toggled, (dis)enable the CMYK controls and create the new preview
	*/
	void ToggleCMYK();
	/*!
	\author Craig Bradney
	\brief If CMYK preview is enabled, create a new preview with the new CMYK plate settings
	*/
	void ToggleGCR();
	void ToggleCMYK_Colour();
	/*!
	\author Petr Vanek
	\date 09/03/2005
	\brief Recompute scaling factor of the preview image
	\param value spinbox value from signal
	*/
	void scaleBox_valueChanged(int value);

signals:
	void doPrint();

protected:
	/*! \brief Percentage value of the scaling widget */
	double scaleFactor;
	QVBoxLayout* PLayout;
	QHBoxLayout* Layout1;
	QVBoxLayout* Layout2;
	QVBoxLayout* Layout3;
	QVBoxLayout* Layout4;
	QHBoxLayout* Layout5;
	QHBoxLayout* Layout6;
	PrefsManager *prefsManager;
	
	void getUserSelection();
	void imageLoadError(QPixmap &);
};
#endif // QUERY_H
