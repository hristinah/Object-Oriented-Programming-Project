#ifndef SVGFILEHOLDER_H_
#define SVGFILEHOLDER_H_

#include <string>
#include <vector>
#include <fstream>

#include "SVGShape.h"
#include "SVGCircle.h"
#include "SVGRectangle.h"
#include "SVGLine.h"

class SVGFileHolder {
public:
	/* Attempts to open a file with the given name. If such a file exists, calls FillDataFromIfstream(),
	otherwise creates a new empty file with the same name, and data remains empty.
	Finally the file is closed.
	IncorrectArgStrException is thrown if file could not be opened, nor created.*/
	SVGFileHolder(std::string file_nm);
	~SVGFileHolder();

	/*The following return a string message for SVGProgram.Run() to print to the console */
	std::string Save();
	std::string SaveAs(std::string file_nm);
	std::string Print();
	std::string Erase(std::vector<std::string> arguments);
	std::string Create(std::vector<std::string> arguments);
	std::string Translate(std::vector<std::string> arguments);
	std::string Within(std::vector<std::string> arguments);

private:
	std::string WithinCircleArea(Circle circle_area);
	std::string WithinRectangleArea(Rectangle rect_area);
	/*Tries to create a new shape from any string between "<" and "/>". The new shape is pushed back to the 
	data vector only if it's valid (NewSVGShape() has not thrown exeption and the shape is not "transparent") */
	void FillDataFromIfstream(std::ifstream& infile);

	std::string file_name;
	std::vector<SVGShape*> data;
};

#endif

