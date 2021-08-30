#ifndef SVGSHAPEFACTORY_H_
#define SVGSHAPEFACTORY_H_

#include <string>
#include <vector>

#include "SVGShape.h"
#include "SVGCircle.h"
#include "SVGRectangle.h"
#include "SVGLine.h"
#include "IncorrectArgStrException.h"

class SVGShapeFactory
{
public:
    static SVGShape* NewSVGShape(std::vector<std::string> arguments)
    {
		if (arguments.size() < 2) {
            throw new IncorrectArgStrException;
        } else {
			SVGShape* new_shape=nullptr;
			std::string shape_name = arguments[0];
			arguments.erase(arguments.begin());

			try {
				if (shape_name == "circle") {
					new_shape = new SVGCircle(arguments);
				} else if (shape_name == "rectangle" || shape_name == "rect") {
					new_shape = new SVGRectangle(arguments);
				} else if (shape_name == "line") {
					new_shape = new SVGLine(arguments);
				} else {
					throw new IncorrectArgStrException;
				}
			}
			catch (IncorrectArgStrException* e) {
					throw e;
				}
			return new_shape;
		}
	}
};

#endif