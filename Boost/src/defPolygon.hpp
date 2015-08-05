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
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <fstream>
#include <iostream>

polygon CreatePolygonFromString();
polygon CreatePolygonFromTuples();
void UnionBoost();
void SVGCreater(std::vector<polygon> poly_);
void SVGCreater(polygon poly_1, polygon poly_2);




#endif /* DEFPOLYGON_HPP_ */
