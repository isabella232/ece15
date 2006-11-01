/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "scpageoutput.h"

#include "qpainter.h"
#include "pageitem.h"
#include "cmsettings.h"
#include "commonstrings.h"
#include "pageitem_imageframe.h"
#include "pageitem_line.h"
#include "pageitem_pathtext.h"
#include "pageitem_polygon.h"
#include "pageitem_polyline.h"
#include "pageitem_textframe.h"
#include "scfonts.h"
#include "scribus.h"
#include "scimage.h"
#include "util.h"

ScPageOutput::ScPageOutput(ScribusDoc* doc, bool reloadImages, int resolution, bool useProfiles)
{
	m_doc = doc;
	m_reloadImages = reloadImages;
	m_imageRes = resolution;
	m_useProfiles = useProfiles;
}

ScImage::RequestType ScPageOutput::translateImageModeToRequest( ScPainterExBase::ImageMode mode )
{
	ScImage::RequestType value = ScImage::RGBData;
	if ( mode == ScPainterExBase::cmykImages )
		value = ScImage::CMYKData;
	else if ( mode == ScPainterExBase::rgbImages )
		value = ScImage::RGBData;
	else if ( mode == ScPainterExBase::rgbProofImages )
		value = ScImage::RGBProof;
	else if ( mode == ScPainterExBase::rawImages )
		value = ScImage::RawData;
	return value;
}

void ScPageOutput::DrawPage( Page* page, ScPainterExBase* painter)
{
	int clipx = static_cast<int>(page->xOffset());
	int clipy = static_cast<int>(page->yOffset());
	int clipw = qRound(page->width());
	int cliph = qRound(page->height());
	DrawMasterItems(painter, page, QRect(clipx, clipy, clipw, cliph));
	DrawPageItems(painter, page, QRect(clipx, clipy, clipw, cliph));
}

void ScPageOutput::DrawMasterItems(ScPainterExBase *painter, Page *page, QRect clip)
{
	double z = painter->zoomFactor();
	if (!page->MPageNam.isEmpty())
	{
		Page* Mp = m_doc->MasterPages.at(m_doc->MasterNames[page->MPageNam]);
		if (page->FromMaster.count() != 0)
		{
			int Lnr;
			struct Layer ll;
			PageItem *currItem;
			ll.isViewable = false;
			ll.LNr = 0;
			Lnr = 0;
			uint layerCount = m_doc->layerCount();
			for (uint la = 0; la < layerCount; ++la)
			{
				Level2Layer(m_doc, &ll, Lnr);
				bool pr = true;
				if ( !ll.isPrintable )
					pr = false;
				if ((ll.isViewable) && (pr))
				{
					uint pageFromMasterCount=page->FromMaster.count();
					for (uint a = 0; a < pageFromMasterCount; ++a)
					{
						currItem = page->FromMaster.at(a);
						if (currItem->LayerNr != ll.LNr)
							continue;
						if ((currItem->OwnPage != -1) && (currItem->OwnPage != static_cast<int>(Mp->pageNr())))
							continue;
						if (!currItem->printEnabled())
							continue;
						int savedOwnPage = currItem->OwnPage;
						double OldX = currItem->xPos();
						double OldY = currItem->yPos();
						double OldBX = currItem->BoundingX;
						double OldBY = currItem->BoundingY;
						currItem->OwnPage = page->pageNr();
						if (!currItem->ChangedMasterItem)
						{
							currItem->moveBy(-Mp->xOffset() + page->xOffset(), -Mp->yOffset() + page->yOffset());
							currItem->BoundingX = OldBX - Mp->xOffset() + page->xOffset();
							currItem->BoundingY = OldBY - Mp->yOffset() + page->yOffset();
						}
						/*if (evSpon)
							currItem->Dirty = true;*/
						QRect oldR(currItem->getRedrawBounding(m_scale));
						if (clip.intersects(oldR))
							DrawItem(currItem, painter, clip);
						currItem->OwnPage = savedOwnPage;
						if (!currItem->ChangedMasterItem)
						{
							currItem->setXPos(OldX);
							currItem->setYPos(OldY);
							currItem->BoundingX = OldBX;
							currItem->BoundingY = OldBY;
						}
					}
					for (uint a = 0; a < pageFromMasterCount; ++a)
					{
						currItem = page->FromMaster.at(a);
						if (currItem->LayerNr != ll.LNr)
							continue;
						if (!currItem->isTableItem)
							continue;
						if ((currItem->OwnPage != -1) && (currItem->OwnPage != static_cast<int>(Mp->pageNr())))
							continue;
						double OldX = currItem->xPos();
						double OldY = currItem->yPos();
						double OldBX = currItem->BoundingX;
						double OldBY = currItem->BoundingY;
						if (!currItem->ChangedMasterItem)
						{
							currItem->setXPos(OldX - Mp->xOffset() + page->xOffset());
							currItem->setYPos(OldY - Mp->yOffset() + page->yOffset());
							currItem->BoundingX = OldBX - Mp->xOffset() + page->xOffset();
							currItem->BoundingY = OldBY - Mp->yOffset() + page->yOffset();
						}
						QRect oldR(currItem->getRedrawBounding(m_scale));
						if (clip.intersects(oldR))
						{
							painter->setZoomFactor(m_scale);
							painter->save();
							painter->translate(currItem->xPos() * m_scale, currItem->yPos() * m_scale);
							painter->rotate(currItem->rotation());
							if (currItem->lineColor() != CommonStrings::None)
							{
								ScColorShade tmp( m_doc->PageColors[currItem->lineColor()], currItem->lineShade());
								if ((currItem->TopLine) || (currItem->RightLine) || (currItem->BottomLine) || (currItem->LeftLine))
								{
									painter->setPen(tmp, currItem->lineWidth(), currItem->PLineArt, Qt::SquareCap, currItem->PLineJoin);
									if (currItem->TopLine)
										painter->drawLine(FPoint(0.0, 0.0), FPoint(currItem->width(), 0.0));
									if (currItem->RightLine)
										painter->drawLine(FPoint(currItem->width(), 0.0), FPoint(currItem->width(), currItem->height()));
									if (currItem->BottomLine)
										painter->drawLine(FPoint(currItem->width(), currItem->height()), FPoint(0.0, currItem->height()));
									if (currItem->LeftLine)
										painter->drawLine(FPoint(0.0, currItem->height()), FPoint(0.0, 0.0));
								}
							}
							painter->restore();
						}
						if (!currItem->ChangedMasterItem)
						{
							currItem->setXPos(OldX);
							currItem->setYPos(OldY);
							currItem->BoundingX = OldBX;
							currItem->BoundingY = OldBY;
						}
					}
				}
				Lnr++;
			}
		}
	}
	painter->setZoomFactor(z);
}

