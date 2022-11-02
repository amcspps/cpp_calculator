#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "token.hpp"


class Parser {
public:
	Parser();
	void eliminate_spaces(std::string& to_eleminate);
	std::vector <std::string> parse_expression(std::string to_separate);
	void tokenize_expression(std::string input);
	void print_tokenized_expression();
	void set_map();
	std::vector<Token> get_tokenized_expression();
	void clear_stacks();
private:
	std::map <std::string, std::pair<int, int>> mapping;
	std::vector<Token> _tokenized_expression;
};