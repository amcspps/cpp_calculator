#include <string>

// first int - parsing_key, second int - precedence, string - field value
using token = std::pair<std::pair<int, int>, std::string>;
//LBR = left bracket, RBR = right bracket
enum parsing_keys {
	LBR = 1,
	RBR = 2,
	OPERATOR = 3,
	FUNCTION = 4,
	NUMBER = 5
};

enum precedence {
	NO = -1, LOW = 0, HIGH = 2, VERY_HIGH = 3
};

class Token {
public:
	Token(token tkn);
	bool is_number();
	bool is_operator();
	bool is_function();
	bool is_lbr();
	bool is_rbr();
	int get_precedence();
	std::string get_value();
private:
	token _tkn;
	double _value;
};