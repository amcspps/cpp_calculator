#include <iostream>
#include "parser.hpp"


using namespace std;


int main()
{
	string str = " sin( 3 )+cos(  4.5 )-2 * 3+1/5)";
	Parser p = Parser();
	//p.parse_expression(str);
	p.tokenize_expression(str);
	p.print_tokenized_expression();
	return 0;
}
