#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/tokenizer.hpp>
using namespace std;
using namespace boost;
// first int - parsing_key, second int - priority, string - field value
using token = pair<pair<int, int>, string>;

enum parsing_keys {
	LBR = 1,
	RBR = 2,
	OPERATOR = 3,
	FUNCTION = 4,
};

enum priorities {
	NO = -1, LOW = 0, MID = 1, HIGH = 2, VERY_HIGH = 3
};

class Parser {
public:
	Parser();
	void eliminate_spaces(string& to_eleminate);
	vector <string> parse_expression(string to_separate);
	void tokenize_expression(string input);
	void print_tokenized_expression();
	void set_map();
private:
	std::map <string, pair<int, int>> mapping;
	vector<token> _tokenized_expression;
};