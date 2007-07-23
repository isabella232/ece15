#ifndef SCTEXT_SHARED_H
#define SCTEXT_SHARED_H

#include <QObject>
#include <QString>
#include <Q3ValueVector>
#include <Q3PtrVector>
#include <Q3PtrList>
#include <cassert>

//#include "text/paragraphlayout.h"
#include "text/frect.h"
#include "style.h"
#include "styles/charstyle.h"
#include "styles/paragraphstyle.h"
#include "styles/stylecontextproxy.h"


class SCRIBUS_API ScText_Shared : public Q3PtrList<ScText>
{
public:
	ParagraphStyle defaultStyle;
	StyleContextProxy pstyleContext;
	uint refs;
	uint len;
	ParagraphStyle trailingStyle;
	ScText_Shared(const StyleContext* pstyles);	

	ScText_Shared(const ScText_Shared& other);

	ScText_Shared& operator= (const ScText_Shared& other);

	~ScText_Shared();
	
	/**
	   A char's stylecontext is the containing paragraph's style, 
       This routines makes sure that all charstyles look for defaults
	   in the parstyle first.
	 */
	void replaceCharStyleContextInParagraph(int pos, const StyleContext* newContext);
};

#endif /*SCTEXT_SHARED_H*/
