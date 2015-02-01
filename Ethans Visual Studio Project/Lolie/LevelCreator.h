#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "Level.h"
#include "Token.h"
#include "Course.h"

class LevelCreator
{
public:
	// Functions
	Level createLevel(TokenList tokenList);
    Course createCourse(TokenList tokenList);
};

#endif /* LEVELCREATOR_H */