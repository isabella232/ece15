/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "scimage.h"
#include "scribus.h"
#include "scpaths.h"
#include "scribuscore.h"
#include "scimgdataloader_gimp.h"
#include "scimgdataloader_jpeg.h"
#include "scimgdataloader_pdf.h"
#include "scimgdataloader_ps.h"
#include "scimgdataloader_psd.h"
#include "scimgdataloader_pdf.h"
#include "scimgdataloader_qt.h"
#include "scimgdataloader_tiff.h"
#include <qmessagebox.h>
#include <qtextstream.h>
#include <memory>
#include <cassert>
#include CMS_INC
#include "cmsutil.h"
#include "gsutil.h"
#include "exif.h"
#include "commonstrings.h"
#include "colorutil.h"
#include "util.h"
#include "rawimage.h"

using namespace std;

typedef struct my_error_mgr
{
	struct jpeg_error_mgr pub;            /* "public" fields */
	jmp_buf setjmp_buffer;  /* for return to caller */
}
*my_error_ptr;

static void my_error_exit (j_common_ptr cinfo)
{
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	(*cinfo->err->output_message) (cinfo);
	longjmp (myerr->setjmp_buffer, 1);
}

ScImage::ScImage(const QImage & image) : QImage(image)
{
	initialize();
}


// ScImage will use implicit sharing:
ScImage::ScImage(const ScImage & image) : QImage(image.copy())
{
	initialize();
}


ScImage::ScImage() : QImage()
{
	initialize();
}

ScImage::ScImage( int width, int height ) : QImage( width, height, 32 )
{
	initialize();
}

const QImage& ScImage::qImage()
{
	return *this;
}

QImage* ScImage::qImagePtr()
{
	return this;
}

QImage ScImage::smoothScale(int h, int w, QImage::ScaleMode mode) const
{
	return QImage::smoothScale(h,w,mode);
}


void ScImage::initialize()
{
	imgInfo.xres = 72;
	imgInfo.yres = 72;
	imgInfo.colorspace = 0;
	imgInfo.valid = false;
	imgInfo.isRequest = false;
	imgInfo.isEmbedded = false;
	imgInfo.progressive = false;
	imgInfo.exifDataValid = false;
	imgInfo.lowResType = 1;
	imgInfo.lowResScale = 1.0;
	imgInfo.PDSpathData.clear();
	imgInfo.RequestProps.clear();
	imgInfo.clipPath = "";
	imgInfo.usedPath = "";
	imgInfo.layerInfo.clear();
	imgInfo.duotoneColors.clear();
	imgInfo.exifInfo.cameraName = "";
	imgInfo.exifInfo.cameraVendor = "";
	imgInfo.exifInfo.thumbnail = QImage();
	imgInfo.BBoxX = 0;
	imgInfo.BBoxH = 0;
}

ScImage::~ScImage()
{
	curveTable.resize(0);
}

void ScImage::applyEffect(QValueList<imageEffect> effectsList, QMap<QString,ScColor> colors, bool cmyk)
{
	if (effectsList.count() != 0)
	{
		for (uint a = 0; a < effectsList.count(); ++a)
		{
			if ((*effectsList.at(a)).effectCode == EF_INVERT)
				invert(cmyk);
			if ((*effectsList.at(a)).effectCode == EF_GRAYSCALE)
				toGrayscale(cmyk);
			if ((*effectsList.at(a)).effectCode == EF_COLORIZE)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				QString col = CommonStrings::None;
				int shading = 100;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				fp >> col;
				fp >> shading;
				colorize(colors[col], shading, cmyk);
			}
			if ((*effectsList.at(a)).effectCode == EF_BRIGHTNESS)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				int brightnessValue = 0;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				fp >> brightnessValue;
				brightness(brightnessValue, cmyk);
			}
			if ((*effectsList.at(a)).effectCode == EF_CONTRAST)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				int contrastValue = 0;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				fp >> contrastValue;
				contrast(contrastValue, cmyk);
			}
			if ((*effectsList.at(a)).effectCode == EF_SHARPEN)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				double radius, sigma;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				fp >> radius;
				fp >> sigma;
				sharpen(radius, sigma);
			}
			if ((*effectsList.at(a)).effectCode == EF_BLUR)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				double radius, sigma;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				fp >> radius;
				fp >> sigma;
				blur(static_cast<int>(radius));
			}
			if ((*effectsList.at(a)).effectCode == EF_SOLARIZE)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				double sigma;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				fp >> sigma;
				solarize(sigma, cmyk);
			}
			if ((*effectsList.at(a)).effectCode == EF_DUOTONE)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				QString col1 = CommonStrings::None;
				int shading1 = 100;
				QString col2 = CommonStrings::None;
				int shading2 = 100;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				col1 = fp.readLine();
				col2 = fp.readLine();
				fp >> shading1;
				fp >> shading2;
				int numVals;
				double xval, yval;
				FPointArray curve1;
				curve1.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve1.addPoint(xval, yval);
				}
				int lin1;
				fp >> lin1;
				FPointArray curve2;
				curve2.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve2.addPoint(xval, yval);
				}
				int lin2;
				fp >> lin2;
				duotone(colors[col1], shading1, curve1, lin1, colors[col2], shading2, curve2, lin2, cmyk);
			}
			if ((*effectsList.at(a)).effectCode == EF_TRITONE)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				QString col1 = CommonStrings::None;
				QString col2 = CommonStrings::None;
				QString col3 = CommonStrings::None;
				int shading1 = 100;
				int shading2 = 100;
				int shading3 = 100;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				col1 = fp.readLine();
				col2 = fp.readLine();
				col3 = fp.readLine();
				fp >> shading1;
				fp >> shading2;
				fp >> shading3;
				int numVals;
				double xval, yval;
				FPointArray curve1;
				curve1.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve1.addPoint(xval, yval);
				}
				int lin1;
				fp >> lin1;
				FPointArray curve2;
				curve2.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve2.addPoint(xval, yval);
				}
				int lin2;
				fp >> lin2;
				FPointArray curve3;
				curve3.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve3.addPoint(xval, yval);
				}
				int lin3;
				fp >> lin3;
				tritone(colors[col1], shading1, curve1, lin1, colors[col2], shading2, curve2, lin2, colors[col3], shading3, curve3, lin3, cmyk);
			}
			if ((*effectsList.at(a)).effectCode == EF_QUADTONE)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				QString col1 = CommonStrings::None;
				QString col2 = CommonStrings::None;
				QString col3 = CommonStrings::None;
				QString col4 = CommonStrings::None;
				int shading1 = 100;
				int shading2 = 100;
				int shading3 = 100;
				int shading4 = 100;
				QTextStream fp(&tmpstr, IO_ReadOnly);
				col1 = fp.readLine();
				col2 = fp.readLine();
				col3 = fp.readLine();
				col4 = fp.readLine();
				fp >> shading1;
				fp >> shading2;
				fp >> shading3;
				fp >> shading4;
				int numVals;
				double xval, yval;
				FPointArray curve1;
				curve1.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve1.addPoint(xval, yval);
				}
				int lin1;
				fp >> lin1;
				FPointArray curve2;
				curve2.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve2.addPoint(xval, yval);
				}
				int lin2;
				fp >> lin2;
				FPointArray curve3;
				curve3.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve3.addPoint(xval, yval);
				}
				int lin3;
				fp >> lin3;
				FPointArray curve4;
				curve4.resize(0);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve4.addPoint(xval, yval);
				}
				int lin4;
				fp >> lin4;
				quadtone(colors[col1], shading1, curve1, lin1, colors[col2], shading2, curve2, lin2, colors[col3], shading3, curve3, lin3, colors[col4], shading4, curve4, lin4, cmyk);
			}
			if ((*effectsList.at(a)).effectCode == EF_GRADUATE)
			{
				QString tmpstr = (*effectsList.at(a)).effectParameters;
				int numVals;
				double xval, yval;
				FPointArray curve;
				curve.resize(0);
				QTextStream fp(&tmpstr, IO_ReadOnly);
				fp >> numVals;
				for (int nv = 0; nv < numVals; nv++)
				{
					fp >> xval;
					fp >> yval;
					curve.addPoint(xval, yval);
				}
				int lin;
				fp >> lin;
				doGraduate(curve, cmyk, lin);
			}
		}
	}
}

void ScImage::liberateMemory(void **memory)
{
	assert(memory != (void **)NULL);
	if(*memory == (void *)NULL)
		return;
	free(*memory);
	*memory=(void *) NULL;
}

