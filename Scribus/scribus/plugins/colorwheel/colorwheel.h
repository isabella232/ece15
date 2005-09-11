/* $Id$ */
#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include "pluginapi.h"
#include "scplugin.h"

/** \brief This is a simple "Color Theory" plugin for Scribus 1.3 and later.
Harmonious colors are colors that work well together, that produce a color
scheme that looks attractive; the color wheel can be used as a valuable
tool for determining harmonious colors.
More on: http://en.wikipedia.org/wiki/Color_wheel
\author Petr Vanek; petr@yarpen.cz
\date April 2005
*/

class PLUGIN_API ColorWheelPlugin : public ScActionPlugin
{
	Q_OBJECT

	public:
		// Standard plugin implementation
		ColorWheelPlugin();
		virtual ~ColorWheelPlugin();
		virtual bool run(QString target = QString::null);
		virtual const QString fullTrName() const;
		virtual const AboutData* getAboutData() const;
		virtual void deleteAboutData(const AboutData* about) const;
		virtual void languageChange();

		// Special features (none)
};

extern "C" PLUGIN_API int colorwheel_getPluginAPIVersion();
extern "C" PLUGIN_API ScPlugin* colorwheel_getPlugin();
extern "C" PLUGIN_API void colorwheel_freePlugin(ScPlugin* plugin);

#endif