void ScPageOutput::DrawPageItems(ScPainterExBase *painter, Page *page, QRect clip)
{
	//linkedFramesToShow.clear();
	double z = painter->zoomFactor();
	if (m_doc->Items->count() != 0)
	{
		//QPainter p;
		int Lnr=0;
		struct Layer ll;
		PageItem *currItem;
		ll.isViewable = false;
		ll.LNr = 0;
		uint layerCount = m_doc->layerCount();
		//int docCurrPageNo=static_cast<int>(m_doc->currentPageNumber());
		int docCurrPageNo=static_cast<int>(page->pageNr());
		for (uint la2 = 0; la2 < layerCount; ++la2)
		{
			Level2Layer(m_doc, &ll, Lnr);
			bool pr = true;
			if (!ll.isPrintable)
				pr = false;
			if ((ll.isViewable) && (pr))
			{
				QPtrListIterator<PageItem> docItem(*m_doc->Items);
				while ( (currItem = docItem.current()) != 0)
				{
					++docItem;
					if (currItem->LayerNr != ll.LNr)
						continue;
					if (!currItem->printEnabled())
						continue;
					if ((m_doc->masterPageMode()) && ((currItem->OwnPage != -1) && (currItem->OwnPage != docCurrPageNo)))
						continue;
					if (!m_doc->masterPageMode() && !currItem->OnMasterPage.isEmpty())
					{
						if (currItem->OnMasterPage != page->pageName())
							continue;
					}
					QRect oldR(currItem->getRedrawBounding(m_scale));
					if (clip.intersects(oldR))
					{
						/*if (evSpon)
							currItem->Dirty = true;*/
						/*if (forceRedraw)
							currItem->Dirty = false;*/
//						if ((!Mpressed) || (m_doc->EditClip))
							DrawItem( currItem, painter, clip );
						//currItem->Redrawn = true;
						if ((currItem->asTextFrame()) && ((currItem->NextBox != 0) || (currItem->BackBox != 0)))
						{
							PageItem *nextItem = currItem;
							while (nextItem != 0)
							{
								if (nextItem->BackBox != 0)
									nextItem = nextItem->BackBox;
								else
									break;
							}
							/*if (linkedFramesToShow.find(nextItem) == -1)
								linkedFramesToShow.append(nextItem);*/
						}
					}
				}
				QPtrListIterator<PageItem> docItem2(*m_doc->Items);
				while ( (currItem = docItem2.current()) != 0 )
				{
					++docItem2;
					if (currItem->LayerNr != ll.LNr)
						continue;
					if (!currItem->isTableItem)
						continue;
					QRect oldR(currItem->getRedrawBounding(m_scale));
					if (clip.intersects(oldR))
					{
						painter->setZoomFactor(m_scale);
						painter->save();
						painter->translate(currItem->xPos() * m_scale, currItem->yPos() * m_scale);
						painter->rotate(currItem->rotation());
						if (currItem->lineColor() != CommonStrings::None)
						{
							ScColorShade tmp( m_doc->PageColors[currItem->lineColor()], currItem->lineShade() );
							if ((currItem->TopLine) || (currItem->RightLine) || (currItem->BottomLine) || (currItem->LeftLine))
							{
								painter->setPen(tmp, currItem->lineWidth(), currItem->PLineArt, Qt::SquareCap, currItem->PLineJoin);
								if (currItem->TopLine)
									painter->drawLine(FPoint(0.0, 0.0), FPoint(currItem->width(), 0.0));
								if (currItem->RightLine)
									painter->drawLine(FPoint(currItem->width(), 0.0), FPoint(currItem->width(), currItem->height()));
								if (currItem->BottomLine)
									painter->drawLine(FPoint(currItem->width(), currItem->height()), FPoint(0.0, currItem->height()));
								if (currItem->LeftLine)
									painter->drawLine(FPoint(0.0, currItem->height()), FPoint(0.0, 0.0));
							}
						}
						painter->restore();
					}
				}
			}
			Lnr++;
		}
	}
	painter->setZoomFactor(z);
}

void ScPageOutput::DrawItem( PageItem* item, ScPainterExBase* painter, QRect rect )
{
	double sc = m_scale;
	DrawItem_Pre(item, painter, sc);
	PageItem::ItemType itemType = item->itemType();
	if( itemType == PageItem::ImageFrame )
		DrawItem_ImageFrame( (PageItem_ImageFrame*) item, painter, sc );
	else if( itemType == PageItem::Line )
		DrawItem_Line( (PageItem_Line*) item, painter );
	else if( itemType == PageItem::PathText )
		DrawItem_PathText(  (PageItem_PathText*) item, painter, sc );
	else if( itemType == PageItem::Polygon )
		DrawItem_Polygon( (PageItem_Polygon*) item, painter );
	else if( itemType == PageItem::PolyLine )
		DrawItem_PolyLine( (PageItem_PolyLine*) item, painter );
	else if( itemType == PageItem::TextFrame )
		DrawItem_TextFrame( (PageItem_TextFrame*) item, painter, rect, sc);
	DrawItem_Post(item, painter);
}

