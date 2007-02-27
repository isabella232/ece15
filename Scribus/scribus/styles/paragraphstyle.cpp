/*
 For general Scribus (>=1.3.2) copyright and licensing information please refer
 to the COPYING file provided with the program. Following this notice may exist
 a copyright and/or license notice that predates the release of Scribus 1.3.2
 for which a new license (GPL+exception) is in place.
 */
/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/



#include "styles/style.h"
#include "paragraphstyle.h"
#include "desaxe/saxiohelper.h"
#include "desaxe/simple_actions.h"


ParagraphStyle::ParagraphStyle() : Style(), cstyleContext(NULL), cstyleContextIsInh(true), cstyle()
{
	setParent("");
	cstyleContext.setDefaultStyle( &cstyle );
//	qDebug(QString("ParagraphStyle() %1 pcontext %2 ccontext %3").arg(reinterpret_cast<uint>(this)).arg(reinterpret_cast<uint>(context())).arg(reinterpret_cast<uint>(defaultStyle()->context())));
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	m_##attr_NAME = attr_DEFAULT; \
	inh_##attr_NAME = true;
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
}


ParagraphStyle::ParagraphStyle(const ParagraphStyle& other) : Style(other), cstyleContext(NULL), cstyleContextIsInh(other.cstyleContextIsInh), cstyle(other.charStyle())
{
	if (cstyleContextIsInh)
		cstyle.setContext(NULL);
	else
		cstyle.setContext(other.charStyle().context());
	cstyleContext.setDefaultStyle( &cstyle );
//	qDebug(QString("ParagraphStyle(%2) %1").arg(reinterpret_cast<uint>(&other)).arg(reinterpret_cast<uint>(this)));
	other.validate();

#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	m_##attr_NAME = other.m_##attr_NAME; \
	inh_##attr_NAME = other.inh_##attr_NAME;
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
}

ParagraphStyle::~ParagraphStyle()
{
//	qDebug(QString("~ParagraphStyle %1").arg(reinterpret_cast<uint>(this)));
}
	

QString ParagraphStyle::displayName() const
{
	if ( hasName() || !hasParent() || !m_context)
		return name();
	//	else if ( inheritsAll() )
	//		return parent()->displayName();
	else 
		return parentStyle()->displayName() + "+";
}


