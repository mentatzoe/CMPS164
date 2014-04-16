#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <string>

struct Token {
	std::string data;
};

typedef std::vector<Token> TokenList;

#endif /* TOKEN_H */