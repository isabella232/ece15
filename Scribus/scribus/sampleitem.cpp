/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "scribus.h"
#include "sampleitem.h"
#include "sampleitem.moc"
#include "loremipsum.h"
#include "scribusdoc.h"
#include "undomanager.h"
#include "commonstrings.h"
#include "prefsmanager.h"
#include <qcolor.h>
#include <qstring.h>
#include "text/nlsconfig.h"

extern ScribusMainWindow* ScMW;


SampleItem::SampleItem() : QObject()
{
	used = true;
	if (ScMW->doc == NULL)
	{
		ScMW->doFileNew(//pageWidth, pageHeight,
									0,0,
									//topMargin, leftMargin, rightMargin, bottomMargin,
									1, 1, 1, 1,
									// autoframes. It's disabled in python
									// columnDistance, numberCols, autoframes,
									0, 1, false,
									//pagesType, unit, firstPageOrder,
									1, 1, 1,
									//orientation, firstPageNr, "Custom");
									1, 1, "custom", 1, true);
		ScMW->doc->pageSets[1/*pagesType*/].FirstPage = 1;//firstPageOrder;
		used = false;
	}
	doc = ScMW->doc;
	// tmp colors. to be removed in descrictor
	ScMW->doc->PageColors.insert("__blackforpreview__", ScColor(0, 0, 0, 255));
	ScMW->doc->PageColors.insert("__whiteforpreview__", ScColor(0, 0, 0, 0));
	ScMW->doc->PageColors.insert("__whiteforpreviewbg__", ScColor(0, 0, 0, 0));
	bgShade = 100;
	tmpStyle.setName("(preview temporary)");
	tmpStyle.setLineSpacingMode(ParagraphStyle::FixedLineSpacing);
	tmpStyle.setLineSpacing((doc->toolSettings.defSize / 10.0)
		* static_cast<double>(doc->typographicSettings.autoLineSpacing) / 100
		+ (doc->toolSettings.defSize / 10.0));
	tmpStyle.setAlignment(0);
	tmpStyle.setLeftMargin(0);
	tmpStyle.setFirstIndent(0);
	tmpStyle.setRightMargin(0);
	tmpStyle.setGapBefore(0);
	tmpStyle.setGapAfter(0);
	tmpStyle.charStyle().setFont(PrefsManager::instance()->appPrefs.AvailFonts[doc->toolSettings.defFont]);
	tmpStyle.charStyle().setFontSize(doc->toolSettings.defSize);
	tmpStyle.tabValues().clear();
	tmpStyle.setHasDropCap(false);
	tmpStyle.setDropCapLines(0);//2;
	tmpStyle.setDropCapOffset(0);
	tmpStyle.charStyle().setEffects(ScStyle_Default);
	tmpStyle.charStyle().setFillColor("__blackforpreview__");
	tmpStyle.charStyle().setFillShade(100); //doc->toolSettings.dShade;
	tmpStyle.charStyle().setStrokeColor("__whiteforpreview__");
	tmpStyle.charStyle().setStrokeShade(100); //doc->toolSettings.dShade2;
	tmpStyle.setUseBaselineGrid(false);
	tmpStyle.charStyle().setShadowXOffset(50);
	tmpStyle.charStyle().setShadowYOffset(-50);
	tmpStyle.charStyle().setOutlineWidth(10);
	tmpStyle.charStyle().setUnderlineOffset(0); //doc->typographicSettings.valueUnderlinePos;
	tmpStyle.charStyle().setUnderlineWidth(0); //doc->typographicSettings.valueUnderlineWidth;
	tmpStyle.charStyle().setStrikethruOffset(0); //doc->typographicSettings.valueStrikeThruPos;
	tmpStyle.charStyle().setStrikethruWidth(0); //doc->typographicSettings.valueStrikeThruPos;
	tmpStyle.charStyle().setScaleH(1000);
	tmpStyle.charStyle().setScaleV(1000);
	tmpStyle.charStyle().setBaselineOffset(0);
	tmpStyle.charStyle().setTracking(0);
}

