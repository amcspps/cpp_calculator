#include "parser.hpp"
#include <boost/regex.hpp>
Parser::Parser() {
	set_map();
};

void Parser::set_map() {
	this->mapping["("] = { LBR, VERY_HIGH };
	this->mapping[")"] = { RBR, VERY_HIGH };
	this->mapping["+"] = { OPERATOR, LOW };
	this->mapping["-"] = { OPERATOR, LOW };
	this->mapping["*"] = { OPERATOR, HIGH };
	this->mapping["/"] = { OPERATOR, HIGH };
	this->mapping["sin"] = { FUNCTION,VERY_HIGH };
	this->mapping["cos"] = { FUNCTION,VERY_HIGH };
	this->mapping["tan"] = { FUNCTION, VERY_HIGH };

}

void Parser::eliminate_spaces(string& to_eliminate) {
	to_eliminate.erase(remove_if(to_eliminate.begin(), to_eliminate.end(), isspace), to_eliminate.end());
}
void Parser::print_tokenized_expression() {
	for (auto element : this->_tokenized_expression) {
		cout << element.first.first << "," << element.first.second << endl;
	}
}

void Parser::tokenize_expression(string input) {
	vector <string> to_tokenize = parse_expression(input);
	/*regex number("([0-9]\.?[0-9]+)");*/
	for (auto element : to_tokenize) {
		switch (mapping[element].first) {
		case LBR:
			this->_tokenized_expression.push_back({ mapping[element], element });
			break;
		case RBR:
			this->_tokenized_expression.push_back({ mapping[element], element });
			break;
		case OPERATOR:
			this->_tokenized_expression.push_back({ mapping[element], element });
			break;
		case FUNCTION:
			this->_tokenized_expression.push_back({ mapping[element], element });
			break;
		default:
			/*if (!regex_match(element, number)) {
				cout << "unrecognized function or variable";
			}*/
			try {
				double val = stod(element);
			} catch (const std::exception& e) {
				cout << "unrecognized function" /*(" << e.what() << ")"*/;
			}
			break;
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