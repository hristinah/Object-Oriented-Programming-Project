#ifndef SVGSHAPE_H_
#define SVGSHAPE_H_

#include <string>
#include <vector>

#include "IncorrectArgStrException.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"

class SVGShape {
public:
	virtual ~SVGShape() {
	}

	virtual void Translate(int horizontal, int vertical) = 0;
	virtual std::string ToString() = 0;
	virtual std::string ToStringForConsole() = 0;
	virtual std::string ShapeType() = 0;
	virtual bool IsWithinCircleArea(Circle circle_area) = 0;
	virtual bool IsWithinRectangleArea(Rectangle rect_area) = 0;

	/*Assigns a value to the given numeric attribute, or throws IncorrectArgStrException
	if argument is invalid.*/
	static void AssignAttributeFromString(std::string argument, std::string attribute_name, int& attribute);
	/*In SVG files the '=' sign separates the arguments name and value, so its existance
	is a good indicator that the argument we are currently working with is in SVG file format */
	static std::size_t PositionEqualsSign(std::string argument);
	static bool ArgumentHoldsTheGivenAttributeName(std::string argument, std::string attribute_name);
	/*Returns the argument's substring representing its value in SVG file format.
	Throws an IncorrectArgStrException if such a substring does not exist*/
	static std::string GetAttributeValueStr(std::string argument);
	
	std::string get_color();

protected:
	std::string color;
};

#endif  