void ScImage::solarize(double factor, bool cmyk)
{
	curveTable.resize(256);
	int fk = qRound(255 / factor);
	for (int i = 0; i < 256; ++i)
	{
		curveTable[i] = QMIN(255, static_cast<int>(i / fk) * fk);
	}
	applyCurve(cmyk);
}

// Stack Blur Algorithm by Mario Klingemann <mario@quasimondo.com>
void ScImage::blur(int radius)
{
    if (radius < 1) {
        return;
    }

    QRgb *pix = (QRgb*)bits();
    int w   = width();
    int h   = height();
    int wm  = w-1;
    int hm  = h-1;
    int wh  = w*h;
    int div = radius+radius+1;

    int *r = new int[wh];
    int *g = new int[wh];
    int *b = new int[wh];
    int *a = new int[wh];
    int rsum, gsum, bsum, asum, x, y, i, yp, yi, yw;
    QRgb p;
    int *vmin = new int[QMAX(w,h)];

    int divsum = (div+1)>>1;
    divsum *= divsum;
    int *dv = new int[256*divsum];
    for (i=0; i < 256*divsum; ++i) {
        dv[i] = (i/divsum);
    }

    yw = yi = 0;

    int **stack = new int*[div];
    for(int i = 0; i < div; ++i) {
        stack[i] = new int[4];
    }


    int stackpointer;
    int stackstart;
    int *sir;
    int rbs;
    int r1 = radius+1;
    int routsum, goutsum, boutsum, aoutsum;
    int rinsum, ginsum, binsum, ainsum;

    for (y = 0; y < h; ++y){
        rinsum = ginsum = binsum = ainsum
               = routsum = goutsum = boutsum = aoutsum
               = rsum = gsum = bsum = asum = 0;
        for(i =- radius; i <= radius; ++i) {
            p = pix[yi+QMIN(wm,QMAX(i,0))];
            sir = stack[i+radius];
            sir[0] = qRed(p);
            sir[1] = qGreen(p);
            sir[2] = qBlue(p);
            sir[3] = qAlpha(p);
            
            rbs = r1-abs(i);
            rsum += sir[0]*rbs;
            gsum += sir[1]*rbs;
            bsum += sir[2]*rbs;
            asum += sir[3]*rbs;
            
            if (i > 0){
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
                ainsum += sir[3];
            } else {
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
                aoutsum += sir[3];
            }
        }
        stackpointer = radius;

        for (x=0; x < w; ++x) {

            r[yi] = dv[rsum];
            g[yi] = dv[gsum];
            b[yi] = dv[bsum];
            a[yi] = dv[asum];

            rsum -= routsum;
            gsum -= goutsum;
            bsum -= boutsum;
            asum -= aoutsum;

            stackstart = stackpointer-radius+div;
            sir = stack[stackstart%div];

            routsum -= sir[0];
            goutsum -= sir[1];
            boutsum -= sir[2];
            aoutsum -= sir[3];

            if (y == 0) {
                vmin[x] = QMIN(x+radius+1,wm);
            }
            p = pix[yw+vmin[x]];

            sir[0] = qRed(p);
            sir[1] = qGreen(p);
            sir[2] = qBlue(p);
            sir[3] = qAlpha(p);

            rinsum += sir[0];
            ginsum += sir[1];
            binsum += sir[2];
            ainsum += sir[3];

            rsum += rinsum;
            gsum += ginsum;
            bsum += binsum;
            asum += ainsum;

            stackpointer = (stackpointer+1)%div;
            sir = stack[(stackpointer)%div];

            routsum += sir[0];
            goutsum += sir[1];
            boutsum += sir[2];
            aoutsum += sir[3];

            rinsum -= sir[0];
            ginsum -= sir[1];
            binsum -= sir[2];
            ainsum -= sir[3];

            ++yi;
        }
        yw += w;
    }
    for (x=0; x < w; ++x){
        rinsum = ginsum = binsum = ainsum 
               = routsum = goutsum = boutsum = aoutsum 
               = rsum = gsum = bsum = asum = 0;
        
        yp =- radius * w;
        
        for(i=-radius; i <= radius; ++i) {
            yi=QMAX(0,yp)+x;

            sir = stack[i+radius];

            sir[0] = r[yi];
            sir[1] = g[yi];
            sir[2] = b[yi];
            sir[3] = a[yi];

            rbs = r1-abs(i);

            rsum += r[yi]*rbs;
            gsum += g[yi]*rbs;
            bsum += b[yi]*rbs;
            asum += a[yi]*rbs;

            if (i > 0) {
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
                ainsum += sir[3];
            } else {
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
                aoutsum += sir[3];
            }

            if (i < hm){
                yp += w;
            }
        }

        yi = x;
        stackpointer = radius;

        for (y=0; y < h; ++y){
            pix[yi] = qRgba(dv[rsum], dv[gsum], dv[bsum], dv[asum]);

            rsum -= routsum;
            gsum -= goutsum;
            bsum -= boutsum;
            asum -= aoutsum;

            stackstart = stackpointer-radius+div;
            sir = stack[stackstart%div];

            routsum -= sir[0];
            goutsum -= sir[1];
            boutsum -= sir[2];
            aoutsum -= sir[3];

            if (x==0){
                vmin[y] = QMIN(y+r1,hm)*w;
            }
            p = x+vmin[y];

            sir[0] = r[p];
            sir[1] = g[p];
            sir[2] = b[p];
            sir[3] = a[p];

            rinsum += sir[0];
            ginsum += sir[1];
            binsum += sir[2];
            ainsum += sir[3];

            rsum += rinsum;
            gsum += ginsum;
            bsum += binsum;
            asum += ainsum;

            stackpointer = (stackpointer+1)%div;
            sir = stack[stackpointer];

            routsum += sir[0];
            goutsum += sir[1];
            boutsum += sir[2];
            aoutsum += sir[3];

            rinsum -= sir[0];
            ginsum -= sir[1];
            binsum -= sir[2];
            ainsum -= sir[3];

            yi += w;
        }
    }
    delete [] r;
    delete [] g;
    delete [] b;
    delete [] a;
    delete [] vmin;
    delete [] dv;

    for(int i = 0; i < div; ++i) {
        delete [] stack[i];
    }
    delete [] stack;
}

bool ScImage::convolveImage(QImage *dest, const unsigned int order, const double *kernel)
{
	long widthk;
	double red, green, blue, alpha;
	double normalize, *normal_kernel;
	register const double *k;
	register unsigned int *q;
	int x, y, mx, my, sx, sy;
	long i;
	int mcx, mcy;
	widthk = order;
	if((widthk % 2) == 0)
		return(false);
	normal_kernel = (double *)malloc(widthk*widthk*sizeof(double));
	if(!normal_kernel)
		return(false);
	dest->reset();
	dest->create(width(), height(), 32);
	normalize=0.0;
	for(i=0; i < (widthk*widthk); i++)
		normalize += kernel[i];
	if(fabs(normalize) <= 1.0e-12)
		normalize=1.0;
	normalize=1.0/normalize;
	for(i=0; i < (widthk*widthk); i++)
		normal_kernel[i] = normalize*kernel[i];
	unsigned int **jumpTablek = (unsigned int **)jumpTable();
	for(y=0; y < dest->height(); ++y)
	{
		sy = y-(widthk/2);
		q = (unsigned int *)dest->scanLine(y);
		for(x=0; x < dest->width(); ++x)
		{
			k = normal_kernel;
			red = green = blue = alpha = 0;
			sy = y-(widthk/2);
			for(mcy=0; mcy < widthk; ++mcy, ++sy)
			{
				my = sy < 0 ? 0 : sy > height()-1 ? height()-1 : sy;
				sx = x+(-widthk/2);
				for(mcx=0; mcx < widthk; ++mcx, ++sx)
				{
					mx = sx < 0 ? 0 : sx > width()-1 ? width()-1 : sx;
					red += (*k)*(qRed(jumpTablek[my][mx])*257);
					green += (*k)*(qGreen(jumpTablek[my][mx])*257);
					blue += (*k)*(qBlue(jumpTablek[my][mx])*257);
					alpha += (*k)*(qAlpha(jumpTablek[my][mx])*257);
					++k;
				}
			}
			red = red < 0 ? 0 : red > 65535 ? 65535 : red+0.5;
			green = green < 0 ? 0 : green > 65535 ? 65535 : green+0.5;
			blue = blue < 0 ? 0 : blue > 65535 ? 65535 : blue+0.5;
			alpha = alpha < 0 ? 0 : alpha > 65535 ? 65535 : alpha+0.5;
			*q++ = qRgba((unsigned char)(red/257UL),
			             (unsigned char)(green/257UL),
			             (unsigned char)(blue/257UL),
			             (unsigned char)(alpha/257UL));
		}
	}
	free(normal_kernel);
	return(true);
}

