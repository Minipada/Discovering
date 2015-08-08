/*
 * defPolygon.hpp
 *
 *  Created on: Aug 5, 2015
 *      Author: david
 */

#ifndef DEFPOLYGON_HPP_
#define DEFPOLYGON_HPP_

namespace boost_geom = boost::geometry;
typedef boost_geom::model::d2::point_xy<double> point_type;
typedef boost_geom::model::polygon<point_type> polygon;

#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/crosses.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <fstream>
#include <iostream>




double getArea(polygon poly);
point_type getCentroid(polygon& poly);
void SVGCreater(std::vector<polygon>& poly_, const char* path);
void SVGCreater(polygon& poly, boost::geometry::svg_mapper<point_type>& mapper, std::string color);
void UnionBoost(polygon& poly1, polygon& poly2);
void areDisjoint(polygon& poly1, polygon& poly2);
void areIntersects(polygon& poly1, polygon& poly2);
void DifferenceBoost(polygon& poly1, polygon& poly2, std::string path);
polygon CreatePolygonFromString();
polygon CreatePolygonFromTuples();
void distancePolygons(polygon poly1, polygon poly2);
void ExtremesPoly(polygon& poly);
void areGeometryEquals(polygon& poly1, polygon& poly2);
void IntersectionBoost(polygon& poly1, polygon& poly2);
void hullBoost(polygon& poly1, std::string path);
void numberOfPoints(polygon& poly1);
void perimeter(polygon& poly1);
void simplifyPolygon(polygon& poly1, double simplify_coefficient, std::string path);
void symDifferenceBoost(polygon& poly1, polygon& poly2);
void InsideBoost(polygon& poly1, polygon& poly2);





#endif /* DEFPOLYGON_HPP_ */
