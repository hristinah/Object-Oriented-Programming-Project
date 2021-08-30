#include "SVGCircle.h"

#include <string>
#include <vector>
#include <sstream>

#include "SVGShape.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "IncorrectArgStrException.h"

SVGCircle::SVGCircle(std::vector<std::string> arguments) {
	if (arguments.size() < 3 || arguments.size() > 4) {
		throw new IncorrectArgStrException;
	}

	try {
		AssignAttributeFromString(arguments[0], "cx", dimensions.center_x);
		AssignAttributeFromString(arguments[1], "cy", dimensions.center_y);
		AssignAttributeFromString(arguments[2], "r", dimensions.radius);

		if (arguments.size() == 4 && ArgumentHoldsTheGivenAttributeName(arguments[3], "fill")) {
			color = GetAttributeValueStr(arguments[3]);
		} else if (arguments.size() == 4) {
			color = arguments[3];
		} else {
			color = "transparent";
		}
	}
	catch (IncorrectArgStrException* e) {
		throw e;
	}
}

void SVGCircle::Translate(int horizontal, int vertical) {
	dimensions.center_x += horizontal;
	dimensions.center_y += vertical;
}

std::string SVGCircle::ToStringForConsole() {
	std::ostringstream content_sstream;
	content_sstream << "circle " 
		<< dimensions.center_x 
		<< " " << dimensions.center_y 
		<< " " << dimensions.radius 
		<< " " << color;
	return content_sstream.str();
}

std::string SVGCircle::ToString() {
	std::ostringstream content_sstream;
	content_sstream << "<circle cx=\"" << dimensions.center_x
		<< "\" cy=\"" << dimensions.center_y
		<< "\" r=\"" << dimensions.radius
		<< "\" fill=\"" << color << "\" />";

	return content_sstream.str();
}

std::string SVGCircle::ShapeType() {
	return "circle";
}

bool SVGCircle::IsWithinCircleArea(Circle circle_area) {
	circle_area.radius -= dimensions.radius;
	Point center(dimensions.center_x, dimensions.center_y);

	if (circle_area.radius >= 0 && center.IsInCircle(circle_area)) {
		return true;
	} else {
		return false;
	}
}

bool SVGCircle::IsWithinRectangleArea(Rectangle rect_area) {
	rect_area.top_left_x += dimensions.radius;
	rect_area.top_left_y += dimensions.radius;
	rect_area.height -= 2 * dimensions.radius;
	rect_area.width -= 2 * dimensions.radius;
	Point center(dimensions.center_x, dimensions.center_y);

	if (rect_area.height >= 0 && rect_area.width >= 0 && center.IsInRectangle(rect_area)) {
		return true;
	} else {
		return false;
	}
}

Circle SVGCircle::get_dimensions() {
	return dimensions;
}

