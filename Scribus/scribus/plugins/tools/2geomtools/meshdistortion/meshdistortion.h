/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
*   Copyright (C) 2008 by Franz Schmid                                     *
*   franz.schmid@altmuehlnet.de                                            *
*                                                                          *
*   This program is free software; you can redistribute it and/or modify   *
*   it under the terms of the GNU General Public License as published by   *
*   the Free Software Foundation; either version 2 of the License, or      *
*   (at your option) any later version.                                    *
*                                                                          *
*   This program is distributed in the hope that it will be useful,        *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*   GNU General Public License for more details.                           *
*                                                                          *
*   You should have received a copy of the GNU General Public License      *
*   along with this program; if not, write to the                          *
*   Free Software Foundation, Inc.,                                        *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
****************************************************************************/

#ifndef MESHDISTORTION_H
#define MESHDISTORTION_H

#include "pluginapi.h"
#include "scplugin.h"
#include "selection.h"

/** \brief This is a simple "MeshDistortion" plugin for Scribus 1.3.5 and later.
\author Franz Schmid
\date November 2007
*/
class PLUGIN_API MeshDistortionPlugin : public ScActionPlugin
{
	Q_OBJECT

	public:
		// Standard plugin implementation
		MeshDistortionPlugin();
		virtual ~MeshDistortionPlugin();
		virtual bool run(ScribusDoc* doc, QString target = QString::null);
		virtual const QString fullTrName() const;
		virtual const AboutData* getAboutData() const;
		virtual void deleteAboutData(const AboutData* about) const;
		virtual void languageChange();
		virtual void addToMainWindowMenu(ScribusMainWindow *) {};
		PageItem *patternItem;
		ScribusDoc* currDoc;
};

extern "C" PLUGIN_API int meshdistortion_getPluginAPIVersion();
extern "C" PLUGIN_API ScPlugin* meshdistortion_getPlugin();
extern "C" PLUGIN_API void meshdistortion_freePlugin(ScPlugin* plugin);

#endif
 
