#ifndef SVGLINE_H_
#define SVGLINE_H_

#include <string>
#include <vector>

#include "SVGShape.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "IncorrectArgStrException.h"

class SVGLine : public SVGShape {
public:
	/*Throws an exception if the given arguments have any faults - incorrect num of arg
	or invalid arg names and /or order */
	SVGLine(std::vector<std::string> arguments);
	~SVGLine() {}

	virtual void Translate(int horizontal, int vertical);
	/*line 5 3 10 -5 blue*/
	virtual std::string ToStringForConsole();
	/*<line x1="5" y1="3" x2="10" y2="-5" fill="blue" / >*/
	virtual std::string ToString();
	virtual std::string ShapeType();
	virtual bool IsWithinCircleArea(Circle circle_area);
	virtual bool IsWithinRectangleArea(Rectangle rect_area);

	Point get_first_point();
	Point get_second_point();

private:

	Point first_point;
	Point second_point;
};

#endif

