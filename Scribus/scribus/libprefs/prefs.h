#ifndef PREFS_H
#define PREFS_H

#include <qdialog.h>
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qspinbox.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include <qframe.h>
#include <qcheckbox.h>
#include <qwidgetstack.h>
#include <qpixmap.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include "linecombo.h"
#include "linkbutton.h"
#include "scribusdoc.h"
#include "scfonts.h"
#include "mspinbox.h"
#include "scribus.h"
#include "fontcombo.h"

#include "langlist.h"

class Preferences : public QDialog
{
    	Q_OBJECT

public:
	Preferences( QWidget* parent, preV *Vor);
	~Preferences();

	//const QString getSelectedGUILang( void );
	QString selectedGUILang;
	double GetZeroFaktor();
	double GetMaxFaktor();
	void DrawRuler();

	QPushButton* buttonOK;
	QPushButton* buttonCancel;
	QWidgetStack* TabWidget3;
	QListBox* TabListe;
	QWidget* tab;
	QGroupBox* Mouse;
	QLabel* TextLabel1_2;
	QLabel* TextLabel1_2_2;
	QSpinBox* SpinBox3;
	QSpinBox* SpinBox3_2;
	QSpinBox* Recen;
	QButtonGroup* ButtonGroup1;
	QLabel* guiLangLabel;
	QLabel* TextGstil;
	QLabel* TextGstil2;
	QSpinBox* GFsize;
	QComboBox* guiLangCombo;
	QComboBox* GUICombo;
	QComboBox* UnitCombo;
	QGroupBox* GroupBox20;
	QGroupBox* GroupBox20a;
	QGroupBox* GroupBox20b;
	QGroupBox* GroupBox200;
	QLabel* PfadText;
	QLineEdit* Docs;
	QToolButton* FileC;
	QLabel* PfadText2;
	QLineEdit* ProPfad;
	QToolButton* FileC2;
	QLabel* PfadText3;
	QLineEdit* ScriptPfad;
	QToolButton* FileC3;
	QLabel* PfadText4;
	QLineEdit* TemplateDir;
	QToolButton* FileC4;
	QButtonGroup* ButtonGroup2;
	QButtonGroup* ButtonGroup5;
	QButtonGroup* ButtonGroup6;
	QRadioButton* RadioButton6;
	QRadioButton* RadioButton7;
	QRadioButton* RadioButton8;
	QRadioButton* RadioButton9;
	QWidget* tab_2;
	QGroupBox* GroupBox1;
	QLabel* TextLabel1;
	QLabel* TextLabel2;
	QLabel* TextLabel2g;
	MSpinBox* SpinBox1;
	MSpinBox* SpinBox2;
	MSpinBox* SpinBox2g;
	QGroupBox* GroupBox2;
	QLabel* TextLabel3;
	QLabel* TextLabel4;
	QLabel* TextLabel4a;
	QLabel* TextLabel4b;
	QLabel* TextLabel4c;
	QLabel* TextLabel4g;
	QLabel* TextLabel4ba;
	QPushButton* minColor;
	QPushButton* MaxColor;
	QPushButton* GuideColor;
	QPushButton* PapColor;
	QPushButton* RandColor;
	QPushButton* BaseColor;
	QWidget* tab_3;
	QWidgetStack* Fram;
	QLabel* TextLabel2_2;
	QLabel* TextLabel1_3;
	FontCombo* FontComb;
	QComboBox* SizeCombo;
	QComboBox* ForegroundT;
	QLabel* TextLabelT1;
	QLabel* TextLabel1_4;
	QWidget* tab_4;
	QGroupBox* GroupBox4_2;
	QLabel* TextLabel2_3_2;
	QLabel* TextLabel1_5_2;
	QSpinBox* VTiefW;
	QSpinBox* VTiefWSc;
	QGroupBox* GroupBox4;
	QLabel* TextLabel2_3;
	QLabel* TextLabel1_5;
	QSpinBox* VHochW;
	QSpinBox* VHochWSc;
	QGroupBox* GroupBox4_3;
	QLabel* TextLabel2_3_3;
	QSpinBox* SmallCaps;
	QGroupBox* GroupBox4_3a;
	QLabel* TextLabel2_3_3a;
	QSpinBox* AutoLineV;
	QToolButton* TextButton;
	QToolButton* BildButton;
	QToolButton* RectButton;
	QToolButton* OvalButton;
	QToolButton* LineButton;
	QToolButton* ZoomButton;
	QToolButton* PolyButton;
	QFrame* ToolFrame;
	QFrame* ToolFrame2;
	QLabel* TextLabelT21;
	QLabel* TextLabelT22;
	QLabel* TextLabelT23;
	QLabel* TextLabelT24;
	QLabel* TextLabelT25;
	QLabel* TextLabelT26;
	QComboBox* Foreground;
	QLabel* TextCol;
	QLabel* TextGap;
	QSpinBox* TextColVal;
	MSpinBox* TextGapVal;
	QSpinBox* Shade2;
	QComboBox* Background;
	QSpinBox* Shade;
	LineCombo* Linestyle;
	MSpinBox* LineW;
	QFrame* ToolFrame3;
	QLabel* TextLabelT31;
	QLabel* TextLabelT32;
	QLabel* TextLabelT35;
	QLabel* TextLabelT36;
	QComboBox* Foreground2;
	QSpinBox* Shade22;
	LineCombo* Linestyle2;
	MSpinBox* LineW2;
	QFrame* ToolFrame4;
	QLabel* TextLabelT42;
	QLabel* TextLabelT43;
	QLabel* TextLabelT44;
	QSpinBox* MinMag;
	QSpinBox* MaxMag;
	QSpinBox* StepMag;
	QButtonGroup* ToolFrame5;
	QLabel* TextLabelT51;
	QLabel* TextLabelT52;
	QLabel* TextLabelT53;
	QLabel* TextLabelT54;
	QRadioButton* FreeScale;
	QRadioButton* FrameScale;
	QCheckBox* Aspect;
	QSpinBox* XScale;
	QSpinBox* YScale;
	LinkButton* Kette;
	QComboBox* BackgroundP;
	QSpinBox* ShadeP;
	QLabel* TextLabelP;
	QWidget* tab_5;
	QGroupBox* Saving;
	QCheckBox* SaveAtQuit;
	QGroupBox* Preview;
	QComboBox* PreviewSize;
	QFrame* Frame6;
	QWidget* tab_6;
	QGroupBox* GroupBox10;
	QCheckBox* SidebySide;
	QCheckBox* RandFarb;
	QFrame* ToolFrame6;
	QLabel* T6_Text1;
	QSpinBox* T6_Ecken;
	QCheckBox* T6_Konvex;
	QLabel* T6_Text2;
	QSpinBox* T6_Faktor;
	QSlider* T6_Slider1;
	QLabel* T6_Preview;
	QLabel* T6_Text2_2;
	QSpinBox* T6_Faktor2;
	QSlider* T6_Slider2;
	QWidget* tab_7;
	QButtonGroup* GroupSize;
	QLabel* GZText2;
	QComboBox* GZComboF;
	QComboBox* GZComboO;
	QLabel* GZText1;
	QLabel* GZText3;
	QLabel* GZText4;
	MSpinBox* Breite;
	MSpinBox* Hoehe;
	QCheckBox* Doppelseiten;
	QCheckBox* Linkszuerst;
	QGroupBox* GroupRand;
	QLabel* GRText3;
	MSpinBox* TopR;
	MSpinBox* BottomR;
	MSpinBox* RightR;
	MSpinBox* LeftR;
	QLabel* GRText2;
	QLabel* GRText1;
	QLabel* GRText4;
	QCheckBox *UsePDFTrans;
	QGroupBox* GroupAS;
	QCheckBox* ASon;
	QLabel* ASText;
	QSpinBox* ASTime;
	QGroupBox* CaliGroup;
	QLabel* CaliText;
	QLabel* CaliRuler;
	QSlider* CaliSlider;
	QLabel* CaliAnz;
 	QWidget* ExtTool;
	QGroupBox* groupGS;
	QLabel* GSText;
	QLineEdit* GSName;
	QCheckBox* GSantiText;
	QCheckBox* GSantiGraph;
	QGroupBox* groupGimp;
	QLabel* GimpText;
	QLineEdit* GimpName;
	QWidget* Misc;
	QGroupBox* groupPrint;
	QCheckBox* ClipMarg;
	QCheckBox* DoGCR;
	MSpinBox* BaseGrid;
	QLabel* TextLabel2_3_3b;
	MSpinBox* BaseOffs;
	QLabel* TextLabel2_3_3c;
	
