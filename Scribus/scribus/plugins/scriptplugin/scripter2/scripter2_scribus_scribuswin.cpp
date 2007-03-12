/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "cmdvar.h"

#include "scribuswin.h"

void export_ScribusWin()
{
	using namespace boost::python;

	class_<ScribusWin, bases<Q3MainWindow>, boost::noncopyable>("ScribusWin",
			"A Scribus document window",
			no_init);
}
