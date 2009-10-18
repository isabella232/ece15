/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
 
#ifndef SCCOLORPROFILE_H
#define SCCOLORPROFILE_H

#include <QSharedPointer>
#include "scribusapi.h"
#include "sccolorprofiledata.h"

class SCRIBUS_API ScColorProfile
{
public:
	ScColorProfile();
	ScColorProfile(ScColorProfileData*);
	
	ScColorMngtEngine& engine() { return m_data->engine(); }
	const ScColorMngtEngine& engine() const { return m_data->engine(); }
	
	inline bool isNull()    const { return (m_data.isNull() || m_data->isNull()); }
	inline operator bool () const { return !isNull(); }

	QString profilePath() const;
	QString productDescription() const;
	
	icColorSpaceSignature   colorSpace()  const;
	icProfileClassSignature deviceClass() const;
	
	const ScColorProfileData* data() const { return m_data.data(); }

	bool operator==(const ScColorProfile& prof) const;
	
protected:
	QSharedPointer<ScColorProfileData> m_data;
};

#endif
