#ifndef STRINGSPLITTER_H_
#define STRINGSPLITTER_H_

#include <string>
#include <sstream>
#include <vector>

class StringSplitter {
public:
	static std::vector<std::string> split_in_words(std::string str) {
		std::string word;
		std::vector<std::string> words;
		std::istringstream inp_str_stream(str);

		while (std::getline(inp_str_stream, word, ' ')) {
			if (!word.empty() && word != "/") {
				words.push_back(word);
			}
		}
		return words;
	}
};

#endif