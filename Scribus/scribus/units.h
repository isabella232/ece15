/***************************************************************************
    begin                : Jan 2005
    copyright            : (C) 2005 by Craig Bradney
    email                : cbradney@zip.com.au
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef UNITS_H
#define UNITS_H

#include <qstring.h>
#include <qstringlist.h>

#define UNITCOUNT 5

enum Unit {
	SC_POINTS      = 0,
	SC_PT          = 0,
	SC_MILLIMETERS = 1,
	SC_MM          = 1,
	SC_INCHES      = 2,
	SC_IN          = 2,
	SC_PICAS       = 3,
	SC_P           = 3,
	SC_CENTIMETERS = 4,
	SC_CM          = 4,
	SC_CICERO      = 5,
	SC_C           = 5
};

const double unitGetRatioFromIndex(const int index);
const QString unitGetStrFromIndex(const int index);
const QString unitGetSuffixFromIndex(const int index);
const int unitGetDecimalsFromIndex(const int index);
const int unitGetPrecisionFromIndex(const int index);
const double unitValueFromString(const QString& value);
const Unit unitIndexFromString(const QString& value);
const QStringList unitGetTextUnitList();
const int unitGetMaxIndex();
const double mm2pts(double mm);
const double in2pts(double in);
const double p2pts(double p);
const double cm2pts(double cm);
const double c2pts(double c);
const double pts2mm(double pts);
const double pts2in(double pts);
const double pts2p(double pts);
const double pts2cm(double pts);
const double pts2c(double pts);
double pts2value(double Val, int unit);
double value2pts(double unitValue, int unit);
double value2value(double unitValue, int primaryUnit, int secondaryUnit);
//Ruler specific functions
double unitRulerGetIter1FromIndex(const int index);
double unitRulerGetIter2FromIndex(const int index);


#endif // UNITS_H

