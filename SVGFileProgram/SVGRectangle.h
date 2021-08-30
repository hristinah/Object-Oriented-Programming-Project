#ifndef SVGRECTANGLE_H_
#define SVGRECTANGLE_H_

#include <string>
#include <vector>

#include "SVGShape.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "IncorrectArgStrException.h"

class SVGRectangle : public SVGShape {
public:
	/*Throws an exception if the given arguments have any faults - incorrect num of arg
	or invalid arg names and /or order (color can be ommited -> "transparent" by default).*/
	SVGRectangle(std::vector<std::string> arguments);
	~SVGRectangle() {}

	virtual void Translate(int horizontal, int vertical);
	/*rectangle 100 60 10 10 red*/
	virtual std::string ToStringForConsole();
	/*<rect x="100" y="60" width="10" height="10" fill="red" />*/
	virtual std::string ToString();
	virtual std::string ShapeType();
	virtual bool IsWithinCircleArea(Circle circle_area);
	virtual bool IsWithinRectangleArea(Rectangle rect_area);

	Rectangle get_dimensions();

private:
	Rectangle dimensions;
};

#endif