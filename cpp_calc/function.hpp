#pragma once
#include <string>
#include <functional>

class Function {
public:
	Function();
	std::string get_name();
	~Function() = default;
protected:
	std::string _name;
};

class UnFunction : public Function {
public:
	UnFunction();
	UnFunction(std::function<double(double)> fn, std::string name);
	void set_argument(double arg);
	double evaluate();
	~UnFunction() = default;
private:
	std::function <double(double)> _fn;
	double _arg;
};

class BinFunction:public Function {
public:
	BinFunction();
	BinFunction(std::function<double(double, double)> fn, std::string name);
	double evaluate();
	void set_arguments(double fst, double snd);
	~BinFunction() = default;
private:
	std::function <double(double, double)> _fn;
	double _fst_arg;
	double _snd_arg;
};