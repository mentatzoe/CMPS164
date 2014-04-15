#include <cstdlib>
#include <cassert>
#include "FileParser.h"

int main(int argc, char* argv[])
{
	assert(argc == 2);
	FileParser parser;

	TokenList list = parser.tokenize(argv[1], ' ');

	



	system("pause");
	return 0;
}