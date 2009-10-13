/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#ifndef SCLCMSCOLORPROFILEIMPL_H
#define SCLCMSCOLORPROFILEIMPL_H

#include <QString>

#include "lcms.h"
#include "sccolormngtimplelem.h"
#include "sccolorprofiledata.h"

class ScLcmsColorProfileImpl : public ScColorProfileImplBase
{
	friend class ScLcmsColorMngtEngineImpl;

public:
	ScLcmsColorProfileImpl(ScColorMngtEngine& engine, cmsHPROFILE lcmsProfile);
	virtual ~ScLcmsColorProfileImpl();

	virtual bool isNull() const;

	virtual icColorSpaceSignature   colorSpace()  const;
	virtual icProfileClassSignature deviceClass() const;
	virtual QString                 productDescription() const;

protected:
	cmsHPROFILE     m_profileHandle;
	mutable QString m_productDescription;

	void closeProfile(void);
};

#endif