bool ParagraphStyle::equiv(const Style& other) const
{
	other.validate();
	const ParagraphStyle* oth = dynamic_cast<const ParagraphStyle*> ( & other );
	return  oth &&
		parent() == oth->parent() && cstyle.equiv(oth->charStyle())
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
		&& (inh_##attr_NAME == oth->inh_##attr_NAME) \
		&& (inh_##attr_NAME || m_##attr_NAME == oth->m_##attr_NAME)
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
		;
}	



ParagraphStyle& ParagraphStyle::operator=(const ParagraphStyle& other) 
{
	other.validate();
	static_cast<Style&>(*this) = static_cast<const Style&>(other);

	cstyle = other.charStyle();

	// we dont want cstyleContext to point to other's charstyle...
	cstyleContext.setDefaultStyle( &cstyle );
	
	if (cstyleContextIsInh)
	{
		const ParagraphStyle * parent = dynamic_cast<const ParagraphStyle*> ( parentStyle() );
		cstyle.setContext(parent ? parent->charStyleContext() : NULL);
	}
	else
	{
		cstyle.setContext(other.charStyle().context());
	}
	
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	m_##attr_NAME = other.m_##attr_NAME; \
	inh_##attr_NAME = other.inh_##attr_NAME;
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
	return *this;
}


void ParagraphStyle::setContext(const StyleContext* context)
{
	Style::setContext(context);
//	qDebug(QString("ParagraphStyle::setContext(%1) parent=%2").arg((unsigned long int)context).arg((unsigned long int)oth));
	repairImplicitCharStyleInheritance();
}

void ParagraphStyle::repairImplicitCharStyleInheritance()
{
	if (cstyleContextIsInh) {
		const ParagraphStyle * newParent = dynamic_cast<const ParagraphStyle*> ( parentStyle() );
		cstyle.setContext(newParent ? newParent->charStyleContext() : NULL);
	}
}


void ParagraphStyle::breakImplicitCharStyleInheritance(bool val)
{ 
	cstyleContextIsInh = !val;
	repairImplicitCharStyleInheritance();
}

void ParagraphStyle::update(const StyleContext* context)
{
	Style::update(context);
	assert ( &cstyleContext != cstyle.context());

	repairImplicitCharStyleInheritance();
	assert ( &cstyleContext != cstyle.context());
	cstyle.validate();
	cstyleContext.invalidate();

	const ParagraphStyle * oth = dynamic_cast<const ParagraphStyle*> ( parentStyle() );
//	qDebug(QString("ParagraphStyle::update(%1) parent=%2").arg((unsigned long int)context).arg((unsigned long int)oth));
	if (oth) {
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
		if (inh_##attr_NAME) \
			m_##attr_NAME = oth->attr_GETTER();
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
	}
}



void ParagraphStyle::applyStyle(const ParagraphStyle& other) 
{
	Style::applyStyle(other);
	cstyle.applyCharStyle(other.charStyle());
	cstyleContext.invalidate();
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	if (! other.inh_##attr_NAME) \
		set##attr_NAME(other.m_##attr_NAME);
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
}


void ParagraphStyle::eraseStyle(const ParagraphStyle& other) 
{
	other.validate();
	Style::eraseStyle(other);
	cstyle.eraseCharStyle(other.charStyle());
	cstyleContext.invalidate();
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	if (!inh_##attr_NAME && m_##attr_NAME == other.m_##attr_NAME) \
		reset##attr_NAME();
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
}

void ParagraphStyle::setStyle(const ParagraphStyle & other) 
{
	other.validate();
	setParent(other.parent());
	cstyle.setStyle(other.charStyle());
	cstyleContext.invalidate();
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	inh_##attr_NAME = other.inh_##attr_NAME; \
	m_##attr_NAME = other.m_##attr_NAME;
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
}


static QString toXMLString(ParagraphStyle::AlignmentType val)
{
	return QString::number(static_cast<int>(val));
}


static QString toXMLString(const QValueList<ParagraphStyle::TabRecord> & )
{
	return "dummy";
}

void ParagraphStyle::saxx(SaxHandler& handler, const Xml_string elemtag) const
{
	Xml_attr att;
	Style::saxxAttributes(att);
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	if (!inh_##attr_NAME && strcmp(# attr_NAME, "TabValues") != 0) \
		att.insert(# attr_NAME, toXMLString(m_##attr_NAME)); 
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
	if (!name().isEmpty())
		att["id"] = elemtag + toXMLString((unsigned long)(this));
	handler.begin(elemtag, att);
	if (parentStyle() && hasParent())
		parentStyle()->saxx(handler);
	QValueList<ParagraphStyle::TabRecord>::const_iterator it;
	for (it=m_TabValues.begin(); it != m_TabValues.end(); ++it)
	{
		const ParagraphStyle::TabRecord& tb(*it);
		Xml_attr tab;
		tab.insert("pos", toXMLString(tb.tabPosition));
		tab.insert("fillChar", toXMLString(tb.tabFillChar.unicode()));
		tab.insert("type", toXMLString(tb.tabType));
		handler.beginEnd("tabstop", tab);
	}
	if (charStyle() != CharStyle())
		charStyle().saxx(handler);
	handler.end(elemtag);
}

///   PageItem StoryText -> PageItem StoryText
class SetCharStyle_body : public desaxe::Action_body
{
	void end (const Xml_string /*tagname*/)
	{
		ParagraphStyle* pstyle = this->dig->top<ParagraphStyle>(1);
		CharStyle* cstyle = this->dig->top<CharStyle>(0);
		pstyle->charStyle() = *cstyle;
	}
};

class SetCharStyle : public desaxe::MakeAction<SetCharStyle_body>
{};



class SetTabStop_body : public desaxe::Action_body
{
	void begin (const Xml_string /*tagname*/, Xml_attr attr)
	{
		ParagraphStyle* pstyle = this->dig->top<ParagraphStyle>();
		ParagraphStyle::TabRecord tb;
		tb.tabPosition = parseDouble(attr["pos"]);
		tb.tabFillChar = QChar(parseInt(attr["fillChar"]));
		tb.tabType = parseInt(attr["type"]);
		QValueList<ParagraphStyle::TabRecord> tabs = pstyle->tabValues();
		tabs.append(tb);
		pstyle->setTabValues(tabs);
	}
};

class SetTabStop : public desaxe::MakeAction<SetTabStop_body>
{};




template<>
ParagraphStyle::AlignmentType parse<ParagraphStyle::AlignmentType>(Xml_string str)
{
	return parseEnum<ParagraphStyle::AlignmentType>(str);
}


template<>
ParagraphStyle::LineSpacingMode parse<ParagraphStyle::LineSpacingMode>(Xml_string str)
{
	return parseEnum<ParagraphStyle::LineSpacingMode>(str);
}


typedef QValueList<ParagraphStyle::TabRecord> Tablist;

template<>
Tablist parse<Tablist>(Xml_string str)
{
	return Tablist();
}


using namespace desaxe;

const Xml_string ParagraphStyle::saxxDefaultElem("style");

void ParagraphStyle::desaxeRules(Xml_string prefixPattern, Digester& ruleset, Xml_string elemtag)
{
	typedef ParagraphStyle::TabRecord TabRecord;
		
	Xml_string stylePrefix(Digester::concat(prefixPattern, elemtag));
	ruleset.addRule(stylePrefix, Factory<ParagraphStyle>());
	ruleset.addRule(stylePrefix, IdRef<ParagraphStyle>());
	Style::desaxeRules<ParagraphStyle>(prefixPattern, ruleset, elemtag);
#define ATTRDEF(attr_TYPE, attr_GETTER, attr_NAME, attr_DEFAULT) \
	if ( strcmp(# attr_NAME, "TabValues") != 0) \
		ruleset.addRule(stylePrefix, SetAttributeWithConversion<ParagraphStyle, attr_TYPE> ( & ParagraphStyle::set##attr_NAME,  # attr_NAME, &parse<attr_TYPE> ));
#include "paragraphstyle.attrdefs.cxx"
#undef ATTRDEF
	Xml_string charstylePrefix(Digester::concat(stylePrefix, CharStyle::saxxDefaultElem));
	CharStyle::desaxeRules(stylePrefix, ruleset);
	ruleset.addRule(charstylePrefix, SetCharStyle());
	
	Xml_string tabPrefix(Digester::concat(stylePrefix, "tabstop"));
	ruleset.addRule(tabPrefix, SetTabStop());
}
