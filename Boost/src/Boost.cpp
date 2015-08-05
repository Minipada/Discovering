//============================================================================
// Name        : Boost.cpp
// Author      : David
// Version     :
// Copyright   : Copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <boost/assign.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <fstream>
#include <iostream>

#include "defPolygon.hpp"

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

void SVGCreater(std::vector<polygon> poly_)
{
  std::ofstream svg("/home/david/Development/Discovering/Boost/maps/union.svg");
  boost::geometry::svg_mapper<point_type> mapper(svg, 400, 400);

	for (std::vector<polygon>::iterator it = poly_.begin(); it != poly_.end(); it++)
	{
    mapper.add(*it);
    mapper.map(*it, "fill-opacity:0.3;fill:rgb(51,51,153);stroke:rgb(51,51,153);stroke-width:2");
	}

}

void SVGCreater(polygon poly_1, polygon poly_2)
{
  std::ofstream svg("/home/david/Development/Discovering/Boost/maps/union_.svg");
  boost::geometry::svg_mapper<point_type> mapper(svg, 400, 400);

	mapper.add(poly_1);
	mapper.add(poly_2);
	mapper.map(poly_1, "fill-opacity:0.3;fill:rgb(212,0,0);stroke:rgb(212,0,0);stroke-width:2");
	mapper.map(poly_2, "fill-opacity:0.3;fill:rgb(22,84,210);stroke:rgb(22,84,210);stroke-width:2");
}

void UnionBoost()
{
  // Working with points
	polygon poly_string = CreatePolygonFromString();
	polygon poly_tuples = CreatePolygonFromTuples();

	// Correct polygons - Needed because polygons can't be merged if not in the same direction
	// Clockwise or counterclockwise
  boost::geometry::correct(poly_string);
  boost::geometry::correct(poly_tuples);

  SVGCreater(poly_string,poly_tuples);

  std::vector<polygon> output_union;
  boost::geometry::union_(poly_string, poly_tuples, output_union);

  //SVG
  SVGCreater(output_union);
}


polygon CreatePolygonFromString()
{
	polygon poly_string_;
	// Clockwise
	boost::geometry::read_wkt(
	        "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
	            "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))", poly_string_);

	return poly_string_;
}

polygon CreatePolygonFromTuples()
{
	polygon poly_tuples_;

	// Counterclockwise
	std::vector<point_type> points_ =
			{
					{4.0, -0.5}, {4.5, 1.0}, {6.0, 1.5} , {4.5, 2.0}, {4.0, 3.5} , {3.5, 2.0} , {2.0, 1.5} , {3.5, 1.0} , {4.0, -0.5}
			};
	for (std::vector<point_type>::iterator it = points_.begin(); it != points_.end(); it++)
	{
		boost_geom::append(poly_tuples_, boost::make_tuple(it->x(), it->y()));
	}

	return poly_tuples_;
}


int main() {

	std::cout << "!!!Hello Boost!!!" << std::endl;

	// Union
	std::cout << "!!!Union!!!" << std::endl;
	UnionBoost();

	return 0;
}
