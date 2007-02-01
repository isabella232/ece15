/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          pageitem.cpp  -  description
                             -------------------
    begin                : Sat Apr 7 2001
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

#include "pageitem_textframe.h"
#include "pageitem_textframe.moc"
#include <qpainter.h>
#include <qpen.h>
#include <qfont.h>
#include <qregion.h>
#include <qpoint.h>
#include <qfileinfo.h>
#include <qdrawutil.h>
#include <qbitmap.h>
#include <qregexp.h>
#include <qmessagebox.h>
#include <cmath>
#include <cassert>

#include "hyphenator.h"
#include "mpalette.h"
#include "page.h"
#include "pageitem.h"
#include "prefsmanager.h"
#include "scpaths.h"
#include "scribus.h"
#include "scribusstructs.h"
#include "scribusdoc.h"
#include "selection.h"
#include "undomanager.h"
#include "undostate.h"
#include "scconfig.h"
#include "commonstrings.h"
#include "guidemanager.h"

#include "util.h"
#include "text/nlsconfig.h"
#ifdef HAVE_CAIRO
#include <cairo.h>
#endif

using namespace std;

PageItem_TextFrame::PageItem_TextFrame(ScribusDoc *pa, double x, double y, double w, double h, double w2, QString fill, QString outline)
	: PageItem(pa, PageItem::TextFrame, x, y, w, h, w2, fill, outline)
{
	unicodeTextEditMode = false;
	unicodeInputCount = 0;
	unicodeInputString = "";
}


static QRegion itemShape(PageItem* docItem, ScribusView* view, double xOffset, double yOffset)
{
	QRegion res;
	QPainter pp;
	pp.begin(view->viewport());
	pp.translate(docItem->xPos() - xOffset, docItem->yPos() - yOffset);
	pp.rotate(docItem->rotation());
	if (docItem->textFlowUsesBoundingBox())
	{
		QPointArray tcli(4);
		tcli.setPoint(0, QPoint(0,0));
		tcli.setPoint(1, QPoint(qRound(docItem->width()), 0));
		tcli.setPoint(2, QPoint(qRound(docItem->width()), qRound(docItem->height())));
		tcli.setPoint(3, QPoint(0, qRound(docItem->height())));
		res = QRegion(pp.xForm(tcli));
	}
	else
	{
		if ((docItem->textFlowUsesContourLine()) && (docItem->ContourLine.size() != 0))
		{
			QValueList<uint> Segs;
			QPointArray Clip2 = FlattenPath(docItem->ContourLine, Segs);
			res = QRegion(pp.xForm(Clip2));
		}
		else
			res = QRegion(pp.xForm(docItem->Clip));
	}
	pp.end();
	return  res;
}

QRegion PageItem_TextFrame::availableRegion(QRegion clip)
{
	QRegion result(clip);
	if (!isEmbedded)
	{
		int LayerLev = m_Doc->layerLevelFromNumber(LayerNr);
		uint docItemsCount=m_Doc->Items->count();
		Page* Mp=0;
		Page* Dp=0;
		PageItem* docItem=0;
		int LayerLevItem;
		if (!OnMasterPage.isEmpty())
		{
			if ((savedOwnPage == -1) || (savedOwnPage >= signed(m_Doc->Pages->count())))
				return result;
			Mp = m_Doc->MasterPages.at(m_Doc->MasterNames[OnMasterPage]);
			Dp = m_Doc->Pages->at(savedOwnPage);
			for (uint a = 0; a < m_Doc->MasterItems.count(); ++a)
			{
				docItem = m_Doc->MasterItems.at(a);
				LayerLevItem = m_Doc->layerLevelFromNumber(docItem->LayerNr);
				if (((docItem->ItemNr > ItemNr) && (docItem->LayerNr == LayerNr)) || (LayerLevItem > LayerLev) && (m_Doc->layerFlow(docItem->LayerNr)))
				{
					if (docItem->textFlowAroundObject())
					{
						result = result.subtract(itemShape(docItem, m_Doc->view(),  Mp->xOffset() - Dp->xOffset(), Mp->yOffset() - Dp->yOffset()));
					}
				}
			} // for all masterItems
			if (!m_Doc->masterPageMode())
			{
				for (uint a = 0; a < docItemsCount; ++a)
				{
					docItem = m_Doc->Items->at(a);
					Mp = m_Doc->MasterPages.at(m_Doc->MasterNames[OnMasterPage]);
					Dp = m_Doc->Pages->at(OwnPage);
					if ((docItem->textFlowAroundObject()) && (docItem->OwnPage == OwnPage))
					{
						result = result.subtract(itemShape(docItem, m_Doc->view(), Mp->xOffset() - Dp->xOffset(), Mp->yOffset() - Dp->yOffset()));
					}
				} // for all docItems
			} // if (! masterPageMode)
		} // if (!OnMasterPage.isEmpty())
		else
		{
			for (uint a = 0; a < docItemsCount; ++a)
			{
				docItem = m_Doc->Items->at(a);
				LayerLevItem = m_Doc->layerLevelFromNumber(docItem->LayerNr);
				if (((docItem->ItemNr > ItemNr) && (docItem->LayerNr == LayerNr)) || (LayerLevItem > LayerLev) && (m_Doc->layerFlow(docItem->LayerNr)))
				{
					 if (docItem->textFlowAroundObject())
						result = result.subtract(itemShape(docItem, m_Doc->view(), 0, 0));
				}
			} // for all docItems
			} // if(OnMasterPage.isEmpty()		
	} // if(!Embedded)
	return result;
}


void PageItem_TextFrame::setShadow()
{
	if (OnMasterPage.isEmpty())
		return;
	
	QString newShadow = m_Doc->masterPageMode() ? OnMasterPage : QString::number(OwnPage);
	if (newShadow != currentShadow) {
		if (currentShadow == OnMasterPage) {
			// masterpage was edited, clear all shadows
			shadows.clear();
		}
		if (!shadows.contains(newShadow)) {
			if (!shadows.contains(OnMasterPage)) {
				shadows[OnMasterPage] = itemText;
//				const ParagraphStyle& pstyle(shadows[OnMasterPage].paragraphStyle(0));
//				qDebug(QString("Pageitem_Textframe: style of master: %1 align=%2").arg(pstyle.parent()).arg(pstyle.alignment()));
//				qDebug(QString("Pageitem_Textframe: shadow itemText->%1").arg(OnMasterPage));
			}
			if (newShadow != OnMasterPage) {
				shadows[newShadow] = shadows[OnMasterPage].copy();
//				const ParagraphStyle& pstyle(shadows[newShadow].paragraphStyle(0));
//				qDebug(QString("Pageitem_Textframe: style of shadow copy: %1 align=%2").arg(pstyle.parent()).arg(pstyle.alignment()));
			}
//			qDebug(QString("Pageitem_Textframe: shadow %1<-%2").arg(newShadow).arg(OnMasterPage));
		}
		itemText = shadows[newShadow];
//		const ParagraphStyle& pstyle(itemText.paragraphStyle(0));
//		qDebug(QString("Pageitem_Textframe: style of shadow: %1 align=%2").arg(pstyle.parent()).arg(pstyle.alignment()));
		invalid = true;
		currentShadow = newShadow;
	}
}
		
#ifdef NLS_PROTO
#include "text/pageitem_textframe.cpp"
#else

static void dumpIt(const ParagraphStyle& pstyle, QString indent = QString("->"))
{
	qDebug(QString("%6%1/%2 @ %3: %4--%5 linespa%6: %7 align%8")
		   .arg(pstyle.name())
		   .arg(pstyle.parent())
		   .arg( (unsigned long int) &pstyle)
		   .arg(pstyle.leftMargin())
		   .arg(pstyle.rightMargin())
		   .arg(indent)
		   .arg(pstyle.lineSpacingMode())
		   .arg(pstyle.lineSpacing())
		   .arg(pstyle.alignment()));
	static QString more("  ");
	if (pstyle.hasParent())
		dumpIt(*dynamic_cast<const ParagraphStyle*>(pstyle.parentStyle()), more + indent);
}


static void layoutDropCap(GlyphLayout layout, double curX, double curY, double offsetX, double offsetY, double dropCapDrop) 
{	
}


static void fillInTabLeaders(StoryText & itemText, LineSpec & curLine)
{
	// fill in tab leaders
	double xPos = curLine.x;
	for (int ti= curLine.firstItem; ti < curLine.lastItem; ++ti)
	{
		ScText * hl = itemText.item(ti);
		if (hl->ch[0] == SpecialChars::TAB) 
		{
			GlyphLayout * tglyph = hl->glyph.more;
			
			if (!tglyph)
				continue;
			
			const CharStyle & charStyle(itemText.charStyle(ti));
			double wt   = charStyle.font().glyphWidth(tglyph->glyph, charStyle.fontSize() * tglyph->scaleV / 10.0);
			double len  = hl->glyph.xadvance;
			int count   = static_cast<int>(len / wt);
			double sPos = -len;
			tglyph->xoffset = sPos;
//			qDebug(QString("tab leaders: %1 %2 width=%3 count=%4").arg(sPos).arg(curLine.y).arg(wt).arg(count));
			for (int cx = 1; cx < count; ++cx)
			{
				// clone fillchar
				tglyph->grow();
				*(tglyph->more) = *tglyph;
				tglyph->more->more = NULL;
				tglyph = tglyph->more;
				tglyph->xoffset =  sPos + wt * cx;
			}
		}
		xPos += hl->glyph.wide();
	}
}


static bool isBreakingSpace(QChar c)
{
	static const QChar blnk(' ');
	return c == blnk || c == SpecialChars::ZWSPACE;
}

static bool isExpandingSpace(QChar c)
{
	static const QChar blnk(' ');
	return c == blnk || c == SpecialChars::NBSPACE;
}

static bool isBreak(QChar c, bool includeColBreak = true)
{
	return (c == SpecialChars::PARSEP 
			|| c == SpecialChars::LINEBREAK 
			|| c == SpecialChars::FRAMEBREAK 
			|| (includeColBreak && c == SpecialChars::COLBREAK));
}


enum TabStatus {
	TabNONE    = 0,
	TabLEFT    = TabNONE,
	TabRIGHT   = 1,
	TabPOINT   = 2,
	TabCOMMA   = 3,
	TabCENTER  = 4
};

struct TabControl {
	bool   active;
	int    status;
	int    charIndex;
	double xPos;
	QChar  fillChar;
};

struct LineControl {
	LineSpec line;
	int      itemsInLine;
	int      hyphenCount;
	double   colWidth;
	double   colGap;
	double   colLeft;
	double   colRight;
	int      column;
	bool     startOfCol;
	double   ascend;
	double   descend;
	double   width;
	double   xPos;
	double   yPos;
	int      breakIndex;
	double   breakXPos;
	
	
	void init(double w, double h, const MarginStruct& extra, double lCorr)
	{
		insets = extra;
		lineCorr = lCorr;
		frameWidth = w;
		frameHeight = h;
	}
	
	void initColumns(double width, double gap)
	{
		column = 0;
		colWidth = width;
		colGap = gap;
	}
	
	void nextColumn(double asce)
	{
		startOfCol = true;
		colLeft = (colWidth + colGap) * column + insets.Left + lineCorr;
		colRight = colLeft + colWidth;
//		colRight += insets.Right + lineCorr; //???
		xPos = colLeft;
		yPos = asce + insets.Top + lineCorr + 1;
	}
	
	bool isEndOfCol(double morespace = 0)
	{
		return yPos + morespace + insets.Bottom + lineCorr > frameHeight;
	}
	
	void startLine(int first)
	{		
		itemsInLine = 0;
		line.x = xPos;
		line.y = yPos;
		line.firstItem = first;
		line.ascent = 10;
		line.descent = 0;
		line.width = 0;
		line.naturalWidth = 0;
		breakIndex = -1;
		breakXPos = 0;
	}
	
	void rememberBreak(int index, double pos)
	{
		breakIndex = index;
		breakXPos = pos;
	}
	
	
	void breakLine(const StoryText& itemText, int last)
	{
		breakIndex = last;
		breakXPos  = line.x;
		for (int j = line.firstItem; j <= last; ++j)
			if ( (itemText.item(j)->effects() & ScStyle_SuppressSpace) == 0)
				breakXPos += itemText.item(j)->glyph.wide();
	}
	
	void finishLine(double endX)
	{
		line.lastItem = breakIndex;
		line.naturalWidth = breakXPos - line.x;
		line.width = endX - line.x;
	}
	
	
	bool isEndOfLine(double moreSpace = 0)
	{
//		return xPos + insets.Right + lineCorr + moreSpace > colRight;
		return xPos + lineCorr + moreSpace > colRight;
	}
	
	double startOfLine(const QRegion& shape, const QPainter& pf2, double ascent, double descent, double morespace)
	{
		QPoint pt1, pt2;
		double tmpX = xPos;
		pt1 = QPoint(static_cast<int>(ceil(tmpX)), static_cast<int>(yPos + descent));
		pt2 = QPoint(static_cast<int>(ceil(tmpX)), static_cast<int>(ceil(yPos - ascent)));
		// increase pt1/pt2 until i-beam reaches end of line
		while ((!shape.contains(pf2.xForm(pt1))) || (!shape.contains(pf2.xForm(pt2))))
		{
			tmpX++;
			if (isEndOfLine(morespace))
			{
				return tmpX;
			}
			pt1 = QPoint(static_cast<int>(ceil(tmpX)), static_cast<int>(yPos + descent));
			pt2 = QPoint(static_cast<int>(ceil(tmpX)), static_cast<int>(ceil(yPos - ascent)));
		}
		return tmpX;
	}
	
	double endOfLine(const QRegion& shape, const QPainter& pf2, double ascent, double descent, double morespace = 0)
	{
		double EndX = floor(QMAX(line.x, breakXPos - 1));
		QPoint pt1, pt2;
		//	qDebug(QString("endx start=%1, hl is '%2'").arg(EndX).arg(hl->ch));
		do {
			EndX += 0.125;
			pt1 = QPoint(qRound(EndX + insets.Right), static_cast<int>(yPos+descent));
			pt2 = QPoint(qRound(EndX + insets.Right), static_cast<int>(ceil(yPos-ascent)));
		} while 
//			(   (EndX + lineCorr  + insets.Right < colRight - morespace)
			(   (EndX + lineCorr  < colRight - morespace)
			  && shape.contains(pf2.xForm(pt1))
			  && shape.contains(pf2.xForm(pt2)) 
			  );
		
		return EndX;
	}
	
	
private:
	double frameWidth;
	double frameHeight;
	MarginStruct insets;
	double lineCorr;
};