void ScPageOutput::DrawItem_Pre( PageItem* item, ScPainterExBase* painter, double scale  )
{
	double sc = scale;
	painter->save();
	if (!item->isEmbedded)
	{
		painter->setZoomFactor(sc);
		painter->translate( item->xPos() * sc, item->yPos() * sc);
//		painter->rotate(item->rotation());
	}
	painter->rotate(item->rotation());
	painter->setLineWidth(item->lineWidth());
	if (item->GrType != 0)
	{
		painter->setFillMode(ScPainterExBase::Gradient);
		painter->fill_gradient = VGradientEx(item->fill_gradient, *m_doc);
		QWMatrix grm;
		grm.rotate(item->rotation());
		FPointArray gra;
		switch (item->GrType)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			case 6:
				gra.setPoints(2, item->GrStartX, item->GrStartY, item->GrEndX, item->GrEndY);
				gra.map(grm);
				painter->setGradient(VGradientEx::linear, gra.point(0), gra.point(1));
				break;
			case 5:
			case 7:
				gra.setPoints(2, item->GrStartX, item->GrStartY, item->GrEndX, item->GrEndY);
				painter->setGradient(VGradientEx::radial, gra.point(0), gra.point(1), gra.point(0));
				break;
		}
	}
	else
	{
		painter->fill_gradient = VGradientEx(VGradientEx::linear);
		if (item->fillColor() != CommonStrings::None)
		{
			painter->setBrush( ScColorShade(m_doc->PageColors[item->fillColor()], item->fillShade()) );
			painter->setFillMode(ScPainterExBase::Solid);
		}
		else
			painter->setFillMode(ScPainterExBase::None);
	}
	if (item->lineColor() != CommonStrings::None)
	{
		if ((item->lineWidth() == 0) && !item->asLine())
			painter->setLineWidth(0);
		else
		{
			ScColorShade tmp(m_doc->PageColors[item->lineColor()], item->lineShade());
			painter->setPen( tmp , item->lineWidth(), item->PLineArt, item->PLineEnd, item->PLineJoin);
			if (item->DashValues.count() != 0)
				painter->setDash(item->DashValues, item->DashOffset);
		}
	}
	else
		painter->setLineWidth(0);
	painter->setBrushOpacity(1.0 - item->fillTransparency());
	painter->setPenOpacity(1.0 - item->lineTransparency());
	painter->setFillRule(item->fillRule);
}

void ScPageOutput::DrawItem_Post( PageItem* item, ScPainterExBase* painter )
{
	bool doStroke=true;
	if ( item->itemType() == PageItem::PathText || item->itemType() == PageItem::PolyLine || item->itemType() == PageItem::Line )
		doStroke=false;
	if ((doStroke))
	{
		if (item->lineColor() != CommonStrings::None)
		{
			ScColorShade tmp(m_doc->PageColors[item->lineColor()], item->lineShade());
			painter->setPen(tmp, item->lineWidth(), item->PLineArt, item->PLineEnd, item->PLineJoin);
			if (item->DashValues.count() != 0)
				painter->setDash(item->DashValues, item->DashOffset);
		}
		else
			painter->setLineWidth(0);
		if (!item->isTableItem)
		{
			painter->setupPolygon(&item->PoLine);
			if (item->NamedLStyle.isEmpty())
				painter->strokePath();
			else
			{
				multiLine ml = m_doc->MLineStyles[item->NamedLStyle];
				for (int it = ml.size()-1; it > -1; it--)
				{
					ScColorShade tmp( m_doc->PageColors[ml[it].Color], ml[it].Shade );
					painter->setPen(tmp, ml[it].Width,
							static_cast<Qt::PenStyle>(ml[it].Dash),
							static_cast<Qt::PenCapStyle>(ml[it].LineEnd),
							static_cast<Qt::PenJoinStyle>(ml[it].LineJoin));
					painter->strokePath();
				}
			}
		}
	}
	if ((!item->isEmbedded))
	{
		double scpInv = 1.0 / (QMAX(m_scale, 1));
	}
	item->Tinput = false;
	item->FrameOnly = false;
	painter->restore();
}