int ScImage::getOptimalKernelWidth(double radius, double sigma)
{
	double normalize, value;
	long width;
	register long u;
	assert(sigma != 0.0);
	if(radius > 0.0)
		return((int)(2.0*ceil(radius)+1.0));
	for(width=5; ;)
	{
		normalize=0.0;
		for(u=(-width/2); u <= (width/2); u++)
			normalize+=exp(-((double) u*u)/(2.0*sigma*sigma))/(2.50662827463100024161235523934010416269302368164062*sigma);
		u=width/2;
		value=exp(-((double) u*u)/(2.0*sigma*sigma))/(2.50662827463100024161235523934010416269302368164062*sigma)/normalize;
		if((long)(65535*value) <= 0)
			break;
		width+=2;
	}
	return((int)width-2);
}

void ScImage::sharpen(double radius, double sigma)
{
	double alpha, normalize, *kernel;
	int widthk;
	register long i, u, v;
	QImage dest;
	if(sigma == 0.0)
		return;
	widthk = getOptimalKernelWidth(radius, sigma);
	if(width() < widthk)
		return;
	kernel = (double *)malloc(widthk*widthk*sizeof(double));
	if(!kernel)
		return;
	i = 0;
	normalize=0.0;
	for (v=(-widthk/2); v <= (widthk/2); v++)
	{
		for (u=(-widthk/2); u <= (widthk/2); u++)
		{
			alpha=exp(-((double) u*u+v*v)/(2.0*sigma*sigma));
			kernel[i]=alpha/(2.0*3.14159265358979323846264338327950288419716939937510*sigma*sigma);
			normalize+=kernel[i];
			i++;
		}
	}
	kernel[i/2]=(-2.0)*normalize;
	convolveImage(&dest, widthk, kernel);
	liberateMemory((void **) &kernel);
	for( int yi=0; yi < dest.height(); ++yi )
	{
		QRgb *s = (QRgb*)(dest.scanLine( yi ));
		QRgb *d = (QRgb*)(scanLine( yi ));
		for(int xi=0; xi < dest.width(); ++xi )
		{
			(*d) = (*s);
			s++;
			d++;
		}
	}
	return;
}

void ScImage::contrast(int contrastValue, bool cmyk)
{
	curveTable.resize(256);
	QPoint p1(0,0 - contrastValue);
	QPoint p2(256, 256 + contrastValue);
	double mc = (p1.y() - p2.y()) / (double)(p1.x() - p2.x());
	for (int i = 0; i < 256; ++i)
	{
		curveTable[i] = QMIN(255, QMAX(0, int(i * mc) + p1.y()));
	}
	applyCurve(cmyk);
}

void ScImage::brightness(int brightnessValue, bool cmyk)
{
	curveTable.resize(256);
	QPoint p1(0,0 + brightnessValue);
	QPoint p2(256, 256 + brightnessValue);
	double mc = (p1.y() - p2.y()) / (double)(p1.x() - p2.x());
	for (int i = 0; i < 256; ++i)
	{
		curveTable[i] = QMIN(255, QMAX(0, int(i * mc) + p1.y()));
	}
	applyCurve(cmyk);
}

void ScImage::doGraduate(FPointArray curve, bool cmyk, bool linear)
{
	curveTable.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve, x / 255.0, linear) * 255)));
	}
	applyCurve(cmyk);
}

void ScImage::applyCurve(bool cmyk)
{
	int h = height();
	int w = width();
	QRgb *s;
	QRgb r;
	int c, m, y, k;
	unsigned char *p;
	unsigned char rc, gc, bc;
	for( int yi=0; yi < h; ++yi )
	{
		s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			r = *s;
			if (cmyk)
			{
				p = (unsigned char *) s;
				rc = 255 - QMIN(255, p[0] + p[3]);
				gc = 255 - QMIN(255, p[1] + p[3]);
				bc = 255 - QMIN(255, p[2] + p[3]);
				c = 255 - curveTable[(int)rc];
				m = 255 - curveTable[(int)gc];
				y = 255 - curveTable[(int)bc];
				k = QMIN(QMIN(c, m), y);
				*s = qRgba(y - k, m - k, c - k, k );
			}
			else
			{
				c = curveTable[qRed(r)];
				m = curveTable[qGreen(r)];
				y = curveTable[qBlue(r)];
				k = qAlpha(r);
				*s = qRgba(c, m, y, k);
			}
			s++;
		}
	}
}

void ScImage::colorize(ScColor color, int shade, bool cmyk)
{
	int h = height();
	int w = width();
	int cc, cm, cy, ck;
	int hu, sa, v;
	ScColor tmp2;
	QColor tmpR;
	QRgb *s;
	QRgb r;
	double k;
	int cc2, cm2, cy2, k2;
	if (cmyk)
		color.getShadeColorCMYK(&cc, &cm, &cy, &ck, shade);
	else
	{
		ck = 0;
		color.getShadeColorRGB(&cc, &cm, &cy, shade);
	}
	for( int yi=0; yi < h; ++yi )
	{
		s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			r = *s;
			if (cmyk)
			{
				k = QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r) + qAlpha(r)), 255) / 255.0;
				*s = qRgba(QMIN(qRound(cc*k), 255), QMIN(qRound(cm*k), 255), QMIN(qRound(cy*k), 255), QMIN(qRound(ck*k), 255));
			}
			else
			{
				k2 = 255 - QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r)), 255);
				tmpR.setRgb(cc, cm, cy);
				tmpR.hsv(&hu, &sa, &v);
				tmpR.setHsv(hu, sa * k2 / 255, 255 - ((255 - v) * k2 / 255));
				tmpR.getRgb(&cc2, &cm2, &cy2);
				*s = qRgba(cc2, cm2, cy2, qAlpha(r));
			}
			s++;
		}
	}
}

void ScImage::duotone(ScColor color1, int shade1, FPointArray curve1, bool lin1, ScColor color2, int shade2, FPointArray curve2, bool lin2, bool cmyk)
{
	int h = height();
	int w = width();
	int c, c1, m, m1, y, y1, k, k1;
	int cn, c1n, mn, m1n, yn, y1n, kn, k1n;
	uchar cb;
	QMemArray<int> curveTable1;
	QMemArray<int> curveTable2;
	color1.getShadeColorCMYK(&c, &m, &y, &k, shade1);
	color2.getShadeColorCMYK(&c1, &m1, &y1, &k1, shade2);
	curveTable1.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable1[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve1, x / 255.0, lin1) * 255)));
	}
	curveTable2.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable2[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve2, x / 255.0, lin2) * 255)));
	}
	for( int yi=0; yi < h; ++yi )
	{
		QRgb * s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			QRgb r=*s;
			if (cmyk)
				cb = QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r) + qAlpha(r)), 255);
			else
				cb = 255 - QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r)), 255);
			cn = QMIN((c * curveTable1[(int)cb]) >> 8, 255);
			mn = QMIN((m * curveTable1[(int)cb]) >> 8, 255);
			yn = QMIN((y * curveTable1[(int)cb]) >> 8, 255);
			kn = QMIN((k * curveTable1[(int)cb]) >> 8, 255);
			c1n = QMIN((c1 * curveTable1[(int)cb]) >> 8, 255);
			m1n = QMIN((m1 * curveTable2[(int)cb]) >> 8, 255);
			y1n = QMIN((y1 * curveTable2[(int)cb]) >> 8, 255);
			k1n = QMIN((k1 * curveTable2[(int)cb]) >> 8, 255);
			ScColor col = ScColor(QMIN(cn+c1n, 255), QMIN(mn+m1n, 255), QMIN(yn+y1n, 255), QMIN(kn+k1n, 255));
			if (cmyk)
				col.getCMYK(&cn, &mn, &yn, &kn);
			else
			{
				col.getRawRGBColor(&cn, &mn, &yn);
				kn = qAlpha(r);
			}
			*s = qRgba(cn, mn, yn, kn);
			s++;
		}
	}
}

