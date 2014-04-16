#include <cstdlib>
#include <cassert>
#include <iostream>
#include "FileParser.h"
#include "LevelCreator.h"

int main(int argc, char* argv[])
{
	assert(argc == 2);
	FileParser parser;

	TokenList list = parser.tokenize(argv[1]);

	std::cout << "FILEPARSER CHECK:\n";
	for (int i = 0; i < list.size(); i++){
		std::cout << "   list[" << i << "] = \"" << list[i].data << "\"\n";
	}

	LevelCreator creator;

	Level test = creator.createLevel(list);



	system("pause");
	return 0;
}