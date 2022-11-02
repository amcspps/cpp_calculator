#include "calc.hpp"

using namespace std;

Calculator::Calculator(string plugin_path) {
	this->_parser = Parser();
	this->_solver = Solver(plugin_path);
}

void Calculator::calculate(string expression) {
	_parser.tokenize_expression(expression);
	_solver.generate_rpn(_parser.get_tokenized_expression());
	cout << _solver.generate_ans() << endl;
	_solver.clear_stacks();
	_parser.clear_stacks();


}