void ScImage::tritone(ScColor color1, int shade1, FPointArray curve1, bool lin1, ScColor color2, int shade2, FPointArray curve2, bool lin2, ScColor color3, int shade3, FPointArray curve3, bool lin3, bool cmyk)
{
	int h = height();
	int w = width();
	int c, c1, c2, m, m1, m2, y, y1, y2, k, k1, k2;
	int cn, c1n, c2n, mn, m1n, m2n, yn, y1n, y2n, kn, k1n, k2n;
	uchar cb;
	QMemArray<int> curveTable1;
	QMemArray<int> curveTable2;
	QMemArray<int> curveTable3;
	color1.getShadeColorCMYK(&c, &m, &y, &k, shade1);
	color2.getShadeColorCMYK(&c1, &m1, &y1, &k1, shade2);
	color3.getShadeColorCMYK(&c2, &m2, &y2, &k2, shade3);
	curveTable1.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable1[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve1, x / 255.0, lin1) * 255)));
	}
	curveTable2.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable2[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve2, x / 255.0, lin2) * 255)));
	}
	curveTable3.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable3[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve2, x / 255.0, lin3) * 255)));
	}
	for( int yi=0; yi < h; ++yi )
	{
		QRgb * s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			QRgb r=*s;
			if (cmyk)
				cb = QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r) + qAlpha(r)), 255);
			else
				cb = 255 - QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r)), 255);
			cn = QMIN((c * curveTable1[(int)cb]) >> 8, 255);
			mn = QMIN((m * curveTable1[(int)cb]) >> 8, 255);
			yn = QMIN((y * curveTable1[(int)cb]) >> 8, 255);
			kn = QMIN((k * curveTable1[(int)cb]) >> 8, 255);
			c1n = QMIN((c1 * curveTable2[(int)cb]) >> 8, 255);
			m1n = QMIN((m1 * curveTable2[(int)cb]) >> 8, 255);
			y1n = QMIN((y1 * curveTable2[(int)cb]) >> 8, 255);
			k1n = QMIN((k1 * curveTable2[(int)cb]) >> 8, 255);
			c2n = QMIN((c2 * curveTable3[(int)cb]) >> 8, 255);
			m2n = QMIN((m2 * curveTable3[(int)cb]) >> 8, 255);
			y2n = QMIN((y2 * curveTable3[(int)cb]) >> 8, 255);
			k2n = QMIN((k2 * curveTable3[(int)cb]) >> 8, 255);
			ScColor col = ScColor(QMIN(cn+c1n+c2n, 255), QMIN(mn+m1n+m2n, 255), QMIN(yn+y1n+y2n, 255), QMIN(kn+k1n+k2n, 255));
			if (cmyk)
				col.getCMYK(&cn, &mn, &yn, &kn);
			else
			{
				col.getRawRGBColor(&cn, &mn, &yn);
				kn = qAlpha(r);
			}
			*s = qRgba(cn, mn, yn, kn);
			s++;
		}
	}
}

void ScImage::quadtone(ScColor color1, int shade1, FPointArray curve1, bool lin1, ScColor color2, int shade2, FPointArray curve2, bool lin2, ScColor color3, int shade3, FPointArray curve3, bool lin3, ScColor color4, int shade4, FPointArray curve4, bool lin4, bool cmyk)
{
	int h = height();
	int w = width();
	int c, c1, c2, c3, m, m1, m2, m3, y, y1, y2, y3, k, k1, k2, k3;
	int cn, c1n, c2n, c3n, mn, m1n, m2n, m3n, yn, y1n, y2n, y3n, kn, k1n, k2n, k3n;
	uchar cb;
	QMemArray<int> curveTable1;
	QMemArray<int> curveTable2;
	QMemArray<int> curveTable3;
	QMemArray<int> curveTable4;
	color1.getShadeColorCMYK(&c, &m, &y, &k, shade1);
	color2.getShadeColorCMYK(&c1, &m1, &y1, &k1, shade2);
	color3.getShadeColorCMYK(&c2, &m2, &y2, &k2, shade3);
	color4.getShadeColorCMYK(&c3, &m3, &y3, &k3, shade4);
	curveTable1.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable1[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve1, x / 255.0, lin1) * 255)));
	}
	curveTable2.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable2[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve2, x / 255.0, lin2) * 255)));
	}
	curveTable3.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable3[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve3, x / 255.0, lin3) * 255)));
	}
	curveTable4.resize(256);
	for (int x = 0 ; x < 256 ; x++)
	{
		curveTable4[x] = QMIN(255, QMAX(0, qRound(getCurveYValue(curve4, x / 255.0, lin4) * 255)));
	}
	for( int yi=0; yi < h; ++yi )
	{
		QRgb * s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			QRgb r=*s;
			if (cmyk)
				cb = QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r) + qAlpha(r)), 255);
			else
				cb = 255 - QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r)), 255);
			cn = QMIN((c * curveTable1[(int)cb]) >> 8, 255);
			mn = QMIN((m * curveTable1[(int)cb]) >> 8, 255);
			yn = QMIN((y * curveTable1[(int)cb]) >> 8, 255);
			kn = QMIN((k * curveTable1[(int)cb]) >> 8, 255);
			c1n = QMIN((c1 * curveTable2[(int)cb]) >> 8, 255);
			m1n = QMIN((m1 * curveTable2[(int)cb]) >> 8, 255);
			y1n = QMIN((y1 * curveTable2[(int)cb]) >> 8, 255);
			k1n = QMIN((k1 * curveTable2[(int)cb]) >> 8, 255);
			c2n = QMIN((c2 * curveTable3[(int)cb]) >> 8, 255);
			m2n = QMIN((m2 * curveTable3[(int)cb]) >> 8, 255);
			y2n = QMIN((y2 * curveTable3[(int)cb]) >> 8, 255);
			k2n = QMIN((k2 * curveTable3[(int)cb]) >> 8, 255);
			c3n = QMIN((c3 * curveTable4[(int)cb]) >> 8, 255);
			m3n = QMIN((m3 * curveTable4[(int)cb]) >> 8, 255);
			y3n = QMIN((y3 * curveTable4[(int)cb]) >> 8, 255);
			k3n = QMIN((k3 * curveTable4[(int)cb]) >> 8, 255);
			ScColor col = ScColor(QMIN(cn+c1n+c2n+c3n, 255), QMIN(mn+m1n+m2n+m3n, 255), QMIN(yn+y1n+y2n+y3n, 255), QMIN(kn+k1n+k2n+k3n, 255));
			if (cmyk)
				col.getCMYK(&cn, &mn, &yn, &kn);
			else
			{
				col.getRawRGBColor(&cn, &mn, &yn);
				kn = qAlpha(r);
			}
			*s = qRgba(cn, mn, yn, kn);
			s++;
		}
	}
}

void ScImage::invert(bool cmyk)
{
	int h = height();
	int w = width();
	unsigned char *p;
	QRgb * s;
	unsigned char c, m, y, k;
	for( int yi=0; yi < h; ++yi )
	{
		s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			if (cmyk)
			{
				p = (unsigned char *) s;
				c = 255 - QMIN(255, p[0] + p[3]);
				m = 255 - QMIN(255, p[1] + p[3]);
				y = 255 - QMIN(255, p[2] + p[3]);
				k = QMIN(QMIN(c, m), y);
				p[0] = c - k;
				p[1] = m - k;
				p[2] = y - k;
				p[3] = k;
			}
			else
				*s ^= 0x00ffffff;
			s++;
		}
	}
}

void ScImage::toGrayscale(bool cmyk)
{
	int h = height();
	int w = width();
	int k;
	QRgb * s;
	QRgb r;
	for( int yi=0; yi < h; ++yi )
	{
		s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			r = *s;
			if (cmyk)
			{
				k = QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r) + qAlpha(r)), 255);
				*s = qRgba(0, 0, 0, k);
			}
			else
			{
				k = QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r)), 255);
				*s = qRgba(k, k, k, qAlpha(r));
			}
			s++;
		}
	}
}

void ScImage::swapRGBA()
{
	unsigned int *ptr;
	unsigned char *p;
	unsigned char r, b;
	for (int i = 0; i < height(); ++i)
	{
		ptr = (unsigned int *) scanLine(i);
		for (int j = 0; j < width(); ++j)
		{
			p = (unsigned char *) ptr;
			r = p[0];
			b = p[2];
			p[2] = r;
			p[0] = b;
			ptr++;
		}
	}
}

void ScImage::createLowRes(double scale)
{
	int w = qRound(width() / scale);
	int h = qRound(height() / scale);
	QImage tmp = smoothScale(w, h);
	create(w, h, 32);
	setAlphaBuffer(true);
	tmp = tmp.convertDepth(32);
	QRgb *s;
	QRgb *d;
	for( int yi=0; yi < tmp.height(); ++yi )
	{
		s = (QRgb*)(tmp.scanLine( yi ));
		d = (QRgb*)(scanLine( yi ));
		for(int xi=0; xi < tmp.width(); ++xi )
		{
			(*d) = (*s);
			s++;
			d++;
		}
	}
}

