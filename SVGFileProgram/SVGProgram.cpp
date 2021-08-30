#include "SVGProgram.h"

#include <string>
#include <vector>
#include <iostream>

#include "SVGFileHolder.h"
#include "StringSplitter.h"
#include "IncorrectArgStrException.h"

SVGProgram::SVGProgram() {
	loaded_file = nullptr;
	has_loaded_file = false;
}

SVGProgram::~SVGProgram() {
	if (loaded_file != nullptr) {
		delete loaded_file;
	}
}

void SVGProgram::Run() {
	PrintInstructions();
	State runtime_state = State::Ok;
	std::string command_and_arg;

	while (runtime_state == State::Ok) {
		std::getline(std::cin, command_and_arg);
		std::vector<std::string> arguments = StringSplitter::split_in_words(command_and_arg);
		std::string command_name = arguments[0];
		arguments.erase(arguments.begin());

		if (command_name == "open") {
			runtime_state = Open(arguments);
		} else if (command_name == "exit" && arguments.empty()) {
			runtime_state = Exit();
		} else if (command_name == "close" && arguments.empty()) {
			runtime_state = Close();
		} else if (command_name == "save" && arguments.empty()) {
			runtime_state = Save();
		} else if (command_name == "saveas") {
			runtime_state = SaveAs(arguments);
		} else if (command_name == "print" && arguments.empty()) {
			runtime_state = Print();
		} else if (command_name == "erase") {
			runtime_state = Erase(arguments);
		} else if (command_name == "create") {
			runtime_state = Create(arguments);
		} else if (command_name == "translate") {
			runtime_state = Translate(arguments);
		} else if (command_name == "within") {
			runtime_state = Within(arguments);
		} else {
			std::cout << "No such command exists." << std::endl;
			PrintInstructions();
		}
		std::cout << std::endl;
	}
	std::cout << "Exit" << std::endl;
}

void SVGProgram::PrintInstructions() {
	std::cout << "   Command list   " << std::endl
		<< "1) open file_name" << std::endl
		<< "2) close" << std::endl
		<< "3) save" << std::endl
		<< "4) saveas file_name" << std::endl
		<< "5) print" << std::endl
		<< "6) erase shape_number" << std::endl
		<< "7) create shape_name shape_attributes" << std::endl
		<< "8) translate vertical=\"x\" horizontal = \"y\"" << std::endl
		<< "9) within circle/rectangle shape_attributes" << std::endl
		<< "10) exit" << std::endl << std::endl;
}



SVGProgram::State SVGProgram::Open(std::vector<std::string> arguments) {
	if (arguments.size() != 1) {
		std::cout << "Incorrect arguments." << std::endl;
		return State::Ok;
	} else if (has_loaded_file == true) {
		std::cout << "Another file is already open. Please close it and try again." << std::endl;
		return State::Ok;
	} else {
		try {
			loaded_file = new SVGFileHolder(arguments[0]);
			has_loaded_file = true;
			return State::Ok;
		}
		catch (...) {
			return State::Exit;
		}
	}
}

SVGProgram::State SVGProgram::Exit() {
	return State::Exit;
}

SVGProgram::State SVGProgram::Close() {
	if (has_loaded_file == true && loaded_file != nullptr) {
		delete loaded_file;
		loaded_file = nullptr;
		has_loaded_file = false;
		std::cout << "The file has been succesfully closed." << std::endl;
		return State::Ok;
	} else {
		std::cout << "A file is not currently open. Please open a file and try again." << std::endl;
		return State::Ok;
	}
}

SVGProgram::State SVGProgram::Save() {
	if (has_loaded_file == true && loaded_file != nullptr) {
		std::cout << loaded_file->Save();
		return State::Ok;
	} else {
		std::cout << "There is no content to be saved. Please open a file and try again." << std::endl;
		return State::Ok;
	}
}

SVGProgram::State SVGProgram::SaveAs(std::vector<std::string> arguments) {
	if (arguments.size() != 1) {
		std::cout << "Incorrect arguments." << std::endl;
		return State::Ok;
	} else if (has_loaded_file == true && loaded_file != nullptr) {
		std::cout << loaded_file->SaveAs(arguments[0]);
		return State::Ok;
	} else {
		std::cout << "There is no file to be saved. Please open a file and try again." << std::endl;
		return State::Ok;
	}
}

SVGProgram::State SVGProgram::Print() {
	if (has_loaded_file == true && loaded_file != nullptr) {
		std::cout << loaded_file->Print();
		return State::Ok;
	} else {
		std::cout << "There is no content to be printed. Please open a file and try again." << std::endl;
		return State::Ok;
	}
}

SVGProgram::State SVGProgram::Erase(std::vector<std::string> arguments) {
	if (has_loaded_file == true && loaded_file != nullptr) {
		std::cout << loaded_file->Erase(arguments);
		return State::Ok;
	} else {
		std::cout << "There is no content to be erased. Please open a file and try again." << std::endl;
		return State::Ok;
	}
}

SVGProgram::State SVGProgram::Create(std::vector<std::string> arguments) {
	if (has_loaded_file == true && loaded_file != nullptr) {
		std::cout << loaded_file->Create(arguments);
		return State::Ok;
	} else {
		std::cout << "You cannot create shapes, before choosing a file to save them in." << std::endl 
			<< "Please open a file and try again." << std::endl;
		return State::Ok;
	}
}

SVGProgram::State SVGProgram::Translate(std::vector<std::string> arguments) {
	if (has_loaded_file == true && loaded_file != nullptr) {
		std::cout << loaded_file->Translate(arguments);
		return State::Ok;
	}
	else {
		std::cout << "There is no content to be translated. Please open a file and try again." << std::endl;
		return State::Ok;
	}
}

SVGProgram::State SVGProgram::Within(std::vector<std::string> arguments) {
	if (has_loaded_file == true && loaded_file != nullptr) {
		std::cout << loaded_file->Within(arguments);
		return State::Ok;
	}
	else {
		std::cout << "There is no content to be checked. Please open a file and try again." << std::endl;
		return State::Ok;
	}
}
