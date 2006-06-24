/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef NEWDOC_H
#define NEWDOC_H

#include <qdialog.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qspinbox.h>
#include <qstringlist.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qtabwidget.h>
#include <qframe.h>
#include <qlistbox.h>

#include "scribusapi.h"
#include "scribusstructs.h"

#include "customfdialog.h"

class PrefsManager;
class MarginWidget;
class PageLayouts;
class MSpinBox;
class CustomFDialog;


class SCRIBUS_API NewDoc : public QDialog
{
	Q_OBJECT

public:
	NewDoc( QWidget* parent, const QStringList& recentDocs, bool startUp = false );
	~NewDoc() {};
	void createNewDocPage();
	void createOpenDocPage();
	void createRecentDocPage();
	void setSize(QString gr);

	QTabWidget* tabWidget;
	QFrame* newDocFrame;
	PageLayouts* docLayout;
	QButtonGroup* ButtonGroup1_2;
	MarginWidget* marginGroup;
	QGroupBox* GroupBox3;
	QGroupBox* AutoFrame;
	QLabel* TextLabel1;
	QLabel* TextLabel2;
	QLabel* TextLabel3;
	QLabel* TextLabel4;
	QLabel* TextLabel1_2;
	QLabel* TextLabel1_3;
	QLabel* TextLabel1_3a;
	QLabel* TextLabel2_2;
	QLabel* TextLabel2_3;
	QComboBox* pageSizeComboBox;
	QComboBox* pageOrientationComboBox;
	QComboBox* unitOfMeasure;
	QCheckBox* startUpDialog;
	MSpinBox* Distance;
	QSpinBox* numberOfCols;
	//QSpinBox* PgNr;
	QSpinBox* PgNum;
	MSpinBox* widthMSpinBox;
	MSpinBox* heightMSpinBox;
	QFrame* openDocFrame;
	CustomFDialog *fileDialog;
	QFrame* recentDocFrame;
	QListBox* recentDocListBox;
	QPushButton* OKButton;
	QPushButton* CancelB;
	double unitRatio;
	int Orient;
	int precision;
	int choosenLayout;
	double pageWidth;
	double pageHeight;
	double Dist;
	QString unitSuffix;
	int unitIndex;
	int tabSelected;
	bool onStartup;

public slots:
	void setHeight(int v);
	void setWidth(int v);
	void setDist(int v);
	void setUnit(int u);
	void ExitOK();
	void setOrien(int ori);
	void setPGsize(const QString &);
	void setDS(int layout);
	/*! Opens document on doubleclick
	\param item QListViewItem sent by signall caller
	\author Petr Vanek <petr@yarpen.cz
	*/
	void recentDocListBox_doubleClicked(QListBoxItem * item);
	void openFile(const QString &);

protected:
	QVBoxLayout* TabbedNewDocLayout;
	QGridLayout* Layout4;
	QHBoxLayout* NewDocLayout;
	QVBoxLayout* Layout9;
	QVBoxLayout* ButtonGroup1_2Layout;
	QGridLayout* Layout6;
	QHBoxLayout* Layout5;
	QVBoxLayout* Layout10;
	QGridLayout* GroupBox3Layout;
	QHBoxLayout* GroupBox4Layout;
	QGridLayout* Layout2;
	QHBoxLayout* Layout1;
	QVBoxLayout* recentDocLayout;
	QString customText, customTextTR;
	PrefsManager* prefsManager;
	QStringList recentDocList;
};

#endif // NEWDOC_H