SampleItem::~SampleItem()
{
	cleanupTemporary();
	// clean tmp document
	if (used == false)
	{
		doc->setModified(false);
		ScMW->slotFileClose();
	}
}

void SampleItem::setText(QString aText)
{
	text = aText;
}

void SampleItem::setLoremIpsum(int para)
{
	LoremParser *m = new LoremParser("loremipsum.xml");
	text = m->createLorem(para);
	text = QString::fromUtf8(text);
	delete m;
}

void SampleItem::setStyle(const ParagraphStyle& aStyle)
{
	tmpStyle = aStyle;
}

void SampleItem::setBgColor(QColor c)
{
	ScMW->doc->PageColors["__whiteforpreviewbg__"].fromQColor(c);
}

void SampleItem::setBgShade(int c)
{
	bgShade = c;
}

void SampleItem::setTxColor(QColor c)
{
	ScMW->doc->PageColors["__blackforpreview__"].fromQColor(c);
}

void SampleItem::setTxShade(int c)
{
	tmpStyle.charStyle().setFillShade(c);
}

void SampleItem::setLineSpaMode(int lineSpaMode)
{
	tmpStyle.setLineSpacingMode(static_cast<ParagraphStyle::LineSpacingMode>(lineSpaMode));
}

void SampleItem::setLineSpa(double lineSpa)
{
	tmpStyle.setLineSpacing(lineSpa);
}

void SampleItem::setTextAlignment(int textAlignment)
{
	tmpStyle.setAlignment(textAlignment);
}

void SampleItem::setIndent(double indent)
{
	tmpStyle.setLeftMargin(indent);
}

void SampleItem::setFirst(double first)
{
	tmpStyle.setFirstIndent(first);
}

void SampleItem::setGapBefore(double gapBefore)
{
	tmpStyle.setGapBefore(gapBefore);
}

void SampleItem::setGapAfter(double gapAfter)
{
	tmpStyle.setGapAfter(gapAfter);
}

void SampleItem::setFont(QString font)
{
	tmpStyle.charStyle().setFont(PrefsManager::instance()->appPrefs.AvailFonts[font]);
}

void SampleItem::setFontSize(int fontSize, bool autoLineSpa)
{
	tmpStyle.charStyle().setFontSize(fontSize);
	if (autoLineSpa)
		tmpStyle.setLineSpacing(((fontSize / 10)  * (doc->typographicSettings.autoLineSpacing / 100) + (fontSize / 10)));
}

/*void SampleItem::setTabValues(QValueList<PageItem::TabRecord> tabValues)
{
	tmpStyle.TabValues = tabValues;
}*/

void SampleItem::setDrop(bool drop)
{
	tmpStyle.setHasDropCap(drop);
}

void SampleItem::setDropLin(int dropLin)
{
	tmpStyle.setDropCapLines(dropLin);
}

void SampleItem::setDropDist(double dropDist)
{
	tmpStyle.setDropCapOffset(dropDist);
}

void SampleItem::setFontEffect(int fontEffect)
{
	tmpStyle.charStyle().setEffects(static_cast<StyleFlag>(fontEffect));
}

void SampleItem::setFColor(QString fColor)
{
	tmpStyle.charStyle().setFillColor(fColor);
}

void SampleItem::setFShade(int fShade)
{
	tmpStyle.charStyle().setFillShade(fShade);
}

void SampleItem::setSColor(QString sColor)
{
	tmpStyle.charStyle().setStrokeColor(sColor);
}

void SampleItem::setSShade(int sShade)
{
	tmpStyle.charStyle().setStrokeShade(sShade);
}

void SampleItem::setBaseAdj(bool baseAdj)
{
	tmpStyle.setUseBaselineGrid(baseAdj);
}

void SampleItem::setTxtShadowX(int txtShadowX)
{
	tmpStyle.charStyle().setShadowXOffset(txtShadowX);
}

void SampleItem::setTxtShadowY(int txtShadowY)
{
	tmpStyle.charStyle().setShadowYOffset(txtShadowY);
}

void SampleItem::setTxtOutline(int txtOutline)
{
	tmpStyle.charStyle().setOutlineWidth(txtOutline);
}

