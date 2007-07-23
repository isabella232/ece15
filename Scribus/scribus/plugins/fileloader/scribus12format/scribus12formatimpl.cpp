/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "scribus12formatimpl.h"
//#include "scribus12formatimpl.moc"
#include "scribuscore.h"

#include <QString>
#include <QMessageBox>

// Initialize members here, if any
Scribus12FormatImpl::Scribus12FormatImpl() : QObject(0, "Scribus12FormatImpl")
{
}

// This method is connected to the "import page" entry in the UI
// For now, we just call back into Scribus
bool Scribus12FormatImpl::run(const QString & )
{
	ScCore->primaryMainWindow()->slotPageImport();
	return true;
}
