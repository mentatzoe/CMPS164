#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "Level.h"
#include "Token.h"
#include "Course.h"

class LevelCreator
{
public:
	Level createLevel(TokenList tokenList);
    Course createCourse(TokenList tokenList);

private:
    Level createLevelInsideCourse(TokenList tokenList, std::__wrap_iter<Token*> curToken);
};

#endif /* LEVELCREATOR_H */