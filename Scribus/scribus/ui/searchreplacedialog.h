#ifndef SEARCHREPLACEDIALOG_H
#define SEARCHREPLACEDIALOG_H

#include "ui_searchreplacedialog.h"
#include "scribusapi.h"
class ScrSpinBox;
class FontCombo;
class StyleSelect;
class ShadeButton;
class PrefsContext;
class ColorCombo;
class ScribusDoc;
class PageItem;

class SCRIBUS_API SearchReplaceDialog : public QDialog, private Ui::SearchreplaceDialog
{
	Q_OBJECT
	
public:
	explicit SearchReplaceDialog(QWidget *parent, ScribusDoc *doc, PageItem* ite, bool mode = false );
	void languageChange();
	void unitChange(int unitIndex);

protected:
	void changeEvent(QEvent *e);
//	void doSearch();
	bool checkItem(PageItem* item, bool onlyItemsSearch);
	bool onlyItemsSearch();
	void doReplace();
	void readPrefs();
	void connectIndexReset(QObject * child = NULL);
	void rebuildRangeCombo();
	PageItem* Item;
	ScribusDoc* Doc;
	uint ReplStart;
	PrefsContext* prefs;
	bool NotFound;
	bool styleEditorMode;
	int matchesFound;
	int currItemIndex;

public slots:
	void slotSearch();
	void slotReplace();
	void slotReplaceAll();
	void enableTxSearch();
	void enableStyleSearch();
	void enableAlignSearch();
	void enableFontSearch();
	void enableSizeSearch();
	void enableEffSearch();
	void enableFillSearch();
	void enableFillSSearch();
	void enableStrokeSearch();
	void enableStrokeSSearch();
	void enableTxReplace();
	void enableStyleReplace();
	void enableAlignReplace();
	void enableFontReplace();
	void enableSizeReplace();
	void enableEffReplace();
	void enableFillReplace();
	void enableFillSReplace();
	void enableStrokeReplace();
	void enableStrokeSReplace();
	void writePrefs();
	void clear();
	void resetIndexes();

signals:
	void NewFont(const QString&);
	void NewAbs(int);
};

#endif // SEARCHREPLACEDIALOG_H
