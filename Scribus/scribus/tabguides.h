#ifndef TABGUIDES_H
#define TABGUIDES_H

#include "scribusapi.h"

#include <qvariant.h>
#include <qwidget.h>
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QButtonGroup;
class QRadioButton;
class QLabel;
class MSpinBox;
class QSpinBox;
class QPushButton;
class QCheckBox;
class QColor;

class SCRIBUS_API TabGuides : public QWidget
{
	Q_OBJECT

public:
	TabGuides( QWidget* parent, struct guidesPrefs *prefsData, struct typoPrefs *prefsData2, int unitIndex);
	~TabGuides() {};
	void restoreDefaults(struct guidesPrefs *prefsData, struct typoPrefs *prefsData2, int unitIndex);

	MSpinBox* majorSpace;
	MSpinBox* minorSpace;
	MSpinBox* snapDistance;
	QLabel* checkBaseline;
	QColor colorGuides;
	QColor colorMargin;
	QColor colorMajorGrid;
	QColor colorMinorGrid;
	QColor colorBaselineGrid;
	QGroupBox* checkGrid;
	QGroupBox* groupBox1;
	QGroupBox* groupBox2;
	QGroupBox* commonBox;
	QGroupBox* snapBox;
	QGroupBox* guideBox;
	QGroupBox* marginBox;
	QGroupBox* baselineBox;
	QGroupBox* baseGridBox;
	QButtonGroup* buttonGroup1;
	QRadioButton* inBackground;
	QRadioButton* inForeground;
	QLabel* textLabel4;
	QLabel* textLabel5;
	QLabel* textLabel6;
	QLabel* textLabel7;
	QLabel* textLabel8;
	QLabel* textLabel82;
	QLabel* checkMargin;
	QLabel* checkGuides;
	QPushButton* majorGridColor;
	QPushButton* minorGridColor;
	QPushButton* baselineColor;
	QPushButton* guideColor;
	QPushButton* marginColor;
	QSpinBox* grabDistance;
	QLabel* textLabel6a;
	QLabel* textLabel7a;
	MSpinBox* baseGrid;
	MSpinBox* baseOffset;
	QLabel* textLabel8a;

protected slots:
	virtual void changeMajorColor();
	virtual void changeMinorColor();
	virtual void changeBaselineColor();
	virtual void changeGuideColor();
	virtual void changeMarginColor();

protected:
	QVBoxLayout* tabGuidesLayout;
	QGridLayout* checkGridLayout;
	QGridLayout* groupBox1Layout;
	QGridLayout* groupBox2Layout;
	QHBoxLayout* commonBoxLayout;
	QGridLayout* snapBoxLayout;
	QHBoxLayout* guideBoxLayout;
	QHBoxLayout* marginBoxLayout;
	QGridLayout* baselineBoxLayout;
	QGridLayout* baseGridBoxLayout;
	QVBoxLayout* buttonGroup1Layout;
	QHBoxLayout* layout9;
	QHBoxLayout* layout9a;
	
	double unitRatio;
	QString unit;
	int precision;
};
#endif
