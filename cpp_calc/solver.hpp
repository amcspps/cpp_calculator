#pragma once
#include <stack>
#include "parser.hpp"
#include "function.hpp"


class Solver {
public:
	Solver();
	Solver(std::string plugin_path);
	Solver(std::vector<Token> tokenized_expression);
	void generate_rpn(std::vector<Token> tokenized_expression);
	double generate_ans();
	UnFunction find_u_func(Token token);
	BinFunction find_b_func(Token token);
	
	void set_additional_functionality();
	void set_plugin_path(std::string plugin_path);
	void clear_stacks();
private:
	void _get_func_from_dll(std::string filename);
	void _set_basic_functionality();
	std::string _plugin_path;
	std::vector <BinFunction> _binary_function_list;
	std::vector <UnFunction> _unary_function_list;
	std::stack<Token> _operator_stack;
	std::stack<double> _value_stack;
	std::vector<Token> _output_rpn;

};