void ScImage::Convert2JPG(QString fn, int Quality, bool isCMYK, bool isGray)
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
	if ((outfile = fopen (fn.local8Bit(), "wb")) == NULL)
		return;
	jpeg_stdio_dest (&cinfo, outfile);
	cinfo.image_width  = width();
	cinfo.image_height = height();
	if (isCMYK)
	{
		cinfo.in_color_space = JCS_CMYK;
		cinfo.input_components = 4;
	}
	else
	{
		if (isGray)
		{
			cinfo.in_color_space = JCS_GRAYSCALE;
			cinfo.input_components = 1;
		}
		else
		{
			cinfo.in_color_space = JCS_RGB;
			cinfo.input_components = 3;
		}
	}
	jpeg_set_defaults (&cinfo);
	int qual[] = { 95, 85, 75, 50, 25 };  // These are the JPEG Quality settings 100 means best, 0 .. don't discuss
	jpeg_set_quality (&cinfo, qual[Quality], true);
	jpeg_start_compress (&cinfo, true);
	row_pointer[0] = new uchar[cinfo.image_width*cinfo.input_components];
	int w = cinfo.image_width;
	while (cinfo.next_scanline < cinfo.image_height)
	{
		uchar *row = row_pointer[0];
		if (isCMYK)
		{
			QRgb* rgba = (QRgb*)scanLine(cinfo.next_scanline);
			for (int i=0; i<w; ++i)
			{
				*row++ = 255-qRed(*rgba);
				*row++ = 255-qGreen(*rgba);
				*row++ = 255-qBlue(*rgba);
				*row++ = 255-qAlpha(*rgba);
				++rgba;
			}
		}
		else
		{
			if (isGray)
			{
				QRgb* rgba = (QRgb*)scanLine(cinfo.next_scanline);
				for (int i=0; i<w; ++i)
				{
					*row++ = qRed(*rgba);
					++rgba;
				}
			}
			else
			{
				QRgb* rgb = (QRgb*)scanLine(cinfo.next_scanline);
				for (int i=0; i<w; i++)
				{
					*row++ = qRed(*rgb);
					*row++ = qGreen(*rgb);
					*row++ = qBlue(*rgb);
					++rgb;
				}
			}
		}
		jpeg_write_scanlines (&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress (&cinfo);
	fclose (outfile);
	jpeg_destroy_compress (&cinfo);
	delete [] row_pointer[0];
}

QByteArray ScImage::ImageToArray()
{
	int i = 0;
	int h = height();
	int w = width();
	unsigned char u;
	QRgb *s;
	QRgb r;
	QByteArray imgArray(3 * h * w);
	for( int yi=0; yi < h; ++yi )
	{
		s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			r = *s++;
			u=qRed(r);
			imgArray[i++] = u;
			u=qGreen(r);
			imgArray[i++] = u;
			u=qBlue(r);
			imgArray[i++] = u;
		}
	}
	return imgArray;
}

QByteArray ScImage::ImageToGray()
{
	int i = 0;
	int h = height();
	int w = width();
	QRgb *s;
	QRgb r;
	QByteArray imgArray(h * w);
	int k;
	for( int yi=0; yi < h; ++yi )
	{
		s = (QRgb*)(scanLine( yi ));
		for( int xi=0; xi < w; ++xi )
		{
			r = *s;
			k = qRgba(QMIN(qRound(0.3 * qRed(r) + 0.59 * qGreen(r) + 0.11 * qBlue(r)), 255), 0, 0, 0);
			*s = k;
			imgArray[i++] = k;
			s++;
		}
	}
	return imgArray;
}

QByteArray ScImage::ImageToCMYK_PDF(bool pre)
{
	int i = 0;
	int h = height();
	int w = width();
	QRgb *s;
	QRgb r;
	int c, m, y, k;
	QByteArray imgArray( 4 * h * w );
	if (pre)
	{
		for( int yi=0; yi < h; ++yi )
		{
			s = (QRgb*)(scanLine( yi ));
			for( int xi=0; xi < w; ++xi )
			{
				r = *s;
				imgArray[i++] = static_cast<unsigned char> (qRed(r));
				imgArray[i++] = static_cast<unsigned char> (qGreen(r));
				imgArray[i++] = static_cast<unsigned char> (qBlue(r));
				imgArray[i++] = static_cast<unsigned char> (qAlpha(r));
				s++;
			}
		}
	}
	else
	{
		for( int yi=0; yi < h; ++yi )
		{
			s = (QRgb*)(scanLine( yi ));
			for( int xi=0; xi < w; ++xi )
			{
				r = *s;
				c = 255 - qRed(r);
				m = 255 - qGreen(r);
				y = 255 - qBlue(r);
				k = QMIN(QMIN(c, m), y);
				imgArray[i++] = static_cast<unsigned char> (c - k);
				imgArray[i++] = static_cast<unsigned char> (m - k);
				imgArray[i++] = static_cast<unsigned char> (y - k);
				imgArray[i++] = static_cast<unsigned char> (k);
				s++;
			}
		}
	}
	return imgArray;
}

QByteArray ScImage::ImageToCMYK_PS(int pl, bool pre)
{
	int i = 0;
	int h = height();
	int w = width();
	QByteArray imgArray;
	QRgb *s;
	QRgb r;
	int c, m, y, k;
	if(pl == -1)
		imgArray.resize(4 * h * w);
	else
		imgArray.resize(h * w);
	if (pre)
	{
		for( int yi=0; yi < h; ++yi )
		{
			s = (QRgb*)(scanLine( yi ));
			for( int xi=0; xi < w; ++xi )
			{
				r = *s++;
				c = qRed(r);
				m = qGreen(r);
				y = qBlue(r);
				k = qAlpha(r);
				if (pl == -1)
				{
					imgArray[i++] = static_cast<unsigned char> (c);
					imgArray[i++] = static_cast<unsigned char> (m);
					imgArray[i++] = static_cast<unsigned char> (y);
					imgArray[i++] = static_cast<unsigned char> (k);
				}
				else
				{
					if (pl == -2)
						imgArray[i++] = static_cast<unsigned char> (QMIN(255, qRound(0.3 * c + 0.59 * m + 0.11 * y + k)));
					if (pl == 1)
						imgArray[i++] = static_cast<unsigned char> (c);
					if (pl == 2)
						imgArray[i++] = static_cast<unsigned char> (m);
					if (pl == 3)
						imgArray[i++] = static_cast<unsigned char> (y);
					if (pl == 0)
						imgArray[i++] = static_cast<unsigned char> (k);
				}
			}
		}
	}
	else
	{
		for( int yi=0; yi < h; ++yi )
		{
			s = (QRgb*)(scanLine( yi ));
			for( int xi=0; xi < w; ++xi )
			{
				r = *s++;
				c = 255 - qRed(r);
				m = 255 - qGreen(r);
				y = 255 - qBlue(r);
				k = QMIN(QMIN(c, m), y);
				if (pl == -1)
				{
					imgArray[i++] = static_cast<unsigned char> (c - k);
					imgArray[i++] = static_cast<unsigned char> (m - k);
					imgArray[i++] = static_cast<unsigned char> (y - k);
					imgArray[i++] = static_cast<unsigned char> (k);
				}
				else
				{
					if (pl == -2)
						imgArray[i++] = static_cast<unsigned char> (QMIN(255, qRound(0.3 * c + 0.59 * m + 0.11 * y + k)));
					if (pl == 1)
						imgArray[i++] = static_cast<unsigned char> (c - k);
					if (pl == 2)
						imgArray[i++] = static_cast<unsigned char> (m - k);
					if (pl == 3)
						imgArray[i++] = static_cast<unsigned char> (y - k);
					if (pl == 0)
						imgArray[i++] = static_cast<unsigned char> (k);
				}
			}
		}
	}
	return imgArray;
}

