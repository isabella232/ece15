/***************************************************************************
                          util.cpp  -  description
                             -------------------
    begin                : Fri Sep 14 2001
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

#include <qstring.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qpainter.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <qmap.h>
#include <qdom.h>
#include <qimage.h>
#include <qdir.h>
#include <qpointarray.h>
#include <qmessagebox.h>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include "md5.h"
#include <setjmp.h>
#include "qprocess.h"

#ifdef _MSC_VER
 #if (_MSC_VER >= 1200)
  #include "win-config.h"
 #endif
#else
 #include "config.h"
#endif

extern "C" {
#define XMD_H           // shut JPEGlib up
#if defined(Q_OS_UNIXWARE)
#  define HAVE_BOOLEAN  // libjpeg under Unixware seems to need this
#endif
#include <jpeglib.h>
#include <jerror.h>
#undef HAVE_STDLIB_H
#ifdef const
#  undef const          // remove crazy C hackery in jconfig.h
#endif
}

#include "scribus.h"
#include "libpdf/pdflib.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_GLYPH_H
#ifdef HAVE_LIBZ
	#include <zlib.h>
#endif
#ifdef HAVE_TIFF
	#include <tiffio.h>
#endif
#ifdef HAVE_CMS
	#include CMS_INC
	extern cmsHPROFILE CMSoutputProf;
	extern cmsHPROFILE CMSprinterProf;
	extern cmsHTRANSFORM stdTrans;
	extern cmsHTRANSFORM stdProof;
	extern cmsHTRANSFORM stdTransImg;
	extern cmsHTRANSFORM stdProofImg;
	extern bool SoftProofing;
	extern bool Gamut;
	extern bool CMSuse;
	extern int IntentMonitor;
	extern int IntentPrinter;
#endif
extern ProfilesL InputProfiles;
extern ScribusApp* ScApp;

using namespace std;


QColor SetColor(ScribusDoc *currentDoc, QString color, int shad);
void GetItemProps(bool newVersion, QDomElement *obj, struct CopyPasteBuffer *OB);
QStringList sortQStringList(QStringList aList);
void ReOrderText(ScribusDoc *currentDoc, ScribusView *view);
void WordAndPara(PageItem* b, int *w, int *p, int *c, int *wN, int *pN, int *cN);
void CopyPageItem(struct CopyPasteBuffer *Buffer, PageItem *b);
bool overwrite(QWidget *parent, QString filename);
int setBestEncoding(FT_Face face);
FPointArray traceChar(FT_Face face, uint chr, int chs, double *x, double *y, bool &err);
FPoint getMaxClipF(FPointArray* Clip);
FPoint getMinClipF(FPointArray* Clip);
QPixmap FontSample(QString da, int s, QString ts, QColor back, bool force = false);
QPixmap fontSamples(QString da, int s, QString ts, QColor back);
QString Path2Relative(QString Path);
QPixmap LoadPDF(QString fn, int Page, int Size, int *w, int *h);
bool GlyNames(QMap<uint, QString> *GList, QString Dat);
bool GlyIndex(QMap<uint, PDFlib::GlNamInd> *GListInd, QString Dat);
QByteArray ComputeMD5Sum(QByteArray *in);
char *toHex( uchar u );
QString String2Hex(QString *in, bool lang = true);
QString CompressStr(QString *in);
QString ImageToTxt(QImage *im);
QString ImageToCMYK(QImage *im);
QString ImageToCMYK_PS(QImage *im, int pl, bool pre);
void Convert2JPG(QString fn, QImage *image, int Quality, bool isCMYK);
QString MaskToTxt(QImage *im, bool PDF = true);
QString MaskToTxt14(QImage *im);
void Level2Layer(ScribusDoc *currentDoc, struct Layer *ll, int Level);
void BezierPoints(QPointArray *ar, QPoint n1, QPoint n2, QPoint n3, QPoint n4);
double xy2Deg(double x, double y);
QPointArray FlattenPath(FPointArray ina, QValueList<uint> &Segs);
QPointArray RegularPolygon(double w, double h, uint c, bool star, double factor, double rota);
FPointArray RegularPolygonF(double w, double h, uint c, bool star, double factor, double rota);
QPixmap loadIcon(QString nam);
uint getDouble(QString in, bool raw);
bool loadText(QString nam, QString *Buffer);
double Cwidth(ScribusDoc *currentDoc, QString name, QString ch, int Siz, QString ch2 = " ");
double RealCWidth(ScribusDoc *currentDoc, QString name, QString ch, int Siz);
double QStodouble(QString in);
int QStoInt(QString in);
QString GetAttr(QDomElement *el, QString at, QString def="0");
QImage LoadPict(QString fn, bool *gray = 0);
#ifdef HAVE_CMS
	QImage ProofPict(QImage *Im, QString Prof, int Rend, cmsHPROFILE emPr=0);
	QImage LoadPictCol(QString fn, QString Prof, bool UseEmbedded, bool *realCMYK);
#else
	QImage ProofPict(QImage *Im, QString Prof, int Rend);
#endif
QImage ProofImage(QImage *Im);
int System(const QStringList & args);
int callGS(const QStringList & args_in);
int copyFile(QString source, QString target);
int moveFile(QString source, QString target);

#ifdef HAVE_CMS
QImage ProofPict(QImage *Im, QString Prof, int Rend, cmsHPROFILE emPr)
#else
QImage ProofPict(QImage *Im, QString Prof, int Rend)
#endif
{
	bool emp = false;
	if (Prof == "")
		return Im->copy();
#ifdef HAVE_CMS
	QImage out = Im->copy();
	if ((CMSuse) && (SoftProofing))
	{
		cmsHTRANSFORM xform;
		cmsHPROFILE inputProf;
	  	if (emPr != 0)
  			inputProf = emPr;
  		else
		{
  			inputProf = cmsOpenProfileFromFile(InputProfiles[Prof], "r");
			emp = true;
		}
		int dcmsFlags = 0;
		dcmsFlags |= Gamut ? cmsFLAGS_GAMUTCHECK : cmsFLAGS_SOFTPROOFING;
		xform = cmsCreateProofingTransform(inputProf, TYPE_RGBA_8,
												 CMSoutputProf, TYPE_RGBA_8,
												 CMSprinterProf,
												 IntentPrinter,
												 Rend, dcmsFlags);
		for (int i=0; i < out.height(); ++i)
		{
			LPBYTE ptr = out.scanLine(i);
			cmsDoTransform(xform, ptr, ptr, out.width());
		}
		cmsDeleteTransform(xform);
		if (emp)
			cmsCloseProfile(inputProf);
	}
	else
	{
		if (CMSuse)
		{
			cmsHTRANSFORM xform;
			cmsHPROFILE inputProf;
  			if (emPr != 0)
  				inputProf = emPr;
  			else
			{
  				inputProf = cmsOpenProfileFromFile(InputProfiles[Prof], "r");
				emp = true;
			}
			xform = cmsCreateTransform(inputProf, TYPE_RGBA_8,
										 	 CMSoutputProf, TYPE_RGBA_8,
										 	 Rend,
										 	 0);
			for (int i=0; i < out.height(); ++i)
			{
				LPBYTE ptr = out.scanLine(i);
				cmsDoTransform(xform, ptr, ptr, out.width());
			}
			cmsDeleteTransform(xform);
			if (emp)
				cmsCloseProfile(inputProf);
		}
	}
	return out;
#else
	return Im->copy();
#endif
}

QImage ProofImage(QImage *Image)
{
#ifdef HAVE_CMS
	QImage out = Image->copy();
	if ((CMSuse) && (SoftProofing))
	{
		for (int i=0; i < out.height(); ++i)
		{
			LPBYTE ptr = out.scanLine(i);
			cmsDoTransform(stdProofImg, ptr, ptr, out.width());
		}
	}
	else
	{
		if (CMSuse)
		{
			for (int i=0; i < out.height(); ++i)
			{
				LPBYTE ptr = out.scanLine(i);
				cmsDoTransform(stdTransImg, ptr, ptr, out.width());
			}
		}
	}
	return out;
#else
	return Image->copy();
#endif
}

/******************************************************************
 * Function System()
 *  
 * Create a new process via QProcess and wait until finished.
 * return the process exit code.
 *
 ******************************************************************/

int System(const QStringList & args)
{
	QProcess *proc = new QProcess(NULL);
	proc->setArguments(args);
	if ( !proc->start() )
	{
		delete proc;
		return 1;
	}
	/* start was OK */
	/* wait a little bit */
	while( proc->isRunning() )
		usleep(5000);

	int ex = proc->exitStatus();
	delete proc;
	return ex;
}

/******************************************************************
 * Function callGS()
 *   build the complete list of arguments for the call of our
 *   System() function.
 *
 *   The gs commands are all similar and consist of a few constant
 *   arguments, the variablke arguments and the end arguments which
 *   are also invariant.
 ******************************************************************/
 
int callGS(const QStringList & args_in)
{
	QString cmd1 = ScApp->Prefs.gs_exe;
	cmd1 += " -q -dNOPAUSE";
	if (ScApp->HavePngAlpha != 0)
		cmd1 += " -sDEVICE=png16m";
	else
		cmd1 += " -sDEVICE=pngalpha";
	if (ScApp->Prefs.gs_antiText)
		cmd1 += " -dTextAlphaBits=4";
	if (ScApp->Prefs.gs_antiGraph)
		cmd1 += " -dGraphicsAlphaBits=4";
	QString extArgs = args_in.join(" ");
	cmd1 += " " + extArgs + " -c showpage -c quit";
	return system(cmd1);
}

int copyFile(QString source, QString target)
{
	if ((source.isNull()) || (target.isNull()))
		return -1;
	if (source == target)
		return -1;
	QFile s(source);
	QFile t(target);
	if (!s.exists())
		return -1;
	QByteArray bb(s.size());
	if (s.open(IO_ReadOnly))
	{
		s.readBlock(bb.data(), s.size());
		s.close();
		if (t.open(IO_WriteOnly))
		{
			t.writeBlock(bb.data(), bb.size());
			t.close();
		}
	}
	return 0;
}

