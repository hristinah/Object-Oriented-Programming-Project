#include "SVGLine.h"
#include <string>
#include <vector>
#include <sstream>

#include "SVGShape.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "IncorrectArgStrException.h"

SVGLine::SVGLine(std::vector<std::string> arguments) {
	if (arguments.size() != 5) {
		throw new IncorrectArgStrException;
	}

	try {
		AssignAttributeFromString(arguments[0], "x1", first_point.x);
		AssignAttributeFromString(arguments[1], "y1", first_point.y);
		AssignAttributeFromString(arguments[2], "x2", second_point.x);
		AssignAttributeFromString(arguments[3], "y2", second_point.y);
		if (ArgumentHoldsTheGivenAttributeName(arguments[4], "fill")) {
			color = GetAttributeValueStr(arguments[4]);
		} else {
			color = arguments[4];
		}
	}
	catch (IncorrectArgStrException* e) {
		throw e;
	}

}

void SVGLine::Translate(int horizontal, int vertical) {
	first_point.Translate(horizontal, vertical);
	second_point.Translate(horizontal, vertical);
}

std::string SVGLine::ToStringForConsole() {
	std::ostringstream content_sstream;
	content_sstream << "line " 
		<< first_point.x 
		<< " " << first_point.y 
		<< " "<< second_point.x 
		<< " " << second_point.y 
		<< " " << color;
	return content_sstream.str();
}

std::string SVGLine::ToString() {
	std::ostringstream content_sstream;
	content_sstream << "<line x1=\"" << first_point.x
		<< "\" y1=\"" << first_point.y
		<< "\" x2=\"" << second_point.x
		<< "\" y2=\"" << second_point.y
		<< "\" fill=\"" << color << "\" />";

	return content_sstream.str();
}

std::string SVGLine::ShapeType() {
	return "line";
}

bool SVGLine::IsWithinCircleArea(Circle circle_area) {
	if (first_point.IsInCircle(circle_area) && second_point.IsInCircle(circle_area)) {
		return true;
	} else {
		return false;
	}
}

bool SVGLine::IsWithinRectangleArea(Rectangle rect_area) {
	if (first_point.IsInRectangle(rect_area) && second_point.IsInRectangle(rect_area)) {
		return true;
	} else {
		return false;
	}
}

Point SVGLine::get_first_point() {
	return first_point;
}

Point SVGLine::get_second_point() {
	return second_point;
}