void ScImage::scaleImage(int nwidth, int nheight)
{
	QImage dst;
	dst.create(nwidth, nheight,32);
	QRgb* xelrow = 0;
	QRgb* tempxelrow = 0;
	register QRgb* xP;
	register QRgb* nxP;
	int rows, cols, rowsread, newrows, newcols;
	register int row, col, needtoreadrow;
	const uchar maxval = 255;
	double xscale, yscale;
	long sxscale, syscale;
	register long fracrowtofill, fracrowleft;
	long* as;
	long* rs;
	long* gs;
	long* bs;
	int rowswritten = 0;
	cols = width();
	rows = height();
	newcols = dst.width();
	newrows = dst.height();
	long SCALE;
	long HALFSCALE;
	if (cols > 4096)
	{
		SCALE = 4096;
		HALFSCALE = 2048;
	}
	else
	{
		int fac = 4096;
		while (cols * fac > 4096)
		{
			fac /= 2;
		}
		SCALE = fac * cols;
		HALFSCALE = fac * cols / 2;
	}
	xscale = (double) newcols / (double) cols;
	yscale = (double) newrows / (double) rows;
	sxscale = (long)(xscale * SCALE);
	syscale = (long)(yscale * SCALE);
	if ( newrows != rows )	/* shortcut Y scaling if possible */
		tempxelrow = new QRgb[cols];
	as = new long[cols];
	rs = new long[cols];
	gs = new long[cols];
	bs = new long[cols];
	rowsread = 0;
	fracrowleft = syscale;
	needtoreadrow = 1;
	for ( col = 0; col < cols; ++col )
		rs[col] = gs[col] =  as[col] = bs[col] = HALFSCALE;
	fracrowtofill = SCALE;
	for ( row = 0; row < newrows; ++row )
	{
		if ( newrows == rows )
			tempxelrow = xelrow = (QRgb*)scanLine(rowsread++);
		else
		{
			while ( fracrowleft < fracrowtofill )
			{
				if ( needtoreadrow && rowsread < rows )
					xelrow = (QRgb*)scanLine(rowsread++);
				for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
				{
					as[col] += fracrowleft * qAlpha( *xP );
					rs[col] += fracrowleft * qRed( *xP );
					gs[col] += fracrowleft * qGreen( *xP );
					bs[col] += fracrowleft * qBlue( *xP );
				}
				fracrowtofill -= fracrowleft;
				fracrowleft = syscale;
				needtoreadrow = 1;
			}
			if ( needtoreadrow && rowsread < rows )
			{
				xelrow = (QRgb*)scanLine(rowsread++);
				needtoreadrow = 0;
			}
			register long a=0;
			for ( col = 0, xP = xelrow, nxP = tempxelrow; col < cols; ++col, ++xP, ++nxP )
			{
				register long r, g, b;
				a = as[col] + fracrowtofill * qAlpha( *xP );
				r = rs[col] + fracrowtofill * qRed( *xP );
				g = gs[col] + fracrowtofill * qGreen( *xP );
				b = bs[col] + fracrowtofill * qBlue( *xP );
				r /= SCALE;
				if ( r > maxval ) r = maxval;
				g /= SCALE;
				if ( g > maxval ) g = maxval;
				b /= SCALE;
				if ( b > maxval ) b = maxval;
				a /= SCALE;
				if ( a > maxval ) a = maxval;
				*nxP = qRgba( (int)r, (int)g, (int)b , (int)a);
				rs[col] = as[col] = gs[col] = bs[col] = HALFSCALE;
			}
			fracrowleft -= fracrowtofill;
			if ( fracrowleft == 0 )
			{
				fracrowleft = syscale;
				needtoreadrow = 1;
			}
			fracrowtofill = SCALE;
		}
		if ( newcols == cols )
			memcpy(dst.scanLine(rowswritten++), tempxelrow, newcols*4);
		else
		{
			register long a, r, g, b;
			register long fraccoltofill, fraccolleft = 0;
			register int needcol;
			nxP = (QRgb*)dst.scanLine(rowswritten++);
			fraccoltofill = SCALE;
			a = r = g = b = HALFSCALE;
			needcol = 0;
			for ( col = 0, xP = tempxelrow; col < cols; ++col, ++xP )
			{
				fraccolleft = sxscale;
				while ( fraccolleft >= fraccoltofill )
				{
					if ( needcol )
					{
						++nxP;
						a = r = g = b = HALFSCALE;
					}
					a += fraccoltofill * qAlpha( *xP );
					r += fraccoltofill * qRed( *xP );
					g += fraccoltofill * qGreen( *xP );
					b += fraccoltofill * qBlue( *xP );
					r /= SCALE;
					if ( r > maxval ) r = maxval;
					g /= SCALE;
					if ( g > maxval ) g = maxval;
					b /= SCALE;
					if ( b > maxval ) b = maxval;
					a /= SCALE;
					if ( a > maxval ) a = maxval;
					*nxP = qRgba( (int)r, (int)g, (int)b, (int)a );
					fraccolleft -= fraccoltofill;
					fraccoltofill = SCALE;
					needcol = 1;
				}
				if ( fraccolleft > 0 )
				{
					if ( needcol )
					{
						++nxP;
						a = r = g = b = HALFSCALE;
						needcol = 0;
					}
					a += fraccolleft * qAlpha( *xP );
					r += fraccolleft * qRed( *xP );
					g += fraccolleft * qGreen( *xP );
					b += fraccolleft * qBlue( *xP );
					fraccoltofill -= fraccolleft;
				}
			}
			if ( fraccoltofill > 0 )
			{
				--xP;
				a += fraccolleft * qAlpha( *xP );
				r += fraccoltofill * qRed( *xP );
				g += fraccoltofill * qGreen( *xP );
				b += fraccoltofill * qBlue( *xP );
			}
			if ( ! needcol )
			{
				r /= SCALE;
				if ( r > maxval ) r = maxval;
				g /= SCALE;
				if ( g > maxval ) g = maxval;
				b /= SCALE;
				if ( b > maxval ) b = maxval;
				a /= SCALE;
				if ( a > maxval ) a = maxval;
				*nxP = qRgba( (int)r, (int)g, (int)b, (int)a );
			}
		}
	}
	if ( newrows != rows && tempxelrow )// Robust, tempxelrow might be 0 1 day
		delete [] tempxelrow;
	if ( as )				// Avoid purify complaint
		delete [] as;
	if ( rs )				// Robust, rs might be 0 one day
		delete [] rs;
	if ( gs )				// Robust, gs might be 0 one day
		delete [] gs;
	if ( bs )				// Robust, bs might be 0 one day
		delete [] bs;
	create(nwidth, nheight,32);
	for( int yi=0; yi < dst.height(); ++yi )
	{
		QRgb *s = (QRgb*)(dst.scanLine( yi ));
		QRgb *d = (QRgb*)(scanLine( yi ));
		for(int xi=0; xi < dst.width(); ++xi )
		{
			(*d) = (*s);
			s++;
			d++;
		}
	}
	return;
}

QByteArray ScImage::getAlpha(QString fn, bool PDF, bool pdf14, int gsRes)
{
	QByteArray retArray;
	ScImgDataLoader* pDataLoader = NULL;
	imgInfo.valid = false;
	imgInfo.clipPath = "";
	imgInfo.PDSpathData.clear();
	imgInfo.layerInfo.clear();
	QFileInfo fi = QFileInfo(fn);
	if (!fi.exists())
		return retArray;
	QString tmp, BBox, tmp2;
	QString ext = fi.extension(false).lower();
	if ((ext == "jpg") || (ext == "jpeg"))
		return retArray;
	if (ext == "pdf")
		pDataLoader = new ScImgDataLoader_PDF();
	else if ((ext == "eps") || (ext == "ps"))
		pDataLoader = new ScImgDataLoader_PS();
	else if ((ext == "tif") || (ext == "tiff"))
	{
		pDataLoader = new ScImgDataLoader_TIFF();
		if	(pDataLoader)
			pDataLoader->setRequest(imgInfo.isRequest, imgInfo.RequestProps);
	}
	else if (ext == "psd")
	{
		pDataLoader = new ScImgDataLoader_PSD();
		if	(pDataLoader)
			pDataLoader->setRequest(imgInfo.isRequest, imgInfo.RequestProps);
	}
	else
		pDataLoader = new ScImgDataLoader_QT();

	if	(pDataLoader)
	{
		pDataLoader->preloadAlphaChannel(fn, gsRes);
		QImage rImage;
		if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
		{
			if ((pDataLoader->r_image.channels() == 5) || (pDataLoader->imageInfoRecord().colorspace == 1))
				rImage = pDataLoader->r_image.convertToQImage(true);
			else
				rImage = pDataLoader->r_image.convertToQImage(false);
		}
		else
			rImage = pDataLoader->image();
		if (rImage.isNull())
		{
			delete pDataLoader;
			return retArray;
		}
		int i = 0;
		unsigned char u;
		int hm = rImage.height();
		int wm = rImage.width();
		int w2;
		QRgb *s;
		QRgb r;
		if (pdf14)
		{
			retArray.resize(hm * wm);
			for( int yi=0; yi < hm; ++yi )
			{
				s = (QRgb*)(rImage.scanLine( yi ));
				for( int xi=0; xi < wm; ++xi )
				{
					r = *s++;
					u=qAlpha(r);
					retArray[i++] = u;
				}
			}
		}
		else
		{
			QImage iMask = rImage.createAlphaMask();
			hm = iMask.height();
			wm = iMask.width();
			w2 = wm / 8;
			if ((wm % 8) != 0)
				w2++;
			retArray.resize(hm * w2);
			uchar * s;
			for( int yi=0; yi < hm; ++yi )
			{
				s = iMask.scanLine( yi );
				for( int xi=0; xi < w2; ++xi )
				{
					u = *(s+xi);
					if(PDF) u = ~u;
					retArray[i++] = u;
				}
			}
		}
		delete pDataLoader;
	}
	return retArray;
}

