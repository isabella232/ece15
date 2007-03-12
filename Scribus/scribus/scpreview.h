/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef SCPREVIEW_H
#define SCPREVIEW_H

#include "scribusapi.h"
#include "scribusstructs.h"
//Added by qt3to4:
#include <Q3ValueList>
#include <QPixmap>

class QString;
class ScColor;
class PrefsManager;
class QDomDocument;

class SCRIBUS_API ScPreview
{
public:
	ScPreview();
	~ScPreview() {};
	QPixmap createPreview(QString data);
	void SetFarbe(QColor *tmp, const QString& farbe, int shad);
	void DrawZeichenS(ScPainter *p, double xco, double yco, QString ch, QString ZFo, bool Reverse, int Style, int mode, int Siz);
	QMap<QString,ScColor> Farben;
	QMap<QString,multiLine> MLineStyles;
	Q3ValueList<uint> Segments;
protected:
	PrefsManager* prefsManager;
};
#endif

