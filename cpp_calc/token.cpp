#include "token.hpp"

using namespace std;

Token::Token(token tkn) {
	this->_tkn = tkn;
	this->_value = 0;
};
string Token::get_value() {
	return this->_tkn.second;
};
bool Token::is_number() {
	return this->_tkn.first.first == NUMBER;
}
bool Token::is_operator() {
	return this->_tkn.first.first == OPERATOR;
}

bool Token::is_function() {
	return this->_tkn.first.first == FUNCTION;
}

bool Token::is_lbr() {
	return this->_tkn.first.first == LBR;
}
bool Token::is_rbr() {
	return this->_tkn.first.first == RBR;
}
int Token::get_precedence() {
	return this->_tkn.first.second;
}