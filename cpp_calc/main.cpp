#include <iostream>
#include "calc.hpp"
using namespace std;


int main()
{
	string expression = "";
	string plugin_path = "C:\\test";
	Calculator calculator = Calculator(plugin_path);
	while (true) {
		getline(cin, expression);
		calculator.calculate(expression);
	}
	//string str = "6+(sin(cos(3/2+6)))+1";
	//Parser p = Parser();
	//p.tokenize_expression(str);
	//TODO try catch
	//Solver s = Solver(p.get_tokenized_expression());
	//p.parse_expression(str);
	//p.print_tokenized_expression();
	return 0;
}
