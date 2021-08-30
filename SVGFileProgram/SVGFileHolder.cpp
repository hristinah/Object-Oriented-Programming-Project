#include "SVGFileHolder.h"

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Circle.h"
#include "Rectangle.h"
#include "SVGShape.h"
#include "SVGCircle.h"
#include "SVGRectangle.h"
#include "SVGLine.h"
#include "SVGShapeFactory.h"
#include "StringSplitter.h"
#include "IncorrectArgStrException.h"

SVGFileHolder::~SVGFileHolder() {
    for (SVGShape* shape : data)
    {
        delete shape;
    }
    data.clear();
}

SVGFileHolder::SVGFileHolder(std::string file_nm) : file_name(file_nm) {
        std::ifstream infile(file_name);
        // check stream status
        if (infile) {
            FillDataFromIfstream(infile);
            std::cout << "Successfully opened " << file_name << std::endl;
            infile.close();
        } else {
            std::cout << "File " << file_name << " does not yet exist." << std::endl;
            std::ofstream outfile(file_name);
            if (outfile) {
                std::cout << "New empty file " << file_name << " was created." << std::endl;
                outfile.close();
            } else {
                std::cout << "New empty file " << file_name << " could not be created." << std::endl;
                throw new IncorrectArgStrException;
            }
        }
}

void SVGFileHolder::FillDataFromIfstream(std::ifstream& infile) {
    std::string shape_data;
    while (!infile.eof())
	{
		infile.ignore(256, '<');
		std::getline(infile, shape_data, '>');
        if (!shape_data.empty()) {
            try {
                std::vector<std::string> shape_arguments = StringSplitter::split_in_words(shape_data);
                SVGShape* new_shape = SVGShapeFactory::NewSVGShape(shape_arguments);
                if (new_shape->get_color() != "transparent") {
                    data.push_back(new_shape);
                }
                else {
                    delete new_shape;
                }
            }
            catch (IncorrectArgStrException* e) {
                delete e;
            }
        }
        shape_data.clear();
	}
}



std::string SVGFileHolder::Save() {
    return SaveAs(file_name);
}

std::string  SVGFileHolder::SaveAs(std::string file_nm) {
    std::ostringstream message;
    std::ofstream outfile(file_nm);
    if (outfile) {
        for (SVGShape* shape : data) {
            outfile << shape->ToString() << std::endl;
        }
        message << "Successfully saved " << file_nm << ".\n";
        outfile.close();
    } else {
        message << file_nm << " could not be saved.\n";
    }
    return message.str();
}



std::string SVGFileHolder::Print() {
    std::ostringstream content_sstream;
    for (size_t i = 0; i < data.size(); i++) {
        content_sstream << i + 1 << ". " << data[i]->ToStringForConsole() << "\n";
    }
    return content_sstream.str();
}

std::string SVGFileHolder::Erase(std::vector<std::string> arguments) {
    std::ostringstream message;
    if (arguments.size() == 1) {
        try {
            int index = std::stoi(arguments[0], nullptr) - 1;
            int index_last_data = data.size() - 1;
            if (index >= 0 && index <= index_last_data) {
                message << "Erased a " << data[index]->ShapeType() << " (" << index + 1 << ").\n";
                delete data[index];
                data.erase(data.begin() + index);
            } else {
                message << "There is no figure number "<<index+1<<"!\n";
            }
        }
        catch (...) {
            message << "Incorrect arguments.\n";
        }
    } else {
        message << "Incorrect number of arguments.\n";
    }
    return message.str();
}

std::string SVGFileHolder::Create(std::vector<std::string> arguments) {
    std::ostringstream message;
	if (arguments.size() > 1) {
		try {
			SVGShape* new_shape = SVGShapeFactory::NewSVGShape(arguments);
			if (new_shape->get_color() != "transparent") {
				data.push_back(new_shape);
				message << "Successfully created " << arguments[0] << " (" << data.size() << ").\n";
			}
			else {
				message << "Incorrect number of arguments.\n";
				delete new_shape;
			}
		}
		catch (IncorrectArgStrException* e) {
			delete e;
			message << "Incorrect arguments.\n";
		}
	} else {
        message << "Incorrect number of arguments.\n";
    }
    return message.str();
}

std::string SVGFileHolder::Translate(std::vector<std::string> arguments) {
    std::ostringstream message;

	if (arguments.size() == 2) {
		try {
			int horizontal, vertical;
			SVGShape::AssignAttributeFromString(arguments[0], "vertical", vertical);
			SVGShape::AssignAttributeFromString(arguments[1], "horizontal", horizontal);
            for (SVGShape* shape : data) {
                shape->Translate(horizontal, vertical);
            }
            message << "Translated all figures.\n";
		}
		catch (IncorrectArgStrException* e) {
			delete e;
			message << "Incorrect arguments.\n";
		}
	} else {
		message << "Incorrect number of arguments.\n";
	}

	return message.str();
}

std::string SVGFileHolder::Within(std::vector<std::string> arguments) {
	std::ostringstream message;
	if (arguments.size() > 2) {
		try {
			std::string shape_name = arguments[0];
			arguments.erase(arguments.begin());

			if (shape_name == "circle") {
				SVGCircle area = SVGCircle(arguments);
                message << WithinCircleArea(area.get_dimensions());
			} else if (shape_name == "rectangle") {
				SVGRectangle area = SVGRectangle(arguments);
                message << WithinRectangleArea(area.get_dimensions());
			} else {
                message << "Incorrect shape.\n";
			}
		}
		catch (IncorrectArgStrException* e) {
            delete e;
            message << "Incorrect arguments.\n";
		}
	} else {
		message << "Incorrect number of arguments\n";
	}
	return message.str();
}

std::string SVGFileHolder::WithinCircleArea(Circle circle_area) {
    std::ostringstream message;
    bool exists_shape_in_area = false;

    for (size_t i=0; i < data.size(); i++) {
        if (data[i]->IsWithinCircleArea(circle_area)) {
            exists_shape_in_area = true;
            message << i + 1 << ". " << data[i]->ToStringForConsole() << "\n";
        }
    }
    if (exists_shape_in_area == false) {
        message << "No shapes are located within circle "<<circle_area.center_x<<" "<<
            circle_area.center_y << " " << circle_area.radius << ".\n";
    }
    return message.str();
}

std::string SVGFileHolder::WithinRectangleArea(Rectangle rect_area) {
    std::ostringstream message;
    bool exists_shape_in_area = false;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i]->IsWithinRectangleArea(rect_area)) {
            exists_shape_in_area = true;
            message << i + 1 << ". " << data[i]->ToStringForConsole() << "\n";
        }
    }
    if (exists_shape_in_area == false) {
        message << "No shapes are located within rectangle " << rect_area.top_left_x <<" " <<
            rect_area.top_left_y << " " << rect_area.width << " " << rect_area.height << ".\n";
    }
    return message.str();
}
