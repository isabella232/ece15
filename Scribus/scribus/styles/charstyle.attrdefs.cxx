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


//Syntax: ATTRDEF( datatype, gettername, name, defaultvalue)

ATTRDEF(int, fontSize, FontSize, 200)
ATTRDEF(int, fillShade, FillShade, 100)
ATTRDEF(int, strokeShade, StrokeShade, 100)
ATTRDEF(StyleFlag, effects, Effects, ScStyle_Default)
ATTRDEF(int, scaleH, ScaleH, 1000)
ATTRDEF(int, scaleV, ScaleV, 1000)
ATTRDEF(int, baselineOffset, BaselineOffset, 0)
ATTRDEF(int, shadowXOffset, ShadowXOffset, 0)
ATTRDEF(int, shadowYOffset, ShadowYOffset, 0)
ATTRDEF(int, outlineWidth, OutlineWidth, 0)
ATTRDEF(int, underlineOffset, UnderlineOffset, 0)
ATTRDEF(int, underlineWidth, UnderlineWidth, 0)
ATTRDEF(int, strikethruOffset, StrikethruOffset, 0)
ATTRDEF(int, strikethruWidth, StrikethruWidth, 0)
ATTRDEF(int, tracking, Tracking, 0)
ATTRDEF(QString, fillColor, FillColor, "undef")
ATTRDEF(QString, strokeColor, StrokeColor, "Black")
ATTRDEF(QString, language, Language, "")
ATTRDEF(ScFace, font, Font, ScFace::none())

