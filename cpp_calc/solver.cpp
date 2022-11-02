#include "solver.hpp"
#include <Windows.h>
using namespace std;

Solver::Solver() {}
Solver::Solver(string plugin_path) {
	set_plugin_path(plugin_path);
	_set_basic_functionality();
	set_additional_functionality();
}
Solver::Solver(vector<Token> tokenized_expression) {
	generate_rpn(tokenized_expression);
}

void Solver::clear_stacks() {
	while (!_operator_stack.empty()) {
		_operator_stack.pop();
	}
	while (!_value_stack.empty()) {
		_value_stack.pop();
	}
	while (!_output_rpn.empty()) {
		_output_rpn.pop_back();
	}
}
void Solver::set_plugin_path(string _plugin_path) {
	this->_plugin_path = _plugin_path;
}

void Solver::_get_func_from_dll(string filename) {
	HMODULE hm = LoadLibraryA((_plugin_path + filename).c_str());

	if (hm == nullptr) {
		throw std::exception("dll not found");
	}
	string func_name = filename.substr(0, filename.find(".dll"));
	function<double(double)> import_func = reinterpret_cast<double(*)(double)>(GetProcAddress(hm, "export_function"));
	if (!import_func) {
		throw std::exception("failed to load function");
	}
	this->_unary_function_list.push_back({ import_func, func_name });
}

void Solver::set_additional_functionality() {
	WIN32_FIND_DATAA wfd;
	HANDLE const hFind = FindFirstFileA((this->_plugin_path + std::string("*.dll")).c_str(), &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::string dllFileName(wfd.cFileName);
			_get_func_from_dll(dllFileName);
		} while (NULL != FindNextFileA(hFind, &wfd));
		FindClose(hFind);
	}
	else
	{
		throw std::exception("path not found");
	}
}

void Solver::_set_basic_functionality() {
	this->_binary_function_list.push_back({ [](double fst, double snd) { return fst + snd; }, "+" });
	this->_binary_function_list.push_back({ [](double fst, double snd) { return fst - snd; }, "-" });
	this->_binary_function_list.push_back({ [](double fst, double snd) { return fst * snd; }, "*" });
	this->_binary_function_list.push_back({ [](double fst, double snd) { return fst / snd; }, "/" });
}

BinFunction Solver::find_b_func(Token token) {
	string name = token.get_value();
	for (auto it : _binary_function_list) {
		if (it.get_name() == name) {
			return it;
		}
	}
	throw std::exception("no function found");
}

UnFunction Solver::find_u_func(Token token) {
	string name = token.get_value();
	for (auto it : _unary_function_list) {
		if (it.get_name() == name) {
			return it;
		}
	}
	throw std::exception("no function found");
}
double Solver::generate_ans() {
	UnFunction u_f = UnFunction();
	BinFunction b_f = BinFunction();
	for (auto token : _output_rpn) {
		if (token.is_number()) {
			_value_stack.push(stod(token.get_value()));
		}
		else if (token.is_function() && !_value_stack.empty()) {
			u_f = find_u_func(token);
			if (!_value_stack.empty()) {
				u_f.set_argument(_value_stack.top());
				_value_stack.pop();
				_value_stack.push(u_f.evaluate());
			}
		}
		else if (token.is_operator() && !_value_stack.empty()) {
			b_f = find_b_func(token);
			double snd_arg = _value_stack.top();
			_value_stack.pop();
			if (!_value_stack.empty()) {
				double fst_arg = _value_stack.top();
				_value_stack.pop();
				b_f.set_arguments(fst_arg, snd_arg);
			}
			_value_stack.push(b_f.evaluate());
		}
		else {
			throw std::exception("wrong operations order");
		}
	}
	return _value_stack.top();
}

void Solver::generate_rpn(vector<Token> tokenized_expression) {
	for (auto token : tokenized_expression) {
		if (token.is_number()) {
			this->_output_rpn.push_back(token);
		}
		if (token.is_function()) {
			_operator_stack.push(token);
		}
		if (token.is_operator()) {
			while ((!_operator_stack.empty()) && ((!_operator_stack.top().is_lbr()) && (_operator_stack.top().get_precedence() >= token.get_precedence()))) /*considering there`s no right-associative operations we`ll skip "||" condition*/ {
				this->_output_rpn.push_back(_operator_stack.top());
				_operator_stack.pop();
			}
			_operator_stack.push(token);
		}
		if (token.is_lbr()) {
			_operator_stack.push(token);
		}
		if (token.is_rbr()) {
			while (!_operator_stack.empty() && !_operator_stack.top().is_lbr()) {
				this->_output_rpn.push_back(_operator_stack.top());
				_operator_stack.pop();
			}
			if (_operator_stack.top().is_lbr()) {
				_operator_stack.pop();
			}
			if (_operator_stack.top().is_function()) {
				this->_output_rpn.push_back(_operator_stack.top());
				_operator_stack.pop();
			}
		}
	}
	while (!_operator_stack.empty()) {
		if (!_operator_stack.top().is_lbr()) {
			this->_output_rpn.push_back(_operator_stack.top());
		}
		_operator_stack.pop();
	}
};