#ifndef SCRIPTERCORE_H
#define SCRIPTERCORE_H

#include "cmdvar.h"

#include "qmap.h"
#include "qguardedptr.h"

#include "menumanager.h"
#include "pconsole.h"
#include "conswin.h"

class ScrAction;
class MenuManager;

class ScripterCore : public QObject
{
	Q_OBJECT

public:
	ScripterCore(QWidget* parent);
	~ScripterCore();

public slots:
	void slotTest();
	void StdScript(QString filebasename);
	void RecentScript(QString fn);
	void slotRunScriptFile(QString fileName, bool inMainInterpreter = false);
	QString slotRunScript(QString Script);
	void slotInteractiveScript(bool);
	void slotExecute();
	void aboutScript();
	/*** Sets up the plugin for extension scripts, if enabled */
	void initExtensionScripts();
	/*** Runs the startup script, if enabled */
	void runStartupScript();
	void languageChange();

protected:
	// Private helper functions
	void FinishScriptRun();
	void ReadPlugPrefs();
	void SavePlugPrefs();
	void rebuildRecentScriptsMenu();
	void buildScribusScriptsMenu();
	void buildRecentScriptsMenu();
	void rebuildScribusScriptsMenu();

	// Internal members
	PConsole pcon;
	int cons;
	int about;
	QStringList SavedRecentScripts;
	QStringList RecentScripts;
	MenuManager *menuMgr;
	QMap<QString, QGuardedPtr<ScrAction> > scrScripterActions;
	QMap<QString, QGuardedPtr<ScrAction> > scrRecentScriptActions;

	// Preferences
	/*** pref: Enable access to main interpreter and 'extension scripts' */
	bool enableExtPython;
	/*** pref: Run 'from scribus import *' at scripter startup */
	bool importAllNames;
	/*** pref: Load this script on startup */
	QString startupScript;
};

#endif