void ScImage::getEmbeddedProfile(const QString & fn, QByteArray *profile, int *components)
{
	Q_ASSERT(profile);
	Q_ASSERT(components);
	ScImgDataLoader* pDataLoader = NULL;
	cmsHPROFILE prof = 0;

	profile->resize(0);
	*components = 0;
	QFileInfo fi = QFileInfo(fn);
	if (!fi.exists())
		return;
	QString ext = fi.extension(false).lower();

	if (ext == "psd")
		pDataLoader = new ScImgDataLoader_PSD();
	else if (ext == "eps")
		pDataLoader = new ScImgDataLoader_PS();
	else if ((ext == "tif") || (ext == "tiff"))
		pDataLoader = new ScImgDataLoader_TIFF();
	else if ((ext == "jpg") || (ext == "jpeg"))
		pDataLoader = new ScImgDataLoader_JPEG();

	if	(pDataLoader)
	{
		pDataLoader->loadEmbeddedProfile(fn);
		QByteArray embeddedProfile = pDataLoader->embeddedProfile();
		if	(embeddedProfile.size())
		{
			prof = cmsOpenProfileFromMem(embeddedProfile.data(), embeddedProfile.size());
			if (prof)
			{
				if (static_cast<int>(cmsGetColorSpace(prof)) == icSigRgbData)
					*components = 3;
				if (static_cast<int>(cmsGetColorSpace(prof)) == icSigCmykData)
					*components = 4;
				*profile = embeddedProfile;
			}
			cmsCloseProfile(prof);
		}
		delete pDataLoader;
	}
}

