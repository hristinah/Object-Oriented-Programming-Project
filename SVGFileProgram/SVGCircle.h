#ifndef SVGCIRCLE_H_
#define SVGCIRCLE_H_

#include <string>
#include <vector>

#include "SVGShape.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "IncorrectArgStrException.h"

class SVGCircle : public SVGShape {
public:
	/*Throws an exception if the given arguments have any faults - incorrect num of arg
	or invalid arg names and /or order (color can be ommited -> "transparent" by default).*/
	SVGCircle(std::vector<std::string> arguments);
	~SVGCircle() {}

	virtual void Translate(int horizontal, int vertical);
	/*circle 5 5 10 blue*/
	virtual std::string ToStringForConsole();
	/*<circle cx="5" cy="5" r="10" fill="blue" />*/
	virtual std::string ToString();
	virtual std::string ShapeType();
	virtual bool IsWithinCircleArea(Circle circle_area);
	virtual bool IsWithinRectangleArea(Rectangle rect_area);

	Circle get_dimensions();

private:
	Circle dimensions;
};

#endif

