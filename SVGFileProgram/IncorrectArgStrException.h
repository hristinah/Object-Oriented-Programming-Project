#ifndef INCORRECTARGSTREXCEPT_H_
#define INCORRECTARGSTREXCEPT_H_

#include <exception>

class IncorrectArgStrException : public std::exception {
	virtual const char* what() const throw() {
		return "Incorrect arguments";
	}
};

#endif
