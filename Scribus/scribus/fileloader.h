#ifndef _FILELOADER_
#define _FILELOADER_
#include <qstring.h>
#include <qvaluelist.h>
#include <qmap.h>

#include "scribusapi.h"
#include "scribusstructs.h"

class QDomElement;
class QProgressBar;
class ScribusDoc;
class ScribusView;
class ScribusApp;
class SCFonts;
class PrefsManager;

class SCRIBUS_API FileLoader
{
public:
	FileLoader(QString fileName, ScribusApp* app);
	~FileLoader() {};
	int TestFile();
	int CheckScribus();
	QString ReadDatei(QString fileName);
	bool LoadFile(ScribusApp* app);
	bool ReadDoc(ScribusApp* app, QString fileName, SCFonts &avail, ScribusDoc *doc, ScribusView *view, QProgressBar *dia2);
	void GetItemText(QDomElement *it, ScribusDoc *doc, PageItem* obj);
	PageItem* PasteItem(QDomElement *obj, ScribusDoc *doc, ScribusView *view);
	QString FileName;
	int FileType;
	bool havePS;
	bool haveSVG;
	bool haveSXD;
	bool newReplacement;
	QValueList<int> LFrames;
	QMap<QString,QString> ReplacedFonts;
	QMap<uint,QString> DoVorl;
	QPtrList<Foi> dummyFois;
	
private:
	PrefsManager* prefsManager;
};

#endif