void ScPageOutput::DrawGlyphs(PageItem* item, ScPainterExBase *painter, const CharStyle& style, GlyphLayout& glyphs)
{
	uint glyph = glyphs.glyph;
	if (glyph == (ScFace::CONTROL_GLYPHS + 29)) // NBSPACE
		glyph = style.font().char2CMap(QChar(' '));
	else if (glyph == (ScFace::CONTROL_GLYPHS + 24)) // NBHYPHEN
		glyph = style.font().char2CMap(QChar('-'));
	
	if (glyph >= ScFace::CONTROL_GLYPHS)
		return;
	
	//if (style.font().canRender(QChar(glyph)))
	{
		QWMatrix chma, chma2, chma3, chma4, chma5, chma6;
		chma.scale(glyphs.scaleH * style.fontSize() / 100.00, glyphs.scaleV * style.fontSize() / 100.0);
//		qDebug(QString("glyphscale: %1 %2").arg(glyphs.scaleH).arg(glyphs.scaleV));
		chma5.scale(painter->zoomFactor(), painter->zoomFactor());
		FPointArray gly = style.font().glyphOutline(glyph);
		// Do underlining first so you can get typographically correct
		// underlines when drawing a white outline
		if ((style.effects() & ScStyle_Underline) || ((style.effects() & ScStyle_UnderlineWords) && (glyph != style.font().char2CMap(QChar(' ')))))
		{
			double st, lw;
			if ((style.underlineOffset() != -1) || (style.underlineWidth() != -1))
			{
				if (style.underlineOffset() != -1)
					st = (style.underlineOffset() / 1000.0) * (style.font().descent(style.fontSize() / 10.0));
				else
					st = style.font().underlinePos(style.fontSize() / 10.0);
				if (style.underlineWidth() != -1)
					lw = (style.underlineWidth() / 1000.0) * (style.fontSize() / 10.0);
				else
					lw = QMAX(style.font().strokeWidth(style.fontSize() / 10.0), 1);
			}
			else
			{
				st = style.font().underlinePos(style.fontSize() / 10.0);
				lw = QMAX(style.font().strokeWidth(style.fontSize() / 10.0), 1);
			}
			if (style.baselineOffset() != 0)
				st += (style.fontSize() / 10.0) * glyphs.scaleV * (style.baselineOffset() / 1000.0);
			ScColorShade tmpPen = painter->pen();
			painter->setPen(painter->brush());
			painter->setLineWidth(lw);
			painter->drawLine(FPoint(glyphs.xoffset, glyphs.yoffset - st), FPoint(glyphs.xoffset + glyphs.xadvance, glyphs.yoffset - st));
			painter->setPen(tmpPen);
		}
		if (gly.size() > 3)
		{
			if (item->reversed())
			{
				chma3.scale(-1, 1);
				chma3.translate(-glyphs.xadvance, 0);
			}
			chma4.translate(glyphs.xoffset, glyphs.yoffset - ((style.fontSize() / 10.0) * glyphs.scaleV));
			if (style.baselineOffset() != 0)
				chma6.translate(0, -(style.fontSize() / 10.0) * (style.baselineOffset() / 1000.0) * painter->zoomFactor());
			gly.map(chma * chma3 * chma4 * chma5 * chma6);
			painter->setFillMode(1);
			bool fr = painter->fillRule();
			painter->setFillRule(false);
			painter->setupTextPolygon(&gly);
			if ((style.font().isStroked()) && ((style.fontSize() * glyphs.scaleV * style.outlineWidth() / 10000.0) != 0))
			{
				ScColorShade tmp = painter->brush();
				painter->setPen(tmp, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
				painter->setLineWidth(style.fontSize() * glyphs.scaleV * style.outlineWidth() / 10000.0);
				painter->strokePath();
			}
			else
			{
				if ((style.effects() & ScStyle_Shadowed) && (style.strokeColor() != CommonStrings::None))
				{
					painter->save();
					painter->translate((style.fontSize() * glyphs.scaleH * style.shadowXOffset() / 10000.0) * painter->zoomFactor(), -(style.fontSize() * glyphs.scaleV * style.shadowYOffset() / 10000.0) * painter->zoomFactor());
					ScColorShade tmp = painter->brush();
					painter->setBrush(painter->pen());
					painter->setupTextPolygon(&gly);
					painter->fillPath();
					painter->setBrush(tmp);
					painter->restore();
					painter->setupTextPolygon(&gly);
				}
				if (style.fillColor() != CommonStrings::None)
					painter->fillPath();
				if ((style.effects() & ScStyle_Outline) && (style.strokeColor() != CommonStrings::None) && ((style.fontSize() * glyphs.scaleV * style.outlineWidth() / 10000.0) != 0))
				{
					painter->setLineWidth(style.fontSize() * glyphs.scaleV * style.outlineWidth() / 10000.0);
					painter->strokePath();
				}
			}
			painter->setFillRule(fr);
		}
		if (style.effects() & ScStyle_Strikethrough)
		{
			double st, lw;
			if ((style.strikethruOffset() != -1) || (style.strikethruWidth() != -1))
			{
				if (style.strikethruOffset() != -1)
					st = (style.strikethruOffset() / 1000.0) * (style.font().ascent(style.fontSize() / 10.0));
				else
					st = style.font().strikeoutPos(style.fontSize() / 10.0);
				if (style.strikethruWidth() != -1)
					lw = (style.strikethruWidth() / 1000.0) * (style.fontSize() / 10.0);
				else
					lw = QMAX(style.font().strokeWidth(style.fontSize() / 10.0), 1);
			}
			else
			{
				st = style.font().strikeoutPos(style.fontSize() / 10.0);
				lw = QMAX(style.font().strokeWidth(style.fontSize() / 10.0), 1);
			}
			if (style.baselineOffset() != 0)
				st += (style.fontSize() / 10.0) * glyphs.scaleV * (style.baselineOffset() / 1000.0);
			painter->setPen(painter->brush());
			painter->setLineWidth(lw);
			painter->drawLine(FPoint(glyphs.xoffset, glyphs.yoffset - st), FPoint(glyphs.xoffset + glyphs.xadvance, glyphs.yoffset - st));
		}
	}
	/*else
	{
		painter->setLineWidth(1);
		painter->setPen(ScColorShade(Qt::red, 100));
		painter->setBrush(ScColorShade(Qt::red, 100));
		painter->setFillMode(1);
		painter->drawRect(glyphs.xoffset, glyphs.yoffset - (style.fontSize() / 10.0) * glyphs.scaleV , (style.fontSize() / 10.0) * glyphs.scaleH, (style.fontSize() / 10.0) * glyphs.scaleV);
	}*/
	if (glyphs.more)
	{
		painter->translate(glyphs.xadvance * painter->zoomFactor(), 0);
		DrawGlyphs(item, painter, style, *glyphs.more);
	}
}

void ScPageOutput::DrawItem_Embedded( PageItem* item, ScPainterExBase *p, QRect e, const CharStyle& style, PageItem* cembedded)
{
	QPtrList<PageItem> emG;
	emG.clear();
	if (cembedded != 0)
	{
		if (!item->doc()->DoDrawing)
		{
			cembedded->Tinput = false;
			cembedded->FrameOnly = false;
			return;
		}
		emG.append(cembedded);
		if (cembedded->Groups.count() != 0)
		{
			for (uint ga=0; ga < m_doc->FrameItems.count(); ++ga)
			{
				if (m_doc->FrameItems.at(ga)->Groups.count() != 0)
				{
					if (m_doc->FrameItems.at(ga)->Groups.top() == cembedded->Groups.top())
					{
						if (m_doc->FrameItems.at(ga)->ItemNr != cembedded->ItemNr)
						{
							if (emG.find(m_doc->FrameItems.at(ga)) == -1)
								emG.append(m_doc->FrameItems.at(ga));
						}
					}
				}
			}
		}
		for (uint em = 0; em < emG.count(); ++em)
		{
			PageItem* embedded = emG.at(em);
/*
 ParagraphStyle vg;
			QValueList<ParagraphStyle> savedParagraphStyles;
			for (int xxx=0; xxx<5; ++xxx)
			{
				vg.setLineSpacingMode(static_cast<ParagraphStyle::LineSpacingMode>(m_Doc->docParagraphStyles[xxx].lineSpacingMode()));
				vg.setUseBaselineGrid(m_Doc->docParagraphStyles[xxx].useBaselineGrid());
				vg.setLineSpacing(m_Doc->docParagraphStyles[xxx].lineSpacing());
				vg.charStyle().setFontSize(m_Doc->docParagraphStyles[xxx].charStyle().fontSize());
				vg.setLeftMargin(m_Doc->docParagraphStyles[xxx].leftMargin());
				vg.setFirstIndent(m_Doc->docParagraphStyles[xxx].firstIndent());
				vg.setGapBefore(m_Doc->docParagraphStyles[xxx].gapBefore());
				vg.setGapAfter(m_Doc->docParagraphStyles[xxx].gapAfter());
				savedParagraphStyles.append(vg);
			}
 */
			p->save();
			double pws=0;
/*	FIXME
				embedded->Xpos = Xpos + hl->xco + embedded->gXpos;
			embedded->Ypos = Ypos + (hl->yco - (embedded->gHeight * (hl->scalev / 1000.0))) + embedded->gYpos;
			p->translate((hl->xco + embedded->gXpos * (hl->scale / 1000.0)) * p->zoomFactor(), (hl->yco - (embedded->gHeight * (hl->scalev / 1000.0)) + embedded->gYpos * (hl->scalev / 1000.0)) * p->zoomFactor());
			if (hl->base != 0)
			{
				p->translate(0, -embedded->gHeight * (hl->base / 1000.0) * p->zoomFactor());
				embedded->Ypos -= embedded->gHeight * (hl->base / 1000.0);
			}
			p->scale(hl->scale / 1000.0, hl->scalev / 1000.0);
			embedded->Dirty = Dirty;
			embedded->invalid = invalid;
			double sc;
			double pws = embedded->m_lineWidth;
			embedded->DrawObj_Pre(p, sc);
			switch(embedded->itemType())
			{
				case ImageFrame:
				case TextFrame:
				case Polygon:
				case PathText:
					embedded->DrawObj_Item(p, e, sc);
					break;
				case Line:
				case PolyLine:
					embedded->m_lineWidth = pws * QMIN(hl->scale / 1000.0, hl->scalev / 1000.0);
					embedded->DrawObj_Item(p, e, sc);
					break;
				default:
					break;
			}
			embedded->m_lineWidth = pws * QMIN(hl->scale / 1000.0, hl->scalev / 1000.0);
			embedded->DrawObj_Post(p);
*/
			p->restore();
			embedded->setLineWidth(pws);
/*
 for (int xxx=0; xxx<5; ++xxx)
			{
				m_Doc->docParagraphStyles[xxx].setLineSpacingMode(static_cast<ParagraphStyle::LineSpacingMode>(savedParagraphStyles[xxx].lineSpacingMode()));
				m_Doc->docParagraphStyles[xxx].setUseBaselineGrid(savedParagraphStyles[xxx].useBaselineGrid());
				m_Doc->docParagraphStyles[xxx].setLineSpacing(savedParagraphStyles[xxx].lineSpacing());
				m_Doc->docParagraphStyles[xxx].charStyle().setFontSize(savedParagraphStyles[xxx].charStyle().fontSize());
				m_Doc->docParagraphStyles[xxx].setLeftMargin(savedParagraphStyles[xxx].leftMargin());
				m_Doc->docParagraphStyles[xxx].setFirstIndent(savedParagraphStyles[xxx].firstIndent());
				m_Doc->docParagraphStyles[xxx].setGapBefore(savedParagraphStyles[xxx].gapBefore());
				m_Doc->docParagraphStyles[xxx].setGapAfter(savedParagraphStyles[xxx].gapAfter());
			}
			savedParagraphStyles.clear();
*/
		}
	}
}

void ScPageOutput::DrawItem_ImageFrame( PageItem_ImageFrame* item, ScPainterExBase* painter, double scale  )
{
	ScPainterExBase::ImageMode mode = ScPainterExBase::rgbImages;
	if ((item->fillColor() != CommonStrings::None) || (item->GrType != 0))
	{
		painter->setupPolygon(&item->PoLine);
		painter->fillPath();
	}
	if (item->Pfile.isEmpty())
	{
		if ((item->Frame) && (m_doc->guidesSettings.framesShown))
		{
			painter->setPen( ScColorShade(Qt::black, 100), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
			painter->drawLine(FPoint(0, 0), FPoint(item->width(), item->height()));
			painter->drawLine(FPoint(0, item->height()), FPoint(item->width(), 0));
		}
	}
	else
	{
		if ((!item->imageShown()) || (!item->PicAvail))
		{
			if ((item->Frame) && (m_doc->guidesSettings.framesShown))
			{
				painter->setPen( ScColorShade(Qt::red, 100), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
				painter->drawLine(FPoint(0, 0), FPoint(item->width(), item->height()));
				painter->drawLine(FPoint(0, item->height()), FPoint(item->width(), 0));
			}
		}
		else
		{
			ScImage scImg;
			ScImage* pImage = NULL;
			double imScaleX = item->imageXScale();
			double imScaleY = item->imageYScale();
			if( m_reloadImages )
			{
				bool dummy;
				bool useCmyk = false;
				ScPainterExBase::ImageMode imageMode = painter->imageMode();
				if ( imageMode == ScPainterExBase::cmykImages )
					useCmyk = true;
				QFileInfo fInfo(item->Pfile);
				QString ext = fInfo.extension(false);
				CMSettings cmsSettings(item->doc(), item->IProfile, item->IRender);
				scImg.imgInfo.valid = false;
				scImg.imgInfo.clipPath = "";
				scImg.imgInfo.PDSpathData.clear();
				scImg.imgInfo.layerInfo.clear();
				scImg.imgInfo.RequestProps = item->pixm.imgInfo.RequestProps;
				scImg.imgInfo.isRequest = item->pixm.imgInfo.isRequest;
				scImg.LoadPicture(item->Pfile, cmsSettings, item->UseEmbedded, m_useProfiles, translateImageModeToRequest(imageMode), m_imageRes, &dummy);
				if( ext == "eps" || ext == "pdf" || ext == "ps" )
				{
					imScaleX *= (72.0 / (double) m_imageRes);
					imScaleY *= (72.0 / (double) m_imageRes);
				}
				scImg.applyEffect(item->effectsInUse, m_doc->PageColors, useCmyk);
				mode = imageMode;
				pImage = &scImg;
			}
			else
				pImage = &item->pixm;

			painter->save();
			if (item->imageClip.size() != 0)
			{
				painter->setupPolygon(&item->imageClip);
				painter->setClipPath();
			}
			painter->setupPolygon(&item->PoLine);
			painter->setClipPath();
			if (item->imageFlippedH())
			{
				painter->translate(item->width() * scale, 0);
				painter->scale(-1, 1);
			}
			if (item->imageFlippedV())
			{
				painter->translate(0, item->height() * scale);
				painter->scale(1, -1);
			}
			painter->translate(item->imageXOffset() * item->imageXScale() * scale, item->imageYOffset() * item->imageYScale() * scale);
			//painter->translate(item->LocalX * imScaleX * scale, item->LocalY * imScaleY * scale); ??
			painter->scale( imScaleX, imScaleY );
			if (pImage->imgInfo.lowResType != 0)
				painter->scale(pImage->imgInfo.lowResScale, pImage->imgInfo.lowResScale);
			painter->drawImage(pImage, mode);
			painter->restore();
		}
	}
}

void ScPageOutput::DrawItem_Line( PageItem_Line* item, ScPainterExBase* painter )
{
 int startArrowIndex;
 int endArrowIndex;

	startArrowIndex = item->startArrowIndex();
	endArrowIndex = item->endArrowIndex();

	if (item->NamedLStyle.isEmpty())
		painter->drawLine(FPoint(0, 0), FPoint(item->width(), 0));
	else
	{
		multiLine ml = m_doc->MLineStyles[item->NamedLStyle];
		for (int it = ml.size()-1; it > -1; it--)
		{
			ScColorShade colorShade(m_doc->PageColors[ml[it].Color], ml[it].Shade);
			painter->setPen(colorShade, ml[it].Width,
						static_cast<Qt::PenStyle>(ml[it].Dash),
						static_cast<Qt::PenCapStyle>(ml[it].LineEnd),
						static_cast<Qt::PenJoinStyle>(ml[it].LineJoin));
			painter->drawLine(FPoint(0, 0), FPoint(item->width(), 0));
		}
	}
	if (startArrowIndex != 0)
	{
		QWMatrix arrowTrans;
		FPointArray arrow = ( *m_doc->arrowStyles.at(startArrowIndex - 1) ).points.copy();
		arrowTrans.translate( 0, 0 );
		arrowTrans.scale( item->lineWidth(), item->lineWidth());
		arrowTrans.scale( -1 , 1 );
		arrow.map( arrowTrans );
		painter->setBrush( painter->pen() );
		painter->setBrushOpacity( 1.0 - item->lineTransparency() );
		painter->setLineWidth( 0 );
		painter->setFillMode(ScPainterExBase::Solid);
		painter->setupPolygon( &arrow );
		painter->fillPath();
	}
	if (endArrowIndex != 0)
	{
		QWMatrix arrowTrans;
		FPointArray arrow = (*m_doc->arrowStyles.at(endArrowIndex-1) ).points.copy();
		arrowTrans.translate( item->width(), 0 );
		arrowTrans.scale( item->lineWidth(), item->lineWidth());
		arrow.map( arrowTrans );
		painter->setBrush( painter->pen() );
		painter->setBrushOpacity( 1.0 - item->lineTransparency() );
		painter->setLineWidth( 0 );
		painter->setFillMode( ScPainterExBase::Solid );
		painter->setupPolygon( &arrow );
		painter->fillPath();
	}
}

void ScPageOutput::DrawItem_PathText( PageItem_PathText* item, ScPainterExBase* painter, double scale )
{
	int a;
	int chs;
	double wide;
	QString chstr, chstr2, chstr3;
	ScText *hl;
	double dx;
	double sp = 0;
	double oldSp = 0;
	double oCurX = 0;
	FPoint point = FPoint(0, 0);
	FPoint normal = FPoint(0, 0);
	FPoint tangent = FPoint(0, 0);
	FPoint extPoint = FPoint(0, 0);
	bool ext = false;
	bool first = true;
	double fsx = 0;
	uint seg = 0;
	double segLen = 0;
	double distCurX;
	double CurX = item->textToFrameDistLeft(); // item->CurX = item->textToFrameDistLeft()
	double CurY = 0;
	if (item->lineColor() != CommonStrings::None && item->PoShow)
	{
		painter->setupPolygon(&item->PoLine, false);
		painter->strokePath();
	}
	if (item->itemText.length() != 0)
		CurX += item->itemText.item(0)->fontSize() * item->itemText.item(0)->tracking() / 10000.0;
	segLen = item->PoLine.lenPathSeg(seg);
	for (a = 0; a < item->itemText.length(); ++a)
	{
		CurY = 0;
		hl = item->itemText.item(a);
		chstr = hl->ch;
		if ((chstr == QChar(30)) || (chstr == QChar(13)) || (chstr == QChar(9)) || (chstr == QChar(28)))
			continue;
		chs = hl->fontSize();
		//item->SetZeichAttr(*hl, &chs, &chstr); //FIXME: layoutglyphs
		if (chstr == QChar(29))
			chstr2 = " ";
		else if (chstr == QChar(24))
			chstr2 = "-";
		else
			chstr2 = chstr;
		if (a < item->itemText.length() - 1)
		{
			if (item->itemText.item(a+1)->ch == QChar(29))
				chstr3 = " ";
			else if (item->itemText.item(a+1)->ch == QChar(24))
				chstr3 = "-";
			else
				chstr3 = item->itemText.text(a+1, 1);
			wide = hl->font().charWidth(chstr2[0], chs, chstr3[0]);
		}
		else
			wide = hl->font().charWidth(chstr2[0], chs);
		wide = wide * (hl->scaleH() / 1000.0);
		dx = wide / 2.0;
		CurX += dx;
		ext = false;
		while ( (seg < item->PoLine.size()-3) && (CurX > fsx + segLen))
		{
			fsx += segLen;
			seg += 4;
			if (seg > item->PoLine.size()-3)
				break;
			segLen = item->PoLine.lenPathSeg(seg);
			ext = true;
		}
		if (seg > item->PoLine.size()-3)
			break;
		if (CurX > fsx + segLen)
			break;
		if (ext)
		{
			sp = 0;
			distCurX = item->PoLine.lenPathDist(seg, 0, sp);
			while (distCurX <= ((CurX - oCurX) - (fsx - oCurX)))
			{
				sp += 0.001;
				distCurX = item->PoLine.lenPathDist(seg, 0, sp);
			}
			item->PoLine.pointTangentNormalAt(seg, sp, &point, &tangent, &normal );
			CurX = (CurX - (CurX - fsx)) + distCurX;
			oldSp = sp;
			ext = false;
		}
		else
		{
			if( seg < item->PoLine.size()-3 )
			{
				if (CurX > fsx + segLen)
					break;
				distCurX = item->PoLine.lenPathDist(seg, oldSp, sp);
				while (distCurX <= (CurX - oCurX))
				{
					sp += 0.001;
					if (sp >= 1.0)
					{
						sp = 0.9999;
						break;
					}
					distCurX = item->PoLine.lenPathDist(seg, oldSp, sp);
				}
				item->PoLine.pointTangentNormalAt(seg, sp, &point, &tangent, &normal );
				CurX = oCurX + distCurX;
				oldSp = sp;
			}
			else
				break;
		}
		hl->glyph.xoffset = point.x();
		hl->glyph.yoffset = point.y();
		hl->PtransX = tangent.x();
		hl->PtransY = tangent.y();
		hl->PRot = dx;
		QWMatrix trafo = QWMatrix( 1, 0, 0, -1, -dx * scale, 0 );
		trafo *= QWMatrix( tangent.x(), tangent.y(), tangent.y(), -tangent.x(), point.x() * scale, point.y() * scale);
		QWMatrix sca = painter->worldMatrix();
		trafo *= sca;
		painter->save();
		QWMatrix savWM = painter->worldMatrix();
		painter->setWorldMatrix(trafo);
		//DrawCharacters(item, painter, Zli);
		painter->setWorldMatrix(savWM);
		painter->restore();
		painter->setZoomFactor(scale);
		//item->MaxChars = a+1;
		oCurX = CurX;
		CurX -= dx;
		CurX += wide+hl->fontSize() * hl->tracking() / 10000.0;
		first = false;
	}
}

void ScPageOutput::DrawItem_Polygon ( PageItem_Polygon* item , ScPainterExBase* painter )
{
	painter->setupPolygon(&item->PoLine);
	painter->fillPath();
}

void ScPageOutput::DrawItem_PolyLine( PageItem_PolyLine* item, ScPainterExBase* painter )
{
 int startArrowIndex;
 int endArrowIndex;

	startArrowIndex = item->startArrowIndex();
	endArrowIndex = item->endArrowIndex();

	if (item->PoLine.size()>=4)
	{
		if ((item->fillColor() != CommonStrings::None) || (item->GrType != 0))
		{
			FPointArray cli;
			FPoint Start;
			bool firstp = true;
			for (uint n = 0; n < item->PoLine.size()-3; n += 4)
			{
				if (firstp)
				{
					Start = item->PoLine.point(n);
					firstp = false;
				}
				if (item->PoLine.point(n).x() > 900000)
				{
					cli.addPoint(item->PoLine.point(n-2));
					cli.addPoint(item->PoLine.point(n-2));
					cli.addPoint(Start);
					cli.addPoint(Start);
					cli.setMarker();
					firstp = true;
					continue;
				}
				cli.addPoint(item->PoLine.point(n));
				cli.addPoint(item->PoLine.point(n+1));
				cli.addPoint(item->PoLine.point(n+2));
				cli.addPoint(item->PoLine.point(n+3));
			}
			if (cli.size() > 2)
			{
				FPoint l1 = cli.point(cli.size()-2);
				cli.addPoint(l1);
				cli.addPoint(l1);
				cli.addPoint(Start);
				cli.addPoint(Start);
			}
			painter->setupPolygon(&cli);
			painter->fillPath();
		}
		painter->setupPolygon(&item->PoLine, false);
		if (item->NamedLStyle.isEmpty())
			painter->strokePath();
		else
		{
			multiLine ml = m_doc->MLineStyles[item->NamedLStyle];
			for (int it = ml.size()-1; it > -1; it--)
			{
				ScColorShade tmp(m_doc->PageColors[ml[it].Color], ml[it].Shade);
				painter->setPen(tmp, ml[it].Width,
							static_cast<Qt::PenStyle>(ml[it].Dash),
							static_cast<Qt::PenCapStyle>(ml[it].LineEnd),
							static_cast<Qt::PenJoinStyle>(ml[it].LineJoin));
				painter->strokePath();
			}
		}
		if (startArrowIndex != 0)
		{
			FPoint Start = item->PoLine.point(0);
			for (uint xx = 1; xx < item->PoLine.size(); xx += 2)
			{
				FPoint Vector = item->PoLine.point(xx);
				if ((Start.x() != Vector.x()) || (Start.y() != Vector.y()))
				{
					double r = atan2(Start.y()-Vector.y(),Start.x()-Vector.x())*(180.0/M_PI);
					QWMatrix arrowTrans;
					FPointArray arrow = (*m_doc->arrowStyles.at(startArrowIndex-1)).points.copy();
					arrowTrans.translate(Start.x(), Start.y());
					arrowTrans.rotate(r);
					arrowTrans.scale(item->lineWidth(), item->lineWidth());
					arrow.map(arrowTrans);
					painter->setBrush(painter->pen());
					painter->setBrushOpacity(1.0 - item->lineTransparency());
					painter->setLineWidth(0);
					painter->setFillMode(ScPainterExBase::Solid);
					painter->setupPolygon(&arrow);
					painter->fillPath();
					break;
				}
			}
		}
		if (endArrowIndex != 0)
		{
			FPoint End = item->PoLine.point(item->PoLine.size()-2);
			for (uint xx = item->PoLine.size()-1; xx > 0; xx -= 2)
			{
				FPoint Vector = item->PoLine.point(xx);
				if ((End.x() != Vector.x()) || (End.y() != Vector.y()))
				{
					double r = atan2(End.y()-Vector.y(),End.x()-Vector.x())*(180.0/M_PI);
					QWMatrix arrowTrans;
					FPointArray arrow = (*m_doc->arrowStyles.at(endArrowIndex-1)).points.copy();
					arrowTrans.translate(End.x(), End.y());
					arrowTrans.rotate(r);
					arrowTrans.scale( item->lineWidth(), item->lineWidth() );
					arrow.map(arrowTrans);
					painter->setBrush(painter->pen());
					painter->setBrushOpacity(1.0 - item->lineTransparency());
					painter->setLineWidth(0);
					painter->setFillMode(ScPainterExBase::Solid);
					painter->setupPolygon(&arrow);
					painter->fillPath();
					break;
				}
			}
		}
	}
}

void ScPageOutput::DrawItem_TextFrame( PageItem_TextFrame* item, ScPainterExBase* painter, QRect e, double scale )
{
	QWMatrix wm;
	QPoint pt1, pt2;
	FPoint ColBound;
	QRegion cm;
	int a;
	double lineCorr;
	QString chstr, chstr2, chstr3;
	ScText *hl;

	QValueList<ParagraphStyle::TabRecord> tTabValues;
	double desc, asce, tabDist;
	tTabValues.clear();
	
	QRect e2;
	painter->save();
	if (item->isEmbedded)
		e2 = e;
	else
	{
		e2 = QRect(qRound(e.x()  / scale + m_doc->minCanvasCoordinate.x()), qRound(e.y()  / scale + m_doc->minCanvasCoordinate.y()), qRound(e.width() / scale), qRound(e.height() / scale));
		wm.translate(item->xPos(), item->yPos());
	}
	wm.rotate(item->rotation());
	if ((item->fillColor() != CommonStrings::None) || (item->GrType != 0))
	{
		painter->setupPolygon(&item->PoLine);
		painter->fillPath();
	}
	if (item->lineColor() != CommonStrings::None)
		lineCorr = item->lineWidth() / 2.0;
	else
		lineCorr = 0;
	if ((item->isAnnotation()) && (item->annotation().Type() == 2) && (!item->Pfile.isEmpty()) && (item->PicAvail) && (item->imageShown()) && (item->annotation().UseIcons()))
	{
		painter->setupPolygon(&item->PoLine);
		painter->setClipPath();
		painter->save();
		painter->scale(item->imageXScale(), item->imageYScale());
		painter->translate(static_cast<int>(item->imageXOffset() * item->imageXScale()), static_cast<int>(item->imageYOffset()  * item->imageYScale()));
		if (!item->pixm.qImage().isNull())
			painter->drawImage(&item->pixm, ScPainterExBase::rgbImages);
		painter->restore();
	}
	if ((item->itemText.length() != 0))
	{
		if (item->imageFlippedH())
		{
			painter->translate(item->width() * scale, 0);
			painter->scale(-1, 1);
		}
		if (item->imageFlippedV())
		{
			painter->translate(0, item->height() * scale);
			painter->scale(1, -1);
		}
		uint tabCc = 0;
		for (uint ll=0; ll < item->itemText.lines(); ++ll)
		{
			LineSpec ls = item->itemText.line(ll);
			tabDist = ls.x;
			double CurX = ls.x;
			for (a = ls.firstItem; a <= ls.lastItem; ++a)
			{
				hl = item->itemText.item(a);
				const CharStyle& charStyle = item->itemText.charStyle(a);
				const ParagraphStyle& style = item->itemText.paragraphStyle(a);
				tTabValues = style.tabValues();
				double chs = charStyle.fontSize() * hl->glyph.scaleV;
				bool selected = item->itemText.selected(a);
				if (charStyle.effects() & ScStyle_StartOfLine)
					tabCc = 0;
				chstr = hl->ch;
				if (hl->glyph.glyph == 0)
					continue;
				if (charStyle.fillColor() != CommonStrings::None)
				{
					ScColorShade tmp(m_doc->PageColors[charStyle.fillColor()], hl->fillShade());
					painter->setBrush(tmp);
				}
				if (charStyle.strokeColor() != CommonStrings::None)
				{
					ScColorShade tmp(m_doc->PageColors[charStyle.strokeColor()], hl->strokeShade());
					painter->setPen(tmp, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
				}
				if (charStyle.effects() & ScStyle_DropCap)
				{
					if (style.useBaselineGrid())
						chs = qRound(10 * ((m_doc->typographicSettings.valueBaseGrid * (style.dropCapLines()-1) + (charStyle.font().ascent(style.charStyle().fontSize() / 10.0))) / charStyle.font().realCharHeight(chstr[0], 10)));
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
				if ((chstr == SpecialChars::TAB) && (tTabValues.count() != 0) && (tabCc < tTabValues.count()) && (!tTabValues[tabCc].tabFillChar.isNull()))
				{
					QChar tabFillChar(tTabValues[tabCc].tabFillChar);
					double wt = charStyle.font().charWidth(tabFillChar, chs / 10.0);
					int coun = static_cast<int>((CurX - tabDist) / wt);
					double sPos = tabDist - CurX + hl->glyph.xoffset + 1;
					desc = -charStyle.font().descent(chs / 10.0);
					asce = charStyle.font().ascent(chs / 10.0);
					GlyphLayout tglyph;
					tglyph.glyph = tabFillChar.unicode();
					tglyph.yoffset = hl->glyph.yoffset;
					tglyph.scaleV = tglyph.scaleH = chs / charStyle.fontSize();
					tglyph.xadvance = wt;
					painter->save();
					for (int cx = 0; cx < coun; ++cx)
					{
						tglyph.xoffset =  sPos + wt * cx;
						if (e2.intersects(wm.mapRect(QRect(qRound(CurX + tglyph.xoffset),qRound(ls.y + tglyph.yoffset-asce), qRound(tglyph.xadvance+1), qRound(asce+desc)))))
							DrawGlyphs(item, painter, charStyle, tglyph);
					}
					painter->restore();
				}
				if (chstr[0] == SpecialChars::TAB)
					tabCc++;
				//if (!m_doc->RePos)
				{
					double xcoZli = CurX + hl->glyph.xoffset;
					desc = - charStyle.font().descent(charStyle.fontSize() / 10.0);
					asce = charStyle.font().ascent(charStyle.fontSize() / 10.0);
					if (charStyle.strokeColor() != CommonStrings::None)
					{
						ScColorShade tmp(m_doc->PageColors[charStyle.strokeColor()], charStyle.strokeShade());
						painter->setPen(tmp, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
					}
					if (e2.intersects(wm.mapRect(QRect(qRound(CurX + hl->glyph.xoffset),qRound(ls.y + hl->glyph.yoffset-asce), qRound(hl->glyph.xadvance+1), qRound(asce+desc)))))
					{
						painter->save();
						painter->translate(CurX * painter->zoomFactor(), ls.y * painter->zoomFactor());
						if (hl->ch[0] == SpecialChars::OBJECT)
						{
							DrawItem_Embedded(item, painter, e, charStyle, hl->cembedded);
							CurX += (hl->cembedded->gWidth + hl->cembedded->lineWidth()) *  painter->zoomFactor();
						}
						else
						{
							DrawGlyphs(item, painter, charStyle, hl->glyph);
							CurX += hl->glyph.wide();
						}
						painter->restore();
					}
				}
				tabDist = CurX;
			}
		}
	}
	painter->restore();
}