int moveFile(QString source, QString target)
{
	if ((source.isNull()) || (target.isNull()))
		return -1;
	if (source == target)
		return -1;
	copyFile(source, target);
	unlink(source);
	return 0;
}

QPixmap LoadPDF(QString fn, int Page, int Size, int *w, int *h)
{
	QString tmp, cmd1, cmd2;
	QString tmpFile = QDir::convertSeparators(QDir::homeDirPath()+"/.scribus/sc.png");
	QPixmap pm;
	int ret = -1;
	tmp.setNum(Page);
	QStringList args;
	args.append("-r72");
	args.append("-sOutputFile="+tmpFile);
	args.append("-dFirstPage="+tmp);
	args.append("-dLastPage="+tmp);
	args.append(fn);
	ret = callGS(args);
	if (ret == 0)
	{
		QImage image;
		image.load(tmpFile);
		unlink(tmpFile);
  		QImage im2;
		*h = image.height();
		*w = image.width();
		double sx = image.width() / static_cast<double>(Size);
		double sy = image.height() / static_cast<double>(Size);
		double t = (sy < sx ? sx : sy);
		im2 = image.smoothScale(static_cast<int>(image.width() / t), static_cast<int>(image.height() / t));
		pm.convertFromImage(im2);
		QPainter p;
		p.begin(&pm);
		p.setBrush(Qt::NoBrush);
		p.setPen(Qt::black);
		p.drawRect(0, 0, pm.width(), pm.height());
		p.end();
		im2.detach();
	}
	return pm;
}

QImage LoadPict(QString fn, bool *gray)
{
	QString tmp, dummy, cmd1, cmd2, BBox, tmp2;
	QChar tc;
	QImage Bild;
	double x, y, b, h;
	bool found = false;
	int ret = -1;
	QString tmpFile = QDir::convertSeparators(QDir::homeDirPath()+"/.scribus/sc.png");
	QFileInfo fi = QFileInfo(fn);
	QString ext = fi.extension(false).lower();
	if (ext == "pdf")
	{
		QStringList args;
		args.append("-r72");
		args.append("-sOutputFile="+tmpFile);
		args.append("-dFirstPage=1");
		args.append("-dLastPage=1");
		args.append(fn);
		ret = callGS(args);
		if (ret == 0)
		{
			QImage image;
			image.load(tmpFile);
  			Bild = image.convertDepth(32);
			unlink(tmpFile);
		}
	}
	if ((ext == "eps") || (ext == "ps"))
	{
		QFile f(fn);
		if (f.open(IO_ReadOnly))
		{
			QTextStream ts(&f);
			while (!ts.atEnd())
			{
				tc = ' ';
				tmp = "";
				while ((tc != '\n') && (tc != '\r'))
				{
					ts >> tc;
					if ((tc != '\n') && (tc != '\r'))
						tmp += tc;
				}
				if (tmp.startsWith("%%BoundingBox:"))
				{
					found = true;
					BBox = tmp.remove("%%BoundingBox:");
				}
				if (!found)
				{
					if (tmp.startsWith("%%BoundingBox"))
					{
						found = true;
						BBox = tmp.remove("%%BoundingBox");
					}
				}
				if (tmp.startsWith("%%EndComments"))
					break;
			}
			f.close();
			if (found)
			{
				QTextStream ts2(&BBox, IO_ReadOnly);
				ts2 >> x >> y >> b >> h;
				QStringList args;
				args.append("-r72");
				args.append("-sOutputFile="+tmpFile);
				args.append("-g"+tmp.setNum(qRound(b))+"x"+tmp2.setNum(qRound(h)));
				args.append(fn);
				ret = callGS(args);
				if (ret == 0)
				{
					QImage image;
					image.load(tmpFile);
				  	image = image.convertDepth(32);
					image.setAlphaBuffer(true);
					if (ScApp->HavePngAlpha != 0)
					{
						int wi = image.width();
						int hi = image.height();
					    for( int yi=0; yi < hi; ++yi )
						{
							QRgb *s = (QRgb*)(image.scanLine( yi ));
							for(int xi=0; xi < wi; ++xi )
							{
								if((*s) == 0xffffffff)
									(*s) &= 0x00ffffff;
								s++;
							}
				    	}
					}
					Bild = image.copy(static_cast<int>(x), 0, static_cast<int>(b-x), static_cast<int>(h-y));
					unlink(tmpFile);
				}
			}
		}
	}
#ifdef HAVE_TIFF
	if (ext == "tif")
	{
		QImage img;
		QImage inI2;
		TIFF* tif = TIFFOpen(fn, "r");
		if(tif)
		{
			unsigned width, height,size;
			TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
			TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
			size=width*height;
			uint32 *bits=(uint32*) _TIFFmalloc(size * sizeof (uint32));
			if(bits)
			{
				if (TIFFReadRGBAImage(tif, width, height, bits, 0))
				{
    		    		img.create(width,height,32);
				img.setAlphaBuffer(true);
					if(TIFFGetR(0x1234567)==qRed  (0x1234567) &&
						 TIFFGetG(0x1234567)==qGreen(0x1234567) &&
						 TIFFGetB(0x1234567)==qBlue (0x1234567))
					{
						for(unsigned y=0; y<height; ++y)
							memcpy(img.scanLine(height-1-y),bits+y*width,width*4);
					}
					else
					{
						uint32 *inp=bits;
						for(unsigned y=0; y<height; ++y)
						{
							QRgb *row=(QRgb*) (img.scanLine(height-1-y));
							for(unsigned x=0; x<width; ++x)
							{
								const uint32 col=*(inp++);
								row[x]=qRgba(TIFFGetR(col), TIFFGetG(col), TIFFGetB(col), TIFFGetA(col));
							}
						}
					}
					Bild = img.copy();
				}
				_TIFFfree(bits);
			}
			TIFFClose(tif);
		}
	}
#endif
	else
	{
		if (Bild.load(fn))
		{
			if (gray != 0)
			{
				if ((Bild.depth() == 8) && (Bild.isGrayscale()))
					*gray = true;
				else
					*gray = false;
			}
			Bild = Bild.convertDepth(32);
		}
	}
	return Bild;
}

#ifdef HAVE_CMS
QImage LoadPictCol(QString fn, QString Prof, bool UseEmbedded, bool *realCMYK)
{
	QString tmp, dummy, cmd1, cmd2, BBox, tmp2;
	QChar tc;
	QImage Bild;
	double x, y, b, h;
	bool found = false;
	int ret = -1;
	QString tmpFile = QDir::convertSeparators(QDir::homeDirPath()+"/.scribus/sc.png");
	QFileInfo fi = QFileInfo(fn);
	QString ext = fi.extension(false).lower();
	if (ext == "pdf")
	{
		QStringList args;
		args.append("-r72");
		args.append("-sOutputFile="+tmpFile);
		args.append("-dFirstPage=1");
		args.append("-dLastPage=1");
		args.append(fn);
		ret = callGS(args);
		if (ret == 0)
		{
			QImage image;
			image.load(tmpFile);
  			Bild = image.convertDepth(32);
			unlink(tmpFile);
			*realCMYK = false;
		}
		}
		if ((ext == "eps") || (ext == "ps"))
		{
			QFile f(fn);
			if (f.open(IO_ReadOnly))
			{
				QTextStream ts(&f);
				while (!ts.atEnd())
				{
					tc = ' ';
					tmp = "";
					while ((tc != '\n') && (tc != '\r'))
					{
						ts >> tc;
						if ((tc != '\n') && (tc != '\r'))
							tmp += tc;
					}
					if (tmp.startsWith("%%BoundingBox:"))
					{
						found = true;
						BBox = tmp.remove("%%BoundingBox:");
					}
					if (!found)
					{
						if (tmp.startsWith("%%BoundingBox"))
						{
							found = true;
							BBox = tmp.remove("%%BoundingBox");
						}
					}
					if (tmp.startsWith("%%EndComments"))
						break;
				}
				f.close();
				if (found)
				{
					QTextStream ts2(&BBox, IO_ReadOnly);
					ts2 >> x >> y >> b >> h;
					QStringList args;
					args.append("-r72");
					args.append("-sOutputFile="+tmpFile);
					args.append("-g"+tmp.setNum(qRound(b))+"x"+tmp2.setNum(qRound(h)));
					args.append(fn);
					ret = callGS(args);
					if (ret == 0)
					{
						QImage image;
						image.load(tmpFile);
					  	image = image.convertDepth(32);
						image.setAlphaBuffer(true);
						if (ScApp->HavePngAlpha != 0)
						{
							int wi = image.width();
							int hi = image.height();
						    for( int yi=0; yi < hi; ++yi )
							{
								QRgb *s = (QRgb*)(image.scanLine( yi ));
								for(int xi=0; xi < wi; ++xi )
								{
									if((*s) == 0xffffffff)
										(*s) &= 0x00ffffff;
									s++;
								}
							}
					    }
						Bild = image.copy(static_cast<int>(x), 0, static_cast<int>(b-x), static_cast<int>(h-y));
						unlink(tmpFile);
						*realCMYK = false;
					}
				}
			}
		}
#ifdef HAVE_TIFF
		if (ext == "tif")
		{
			QImage img;
			QImage inI2;
			TIFF* tif = TIFFOpen(fn, "r");
			if(tif)
			{
    			DWORD EmbedLen = 0;
    			LPBYTE EmbedBuffer;
				unsigned width, height,size;
				TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
				TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
				size=width*height;
				uint32 *bits=(uint32*) _TIFFmalloc(size * sizeof (uint32));
				if(bits)
				{
					if (TIFFReadRGBAImage(tif, width, height, bits, 0))
					{
    			    	img.create(width,height,32);
				img.setAlphaBuffer(true);
						if(TIFFGetR(0x1234567)==qRed  (0x1234567) &&
							 TIFFGetG(0x1234567)==qGreen(0x1234567) &&
							 TIFFGetB(0x1234567)==qBlue (0x1234567))
						{
							for(unsigned y=0; y<height; ++y)
								memcpy(img.scanLine(height-1-y),bits+y*width,width*4);
						}
						else
						{
							uint32 *inp=bits;
							for(unsigned y=0; y<height; ++y)
							{
								QRgb *row=(QRgb*) (img.scanLine(height-1-y));
								for(unsigned x=0; x<width; ++x)
								{
									const uint32 col=*(inp++);
									row[x]=qRgba(TIFFGetR(col), TIFFGetG(col), TIFFGetB(col), TIFFGetA(col));
								}
							}
						}
						Bild = img.copy();
					}
					_TIFFfree(bits);
					cmsHTRANSFORM xform;
					cmsHPROFILE inputProf;
					if((TIFFGetField(tif, TIFFTAG_ICCPROFILE, &EmbedLen, &EmbedBuffer)) && (UseEmbedded))
					{
						inputProf = cmsOpenProfileFromMem(EmbedBuffer, EmbedLen);
						if (static_cast<int>(cmsGetColorSpace(inputProf)) == icSigRgbData)
						{
							switch (static_cast<int>(cmsGetColorSpace(CMSprinterProf)))
							{
								case icSigRgbData:
										*realCMYK = false;
										xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_RGBA_8, IntentPrinter, 0);
										break;
								case icSigCmykData:
										*realCMYK = true;
										xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_CMYK_8, IntentPrinter, 0);
									break;
								default:
										*realCMYK = false;
										xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_RGBA_8, IntentPrinter, 0);
										break;
							}
							for (int i=0; i < Bild.height(); ++i)
							{
								LPBYTE ptr = Bild.scanLine(i);
								cmsDoTransform(xform, ptr, ptr, Bild.width());
							}
						}
					}
					else
					{
						inputProf = cmsOpenProfileFromFile(InputProfiles[Prof], "r");
						switch (static_cast<int>(cmsGetColorSpace(CMSprinterProf)))
						{
							case icSigRgbData:
										*realCMYK = false;
										xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_RGBA_8, IntentPrinter, 0);
										break;
							case icSigCmykData:
										*realCMYK = true;
										xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_CMYK_8, IntentPrinter, 0);
										break;
							default:
										*realCMYK = false;
										xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_RGBA_8, IntentPrinter, 0);
										break;
						}
						for (int i=0; i < Bild.height(); ++i)
						{
							LPBYTE ptr = Bild.scanLine(i);
							cmsDoTransform(xform, ptr, ptr, Bild.width());
						}
					}
					cmsDeleteTransform(xform);
					cmsCloseProfile(inputProf);
				}
				TIFFClose(tif);
			}
		}
