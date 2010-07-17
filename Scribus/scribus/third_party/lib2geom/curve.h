/**
 * \file
 * \brief Abstract curve type
 *
 *//*
 * Authors:
 *   MenTaLguY <mental@rydia.net>
 *   Marco Cecchetti <mrcekets at gmail.com>
 *   Krzysztof Kosiński <tweenk.pl@gmail.com>
 * 
 * Copyright 2007-2009 Authors
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


#ifndef _2GEOM_CURVE_H_
#define _2GEOM_CURVE_H_

#include <vector>
#include "coord.h"
#include "point.h"
#include "interval.h"
#include "sbasis.h"
#include "d2.h"
#include "affine.h"

namespace Geom 
{

class Curve;

struct CurveHelpers {
protected:
  static int root_winding(Curve const &c, Point p);
};


/**
 * @brief Abstract continuous curve on a plane defined on [0,1].
 *
 * Formally, a curve in 2Geom is defined as a function
 * \f$\mathbf{C}: [0, 1] \to \mathbb{R}^2\f$
 * (a function that maps the unit interval to points on a 2D plane). Its image (the set of points
 * the curve passes through) will be denoted \f$\mathcal{C} = \mathbf{C}[ [0, 1] ]\f$.
 * All curve types available in 2Geom are continuous and differentiable on their
 * interior, e.g. \f$(0, 1)\f$. Sometimes the curve's image (value set) is referred to as the curve
 * itself for simplicity, but keep in mind that it's not strictly correct.
 * 
 * It is common to think of the parameter as time. The curve can then be interpreted as
 * describing the position of some moving object from time \f$t=0\f$ to \f$t=1\f$.
 * Because of this, the parameter is frequently called the time value.
 *
 * Some methods return pointers to newly allocated curves. They are expected to be freed
 * by the caller when no longer used. Default implementations are provided for some methods.
 *
 * @ingroup Curves
 */
class Curve : private CurveHelpers {
public:
    virtual ~Curve() {}

    /// @name Evaluate the curve
    /// @{
    /** @brief Retrieve the start of the curve.
    * @return The point corresponding to \f$\mathbf{C}(0)\f$. */
    virtual Point initialPoint() const = 0;
    /** Retrieve the end of the curve.
     * @return The point corresponding to \f$\mathbf{C}(1)\f$. */
    virtual Point finalPoint() const = 0;
    /** @brief Check whether the curve has exactly zero length.
     * @return True if the curve's initial point is exactly the same as its final point, and it contains
     *         no other points (its value set contains only one element).
     */
    virtual bool isDegenerate() const = 0;
    /** @brief Evaluate the curve at a specified time value.
     * @param t Time value
     * @return \f$\mathbf{C}(t)\f$ */
    virtual Point pointAt(Coord t) const { return pointAndDerivatives(t, 0).front(); }
    /** @brief Evaluate one of the coordinates at the specified time value.
     * @param t Time value
     * @param d The dimension to evaluate
     * @return The specified coordinate of \f$\mathbf{C}(t)\f$ */
    virtual Coord valueAt(Coord t, Dim2 d) const { return pointAt(t)[d]; }
    /** @brief Evaluate the function at the specified time value. Allows curves to be used
     * as functors. */
    virtual Point operator() (Coord t)  const { return pointAt(t); }
    /** @brief Evaluate the curve and its derivatives.
     * This will return a vector that contains the value of the curve and the specified number
     * of derivatives. However, the returned vector might contain less elements than specified
     * if some derivatives do not exist.
     * @param t Time value
     * @param n The number of derivatives to compute
     * @return Vector of at most \f$n+1\f$ elements of the form \f$[\mathbf{C}(t),
        \mathbf{C}'(t), \mathbf{C}''(t), \ldots]\f$ */
    virtual std::vector<Point> pointAndDerivatives(Coord t, unsigned n) const = 0;
    /// @}

    /// @name Change the curve's endpoints
    /// @{
    /** @brief Change the starting point of the curve.
     * After calling this method, it is guaranteed that \f$\mathbf{C}(0) = \mathbf{p}\f$,
     * and the curve is still continuous. The precise new shape of the curve varies with curve
     * type.
     * @param p New starting point of the curve */
    virtual void setInitial(Point const &v) = 0;
    /** @brief Change the ending point of the curve.
     * After calling this method, it is guaranteed that \f$\mathbf{C}(0) = \mathbf{p}\f$,
     * and the curve is still continuous. The precise new shape of the curve varies
     * with curve type.
     * @param p New ending point of the curve */
    virtual void setFinal(Point const &v) = 0;
    /// @}

