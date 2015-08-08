//============================================================================
// Name        : Boost.cpp
// Author      : David
// Version     :
// Copyright   : Copyright
// Description : Hello World in C++, Ansi-style
//============================================================================
//g++ -std=c++11 Boost.cpp -o Boost

#include <boost/assign.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <fstream>
#include <iostream>

#include "defPolygon.hpp"

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

double getArea(polygon poly)
{
	return boost::geometry::area(poly);
}

point_type getCentroid(polygon& poly)
{
  point_type p;
  boost::geometry::centroid(poly,p);
  return p;
}

void SVGCreater(std::vector<polygon>& poly_, const char* path)
{
  std::ofstream svg(path);
  boost::geometry::svg_mapper<point_type> mapper(svg, 400, 400);

	for (std::vector<polygon>::iterator it = poly_.begin(); it != poly_.end(); it++)
	{
    mapper.add(*it);
    mapper.map(*it, "fill-opacity:0.3;fill:rgb(51,51,153);stroke:rgb(51,51,153);stroke-width:2");
    std::cout << "Area: " << getArea(*it) << "\n";

    std::cout << "Centroid: " << boost::geometry::dsv(getCentroid(*it)) << "\n";
	}

}

void SVGCreater(polygon& poly, boost::geometry::svg_mapper<point_type>& mapper, std::string color)
{
	std::string svg_color = "fill-opacity:0.3;fill:rgb("
			+ color + ");stroke:rgb("
			+ color + ");stroke-width:2";

	mapper.add(poly);
	mapper.map(poly, svg_color);
  std::cout << "Area: " << getArea(poly) << "\n";
  std::cout << "Centroid: " << boost::geometry::dsv(getCentroid(poly)) << "\n";
}

void UnionBoost(polygon& poly1, polygon& poly2)
{
	// Correct polygons - Needed because polygons can't be merged if not in the same direction
	// Clockwise or counterclockwise
  boost::geometry::correct(poly1);
  boost::geometry::correct(poly2);

  std::vector<polygon> output_union;
  boost::geometry::union_(poly1, poly2, output_union);

  //SVG
  SVGCreater(output_union, "/home/david/Development/Discovering/Boost/maps/union_.svg");
}

void areDisjoint(polygon& poly1, polygon& poly2)
{
	bool dis = boost::geometry::disjoint(poly1,poly2);

	if (dis == 0)
	{
		std::cout << "Not disjoint" << "\n";
	}
	else {
		std::cout << "Disjoint" << "\n";
	}
}

void areIntersects(polygon& poly1, polygon& poly2)
{
	bool dis = boost::geometry::intersects(poly1,poly2);

	if (dis == 0)
	{
		std::cout << "No intersection" << "\n";
	}
	else {
		std::cout << "Intersection" << "\n";
	}
}

