#ifndef PARSEMD_H
#define PARSEMD_H

#include "pageparser.h"
#include <vector>

class ParseMD : public PageParser{
	public:
		void parse(std::string filename, MySet<std::string>& allWords, MySet<std::string>& allLinks);
		void linksParse(std::string filename, std::vector<std::string>& links);
};

#endif