    /// @name Compute the bounding box
    /// @{
    /** @brief Quickly compute the curve's approximate bounding box.
     * The resulting rectangle is guaranteed to contain all points belonging to the curve,
     * but it might not be the smallest such rectangle. This method is usually fast.
     * @return A rectangle that contains all points belonging to the curve. */
    virtual Rect boundsFast() const = 0;
    /** @brief Compute the curve's exact bounding box.
     * This method can be dramatically slower than boundsExact() depending on the curve type.
     * @return The smallest possible rectangle containing all of the curve's points. */
    virtual Rect boundsExact() const = 0;
    // I have no idea what the 'deg' parameter is for, so this is undocumented for now.
    virtual OptRect boundsLocal(OptInterval const &i, unsigned deg) const = 0;
    /** @brief Compute the bounding box of a part of the curve.
     * Since this method returns the smallest possible bounding rectangle of the specified portion,
     * it can also be rather slow.
     * @param a An interval specifying a part of the curve, or nothing.
     *          If \f$[0, 1] \subseteq a\f$, then the bounding box for the entire curve
     *          is calculated.
     * @return The smallest possible rectangle containing all points in \f$\mathbf{C}[a]\f$,
     *         or nothing if the supplied interval is empty. */
    OptRect boundsLocal(OptInterval const &a) const { return boundsLocal(a, 0); }
    /// @}

    /// @name Create new curves based on this one
    /// @{
    /** @brief Create an exact copy of this curve.
     * @return Pointer to a newly allocated curve, identical to the original */
    virtual Curve *duplicate() const = 0;
    /** @brief Create a curve transformed by an affine transformation.
     * This method returns a new curve instead modifying the existing one, because some curve
     * types are not closed under affine transformations. The returned curve may be of different
     * underlying type (as is the case for horizontal and vertical line segments).
     * @param m Affine describing the affine transformation
     * @return Pointer to a new, transformed curve */
    virtual Curve *transformed(Affine const &m) const = 0;
    /** @brief Create a curve that corresponds to a part of this curve.
     * For \f$a > b\f$, the returned portion will be reversed with respect to the original.
     * The returned curve will always be of the same type.
     * @param a Beginning of the interval specifying the portion of the curve
     * @param b End of the interval
     * @return New curve \f$\mathbf{D}\f$ such that:
     * - \f$\mathbf{D}(0) = \mathbf{C}(a)\f$
     * - \f$\mathbf{D}(1) = \mathbf{C}(b)\f$
     * - \f$\mathbf{D}[ [0, 1] ] = \mathbf{C}[ [a?b] ]\f$,
     *   where \f$[a?b] = [\min(a, b), \max(a, b)]\f$ */
    virtual Curve *portion(Coord a, Coord b) const = 0;
    /** @brief A version of that accepts an Interval. */
    Curve *portion(Interval const &i) const { return portion(i.min(), i.max()); }
    /** @brief Create a reversed version of this curve.
     * The result corresponds to <code>portion(1, 0)</code>, but this method might be faster.
     * @return Pointer to a new curve \f$\mathbf{D}\f$ such that
     *         \f$\forall_{x \in [0, 1]} \mathbf{D}(x) = \mathbf{C}(1-x)\f$ */
    virtual Curve *reverse() const { return portion(1, 0); }
    /** @brief Create a derivative of this curve.
     * It's best to think of the derivative in physical terms: if the curve describes
     * the position of some object on the plane from time \f$t=0\f$ to \f$t=1\f$ as said in the
     * introduction, then the curve's derivative describes that object's speed at the same times.
     * The second derivative refers to its acceleration, the third to jerk, etc.
     * @return New curve \f$\mathbf{D} = \mathbf{C}'\f$. */
    virtual Curve *derivative() const = 0;
    /// @}