#endif
	else
	{
		cmsHTRANSFORM xform;
		cmsHPROFILE inputProf;
		Bild.load(fn);
  		Bild = Bild.convertDepth(32);
		inputProf = cmsOpenProfileFromFile(InputProfiles[Prof], "r");
		switch (static_cast<int>(cmsGetColorSpace(CMSprinterProf)))
		{
			case icSigRgbData:
				*realCMYK = false;
				xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_RGBA_8, IntentPrinter, 0);
				break;
			case icSigCmykData:
				*realCMYK = true;
				xform = cmsCreateTransform(inputProf, TYPE_RGBA_8, CMSprinterProf, TYPE_CMYK_8, IntentPrinter, 0);
				break;
		}
		for (int i=0; i < Bild.height(); ++i)
		{
			LPBYTE ptr = Bild.scanLine(i);
			cmsDoTransform(xform, ptr, ptr, Bild.width());
		}
		cmsDeleteTransform(xform);
		cmsCloseProfile(inputProf);
	}
	return Bild;
}
#endif

QString GetAttr(QDomElement *el, QString at, QString def)
{
	return el->attribute(at, def);
}

int QStoInt(QString in)
{
	bool ok = false;
	int c = in.toInt(&ok);
	return ok ? c : 0;
}

double QStodouble(QString in)
{
	bool ok = false;
	double c = in.toDouble(&ok);
	return ok ? c : 0.0;
}

QPixmap loadIcon(QString nam)
{
	QString pfad = ICONDIR;
	pfad += nam;
	QPixmap pm;
	pm.load(pfad);
	return pm;
}

uint getDouble(QString in, bool raw)
{
	QByteArray bb(4);
	if (raw)
	{
		bb[3] = static_cast<uchar>(QChar(in.at(0)));
		bb[2] = static_cast<uchar>(QChar(in.at(1)));
		bb[1] = static_cast<uchar>(QChar(in.at(2)));
		bb[0] = static_cast<uchar>(QChar(in.at(3)));
	}
	else
	{
		bb[0] = static_cast<uchar>(QChar(in.at(0)));
		bb[1] = static_cast<uchar>(QChar(in.at(1)));
		bb[2] = static_cast<uchar>(QChar(in.at(2)));
		bb[3] = static_cast<uchar>(QChar(in.at(3)));
	}
	uint ret;
	ret = bb[0] & 0xff;
	ret |= (bb[1] << 8) & 0xff00;
	ret |= (bb[2] << 16) & 0xff0000;
	ret |= (bb[3] << 24) & 0xff000000;
	return ret;
}

bool loadText(QString filename, QString *Buffer)
{
	QFile f(filename);
	QFileInfo fi(f);
	if (!fi.exists())
		return false;
	bool ret;
	QByteArray bb(f.size());
	if (f.open(IO_ReadOnly))
	{
		f.readBlock(bb.data(), f.size());
		f.close();
		for (uint posi = 0; posi < bb.size(); ++posi)
			*Buffer += bb[posi];
		ret = true;
	}
	else
		ret = false;
	return ret;
}

double Cwidth(ScribusDoc *currentDoc, QString name, QString ch, int Size, QString ch2)
{
	double width;
	FT_Vector  delta;
	uint c1 = ch.at(0).unicode();
	uint c2 = ch2.at(0).unicode();
	Foi* fo = (*currentDoc->AllFonts)[name];
	if (fo->CharWidth.contains(c1))
	{
		width = fo->CharWidth[c1]*(Size / 10.0);
		if (fo->HasKern)
		{
			uint cl = FT_Get_Char_Index(currentDoc->FFonts[name], c1);
			uint cr = FT_Get_Char_Index(currentDoc->FFonts[name], c2);
			FT_Get_Kerning(currentDoc->FFonts[name], cl, cr, ft_kerning_unscaled, &delta);
			width += delta.x / fo->uniEM * (Size / 10.0);
		}
		return width;
	}
	else
		return static_cast<double>(Size / 10.0);
}

double RealCWidth(ScribusDoc *currentDoc, QString name, QString ch, int Size)
{
	double w, ww;
	uint c1 = ch.at(0).unicode();
	Foi* fo = (*currentDoc->AllFonts)[name];
	if (fo->CharWidth.contains(c1))
	{
		uint cl = FT_Get_Char_Index(currentDoc->FFonts[name], c1);
		FT_Load_Glyph( currentDoc->FFonts[name], cl, FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP );
		w = (currentDoc->FFonts[name]->glyph->metrics.width + fabs((double)currentDoc->FFonts[name]->glyph->metrics.horiBearingX)) / fo->uniEM * (Size / 10.0);
		ww = currentDoc->FFonts[name]->glyph->metrics.horiAdvance / fo->uniEM * (Size / 10.0);
		return QMAX(ww, w);
	}
	else
		return static_cast<double>(Size / 10.0);
}

QPointArray RegularPolygon(double w, double h, uint c, bool star, double factor, double rota)
{
	uint cx = star ? c * 2 : c;
	double seg = 360.0 / cx;
	double sc = rota + 180.0;
	double di = factor;
	int mx = 0;
	int my = 0;
	QPointArray pts = QPointArray();
	for (uint x = 0; x < cx; ++x)
	{
		sc = seg * x + 180.0 + rota;
		if (star)
		{
			double wf = x % 2 == 0 ? w / 2 : w / 2 * di;
			double hf = x % 2 == 0 ? h / 2 : h / 2 * di;
			mx = qRound(sin(sc / 180 * M_PI) * (wf) + (w/2));
			my = qRound(cos(sc / 180 * M_PI) * (hf) + (h/2));
		}
		else
		{
			mx = qRound(sin(sc / 180 * M_PI) * (w/2) + (w/2));
			my = qRound(cos(sc / 180 * M_PI) * (h/2) + (h/2));
		}
		pts.resize(x+1);
		pts.setPoint(x, mx, my);
	}
	return pts;
}

FPointArray RegularPolygonF(double w, double h, uint c, bool star, double factor, double rota)
{
	uint cx = star ? c * 2 : c;
	double seg = 360.0 / cx;
	double sc = rota + 180.0;
	double di = factor;
	double mx = 0;
	double my = 0;
	FPointArray pts = FPointArray();
	for (uint x = 0; x < cx; ++x)
	{
		sc = seg * x + 180.0 + rota;
		if (star)
		{
			double wf = x % 2 == 0 ? w / 2 : w / 2 * di;
			double hf = x % 2 == 0 ? h / 2 : h / 2 * di;
			mx = qRound(sin(sc / 180 * M_PI) * (wf) + (w/2));
			my = qRound(cos(sc / 180 * M_PI) * (hf) + (h/2));
		}
		else
		{
			mx = sin(sc / 180 * M_PI) * (w/2) + (w/2);
			my = cos(sc / 180 * M_PI) * (h/2) + (h/2);
		}
		pts.resize(x+1);
		pts.setPoint(x, mx, my);
	}
	return pts;
}

QPointArray FlattenPath(FPointArray ina, QValueList<uint> &Segs)
{
	QPointArray Bez(4);
	QPointArray outa, cli;
	Segs.clear();
	if (ina.size() > 3)
	{
		for (uint poi=0; poi<ina.size()-3; poi += 4)
		{
			if (ina.point(poi).x() > 900000)
			{
				outa.resize(outa.size()+1);
				outa.setPoint(outa.size()-1, cli.point(cli.size()-1));
				Segs.append(outa.size());
				continue;
			}
			BezierPoints(&Bez, ina.pointQ(poi), ina.pointQ(poi+1), ina.pointQ(poi+3), ina.pointQ(poi+2));
			cli = Bez.cubicBezier();
			outa.putPoints(outa.size(), cli.size()-1, cli);
		}
		outa.resize(outa.size()+1);
		outa.setPoint(outa.size()-1, cli.point(cli.size()-1));
	}
	return outa;
}

