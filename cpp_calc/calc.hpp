#pragma once
#include "parser.hpp"
#include "solver.hpp"
#include "function.hpp"


class Calculator {
public:
	Calculator(std::string plugin_path);
	void calculate(std::string expression);
private:
	Parser _parser;
	Solver _solver;
};