void DifferenceBoost(polygon& poly1, polygon& poly2, std::string path)
{
	// Correct polygons - Needed because polygons can't be merged if not in the same direction
	// Clockwise or counterclockwise
  boost::geometry::correct(poly1);
  boost::geometry::correct(poly2);

  std::vector<polygon> output_difference;
  boost::geometry::difference(poly1, poly2, output_difference);

  //SVG
  SVGCreater(output_difference, (path + ".svg").c_str());
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

void distancePolygons(polygon poly1, polygon poly2)
{
//	double test = boost::geometry::distance(poly1, poly2);
	std::cout << "Distance: " << boost::geometry::distance(poly1, poly2) << "\n";
}

void ExtremesPoly(polygon& poly)
{
  boost::geometry::model::box<point_type> box;
  boost::geometry::envelope(poly, box);

  std::cout << "Min X: " << box.min_corner().x() << "| "
  		<< "Min Y: " << box.min_corner().y() << "| "
			<< "Max X: " << box.max_corner().x() << "| "
			<< "Max Y: " << box.max_corner().y() << "| " << "\n";
}

void areGeometryEquals(polygon& poly1, polygon& poly2)
{
	if (boost::geometry::equals(poly1, poly2) == true)
	{
	  std::cout << "Geometries equal" << "\n";
	}
	else
	{
	  std::cout << "Geometries not equal" << "\n";
	}
}

void IntersectionBoost(polygon& poly1, polygon& poly2)
{
	// Correct polygons - Needed because polygons can't be merged if not in the same direction
	// Clockwise or counterclockwise
  boost::geometry::correct(poly1);
  boost::geometry::correct(poly2);

  std::vector<polygon> output_difference;
  boost::geometry::intersection(poly1, poly2, output_difference);

  //SVG
  SVGCreater(output_difference, "/home/david/Development/Discovering/Boost/maps/intersection.svg");
}

void hullBoost(polygon& poly1, std::string path)
{
  polygon poly_hull;
  boost::geometry::convex_hull(poly1, poly_hull);

  std::ofstream svg(path.c_str());
  boost::geometry::svg_mapper<point_type> mapper_hull(svg, 400, 400);
  SVGCreater(poly_hull, mapper_hull, "77,200,42");
}

void numberOfPoints(polygon& poly1)
{
  std::cout << "Number of points: " << boost::geometry::num_points(poly1) << "\n";
}

void perimeter(polygon& poly1)
{
	std::cout << "Perimeter: " << boost::geometry::perimeter(poly1) << "\n";
}

void simplifyPolygon(polygon& poly1, double simplify_coefficient, std::string path)
{
  polygon simplified_polygon;
  boost::geometry::simplify(poly1, simplified_polygon, simplify_coefficient);

  std::ofstream svg(path.c_str());
  boost::geometry::svg_mapper<point_type> mapper_simplify(svg, 400, 400);
  SVGCreater(simplified_polygon, mapper_simplify, "17,20,92");

}

void symDifferenceBoost(polygon& poly1, polygon& poly2)
{
 boost::geometry::model::multi_polygon<polygon> multi;

	// Correct polygons - Needed because polygons can't be merged if not in the same direction
	// Clockwise or counterclockwise
 boost::geometry::correct(poly1);
 boost::geometry::correct(poly2);

 boost::geometry::sym_difference(poly1, poly2, multi);

	std::cout
			<< "poly1 XOR poly2:" << "\n"
			<< "total: " << boost::geometry::area(multi) << "\n";
	int i = 0;
	BOOST_FOREACH(polygon const& p, multi)
	{
			std::cout << i++ << ": " << boost::geometry::area(p) << "\n";
	}
}

void InsideBoost(polygon& poly1, polygon& poly2)
{
	bool result = boost::geometry::within(poly1, poly2);

	if (result == true)
	{
		std::cout << "Poly1 inside Poly2" << "\n";
	}
	else {
		std::cout << "Poly1 not inside Poly2" << "\n";
	}
}

int main() {

	std::cout << "!!!Hello Boost!!!" << "\n" ;

  // Working with points
	polygon poly_string = CreatePolygonFromString();
	polygon poly_tuples = CreatePolygonFromTuples();

	// Sym Difference
	symDifferenceBoost(poly_string, poly_tuples);
	symDifferenceBoost(poly_tuples, poly_string);

	// Hull
	hullBoost(poly_string,"/home/david/Development/Discovering/Boost/maps/hull1.svg");
	hullBoost(poly_tuples,"/home/david/Development/Discovering/Boost/maps/hull2.svg");

	// Number of points
	numberOfPoints(poly_string);
	numberOfPoints(poly_tuples);

	// Perimeter
	perimeter(poly_string);
	perimeter(poly_tuples);

	// Minimums and maximums
	ExtremesPoly(poly_string);
	ExtremesPoly(poly_tuples);

	// Simplify
	simplifyPolygon(poly_string,0.5, "/home/david/Development/Discovering/Boost/maps/simplified1.svg");
	simplifyPolygon(poly_tuples,0.5, "/home/david/Development/Discovering/Boost/maps/simplified2.svg");

	// Number of points
	numberOfPoints(poly_string);
	numberOfPoints(poly_tuples);

	// Equals
	areGeometryEquals(poly_string, poly_tuples);

	//Disjoint
	areDisjoint(poly_string, poly_tuples);

	//Intersects
	areIntersects(poly_string, poly_tuples);

	// Distance
	distancePolygons(poly_string, poly_tuples);

	// Union
	std::cout << "!!!Union!!!" << "\n";
	UnionBoost(poly_string, poly_tuples);

	std::string difference = "/home/david/Development/Discovering/Boost/maps/difference_";

	// Difference
	std::cout << "!!!Difference 1!!!" << "\n";
	DifferenceBoost(poly_string, poly_tuples, (difference + "1"));

	std::cout << "!!!Difference 2!!!" << "\n";
	DifferenceBoost(poly_tuples, poly_string, (difference + "2"));

	// Intersection
	IntersectionBoost(poly_tuples, poly_string);

	// Inside
	InsideBoost(poly_string, poly_tuples);

	return 0;
}
