#include "FileParser.h"
#include <sstream>

TokenList FileParser::tokenize(std::string filename)
{
	std::ifstream myFile(filename);
	TokenList tokenList;
	std::string item;
    
	if (myFile.is_open())
	{
		while (std::getline(myFile, item, '\n'))
		{
			std::istringstream buf(item);
			std::istream_iterator<std::string> beg(buf), end;

			std::vector<std::string> tokens(beg, end);

			for (auto& s : tokens){
				Token token;
				token.data = s;
				tokenList.push_back(token);
			}
		}
	} else {
        printf ("File doesn't exist \n");
        exit (EXIT_FAILURE);
    }

	return tokenList;
}