double xy2Deg(double x, double y)
{
	return (atan2(y,x)*(180.0/M_PI));
}

void BezierPoints(QPointArray *ar, QPoint n1, QPoint n2, QPoint n3, QPoint n4)
{
	ar->setPoint(0, n1);
	ar->setPoint(1, n2);
	ar->setPoint(2, n3);
	ar->setPoint(3, n4);
	return;
}

void Level2Layer(ScribusDoc *currentDoc, struct Layer *ll, int Level)
{
	for (uint la2 = 0; la2 < currentDoc->Layers.count(); ++la2)
	{
		if (currentDoc->Layers[la2].Level == Level)
		{
			ll->isViewable = currentDoc->Layers[la2].isViewable;
			ll->isPrintable = currentDoc->Layers[la2].isPrintable;
			ll->LNr = currentDoc->Layers[la2].LNr;
			break;
		}
	}
}

QString ImageToTxt(QImage *im)
{
	int h = im->height();
	int w = im->width();
	QString ImgStr = "";
	for( int yi=0; yi < h; ++yi )
	{
		QRgb * s = (QRgb*)(im->scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			QRgb r=*s++;
			unsigned char u=qRed(r);
			ImgStr += u;
			u=qGreen(r);
			ImgStr += u;
			u=qBlue(r);
			ImgStr += u;
		}
	}
	return ImgStr;
}

QString ImageToCMYK(QImage *im)
{
	int h = im->height();
	int w = im->width();
	QString ImgStr = "";
	for( int yi=0; yi < h; ++yi )
	{
		QRgb * s = (QRgb*)(im->scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			QRgb r=*s;
			int c = 255 - qRed(r);
			int m = 255 - qGreen(r);
			int y = 255 - qBlue(r);
			int k = QMIN(QMIN(c, m), y);
			*s = qRgba(m - k, y - k, k, c - k);
			ImgStr += c - k;
			ImgStr += m - k;
			ImgStr += y - k;
			ImgStr += k;
			s++;
		}
	}
	return ImgStr;
}

QString ImageToCMYK_PS(QImage *im, int pl, bool pre)
{
	int h = im->height();
	int w = im->width();
	QString ImgStr = "";
	if (pre)
	{
		for( int yi=0; yi < h; ++yi )
		{
			QRgb * s = (QRgb*)(im->scanLine( yi ));
			for( int xi=0; xi < w; ++xi )
			{
				QRgb r=*s++;
				int c = qRed(r);
				int m = qGreen(r);
				int y = qBlue(r);
				int k = qAlpha(r);
				if (pl == -1)
				{
					ImgStr += c;
					ImgStr += m;
					ImgStr += y;
					ImgStr += k;
				}
				else
				{
					if (pl == -2)
						ImgStr += QMIN(255, qRound(0.3 * c + 0.59 * m + 0.11 * y + k));
					if (pl == 1)
						ImgStr += c;
					if (pl == 2)
						ImgStr += m;
					if (pl == 3)
						ImgStr += y;
					if (pl == 0)
						ImgStr += k;
				}
			}
		}
	}
	else
	{
		for( int yi=0; yi < h; ++yi )
		{
			QRgb * s = (QRgb*)(im->scanLine( yi ));
			for( int xi=0; xi < w; ++xi )
			{
				QRgb r=*s++;
				int c = 255 - qRed(r);
				int m = 255 - qGreen(r);
				int y = 255 - qBlue(r);
				int k = QMIN(QMIN(c, m), y);
				if (pl == -1)
				{
					ImgStr += c - k;
					ImgStr += m - k;
					ImgStr += y - k;
					ImgStr += k;
				}
				else
				{
					if (pl == -2)
						ImgStr += QMIN(255, qRound(0.3 * c + 0.59 * m + 0.11 * y + k));
					if (pl == 1)
						ImgStr += c - k;
					if (pl == 2)
						ImgStr += m - k;
					if (pl == 3)
						ImgStr += y - k;
					if (pl == 0)
						ImgStr += k;
				}
			}
		}
	}
	return ImgStr;
}

QString MaskToTxt(QImage *im, bool PDF)
{
	int h = im->height();
	int w = im->width();
	int w2;
	w2 = w / 8;
	if ((w % 8) != 0)
  		w2++;
	QString ImgStr = "";
	for( int yi=0; yi < h; ++yi )
	{
		uchar * s = im->scanLine( yi );
		for( int xi=0; xi < w2; ++xi )
		{
			unsigned char u = *(s+xi);
			ImgStr += PDF ? ~u : u;
		}
	}
	return ImgStr;
}

QString MaskToTxt14(QImage *im)
{
	int h = im->height();
	int w = im->width();
	QString ImgStr = "";
	for( int yi=0; yi < h; ++yi )
	{
		QRgb * s = (QRgb*)(im->scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			QRgb r=*s++;
			unsigned char u=qAlpha(r);
			ImgStr += u;
		}
	}
	return ImgStr;
}

typedef struct my_error_mgr
{
  struct jpeg_error_mgr pub;            /* "public" fields */
  jmp_buf setjmp_buffer;  /* for return to caller */
} *my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

static void my_error_exit (j_common_ptr cinfo)
{
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  (*cinfo->err->output_message) (cinfo);
  longjmp (myerr->setjmp_buffer, 1);
}

