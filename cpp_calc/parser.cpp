#include "parser.hpp"
#include <boost/tokenizer.hpp>


using namespace boost;
using namespace std;


Parser::Parser() {
	_set_map();
}

void Parser::clear_stacks() {
	while (!_tokenized_expression.empty()) {
		_tokenized_expression.pop_back();
	}
}

void Parser::_set_map() {
	this->mapping["("] = { LBR, VERY_HIGH };
	this->mapping[")"] = { RBR, VERY_HIGH };
	this->mapping["+"] = { OPERATOR, LOW };
	this->mapping["-"] = { OPERATOR, LOW };
	this->mapping["*"] = { OPERATOR, HIGH };
	this->mapping["/"] = { OPERATOR, HIGH };

}

vector<Token> Parser::get_tokenized_expression() {
	return this->_tokenized_expression;
}

void Parser::eliminate_spaces(string& to_eliminate) {
	to_eliminate.erase(remove_if(to_eliminate.begin(), to_eliminate.end(), isspace), to_eliminate.end());
}


void Parser::tokenize_expression(string input) {
	// bracket check
	int bracket_count = 0;
	for (auto c : input) {
		if (c == '(') {
			bracket_count++;
		}
		if (c == ')') {
			bracket_count--;
		}
		if (bracket_count < 0) {
			throw invalid_argument("bracket error");
		}
	}
	if (bracket_count != 0) {
		throw invalid_argument("bracket error");
	}
	vector <string> to_tokenize = parse_expression(input);
	//eliminate minus
	for (int i = 0; i < to_tokenize.size(); i++) {
		if (to_tokenize[0].find("-") == 0) {
			to_tokenize[0 + 1].insert(0, "-");
			to_tokenize[0].replace(0, 1, "0");
			to_tokenize.insert(to_tokenize.begin() + 1, "+");
			i+=2;
		}
		else if ((to_tokenize[i].find("-") == 0 && to_tokenize[i-1] == "(")) {
			to_tokenize[i + 1].insert(0, "-");
			to_tokenize.insert(to_tokenize.begin() + i + 1, "+");
			to_tokenize[i].replace(0, 1, "0");
			i+=2;
			//to_tokenize[i].erase("-");
		}
	}
	for (auto element : to_tokenize) {
		if (mapping.find(element) != mapping.end()) {
			// if included in map
			this->_tokenized_expression.push_back({ { mapping[element], element} });
		}
		else {
			// else element either number or function
			try {
				double val = stod(element);
				this->_tokenized_expression.push_back({ { {NUMBER, NO}, element}});
			}
			catch (const std::invalid_argument& e) {
				this->_tokenized_expression.push_back({ { {FUNCTION, VERY_HIGH}, element} });
			}
		}
	}
}

vector <string> Parser::parse_expression(string to_separate) {
	eliminate_spaces(to_separate);
	vector <string> to_tokenize;
	boost::char_separator<char> sep("", "+-*/()");
	boost::tokenizer<boost::char_separator<char>> tok(to_separate, sep);
	for (auto it = tok.begin(); it != tok.end(); it++) {
		to_tokenize.push_back(*it);
	}
	return to_tokenize;
}