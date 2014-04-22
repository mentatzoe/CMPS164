#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "Level.h"
#include "Token.h"

class LevelCreator
{
public:
	Level createLevel(TokenList tokenList);
};

#endif /* LEVELCREATOR_H */