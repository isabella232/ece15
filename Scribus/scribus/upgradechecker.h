/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef UPGRADECHECKER_H
#define UPGRADECHECKER_H

#include <qhttp.h>
#include <qobject.h>
#include <qstring.h>
#include <qstringlist.h>

/**
	@author Craig Bradney <cbradney@zip.com.au>
*/
class UpgradeChecker : public QObject
{
	Q_OBJECT
	
public:
	UpgradeChecker();
	~UpgradeChecker();
	
	bool fetch();
	bool process(QFile& dataFile);
	void show(bool error);
	QStringList upgradeData();
	
public slots:
	void fileStarted(bool error);
	void fileFinished(bool error);
	void reqStarted(int id);
	void reqFinished(int id, bool error);
	
protected:
	QString version;
	QString stability;
	uint major, minor, revision1, revision2;
	bool isCVS;
	QString platform;
	QStringList updates;
	QString tempFile;
	bool fin;
	QHttp* getter;
	int getterID;
	bool retrieveError;
};

#endif
