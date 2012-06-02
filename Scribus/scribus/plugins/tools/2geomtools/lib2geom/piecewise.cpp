/*
 * piecewise.cpp - Piecewise function class
 *
 * Copyright 2007 Michael Sloan <mgsloan@gmail.com>
 * Copyright 2007 JF Barraud
 *
 * This library is free software; you can redistribute it and/or
 * modify it either under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * (the "LGPL") or, at your option, under the terms of the Mozilla
 * Public License Version 1.1 (the "MPL"). If you do not alter this
 * notice, a recipient may use your version of this file under either
 * the MPL or the LGPL.
 *
 * You should have received a copy of the LGPL along with this library
 * in the file COPYING-LGPL-2.1; if not, output to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * You should have received a copy of the MPL along with this library
 * in the file COPYING-MPL-1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
 * OF ANY KIND, either express or implied. See the LGPL or the MPL for
 * the specific language governing rights and limitations.
 *
 */

#include "piecewise.h"
#include <iterator>
#include <map>

namespace Geom {

Piecewise<SBasis> divide(Piecewise<SBasis> const &a, Piecewise<SBasis> const &b, unsigned k) {
    Piecewise<SBasis> pa = partition(a, b.cuts), pb = partition(b, a.cuts);
    Piecewise<SBasis> ret = Piecewise<SBasis>();
    assert(pa.size() == pb.size());
    ret.cuts = pa.cuts;
    for (unsigned i = 0; i < pa.size(); i++)
        ret.push_seg(divide(pa[i], pb[i], k));
    return ret;
}

Piecewise<SBasis> 
divide(Piecewise<SBasis> const &a, Piecewise<SBasis> const &b, double tol, unsigned k, double zero) {
    Piecewise<SBasis> pa = partition(a, b.cuts), pb = partition(b, a.cuts);
    Piecewise<SBasis> ret = Piecewise<SBasis>();
    assert(pa.size() == pb.size());
    for (unsigned i = 0; i < pa.size(); i++){
        Piecewise<SBasis> divi = divide(pa[i], pb[i], tol, k, zero);
        divi.setDomain(Interval(pa.cuts[i],pa.cuts[i+1]));
        ret.concat(divi);
    }
    return ret;
}
Piecewise<SBasis> divide(Piecewise<SBasis> const &a, SBasis const &b, double tol, unsigned k, double zero){
    return divide(a,Piecewise<SBasis>(b),tol,k,zero);
}
Piecewise<SBasis> divide(SBasis const &a, Piecewise<SBasis> const &b, double tol, unsigned k, double zero){
    return divide(Piecewise<SBasis>(a),b,tol,k,zero);
}
Piecewise<SBasis> divide(SBasis const &a, SBasis const &b, double tol, unsigned k, double zero) {
    if (b.tailError(0)<2*zero){
        //TODO: have a better look at sgn(b).
        double sgn= (b(.5)<0.)?-1.:1;
        return Piecewise<SBasis>(Linear(sgn/zero)*a);
    }

    if (fabs(b.at0())>zero && fabs(b.at1())>zero ){
        SBasis c,r=a;
        //TODO: what is a good relative tol? atm, c=a/b +/- (tol/a)%...
        
        k+=1;
        r.resize(k, Linear(0,0));
        c.resize(k, Linear(0,0));
        
        //assert(b.at0()!=0 && b.at1()!=0);
        for (unsigned i=0; i<k; i++){
            Linear ci = Linear(r[i][0]/b[0][0],r[i][1]/b[0][1]);
            c[i]=ci;
            r-=shift(ci*b,i);
        }
        
        if (r.tailError(k)<tol) return Piecewise<SBasis>(c);
    }
    
    Piecewise<SBasis> c0,c1;
    c0 = divide(compose(a,Linear(0.,.5)),compose(b,Linear(0.,.5)),tol,k);
    c1 = divide(compose(a,Linear(.5,1.)),compose(b,Linear(.5,1.)),tol,k);
    c0.setDomain(Interval(0.,.5));
    c1.setDomain(Interval(.5,1.));
    c0.concat(c1);
    return c0;
}


//-- compose(pw<T>,SBasis) ---------------
/* 
   the purpose of the following functions is only to reduce the code in piecewise.h
   TODO: use a vector<pairs<double,unsigned> > instead of a map<double,unsigned>.
 */

std::map<double,unsigned> compose_pullback(std::vector<double> const &values, SBasis const &g){
   std::map<double,unsigned> result;

   std::vector<std::vector<double> > roots = multi_roots(g, values);
   for(unsigned i=0; i<roots.size(); i++){
       for(unsigned j=0; j<roots[i].size();j++){
           result[roots[i][j]]=i;
       }
   }
  // Also map 0 and 1 to the first value above(or =) g(0) and g(1).
  if(result.count(0.)==0){
      unsigned i=0;
      while (i<values.size()&&(g.at0()>values[i])) i++;
      result[0.]=i;
  }
  if(result.count(1.)==0){
      unsigned i=0;
      while (i<values.size()&&(g.at1()>values[i])) i++;
      result[1.]=i;
  }
  return(result);
}

int compose_findSegIdx(std::map<double,unsigned>::iterator  const &cut,
                       std::map<double,unsigned>::iterator  const &next,
                       std::vector<double>  const &levels,
                       SBasis const &g){
    double     t0=(*cut).first;
    unsigned idx0=(*cut).second;
    double     t1=(*next).first;
    unsigned idx1=(*next).second;
    assert(t0<t1);
    int  idx; //idx of the relevant f.segs
    if (std::max(idx0,idx1)==levels.size()){ //g([t0,t1]) is above the top level,
      idx=levels.size()-1;
    } else if (idx0 != idx1){                //g([t0,t1]) crosses from level idx0 to idx1,
      idx=std::min(idx0,idx1);
    } else if(g((t0+t1)/2) < levels[idx0]) { //g([t0,t1]) is a 'U' under level idx0,
      idx=idx0-1;
    } else if(g((t0+t1)/2) > levels[idx0]) { //g([t0,t1]) is a 'bump' over level idx0,
      idx=idx0;
    } else {                                 //g([t0,t1]) is contained in level idx0!...
      idx = (idx0==levels.size())? idx0-1:idx0;
    }

    //move idx back from levels f.cuts 
    idx+=1;
    return idx;
}

std::vector<double> roots(Piecewise<SBasis> const &f){
    std::vector<double> result;
    for (unsigned i=0; i<f.size(); i++){
        std::vector<double> rts=roots(f.segs[i]);
        rts=roots(f.segs[i]);

        for (unsigned r=0; r<rts.size(); r++){
            result.push_back(f.mapToDomain(rts[r], i));
        }
    }
    return result;
}

}
/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
