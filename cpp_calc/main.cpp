#include <iostream>
#include "calc.hpp"
using namespace std;


int main()
{
	string expression = "";
	string plugin_path = "./plugins/";
	Calculator calculator = Calculator(plugin_path);
	while (true) {
		getline(cin, expression);
		calculator.calculate(expression);
	}
	return 0;
}
