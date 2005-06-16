//
//  Little cms - profiler construction set
//  Copyright (C) 1998-2001 Marti Maria
//
// THIS SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
// EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
// WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL MARTI MARIA BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
// INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
// OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
// LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
// This file is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// As a special exception to the GNU General Public License, if you
// distribute this file as part of a program that contains a
// configuration script generated by Autoconf, you may include it under
// the same distribution terms that you use for the rest of that program.
//
// Version 1.09a
//
// Incremental Interpolator

#include "lcmsprf.h"


// Res points to a result in XYZ or Lab

BOOL cdecl cmsxRegressionInterpolatorRGB(LPMEASUREMENT m,
                                       int ColorSpace,
                                       int    RegressionTerms,
                                       BOOL   lUseLocalPatches,
                                       int    MinPatchesToCollect,
                                       double r, double g, double b,
                                       void* Res);


// -------------------------------------------------------------- Implementation

// #define DEBUG 1

// Estimate regression matrix
static
void EstimateRegression(LPMEASUREMENT m, double r, double g, double b,
                                        int ColorSpace,
                                        LPMATN* ptfm,                                        
                                        int nterms,
                                        BOOL lIncludeAllPatches,
                                        int MinPatchesToCollect)
{
    int nCollected;
    MLRSTATISTICS maxAns;
    int ToCollect;
    SETOFPATCHES collected = cmsxPCollBuildSet(m, FALSE);
    SETOFPATCHES allowed   = cmsxPCollBuildSet(m, TRUE);
    BOOL rc;
    BOOL lPatchesExhausted = FALSE;


    CopyMemory(allowed, m -> Allowed, m->nPatches*sizeof(BOOL));

    *ptfm = NULL;

    ToCollect = max(MinPatchesToCollect, (nterms + 1));

    do {

                if (lIncludeAllPatches) {

                        CopyMemory(collected, allowed, m->nPatches*sizeof(BOOL));
                        lPatchesExhausted = TRUE;
                        ToCollect = nCollected = m->nPatches;
                }
                else
                {

                nCollected =  cmsxPCollPatchesNearRGB(m, m -> Allowed,
                                                            r, g, b,
                                                            ToCollect, collected);

                if (nCollected < ToCollect) {           // No more patches available
                        lPatchesExhausted = TRUE;
                }
                else    {
                        ToCollect = nCollected + 1;     // Start from here in next iteration
                }
        }

        // We are going always 3 -> 3 for now....
        rc = cmsxRegressionCreateMatrix(m, collected, nterms, ColorSpace, ptfm, &maxAns);


        // Does fit?
        if ((rc == FALSE) || maxAns.R2adj < 0.95 ||  maxAns.R2adj > 1.0) {

                maxAns.R2adj = -100;  // No, repeat              
        }
	

    } while (!lPatchesExhausted && maxAns.R2adj < 0.95);

#ifdef DEBUG
        printf("R2adj: %g, F: %g\n", maxAns.R2adj, maxAns.F);
#endif

    free(collected);
    free(allowed);
}



BOOL cmsxRegressionInterpolatorRGB(LPMEASUREMENT m,
                                       int ColorSpace,                                       
                                       int    RegressionTerms,
                                       BOOL   lUseLocalPatches,
                                       int    MinPatchesToCollect,
                                       double r, double g, double b,
                                       void* Res)
{
    LPMATN   tfm = NULL;

            
	EstimateRegression(m, r, g, b, ColorSpace, &tfm, RegressionTerms, 
									!lUseLocalPatches, MinPatchesToCollect);

	if (tfm == NULL) return FALSE; 

    switch (ColorSpace) {

        case PT_Lab:

                if (!cmsxRegressionRGB2Lab(r, g, b, tfm, (LPcmsCIELab) Res)) return FALSE;
                break;

        case PT_XYZ:
                if (!cmsxRegressionRGB2XYZ(r, g, b, tfm, (LPcmsCIEXYZ) Res)) return FALSE;
                break;

        default:
                return FALSE;
        }

        MATNfree(tfm);


#ifdef DEBUG
    printf("INTERPOLATED RGB %g,%g,%g Lab %g, %g, %g \n", r , g,  b,
            Lab->L, Lab->a, Lab->b);

#endif
    return TRUE;
}


// Check the results of a given regression matrix

static
void CheckOneRegressionMatrix(LPPROFILERCOMMONDATA hdr, LPMATN Matrix, 
										double* Mean, double* Std, double* Max)
{

    cmsCIELab Lab;
    cmsCIEXYZ XYZ;
    double Hit, sum, sum2, n, dE;
    int i;
	cmsCIEXYZ D50;


	D50.X = cmsD50_XYZ() -> X* 100.;
	D50.Y = cmsD50_XYZ() -> Y* 100.;
	D50.Z = cmsD50_XYZ() -> Z* 100.;

    Hit = sum = sum2 = n = 0;
    for (i=0; i < hdr -> m.nPatches; i++) {

        if (hdr -> m.Allowed[i]) {

            LPPATCH p = hdr -> m.Patches + i;

            if (hdr -> PCSType == PT_Lab) {

                    WORD ProfileLabEncoded[3];

                    cmsxRegressionRGB2Lab(p -> Colorant.RGB[0], 
                                        p -> Colorant.RGB[1],
                                        p -> Colorant.RGB[2],
                                        Matrix, &Lab);

                    cmsFloat2LabEncoded(ProfileLabEncoded, &Lab);
                    cmsLabEncoded2Float(&Lab, ProfileLabEncoded);

                    dE = cmsDeltaE(&Lab, &p ->Lab);
            }
            else {
                    cmsCIELab Lab2;

                    cmsxRegressionRGB2XYZ(p -> Colorant.RGB[0], 
                                        p -> Colorant.RGB[1],
                                        p -> Colorant.RGB[2],
                                        Matrix, &XYZ);
					_cmsxClampXYZ100(&XYZ);

                    cmsXYZ2Lab(&D50, &Lab, &XYZ);
                    cmsXYZ2Lab(&D50, &Lab2, &p ->XYZ);

                    dE = cmsDeltaE(&Lab, &Lab2);
            }


            if (dE > Hit)
                Hit = dE;

            sum  += dE;
            sum2 += dE * dE;
            n = n + 1;

        }
    }

    *Mean = sum / n;
    *Std  = sqrt((n * sum2 - sum * sum) / (n*(n-1)));
    *Max  = Hit;

}


// Trial-and-error in order to get best number of terms.

int cmsxFindOptimumNumOfTerms(LPPROFILERCOMMONDATA hdr, int nMaxTerms, BOOL* lAllOk)
{
    int i, BestTerms;
    BOOL rc;
    LPMATN Matrix = NULL;
    MLRSTATISTICS Stat;
    double dEmean, dEStd, dEHit, Best;
    BOOL lOneFound;
	

    BestTerms = 4;
    Best = 1000.;
    lOneFound = FALSE;

    for (i=4; i <= nMaxTerms; i++) {		// 55

            rc = cmsxRegressionCreateMatrix(&hdr -> m, hdr -> m.Allowed, 
                                       i, hdr -> PCSType, &Matrix, &Stat);

            if (rc && Stat.R2adj < 1 && Stat.R2adj > 0.6) {
                
                CheckOneRegressionMatrix(hdr, Matrix, &dEmean, &dEStd, &dEHit);

                if (dEStd < Best && dEHit < 50.) {

                        Best = dEStd;
                        BestTerms = i;
                        lOneFound = TRUE;
                }

            }
        MATNfree(Matrix);
        Matrix = NULL;
    }

    *lAllOk = lOneFound;
	
    return BestTerms;
}


