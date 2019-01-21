#include "vector2.h"

// -- Constructor --
vector2::vector2() {}

vector2::vector2(float a, float b) {
	_a = a;
	_b = b;
}

vector2::vector2(std::tuple<float, float> vc2) {
	_a = std::get<0>(vc2);
	_b = std::get<1>(vc2);
}


// -- Data --
float* vector2::data() {
	float* v = new float[2];

	v[0] = _a;
	v[1] = _b;

	return v;
}


// -- Read --
vector2 vector2::readVc2() {
	std::string aAux, bAux;
	float a, b;

	std::cout << "A vector 2D have the structure v = (a, b)\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);

	a = std::stof(aAux);
	b = std::stof(bAux);

	vector2 v(a, b);
	std::cout << "The vector " << "(" << a << ", " << b << ") " << "was created\n";

	return v;
}

// -- Print --
void vector2::printVc2() {
	std::cout << "(" << _a << "," << _b << ")" << "\n";
}


// Overloading operator =
vector2 vector2::operator=(const vector2& v2) {
	vector2 vCopy(v2._a, v2._b);

	return vCopy;
}


// Overloading operator ==
bool vector2::operator==(const vector2& v2) {
	return _a == v2._a && _b == v2._b;
}


// Overloading operator +
vector2 vector2::operator+(const vector2& v2) {
	float a = _a + v2._a;
	float b = _b + v2._b;

	vector2 auxVc(a, b);
	return auxVc;
}


// Overloading operator -
vector2 vector2::operator-(const vector2& v2) {
	float a = _a - v2._a;
	float b = _b - v2._b;

	vector2 auxVc(a, b);
	return auxVc;
}


// Overloading operator *
vector2 vector2::operator*(const float x) {
	float a = _a * x;
	float b = _b * x;

	vector2 auxVc(a, b);
	return auxVc;
}