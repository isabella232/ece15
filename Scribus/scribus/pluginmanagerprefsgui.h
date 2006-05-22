/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef PLUGINMANAGERPREFS_H
#define PLUGINMANAGERPREFS_H

#include "qwidget.h"
#include "qmap.h"
#include "prefspanel.h"
#include "qpixmap.h"

class QVBoxLayout;
class QGroupBox;
class QGridLayout;
class QListView;
class QLabel;
class QListViewItem;

class PluginManagerPrefsGui : public PrefsPanel
{
	Q_OBJECT

	public:
		PluginManagerPrefsGui(QWidget * parent);
		~PluginManagerPrefsGui();

	public slots:
		/*! \brief Set selected item(=plugin) un/loadable
		\author Petr Vanek
		\param item atual item
		\param column id of the column clicked 0=1st
		*/
		void updateSettings(QListViewItem *item, const QPoint &, int column);

		//! \brief Apply changes to each plugin's PluginSettings
		void apply();

	private:
		QPixmap checkOn;
		QPixmap checkOff;

	protected:
		QVBoxLayout* pluginMainLayout;
		QGroupBox* plugGroupBox;
		QGridLayout* plugGroupBoxLayout;
		QVBoxLayout* plugLayout1;
		QListView* pluginsList;
		QLabel* pluginWarning;

		/*! \brief Stores current settings for each plugin
		 * \param enableOnStartup - Load the plug-in on startup?
		 */
		struct PluginSettings
		{
			bool enableOnStartup;
		};

		//! \brief Store current settings about each plug-in
		QMap<QCString,PluginSettings> pluginSettings;
};

#endif
