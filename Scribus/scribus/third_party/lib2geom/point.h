/**
 *  \file
 *  \brief Cartesian point / 2D vector and related operations
 *//*
 *  Authors:
 *    Michael G. Sloan <mgsloan@gmail.com>
 *    Nathan Hurst <njh@njhurst.com>
 *    Krzysztof Kosiński <tweenk.pl@gmail.com>
 *
 * Copyright (C) 2006-2009 Authors
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
 */

#ifndef SEEN_Geom_POINT_H
#define SEEN_Geom_POINT_H

#include "scconfig.h"
#include <iostream>
#include <iterator>
#include <boost/operators.hpp>
#include "forward.h"
#include "coord.h"
#include "isnan.h" //temporary fix for isnan()
#include "math-utils.h"

namespace Geom {

enum Dim2 { X=0, Y=1 };

class Point
    : boost::additive< Point
    , boost::totally_ordered< Point
    , boost::multiplicative< Point, Coord
    , boost::multiplicative< Point, Affine
    , boost::multiplicative< Point, Translate
    , boost::multiplicative< Point, Rotate
    , boost::multiplicative< Point, Scale
    , boost::multiplicative< Point, HShear
    , boost::multiplicative< Point, VShear
      > > > > > > > > > // this uses chaining so it looks weird, but works
{
    Coord _pt[2];

public:
    /** Construct a point on the origin. */
    inline Point()
    { _pt[X] = _pt[Y] = 0; }

    /** Construct a point from its coordinates. */
    inline Point(Coord x, Coord y) {
        _pt[X] = x; _pt[Y] = y;
    }
    inline Point(Point const &p) {
        for (unsigned i = 0; i < 2; ++i)
            _pt[i] = p._pt[i];
    }
    inline Point &operator=(Point const &p) {
        for (unsigned i = 0; i < 2; ++i)
            _pt[i] = p._pt[i];
        return *this;
    }

    /// @name Access the coordinates of a point
    /// @{
    inline Coord operator[](unsigned i) const { return _pt[i]; }
    inline Coord &operator[](unsigned i) { return _pt[i]; }

    Coord operator[](Dim2 d) const throw() { return _pt[d]; }
    Coord &operator[](Dim2 d) throw() { return _pt[d]; }
    /// @}

    /// @name Vector operations
    /// @{
    /** @brief Compute the distance from origin.
     * @return Length of the vector from origin to this point */
    inline Coord length() const { return hypot(_pt[0], _pt[1]); }
    void normalize();

    /** @brief Return a point like this point but rotated -90 degrees.
     * If the y axis grows downwards and the x axis grows to the
     * right, then this is 90 degrees counter-clockwise. */
    Point ccw() const {
        return Point(_pt[Y], -_pt[X]);
    }

    /** @brief Return a point like this point but rotated +90 degrees.
     * If the y axis grows downwards and the x axis grows to the
     * right, then this is 90 degrees clockwise. */
    Point cw() const {
        return Point(-_pt[Y], _pt[X]);
    }
    /// @}

    /// @name Vector-like arithmetic operations
    /// @{
    inline Point operator-() const {
        return Point(-_pt[X], -_pt[Y]);
    }
    inline Point &operator+=(Point const &o) {
        for ( unsigned i = 0 ; i < 2 ; ++i ) {
            _pt[i] += o._pt[i];
        }
        return *this;
    }
    inline Point &operator-=(Point const &o) {
        for ( unsigned i = 0 ; i < 2 ; ++i ) {
            _pt[i] -= o._pt[i];
        }
        return *this;
    }
    inline Point &operator*=(double s) {
        for ( unsigned i = 0 ; i < 2 ; ++i ) _pt[i] *= s;
        return *this;
    }
    inline Point &operator/=(double s) {
        //TODO: s == 0?
        for ( unsigned i = 0 ; i < 2 ; ++i ) _pt[i] /= s;
        return *this;
    }
    /// @}

    /// @name Affine transformations
    /// @{
    Point &operator*=(Affine const &m);
    // implemented in transforms.cpp
    Point &operator*=(Translate const &t);
    Point &operator*=(Scale const &s);
    Point &operator*=(Rotate const &r);
    Point &operator*=(HShear const &s);
    Point &operator*=(VShear const &s);
    /** @brief Transform the point by the inverse of the specified matrix. */
    template <typename T>
    Point &operator/=(T const &m) {
        *this *= m.inverse();
        return *this;
    }
    /// @}

    /// @name Various utilities
    /// @{
    /** @brief Lower the precision of the point.
     * This will round both coordinates to multiples of \f$10^p\f$. */
    inline void round (int p = 0) {
        _pt[X] = (Coord)(decimal_round((double)_pt[X], p));
        _pt[Y] = (Coord)(decimal_round((double)_pt[Y], p));
        return;
    }

    /** @brief Check whether both coordinates are finite.
     * @return True if neither coordinate is infinite. */
    inline bool isFinite() const {
        for ( unsigned i = 0 ; i < 2 ; ++i ) {
            if(!IS_FINITE(_pt[i])) return false;
        }
        return true;
    }
    /** @brief Equality operator.
     * This tests for exact identity (as opposed to are_near()). Note that due to numerical
     * errors, this test might return false even if the points should be identical. */
    inline bool operator==(const Point &in_pnt) const {
        return ((_pt[X] == in_pnt[X]) && (_pt[Y] == in_pnt[Y]));
    }
    /** @brief Lexicographical ordering for points.
     * Y coordinate is regarded as more significant. When sorting according to this
     * ordering, the points will be sorted according to the Y coordinate, and within
     * points with the same Y coordinate according to the X coordinate. */
    inline bool operator<(const Point &p) const {
        return ( ( _pt[Y] < p[Y] ) ||
             (( _pt[Y] == p[Y] ) && ( _pt[X] < p[X] )));
    }
    /// @}

    /// @name Point factories
    /// @{
    /** @brief Construct a point from its polar coordinates.
     * The angle is specified in radians, in the mathematical convention (increasing
     * counter-clockwise from +X). */
    static inline Point polar(Coord angle, Coord radius) {
        Point ret(polar(angle));
        ret *= radius;
        return ret;
    }
    /** @brief Construct an unit vector from its angle.
     * The angle is specified in radians, in the mathematical convention (increasing
     * counter-clockwise from +X). */
    static inline Point polar(Coord angle) {
        Point ret;
        sincos(angle, ret[Y], ret[X]);
        return ret;
    }
    /// @}

    /** @brief Lexicographical ordering functor. */
    template <Dim2 d> struct LexOrder;
    /** @brief Lexicographical ordering functor with runtime dimension. */
    class LexOrderRt {
    public:
        LexOrderRt(Dim2 d) : dim(d) {}
        inline bool operator()(Point const &a, Point const &b);
    private:
        Dim2 dim;
    };

    friend inline std::ostream &operator<< (std::ostream &out_file, const Geom::Point &in_pnt);
};

/** @brief Output operator for points.
 * Prints out the coordinates.
 * @relates Point */
inline std::ostream &operator<< (std::ostream &out_file, const Geom::Point &in_pnt) {
    out_file << "X: " << in_pnt[X] << "  Y: " << in_pnt[Y];
    return out_file;
}

template<> struct Point::LexOrder<X> {
    bool operator()(Point const &a, Point const &b) {
        return a[X] < b[X] || (a[X] == b[X] && a[Y] < b[Y]);
    }
};
template<> struct Point::LexOrder<Y> {
    bool operator()(Point const &a, Point const &b) {
        return a[Y] < b[Y] || (a[Y] == b[Y] && a[X] < b[X]);
    }
};
inline bool Point::LexOrderRt::operator()(Point const &a, Point const &b) {
    return dim ? Point::LexOrder<Y>()(a, b) : Point::LexOrder<X>()(a, b);
}

/** @brief Compute the second (Euclidean) norm of @a p.
 * This corresponds to the length of @a p. The result will not overflow even if
 * \f$p_X^2 + p_Y^2\f$ is larger that the maximum value that can be stored
 * in a <code>double</code>.
 * @return \f$\sqrt{p_X^2 + p_Y^2}\f$
 * @relates Point */
inline Coord L2(Point const &p)
{
    return p.length();
}

/** @brief Compute the square of the Euclidean norm of @a p.
 * Warning: this can overflow where L2 won't.
 * @return \f$p_X^2 + p_Y^2\f$
 * @relates Point */
inline Coord L2sq(Point const &p)
{
    return p[0]*p[0] + p[1]*p[1];
}

//IMPL: NearConcept
/** @brief Nearness predicate for points.
 * True if neither coordinate of @a a is further than @a eps from the corresponding
 * coordinate of @a b.
 * @relates Point */
inline bool are_near(Point const &a, Point const &b, double const eps=EPSILON)
{
    return ( are_near(a[X],b[X],eps) && are_near(a[Y],b[Y],eps) );
}

/** @brief Return a point halfway between the specified ones.
 * @relates Point */
inline Point middle_point(Point const& P1, Point const& P2)
{
    return (P1 + P2) / 2;
}

/** @brief Returns p * Geom::rotate_degrees(90), but more efficient.
 *
 * Angle direction in 2Geom: If you use the traditional mathematics convention that y
 * increases upwards, then positive angles are anticlockwise as per the mathematics convention.  If
 * you take the common non-mathematical convention that y increases downwards, then positive angles
 * are clockwise, as is common outside of mathematics.
 *
 * There is no function to rotate by -90 degrees: use -rot90(p) instead.
 * @relates Point */
inline Point rot90(Point const &p)
{
    return Point(-p[Y], p[X]);
}

/** @brief Linear interpolation between two points.
 * @param t Time value
 * @param a First point
 * @param b Second point
 * @return Point on a line between a and b. The ratio of its distance from a
 *         and the distance between a and b will be equal to t.
 * @relates Point */
inline Point lerp(double const t, Point const &a, Point const &b)
{
    return (a * (1 - t) + b * t);
}

/** @brief Compute the dot product of a and b.
 * Dot product can be interpreted as a measure of how parallel the vectors are.
 * For perpendicular vectors, it is zero. For parallel ones, its absolute value is highest,
 * and the sign depends on whether they point in the same direction (+) or opposite ones (-).
 * @return \f$a \cdot b = a_X b_X + a_Y b_Y\f$.
 * @relates Point*/
inline Coord dot(Point const &a, Point const &b)
{
    return a[0] * b[0] + a[1] * b[1];
}

/** @brief Compute the 2D cross product.
 * Defined as dot(a, b.cw()). This means it will be zero for parallel vectors,
 * and its absolute value highest for perpendicular vectors.
 * @relates Point*/
inline Coord cross(Point const &a, Point const &b)
{
    return dot(a, b.cw());
}

/** @brief Compute the (Euclidean) distance between points.
 * @relates Point */
inline Coord distance (Point const &a, Point const &b)
{
    return L2(a - b);
}

/** @brief Compute the square of the distance between points.
 * @relates Point */
inline Coord distanceSq (Point const &a, Point const &b)
{
    return L2sq(a - b);
}

Point unit_vector(Point const &a);
Coord L1(Point const &p);
Coord LInfty(Point const &p);
bool is_zero(Point const &p);
bool is_unit_vector(Point const &p);
extern double atan2(Point const &p);
extern double angle_between(Point const &a, Point const &b);
Point abs(Point const &b);
Point constrain_angle(Point const &A, Point const &B, unsigned int n = 4, Geom::Point const &dir = Geom::Point(1,0));

} /* namespace Geom */

// This is required to fix a bug in GCC 4.3.3 (and probably others) that causes the compiler
// to try to instantiate the iterator_traits template and fail. Probably it thinks that Point
// is an iterator and tries to use std::distance instead of Geom::distance.
namespace std {
template <> class iterator_traits<Geom::Point> {};
}

#endif /* !SEEN_Geom_POINT_H */

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