    /// @name Advanced operations
    /// @{
    /** @brief Compute a time value at which the curve comes closest to a specified point.
     * The first value with the smallest distance is returned if there are multiple such points.
     * @param p Query point
     * @param a Minimum time value to consider
     * @param b Maximum time value to consider; \f$a < b\f$
     * @return \f$q \in [a, b]: ||\mathbf{C}(q) - \mathbf{p}|| = 
               \inf(\{r \in \mathbb{R} : ||\mathbf{C}(r) - \mathbf{p}||\})\f$ */
    virtual Coord nearestPoint( Point const& p, Coord a = 0, Coord b = 1 ) const;
    /** @brief A version that takes an Interval. */
    Coord nearestPoint(Point const &p, Interval const &i) const {
        return nearestPoint(p, i.min(), i.max());
    }
    /** @brief Compute time values at which the curve comes closest to a specified point.
     * @param p Query point
     * @param a Minimum time value to consider
     * @param b Maximum time value to consider; \f$a < b\f$
     * @return Vector of points closest and equally far away from the query point */
    virtual std::vector<Coord> allNearestPoints( Point const& p, Coord from = 0,
        Coord to = 1 ) const;
    /** @brief A version that takes an Interval. */
    std::vector<Coord> allNearestPoints(Point const &p, Interval const &i) {
        return allNearestPoints(p, i.min(), i.max());
    }
    /** @brief Compute the arc length of this curve.
     * For a curve \f$\mathbf{C}(t) = (C_x(t), C_y(t))\f$, arc length is defined for 2D curves as
     * \f[ \ell = \int_{0}^{1} \sqrt { [C_x'(t)]^2 + [C_y'(t)]^2 }\, \text{d}t \f]
     * In other words, we divide the curve into infinitely small linear segments
     * and add together their lengths. Of course we can't subdivide the curve into
     * infinitely many segments on a computer, so this method returns an approximation.
     * Not that there is usually no closed form solution to such integrals, so this
     * method might be slow.
     * @param tolerance Maximum allowed error
     * @return Total distance the curve's value travels on the plane when going from 0 to 1 */
    virtual Coord length(Coord tolerance=0.01) const;
    /** @brief Computes time values at which the curve intersects an axis-aligned line.
     * @param v The coordinate of the line
     * @param d Which axis the coordinate is on. X means a vertical line, Y a horizontal line. */
    virtual std::vector<Coord> roots(Coord v, Dim2 d) const = 0;
    /** @brief Compute the winding number of the curve at the specified point.
     * @todo Does this makes sense for curves at all? */
    virtual int winding(Point const &p) const { return root_winding(*this, p); }
    /** @brief Compute a vector tangent to the curve.
     * This will return an unit vector (a Point with length() equal to 1) that denotes a vector
     * tangent to the curve. This vector is defined as
     * \f$ \mathbf{v}(t) = \frac{\mathbf{C}'(t)}{||\mathbf{C}'(t)||} \f$. It is pointed
     * in the direction of increasing \f$t\f$, at the specfied time value. The method uses
     * l'Hopital's rule when the derivative is zero. A zero vector is returned if no non-zero
     * derivative could be found.
     * @param t Time value
     * @param n The maximum order of derivative to consider
     * @return Unit tangent vector \f$\mathbf{v}(t)\f$
     * @bug This method might currently break for the case of t being exactly 1. A workaround
     *      is to reverse the curve and use the negated unit tangent at 0 like this:
     * @code
        Curve *c_reverse = c.reverse();
        Point tangent = - c_reverse->unitTangentAt(0);
        delete c_reverse; @endcode */
    virtual Point unitTangentAt(Coord t, unsigned n = 3) const;
    /** @brief Convert the curve to a symmetric power basis polynomial.
     * Symmetric power basis polynomials (S-basis for short) are numerical representations
     * of curves with excellent numerical properties. Most high level operations provided by 2Geom
     * are implemented in terms of S-basis operations, so every curve has to provide a method
     * to convert it to an S-basis polynomial on two variables. See SBasis class reference
     * for more information. */
    virtual D2<SBasis> toSBasis() const = 0;
    /// @}
    
    /// @name Miscellaneous
    /// @{
    /** Return the number of independent parameters required to represent all variations
     * of this curve. For example, for Bezier curves it returns the curve's order
     * multiplied by 2. */
    virtual int degreesOfFreedom() const { return 0;}
    /** @brief Test equality of two curves.
     * @return True if the curves are identical, false otherwise */
    virtual bool operator==(Curve const &c) const { return this == &c;}
    /// @}
};

inline
Coord nearest_point(Point const& p, Curve const& c) {
    return c.nearestPoint(p);
}

} // end namespace Geom


#endif // _2GEOM_CURVE_H_

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