static void justifyLine(StoryText& itemText, LineSpec& line)
{
	// count the available spaces
	int aSpa = 0;
	double OFs2;
	for (int sof = line.firstItem; sof < line.lastItem; ++sof)
	{
		if (isExpandingSpace(itemText.text(sof))
			&& ! (itemText.item(sof)->effects() & ScStyle_SuppressSpace)
			)
			aSpa++;
	}
	if (aSpa != 0)
		OFs2 = (line.width - line.naturalWidth) / aSpa;
	else
		OFs2 = 0;
	
	// distribute whitespace on spaces
	for (int yof = line.firstItem; yof < line.lastItem; ++yof)
	{
		if (isExpandingSpace(itemText.text(yof)) 
			&& ! (itemText.item(yof)->effects() & ScStyle_SuppressSpace)
			)
		{
			itemText.item(yof)->glyph.last()->xadvance += OFs2;
		}
	}
}


static void indentLine(LineSpec& line, double leftIndent)
{
	line.x += leftIndent;
	line.width -= leftIndent;
}

static double opticalLeftMargin(const StoryText& itemText, const LineSpec& line)
{
	int b = line.firstItem;
	while (b < line.lastItem && (itemText.item(b)->effects() & ScStyle_SuppressSpace))
		   ++b;
	
	double chs = itemText.charStyle(b).fontSize() * (itemText.charStyle(b).scaleH() / 1000.0);
	QChar chr = itemText.text(b);
	double leftCorr = itemText.charStyle(b).font().realCharWidth(chr, chs / 10.0);
	if (QString("'´`").find(chr) >= 0
		|| chr == QChar(0x2018)
		|| chr == QChar(0x2019)
		|| chr == QChar(0x201a)
		|| chr == QChar(0x201b)
		|| chr == QChar(0x2039)
		|| chr == QChar(0x203a)
		)
		leftCorr *= -0.7;
	else if (QString("\"").find(chr) >= 0
			 || chr == QChar(0x00ab)
			 || chr == QChar(0x00bb)
			 || chr == QChar(0x201c)
			 || chr == QChar(0x201d)
			 || chr == QChar(0x201e)
			 || chr == QChar(0x201f)
			 ) 
		leftCorr *= -0.5;
	else {
		leftCorr = itemText.charStyle(b).font().charWidth(QChar(' '), chs / 10.0, chr);
		leftCorr -= itemText.charStyle(b).font().charWidth(QChar(' '), chs / 10.0);
//				double leftCorr2 = itemText.charStyle(a).font().charWidth(QChar('K'), chs / 10.0, chr);
//				leftCorr2 -= itemText.charStyle(a).font().charWidth(QChar('K'), chs / 10.0);
//				leftCorr = QMIN(leftCorr, leftCorr2);
	}
	return leftCorr;
}


static double opticalRightMargin(const StoryText& itemText, const LineSpec& line)
{
	int b = line.lastItem;
	while (b > line.firstItem && 
		   (isBreakingSpace(itemText.text(b)) || isBreak(itemText.text(b)))
		   )
		--b;
	if (b >= line.firstItem) 
	{
		double chs = itemText.charStyle(b).fontSize() * (itemText.charStyle(b).scaleH() / 1000.0);
		QChar chr = (itemText.item(b)->effects() & ScStyle_SmartHyphenVisible) ? 
			QChar('-') : itemText.text(b);
		double rightCorr = itemText.charStyle(b).font().realCharWidth(chr, chs / 10.0);
		if (QString("-,.`´'~").find(chr) >= 0
			|| chr == QChar(0x2018)
			|| chr == QChar(0x2019)
			|| chr == QChar(0x201a)
			|| chr == QChar(0x201b)
			|| chr == QChar(0x2039)
			|| chr == QChar(0x203a)
			|| chr == QChar(0x2032)
			)
			rightCorr *= 0.7;
		else if (QString(";:\"").find(chr) >= 0
				 || chr == QChar(0x00ab)
				 || chr == QChar(0x00bb)
				 || chr == QChar(0x201c)
				 || chr == QChar(0x201d)
				 || chr == QChar(0x201e)
				 || chr == QChar(0x201f)
				 || chr == QChar(0x2013)
				 || chr == QChar(0x2033)
				 )
			rightCorr *= 0.5;
		else {
			rightCorr = itemText.charStyle(b).font().charWidth(chr, chs / 10.0);
			rightCorr -= itemText.charStyle(b).font().charWidth(chr, chs / 10.0, QChar('.'));
		}
		return rightCorr;
	}
	return 0.0;
}


