/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
 
#ifndef SCCOLORMNGTSTRUCTS_H
#define SCCOLORMNGTSTRUCTS_H

#include <QString>

typedef enum
{
	Format_Undefined,
	Format_RGB_8,
	Format_RGB_16,
	Format_RGBA_8,
	Format_RGBA_16,
	Format_ARGB_8,
	Format_ARGB_16,
	Format_BGRA_8,
	Format_BGRA_16,
	Format_CMYK_8,
	Format_CMYK_16,
	Format_CMYKA_8,
	Format_CMYKA_16,
	Format_YMCK_8,
	Format_YMCK_16,
	Format_GRAY_8,
	Format_GRAY_16
} eColorFormat;

typedef enum
{
	Ctf_BlackPointCompensation = 1,
	Ctf_BlackPreservation      = 2,
	Ctf_Softproofing           = 4,
	Ctf_GamutCheck             = 8
} eColorTransformFlags;

typedef enum
{
	Intent_Perceptual,
	Intent_Relative_Colorimetric,
	Intent_Saturation,
	Intent_Absolute_Colorimetric
} eRenderIntent;

class ScColorMngtStrategy
{
public:
	bool useBlackPointCompensation;
	bool useBlackPreservation;
	
	ScColorMngtStrategy ()
	{
		useBlackPointCompensation = true;
		useBlackPreservation      = false;
	}
};

typedef struct
{
	QString inputProfile;
	QString outputProfile;
	QString proofingProfile;
	eColorFormat inputFormat;
	eColorFormat outputFormat;
	eRenderIntent renderIntent;
	eRenderIntent proofingIntent;
	long flags;
} ScColorTransformInfo;

bool operator==(const ScColorTransformInfo& v1, const ScColorTransformInfo& v2);

#endif
