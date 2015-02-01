#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <string>

struct Token {
	// Member Variables
	std::string data;
};

// Container Type Definition
typedef std::vector<Token> TokenList;

#endif /* TOKEN_H */