void Convert2JPG(QString fn, QImage *image, int Quality, bool isCMYK)
{
	struct jpeg_compress_struct cinfo;
	struct my_error_mgr         jerr;
	FILE     *outfile;
	JSAMPROW row_pointer[1];
	row_pointer[0] = 0;
	cinfo.err = jpeg_std_error (&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	outfile = NULL;
	if (setjmp (jerr.setjmp_buffer))
	{
		jpeg_destroy_compress (&cinfo);
		if (outfile)
			fclose (outfile);
		return;
	}
	jpeg_create_compress (&cinfo);
	if ((outfile = fopen (fn, "wb")) == NULL)
		return;
	jpeg_stdio_dest (&cinfo, outfile);
	cinfo.image_width  = image->width();
	cinfo.image_height = image->height();
	if (isCMYK)
	{
		cinfo.in_color_space = JCS_CMYK;
		cinfo.input_components = 4;
	}
	else
	{
		cinfo.in_color_space = JCS_RGB;
		cinfo.input_components = 3;
	}
	jpeg_set_defaults (&cinfo);
	int qual[] = { 95, 85, 75, 50, 25 };  // These are the JPEG Quality settings 100 means best, 0 .. don't discuss
	jpeg_set_quality (&cinfo, qual[Quality], true);
	jpeg_start_compress (&cinfo, TRUE);
	row_pointer[0] = new uchar[cinfo.image_width*cinfo.input_components];
	int w = cinfo.image_width;
	while (cinfo.next_scanline < cinfo.image_height)
	{
		uchar *row = row_pointer[0];
		if (isCMYK)
		{
			QRgb* rgba = (QRgb*)image->scanLine(cinfo.next_scanline);
			for (int i=0; i<w; ++i)
			{
	 			*row++ = qAlpha(*rgba);
	 			*row++ = qRed(*rgba);
	 			*row++ = qGreen(*rgba);
	 			*row++ = qBlue(*rgba);
	 			++rgba;
			}
		}
		else
		{
			QRgb* rgb = (QRgb*)image->scanLine(cinfo.next_scanline);
			for (int i=0; i<w; i++)
			{
	 			*row++ = qRed(*rgb);
	 			*row++ = qGreen(*rgb);
	 			*row++ = qBlue(*rgb);
	 			++rgb;
			}
		}
		jpeg_write_scanlines (&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress (&cinfo);
	fclose (outfile);
	jpeg_destroy_compress (&cinfo);
	delete [] row_pointer[0];
}

QString CompressStr(QString *in)
{
	QString out = "";
#ifdef HAVE_LIBZ
	QByteArray bb(in->length());
	for (uint ax = 0; ax < in->length(); ++ax)
		bb[ax] = uchar(QChar(in->at(ax)));
	uLong exlen = uint(bb.size() * 0.001 + 16) + bb.size();
	QByteArray bc(exlen);
	compress2((Byte *)bc.data(), &exlen, (Byte *)bb.data(), uLong(bb.size()), 9);
	for (uint cl = 0; cl < exlen; ++cl)
		out += bc[cl];
#else
	out = *in;
#endif
	return out;
}

char *toHex( uchar u )
{
    static char hexVal[3];
    int i = 1;
    while ( i >= 0 )
	{
		ushort hex = (u & 0x000f);
		if ( hex < 0x0a )
	    	hexVal[i] = '0'+hex;
		else
	    	hexVal[i] = 'A'+(hex-0x0a);
		u = u >> 4;
			i--;
    }
    hexVal[2] = '\0';
    return hexVal;
}

QString String2Hex(QString *in, bool lang)
{
	int i = 0;
	QString out = "";
	for( uint xi = 0; xi < in->length(); ++xi )
	{
		out += toHex(uchar(QChar(in->at(xi))));
		++i;
		if ((i>40) && (lang))
		{
			out += '\n';
			i=0;
		}
	}
	return out;
}

QByteArray ComputeMD5Sum(QByteArray *in)
{
	QByteArray MDsum(16);
	md5_buffer (in->data(), in->size(), reinterpret_cast<void*>(MDsum.data()));
	return MDsum;
}

QString Path2Relative(QString Path)
{
	QString	Ndir = "";
	QStringList Pdir = QStringList::split("/", QDir::currentDirPath());
	QFileInfo Bfi = QFileInfo(Path);
	QStringList Bdir = QStringList::split("/", Bfi.dirPath(true));
	bool end = true;
	uint dcoun = 0;
	uint dcoun2 = 0;
	while (end)
	{
		if (Pdir[dcoun] == Bdir[dcoun])
			dcoun++;
		else
			break;
		if (dcoun > Pdir.count())
			break;
	}
	dcoun2 = dcoun;
	for (uint ddx2 = dcoun; ddx2 < Pdir.count(); ddx2++)
		Ndir += "../";
	for (uint ddx = dcoun2; ddx < Bdir.count(); ddx++)
		Ndir += Bdir[ddx]+"/";
	Ndir += Bfi.fileName();
	return Ndir;
}

int setBestEncoding(FT_Face face)
{
	FT_ULong  charcode;
	FT_UInt   gindex;
	bool foundEncoding = false;
	int countUniCode = 0;
	int chmapUniCode = 0;
	int chmapCustom = 0;
	int retVal = 0;
	FT_CharMap defaultEncoding = face->charmap;
	for(int u = 0; u < face->num_charmaps; u++)
	{
		if (face->charmaps[u]->encoding == FT_ENCODING_UNICODE )
		{
			FT_Set_Charmap(face, face->charmaps[u]);
			chmapUniCode = u;
			gindex = 0;
			charcode = FT_Get_First_Char( face, &gindex );
			while ( gindex != 0 )
			{
				countUniCode++;
				charcode = FT_Get_Next_Char( face, charcode, &gindex );
			}
		}
		if (face->charmaps[u]->encoding == FT_ENCODING_ADOBE_CUSTOM)
		{
			chmapCustom = u;
			foundEncoding = true;
			retVal = 1;
			break;
		}
		else if (face->charmaps[u]->encoding == FT_ENCODING_MS_SYMBOL)
		{
			chmapCustom = u;
			foundEncoding = true;
			retVal = 2;
			break;
		}
	}
	if (countUniCode > 255)
	{
		FT_Set_Charmap(face, face->charmaps[chmapUniCode]);
		retVal = 0;
	}
	else if (foundEncoding)
		FT_Set_Charmap(face, face->charmaps[chmapCustom]);
	else
	{
		FT_Set_Charmap(face, defaultEncoding);
		retVal = 0;
	}
	return retVal;
}

bool GlyNames(QMap<uint, QString> *GList, QString Dat)
{
	bool error;
	char *buf[50];
	FT_Library library;
	FT_Face face;
	FT_ULong  charcode;
	FT_UInt gindex;
	error = FT_Init_FreeType(&library);
	error = FT_New_Face(library, Dat, 0, &face);
	setBestEncoding(face);
	gindex = 0;
	charcode = FT_Get_First_Char(face, &gindex );
	while (gindex != 0)
	{
		FT_Get_Glyph_Name(face, gindex, buf, 50);
		GList->insert(charcode, QString(reinterpret_cast<char*>(buf)));
    	charcode = FT_Get_Next_Char(face, charcode, &gindex );
	}
	FT_Done_FreeType( library );
	return true;
}

bool GlyIndex(QMap<uint, PDFlib::GlNamInd> *GListInd, QString Dat)
{
	struct PDFlib::GlNamInd gln;
	bool error;
	char *buf[50];
	FT_Library library;
	FT_Face face;
	FT_ULong  charcode;
	FT_UInt   gindex;
	uint counter1 = 32;
	uint counter2 = 0;
	error = FT_Init_FreeType(&library);
	error = FT_New_Face(library, Dat, 0, &face);
	setBestEncoding(face);
	gindex = 0;
	charcode = FT_Get_First_Char(face, &gindex );
	while (gindex != 0)
	{
		FT_Get_Glyph_Name(face, gindex, buf, 50);
		gln.Code = counter1 + counter2;
		gln.Name = "/"+QString(reinterpret_cast<char*>(buf));
		GListInd->insert(charcode, gln);
    	charcode = FT_Get_Next_Char(face, charcode, &gindex );
    	counter1++;
    	if (counter1 > 255)
		{
			counter1 = 32;
			counter2 += 0x100;
		}
	}
	FT_Done_FreeType( library );
	return true;
}

FPoint firstP;
bool FirstM;

int traceMoveto( FT_Vector *to, FPointArray *composite )
{
	double tox = ( to->x / 64.0 );
	double toy = ( to->y / 64.0 );
	if (!FirstM)
	{
		composite->addPoint(firstP);
		composite->addPoint(firstP);
		composite->setMarker();
	}
	else
		FirstM = false;
	composite->addPoint(FPoint(tox, toy));
	composite->addPoint(FPoint(tox, toy));
	firstP = FPoint(tox, toy);
	return 0;
}

int traceLineto( FT_Vector *to, FPointArray *composite )
{
	double tox = ( to->x / 64.0 );
	double toy = ( to->y / 64.0 );
	if (composite->size() > 4)
	{
		FPoint b1 = composite->point(composite->size()-4);
		FPoint b2 = composite->point(composite->size()-3);
		FPoint b3 = composite->point(composite->size()-2);
		FPoint b4 = composite->point(composite->size()-1);
		FPoint n1 = FPoint(tox, toy);
		FPoint n2 = FPoint(tox, toy);
		FPoint n3 = FPoint(tox, toy);
		FPoint n4 = FPoint(tox, toy);
		if ((b1 == n1) && (b2 == n2) && (b3 == n3) && (b4 == n4))
			return 0;
	}
	composite->addPoint(FPoint(tox, toy));
	composite->addPoint(FPoint(tox, toy));
	composite->addPoint(FPoint(tox, toy));
	composite->addPoint(FPoint(tox, toy));
	return 0;
}

int traceQuadraticBezier( FT_Vector *control, FT_Vector *to, FPointArray *composite )
{
	double x1 = ( control->x / 64.0 );
	double y1 = ( control->y / 64.0 );
	double x2 = ( to->x / 64.0 );
	double y2 = ( to->y / 64.0 );
	if (composite->size() > 4)
	{
		FPoint b1 = composite->point(composite->size()-4);
		FPoint b2 = composite->point(composite->size()-3);
		FPoint b3 = composite->point(composite->size()-2);
		FPoint b4 = composite->point(composite->size()-1);
		FPoint n1 = FPoint(x2, y2);
		FPoint n2 = FPoint(x1, y1);
		FPoint n3 = FPoint(x2, y2);
		FPoint n4 = FPoint(x2, y2);
		if ((b1 == n1) && (b2 == n2) && (b3 == n3) && (b4 == n4))
			return 0;
	}
	composite->addPoint(FPoint(x2, y2));
	composite->addPoint(FPoint(x1, y1));
	composite->addPoint(FPoint(x2, y2));
	composite->addPoint(FPoint(x2, y2));
	return 0;
}

int traceCubicBezier( FT_Vector *p, FT_Vector *q, FT_Vector *to, FPointArray *composite )
{
	double x1 = ( p->x / 64.0 );
	double y1 = ( p->y / 64.0 );
	double x2 = ( q->x / 64.0 );
	double y2 = ( q->y / 64.0 );
	double x3 = ( to->x / 64.0 );
	double y3 = ( to->y / 64.0 );
	if (composite->size() > 4)
	{
		FPoint b1 = composite->point(composite->size()-4);
		FPoint b2 = composite->point(composite->size()-3);
		FPoint b3 = composite->point(composite->size()-2);
		FPoint b4 = composite->point(composite->size()-1);
		FPoint n1 = FPoint(x3, y3);
		FPoint n2 = FPoint(x2, y2);
		FPoint n3 = FPoint(x3, y3);
		FPoint n4 = FPoint(x3, y3);
		if ((b1 == n1) && (b2 == n2) && (b3 == n3) && (b4 == n4))
			return 0;
	}
	composite->setPoint(composite->size()-1, FPoint(x1, y1));
	composite->addPoint(FPoint(x3, y3));
	composite->addPoint(FPoint(x2, y2));
	composite->addPoint(FPoint(x3, y3));
	composite->addPoint(FPoint(x3, y3));
	return 0;
}

FT_Outline_Funcs OutlineMethods =
{
	(FT_Outline_MoveTo_Func) traceMoveto,
	(FT_Outline_LineTo_Func) traceLineto,
	(FT_Outline_ConicTo_Func) traceQuadraticBezier,
	(FT_Outline_CubicTo_Func) traceCubicBezier,
	0,
	0
};

FPointArray traceChar(FT_Face face, uint chr, int chs, double *x, double *y, bool *err)
{
	bool error = false;
	FT_UInt glyphIndex;
	FPointArray pts, pts2;
	pts.resize(0);
	pts2.resize(0);
	firstP = FPoint(0,0);
	FirstM = true;
	error = FT_Set_Char_Size( face, 0, chs*64, 72, 72 );
	if (error)
	{
		*err = error;
		return pts2;
	}
	glyphIndex = FT_Get_Char_Index(face, chr);
	if (glyphIndex == 0)
	{
		*err = true;
		return pts2;
	}
	error = FT_Load_Glyph( face, glyphIndex, FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP );
	if (error)
	{
		*err = error;
		return pts2;
	}
	error = FT_Outline_Decompose(&face->glyph->outline, &OutlineMethods, reinterpret_cast<void*>(&pts));
	if (error)
	{
		*err = error;
		return pts2;
	}
	*x = face->glyph->metrics.horiBearingX / 64.0;
	*y = face->glyph->metrics.horiBearingY / 64.0;
	QWMatrix ma;
	ma.scale(1, -1);
	pts.map(ma);
	pts.translate(0, chs);
	pts2.putPoints(0, pts.size()-2, pts, 0);
	return pts2;
}

FPoint getMaxClipF(FPointArray* Clip)
{
	FPoint np, rp;
	double mx = 0;
	double my = 0;
	for (uint c = 0; c < Clip->size(); ++c)
	{
		np = Clip->point(c);
		if (np.x() > 900000)
			continue;
		if (np.x() > mx)
			mx = np.x();
		if (np.y() > my)
			my = np.y();
	}
	rp = FPoint(mx, my);
	return rp;
}

FPoint getMinClipF(FPointArray* Clip)
{
	FPoint np, rp;
	double mx = 99999;
	double my = 99999;
	for (uint c = 0; c < Clip->size(); ++c)
	{
		np = Clip->point(c);
		if (np.x() > 900000)
			continue;
		if (np.x() < mx)
			mx = np.x();
		if (np.y() < my)
			my = np.y();
	}
	rp = FPoint(mx, my);
	return rp;
}

QPixmap FontSample(QString da, int s, QString ts, QColor back, bool force)
{
	FT_Face face;
	FT_Library library;
	double x, y, ymax;
	bool error;
	int  pen_x;
	FPoint gp;
	error = FT_Init_FreeType( &library );
	error = FT_New_Face( library, da, 0, &face );
	int encode = setBestEncoding(face);
	double uniEM = static_cast<double>(face->units_per_EM);
	int h = qRound(face->height / uniEM) * s + 1;
	double a = static_cast<double>(face->descender) / uniEM * s + 1;
	int w = qRound((face->bbox.xMax - face->bbox.xMin) / uniEM) * s * (ts.length()+1);
	QPixmap pm(w, h);
	pm.fill();
	pen_x = 0;
	ymax = 0.0;
	ScPainter *p = new ScPainter(&pm, pm.width(), pm.height());
	p->setFillMode(1);
	p->setLineWidth(0.0);
	p->setBrush(back);
	p->drawRect(0.0, 0.0, static_cast<double>(w), static_cast<double>(h));
	p->setBrush(Qt::black);
	FPointArray gly;
	uint dv;
	dv = ts[0].unicode();
	error = false;
	gly = traceChar(face, dv, s, &x, &y, &error);
	if (((encode != 0) || (error)) && (!force))
	{
		error = false;
		FT_ULong  charcode;
		FT_UInt gindex;
		gindex = 0;
		charcode = FT_Get_First_Char(face, &gindex );
		for (uint n = 0; n < ts.length(); ++n)
		{
			gly = traceChar(face, charcode, s, &x, &y, &error);
			if (error)
				break;
			if (gly.size() > 3)
			{
				gly.translate(static_cast<double>(pen_x) / 64.0, a);
				gp = getMaxClipF(&gly);
				ymax = QMAX(ymax, gp.y());
				p->setupPolygon(&gly);
				p->fillPath();
			}
			pen_x += face->glyph->advance.x;
			charcode = FT_Get_Next_Char(face, charcode, &gindex );
			if (gindex == 0)
				break;
		}
	}
	else
	{
		for (uint n = 0; n < ts.length(); ++n)
		{
			dv = ts[n].unicode();
			error = false;
			gly = traceChar(face, dv, s, &x, &y, &error);
			if (gly.size() > 3)
			{
				gly.translate(static_cast<double>(pen_x) / 64.0, a);
				gp = getMaxClipF(&gly);
				ymax = QMAX(ymax, gp.y());
				p->setupPolygon(&gly);
				p->fillPath();
			}
			pen_x += face->glyph->advance.x;
		}
	}
	p->end();
	pm.resize(QMIN(qRound(gp.x()), w), QMIN(qRound(ymax), h));
	delete p;
	FT_Done_FreeType( library );
	return pm;
}
 
/** Same as FontSample() with \n strings support added.
09/26/2004 petr vanek
*/
QPixmap fontSamples(QString da, int s, QString ts, QColor back)
{
	QStringList lines = QStringList::split("\n", ts);
	QPixmap ret(640, 480);
	QPixmap sample;
	QPainter *painter = new QPainter(&ret);
	int y = 0;
	int x = 0;
	ret.fill(back);
	for ( QStringList::Iterator it = lines.begin(); it != lines.end(); ++it ) {
		sample = FontSample(da, s, *it, back);
		if (!sample.isNull())
			painter->drawPixmap(0, y, sample, 0, 0);
		y = y + sample.height();
		if (x < sample.width())
			x = sample.width();
	} // for
	delete(painter);
	QPixmap final(x, y);
	if ((x != 0) && (y != 0))
	{
		QPainter *fpainter = new QPainter(&final);
		fpainter->drawPixmap(0, 0, ret, 0, 0, x, y);
		delete(fpainter);
	}
	return final;
}

/***************************************************************************
    begin                : Wed Oct 29 2003
    copyright            : (C) 2003 The Scribus Team
    email                : paul@all-the-johnsons.co.uk
 ***************************************************************************/
// check if the file exists, if it does, ask if they're sure
// return true if they're sure, else return false;

bool overwrite(QWidget *parent, QString filename)
{
	bool retval = true;
	QFileInfo fi(filename);
	if (fi.exists())
  	{
    	int t = QMessageBox::warning(parent, QObject::tr("Warning"),
  						QObject::tr("Do you really want to overwrite the File:\n%1 ?").arg(filename),
                        QMessageBox::No, QMessageBox::Yes, QMessageBox::NoButton);
	    if (t == QMessageBox::No)
			retval = false;
  	}
  return retval;
}

void CopyPageItem(struct CopyPasteBuffer *Buffer, PageItem *b)
{
	uint a;
	Buffer->PType = b->PType;
	Buffer->Xpos = b->Xpos;
	Buffer->Ypos = b->Ypos;
	Buffer->Width = b->Width;
	Buffer->Height = b->Height;
	Buffer->RadRect = b->RadRect;
	Buffer->FrameType = b->FrameType;
	Buffer->ClipEdited = b->ClipEdited;
	Buffer->Pwidth = b->Pwidth;
	Buffer->Pcolor = b->Pcolor;
	Buffer->Pcolor2 = b->Pcolor2;
	Buffer->Shade = b->Shade;
	Buffer->Shade2 = b->Shade2;
	Buffer->GrColor = "";
	Buffer->GrColor2 = "";
	Buffer->GrShade = 100;
	Buffer->GrShade2 = 100;
	Buffer->fill_gradient = b->fill_gradient;
	Buffer->GrType = b->GrType;
	Buffer->GrStartX = b->GrStartX;
	Buffer->GrStartY = b->GrStartY;
	Buffer->GrEndX = b->GrEndX;
	Buffer->GrEndY = b->GrEndY;
	Buffer->TxtStroke = b->TxtStroke;
	Buffer->TxtFill = b->TxtFill;
	Buffer->ShTxtStroke = b->ShTxtStroke;
	Buffer->ShTxtFill = b->ShTxtFill;
	Buffer->TxtScale = b->TxtScale;
	Buffer->TxTStyle = b->TxTStyle;
	Buffer->Rot = b->Rot;
	Buffer->PLineArt = b->PLineArt;
	Buffer->PLineEnd = b->PLineEnd;
	Buffer->PLineJoin = b->PLineJoin;
	Buffer->LineSp = b->LineSp;
	Buffer->LocalScX = b->LocalScX;
	Buffer->LocalScY = b->LocalScY;
	Buffer->LocalX = b->LocalX;
	Buffer->LocalY = b->LocalY;
	Buffer->PicArt = b->PicArt;
	Buffer->flippedH = b->flippedH;
	Buffer->flippedV = b->flippedV;
	Buffer->BBoxX = b->BBoxX;
	Buffer->BBoxH = b->BBoxH;
	Buffer->isPrintable = b->isPrintable;
	Buffer->isBookmark = b->isBookmark;
	Buffer->BMnr = b->BMnr;
	Buffer->isAnnotation = b->isAnnotation;
	Buffer->AnType = b->AnType;
	Buffer->AnAction = b->AnAction;
	Buffer->An_E_act = b->An_E_act;
	Buffer->An_X_act = b->An_X_act;
	Buffer->An_D_act = b->An_D_act;
	Buffer->An_Fo_act = b->An_Fo_act;
	Buffer->An_Bl_act = b->An_Bl_act;
	Buffer->An_K_act = b->An_K_act;
	Buffer->An_F_act = b->An_F_act;
	Buffer->An_V_act = b->An_V_act;
	Buffer->An_C_act = b->An_C_act;
	Buffer->An_Extern = b->An_Extern;
	Buffer->AnZiel = b->AnZiel;
	Buffer->AnName = b->AnName;
	Buffer->AnActType = b->AnActType;
	Buffer->AnToolTip = b->AnToolTip;
	Buffer->AnBwid = b->AnBwid;
	Buffer->AnBsty = b->AnBsty;
	Buffer->AnFeed = b->AnFeed;
	Buffer->AnFlag = b->AnFlag;
	Buffer->AnFont = b->AnFont;
	Buffer->AnRollOver = b->AnRollOver;
	Buffer->AnDown = b->AnDown;
	Buffer->AnFormat = b->AnFormat;
	Buffer->AnVis = b->AnVis;
	Buffer->AnMaxChar = b->AnMaxChar;
	Buffer->AnChkStil = b->AnChkStil;
	Buffer->AnIsChk = b->AnIsChk;
	Buffer->AnAAact = b->AnAAact;
	Buffer->AnBColor = b->AnBColor;
	Buffer->AnHTML = b->AnHTML;
	Buffer->AnUseIcons = b->AnUseIcons;
	Buffer->AnIPlace = b->AnIPlace;
	Buffer->AnScaleW = b->AnScaleW;
	Buffer->Extra = b->Extra;
	Buffer->TExtra = b->TExtra;
	Buffer->BExtra = b->BExtra;
	Buffer->RExtra = b->RExtra;
	Buffer->Pfile = b->Pfile;
	Buffer->Pfile2 = b->Pfile2;
	Buffer->Pfile3 = b->Pfile3;
	QString Text = "";
	if (b->itemText.count() != 0)
	{
		for (a=0; a<b->itemText.count(); ++a)
		{
			if( (b->itemText.at(a)->ch == "\n") || (b->itemText.at(a)->ch == "\r"))
				Text += QString(QChar(5))+"\t";
			else if(b->itemText.at(a)->ch == "\t")
				Text += QString(QChar(4))+"\t";
			else
				Text += b->itemText.at(a)->ch+"\t";
			Text += b->itemText.at(a)->cfont+"\t";
			Text += QString::number(b->itemText.at(a)->csize / 10.0)+"\t";
			Text += b->itemText.at(a)->ccolor+"\t";
			Text += QString::number(b->itemText.at(a)->cextra)+"\t";
			Text += QString::number(b->itemText.at(a)->cshade)+'\t';
			Text += QString::number(b->itemText.at(a)->cstyle)+'\t';
			Text += QString::number(b->itemText.at(a)->cab)+'\t';
			Text += b->itemText.at(a)->cstroke+"\t";
			Text += QString::number(b->itemText.at(a)->cshade2)+'\t';
			Text += QString::number(b->itemText.at(a)->cscale)+'\n';
		}
	}
	Buffer->itemText = Text;
	Buffer->Clip = b->Clip.copy();
	Buffer->PoLine = b->PoLine.copy();
	Buffer->ContourLine = b->ContourLine.copy();
	Buffer->UseContour = b->UseContour;
	Buffer->TabValues = b->TabValues;
	Buffer->DashValues = b->DashValues;
	Buffer->DashOffset = b->DashOffset;
	Buffer->PoShow = b->PoShow;
	Buffer->BaseOffs = b->BaseOffs;
	Buffer->Textflow = b->Textflow;
	Buffer->Textflow2 = b->Textflow2;
	Buffer->textAlignment = b->textAlignment;
	Buffer->IFont = b->IFont;
	Buffer->ISize = b->ISize;
	Buffer->ExtraV = b->ExtraV;
	Buffer->Groups = b->Groups;
	Buffer->IProfile = b->IProfile;
	Buffer->IRender = b->IRender;
	Buffer->UseEmbedded = b->UseEmbedded;
	Buffer->EmProfile = b->EmProfile;
	Buffer->LayerNr = b->LayerNr;
	Buffer->ScaleType = b->ScaleType;
	Buffer->AspectRatio = b->AspectRatio;
	Buffer->Locked = b->Locked;
	Buffer->LockRes = b->LockRes;
	Buffer->Transparency = b->Transparency;
	Buffer->TranspStroke = b->TranspStroke;
	Buffer->Reverse = b->Reverse;
	Buffer->InvPict = b->InvPict;
	Buffer->NamedLStyle = b->NamedLStyle;
	Buffer->Language = b->Language;
	Buffer->Cols = b->Cols;
	Buffer->ColGap = b->ColGap;
	Buffer->isTableItem = b->isTableItem;
	Buffer->TopLine = b->TopLine;
	Buffer->LeftLine = b->LeftLine;
	Buffer->RightLine = b->RightLine;
	Buffer->BottomLine = b->BottomLine;
	if (b->isTableItem)
	{
		if (b->TopLink != 0)
			Buffer->TopLinkID = b->TopLink->ItemNr;
		else
			Buffer->TopLinkID = -1;
		if (b->LeftLink != 0)
			Buffer->LeftLinkID = b->LeftLink->ItemNr;
		else
			Buffer->LeftLinkID = -1;
		if (b->RightLink != 0)
			Buffer->RightLinkID = b->RightLink->ItemNr;
		else
			Buffer->RightLinkID = -1;
		if (b->BottomLink != 0)
			Buffer->BottomLinkID = b->BottomLink->ItemNr;
		else
			Buffer->BottomLinkID = -1;
	}
	Buffer->startArrowIndex = b->startArrowIndex;
	Buffer->endArrowIndex = b->endArrowIndex;
}

void WordAndPara(PageItem* b, int *w, int *p, int *c, int *wN, int *pN, int *cN)
{
	QChar Dat = QChar(32);
	int para = 0;
	int ww = 0;
	int cc = 0;
	int paraN = 0;
	int wwN = 0;
	int ccN = 0;
	bool first = true;
	PageItem *nb = b;
	PageItem *nbl = b;
	while (nb != 0)
	{
		if (nb->BackBox != 0)
			nb = nb->BackBox;
		else
			break;
	}
	while (nb != 0)
	{
  		for (uint a = 0; a < nb->itemText.count(); ++a)
  		{
			QChar b = nb->itemText.at(a)->ch[0];
			if (b == QChar(13))
			{
				if (a >= nb->MaxChars)
					paraN++;
				else
					para++;
			}
			if ((!b.isLetterOrNumber()) && (Dat.isLetterOrNumber()) && (!first))
			{
				if (a >= nb->MaxChars)
					wwN++;
				else
					ww++;
			}
			if (a >= nb->MaxChars)
				ccN++;
			else
				cc++;
    		Dat = b;
			first = false;
    	}
		nbl = nb;
		nb = nb->NextBox;
	}
	if (nbl->MaxChars < nbl->itemText.count())
		paraN++;
	else
		para++;
	if (Dat.isLetterOrNumber())
	{
		if (nbl->MaxChars < nbl->itemText.count())
			wwN++;
		else
			ww++;
	}
	*w = ww;
	*p = para;
	*c = cc;
	*wN = wwN;
	*pN = paraN;
	*cN = ccN;
}

void ReOrderText(ScribusDoc *currentDoc, ScribusView *view)
{
	double savScale = view->Scale;
	view->Scale = 1.0;
	currentDoc->RePos = true;
	QPixmap pgPix(10, 10);
	QRect rd = QRect(0,0,9,9);
	ScPainter *painter = new ScPainter(&pgPix, pgPix.width(), pgPix.height());
	for (uint azz=0; azz<currentDoc->MasterItems.count(); ++azz)
	{
		PageItem *ite = currentDoc->MasterItems.at(azz);
		if (ite->PType == 8)
			ite->DrawObj(painter, rd);
	}
	for (uint azz=0; azz<currentDoc->Items.count(); ++azz)
	{
		PageItem *ite = currentDoc->Items.at(azz);
		if ((ite->PType == 4) || (ite->PType == 8))
			ite->DrawObj(painter, rd);
	}
	currentDoc->RePos = false;
	view->Scale = savScale;
	delete painter;
}

/*! 10/06/2004 - pv
\param QString s1 first string
\param QString s2 second string
\retval bool t/f related s1>s2
 */
bool compareQStrings(QString s1, QString s2)
{
	if (QString::localeAwareCompare(s1, s2) >= 0)
		return FALSE;
	return TRUE;
}

/*! 10/06/2004 - pv
Returns a sorted list of QStrings - sorted by locale specific
rules! Uses compareQStrings() as rule. There is STL used!
TODO: Maybe we can implement one cass for various sorting...
\param QStringList aList unsorted string list
\retval QStringList sorted string list
*/
QStringList sortQStringList(QStringList aList)
{
	std::vector<QString> sortList;
	QStringList retList;
	QStringList::Iterator it;
	for (it = aList.begin(); it != aList.end(); ++it)
		sortList.push_back(*it);
	std::sort(sortList.begin(), sortList.end(), compareQStrings);
	for(uint i = 0; i < sortList.size(); i++)
		retList.append(sortList[i]);
	return retList;
}

void GetItemProps(bool newVersion, QDomElement *obj, struct CopyPasteBuffer *OB)
{
	QString tmp;
	int x, y;
	double xf, yf;
	OB->PType = QStoInt(obj->attribute("PTYPE"));
	OB->Width=QStodouble(obj->attribute("WIDTH"));
	OB->Height=QStodouble(obj->attribute("HEIGHT"));
	OB->RadRect = QStodouble(obj->attribute("RADRECT","0"));
	OB->ClipEdited = QStoInt(obj->attribute("CLIPEDIT", "0"));
	OB->FrameType = QStoInt(obj->attribute("FRTYPE", "0"));
	OB->Pwidth=QStodouble(obj->attribute("PWIDTH"));
	OB->Pcolor=obj->attribute("PCOLOR");
	if ((!newVersion) && (OB->PType == 4))
	{
		OB->TxtFill = obj->attribute("PCOLOR2");
		OB->Pcolor2 = "None";
	}
	else
	{
		OB->Pcolor2 = obj->attribute("PCOLOR2");
		OB->TxtFill = obj->attribute("TXTFILL", "Black");
	}
	OB->Shade=QStoInt(obj->attribute("SHADE"));
	OB->Shade2=QStoInt(obj->attribute("SHADE2"));
	OB->TxtStroke=obj->attribute("TXTSTROKE", "None");
	OB->ShTxtFill=QStoInt(obj->attribute("TXTFILLSH", "100"));
	OB->ShTxtStroke=QStoInt(obj->attribute("TXTSTRSH", "100"));
	OB->TxtScale=QStoInt(obj->attribute("TXTSCALE", "100"));
	OB->TxTStyle=QStoInt(obj->attribute("TXTSTYLE", "0"));
	OB->Cols = QStoInt(obj->attribute("COLUMNS","1"));
	OB->ColGap = QStodouble(obj->attribute("COLGAP","0.0"));
	OB->GrType = QStoInt(obj->attribute("GRTYP","0"));
	OB->fill_gradient.clearStops();
	if (OB->GrType != 0)
	{
		OB->GrStartX = QStodouble(obj->attribute("GRSTARTX","0.0"));
		OB->GrStartY = QStodouble(obj->attribute("GRSTARTY","0.0"));
		OB->GrEndX = QStodouble(obj->attribute("GRENDX","0.0"));
		OB->GrEndY = QStodouble(obj->attribute("GRENDY","0.0"));
		OB->GrColor = obj->attribute("GRCOLOR","");
		if (OB->GrColor != "")
		{
			OB->GrColor2 = obj->attribute("GRCOLOR2","");
			OB->GrShade = QStoInt(obj->attribute("GRSHADE","100"));
			OB->GrShade2 = QStoInt(obj->attribute("GRSHADE2","100"));
		}
	}
	OB->Rot=QStodouble(obj->attribute("ROT"));
	OB->PLineArt=Qt::PenStyle(QStoInt(obj->attribute("PLINEART")));
	OB->PLineEnd=Qt::PenCapStyle(QStoInt(obj->attribute("PLINEEND","0")));
	OB->PLineJoin=Qt::PenJoinStyle(QStoInt(obj->attribute("PLINEJOIN","0")));
	OB->LineSp=QStodouble(obj->attribute("LINESP"));
	OB->ExtraV=QStodouble(obj->attribute("EXTRAV","0"));
	OB->LocalScX=QStodouble(obj->attribute("LOCALSCX"));
	OB->LocalScY=QStodouble(obj->attribute("LOCALSCY"));
	OB->LocalX=QStodouble(obj->attribute("LOCALX"));
	OB->LocalY=QStodouble(obj->attribute("LOCALY"));
	OB->PicArt=QStoInt(obj->attribute("PICART"));
	OB->flippedH=QStoInt(obj->attribute("FLIPPEDH"));
	OB->flippedV=QStoInt(obj->attribute("FLIPPEDV"));
	OB->BBoxX=QStodouble(obj->attribute("BBOXX"));
	OB->BBoxH=QStodouble(obj->attribute("BBOXH"));
	OB->ScaleType = QStoInt(obj->attribute("SCALETYPE","1"));
	OB->AspectRatio = QStoInt(obj->attribute("RATIO","0"));
	OB->isPrintable=QStoInt(obj->attribute("PRINTABLE"));
	OB->isAnnotation=QStoInt(obj->attribute("ANNOTATION","0"));
	OB->AnType = QStoInt(obj->attribute("ANTYPE","0"));
	OB->AnAction = obj->attribute("ANACTION","");
	OB->An_E_act = obj->attribute("ANEACT","");
	OB->An_X_act = obj->attribute("ANXACT","");
	OB->An_D_act = obj->attribute("ANDACT","");
	OB->An_Fo_act = obj->attribute("ANFOACT","");
	OB->An_Bl_act = obj->attribute("ANBLACT","");
	OB->An_K_act = obj->attribute("ANKACT","");
	OB->An_F_act = obj->attribute("ANFACT","");
	OB->An_V_act = obj->attribute("ANVACT","");
	OB->An_C_act = obj->attribute("ANCACT","");
	OB->AnActType = QStoInt(obj->attribute("ANACTYP","0"));
	OB->An_Extern = obj->attribute("ANEXTERN","");
	if ((OB->An_Extern != "") && (OB->AnActType != 8))
	{
		QFileInfo efp(OB->An_Extern);
		OB->An_Extern = efp.absFilePath();
	}
	OB->AnZiel = QStoInt(obj->attribute("ANZIEL","0"));
	OB->AnName = obj->attribute("ANNAME","");
	OB->AnToolTip = obj->attribute("ANTOOLTIP","");
	OB->AnRollOver = obj->attribute("ANROLL","");
	OB->AnDown = obj->attribute("ANDOWN","");
	OB->AnBwid = QStoInt(obj->attribute("ANBWID","1"));
	OB->AnBsty = QStoInt(obj->attribute("ANBSTY","0"));
	OB->AnFeed = QStoInt(obj->attribute("ANFEED","1"));
	OB->AnFlag = QStoInt(obj->attribute("ANFLAG","0"));
	OB->AnFont = QStoInt(obj->attribute("ANFONT","4"));
	OB->AnFormat = QStoInt(obj->attribute("ANFORMAT","0"));
	OB->AnVis = QStoInt(obj->attribute("ANVIS","0"));
	OB->AnIsChk = static_cast<bool>(QStoInt(obj->attribute("ANCHK","0")));
	OB->AnAAact = static_cast<bool>(QStoInt(obj->attribute("ANAA","0")));
	OB->AnHTML = static_cast<bool>(QStoInt(obj->attribute("ANHTML","0")));
	OB->AnUseIcons = static_cast<bool>(QStoInt(obj->attribute("ANICON","0")));
	OB->AnChkStil = QStoInt(obj->attribute("ANCHKS","0"));
	OB->AnMaxChar = QStoInt(obj->attribute("ANMC","-1"));
	OB->AnBColor = obj->attribute("ANBCOL","None");
	OB->AnIPlace = QStoInt(obj->attribute("ANPLACE","1"));
	OB->AnScaleW = QStoInt(obj->attribute("ANSCALE","0"));
	if (QStoInt(obj->attribute("TRANSPARENT","0")) == 1)
		OB->Pcolor = "None";
	OB->Textflow=QStoInt(obj->attribute("TEXTFLOW"));
	OB->Textflow2 =QStoInt(obj->attribute("TEXTFLOW2","0"));
	OB->UseContour = QStoInt(obj->attribute("TEXTFLOW3","0"));
	OB->Extra=QStodouble(obj->attribute("EXTRA"));
	OB->TExtra=QStodouble(obj->attribute("TEXTRA", "1"));
	OB->BExtra=QStodouble(obj->attribute("BEXTRA", "1"));
	OB->RExtra=QStodouble(obj->attribute("REXTRA", "1"));
	OB->PoShow = QStoInt(obj->attribute("PTLSHOW","0"));
	OB->BaseOffs = QStodouble(obj->attribute("BASEOF","0"));
	OB->ISize = qRound(QStodouble(obj->attribute("ISIZE","12")) * 10);
	OB->Pfile=obj->attribute("PFILE");
	OB->Pfile2=obj->attribute("PFILE2","");
	OB->Pfile3=obj->attribute("PFILE3","");
	OB->IProfile=obj->attribute("PRFILE","");
	OB->EmProfile=obj->attribute("EPROF","");
	OB->IRender = QStoInt(obj->attribute("IRENDER","1"));
	OB->UseEmbedded = QStoInt(obj->attribute("EMBEDDED","1"));
	OB->Locked = static_cast<bool>(QStoInt(obj->attribute("LOCK","0")));
	OB->LockRes = static_cast<bool>(QStoInt(obj->attribute("LOCKR","0")));
	OB->Reverse = static_cast<bool>(QStoInt(obj->attribute("REVERS","0")));
	OB->InvPict = static_cast<bool>(QStoInt(obj->attribute("INVERS","0")));
	OB->isTableItem = static_cast<bool>(QStoInt(obj->attribute("isTableItem","0")));
	OB->TopLine = static_cast<bool>(QStoInt(obj->attribute("TopLine","0")));
	OB->LeftLine = static_cast<bool>(QStoInt(obj->attribute("LeftLine","0")));
	OB->RightLine = static_cast<bool>(QStoInt(obj->attribute("RightLine","0")));
	OB->BottomLine = static_cast<bool>(QStoInt(obj->attribute("BottomLine","0")));
	OB->TopLinkID =  QStoInt(obj->attribute("TopLINK","-1"));
	OB->LeftLinkID =  QStoInt(obj->attribute("LeftLINK","-1"));
	OB->RightLinkID =  QStoInt(obj->attribute("RightLINK","-1"));
	OB->BottomLinkID =  QStoInt(obj->attribute("BottomLINK","-1"));
	OB->Transparency = QStodouble(obj->attribute("TransValue","0.0"));
	if (obj->hasAttribute("TransValueS"))
		OB->TranspStroke = QStodouble(obj->attribute("TransValueS","0.0"));
	else
		OB->TranspStroke = OB->Transparency;
	tmp = "";
	if (obj->hasAttribute("NUMCLIP"))
	{
		OB->Clip.resize(obj->attribute("NUMCLIP").toUInt());
		tmp = obj->attribute("CLIPCOOR");
		QTextStream fc(&tmp, IO_ReadOnly);
		for (uint c=0; c<obj->attribute("NUMCLIP").toUInt(); ++c)
		{
			fc >> x;
			fc >> y;
			OB->Clip.setPoint(c, x, y);
		}
	}
	else
		OB->Clip.resize(0);
	tmp = "";
	if (obj->hasAttribute("NUMPO"))
	{
		OB->PoLine.resize(obj->attribute("NUMPO").toUInt());
		tmp = obj->attribute("POCOOR");
		QTextStream fp(&tmp, IO_ReadOnly);
		for (uint cx=0; cx<obj->attribute("NUMPO").toUInt(); ++cx)
		{
			fp >> xf;
			fp >> yf;
			OB->PoLine.setPoint(cx, xf, yf);
		}
	}
	else
		OB->PoLine.resize(0);
	tmp = "";
	if (obj->hasAttribute("NUMCO"))
	{
		OB->ContourLine.resize(obj->attribute("NUMCO").toUInt());
		tmp = obj->attribute("COCOOR");
		QTextStream fp(&tmp, IO_ReadOnly);
		for (uint cx=0; cx<obj->attribute("NUMCO").toUInt(); ++cx)
		{
			fp >> xf;
			fp >> yf;
			OB->ContourLine.setPoint(cx, xf, yf);
		}
	}
	else
		OB->ContourLine.resize(0);
	tmp = "";
	if ((obj->hasAttribute("NUMTAB")) && (QStoInt(obj->attribute("NUMTAB","0")) != 0))
	{
		tmp = obj->attribute("TABS");
		QTextStream tgv(&tmp, IO_ReadOnly);
		OB->TabValues.clear();
		for (int cxv = 0; cxv < QStoInt(obj->attribute("NUMTAB","0")); ++cxv)
		{
			tgv >> xf;
			OB->TabValues.append(xf);
		}
		tmp = "";
	}
	else
		OB->TabValues.clear();
	if ((obj->hasAttribute("NUMDASH")) && (QStoInt(obj->attribute("NUMDASH","0")) != 0))
	{
		tmp = obj->attribute("DASHS");
		QTextStream dgv(&tmp, IO_ReadOnly);
		OB->DashValues.clear();
		for (int cxv = 0; cxv < QStoInt(obj->attribute("NUMDASH","0")); ++cxv)
		{
			dgv >> xf;
			OB->DashValues.append(xf);
		}
		tmp = "";
	}
	else
		OB->DashValues.clear();
	OB->DashOffset = QStodouble(obj->attribute("DASHOFF","0.0"));
}

QColor SetColor(ScribusDoc *currentDoc, QString color, int shad)
{
	int h, s, v, sneu;
	QColor tmp;
	currentDoc->PageColors[color].getRGBColor().rgb(&h, &s, &v);
	if ((h == s) && (s == v))
	{
		currentDoc->PageColors[color].getRGBColor().hsv(&h, &s, &v);
		sneu = 255 - ((255 - v) * shad / 100);
		tmp.setHsv(h, s, sneu);
	}
	else
	{
		currentDoc->PageColors[color].getRGBColor().hsv(&h, &s, &v);
		sneu = s * shad / 100;
		tmp.setHsv(h, sneu, v);
	}
	return tmp;
}
