#include "SVGRectangle.h"

#include <string>
#include <vector>
#include <sstream>

#include "SVGShape.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "IncorrectArgStrException.h"

SVGRectangle::SVGRectangle(std::vector<std::string> arguments) {
	if (arguments.size() < 4 || arguments.size() > 5) {
		throw new IncorrectArgStrException;
	}

	try {
		AssignAttributeFromString(arguments[0], "x", dimensions.top_left_x);
		AssignAttributeFromString(arguments[1], "y", dimensions.top_left_y);
		AssignAttributeFromString(arguments[2], "width", dimensions.width);
		AssignAttributeFromString(arguments[3], "height", dimensions.height);

		if (arguments.size() == 5 && ArgumentHoldsTheGivenAttributeName(arguments[4], "fill")) {
			color = GetAttributeValueStr(arguments[4]);
		}
		else if (arguments.size() == 5) {
			color = arguments[4];
		}
		else {
			color = "transparent";
		}
	}
	catch (IncorrectArgStrException* e) {
		throw e;
	}
}

void SVGRectangle::Translate(int horizontal, int vertical) {
	dimensions.top_left_x += horizontal;
	dimensions.top_left_y += vertical;
}

std::string SVGRectangle::ToStringForConsole() {
	std::ostringstream content_sstream;
	content_sstream << "rectangle " 
		<< dimensions.top_left_x 
		<< " " << dimensions.top_left_y 
		<< " " << dimensions.width 
		<< " " << dimensions.height 
		<< " " << color;
	return content_sstream.str();
}

std::string SVGRectangle::ToString() {
	std::ostringstream content_sstream;
	content_sstream << "<rect x=\"" << dimensions.top_left_x
		<< "\" y=\"" << dimensions.top_left_y
		<< "\" width=\"" << dimensions.width
		<< "\" height=\"" << dimensions.height
		<< "\" fill=\"" << color << "\" />";

	return content_sstream.str();
}

std::string SVGRectangle::ShapeType() {
	return "rectangle";
}

bool SVGRectangle::IsWithinCircleArea(Circle circle_area) {
	Point top_left(dimensions.top_left_x, dimensions.top_left_y);
	Point bottom_left(dimensions.top_left_x, dimensions.top_left_y + dimensions.height);
	Point top_right(dimensions.top_left_x + dimensions.width, dimensions.top_left_y);
	Point bottom_right(dimensions.top_left_x + dimensions.width, dimensions.top_left_y + dimensions.height);

	if (top_left.IsInCircle(circle_area) && top_right.IsInCircle(circle_area) &&
		bottom_left.IsInCircle(circle_area) && bottom_right.IsInCircle(circle_area)) {
		return true;
	} else {
		return false;
	}
}

bool SVGRectangle::IsWithinRectangleArea(Rectangle rect_area) {
	Point top_left(dimensions.top_left_x, dimensions.top_left_y);
	Point bottom_left(dimensions.top_left_x, dimensions.top_left_y + dimensions.height);
	Point top_right(dimensions.top_left_x + dimensions.width, dimensions.top_left_y);
	Point bottom_right(dimensions.top_left_x + dimensions.width, dimensions.top_left_y + dimensions.height);

	if (top_left.IsInRectangle(rect_area) && top_right.IsInRectangle(rect_area) &&
		bottom_left.IsInRectangle(rect_area) && bottom_right.IsInRectangle(rect_area)) {
		return true;
	} else {
		return false;
	}
}

Rectangle SVGRectangle::get_dimensions() {
	return dimensions;
}