bool ScImage::LoadPicture(const QString & fn, const CMSettings& cmSettings,
						  bool useEmbedded, bool useProf, RequestType requestType,
						  int gsRes, bool *realCMYK, bool showMsg)
{
	// requestType - 0: CMYK, 1: RGB, 2: RGB Proof 3 : RawData, 4: Thumbnail
	// gsRes - is the resolution that ghostscript will render at
	bool isCMYK = false;
	bool ret = false;
	if (realCMYK != 0)
		*realCMYK = false;
	bool bilevel = false;
//	short resolutionunit = 0;
	RequestType reqType = requestType;
	cmsHTRANSFORM xform = 0;
	cmsHPROFILE inputProf = 0;
	int cmsFlags = 0;
	auto_ptr<ScImgDataLoader> pDataLoader;
	QFileInfo fi = QFileInfo(fn);
	if (!fi.exists())
		return ret;
	QString ext = fi.extension(false).lower();
	QString tmp, dummy, cmd1, cmd2, BBox, tmp2;
	QChar tc;
//	bool found = false;

	if (ext.isEmpty())
		ext = getImageType(fn);

	if (ext == "pdf")
		pDataLoader.reset( new ScImgDataLoader_PDF() );
	else if ((ext == "eps") || (ext == "ps"))
		pDataLoader.reset( new ScImgDataLoader_PS() );
	else if ((ext == "tif") || (ext == "tiff"))
	{
		pDataLoader.reset( new ScImgDataLoader_TIFF() );
		pDataLoader->setRequest(imgInfo.isRequest, imgInfo.RequestProps);
	}
	else if (ext == "psd")
	{
		pDataLoader.reset( new ScImgDataLoader_PSD() );
		pDataLoader->setRequest(imgInfo.isRequest, imgInfo.RequestProps);
	}
	else if ((ext == "jpg") || (ext == "jpeg"))
		pDataLoader.reset( new ScImgDataLoader_JPEG() );
	else if (ext == "pat")
		pDataLoader.reset( new ScImgDataLoader_GIMP() );
	else
		pDataLoader.reset( new ScImgDataLoader_QT() );

	if	(pDataLoader->loadPicture(fn, gsRes, (requestType == Thumbnail)))
	{
		*this = pDataLoader->image();
		imgInfo = pDataLoader->imageInfoRecord();
		if (requestType == Thumbnail)
			reqType = RGBData;
		if (!cmSettings.useColorManagement() || !useProf)
		{
			imgInfo.isEmbedded = false;
			imgInfo.profileName = "";
		}
		if (imgInfo.colorspace == 1)
		{
			isCMYK = true;
			if(realCMYK)
				*realCMYK = true;
		}
		else if (imgInfo.colorspace == 2)
			bilevel = true;
		pDataLoader->image() = QImage();
	}
	else
	{
		if	(ScCore->usingGUI() && pDataLoader->issuedErrorMsg() && showMsg)
		{
			QMessageBox::critical(ScCore->primaryMainWindow(), CommonStrings::trWarning, pDataLoader->getMessage(), 1, 0, 0);
		}
		else if (pDataLoader->issuedErrorMsg())
		{
			QString msg = pDataLoader->getMessage();
			qWarning( msg.local8Bit().data() );
		}
		return false;
	}

	if (!((ext == "psd") || (ext == "tif") || (ext == "tiff")))
	{
		if (isNull())
			return  ret;
	}

	QByteArray embeddedProfile = pDataLoader->embeddedProfile();
	if (cmSettings.useColorManagement() && useProf)
	{
		if (embeddedProfile.size() > 0 )
		{
			inputProf = cmsOpenProfileFromMem(embeddedProfile.data(), embeddedProfile.size());
		}
		else
		{
			QCString profilePath;
			//CB If this is null, customfiledialog/picsearch/ScPreview might be sending it
			Q_ASSERT(cmSettings.doc()!=0);
			if (isCMYK)
			{
				if (ScCore->InputProfilesCMYK.contains(cmSettings.profileName()))
					imgInfo.profileName = cmSettings.profileName();
				else
					imgInfo.profileName = cmSettings.doc()->CMSSettings.DefaultImageCMYKProfile;
				profilePath = ScCore->InputProfilesCMYK[imgInfo.profileName].local8Bit();
			}
			else
			{
				if (ScCore->InputProfiles.contains(cmSettings.profileName()))
					imgInfo.profileName = cmSettings.profileName();
				else
					imgInfo.profileName = cmSettings.doc()->CMSSettings.DefaultImageRGBProfile;
				profilePath = ScCore->InputProfiles[imgInfo.profileName].local8Bit();
			}
			inputProf = cmsOpenProfileFromFile(profilePath.data(), "r");
		}
	}
	if (cmSettings.useColorManagement() && useProf && inputProf)
	{
		DWORD inputProfFormat = TYPE_RGBA_8;
		DWORD outputProfFormat = TYPE_CMYK_8;
		int inputProfColorSpace = static_cast<int>(cmsGetColorSpace(inputProf));
		if ( inputProfColorSpace == icSigRgbData )
			inputProfFormat = TYPE_RGBA_8;
		else if (( inputProfColorSpace == icSigCmykData ) && ((ext == "psd") || (ext == "tif") || (ext == "tiff")))
		{
			if (pDataLoader->r_image.channels() == 5)
				inputProfFormat = (COLORSPACE_SH(PT_CMYK)|EXTRA_SH(1)|CHANNELS_SH(4)|BYTES_SH(1));
			else
				inputProfFormat = TYPE_CMYK_8;
		}
		else if ( inputProfColorSpace == icSigCmykData )
			inputProfFormat = TYPE_CMYK_8;
		else if ( inputProfColorSpace == icSigGrayData )
			inputProfFormat = TYPE_GRAY_8;
		int outputProfColorSpace = static_cast<int>(cmsGetColorSpace(cmSettings.printerProfile()));
		if ( outputProfColorSpace == icSigRgbData )
			outputProfFormat = TYPE_RGBA_8;
		else if ( outputProfColorSpace == icSigCmykData )
			outputProfFormat = TYPE_CMYK_8;
		if (cmSettings.doSoftProofing())
		{
			cmsFlags |= cmsFLAGS_SOFTPROOFING;
			if (cmSettings.doGamutCheck())
				cmsFlags |= cmsFLAGS_GAMUTCHECK;
		}
		if (cmSettings.useBlackPoint())
			cmsFlags |= cmsFLAGS_BLACKPOINTCOMPENSATION;
		switch (reqType)
		{
		case CMYKData: // CMYK
//			if ((!isCMYK && (outputProfColorSpace == icSigCmykData)) || (isCMYK && (outputProfColorSpace == icSigRgbData)) )
				xform = scCmsCreateTransform(inputProf, inputProfFormat, cmSettings.printerProfile(), outputProfFormat, cmSettings.imageRenderingIntent(), 0);
			if (outputProfColorSpace != icSigCmykData )
				*realCMYK = isCMYK = false;
			break;
		case Thumbnail:
		case RGBData: // RGB
			if (isCMYK)
				xform = scCmsCreateTransform(inputProf, inputProfFormat, cmSettings.monitorProfile(), TYPE_RGBA_8, cmSettings.intent(), 0);
			else
			{
				if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
				{
					*this = pDataLoader->r_image.convertToQImage(false);
					imgInfo = pDataLoader->imageInfoRecord();
				}
			}
			break;
		case RGBProof: // RGB Proof
			{
				if (!((ext == "psd") || (ext == "tif") || (ext == "tiff")))
				{
					if (inputProfFormat == TYPE_CMYK_8)
						inputProfFormat = (COLORSPACE_SH(PT_CMYK)|CHANNELS_SH(4)|BYTES_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1));//TYPE_YMCK_8;
					else if(inputProfFormat == TYPE_RGBA_8)
						inputProfFormat = TYPE_BGRA_8;
				}
				if (cmSettings.doSoftProofing())
				{
					xform = scCmsCreateProofingTransform(inputProf, inputProfFormat,
					                     cmSettings.monitorProfile(), TYPE_BGRA_8, cmSettings.printerProfile(),
					                     cmSettings.intent(), INTENT_RELATIVE_COLORIMETRIC, cmsFlags);
				}
				else
					xform = scCmsCreateTransform(inputProf, inputProfFormat, cmSettings.monitorProfile(), 
										 TYPE_BGRA_8, cmSettings.intent(), cmsFlags);
			}
			break;
		case RawData: // no Conversion just raw Data
			xform = 0;
			if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
			{
				*this = pDataLoader->r_image.convertToQImage(true, true);
				imgInfo = pDataLoader->imageInfoRecord();
			}
			break;
		}
		if (xform)
		{
			if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
			{
				create(pDataLoader->r_image.width(), pDataLoader->r_image.height(), 32);
				setAlphaBuffer( true );
				imgInfo = pDataLoader->imageInfoRecord();
			}
			LPBYTE ptr2;
			for (int i = 0; i < height(); i++)
			{
				LPBYTE ptr = scanLine(i);
				if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
					ptr2 = pDataLoader->r_image.scanLine(i);
				if ( inputProfFormat == TYPE_GRAY_8 && (reqType != CMYKData) )
				{
					unsigned char* ucs = ptr + 1;
					unsigned char* uc = new unsigned char[width()];
					for( int uci = 0; uci < width(); uci++ )
					{
						uc[uci] = *ucs;
						ucs += 4;
					}
					cmsDoTransform(xform, uc, ptr, width());
					delete[] uc;
				}
				else if ( inputProfFormat == TYPE_GRAY_8 && (reqType == CMYKData) )
				{
					unsigned char  value;
					unsigned char* ucs = ptr;
					for( int uci = 0; uci < width(); uci++ )
					{
						value = 255 - *(ucs + 1);
						ucs[0] = ucs[1] = ucs[2] = 0;
						ucs[3] = value;
						ucs += 4;
					}
				}
				else
				{
					if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
						cmsDoTransform(xform, ptr2, ptr,width());
					else
						cmsDoTransform(xform, ptr, ptr, width());
				}
				// if transforming from CMYK to RGB, flatten the alpha channel
				// which will still contain the black channel
				if (!((ext == "psd") || (ext == "tif") || (ext == "tiff")))
				{
					QRgb alphaFF = qRgba(0,0,0,255);
					QRgb *p;
					if (isCMYK && reqType != CMYKData && !bilevel)
					{
						p = (QRgb *) ptr;
						for (int j = 0; j < width(); j++, p++)
							*p |= alphaFF;
					}
				}
				else
				{
					if (reqType != CMYKData && !bilevel)
					{
						if (pDataLoader->r_image.channels() == 5)
						{
							QRgb *p = (QRgb *) ptr;
							for (int j = 0; j < width(); j++, p++)
							{
								*p = qRgba(qRed(*p), qGreen(*p), qBlue(*p), ptr2[4]);
								ptr2 += 5;
							}
						}
						else
						{
							QRgb *p = (QRgb *) ptr;
							for (int j = 0; j < width(); j++, p++)
							{
								if (isCMYK)
									*p = qRgba(qRed(*p), qGreen(*p), qBlue(*p), 255);
								else
									*p = qRgba(qRed(*p), qGreen(*p), qBlue(*p), ptr2[3]);
								ptr2 += 4;
							}
						}
					}
				}
			}
			cmsDeleteTransform (xform);
		}
		if (inputProf)
			cmsCloseProfile(inputProf);
	}
	else
	{
		switch (reqType)
		{
		case CMYKData:
			if (!isCMYK)
			{
				if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
				{
					*this = pDataLoader->r_image.convertToQImage(false);
					imgInfo = pDataLoader->imageInfoRecord();
				}
				unsigned char cc, cm, cy ,ck;
				QRgb *ptr;
				for (int i = 0; i < height(); i++)
				{
					ptr = (QRgb *) scanLine(i);
					for (int j = 0; j < width(); j++)
					{
						cc = 255 - qRed(*ptr);
						cm = 255 - qGreen(*ptr);
						cy = 255 - qBlue(*ptr);
						ck = QMIN(QMIN(cc, cm), cy);
						*ptr++ = qRgba(cc-ck,cm-ck,cy-ck,ck);
					}
				}
			}
			else
			{
				if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
				{
					*this = pDataLoader->r_image.convertToQImage(true, true);
					imgInfo = pDataLoader->imageInfoRecord();
				}
			}
			break;
		case RGBData:
		case RGBProof:
		case Thumbnail:
			if (isCMYK)
			{
				if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
				{
					*this = pDataLoader->r_image.convertToQImage(true);
					imgInfo = pDataLoader->imageInfoRecord();
				}
				else
				{
					unsigned char cr, cg, cb, ck;
					QRgb *ptr;
					for (int i = 0; i < height(); i++)
					{
						ptr = (QRgb *) scanLine(i);
						for (int j = 0; j < width(); j++)
						{
							ck = qAlpha(*ptr);
							cr = 255 - QMIN(255, qRed(*ptr) + ck);
							cg = 255 - QMIN(255, qGreen(*ptr) + ck);
							cb = 255 - QMIN(255, qBlue(*ptr) + ck);
							*ptr++ = qRgba(cr,cg,cb,255);
						}
					}
				}
			}
			else
			{
				if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
				{
					*this = pDataLoader->r_image.convertToQImage(false);
					imgInfo = pDataLoader->imageInfoRecord();
				}
			}
			break;
		case RawData:
				if ((ext == "psd") || (ext == "tif") || (ext == "tiff"))
				{
					*this = pDataLoader->r_image.convertToQImage(true, true);
					imgInfo = pDataLoader->imageInfoRecord();
				}
			break;
		}
	}
	if (((reqType == CMYKData) || ((reqType == RawData) && isCMYK)) && !bilevel)
		setAlphaBuffer(false);
	setDotsPerMeterX (QMAX(2834, (int) (imgInfo.xres / 0.0254)));
	setDotsPerMeterY (QMAX(2834, (int) (imgInfo.yres / 0.0254)));
	if	(ScCore->usingGUI() && pDataLoader->issuedWarningMsg() && showMsg)
	{
		QMessageBox::warning(ScCore->primaryMainWindow(), CommonStrings::trWarning, pDataLoader->getMessage(), 1, 0, 0);
	}
	else if (pDataLoader->issuedErrorMsg())
	{
		QString msg = pDataLoader->getMessage();
		qWarning( msg.local8Bit().data() );
	}
	return true;
}
