/***************************************************************************
                          scribusdoc.cpp  -  description
                             -------------------
    begin                : Fre Apr  6 21:47:55 CEST 2001
    copyright            : (C) 2001 by Franz Schmid
    email                : Franz.Schmid@altmuehlnet.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "scribusdoc.h"
#include <qfile.h>

ScribusDoc::ScribusDoc()
{
  modified = false;
  MasterP = false;
  Marks = true;
	Guides = true;
	GuideLock = false;
	SnapGuides = false;
  ShowPic = true;
  Raster = false;
  useRaster = false;
  EditClip = false;
  EditClipMode = 0;
  loading = false;
  minorGrid = 20;
  majorGrid = 100;
  minorColor = QColor(green);
  majorColor = QColor(green);
	guideColor = QColor(darkBlue);
	GuideRad = 10;
  Scale = 1.0;
	Dpen = "Black";
	Dshade2 = 100;
	Dbrush = "Black";
	Dshade = 100;
	Dwidth = 1;
	DLineArt = SolidLine;
	DocName = "Document-";
	UsedFonts.clear();
	Dfont = "";
	Dsize = 12;
	CurrentSel = -1;
	DocTitel = "";
	DocAutor = "";
	DocComments = "";
	PageC = 0;
	LastAuto = 0;
	FirstAuto = 0;
	DraggedElem = 0;
	GroupCounter = 1;
	Vorlagen.clear();
	struct StVorL vg;
	vg.Vname = "Normal Internal";
	vg.LineSpa = 15;
	vg.Ausri = 0;
	vg.Indent = 0;
	vg.First = 0;
	vg.Avor = 0;
	vg.Anach = 0;
	vg.Font = "";
	vg.FontSize = Dsize;
	Vorlagen.append(vg);
	vg.Vname = "Center Internal";
	vg.Ausri = 1;
	Vorlagen.append(vg);
	vg.Vname = "Rechts Internal";
	vg.Ausri = 2;
	Vorlagen.append(vg);
	vg.Vname = "Block Internal";
	vg.Ausri = 3;
	Vorlagen.append(vg);
	vg.Vname = "EBlock Internal";
	vg.Ausri = 4;
	Vorlagen.append(vg);
	Layers.clear();
	struct Layer ll;
	ll.LNr = 0;
	ll.Level = 0;
	ll.Name = tr("Background");
	ll.Sichtbar = true;
	ll.Drucken = true;
	Layers.append(ll);
	ActiveLayer = 0;
	JavaScripts.clear();
	UnDoValid = false;
	UnData.UnCode = -1;
  CurrentStyle = 0;
  CurrentABStil = 0;
	TotalItems = 0;
	TemplateMode = false;
	PDF_Optionen.Thumbnails = false;
	PDF_Optionen.Articles = false;
	PDF_Optionen.Compress = true;
	PDF_Optionen.RecalcPic = false;
	PDF_Optionen.Bookmarks = false;
	PDF_Optionen.PicRes = 300;
	PDF_Optionen.Version = 13;
	PDF_Optionen.Resolution = 300;
	PDF_Optionen.Binding = 0;
	PDF_Optionen.EmbedList.clear();
	PDF_Optionen.PresentMode = false;
	PDF_Optionen.Datei = "";
	PDF_Optionen.PresentVals.clear();
	PDF_Optionen.UseRGB = false;
	PDF_Optionen.UseProfiles = false;
	PDF_Optionen.UseProfiles2 = false;
	PDF_Optionen.SolidProf = "";
	PDF_Optionen.SComp = 3;
	PDF_Optionen.ImageProf = "";
	PDF_Optionen.PrintProf = "";
	PDF_Optionen.Info = "";
	PDF_Optionen.Intent = 0;
	PDF_Optionen.Intent2 = 0;
	PDF_Optionen.BleedTop = 0;
	PDF_Optionen.BleedLeft = 0;
	PDF_Optionen.BleedRight = 0;
	PDF_Optionen.BleedBottom = 0;
	PDF_Optionen.EmbeddedI = false;
	PDF_Optionen.Encrypt = false;
	PDF_Optionen.PassOwner = "";
	PDF_Optionen.PassUser = "";
	PDF_Optionen.Permissions = -4;
	RePos = false;
	BookMarks.clear();
	OldBM = false;
	hasName = false;
	RotMode = 0;
	ASaveTimer = new QTimer(this);
	MLineStyles.clear();
#ifdef HAVE_FREETYPE
	FT_Init_FreeType( &library );
#endif
}

ScribusDoc::~ScribusDoc()
{
#ifdef HAVE_FREETYPE
	FT_Done_FreeType( library );
#endif
}

void ScribusDoc::setModified()
{
	modified = true;
}

void ScribusDoc::setUnModified()
{
	modified = false;
}

bool ScribusDoc::isModified() const
{
  return modified;
}
/** Setzt die Seitenattribute */
void ScribusDoc::setPage(float b, float h, float t, float l, float r, float bo, float sp, float ab, bool atf, bool fp)
{
	PageB = b;
	PageH = h;
	PageM.Top = t;
	PageM.Left = l;
	PageM.Right = r;
	PageM.Bottom = bo;
	PageSp = sp;
	PageSpa = ab;
	PageFP = fp;
	PageAT = atf;
}

void ScribusDoc::resetPage(float t, float l, float r, float bo, bool fp)
{
	PageM.Top = t;
	PageM.Left = l;
	PageM.Right = r;
	PageM.Bottom = bo;
	PageFP = fp;
}

void ScribusDoc::AddFont(QString name, QFont fo)
{
#ifdef HAVE_FREETYPE
	FT_Face      face;
	FT_New_Face( library, (*AllFonts)[name]->Datei, 0, &face );
	FFonts[name] = face;
#endif
	UsedFonts[name] = fo;
	(*AllFonts)[name]->ReadMetrics();
	(*AllFonts)[name]->CharWidth[13] = 0;
#ifdef HAVE_FREETYPE
	QString afnm = (*AllFonts)[name]->Datei.left((*AllFonts)[name]->Datei.length()-3);
	QFile afm(afnm+"afm");
	if(!(afm.exists()))
		{
		afm.setName(afnm+"Afm");
		if(!(afm.exists()))
			afm.setName(afnm+"AFM");
		}
	if (afm.exists())
		FT_Attach_File(face, afm.name());
#endif
}
