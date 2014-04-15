#include "FileParser.h"

TokenList FileParser::tokenize(std::string filename, char delim)
{
	std::ifstream myFile(filename);
	TokenList tokenList;
	std::string item;

	if (myFile.is_open())
	{
		while (std::getline(myFile, item, delim))
		{
			Token token;
			token.data = item;
			tokenList.push_back(token);
		}
	}

	return tokenList;
}