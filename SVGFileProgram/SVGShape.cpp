#include "SVGShape.h"
#include <string>
#include <vector>

#include "IncorrectArgStrException.h"

std::string SVGShape::get_color() {
	return color;
}

void SVGShape::AssignAttributeFromString(std::string argument, std::string attribute_name, int& attribute) {
	std::string arg_str;

	if (ArgumentHoldsTheGivenAttributeName(argument,attribute_name)) {
		try {
			arg_str = GetAttributeValueStr(argument);
		}
		catch (IncorrectArgStrException* e) {
			throw e;
		}
	}
	else {
		arg_str = argument;
	}

	try {
		attribute = std::stoi(arg_str, nullptr);
	}
	catch (...) {
		throw new IncorrectArgStrException;
	}
}

bool SVGShape::ArgumentHoldsTheGivenAttributeName(std::string argument, std::string attribute_name) {
	std::size_t pos_equals = PositionEqualsSign(argument);
	if (pos_equals != std::string::npos &&
		argument.substr(0, pos_equals) == attribute_name) {
		return true;
	}
	else {

	} return false;
}

std::size_t SVGShape::PositionEqualsSign(std::string argument) {
	return argument.find('=');
}

std::string SVGShape::GetAttributeValueStr(std::string argument) {
	std::size_t first_quot_mark, second_quot_mark;

	first_quot_mark= argument.find('"');
	if (first_quot_mark != std::string::npos) {
		second_quot_mark = argument.find('"', first_quot_mark+1);
	} else {
		second_quot_mark = std::string::npos;
	}

	if (first_quot_mark == std::string::npos || second_quot_mark == std::string::npos) {
		throw new IncorrectArgStrException;
	}

	return argument.substr(first_quot_mark+1, second_quot_mark - first_quot_mark - 1);
}