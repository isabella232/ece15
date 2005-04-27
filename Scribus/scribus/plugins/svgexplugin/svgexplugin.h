#ifndef SVGPLUG_H
#define SVGPLUG_H

#include <qobject.h>
#include <qdom.h>
#include "pluginmanager.h"

class QString;
class ScribusApp;
class PageItem;
class Page;

/** Calls the Plugin with the main Application window as parent
  * and the main Application Class as parameter */
extern "C" void run(QWidget *d, ScribusApp *plug);
/** Returns the Name of the Plugin.
  * This name appears in the relevant Menue-Entrys */
extern "C" QString name();
/** Returns the Type of the Plugin.
  * 1 = the Plugin is a normal Plugin, which appears in the Extras Menue
  * 2 = the Plugins is a import Plugin, which appears in the Import Menue
  * 3 = the Plugins is a export Plugin, which appears in the Export Menue */
extern "C" PluginManager::PluginType type();
extern "C" int ID();

extern "C" QString actionName();
extern "C" QString actionKeySequence();
extern "C" QString actionMenu();
extern "C" QString actionMenuAfterName();
extern "C" bool actionEnabledOnStartup();

class SVGExPlug : public QObject
{
    Q_OBJECT

public:
    SVGExPlug( ScribusApp *plug, QString fName );
    ~SVGExPlug();

private:
		void ProcessPage(ScribusApp *plug, Page *Seite, QDomDocument *docu, QDomElement *elem);
		QString SetClipPathImage(PageItem *ite);
		QString SetClipPath(PageItem *ite);
		QString FToStr(double c);
		QString IToStr(int c);
		void SetTextProps(QDomElement *tp, struct ScText *hl, ScribusApp *plug);
		QString SetFarbe(QString farbe, int shad, ScribusApp *plug);
		QString GetMultiStroke(ScribusApp *plug, struct SingleLine *sl, PageItem *Item);
		int GradCount;
		int ClipCount;
};

#endif // CMSPLUG_H
