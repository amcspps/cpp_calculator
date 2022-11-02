#include "function.hpp"
#include "token.hpp"


using namespace std;


Function::Function() {}

BinFunction::BinFunction() {}

UnFunction::UnFunction() {}

UnFunction::UnFunction(function<double(double)> fn, string name) {
	this->_fn = fn;
	this->_name = name;
}
BinFunction::BinFunction(function<double(double, double)> fn, string name) {
	this->_fn = fn;
	this->_name = name;
}

double UnFunction::evaluate() {
	return this->_fn(this->_arg);
}

double BinFunction::evaluate() {
	return this->_fn(this->_fst_arg, this->_snd_arg);
}

string Function::get_name() {
	return this->_name;
}

void UnFunction::set_argument(double arg) {
	this->_arg = arg;
}

void BinFunction::set_arguments(double fst, double snd) {
	this->_fst_arg = fst;
	this->_snd_arg = snd;
}