	SCFonts *fon; // can't use a reference, and can't copy whole structure...
	double Umrech;
	QPixmap* Pre;
	double PFactor;
	QColor Cmin;
	QColor Cmax;
	QColor Crand;
	QColor Cpaper;
	QColor Cgui;
	QColor Cbase;
	double Pagebr;
	double Pageho;
	double RandT;
	double RandB;
	double RandL;
	double RandR;
	int Einheit;
	double DisScale;
	ScribusApp *ap;


public slots:

	virtual void changeMaColor();
	virtual void changeMicolor();
	void ChangeDocs();
	void ChangeProfs();
	void ChangeScripts();
	void ChangeTemplates();
	void ChangeScaling();
	void ChangeGrid();
	void setDS();
	void setBreite(int v);
	void setHoehe(int v);
	void setTop(int v);
	void setBottom(int v);
	void setLeft(int v);
	void setRight(int v);
	void setSize(int gr);
	void setOrien(int ori);
	void changePapColor();
	void changeRandColor();
	void changeGuideColor();
	void changeBaseColor();
	void SetSample();
	void SetTool();
	void ToggleKette();
	void HChange();
	void VChange();
	void UnitChange();
	void UpdatePreView();
	double GetFaktor();
	void ValFromSpin(int a);
	void ValFromSpin2(int a);
	void SetDisScale();

protected:
	QVBoxLayout* PrefsLayout;
	QHBoxLayout* PrefsLayout2;
	QGridLayout* tabLayout;
	QGridLayout* ButtonGroup1Layout;
	QHBoxLayout* GroupBox20Layout;
	QHBoxLayout* GroupBox20aLayout;
	QGridLayout* GroupBox20bLayout;
	QGridLayout* GroupBox200Layout;
	QHBoxLayout* MouseLayout;
	QGridLayout* Layout5;
	QGridLayout* tabLayout_2;
	QHBoxLayout* ButtonGroup5Layout;
	QHBoxLayout* ButtonGroup6Layout;
	QVBoxLayout* Layout7;
	QVBoxLayout* Layout18;
	QHBoxLayout* GroupBox1Layout;
	QGridLayout* Layout10;
	QHBoxLayout* GroupBox2Layout;
	QGridLayout* Layout11;
	QGridLayout* tabLayout_3;
	QHBoxLayout* GroupBox4_2Layout;
	QGridLayout* Layout12;
	QHBoxLayout* GroupBox4Layout;
	QGridLayout* Layout13;
	QHBoxLayout* GroupBox4_3Layout;
	QHBoxLayout* Layout14;
	QGridLayout* GroupBox4_3aLayout;
	QHBoxLayout* tabLayout_4;
	QHBoxLayout* ButtonGroup2Layout;
	QGridLayout* Layout16;
	QHBoxLayout* ToolFrameLayout;
	QHBoxLayout* ToolFrame2Layout;
	QHBoxLayout* ToolFrame3Layout;
	QHBoxLayout* ToolFrame4Layout;
	QHBoxLayout* ToolFrame5Layout;
	QGridLayout* Layout15;
	QGridLayout* Layout15a;
	QGridLayout* Layout15b;
	QGridLayout* Layout15c;
	QGridLayout* Layout15d;
	QGridLayout* tabLayout_5;
	QHBoxLayout* SavingLayout;
	QHBoxLayout* PreviewLayout;
	QHBoxLayout* tabLayout_6;
	QHBoxLayout* Layout_6b;
	QVBoxLayout* GroupBox10Layout;
	QHBoxLayout* Layout3;
	QHBoxLayout* PolygonPropsLayout;
	QHBoxLayout* T6_Layout11;
	QVBoxLayout* T6_Layout10;
	QHBoxLayout* T6_Layout2;
	QHBoxLayout* T6_Layout9;
	QVBoxLayout* T6_Layout8;
	QHBoxLayout* T6_Layout7;
	QHBoxLayout* T6_Layout9_2;
	QVBoxLayout* T6_Layout8_2;
	QHBoxLayout* T6_Layout7_2;
	QHBoxLayout* tabLayout_7;
	QVBoxLayout* Layout21;
	QVBoxLayout* Layout21b;
	QVBoxLayout* GroupSizeLayout;
	QGridLayout* Layout6;
	QHBoxLayout* Layout5_2;
	QHBoxLayout* Layout8;
	QGridLayout* GroupRandLayout;
	QGridLayout* GroupASLayout;
	QVBoxLayout* CaliGroupLayout;
	QHBoxLayout* layout15ca;
	QVBoxLayout* ExtToolLayout;
	QVBoxLayout* groupGSLayout;
	QHBoxLayout* GSlayout;
	QHBoxLayout* groupGimpLayout;
	QVBoxLayout* MiscLayout;
	QVBoxLayout* groupPrintLayout;

private slots:
	void setSelectedGUILang( const QString &newLang );

private:
	LanguageManager langMgr;	
};

#endif // PREFS_H
