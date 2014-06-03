#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <vector>
#include <string>
#include <fstream>

#include "Token.h"

class FileParser
{
public:
	// Functions
	TokenList tokenize(std::string filename);
};

#endif /* FILEPARSER_H */