void SampleItem::setTxtUnderPos(int txtUnderPos)
{
	tmpStyle.charStyle().setUnderlineOffset(txtUnderPos);
}

void SampleItem::setTxtUnderWidth(int txtUnderWidth)
{
	tmpStyle.charStyle().setUnderlineWidth(txtUnderWidth);
}

void SampleItem::setTxtStrikePos(int txtStrikePos)
{
	tmpStyle.charStyle().setStrikethruOffset(txtStrikePos);
}

void SampleItem::setTxtStrikeWidth(int txtStrikeWidth)
{
	tmpStyle.charStyle().setStrikethruWidth(txtStrikeWidth);
}

void SampleItem::setScaleH(int scaleH)
{
	tmpStyle.charStyle().setScaleH(scaleH);
}

void SampleItem::setScaleV(int scaleV)
{
	tmpStyle.charStyle().setScaleV(scaleV);
}

void SampleItem::setBaseOff(int baseOff)
{
	tmpStyle.charStyle().setBaselineOffset(baseOff);
}

void SampleItem::setKernVal(int kernVal)
{
	tmpStyle.charStyle().setTracking(kernVal);
}

QPixmap SampleItem::getSample(int width, int height)
{
	// if it's false => the used font will be removed from used fonts
	// after sample creating
	bool previouslyUsedFont = false;

	if (tmpStyle.charStyle().font() == &Foi::NONE)
		return QPixmap();

	UndoManager::instance()->setUndoEnabled(false); // disable undo

	PageItem_TextFrame *previewItem = new PageItem_TextFrame(doc, 0, 0, width, height, 0, "__whiteforpreviewbg__", "__whiteforpreview__");
	QPixmap pm(width, height);
	ScPainter *painter = new ScPainter(&pm, width, height, 0, 0);
	double sca = 1.0; // original scale to set back at the end...
	int userAppMode = ScMW->doc->appMode; // We need to be in normal when creating/repainting items
	ScMW->doc->appMode = modeNormal;

	if (ScMW->view != NULL)
	{
		sca = ScMW->view->scale();
		ScMW->view->setScale(1.0);
	}

	if (doc->UsedFonts.contains(tmpStyle.charStyle().font()->scName()))
		previouslyUsedFont = true;

	doc->AddFont(tmpStyle.charStyle().font()->scName(), qRound(doc->toolSettings.defSize / 10.0));
	doc->docParagraphStyles.append(tmpStyle);
	int tmpIndex = doc->docParagraphStyles.count() - 1;

	previewItem->FrameType = PageItem::TextFrame;
	previewItem->itemText.clear();
//	previewItem->setFont(tmpStyle.charStyle().font()->scName());
	previewItem->Cols = 1;
	text.replace(QChar(10),QChar(13)).replace(QChar(5),QChar(13));
	previewItem->itemText.insertChars(0, text);
	doc->chAbStyle(previewItem, tmpIndex);
	previewItem->itemText.applyStyle(0, text.length(), tmpStyle.charStyle());
	previewItem->setFillColor("__whiteforpreviewbg__");
	previewItem->setFillShade(bgShade);
	previewItem->SetRectFrame();
	previewItem->Frame = false;
	previewItem->DrawObj(painter, QRect(0, 0, width, height));
	painter->end();
	delete(painter);
	delete previewItem;

	// cleanups and resets
	if (!previouslyUsedFont)
		doc->UsedFonts.remove(tmpStyle.charStyle().font()->scName());
	if (ScMW->view != NULL)
		ScMW->view->setScale(sca);
	doc->appMode = userAppMode;
	doc->docParagraphStyles.remove(doc->docParagraphStyles.fromLast());
	UndoManager::instance()->setUndoEnabled(true);
	return pm;
}

void SampleItem::cleanupTemporary()
{
	// clear tmp colors
	ScMW->doc->PageColors.remove("__blackforpreview__");
	ScMW->doc->PageColors.remove("__whiteforpreview__");
	ScMW->doc->PageColors.remove("__whiteforpreviewbg__");
}