void PageItem_TextFrame::layout() 
{
	if (BackBox != NULL && BackBox->invalid) {
//		qDebug("textframe: len=%d, going back", itemText.length());
		invalid = false;
		PageItem_TextFrame* prevInChain = dynamic_cast<PageItem_TextFrame*>(BackBox);
		if (!prevInChain)
			qDebug(QString("layout(): backBox=%1").arg((ulong)BackBox));
		else 
			BackBox->layout();
		return;
	}
	else if (!invalid && OnMasterPage.isEmpty()) {
//		qDebug(QString("textframe: len=%1, invalid=%2 OnMasterPage=%3: no relayout").arg(itemText.length()).arg(invalid).arg(OnMasterPage));
		return;
	}
//	qDebug(QString("textframe(%1,%2): len=%3, start relayout at %4").arg(Xpos).arg(Ypos).arg(itemText.length()).arg(firstInFrame()));
	ScribusView* view = m_Doc->view();
	QPainter pf2;
	PageItem *nextItem;
	QPoint pt1, pt2;
	QRegion cm;
	double chs, chsd = 0;
	double oldCurY, EndX, OFs, wide, kernVal;
	QString chstr;
	ScText *hl;
	ParagraphStyle style;
	int /*ParagraphStyle::OpticalMarginType*/ opticalMargins = ParagraphStyle::OM_None;
	
	bool outs = false;
	bool fBorder = false;
	bool goNoRoom = false;
	bool goNextColumn = false;
	
	TabControl tabs;
	tabs.active    = false;     // RTab
	tabs.status    = TabNONE;   // TabCode
	tabs.charIndex = -1;        // StartRT
	tabs.xPos      = 0;         // RTabX

	QValueList<ParagraphStyle::TabRecord> tTabValues;
	tTabValues.clear();
	
	bool DropCmode = false;
	bool AbsHasDrop = false;
	double desc=0, asce=0, maxDY=0, desc2=0, maxDX=0;
	int DropLines = 0;
	double DropCapDrop = 0;
	
	itemText.clearLines();

	double lineCorr = 0;
	if (lineColor() != CommonStrings::None)
		lineCorr = m_lineWidth / 2.0;
	
	// TODO: refactor this into PageItem
	MarginStruct extra;
	extra.Top = TExtra;
	extra.Left = Extra;
	extra.Right = RExtra;
	extra.Bottom = BExtra;

	LineControl current;
	current.init(Width, Height, extra, lineCorr);
	current.initColumns(columnWidth(), ColGap);
	current.hyphenCount = 0;
				 
	// dump styles
/*	
	for (int i=0; i < itemText.nrOfParagraphs(); ++i) {
		const ParagraphStyle& pstyle(itemText.paragraphStyle(itemText.endOfParagraph(i)));
		qDebug(QString("par %1:").arg(i));
		dumpIt(pstyle);
	}
	qDebug(QString("default:"));
	dumpIt(itemText.defaultStyle());
*/	
	
	pf2.begin(view->viewport());
	pf2.translate(Xpos, Ypos);
	pf2.rotate(Rot);
	
	setShadow();
	if ((itemText.length() != 0)) // || (NextBox != 0))
	{
		// determine layout area
		QRegion cl = availableRegion(QRegion(pf2.xForm(Clip)));
		
		if (imageFlippedH())
		{
			pf2.translate(Width, 0);
			pf2.scale(-1, 1);
		}
		if (imageFlippedV())
		{
			pf2.translate(0, Height);
			pf2.scale(1, -1);
		}
		
		current.nextColumn(0);

		// find start of first line
		if (firstInFrame() < itemText.length())
		{
			hl = itemText.item(firstInFrame());
			style = itemText.paragraphStyle(firstInFrame());
//			qDebug(QString("style @0: %1 -- %2, %4/%5 char: %3").arg(style.leftMargin()).arg(style.rightMargin())
//				   .arg(style.charStyle().asString()).arg(style.name()).arg(style.parent()?style.parent()->name():""));
			if (style.hasDropCap())
			{
				if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
					chs = qRound(m_Doc->typographicSettings.valueBaseGrid  * style.dropCapLines() * 10);
				else
					chs = qRound(style.lineSpacing() * style.dropCapLines() * 10);
			}
			else 
				chs = hl->fontSize();
			desc2 = -hl->font().descent(chs / 10.0);
			current.yPos = extra.Top + lineCorr;
		}
		else // empty itemText:
		{
			desc2 = -itemText.defaultStyle().charStyle().font().descent(itemText.defaultStyle().charStyle().fontSize() / 10.0);
			current.yPos = itemText.defaultStyle().lineSpacing() + extra.Top+lineCorr-desc2;
		}
		current.startLine(firstInFrame());
		outs = false;
		OFs = 0;
		MaxChars = 0;
		for (int a = firstInFrame(); a < itemText.length(); ++a)
		{
			hl = itemText.item(a);
			if (a > 0 && itemText.text(a-1) == SpecialChars::PARSEP)
				style = itemText.paragraphStyle(a);
			if (current.itemsInLine == 0)
				opticalMargins = style.opticalMargins();
			
//			qDebug(QString("style pos %1: %2 (%3)").arg(a).arg(style.alignment()).arg(style.parent()));
			const CharStyle& charStyle = itemText.charStyle(a);
			if (!charStyle.parent().isEmpty())
			{
//				qDebug(QString("charstyle pos %1: %2 (%3 %4 %5 %6 %7 %8 %9)").arg(a).arg(charStyle.parent())
//					   .arg((uint)charStyle.parentStyle()).arg(charStyle.font().scName()).arg(charStyle.fontSize())
//					   .arg(charStyle.fillColor()).arg(charStyle.strokeColor()).arg(charStyle.parentStyle()->name()).arg((uint)charStyle.parentStyle()->parentStyle()));
			}				
//			qDebug(QString("charstyle pos %1: %2 (%3)").arg(a).arg(charStyle.asString()).arg(charStyle.fontSize()));
//			qDebug(QString("style @%6: %1 -- %2, %4/%5 char: %3").arg(style.leftMargin()).arg(style.rightMargin())
//				   .arg(style.charStyle().asString()).arg(style.name()).arg(style.parent())
//				   .arg(a));

			chstr = ExpandToken(a);
//			qDebug(QString("expanded token: '%1'").arg(chstr));
			if (chstr.isEmpty())
				continue;
			if (style.lineSpacingMode() == ParagraphStyle::AutomaticLineSpacing)
				style.setLineSpacing(charStyle.font().height(charStyle.fontSize() / 10.0));
			// find out about par gap and dropcap
			if (a == firstInFrame())
			{
				if (BackBox != 0)
				{
					nextItem = BackBox;
					while (nextItem != 0)
					{
						if (nextItem->frameDisplays(a-1))
						{
							if (nextItem->itemText.text(a-1) == SpecialChars::PARSEP)
							{
								current.yPos += style.gapBefore();
								if (chstr[0] != SpecialChars::PARSEP)
								{
									DropCmode = style.hasDropCap();
									if (DropCmode)
										DropLines = style.dropCapLines();
								}
								else
									DropCmode = false;
								break;
							}
							else
								break;
						}
						nextItem = nextItem->prevInChain();
					}
				}
				else
				{
					if (chstr[0] != SpecialChars::PARSEP)
					{
						DropCmode = style.hasDropCap();
						if (DropCmode)
							DropLines = style.dropCapLines();
					}
					else
						DropCmode = false;
					current.yPos += style.gapBefore();
				}
			}
			{  // local block for 'fl'
				StyleFlag fl = hl->effects();
				fl &= ~ScStyle_DropCap;
				fl &= ~ScStyle_SmartHyphenVisible;
				hl->setEffects(fl);
			}
			// No space at begin of line, unless at begin of par (eeks)
			if ( //((m_Doc->docParagraphStyles[absa].alignment() == 3) || (m_Doc->docParagraphStyles[absa].alignment() == 4)) && 
				 (a > 0 && ! isBreak(itemText.text(a-1))) &&
				 ! (a > 0 && isBreakingSpace(itemText.text(a-1)) && (itemText.charStyle(a-1).effects() & ScStyle_SuppressSpace) != ScStyle_SuppressSpace) &&
				 (current.itemsInLine == 0) && (isBreakingSpace(hl->ch[0])))
			{
				hl->setEffects(hl->effects() | ScStyle_SuppressSpace);
				hl->glyph.xadvance = 0;
				continue;
			}
			else
				hl->setEffects(hl->effects() & ~ScStyle_SuppressSpace);

//			qDebug(QString("textframe(%1,%2): len=%3, fontsize=%4, ascent=%5").arg(Xpos).arg(Ypos).arg(itemText.length())
//					   .arg(charStyle.fontSize()).arg(charStyle.font().ascent()));				
			if (current.itemsInLine == 0)
			{
 				// more about par gap and dropcaps
				if (((a > firstInFrame()) && (itemText.text(a-1) == SpecialChars::PARSEP)) || ((a == 0) && (BackBox == 0)) && (!current.startOfCol))
				{
					current.yPos += style.gapBefore();
					DropCapDrop = 0;
					if (chstr[0] != SpecialChars::PARSEP)
						DropCmode = style.hasDropCap();
					else
						DropCmode = false;
					if (DropCmode)
					{
						DropLines = style.dropCapLines();
						if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
							DropCapDrop = m_Doc->typographicSettings.valueBaseGrid * (DropLines-1);
						else
						{
							if (style.lineSpacingMode() == ParagraphStyle::FixedLineSpacing)
								DropCapDrop = style.lineSpacing() * (DropLines-1);
							else
								DropCapDrop = charStyle.font().height(style.charStyle().fontSize() / 10.0) * (DropLines-1);
						}
						current.yPos += DropCapDrop;
					}
				}
			}
			// find charsize & y pos
			if (DropCmode)
			{
				// dropcap active?
				if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
					DropCapDrop = m_Doc->typographicSettings.valueBaseGrid * (DropLines-1);
				else
				{
					if (style.lineSpacingMode() == ParagraphStyle::FixedLineSpacing)
						DropCapDrop = style.lineSpacing() * (DropLines-1);
					else
						DropCapDrop = charStyle.font().height(style.charStyle().fontSize() / 10.0) * (DropLines-1);
				}

				if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
				{
					chsd = (10 * ((m_Doc->typographicSettings.valueBaseGrid * (DropLines-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / (charStyle.font().realCharHeight(chstr[0], 1))));
					chs = (10 * ((m_Doc->typographicSettings.valueBaseGrid * (DropLines-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / charStyle.font().realCharAscent(chstr[0], 1)));
				}
				else
				{
					if (style.lineSpacingMode() == ParagraphStyle::FixedLineSpacing)
					{
						chsd = (10 * ((style.lineSpacing() * (DropLines-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / (charStyle.font().realCharHeight(chstr[0], 1))));
						chs = (10 * ((style.lineSpacing() * (DropLines-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / charStyle.font().realCharAscent(chstr[0], 1)));
					}
					else
					{
						double currasce = charStyle.font().height(style.charStyle().fontSize() / 10.0);
						chsd = (10 * ((currasce * (DropLines-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / (charStyle.font().realCharHeight(chstr[0], 1))));
						chs = (10 * ((currasce * (DropLines-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / charStyle.font().realCharAscent(chstr[0], 1)));
					}
				}
				hl->setEffects(hl->effects() | ScStyle_DropCap);
				hl->glyph.yoffset -= DropCapDrop;
			}
			else // ! dropCapMode
			{
				if ((hl->ch == SpecialChars::OBJECT) && (hl->cembedded != 0))
					chs = qRound((hl->cembedded->gHeight + hl->cembedded->lineWidth()) * 10);
				else
					chs = charStyle.fontSize();
			}
			// Smallcaps and such
			hl->glyph.yadvance = 0;
			oldCurY = layoutGlyphs(*hl, chstr, hl->glyph);
			// find out width of char
			if ((hl->ch == SpecialChars::OBJECT) && (hl->cembedded != 0))
				wide = hl->cembedded->gWidth + hl->cembedded->lineWidth();
			else
			{
/*				if (a+1 < itemText.length())
				{
						chstr3 = itemText.text(a+1);
					// apply kerning
					wide = charStyle.font().charWidth(chstr2[0], chs / 10.0, chstr3[0]);
				}
				else
					wide = charStyle.font().charWidth(chstr2[0], chs / 10.0);
*/			
				wide = hl->glyph.wide();
				if (a+1 < itemText.length())
				{
					uint glyph2 = charStyle.font().char2CMap(itemText.text(a+1));
					double kern= charStyle.font().glyphKerning(hl->glyph.glyph, glyph2, chs / 10.0) * hl->glyph.scaleH;
					wide += kern;
					hl->glyph.xadvance += kern;
				}
			}
			if (DropCmode)
			{
				// drop caps are wider...
				if ((hl->ch == SpecialChars::OBJECT) && (hl->cembedded != 0))
				{
					wide = hl->cembedded->gWidth + hl->cembedded->lineWidth();
					if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
						asce = m_Doc->typographicSettings.valueBaseGrid * DropLines;
					else
					{
						if (style.lineSpacingMode() == ParagraphStyle::FixedLineSpacing)
							asce = style.lineSpacing() * DropLines;
						else
							asce = charStyle.font().height(style.charStyle().fontSize() / 10.0) * DropLines;
					}
					hl->glyph.scaleH /= hl->glyph.scaleV;
					hl->glyph.scaleV = (asce / (hl->cembedded->gHeight + hl->cembedded->lineWidth()));
					hl->glyph.scaleH *= hl->glyph.scaleV;
				}
				else
				{
					wide = charStyle.font().realCharWidth(chstr[0], chsd / 10.0);
					asce = charStyle.font().realCharHeight(chstr[0], chsd / 10.0);
//					qDebug(QString("dropcaps pre: chsd=%1 realCharHeight = %2 chstr=%3").arg(chsd).arg(asce).arg(chstr2[0]));
					hl->glyph.scaleH /= hl->glyph.scaleV;
					hl->glyph.scaleV = (asce / charStyle.font().realCharHeight(chstr[0], charStyle.fontSize() / 10.0));
					hl->glyph.scaleH *= hl->glyph.scaleV;
				}
				hl->glyph.xadvance = wide;
				desc2 = 0;
				desc = 0;
			}
			else
			{
//				qDebug(QString("textframe ascent/descent: fontsize=%1, ascent=%2, descent=%3")
//					   .arg(charStyle.fontSize()).arg(charStyle.font().ascent()).arg(charStyle.font().descent()));				
				// find ascent / descent
				double hlcsize10=charStyle.fontSize() / 10.0;
				if ((hl->ch == SpecialChars::OBJECT) && (hl->cembedded != 0))
				{
					desc = desc2 = 0;
				}
				else
				{
					desc = desc2 = -charStyle.font().descent(hlcsize10);
				}
				asce = charStyle.font().ascent(hlcsize10);
//				wide = wide * hl->glyph.scaleH;
			}
			fBorder = false;
			// end of col reached?
//			qDebug(QString("eocol? %1 + %2 + %3 > %4 -- asce=%5").arg(current.yPos).arg(extra.Bottom).arg(lineCorr).arg(Height).arg(asce));
			if (current.isEndOfCol())
			{
				current.column++;
				if (current.column < Cols)
				{
					// start next col
					current.nextColumn(asce);
					if (((a > firstInFrame()) && (itemText.text(a-1) == SpecialChars::PARSEP)) 
						|| ((a == firstInFrame()) && (BackBox == 0)))
					{
						if (chstr[0] != SpecialChars::PARSEP)
							DropCmode = style.hasDropCap();
						else
							DropCmode = false;
						if (DropCmode)
						{
							if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
								desc2 = -charStyle.font().descent() * m_Doc->typographicSettings.valueBaseGrid * style.dropCapLines();
							else
								desc2 = -charStyle.font().descent() * style.lineSpacing() * style.dropCapLines();
						}
						if (DropCmode)
							DropLines = style.dropCapLines();
					}
//					qDebug(QString("layout: nextcol grid=%1 x %2").arg(style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing).arg(m_Doc->typographicSettings.valueBaseGrid));
					if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
					{
						double by = Ypos;
						if (OwnPage != -1)
							by = Ypos - m_Doc->Pages->at(OwnPage)->yOffset();
						int ol1 = qRound((by + current.yPos - m_Doc->typographicSettings.offsetBaseGrid) * 10000.0);
						int ol2 = static_cast<int>(ol1 / m_Doc->typographicSettings.valueBaseGrid);
						current.yPos = ceil(  ol2 / 10000.0 ) * m_Doc->typographicSettings.valueBaseGrid + m_Doc->typographicSettings.offsetBaseGrid - by;
					}
				}
				else
				{
					MaxChars = a;
//					qDebug(QString("no room A: %1").arg(a));
					goto NoRoom;
				}
			}
			// ok, there's more room in col
			if (current.itemsInLine == 0)
			{
//				qDebug(QString("newline: '%1' %2 %3").arg(a).arg(current.yPos).arg(asce));
				// start a new line
				double TopOffset = asce;
				double BotOffset = desc2;
				goNoRoom = false;
				if (current.startOfCol)
				{
//					qDebug(QString("current.startOfCol: %1 + %2 + %3").arg(asce).arg(extra.Top).arg(lineCorr));
					current.yPos = asce + extra.Top + lineCorr + 1;
//							if (((a > 0) && (itemText.at(a-1)->ch == QChar(13))) || ((a == 0) && (BackBox == 0)))
//								current.yPos += m_Doc->docParagraphStyles[hl->cab].gapBefore;
				}
//				qDebug(QString("layout: nextline grid=%1 x %2").arg(style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing).arg(m_Doc->typographicSettings.valueBaseGrid));
				if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
				{
					double by = Ypos;
					if (OwnPage != -1)
						by = Ypos - m_Doc->Pages->at(OwnPage)->yOffset();
					int ol1 = qRound((by + current.yPos - m_Doc->typographicSettings.offsetBaseGrid) * 10000.0);
					int ol2 = static_cast<int>(ol1 / m_Doc->typographicSettings.valueBaseGrid);
//					qDebug(QString("useBaselIneGrid: %1 * %2 + %3 - %4").arg(ol2 / 10000.0).arg(m_Doc->typographicSettings.valueBaseGrid).arg(m_Doc->typographicSettings.offsetBaseGrid).arg(by));
					current.yPos = ceil(  ol2 / 10000.0 ) * m_Doc->typographicSettings.valueBaseGrid + m_Doc->typographicSettings.offsetBaseGrid - by;
				}
				if (current.yPos-TopOffset < 0.0)
					current.yPos = TopOffset+1;
				// find linelength:
				pt1 = QPoint(static_cast<int>(ceil(current.xPos)), static_cast<int>(current.yPos+BotOffset));
				pt2 = QPoint(static_cast<int>(ceil(current.xPos)), static_cast<int>(ceil(current.yPos-TopOffset)));
				// increase pt1/pt2 until i-beam reaches end of line
//				qDebug(QString("linestart: %1 + %2 + %3 < %4").arg(current.xPos).arg(wide).arg(style.rightMargin()).arg(current.colRight));
				double leftIndent = 0;
				while (!cl.contains(pf2.xForm(pt1)) || !cl.contains(pf2.xForm(pt2)) || current.isEndOfLine(wide + leftIndent + style.rightMargin()))
				{
					fBorder = true;
					current.xPos++;
					if (current.isEndOfLine(wide + leftIndent + style.rightMargin()))
					{
						qDebug(QString("eocol %5? %1 + %2 + %3 + %4").arg(current.yPos).arg(current.startOfCol).arg(style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing).arg(style.lineSpacing()).arg(current.column));
						// new line
						fBorder = false;
						current.xPos = current.colLeft;

						leftIndent = style.leftMargin();
						if (a > 0 && itemText.text(a-1) == SpecialChars::PARSEP)
							leftIndent += style.firstIndent();

						if (current.startOfCol)
						{
							current.yPos++;
						}
						else
						{
							current.yPos += style.lineSpacing();
						}
//						qDebug(QString("layout: next lower line grid=%1 x %2").arg(style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing).arg(m_Doc->typographicSettings.valueBaseGrid));
						if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
						{
							double by = Ypos;
							if (OwnPage != -1)
								by = Ypos - m_Doc->Pages->at(OwnPage)->yOffset();
							int ol1 = qRound((by + current.yPos - m_Doc->typographicSettings.offsetBaseGrid) * 10000.0);
							int ol2 = static_cast<int>(ol1 / m_Doc->typographicSettings.valueBaseGrid);
							current.yPos = ceil(  ol2 / 10000.0 ) * m_Doc->typographicSettings.valueBaseGrid + m_Doc->typographicSettings.offsetBaseGrid - by;
						}
						if (current.isEndOfCol())
						{
							fBorder = false;
							current.column++;
							if (current.column < Cols)
							{
								current.nextColumn(asce);
								if (((a > firstInFrame()) && (itemText.text(a-1) == SpecialChars::PARSEP)) || ((a == firstInFrame()) && (BackBox == 0)))
								{
									if (chstr[0] != SpecialChars::PARSEP)
										DropCmode = style.hasDropCap();
									else
										DropCmode = false;
									if (DropCmode)
									{
										if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
											desc2 = -charStyle.font().descent() * m_Doc->typographicSettings.valueBaseGrid * style.dropCapLines();
										else
											desc2 = -charStyle.font().descent() * style.lineSpacing() * style.dropCapLines();
									}
									if (DropCmode)
										DropLines = style.dropCapLines();
								}
//								qDebug(QString("layout: nextcol2 grid=%1 x %2").arg(style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing).arg(m_Doc->typographicSettings.valueBaseGrid));
								if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
								{
									double by = Ypos;
									if (OwnPage != -1)
										by = Ypos - m_Doc->Pages->at(OwnPage)->yOffset();
									int ol1 = qRound((by + current.yPos - m_Doc->typographicSettings.offsetBaseGrid) * 10000.0);
									int ol2 = static_cast<int>(ol1 / m_Doc->typographicSettings.valueBaseGrid);
									current.yPos = ceil(  ol2 / 10000.0 ) * m_Doc->typographicSettings.valueBaseGrid + m_Doc->typographicSettings.offsetBaseGrid - by;
								}
							}
							else
							{
								MaxChars = a;
//								qDebug(QString("no room B: %1").arg(a));
								goto NoRoom;
							}
						}
					}
					pt1 = QPoint(static_cast<int>(ceil(current.xPos)), static_cast<int>(current.yPos+BotOffset));
					pt2 = QPoint(static_cast<int>(ceil(current.xPos)), static_cast<int>(ceil(current.yPos-TopOffset)));
				}

				if (((fBorder)) && (!AbsHasDrop))
					current.xPos += extra.Left;
				// indent first line of par
				if (a > 0)
				{
					if (itemText.text(a-1) == SpecialChars::PARSEP)
						current.xPos += style.firstIndent();
				}
				else
				{
					if (BackBox == 0)
						current.xPos += style.firstIndent();
					else
					{
						if (BackBox->frameDisplays(firstInFrame()-1))
						{
							if (BackBox->itemText.text(BackBox->lastInFrame()) == SpecialChars::PARSEP)
								current.xPos += style.firstIndent();
						}
						else
							current.xPos += style.firstIndent();
					}
				}
				// add left margin
				if (!AbsHasDrop)
					current.xPos += style.leftMargin();
				if (opticalMargins & ParagraphStyle::OM_LeftHangingPunct) {
					current.xPos += opticalLeftMargin(itemText, current.line);
				}
				current.line.x = current.xPos;
				current.line.y = current.yPos;
				fBorder = false;
			}
			else {
//				qDebug(QString("cont.' line: '%1'").arg(a));
			}
			// right tab stuff
			if (tabs.active)
			{
				if (((hl->ch == ".") && (tabs.status == TabPOINT)) || ((hl->ch == ",") && (tabs.status == TabCOMMA)) || (hl->ch == SpecialChars::TAB))
				{
					tabs.active = false;
					tabs.status = TabNONE;
				}
			}
			// tab positioning
			if (hl->ch == SpecialChars::TAB)
			{
				wide = 1;
				if (tabs.active)
					tabs.active = false;
				else // ???
				{
					tabs.xPos = current.xPos;
					tTabValues = style.tabValues();
					if (tTabValues.isEmpty())
					{
						if ((current.xPos - current.colLeft) != 0)
						{
							if (current.xPos == current.colLeft + ceil((current.xPos-current.colLeft) / m_Doc->toolSettings.dTabWidth) * m_Doc->toolSettings.dTabWidth)
								current.xPos += m_Doc->toolSettings.dTabWidth;
							else
								current.xPos = current.colLeft + ceil((current.xPos-current.colLeft) / m_Doc->toolSettings.dTabWidth) * m_Doc->toolSettings.dTabWidth;
						}
						else
							current.xPos = current.colLeft + m_Doc->toolSettings.dTabWidth;
						tabs.status = TabNONE;
						tabs.active = false;
					}
					else
					{
						double tCurX = current.xPos - current.colLeft;
						double oCurX = tCurX + wide;
						for (int yg = static_cast<int>(tTabValues.count()-1); yg > -1; yg--)
						{
							if (oCurX < tTabValues[yg].tabPosition)
							{
								tabs.status = static_cast<int>(tTabValues[yg].tabType);
								tCurX = tTabValues[yg].tabPosition;
								tabs.fillChar    = tTabValues[yg].tabFillChar;
							}
						}
						tabs.active = (tabs.status != TabLEFT);
						if (tCurX == oCurX-wide)
							current.xPos = current.colLeft + ceil((current.xPos-current.colLeft) / m_Doc->toolSettings.dTabWidth) * m_Doc->toolSettings.dTabWidth;
						else
							current.xPos = current.colLeft + tCurX;
						
						// remember fill char
//						qDebug(QString("tab: %1 '%2'").arg(tCurX).arg(tabs.fillChar));
						if (!tabs.fillChar.isNull()) {
							hl->glyph.grow();
							GlyphLayout * tglyph = hl->glyph.more;
							tglyph->glyph = charStyle.font().char2CMap(tabs.fillChar);
							tglyph->yoffset = hl->glyph.yoffset;
							tglyph->scaleV = tglyph->scaleH = chs / charStyle.fontSize();
							tglyph->xadvance = 0;
						}
					}
					hl->glyph.xadvance = current.xPos - tabs.xPos;
//					wide = current.xPos - RTabX;
					tabs.charIndex = a;
				}
			}
			
			// remember y pos
//			hl->glyph.yoffset = current.yPos + oldCurY;
//			hl->glyph.yoffset = 0;
			if (DropCmode)
				hl->glyph.yoffset -= charStyle.font().realCharHeight(chstr[0], chsd / 10.0) - charStyle.font().realCharAscent(chstr[0], chsd / 10.0);
			// find tracking
			if (current.itemsInLine == 0)
			{
				itemText.item(a)->setEffects(itemText.item(a)->effects() | ScStyle_StartOfLine);
				kernVal = 0;
			}
			else
			{
				kernVal = 0; // chs * charStyle.tracking() / 10000.0;
				itemText.item(a)->setEffects(itemText.item(a)->effects() & ~ScStyle_StartOfLine);
			}

			// remember possible break
			if ( (isBreakingSpace(hl->ch[0]) || hl->ch == SpecialChars::TAB) && !outs)
			{
				if ( a == firstInFrame() || !isBreakingSpace(itemText.text(a-1)) )
				{
					current.rememberBreak(a, current.xPos);
				}
			}
			
			
			// remember x pos
			if (!tabs.active) // normal case
			{
//				hl->glyph.xoffset = QMAX(current.xPos+kernVal, current.colLeft);
				//hl->glyph.xoffset = current.xPos+kernVal; // needed for left optical margin
				current.xPos += wide+kernVal;
//				current.xPos = QMAX(current.xPos, current.colLeft);
			}
			else if (tabs.active && tabs.status == TabCENTER) 	// center tab
			{
				current.xPos += (wide+kernVal) / 2;
				current.xPos = QMAX(current.xPos, current.colLeft);
			}
			else // other tabs.active			
			{
				current.xPos = QMAX(current.xPos, current.colLeft);
				//hl->glyph.xoffset = current.xPos;
			}
			
			
			// hyphenation
			if (((hl->effects() & ScStyle_HyphenationPossible) || (hl->ch == "-") || hl->ch[0] == SpecialChars::SHYPHEN) && (!outs) && !itemText.text(a-1).isSpace() )
			{
				double breakPos = current.xPos;
				if (hl->ch != "-")
				{
					breakPos += charStyle.font().charWidth('-', charStyle.fontSize() / 10.0) * (charStyle.scaleH() / 1000.0);
				}

				double rightHang = 0;
				if (opticalMargins & ParagraphStyle::OM_RightHangingPunct) {
					rightHang = 0.7 * charStyle.font().realCharWidth('-', (charStyle.fontSize() / 10.0) * (charStyle.scaleH() / 1000.0));
				}
				
				if (breakPos - 0 < current.colRight - style.rightMargin())
				{
					if ((current.hyphenCount < m_Doc->HyCount) || (m_Doc->HyCount == 0) || hl->ch[0] == SpecialChars::SHYPHEN)
					{
						current.rememberBreak(a, breakPos);
					}
				}
			}

			++current.itemsInLine;
			
/*						
			//FIXME: asce / desc set correctly?
			if ((((hl->effects() & ScStyle_HyphenationPossible) || hl->ch == "-") && (current.hyphenCount < m_Doc->HyCount || m_Doc->HyCount == 0))  || hl->ch[0] == SpecialChars::SHYPHEN)
			{
				if (hl->effects() & ScStyle_HyphenationPossible || hl->ch[0] == SpecialChars::SHYPHEN)
				{
					pt1 = QPoint(qRound(ceil(current.xPos+extra.Right+ charStyle.font().charWidth('-', charStyle.fontSize() / 10.0) * (charStyle.scaleH() / 1000.0))), qRound(current.yPos+desc));
					pt2 = QPoint(qRound(ceil(current.xPos+extra.Right+ charStyle.font().charWidth('-', charStyle.fontSize() / 10.0) * (charStyle.scaleH() / 1000.0))), qRound(ceil(current.yPos-asce)));
				}
				else
				{
					pt1 = QPoint(qRound(ceil(current.xPos+extra.Right)), qRound(current.yPos+desc));
					pt2 = QPoint(qRound(ceil(current.xPos+extra.Right)), qRound(ceil(current.yPos-asce)));
				}
			}
			else */
			{
				pt1 = QPoint(qRound(ceil(current.xPos+extra.Right)), qRound(current.yPos+desc));
				pt2 = QPoint(qRound(ceil(current.xPos+extra.Right)), qRound(ceil(current.yPos-asce)));
			}

			// test if end of line reached
			if ((!cl.contains(pf2.xForm(pt1))) || (!cl.contains(pf2.xForm(pt2))) || (current.isEndOfLine(style.rightMargin())))
				outs = true;
			if (current.isEndOfCol())
				outs = true;
			if ((hl->ch == SpecialChars::FRAMEBREAK) && (a < itemText.length()-1))
				goNoRoom = true;
			if ((hl->ch == SpecialChars::COLBREAK) && (Cols > 1))
				goNextColumn = true;

			if (tabs.active)
			{
				double cen = 1;
				if (tabs.status == TabCENTER)
					cen = 2;
				
				double newTabAdvance = itemText.item(tabs.charIndex)->glyph.xadvance - (wide+kernVal) / cen;
				
				if (newTabAdvance >= 0) {
					itemText.item(tabs.charIndex)->glyph.xadvance = newTabAdvance;
				}
				else {
					tabs.active = false;
					tabs.status = TabNONE;
				}
			}
//			BuPos++;
			if (DropCmode)
			{
				DropCmode = false;
				AbsHasDrop = true;
				maxDY = current.yPos;
				current.xPos += style.dropCapOffset();
				hl->glyph.xadvance += style.dropCapOffset();
//				qDebug(QString("dropcapoffset: %1 -> %2").arg(current.xPos-style.dropCapOffset()).arg(current.xPos));
				current.xPos = QMAX(current.xPos, current.colLeft);
				maxDX = current.xPos;
				QPointArray tcli(4);
				if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
				{
					current.yPos -= m_Doc->typographicSettings.valueBaseGrid * (DropLines-1);
					double by = Ypos;
					if (OwnPage != -1)
						by = Ypos - m_Doc->Pages->at(OwnPage)->yOffset();
					int ol1 = qRound((by + current.yPos - m_Doc->typographicSettings.offsetBaseGrid) * 10000.0);
					int ol2 = static_cast<int>(ol1 / m_Doc->typographicSettings.valueBaseGrid);
					current.yPos = ceil(  ol2 / 10000.0 ) * m_Doc->typographicSettings.valueBaseGrid + m_Doc->typographicSettings.offsetBaseGrid - by;
					//FIXME: use current.colLeft instead of xOffset?
					tcli.setPoint(0, QPoint(qRound(hl->glyph.xoffset), qRound(maxDY-DropLines*m_Doc->typographicSettings.valueBaseGrid)));
					tcli.setPoint(1, QPoint(qRound(maxDX), qRound(maxDY-DropLines*m_Doc->typographicSettings.valueBaseGrid)));
				}
				else
				{
					if (style.lineSpacingMode() == ParagraphStyle::FixedLineSpacing)
					{
						current.yPos -= style.lineSpacing() * (DropLines-1);
						tcli.setPoint(0, QPoint(qRound(hl->glyph.xoffset), qRound(maxDY - DropLines * style.lineSpacing())));
						tcli.setPoint(1, QPoint(qRound(maxDX), qRound(maxDY-DropLines*style.lineSpacing())));
					}
					else
					{
						double currasce = charStyle.font().height(style.charStyle().fontSize() / 10.0);
						current.yPos -= currasce * (DropLines-1);
						tcli.setPoint(0, QPoint(qRound(hl->glyph.xoffset), qRound(maxDY-DropLines*currasce)));
						tcli.setPoint(1, QPoint(qRound(maxDX), qRound(maxDY-DropLines*currasce)));
					}
				}
				tcli.setPoint(2, QPoint(qRound(maxDX), qRound(maxDY)));
				tcli.setPoint(3, QPoint(qRound(hl->glyph.xoffset), qRound(maxDY)));
				cm = QRegion(pf2.xForm(tcli));
				cl = cl.subtract(cm);
//				current.yPos = maxDY;
			}
			// end of line
			if ( isBreak(hl->ch[0], Cols > 1) || (outs))
			{
				tabs.active = false;
				tabs.status = TabNONE;
				if (isBreak(hl->ch[0], Cols > 1))
				{
					// find end of line
					current.breakLine(itemText, a);
					EndX = current.endOfLine(cl, pf2, asce, desc, style.rightMargin());
					current.finishLine(EndX);
					
					if (style.alignment() != 0)
					{
						if (opticalMargins & ParagraphStyle::OM_RightHangingPunct)
							current.line.width += opticalRightMargin(itemText, current.line);

						OFs = 0;
						if (style.alignment() == 2)
							OFs = current.line.width - current.line.naturalWidth;
						if (style.alignment() == 1)
							OFs = (current.line.width - current.line.naturalWidth) / 2;
						if (style.alignment() == 3)
							OFs = 0;
						
						if (style.alignment() == 4
							|| (style.alignment() == 3 
								&&  (hl->ch == SpecialChars::LINEBREAK ||
									 hl->ch == SpecialChars::FRAMEBREAK ||
									 hl->ch == SpecialChars::COLBREAK)
								&&  !itemText.text(current.line.lastItem - 1).isSpace()))
						{
							justifyLine(itemText, current.line); 
						}
						else
						{
							// simple offset
							indentLine(current.line, OFs);
						}
						current.xPos = current.line.x + current.line.width;
					}
				}
				else // outs -- last char went outside the columns
				{
					if (current.breakIndex >= 0)            // Hier koenen auch andere Trennungen eingebaut werden
					{
						// go back to last break position
//						qDebug(QString("new break pos a=%1 BuPos=%2 current.breakIndex=%3").arg(a).arg(BuPos).arg(current.breakIndex));
						a = current.breakIndex;
						assert( a >= 0 );
						assert( a < itemText.length() );
						hl = itemText.item(a);
						style = itemText.paragraphStyle(a);
						current.itemsInLine = a - current.line.firstItem + 1;
//						qDebug(QString("style outs pos %1: %2 (%3)").arg(a).arg(style.alignment()).arg(style.parent()));
//						qDebug(QString("style <@%6: %1 -- %2, %4/%5 char: %3").arg(style.leftMargin()).arg(style.rightMargin())
//							   .arg(style.charStyle().asString()).arg(style.name()).arg(style.parent()?style.parent()->name():"")
//							   .arg(a));

						if (hl->ch[0] == ' ') {
							hl->setEffects(hl->effects() | ScStyle_SuppressSpace);
							hl->glyph.xadvance = 0;
						}
						
						EndX = current.endOfLine(cl, pf2, asce, desc, style.rightMargin());
						current.finishLine(EndX);

//???						current.breakXPos = current.line.x;
//???						for (int j=current.line.firstItem; j <= a; ++j)
//???							current.breakXPos += itemText.item(j)->glyph.wide();
						
						if ((hl->effects() & ScStyle_HyphenationPossible) || hl->ch[0] == SpecialChars::SHYPHEN)
						{
							// insert hyphen
							current.hyphenCount++;
							hl->setEffects(hl->effects() | ScStyle_SmartHyphenVisible);
							hl->glyph.grow();
							hl->glyph.more->glyph = charStyle.font().char2CMap(QChar('-'));
							hl->glyph.more->xadvance = charStyle.font().charWidth('-', itemText.charStyle(a).fontSize() / 10.0) * (itemText.charStyle(a).scaleH() / 1000.0);
//							current.breakIndex += 2;
//???							current.breakXPos += hl->glyph.more->xadvance;
						}
						else 
						{
							if (hl->ch[0] != '-')
								current.hyphenCount = 0;
							hl->setEffects(hl->effects() & ~ScStyle_SmartHyphenVisible);
							hl->glyph.shrink();
//							current.breakIndex += 1;
						}
						
						// Justification
						if (style.alignment() != 0)
						{
							if (opticalMargins & ParagraphStyle::OM_RightHangingPunct)
								current.line.width += opticalRightMargin(itemText, current.line);

							OFs = 0;
							if (style.alignment() == 2)
								OFs = current.line.width - current.line.naturalWidth;
							if (style.alignment() == 1)
								OFs = (current.line.width - current.line.naturalWidth) / 2;
							
							if ((style.alignment() == 3) 
								|| (style.alignment() == 4))
							{
								justifyLine(itemText, current.line);
							}
							else
							{
								indentLine(current.line, OFs);
							}
//							qDebug(QString("line: endx=%1 lastchar=%2").arg(EndX).arg(LiList.at(BuPos-1)->xco + LiList.at(BuPos-1)->wide));
							current.xPos = current.line.x + current.line.width;
						}
					}
					else  // no break position
					{
						if (a > current.line.firstItem)
						{
							--a;
							--current.itemsInLine;
							hl = itemText.item(a);
							style = itemText.paragraphStyle(a);
						}
						current.breakLine(itemText, a);
//						qDebug(QString("style no break pos %1: %2 (%3)").arg(a).arg(style.alignment()).arg(style.parent()));
//						qDebug(QString("style nb @%6: %1 -- %2, %4/%5 char: %3").arg(style.leftMargin()).arg(style.rightMargin())
//							   .arg(style.charStyle().asString()).arg(style.name()).arg(style.parent())
//							   .arg(a));
						EndX = current.endOfLine(cl, pf2, asce, desc, style.rightMargin());
						current.finishLine(EndX);
						qDebug(QString("no break pos: %1-%2 @ %3 wid %4 nat %5 endX %6")
							   .arg(current.line.firstItem).arg(current.line.firstItem)
							   .arg(current.line.x).arg(current.line.width).arg(current.line.naturalWidth).arg(EndX));
					}
				}
				if ( outs || isBreak(hl->ch[0], (Cols > 1)) )
				{
					if (outs && current.isEndOfLine(hl->glyph.wide() + style.rightMargin()))
					{
						if (( hl->ch[0] == SpecialChars::PARSEP || hl->ch[0] == SpecialChars::LINEBREAK) 
							&& AbsHasDrop)
						{
							AbsHasDrop = false;
							if (current.yPos < maxDY)
								current.yPos = maxDY;
						}
						bool fromOut = true;
						double BotOffset = desc+extra.Bottom+lineCorr;
//						pt1 = QPoint(qRound(current.xPos+extra.Right), static_cast<int>(current.yPos+BotOffset));
//						pt2 = QPoint(qRound(current.xPos+extra.Right), static_cast<int>(ceil(current.yPos-asce)));
						while (!current.isEndOfLine(style.rightMargin()))
						{
							current.xPos++;
							if (current.isEndOfLine(style.rightMargin()))
							{
								fromOut = false;
//								qDebug(QString("layout: next lower2 grid=%1 x %2").arg(style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing).arg(m_Doc->typographicSettings.valueBaseGrid));
								if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
									current.yPos += m_Doc->typographicSettings.valueBaseGrid;
								else
									current.yPos += style.lineSpacing();
								if (current.isEndOfCol(desc) && (current.column+1 == Cols))
								{
									goNoRoom = true;
//									qDebug(QString("go no room 1: %1").arg(a));
									break;
								}
								if (AbsHasDrop)
								{
									if ((current.yPos > maxDY) && (current.yPos - asce > maxDY))
									{
										AbsHasDrop = false;
										current.xPos = current.colLeft;
									}
									else
										current.xPos = maxDX;
								}
								else
									current.xPos = current.colLeft;
								if (isBreak(hl->ch[0]))
								{
									if (hl->ch == SpecialChars::PARSEP)
										current.yPos += style.gapAfter();
									current.hyphenCount = 0;
								}
								break;
							}
							pt1 = QPoint(qRound(current.xPos+extra.Right), static_cast<int>(current.yPos+BotOffset));
							pt2 = QPoint(qRound(current.xPos+extra.Right), static_cast<int>(ceil(current.yPos-asce)));
							if (cl.contains(pf2.xForm(pt1)) && cl.contains(pf2.xForm(pt2)))
								break;
//							else
//								qDebug(QString("looking for start of line at %1,%2").arg(current.xPos).arg(current.yPos));
						}
						if (fromOut)
						{
							if (current.isEndOfCol(desc) && (current.column+1 == Cols))
							{
								goNoRoom = true;
//								qDebug(QString("go no room 2: %1").arg(a));
								break;
							}
							current.xPos--;
							current.xPos = QMAX(current.xPos, current.colLeft);
						}
					}
					else
					{
						if (( hl->ch == SpecialChars::PARSEP || hl->ch == SpecialChars::LINEBREAK ) 
							&& AbsHasDrop)
						{
							AbsHasDrop = false;
							if (current.yPos < maxDY)
								current.yPos = maxDY;
						}
//						qDebug(QString("layout: next lower3 grid=%1 x %2").arg(style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing).arg(m_Doc->typographicSettings.valueBaseGrid));

						if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
							current.yPos += m_Doc->typographicSettings.valueBaseGrid;
						else
						{
							if (a < lastInFrame())
								current.yPos += itemText.paragraphStyle(a+1).lineSpacing();
							else
								current.yPos += style.lineSpacing();
						}
						if (AbsHasDrop)
						{
							if ((current.yPos > maxDY) && (current.yPos - asce > maxDY))
							{
								AbsHasDrop = false;
								current.xPos = current.colLeft;
							}
							else
								current.xPos = maxDX;
						}
						else
							current.xPos = current.colLeft;
						if ( isBreak(hl->ch[0]) )
						{
							if (hl->ch == SpecialChars::PARSEP)
								current.yPos += style.gapAfter();
							current.hyphenCount = 0;
						}
					}
				}
				

				// calc. needed vertical space
				if (current.itemsInLine != 0)
				{
					if ((!AbsHasDrop) && (current.startOfCol) && (style.lineSpacingMode() != ParagraphStyle::BaselineGridLineSpacing))
					{
						double firstasce = itemText.charStyle(current.line.firstItem).font().ascent(itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
						double currasce = 0;
						if ((itemText.text(current.line.firstItem) == SpecialChars::PARSEP) || (itemText.text(current.line.firstItem) == SpecialChars::LINEBREAK))
							currasce = itemText.charStyle(current.line.firstItem).font().ascent(itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
						else if (itemText.object(current.line.firstItem) != 0)
							currasce = QMAX(currasce, (itemText.object(current.line.firstItem)->gHeight + itemText.object(current.line.firstItem)->lineWidth()) * (itemText.charStyle(current.line.firstItem).scaleV() / 1000.0));
						else //if (itemText.charStyle(current.line.firstItem).effects() & ScStyle_DropCap == 0)
							currasce = itemText.charStyle(current.line.firstItem).font().realCharAscent(itemText.text(current.line.firstItem), itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
						for (int zc = 0; zc < current.itemsInLine; ++zc)
						{
							QChar ch = itemText.text(current.line.firstItem + zc);
							const CharStyle& cStyle(itemText.charStyle(current.line.firstItem + zc));
							if ((ch == SpecialChars::TAB) || (ch == QChar(10))
								|| (ch == SpecialChars::PARSEP) || (ch == SpecialChars::NBHYPHEN)
								|| (ch == SpecialChars::COLBREAK) || (ch == SpecialChars::LINEBREAK)
								|| (ch == SpecialChars::FRAMEBREAK) || (ch == SpecialChars::NBSPACE))
								continue;
							if (itemText.object(current.line.firstItem + zc) != 0)
								currasce = QMAX(currasce, (itemText.object(current.line.firstItem + zc)->gHeight + itemText.object(current.line.firstItem + zc)->lineWidth()) * (cStyle.scaleV() / 1000.0));
							else //if (itemText.charStyle(current.line.firstItem + zc).effects() & ScStyle_DropCap == 0)
								currasce = QMAX(currasce, cStyle.font().realCharAscent(ch, cStyle.fontSize() / 10.0));
						}
						double adj = firstasce - currasce;
						current.line.ascent = currasce;
						current.line.y -= adj;
						current.yPos -= adj;
					}
					else if ((!current.startOfCol) && (style.lineSpacingMode() != ParagraphStyle::BaselineGridLineSpacing) && (style.lineSpacingMode() == ParagraphStyle::AutomaticLineSpacing))
					{
						QChar ch = itemText.text(current.line.firstItem);
						double firstasce = style.lineSpacing();
						double currasce = 0;
						if (itemText.object(current.line.firstItem) != 0)
							currasce = QMAX(currasce, (itemText.object(current.line.firstItem)->gHeight + itemText.object(current.line.firstItem)->lineWidth()) * (itemText.charStyle(current.line.firstItem).scaleV() / 1000.0));
						else //if (itemText.charStyle(current.line.firstItem).effects() & ScStyle_DropCap == 0)
							currasce = itemText.charStyle(current.line.firstItem).font().height(itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
						for (int zc = 0; zc < current.itemsInLine; ++zc)
						{
							QChar ch = itemText.text(current.line.firstItem + zc);
							if ((ch == SpecialChars::TAB) || (ch == QChar(10))
								|| (ch == SpecialChars::PARSEP) || (ch == SpecialChars::NBHYPHEN)
								|| (ch == SpecialChars::COLBREAK) || (ch == SpecialChars::FRAMEBREAK)
								|| (ch == SpecialChars::LINEBREAK) || (ch == SpecialChars::NBSPACE))
								continue;
							if (itemText.object(current.line.firstItem + zc) != 0)
								currasce = QMAX(currasce, (itemText.object(current.line.firstItem + zc)->gHeight + itemText.object(current.line.firstItem + zc)->lineWidth()) * (itemText.charStyle(current.line.firstItem + zc).scaleV() / 1000.0));
							else //if (itemText.charStyle(current.line.firstItem + zc).effects() & ScStyle_DropCap == 0)
								currasce = QMAX(currasce, itemText.charStyle(current.line.firstItem + zc).font().height(itemText.charStyle(current.line.firstItem + zc).fontSize() / 10.0));
						}
							
						double adj = firstasce - currasce;
						current.line.ascent = currasce;
						current.line.y -= adj;
						current.yPos -= adj;
					}
					if ( itemText.charStyle(current.line.firstItem).effects() & ScStyle_DropCap)
					{
						// put line back to top
						current.line.y -= DropCapDrop;
						itemText.item(current.line.firstItem)->glyph.yoffset += DropCapDrop;
					}
				}
				
				fillInTabLeaders(itemText, current.line);

				current.startOfCol = false;
/* has no effect except setting wide, asce and desc
 				uint loopC = BuPos3;
				if (m_Doc->guidesSettings.showControls)
					loopC++;  // ??? AV
				for (int zc = 0; zc < loopC; ++zc)
				{
					if ( zc >= current.itemsInLine) {
						qDebug("layout: zc too large %d / %d", zc, current.itemsInLine);
						continue;
					}
					if ( startLin + zc >= itemText.length()) {
						qDebug("layout: startLin+zc too large %d+%d / %d", startLin, zc, itemText.length());
						continue;
					}
//					else
//						qDebug("layout: startLin, zc ok. %d, %d, %d", startLin, zc, LiList.count());
					double wide2 = 0;
					double xcoZli = itemText.item(current.line.firstItem + zc)->glyph.xoffset;
//					itemText.item(startLin+zc)->glyph.xoffset = Zli2->xco;
///					itemText.item(startLin+zc)->glyph.yoffset = Zli2->yco;
					tTabValues = itemText.paragraphStyle(startLin+zc).tabValues();
					desc = - itemText.charStyle(startLin+zc).font().descent(itemText.charStyle(startLin+zc).fontSize() / 10.0);
					asce = itemText.charStyle(startLin+zc).font().ascent(itemText.charStyle(startLin+zc).fontSize() / 10.0);
					bool Sele = itemText.selected(startLin+zc);
					if (((Sele && (Select)) || (((NextBox != 0) || (BackBox != 0)) && Sele)) && (m_Doc->appMode == modeEdit))
					{
						wide = itemText.item(startLin+zc)->glyph.xadvance;
						if ((zc > 0) && (itemText.text(startLin+zc) == SpecialChars::TAB))
						{
							wide2 = itemText.item(startLin+zc-1)->glyph.xadvance;
							xcoZli = itemText.item(startLin+zc-1)->glyph.xoffset + wide2;
							wide = itemText.item(startLin+zc)->glyph.xoffset - xcoZli + itemText.item(startLin+zc)->glyph.xadvance;
						}
					}
				}
				*/
//				qDebug(QString("layout: line %1 - %2 @ (%3,%4) wd %5/%6").arg(current.line.firstItem).arg(current.line.lastItem)
//					   .arg(current.line.x).arg(current.line.y).arg(current.line.naturalWidth).arg(current.line.width));
				if (current.line.firstItem > current.line.lastItem)
					qDebug(QString("layout: empty line %1 - %2").arg(current.line.firstItem).arg(current.line.lastItem));
				else if (current.itemsInLine > 0)
					itemText.appendLine(current.line);
				current.startLine(a+1);
				outs = false;
				if (goNoRoom)
				{
					goNoRoom = false;
					MaxChars = a+1;
//					qDebug(QString("no room C: %1").arg(a+1));
					goto NoRoom;
				}
				if (goNextColumn)
				{
					goNextColumn = false;
					current.column++;
					if (current.column < Cols)
					{
						current.nextColumn(asce);
					}
					else
					{
						MaxChars = a;
//						qDebug(QString("no room D: %1").arg(a));
						goto NoRoom;
					}
				}
			}
		}
// end of itemText
		int a = itemText.length()-1;
		hl = a >=0 ? itemText.item(a) : NULL;
		current.breakLine(itemText, a);
		EndX = current.endOfLine(cl, pf2, asce, desc, style.rightMargin());
		current.finishLine(EndX);

		if (style.alignment() != 0)
		{
			if (opticalMargins & ParagraphStyle::OM_RightHangingPunct)
			{
				current.line.width += opticalRightMargin(itemText, current.line);
			}
			
			OFs = 0;
			if (style.alignment() == 2)
				OFs = current.line.width - current.line.naturalWidth;
			if (style.alignment() == 1)
				OFs = (current.line.width - current.line.naturalWidth) / 2;
			if (style.alignment() == 3)
				OFs = 0;
			if (style.alignment() == 4
				|| (style.alignment() == 3 
					&&  (hl->ch == SpecialChars::LINEBREAK ||
						 hl->ch == SpecialChars::FRAMEBREAK ||
						 hl->ch == SpecialChars::COLBREAK)
					&&  !itemText.text(current.line.firstItem + current.itemsInLine-1).isSpace()))
			{
				justifyLine(itemText, current.line);
			}
			else
			{
				indentLine(current.line, OFs);
			}
		}

		if (current.itemsInLine != 0)
		{
			if ((!AbsHasDrop) && (current.startOfCol) && (style.lineSpacingMode() != ParagraphStyle::BaselineGridLineSpacing))
			{
				double firstasce = itemText.charStyle(current.line.firstItem).font().ascent(itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
				double currasce = 0;
				if ((itemText.text(current.line.firstItem) == SpecialChars::PARSEP) || (itemText.text(current.line.firstItem) == SpecialChars::LINEBREAK))
					currasce = itemText.charStyle(current.line.firstItem).font().ascent(itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
				else if (itemText.object(current.line.firstItem) != 0)
					currasce = QMAX(currasce, (itemText.object(current.line.firstItem)->gHeight + itemText.object(current.line.firstItem)->lineWidth()) * (itemText.charStyle(current.line.firstItem).scaleV() / 1000.0));
				else //if (itemText.charStyle(current.line.firstItem).effects() & ScStyle_DropCap == 0)
					currasce = itemText.charStyle(current.line.firstItem).font().realCharAscent(itemText.text(current.line.firstItem), itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
				for (int zc = 0; zc < current.itemsInLine; ++zc)
				{
					if ((itemText.text(current.line.firstItem+zc) == SpecialChars::TAB) || (itemText.text(current.line.firstItem+zc) == QChar(10))
						|| (itemText.text(current.line.firstItem+zc) == SpecialChars::PARSEP) || (itemText.text(current.line.firstItem+zc) == SpecialChars::NBHYPHEN)
						|| (itemText.text(current.line.firstItem+zc) == SpecialChars::FRAMEBREAK) || (itemText.text(current.line.firstItem+zc) == SpecialChars::COLBREAK)
						|| (itemText.text(current.line.firstItem+zc) == SpecialChars::LINEBREAK) || (itemText.text(current.line.firstItem+zc) == SpecialChars::NBSPACE))
						continue;
					if (itemText.object(current.line.firstItem+zc) != 0)
						currasce = QMAX(currasce, (itemText.object(current.line.firstItem+zc)->gHeight + itemText.object(current.line.firstItem+zc)->lineWidth()) * itemText.charStyle(current.line.firstItem+zc).scaleV() / 1000.0);
					else //if (itemText.charStyle(current.line.firstItem+zc).effects() & ScStyle_DropCap == 0)
						currasce = QMAX(currasce, itemText.charStyle(current.line.firstItem+zc).font().realCharAscent(itemText.text(current.line.firstItem+zc), itemText.charStyle(current.line.firstItem+zc).fontSize() / 10.0));
				}
				double adj = firstasce - currasce;
				current.line.ascent = currasce;
				current.line.y -= adj;
				current.yPos -= adj;
			}
			else if ((!current.startOfCol) && (style.lineSpacingMode() != ParagraphStyle::BaselineGridLineSpacing) && (style.lineSpacingMode() == ParagraphStyle::AutomaticLineSpacing))
			{
				double firstasce = style.lineSpacing();
				double currasce = 0;
				if (itemText.object(current.line.firstItem) != 0)
					currasce = QMAX(currasce, (itemText.object(current.line.firstItem)->gHeight + itemText.object(current.line.firstItem)->lineWidth()) * (itemText.charStyle(current.line.firstItem).scaleV() / 1000.0));
				else //if (itemText.charStyle(current.line.firstItem).effects() & ScStyle_DropCap == 0)
					currasce = itemText.charStyle(current.line.firstItem).font().height(itemText.charStyle(current.line.firstItem).fontSize() / 10.0);
				for (int zc = 0; zc < current.itemsInLine; ++zc)
				{
					if ((itemText.text(current.line.firstItem+zc) == SpecialChars::TAB) || (itemText.text(current.line.firstItem+zc) == QChar(10))
						|| (itemText.text(current.line.firstItem+zc) == SpecialChars::PARSEP) || (itemText.text(current.line.firstItem+zc) == SpecialChars::NBHYPHEN)
						|| (itemText.text(current.line.firstItem+zc) == SpecialChars::COLBREAK) || (itemText.text(current.line.firstItem+zc) == SpecialChars::FRAMEBREAK)
						|| (itemText.text(current.line.firstItem+zc) == SpecialChars::LINEBREAK) || (itemText.text(current.line.firstItem+zc) == SpecialChars::NBSPACE))
						continue;
					if (itemText.object(current.line.firstItem+zc) != 0)
						currasce = QMAX(currasce, (itemText.object(current.line.firstItem+zc)->gHeight + itemText.object(current.line.firstItem+zc)->lineWidth()) * (itemText.charStyle(current.line.firstItem+zc).scaleV() / 1000.0));
					else //if (itemText.charStyle(current.line.firstItem+zc).effects() & ScStyle_DropCap == 0)
						currasce = QMAX(currasce, itemText.charStyle(current.line.firstItem+zc).font().height(itemText.charStyle(current.line.firstItem+zc).fontSize() / 10.0));
				}
				double adj = firstasce - currasce;
				current.line.ascent = currasce;
				current.line.y -= adj;
				current.yPos -= adj;
			}
			if ( itemText.charStyle(current.line.firstItem).effects() & ScStyle_DropCap )
			{
				// put line back to top
				current.line.y -= DropCapDrop;
				itemText.item(current.line.firstItem)->glyph.yoffset += DropCapDrop;
			}
		}
		fillInTabLeaders(itemText, current.line);
		current.startOfCol = false;
		goNextColumn = false;

//		qDebug(QString("layout: last line %1 - %2 @ (%3,%4) wd %5/%6").arg(current.line.firstItem).arg(current.line.lastItem)
//			   .arg(current.line.x).arg(current.line.y).arg(current.line.naturalWidth).arg(current.line.width));
		
		if (current.itemsInLine > 0) {
			itemText.appendLine(current.line);
		}
	}
	MaxChars = itemText.length();
	invalid = false;
	pf2.end();
	if (NextBox != NULL) {
		NextBox->invalid = true;
		dynamic_cast<PageItem_TextFrame*>(NextBox)->firstChar = MaxChars;
	}
//	qDebug("textframe: len=%d, done relayout", itemText.length());
	return;
			
NoRoom:     
	pf2.end();
	invalid = false;
	PageItem_TextFrame * next = dynamic_cast<PageItem_TextFrame*>(NextBox);
	if (next != 0)
	{
		next->invalid = true;
		next->firstChar = MaxChars;
		if (CPos > signed(MaxChars))
		{
			int nCP = CPos;
//			CPos = MaxChars;
			if ((m_Doc->appMode == modeEdit) && (Tinput))
			{
				//							OwnPage->Deselect(true);
				next->CPos = QMAX(nCP, signed(MaxChars));
				//							Doc->currentPage = NextBox->OwnPage;
				//							NextBox->OwnPage->SelectItemNr(NextBox->ItemNr);
//				qDebug("textframe: len=%d, leaving relayout in editmode && Tinput", itemText.length());
				return;
			}
		}
		// relayout next frame
//		qDebug("textframe: len=%d, going to next", itemText.length());
		next->layout();
	}
//	qDebug("textframe: len=%d, done relayout (no room %d)", itemText.length(), MaxChars);
}


void PageItem_TextFrame::DrawObj_Item(ScPainter *p, QRect e, double sc)
{
	layout();
	if (invalid)
		return;
	
	ScribusView* view = m_Doc->view();
	QPainter pf2;
	QPoint pt1, pt2;
	QRegion cm;
	double wide, lineCorr;
	QString chstr;
	ScText *hl;
	QString cachedStroke = "";
	QString cachedFill = "";
	int cachedFillShade = -1;
	int cachedStrokeShade = -1;
	QString actStroke = "";
	QString actFill = "";
	int actFillShade = -1;
	int actStrokeShade = -1;
	QColor cachedFillQ;
	QColor cachedStrokeQ;
//	QValueList<ParagraphStyle::TabRecord> tTabValues;
	double desc, asce, tabDist;
//	tTabValues.clear();
	p->save();
	pf2.begin(view->viewport());
	QRect e2;
	if (isEmbedded)
		e2 = e;
	else
	{
		e2 = QRect(qRound(e.x()  / sc + m_Doc->minCanvasCoordinate.x()), qRound(e.y()  / sc + m_Doc->minCanvasCoordinate.y()), qRound(e.width() / sc), qRound(e.height() / sc));
		pf2.translate(Xpos, Ypos);
	}
	pf2.rotate(Rot);
	if (!m_Doc->layerOutline(LayerNr))
	{
		if ((fillColor() != CommonStrings::None) || (GrType != 0))
		{
			p->setupPolygon(&PoLine);
			p->fillPath();
		}
	}
	if (lineColor() != CommonStrings::None)
		lineCorr = m_lineWidth / 2.0;
	else
		lineCorr = 0;
	if ((isAnnotation()) && (annotation().Type() == 2) && (!Pfile.isEmpty()) && (PicAvail) && (PicArt) && (annotation().UseIcons()))
	{
		p->setupPolygon(&PoLine);
		p->setClipPath();
		p->save();
		p->scale(LocalScX, LocalScY);
		p->translate(static_cast<int>(LocalX*LocalScX), static_cast<int>(LocalY*LocalScY));
		if (pixm.width() > 0 && pixm.height() > 0) {
			QImage img(pixm.qImage());
			p->drawImage(&img);
		}
		p->restore();
	}
	if (itemText.length() != 0)
	{
//		qDebug("drawing textframe: len=%d", itemText.count());
		if (imageFlippedH())
		{
			p->translate(Width * sc, 0);
			p->scale(-1, 1);
		}
		if (imageFlippedV())
		{
			p->translate(0, Height * sc);
			p->scale(1, -1);
		}
		uint tabCc = 0;
		assert( firstInFrame() >= 0 );
		assert( lastInFrame() < itemText.length() );
		LineSpec ls;
		for (uint ll=0; ll < itemText.lines(); ++ll) {
			ls = itemText.line(ll);
			tabDist = ls.x;
			double CurX = ls.x;
//			p->setLineWidth(0);
//			p->setBrush(Qt::yellow);
//			p->drawRect(ls.x, ls.y-ls.ascent, ls.width, ls.ascent);
//			p->setBrush(Qt::red);
//			p->drawRect(ls.x, ls.y, ls.width, ls.descent);
			
			QColor tmp;
			for (int a = ls.firstItem; a <= ls.lastItem; ++a)
			{
				hl = itemText.item(a);
				const CharStyle& charStyle(itemText.charStyle(a));
				double chs = charStyle.fontSize() * hl->glyph.scaleV;
				bool selected = itemText.selected(a);
				if (charStyle.effects() & ScStyle_StartOfLine)
					tabCc = 0;
				chstr = hl->ch;
				actFill = charStyle.fillColor();
				actFillShade = charStyle.fillShade();
				if (actFill != CommonStrings::None)
				{
					if ((cachedFillShade != actFillShade) || (cachedFill != actFill))
					{
						SetFarbe(&tmp, actFill, actFillShade);
						p->setBrush(tmp);
						cachedFillQ = tmp;
						cachedFill = actFill;
						cachedFillShade = actFillShade;
					}
					else
						p->setBrush(cachedFillQ);
				}
				if (charStyle.effects() & ScStyle_DropCap)
				{
					const ParagraphStyle& style(itemText.paragraphStyle(a));
					if (style.lineSpacingMode() == ParagraphStyle::BaselineGridLineSpacing)
						chs = qRound(10 * ((m_Doc->typographicSettings.valueBaseGrid * (style.dropCapLines()-1) + (charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / charStyle.font().realCharHeight(chstr[0], 10)));
					else
					{
						if (style.lineSpacingMode() == ParagraphStyle::FixedLineSpacing)
							chs = qRound(10 * ((style.lineSpacing() * (style.dropCapLines()-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / charStyle.font().realCharHeight(chstr[0], 10)));
						else
						{
							double currasce = charStyle.font().height(style.charStyle().fontSize() / 10.0);
							chs = qRound(10 * ((currasce * (style.dropCapLines()-1)+(charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / charStyle.font().realCharHeight(chstr[0], 10)));
						}
					}
				}
				if (chstr[0] == SpecialChars::TAB)
					tabCc++;
				// paint selection
				if (!m_Doc->RePos)
				{
					double xcoZli = CurX + hl->glyph.xoffset;
					desc = - charStyle.font().descent(charStyle.fontSize() / 10.0);
					asce = charStyle.font().ascent(charStyle.fontSize() / 10.0);
					if (((selected && Select) || ((NextBox != 0 || BackBox != 0) && selected)) && (m_Doc->appMode == modeEdit))
					{
						wide = hl->glyph.xadvance;
						p->setFillMode(1);
						//							p->setBrush(darkBlue);
						p->setBrush(qApp->palette().color(QPalette::Active, QColorGroup::Highlight));
						p->setLineWidth(0);
//						if ((a > 0) && (QChar(hl->glyph.glyph) == SpecialChars::TAB))
//						{
//							xcoZli = CurX + itemText.item(a-1)->glyph.xoffset + itemText.charStyle(a-1).font().charWidth(itemText.text(a-1), itemText.charStyle(a-1).fontSize() / 10.0);
//							wide = CurX + hl->glyph.xoffset - xcoZli + hl->glyph.xadvance;
//						}
						if (!m_Doc->RePos)
							p->drawRect(xcoZli, qRound(ls.y + hl->glyph.yoffset - asce * hl->glyph.scaleV), wide+1, qRound((asce+desc) * (hl->glyph.scaleV)));
						p->setBrush(qApp->palette().color(QPalette::Active, QColorGroup::HighlightedText));
						//							p->setBrush(white);
					}
					actStroke = charStyle.strokeColor();
					actStrokeShade = charStyle.strokeShade();
					if (actStroke != CommonStrings::None)
					{
						if ((cachedStrokeShade != actStrokeShade) || (cachedStroke != actStroke))
						{
							SetFarbe(&tmp, actStroke, actStrokeShade);
							p->setPen(tmp, 1, SolidLine, FlatCap, MiterJoin);
							cachedStrokeQ = tmp;
							cachedStroke = actStroke;
							cachedStrokeShade = actStrokeShade;
						}
						else
							p->setPen(cachedStrokeQ, 1, SolidLine, FlatCap, MiterJoin);
					}
					// paint glyphs
					if (e2.intersects(pf2.xForm(QRect(qRound(CurX + hl->glyph.xoffset),qRound(ls.y + hl->glyph.yoffset-asce), qRound(hl->glyph.xadvance+1), qRound(asce+desc)))))
					{
						p->save();
#ifdef HAVE_CAIRO
						p->translate(CurX, ls.y);
#else
						p->translate(CurX * p->zoomFactor(), ls.y * p->zoomFactor());
#endif
						if (hl->ch[0] == SpecialChars::OBJECT) 
						{
							DrawObj_Embedded(p, e, charStyle, hl->cembedded);
#ifdef HAVE_CAIRO
							CurX += (hl->cembedded->gWidth + hl->cembedded->lineWidth());
#else
							CurX += (hl->cembedded->gWidth + hl->cembedded->lineWidth()) *  p->zoomFactor();
#endif
						}
						else
						{
							drawGlyphs(p, charStyle, hl->glyph);
							CurX += hl->glyph.wide();
						}
						p->restore();
					}		
				}
				tabDist = CurX;
			}
		}
	}
	else {
//		qDebug("skipping textframe: len=%d", itemText.count());
	}

	pf2.end();
	p->restore();
}


void PageItem_TextFrame::DrawObj_Post(ScPainter *p)
{
	ScribusView* view = m_Doc->view();
	if (m_Doc->layerOutline(LayerNr))
	{
		p->setPen(m_Doc->layerMarker(LayerNr), 1, SolidLine, FlatCap, MiterJoin);
		p->setFillMode(ScPainter::None);
		p->setBrushOpacity(1.0);
		p->setPenOpacity(1.0);
		p->setupPolygon(&PoLine);
		p->strokePath();
	}
	else
	{
#ifdef HAVE_CAIRO
//#if CAIRO_VERSION > CAIRO_VERSION_ENCODE(1, 1, 6)
		if (fillBlendmode() != 0)
			p->endLayer();
//#endif
#endif
		if (!m_Doc->RePos)
		{
#ifdef HAVE_CAIRO
//#if CAIRO_VERSION > CAIRO_VERSION_ENCODE(1, 1, 6)
			if (lineBlendmode() != 0)
				p->beginLayer(1.0 - lineTransparency(), lineBlendmode());
//#endif
#endif
			if (lineColor() != CommonStrings::None)
			{
				p->setPen(strokeQColor, m_lineWidth, PLineArt, PLineEnd, PLineJoin);
				if (DashValues.count() != 0)
					p->setDash(DashValues, DashOffset);
			}
			else
				p->setLineWidth(0);
			if (!isTableItem)
			{
				p->setupPolygon(&PoLine);
				if (NamedLStyle.isEmpty())
					p->strokePath();
				else
				{
					multiLine ml = m_Doc->MLineStyles[NamedLStyle];
					QColor tmp;
					for (int it = ml.size()-1; it > -1; it--)
					{
						SetFarbe(&tmp, ml[it].Color, ml[it].Shade);
						p->setPen(tmp, ml[it].Width,
								static_cast<PenStyle>(ml[it].Dash),
								static_cast<PenCapStyle>(ml[it].LineEnd),
								static_cast<PenJoinStyle>(ml[it].LineJoin));
						p->strokePath();
					}
				}
			}
#ifdef HAVE_CAIRO
//#if CAIRO_VERSION > CAIRO_VERSION_ENCODE(1, 1, 6)
			if (lineBlendmode() != 0)
				p->endLayer();
//#endif
#endif
		}
	}
	if ((!isEmbedded) && (!m_Doc->RePos))
	{
		double scpInv = 1.0 / (QMAX(view->scale(), 1));
		if ((Frame) && (m_Doc->guidesSettings.framesShown) && ((itemType() == ImageFrame) || (itemType() == TextFrame) || (itemType() == PathText)))
		{
			p->setPen(PrefsManager::instance()->appPrefs.DFrameNormColor, scpInv, DotLine, FlatCap, MiterJoin);
			if ((isBookmark) || (m_isAnnotation))
				p->setPen(PrefsManager::instance()->appPrefs.DFrameAnnotationColor, scpInv, DotLine, FlatCap, MiterJoin);
			if ((BackBox != 0) || (NextBox != 0))
				p->setPen(PrefsManager::instance()->appPrefs.DFrameLinkColor, scpInv, SolidLine, FlatCap, MiterJoin);
			if (m_Locked)
				p->setPen(PrefsManager::instance()->appPrefs.DFrameLockColor, scpInv, SolidLine, FlatCap, MiterJoin);

			p->setFillMode(0);
			if (itemType()==PathText)
			{
				if (Clip.count() != 0)
				{
					FPointArray tclip;
					FPoint np = FPoint(Clip.point(0));
					tclip.resize(2);
					tclip.setPoint(0, np);
					tclip.setPoint(1, np);
					for (uint a = 1; a < Clip.size(); ++a)
					{
						np = FPoint(Clip.point(a));
						tclip.putPoints(tclip.size(), 4, np.x(), np.y(), np.x(), np.y(), np.x(), np.y(), np.x(), np.y());
					}
					np = FPoint(Clip.point(0));
					tclip.putPoints(tclip.size(), 2, np.x(), np.y(), np.x(), np.y());
					p->setupPolygon(&tclip);
				}
			}
			else
				p->setupPolygon(&PoLine);
			p->strokePath();
		}
		if ((m_Doc->guidesSettings.framesShown) && textFlowUsesContourLine() && (ContourLine.size() != 0))
		{
			p->setPen(lightGray, scpInv, DotLine, FlatCap, MiterJoin);
			p->setupPolygon(&ContourLine);
			p->strokePath();
		}

		//Draw the overflow icon
		if (frameOverflows())
		{//CB && added here for jghali prior to commit access
			if ((!view->previewMode) && (!view->viewAsPreview))
				drawOverflowMarker(p);
		}
		if ((m_Doc->guidesSettings.colBordersShown) && ((!view->previewMode) && (!view->viewAsPreview)))
			drawColumnBorders(p);
		if ((m_Doc->guidesSettings.layerMarkersShown) && (m_Doc->layerCount() > 1) && (!m_Doc->layerOutline(LayerNr)))
		{
			p->setPen(black, 0.5/ m_Doc->view()->scale(), SolidLine, FlatCap, MiterJoin);
			p->setPenOpacity(1.0);
			p->setBrush(m_Doc->layerMarker(LayerNr));
			p->setBrushOpacity(1.0);
			p->setFillMode(ScPainter::Solid);
			double ofwh = 10;
			double ofx = Width - ofwh/2;
			double ofy = Height - ofwh*3;
			p->drawRect(ofx, ofy, ofwh, ofwh);
		}
		//if (m_Doc->selection->findItem(this)!=-1)
		//	drawLockedMarker(p);
	}
	Tinput = false;
	FrameOnly = false;
	p->restore();
}


void PageItem_TextFrame::clearContents()
{
	PageItem *nextItem = this;
	while (nextItem != 0)
	{
		if (nextItem->prevInChain() != 0)
			nextItem = nextItem->prevInChain();
		else
			break;
	}
	while (nextItem != 0)
	{
		nextItem->CPos = 0;
		nextItem->itemText.clear();
		nextItem->invalid = true;
		nextItem = nextItem->nextInChain();
	}
}

void PageItem_TextFrame::handleModeEditKey(QKeyEvent *k, bool& keyRepeat)
{
	int oldPos = CPos; // 15-mar-2004 jjsa for cursor movement with Shift + Arrow key
	int kk = k->key();
	int as = k->ascii();
	QString uc = k->text();
	QString cr, Tcha, Twort;
	uint Tcoun;
	int len, pos;
	int KeyMod;
	ScribusView* view = m_Doc->view();
	ButtonState buttonState = k->state();
	switch (buttonState)
	{
	case ShiftButton:
		KeyMod = SHIFT;
		break;
	case AltButton:
		KeyMod = ALT;
		break;
	case ControlButton:
		KeyMod = CTRL;
		break;
	default:
		KeyMod = 0;
		break;
	}

	view->slotDoCurs(false);
	switch (kk)
	{
	case Key_Prior:
	case Key_Next:
	case Key_End:
	case Key_Home:
	case Key_Right:
	case Key_Left:
	case Key_Up:
	case Key_Down:
		if ( (buttonState & ShiftButton) == 0 )
			deselectAll();
	}
	//<< ISO 14755
	//if ((buttonState & ControlButton) && (buttonState & ShiftButton))
	//{
	//	if (!unicodeTextEditMode)
	//	{
	//		unicodeTextEditMode=true;
	//		unicodeInputCount = 0;
	//		unicodeInputString = "";
	//		keyrep = false;
	//	}
	//	qDebug(QString("%1 %2 %3 %4 %5").arg("uni").arg("c+s").arg(uc).arg(kk).arg(as));
	//}
	//>>
	if (unicodeTextEditMode)
	{
		int conv = 0;
		bool ok = false;
		unicodeInputString += uc;
		conv = unicodeInputString.toInt(&ok, 16);
		if (!ok)
		{
			unicodeTextEditMode = false;
			unicodeInputCount = 0;
			unicodeInputString = "";
			keyRepeat = false;
			return;
		}
		unicodeInputCount++;
		if (unicodeInputCount == 4)
		{
			unicodeTextEditMode = false;
			unicodeInputCount = 0;
			unicodeInputString = "";
			if (ok)
			{
				if (itemText.lengthOfSelection() > 0)
					deleteSelectedTextFromFrame();
				if (conv < 31)
					conv = 32;
				itemText.insertChars(CPos, QString(QChar(conv)));
				CPos += 1;
				Tinput = true;
				m_Doc->scMW()->setTBvals(this);
				view->RefreshItem(this);
				keyRepeat = false;
				return;
			}
		}
		else
		{
			keyRepeat = false;
			return;
		}
	}
	switch (kk)
	{
	case Key_F12:
		unicodeTextEditMode = true;
		unicodeInputCount = 0;
		unicodeInputString = "";
		keyRepeat = false;
		return;
		break;
	case Key_Home:
		// go to begin of line
		if ( (pos = CPos) == firstInFrame() )
			break; // at begin of frame
		len = lastInFrame();
		if ( pos >= len )
			pos = len-1;
		if ( (buttonState & ControlButton) == 0 )
		{
			pos = itemText.startOfLine(pos);
		}
		else
		{
			//Control Home for start of frame text
			pos = itemText.startOfFrame(pos);
		}
		CPos = pos;
		if ( buttonState & ShiftButton )
			ExpandSel(-1, oldPos);
		if ( this->itemText.lengthOfSelection() > 0 )
			view->RefreshItem(this);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_End:
		// go to end of line
		len = lastInFrame();
		if ( CPos >= len )
			break; // at end of frame
		if ( (buttonState & ControlButton) == 0 )
		{
			CPos = itemText.endOfLine(CPos);
		}
		else
		{
			//Control End for end of frame text
			CPos = itemText.endOfFrame(CPos);
		}
		if ( buttonState & ShiftButton )
			ExpandSel(1, oldPos);
		if ( this->itemText.lengthOfSelection() > 0 )
			view->RefreshItem(this);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_Down:
		if (buttonState & ControlButton)
		{
			// go to end of paragraph
			len = itemText.length();
			CPos = itemText.nextParagraph(CPos);
			if ( buttonState & ShiftButton )
				ExpandSel(1, oldPos);
		}
		else
		{
			if (CPos <= lastInFrame())
			{
				CPos = itemText.nextLine(CPos);
				if ( buttonState & ShiftButton )
				{
					if ( buttonState & AltButton )
						CPos = lastInFrame()+1;
					ExpandSel(1, oldPos);
				}
				else 
					if (CPos > lastInFrame() && NextBox != 0)
					{
						if (NextBox->frameDisplays(CPos))
						{
							view->Deselect(true);
							NextBox->CPos = CPos;
							view->SelectItemNr(NextBox->ItemNr);
						}
					}
			}
			else
			{
				if (NextBox != 0)
				{
					if (NextBox->frameDisplays(lastInFrame()+1))
					{
						view->Deselect(true);
						NextBox->CPos = lastInFrame()+1;
						view->SelectItemNr(NextBox->ItemNr);
					}
				}
			}
		}
		if ( this->itemText.lengthOfSelection() > 0 )
			view->RefreshItem(this);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_Up:
		if (buttonState & ControlButton)
		{
			if ( (pos = CPos) == firstInFrame() )
				break; // at begin of frame
			len = itemText.length();
			CPos = itemText.prevParagraph(CPos);
			if ( buttonState & ShiftButton )
				ExpandSel(-1, oldPos);
		}
		else
		{
			if (CPos > firstInFrame())
			{
				if (CPos > lastInFrame() || CPos >= itemText.length())
					CPos = lastInFrame();
				CPos = itemText.prevLine(CPos);
				if ( buttonState & ShiftButton )
				{
					if ( buttonState & AltButton )
						CPos = firstInFrame();
					ExpandSel(-1, oldPos);
				}
				else
					if (CPos == firstInFrame() && BackBox != 0)
					{
						view->Deselect(true);
						BackBox->CPos = BackBox->lastInFrame();
						view->SelectItemNr(BackBox->ItemNr);
					}
			}
			else
			{
				CPos = firstInFrame();
				if (BackBox != 0)
				{
					view->Deselect(true);
					BackBox->CPos = BackBox->lastInFrame();
					view->SelectItemNr(BackBox->ItemNr);
				}
			}
		}
		if ( this->itemText.lengthOfSelection() > 0 )
			view->RefreshItem(this);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_Prior:
		CPos = itemText.startOfFrame(CPos);
		if ( buttonState & ShiftButton )
			ExpandSel(-1, oldPos);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_Next:
		CPos = itemText.endOfFrame(CPos);
		if ( buttonState & ShiftButton )
			ExpandSel(1, oldPos);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_Left:
		if ( buttonState & ControlButton )
		{
			setNewPos(oldPos, itemText.length(), -1);
			if ( buttonState & ShiftButton )
				ExpandSel(-1, oldPos);
		}
		else if ( buttonState & ShiftButton )
		{
			--CPos;
			if ( CPos < 0 )
				CPos = 0;
			else
				ExpandSel(-1, oldPos);
		}
		else
		{
			--CPos;
			if (CPos < firstInFrame())
			{
				CPos = firstInFrame();
				if (BackBox != 0)
				{
					view->Deselect(true);
					BackBox->CPos = BackBox->lastInFrame();
					view->SelectItemNr(BackBox->ItemNr);
					//currItem = currItem->BackBox;
				}
			}
		}
		if ((CPos > 0) && (CPos >= lastInFrame()))
		{
			CPos = lastInFrame();
			if (itemText.charStyle(CPos-1).effects() & ScStyle_SuppressSpace)
			{
				--CPos;
				while ((CPos > 0) && (itemText.charStyle(CPos).effects() & ScStyle_SuppressSpace))
				{
					--CPos;
					if (CPos == 0)
						break;
				}
			}
		}
		else
		{
			while ((CPos > 0) && (itemText.charStyle(CPos).effects() & ScStyle_SuppressSpace))
			{
				--CPos;
				if (CPos == 0)
					break;
			}
		}
		if ( itemText.lengthOfSelection() > 0 )
			view->RefreshItem(this);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_Right:
		if ( buttonState & ControlButton )
		{
			setNewPos(oldPos, itemText.length(), 1);
			if ( buttonState & ShiftButton )
				ExpandSel(1, oldPos);
		}
		else if ( buttonState & ShiftButton )
		{
			++CPos;
			if ( CPos > itemText.length() )
				--CPos;
			else
				ExpandSel(1, oldPos);
		}
		else
		{
			++CPos; // new position within text ?
			if (CPos > lastInFrame())
			{
//				--CPos;
				CPos = lastInFrame() + 1;
				if (NextBox != 0)
				{
					if (NextBox->frameDisplays(CPos))
					{
						view->Deselect(true);
						NextBox->CPos = CPos;
						view->SelectItemNr(NextBox->ItemNr);
						//currItem = currItem->NextBox;
					}
				}
			}
		}
		if ( itemText.lengthOfSelection() > 0 )
			view->RefreshItem(this);
		m_Doc->scMW()->setTBvals(this);
		break;
	case Key_Delete:
		if (CPos == itemText.length())
		{
			if (itemText.lengthOfSelection() > 0)
			{
				deleteSelectedTextFromFrame();
				m_Doc->scMW()->setTBvals(this);
				view->RefreshItem(this);
			}
			keyRepeat = false;
			return;
		}
		if (itemText.length() == 0)
		{
			keyRepeat = false;
			return;
		}
		cr = itemText.text(CPos,1);
		if (itemText.lengthOfSelection() == 0)
			itemText.select(CPos, 1, true);
		deleteSelectedTextFromFrame();
		Tinput = false;
		if ((cr == QChar(13)) && (itemText.length() != 0))
		{
//			m_Doc->chAbStyle(this, findParagraphStyle(m_Doc, itemText.paragraphStyle(QMAX(CPos-1,0))));
			Tinput = false;
		}
		m_Doc->scMW()->setTBvals(this);
		view->RefreshItem(this);
		break;
	case Key_Backspace:
		if (CPos == 0)
		{
			if (itemText.lengthOfSelection() > 0)
			{
				deleteSelectedTextFromFrame();
				m_Doc->scMW()->setTBvals(this);
				view->RefreshItem(this);
			}
			break;
		}
		if (itemText.length() == 0)
			break;
		cr = itemText.text(QMAX(CPos-1,0),1);
		if (itemText.lengthOfSelection() == 0)
		{
			--CPos;
			itemText.select(CPos, 1, true);
		}
		deleteSelectedTextFromFrame();
		Tinput = false;
		if ((cr == QChar(13)) && (itemText.length() != 0))
		{
//			m_Doc->chAbStyle(this, findParagraphStyle(m_Doc, itemText.paragraphStyle(QMAX(CPos-1,0))));
			Tinput = false;
		}
		m_Doc->scMW()->setTBvals(this);
		view->RefreshItem(this);
		break;
	default:
		if ((itemText.lengthOfSelection() > 0) && (kk < 0x1000))
			deleteSelectedTextFromFrame();
		//if ((kk == Key_Tab) || ((kk == Key_Return) && (buttonState & ShiftButton)))
		if (kk == Key_Tab)
		{
			itemText.insertChars(CPos, QString(SpecialChars::TAB));
			CPos += 1;
			Tinput = true;
			view->RefreshItem(this);
			break;
		}
		if ((uc[0] > QChar(31) && m_Doc->currentStyle.charStyle().font().canRender(uc[0])) || (as == 13) || (as == 30))
		{
			itemText.insertChars(CPos, uc);
			CPos += 1;
			if ((m_Doc->docHyphenator->AutoCheck) && (CPos > 1))
			{
				Twort = "";
				Tcoun = 0;
				for (int hych = CPos-1; hych > -1; hych--)
				{
					Tcha = itemText.text(hych,1);
					if (Tcha[0] == ' ')
					{
						Tcoun = hych+1;
						break;
					}
					Twort.prepend(Tcha);
				}
				if (!Twort.isEmpty())
				{
					m_Doc->docHyphenator->slotHyphenateWord(this, Twort, Tcoun);
				}
			}
			Tinput = true;
			view->RefreshItem(this);
		}
		break;
	}
	view->slotDoCurs(true);
	if ((kk == Key_Left) || (kk == Key_Right) || (kk == Key_Up) || (kk == Key_Down))
	{
		keyRepeat = false;
		return;
	}
}

void PageItem_TextFrame::deleteSelectedTextFromFrame()
{
	if (itemText.lengthOfSelection() > 0) {
		CPos = itemText.startOfSelection();
		itemText.removeSelection();
		HasSel = false;
	}
	m_Doc->updateFrameItems();
	m_Doc->scMW()->DisableTxEdit();
}


//CB Rewrote JJSA code, March 06
// jjsa added on 15-mar-2004
// calculate the end position while ctrl + arrow pressed

void PageItem_TextFrame::setNewPos(int oldPos, int len, int dir)
{
	
	bool isSpace, wasSpace;
	if ( dir > 0 && oldPos < len )
	{
		wasSpace = itemText.text(oldPos).isSpace();
		CPos=oldPos+1;
		while (CPos<len)
		{
			isSpace = itemText.text(CPos).isSpace();
			if (wasSpace && !isSpace)
				break;
			++CPos;
			wasSpace=isSpace;
			
		}
		/*
		isSpace = itemText.at(oldPos)->ch.at(0).isSpace();
		CPos = oldPos +1;
		for (int i=oldPos+1; i < len; i++)
		{
			if ( itemText.at(i)->ch.at(0).isSpace() != isSpace )
				break;
			CPos++;
		}
		*/
	}
	else if ( dir < 0 && oldPos > 0 )
	{
		CPos=oldPos-1;
		wasSpace = itemText.text(CPos).isSpace();
		while (CPos>0)
		{
			isSpace = itemText.text(CPos).isSpace();
			if (!wasSpace && isSpace)
			{
				++CPos;
				break;
			}
			--CPos;
			wasSpace=isSpace;
			
		}
		/*
		oldPos--;
		isSpace = itemText.at(oldPos)->ch.at(0).isSpace();
		for (int i=oldPos; i >= 0; i--)
		{
			if (  itemText.at(i)->ch.at(0).isSpace() != isSpace )
				break;
			CPos--;
		}
		*/
	}
}



// jjsa added on 15-mar-2004 expand / decrease selection

// jjsa added on 14-mar-2004 text selection with pressed
// shift button and <-, -> cursor keys
// Parameters
//   PageItem *currItem text item to be processed
//   inc < 0 for left key > 0 for right key
//  if value is +/-1 work on slection
//  if value is +/-2 refresh if text under cursor is selected

void PageItem_TextFrame::ExpandSel(int dir, int oldPos)
{
	int len = itemText.length();
	ScribusView* view = m_Doc->view();
	bool rightSel = false; // assume left right and actual char not selected
	bool leftSel  = false;
	bool actSel   = false;
	bool selMode  = false;

	if ( dir == -1 || dir == 1 )
		selMode = true;
	else
	{
		if ( dir > 0 )
			dir = 1;
		else
			dir = -1;
	}
   // show for selection of previous, actual and next character
	if ( itemText.lengthOfSelection() > 0 ) /* selection already present */
	{
		if (dir > 0 && oldPos < len) // -> key
		{
			if ( oldPos == 0 )
				leftSel = false;
			else
				leftSel = itemText.selected(oldPos-1);
			actSel = itemText.selected(oldPos);
			rightSel = false; // not relevant
		}
		else if ( dir > 0 && oldPos == len) // -> key
		{
			return;
		}
		else if ( dir < 0 && oldPos > 0 ) // <- key
		{
			actSel = itemText.selected(oldPos-1);
			leftSel = false; // not relevant
			if ( oldPos < len  )
				rightSel = itemText.selected(oldPos);
			else
				rightSel = false;
		}
		else if ( dir < 0 && oldPos == 0 ) // <- key
		{
         return;
		}
		if ( selMode && !(leftSel||actSel||rightSel) )
		{
         // selected outside from concerned range
			itemText.deselectAll();
			HasSel = false;
			//CB Replace with direct call for now //emit HasNoTextSel();
			m_Doc->scMW()->DisableTxEdit();
		}
		else if ( !selMode )
		{
			if (leftSel||actSel||rightSel)
				view->RefreshItem(this);
		}
	}
	if ( !selMode )
		return;
   // no selection
	if ( !HasSel )
	{
		HasSel = true;
		//CB Replace with direct call for now //emit HasTextSel();
		m_Doc->scMW()->EnableTxEdit();
		leftSel = true;
		rightSel = true;
	}
	int start;
	int end;
	int sel;
	if (dir == 1) // ->  key
	{
		start = oldPos;
		end   = CPos;
		sel = leftSel == true;
	}
	else
	{
		start = CPos;
		end   = oldPos;
		sel = rightSel == true;
	}
	itemText.select(start, end-start, sel);
	if ( ! sel )
		//CB Replace with direct call for now //emit  HasNoTextSel();
		m_Doc->scMW()->DisableTxEdit();
	view->RefreshItem(this);
}

void PageItem_TextFrame::deselectAll()
{
	PageItem *item = this;
	while( item->prevInChain() )
		item=item->prevInChain();

	while ( item )
	{
		if ( item->itemText.lengthOfSelection() > 0 )
		{
			item->itemText.deselectAll();
			m_Doc->view()->RefreshItem(this);
			item->HasSel = false;
		}
		item = item->nextInChain();
	}
	//CB Replace with direct call for now //emit HasNoTextSel();
	m_Doc->scMW()->DisableTxEdit();
}

double PageItem_TextFrame::columnWidth()
{
	double lineCorr;
	if (lineColor() != CommonStrings::None)
		lineCorr = m_lineWidth;
	else
		lineCorr = 0;
	return (Width - (ColGap * (Cols - 1)) - Extra - RExtra - 2 * lineCorr) / Cols;
//	return (Width - (ColGap * (Cols - 1)) - Extra - RExtra - lineCorr) / Cols;
}

void PageItem_TextFrame::drawOverflowMarker(ScPainter *p)
{
	/*CB Old large corner indicator.
	double scp1 = 1.0/QMAX(ScMW->view->getScale(), 1);
	double scp16 = 16.0*scp1;
	double scp14 = 14.0*scp1;
	double scp3 = 3.0*scp1;
	double scm_lineWidth16 = Width - scp16;
	double scpheight16 = Height - scp16;
	double scm_lineWidth3 = Width - scp3;
	double scpheight3 = Height - scp3;
	p->setPen(black, scp1, SolidLine, FlatCap, MiterJoin);
	p->setBrush(white);
	p->drawRect(scm_lineWidth16, scpheight16, scp14, scp14);
	p->drawLine(FPoint(scm_lineWidth16, scpheight16), FPoint(scm_lineWidth3, scpheight3));
	p->drawLine(FPoint(scm_lineWidth16, scpheight3), FPoint(scm_lineWidth3, scpheight16));
	*/
	//TODO: CB clean
	ScribusView* view = m_Doc->view();
	double scp1 = 1 ;// / ScMW->view->scale();
	double ofwh = 8 * scp1;
	//CB moved down while locked marker disabled
	//double ofx = Width - ofwh/2;
	//double ofy = Height - ofwh*3.0;
	double ofx = Width - ofwh/2;
	double ofy = Height - ofwh*1.5;
	double lx1= ofx;
	double ly1= ofy;
	double lx2= ofx+ofwh;
	double ly2= ofy+ofwh;
	p->setPen(black, 0.5/ view->scale(), SolidLine, FlatCap, MiterJoin);
	p->setPenOpacity(1.0);
	p->setBrush(Qt::white);
	p->setBrushOpacity(1.0);
	p->setFillMode(ScPainter::Solid);
	p->drawRect(ofx, ofy, ofwh, ofwh);
	p->drawLine(FPoint(lx1, ly1), FPoint(lx2, ly2));
	p->drawLine(FPoint(lx1, ly2), FPoint(lx2, ly1));
}

void PageItem_TextFrame::drawColumnBorders(ScPainter *p)
{
	ScribusView* view = m_Doc->view();
	p->setPen(black, 0.5/ view->scale(), SolidLine, FlatCap, MiterJoin);
	p->setPenOpacity(1.0);
	p->setBrush(Qt::white);
	p->setBrushOpacity(1.0);
	p->setFillMode(ScPainter::Solid);
#ifdef HAVE_CAIRO
	p->setupPolygon(&PoLine);
	p->setClipPath();
#endif
	double colWidth = columnWidth();
	double colLeft=0;
	int curCol=0;
	double lineCorr=0;
	if (lineColor() != CommonStrings::None)
		lineCorr = m_lineWidth / 2.0;
	if (TExtra + lineCorr!=0.0)
		p->drawLine(FPoint(0, TExtra + lineCorr), FPoint(Width, TExtra + lineCorr));
	if (BExtra + lineCorr!=0.0)
		p->drawLine(FPoint(0, Height - BExtra - lineCorr), FPoint(Width, Height - BExtra - lineCorr));
	double oldColRightX = Extra + lineCorr;
	while(curCol < Cols)
	{
		colLeft=(colWidth + ColGap) * curCol + Extra + lineCorr;
		if (colLeft != 0.0)
			p->drawLine(FPoint(colLeft, 0), FPoint(colLeft, 0+Height));
		if (colLeft + colWidth != Width)
			p->drawLine(FPoint(colLeft+colWidth, 0), FPoint(colLeft+colWidth, 0+Height));
		oldColRightX=colLeft+colWidth;
		++curCol;
	}
	
}

#endif  //NLS_PROTO
