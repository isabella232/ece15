/*
 * convex-cover.cpp
 *
 * Copyright 2006 Nathan Hurst <njh@mail.csse.monash.edu.au>
 * Copyright 2006 Michael G. Sloan <mgsloan@gmail.com>
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
 * in the file COPYING-LGPL-2.1; if not, write to the Free Software
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

#include <convex-cover.h>
#include <exception.h>
#include <algorithm>
#include <map>
#include <assert.h>

/** Todo:
    + modify graham scan to work top to bottom, rather than around angles
    + intersection
    + minimum distance between convex hulls
    + maximum distance between convex hulls
    + hausdorf metric?
    + check all degenerate cases carefully
    + check all algorithms meet all invariants
    + generalise rotating caliper algorithm (iterator/circulator?)
*/

using std::vector;
using std::map;
using std::pair;
using std::make_pair;

namespace Geom{

/*** SignedTriangleArea
 * returns the area of the triangle defined by p0, p1, p2.  A clockwise triangle has positive area.
 */
double
SignedTriangleArea(Point p0, Point p1, Point p2) {
    return cross((p1 - p0), (p2 - p0));
}

class angle_cmp{
public:
    Point o;
    angle_cmp(Point o) : o(o) {}

#if 0
    bool
    operator()(Point a, Point b) {
        // not remove this check or std::sort could crash
        if (a == b) return false;
        Point da = a - o;
        Point db = b - o;
        if (da == -db) return false;

#if 1
        double aa = da[0];
        double ab = db[0];
        if((da[1] == 0) && (db[1] == 0))
            return da[0] < db[0];
        if(da[1] == 0)
            return true; // infinite tangent
        if(db[1] == 0)
            return false; // infinite tangent
        aa = da[0] / da[1];
        ab = db[0] / db[1];
        if(aa > ab)
            return true;
#else
        //assert((ata > atb) == (aa < ab));
        double aa = atan2(da);
        double ab = atan2(db);
        if(aa < ab)
            return true;
#endif
        if(aa == ab)
            return L2sq(da) < L2sq(db);
        return false;
    }
#else
    bool operator() (Point const& a, Point const&  b)
    {
        // not remove this check or std::sort could generate
        // a segmentation fault because it needs a strict '<'
        // but due to round errors a == b doesn't mean dxy == dyx
        if (a == b) return false;
        Point da = a - o;
        Point db = b - o;
        if (da == -db) return false;
        double dxy = da[X] * db[Y];
        double dyx = da[Y] * db[X];
        if (dxy > dyx) return true;
        else if (dxy < dyx) return false;
        return L2sq(da) < L2sq(db);
    }
#endif
};

void
ConvexHull::find_pivot() {
    // Find pivot P;
    unsigned pivot = 0;
    for (unsigned i = 1; i < boundary.size(); i++)
        if(boundary[i] <= boundary[pivot])
            pivot = i;

    std::swap(boundary[0], boundary[pivot]);
}

void
ConvexHull::angle_sort() {
// sort points by angle (resolve ties in favor of point farther from P);
// we leave the first one in place as our pivot
    std::sort(boundary.begin()+1, boundary.end(), angle_cmp(boundary[0]));
}


void
ConvexHull::graham_scan() {
    if (boundary.size() < 4) return;
    unsigned stac = 2;
    for(unsigned int i = 2; i < boundary.size(); i++) {
        double o = SignedTriangleArea(boundary[stac-2],
                                      boundary[stac-1],
                                      boundary[i]);
        if(o == 0) { // colinear - dangerous...
            stac--;
        } else if(o < 0) { // anticlockwise
        } else { // remove concavity
            while(o >= 0 && stac > 2) {
                stac--;
                o = SignedTriangleArea(boundary[stac-2],
                                       boundary[stac-1],
                                       boundary[i]);
            }
        }
        boundary[stac++] = boundary[i];
    }
    boundary.resize(stac);
}

void
ConvexHull::graham() {
    if(is_degenerate()) // nothing to do
        return;
    find_pivot();
    angle_sort();
    graham_scan();
}

//Mathematically incorrect mod, but more useful.
int mod(int i, int l) {
    return i >= 0 ?
           i % l : (i % l) + l;
}
//OPT: usages can often be replaced by conditions

/*** ConvexHull::left
 * Tests if a point is left (outside) of a particular segment, n. */
bool
ConvexHull::is_left(Point p, int n) {
    return SignedTriangleArea((*this)[n], (*this)[n+1], p) >= 0;
}

/*** ConvexHull::strict_left
 * Tests if a point is left (outside) of a particular segment, n. */
bool
ConvexHull::is_strict_left(Point p, int n) {
    return SignedTriangleArea((*this)[n], (*this)[n+1], p) > 0;
}

/*** ConvexHull::find_positive
 * May return any number n where the segment n -> n + 1 (possibly looped around) in the hull such
 * that the point is on the wrong side to be within the hull.  Returns -1 if it is within the hull.*/
int
ConvexHull::find_left(Point p) {
    int l = boundary.size(); //Who knows if C++ is smart enough to optimize this?
    for(int i = 0; i < l; i++) {
        if(is_left(p, i)) return i;
    }
    return -1;
}


/*** ConvexHull::find_positive
 * May return any number n where the segment n -> n + 1 (possibly looped around) in the hull such
 * that the point is on the wrong side to be within the hull.  Returns -1 if it is within the hull.*/
int
ConvexHull::find_strict_left(Point p) {
    int l = boundary.size(); //Who knows if C++ is smart enough to optimize this?
    for(int i = 0; i < l; i++) {
        if(is_strict_left(p, i)) return i;
    }
    return -1;
}

//OPT: do a spread iteration - quasi-random with no repeats and full coverage.

/*** ConvexHull::contains_point
 * In order to test whether a point is inside a convex hull we can travel once around the outside making
 * sure that each triangle made from an edge and the point has positive area. */
bool
ConvexHull::contains_point(Point p) {
    return find_left(p) == -1;
}

/*** ConvexHull::strict_contains_point
 * In order to test whether a point is strictly inside (not on the boundary) a convex hull we can travel once around the outside making
 * sure that each triangle made from an edge and the point has positive area. */
bool
ConvexHull::strict_contains_point(Point p) {
    return find_strict_left(p) == -1;
}

/*** ConvexHull::add_point
 * to add a point we need to find whether the new point extends the boundary, and if so, what it
 * obscures.  Tarjan?  Jarvis?*/
void
ConvexHull::merge(Point p) {
    std::vector<Point> out;

    int l = boundary.size();

    if(l < 2) {
        boundary.push_back(p);
        return;
    }

    bool pushed = false;

    bool pre = is_strict_left(p, -1);
    for(int i = 0; i < l; i++) {
        bool cur = is_strict_left(p, i);
        if(pre) {
            if(cur) {
                if(!pushed) {
                    out.push_back(p);
                    pushed = true;
                }
                continue;
            }
            else if(!pushed) {
                out.push_back(p);
                pushed = true;
            }
        }
        out.push_back(boundary[i]);
        pre = cur;
    }

    boundary = out;
}
//OPT: quickly find an obscured point and find the bounds by extending from there.  then push all points not within the bounds in order.
  //OPT: use binary searches to find the actual starts/ends, use known rights as boundaries.  may require cooperation of find_left algo.

/*** ConvexHull::is_clockwise
 * We require that successive pairs of edges always turn right.
 * proposed algorithm: walk successive edges and require triangle area is positive.
 */
bool
ConvexHull::is_clockwise() const {
    if(is_degenerate())
        return true;
    Point first = boundary[0];
    Point second = boundary[1];
    for(std::vector<Point>::const_iterator it(boundary.begin()+2), e(boundary.end());
        it != e;) {
        if(SignedTriangleArea(first, second, *it) > 0)
            return false;
        first = second;
        second = *it;
        ++it;
    }
    return true;
}

/*** ConvexHull::top_point_first
 * We require that the first point in the convex hull has the least y coord, and that off all such points on the hull, it has the least x coord.
 * proposed algorithm: track lexicographic minimum while walking the list.
 */
bool
ConvexHull::top_point_first() const {
    std::vector<Point>::const_iterator pivot = boundary.begin();
    for(std::vector<Point>::const_iterator it(boundary.begin()+1),
            e(boundary.end());
        it != e; it++) {
        if((*it)[1] < (*pivot)[1])
            pivot = it;
        else if(((*it)[1] == (*pivot)[1]) &&
                ((*it)[0] < (*pivot)[0]))
            pivot = it;
    }
    return pivot == boundary.begin();
}
//OPT: since the Y values are orderly there should be something like a binary search to do this.

/*** ConvexHull::no_colinear_points
 * We require that no three vertices are colinear.
proposed algorithm:  We must be very careful about rounding here.
*/
bool
ConvexHull::no_colinear_points() const {
    // XXX: implement me!
    THROW_NOTIMPLEMENTED();
}

bool
ConvexHull::meets_invariants() const {
    return is_clockwise() && top_point_first() && no_colinear_points();
}

/*** ConvexHull::is_degenerate
 * We allow three degenerate cases: empty, 1 point and 2 points.  In many cases these should be handled explicitly.
 */
bool
ConvexHull::is_degenerate() const {
    return boundary.size() < 3;
}


int sgn(double x) {
    if(x == 0) return 0;
    return (x<0)?-1:1;
}

bool same_side(Point L[2], Point  xs[4]) {
    int side = 0;
    for(int i = 0; i < 4; i++) {
        int sn = sgn(SignedTriangleArea(L[0], L[1], xs[i]));
        if(sn and not side)
            side = sn;
        else if(sn != side) return false;
    }
    return true;
}

/** find bridging pairs between two convex hulls.
 *   this code is based on Hormoz Pirzadeh's masters thesis.  There is room for optimisation:
 * 1. reduce recomputation
 * 2. use more efficient angle code
 * 3. write as iterator
 */
std::vector<pair<int, int> > bridges(ConvexHull a, ConvexHull b) {
    vector<pair<int, int> > ret;
    
    // 1. find maximal points on a and b
    int ai = 0, bi = 0;
    // 2. find first copodal pair
    double ap_angle = atan2(a[ai+1] - a[ai]);
    double bp_angle = atan2(b[bi+1] - b[bi]);
    Point L[2] = {a[ai], b[bi]};
    while(ai < int(a.size()) or bi < int(b.size())) {
        if(ap_angle == bp_angle) {
            // In the case of parallel support lines, we must consider all four pairs of copodal points
            {
                assert(0); // untested
                Point xs[4] = {a[ai-1], a[ai+1], b[bi-1], b[bi+1]};
                if(same_side(L, xs)) ret.push_back(make_pair(ai, bi));
                xs[2] = b[bi];
                xs[3] = b[bi+2];
                if(same_side(L, xs)) ret.push_back(make_pair(ai, bi));
                xs[0] = a[ai];
                xs[1] = a[ai+2];
                if(same_side(L, xs)) ret.push_back(make_pair(ai, bi));
                xs[2] = b[bi-1];
                xs[3] = b[bi+1];
                if(same_side(L, xs)) ret.push_back(make_pair(ai, bi));
            }
            ai++;
            ap_angle += angle_between(a[ai] - a[ai-1], a[ai+1] - a[ai]);
            L[0] = a[ai];
            bi++;
            bp_angle += angle_between(b[bi] - b[bi-1], b[bi+1] - b[bi]);
            L[1] = b[bi];
            std::cout << "parallel\n";
        } else if(ap_angle < bp_angle) {
            ai++;
            ap_angle += angle_between(a[ai] - a[ai-1], a[ai+1] - a[ai]);
            L[0] = a[ai];
            Point xs[4] = {a[ai-1], a[ai+1], b[bi-1], b[bi+1]};
            if(same_side(L, xs)) ret.push_back(make_pair(ai, bi));
        } else {
            bi++;
            bp_angle += angle_between(b[bi] - b[bi-1], b[bi+1] - b[bi]);
            L[1] = b[bi];
            Point xs[4] = {a[ai-1], a[ai+1], b[bi-1], b[bi+1]};
            if(same_side(L, xs)) ret.push_back(make_pair(ai, bi));
        }
    }
    return ret;
}

unsigned find_bottom_right(ConvexHull const &a) {
    unsigned it = 1;
    while(it < a.boundary.size() &&
          a.boundary[it][Y] > a.boundary[it-1][Y])
        it++;
    return it-1;
}

/*** ConvexHull sweepline_intersection(ConvexHull a, ConvexHull b);
 * find the intersection between two convex hulls.  The intersection is also a convex hull.
 * (Proof: take any two points both in a and in b.  Any point between them is in a by convexity,
 * and in b by convexity, thus in both.  Need to prove still finite bounds.)
 * This algorithm works by sweeping a line down both convex hulls in parallel, working out the left and right edges of the new hull.
 */
ConvexHull sweepline_intersection(ConvexHull const &a, ConvexHull const &b) {
    ConvexHull ret;

    unsigned al = 0;
    unsigned bl = 0;

    while(al+1 < a.boundary.size() &&
          (a.boundary[al+1][Y] > b.boundary[bl][Y])) {
        al++;
    }
    while(bl+1 < b.boundary.size() &&
          (b.boundary[bl+1][Y] > a.boundary[al][Y])) {
        bl++;
    }
    // al and bl now point to the top of the first pair of edges that overlap in y value
    //double sweep_y = std::min(a.boundary[al][Y],
    //                          b.boundary[bl][Y]);
    return ret;
}

/*** ConvexHull intersection(ConvexHull a, ConvexHull b);
 * find the intersection between two convex hulls.  The intersection is also a convex hull.
 * (Proof: take any two points both in a and in b.  Any point between them is in a by convexity,
 * and in b by convexity, thus in both.  Need to prove still finite bounds.)
 */
ConvexHull intersection(ConvexHull /*a*/, ConvexHull /*b*/) {
    ConvexHull ret;
    /*
    int ai = 0, bi = 0;
    int aj = a.boundary.size() - 1;
    int bj = b.boundary.size() - 1;
    */
    /*while (true) {
        if(a[ai]
    }*/
    return ret;
}

template <typename T>
T idx_to_pair(pair<T, T> p, int idx) {
    return idx?p.second:p.first;
}

/*** ConvexHull merge(ConvexHull a, ConvexHull b);
 * find the smallest convex hull that surrounds a and b.
 */
ConvexHull merge(ConvexHull a, ConvexHull b) {
    ConvexHull ret;

    std::cout << "---\n";
    std::vector<pair<int, int> > bpair = bridges(a, b);
    
    // Given our list of bridges {(pb1, qb1), ..., (pbk, qbk)}
    // we start with the highest point in p0, q0, say it is p0.
    // then the merged hull is p0, ..., pb1, qb1, ..., qb2, pb2, ...
    // In other words, either of the two polygons vertices are added in order until the vertex coincides with a bridge point, at which point we swap.

    unsigned state = (a[0][Y] < b[0][Y])?0:1;
    ret.boundary.reserve(a.size() + b.size());
    ConvexHull chs[2] = {a, b};
    unsigned idx = 0;
    
    for(unsigned k = 0; k < bpair.size(); k++) {
        unsigned limit = idx_to_pair(bpair[k], state);
        std::cout << bpair[k].first << " , " << bpair[k].second << "; "
                  << idx << ", " << limit << ", s: "
                  << state
                  << " \n";
        while(idx <= limit) {
            ret.boundary.push_back(chs[state][idx++]);
        }
        state = 1-state;
        idx = idx_to_pair(bpair[k], state);
    }
    while(idx < chs[state].size()) {
        ret.boundary.push_back(chs[state][idx++]);
    }
    return ret;

    /*
    ab[-1] = 0;
    bb[-1] = 0;

    int i = -1; // XXX: i is int but refers to vector indices

    if(a.boundary[0][1] > b.boundary[0][1]) goto start_b;
    while(true) {
        for(; ab.count(i) == 0; i++) {
            ret.boundary.push_back(a[i]);
            if(i >= (int)a.boundary.size()) return ret;
        }
        if(ab[i] == 0 && i != -1) break;
        i = ab[i];
        start_b:

        for(; bb.count(i) == 0; i++) {
            ret.boundary.push_back(b[i]);
            if(i >= (int)b.boundary.size()) return ret;
        }
        if(bb[i] == 0 && i != -1) break;
        i = bb[i];
    }
    */
    return ret;
}

ConvexHull graham_merge(ConvexHull a, ConvexHull b) {
    ConvexHull result;

    // we can avoid the find pivot step because of top_point_first
    if(b.boundary[0] <= a.boundary[0])
        std::swap(a, b);

    result.boundary = a.boundary;
    result.boundary.insert(result.boundary.end(),
                           b.boundary.begin(), b.boundary.end());

/** if we modified graham scan to work top to bottom as proposed in lect754.pdf we could replace the
 angle sort with a simple merge sort type algorithm. furthermore, we could do the graham scan
 online, avoiding a bunch of memory copies.  That would probably be linear. -- njh*/
    result.angle_sort();
    result.graham_scan();

    return result;
}
//TODO: reinstate
/*ConvexCover::ConvexCover(Path const &sp) : path(&sp) {
    cc.reserve(sp.size());
    for(Geom::Path::const_iterator it(sp.begin()), end(sp.end()); it != end; ++it) {
        cc.push_back(ConvexHull((*it).begin(), (*it).end()));
    }
}*/

double ConvexHull::centroid_and_area(Geom::Point& centroid) const {
    const unsigned n = boundary.size();
    if (n < 2)
        return 0;
    if(n < 3) {
        centroid = (boundary[0] + boundary[1])/2;
        return 0;
    }
    Geom::Point centroid_tmp(0,0);
    double atmp = 0;
    for (unsigned i = n-1, j = 0; j < n; i = j, j++) {
        const double ai = -cross(boundary[j], boundary[i]);
        atmp += ai;
        centroid_tmp += (boundary[j] + boundary[i])*ai; // first moment.
    }
    if (atmp != 0) {
        centroid = centroid_tmp / (3 * atmp);
    }
    return atmp / 2;
}

// TODO: This can be made lg(n) using golden section/fibonacci search three starting points, say 0,
// n/2, n-1 construct a new point, say (n/2 + n)/2 throw away the furthest boundary point iterate
// until interval is a single value
Point const * ConvexHull::furthest(Point direction) const {
    Point const * p = &boundary[0];
    double d = dot(*p, direction);
    for(unsigned i = 1; i < boundary.size(); i++) {
        double dd = dot(boundary[i], direction);
        if(d < dd) {
            p = &boundary[i];
            d = dd;
        }
    }
    return p;
}


// returns (a, (b,c)), three points which define the narrowest diameter of the hull as the pair of
// lines going through b,c, and through a, parallel to b,c TODO: This can be made linear time by
// moving point tc incrementally from the previous value (it can only move in one direction).  It
// is currently n*O(furthest)
double ConvexHull::narrowest_diameter(Point &a, Point &b, Point &c) {
    Point tb = boundary.back();
    double d = INFINITY;
    for(unsigned i = 0; i < boundary.size(); i++) {
        Point tc = boundary[i];
        Point n = -rot90(tb-tc);
        Point ta = *furthest(n);
        double td = dot(n, ta-tb)/dot(n,n);
        if(td < d) {
            a = ta;
            b = tb;
            c = tc;
            d = td;
        }
        tb = tc;
    }
    return d;
}

};

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
