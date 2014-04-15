#include <vector>
#include <string>
#include <fstream>

#include "Token.h"

class FileParser
{
public:
	TokenList tokenize(std::string filename, char delim);
};