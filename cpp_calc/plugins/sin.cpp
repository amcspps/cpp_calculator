#include <cmath>

extern "C" __declspec(dllexport)
double export_function(double x) {
	return sin(x);
}