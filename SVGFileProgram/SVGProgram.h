#ifndef SVGPROGRAM_H_
#define SVGPROGRAM_H_

#include <string>
#include <vector>
#include <iostream>

#include "SVGFileHolder.h"

class SVGProgram
{
public:
	enum class State {
		Ok,
		Exit
	};

	SVGProgram();
	~SVGProgram();

	void Run();
	void PrintInstructions();
	
private:
	/*Returns State::Ok if a new FileHolder was succesfuly created, and has_loaded_file becomes true.
	Returns State::Ok if an incorrect number of arguments was passed or if there already is a loaded file,
	without changing anything.
	Returns State::Exit if file could not be opened, nor created.*/
	State Open(std::vector<std::string> arguments);
	/*Allways returns State::Exit*/
	State Exit();
	/*The following allways return State::Ok*/
	State Close();
	State Save();
	State SaveAs(std::vector<std::string> arguments);
	State Print();
	State Erase(std::vector<std::string> arguments);
	State Create(std::vector<std::string> arguments);
	State Translate(std::vector<std::string> arguments);
	State Within(std::vector<std::string> arguments);

	SVGFileHolder* loaded_file;
	bool has_loaded_file;
};

#endif

