#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include <algorithm>

#include "vector.h"

// -- Constructor --
// Vector2
vector2::vector2(float a, float b) {
	_a = a;
	_b = b;

	//_vc = std::make_tuple(a, b);
}

vector2::vector2(std::tuple<float, float> vc2) {
	_a = std::get<0>(vc2);
	_b = std::get<1>(vc2);
}

// Vector3
vector3::vector3(float a, float b, float c) {
	_a = a;
	_b = b;
	_c = c;
}

vector3::vector3(std::tuple<float, float, float> vc3) {
	_a = std::get<0>(vc3);
	_b = std::get<1>(vc3);
	_c = std::get<2>(vc3);
}

// Vector4
vector4::vector4(float a, float b, float c, float d) {
	_a = a;
	_b = b;
	_c = c;
	_d = d;
}

vector4::vector4(std::tuple<float, float, float, float> vc4) {
	_a = std::get<0>(vc4);
	_b = std::get<1>(vc4);
	_c = std::get<2>(vc4);
	_d = std::get<3>(vc4);
}

// Data
// Vector 2
float* vector2::data() {
	float* v = new float[2];

	v[0] = _a;
	v[1] = _b;

	return v;
}

// Vector 3
float* vector3::data() {
	float* v = new float[3];

	v[0] = _a;
	v[1] = _b;
	v[2] = _c;

	return v;
}

// Vector 4
float* vector4::data() {
	float* v = new float[4];

	v[0] = _a;
	v[1] = _b;
	v[2] = _c;
	v[3] = _d;
	
	return v;
}
// -- Read --
// Vector 2
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

// Vector 3
vector3 vector3::readVc3() {
	std::string aAux, bAux, cAux;
	float a, b, c;

	std::cout << "A vector 3D have the structure v = (a, b, c)\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);
	std::cout << "Please introduce your c:\n";
	getline(std::cin, cAux);

	a = std::stof(aAux);
	b = std::stof(bAux);
	c = std::stof(cAux);

	vector3 v (a, b, c);
	std::cout << "The vector " << "(" << a << ", " << b << ", " << c << ") " << "was created\n";

	return v;
}

// Vector 4
vector4 vector4::readVc4() {
	std::string aAux, bAux, cAux, dAux;
	float a, b, c, d;

	std::cout << "A vector 4D have the structure v = (a, b, c, d)\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);
	std::cout << "Please introduce your c:\n";
	getline(std::cin, cAux);
	std::cout << "Please introduce your d:\n";
	getline(std::cin, dAux);

	a = std::stof(aAux);
	b = std::stof(bAux);
	c = std::stof(cAux);
	d = std::stof(dAux);

	vector4 v(a, b, c, d);
	std::cout << "The vector " << "(" << a << ", " << b << ", " << c << ", " << d << ") " << "was created\n";

	return v;
}


// -- Print --
void vector2::printVc2() {
	std::cout << "(" << _a << "," << _b << ")" << "\n";
}

void vector3::printVc3() {
	std::cout << "(" << _a << "," << _b << "," << _c << ")" << "\n";
}

void vector4::printVc4() {
	std::cout << "(" << _a << "," << _b << "," << _c << "," << _d  << ")" << "\n";
}

// Overloading operator =
// Matrix 2x2
vector2 vector2::operator=(const vector2& v2) {
	vector2 vCopy (v2._a, v2._b);

	return vCopy;
}

// Matrix 3x3
vector3 vector3::operator=(const vector3& v) {
	vector3 vCopy (v._a, v._b, v._c);

	return vCopy;
}

// Matrix 4x4
vector4 vector4::operator=(const vector4& v) {
	vector4 vCopy (v._a, v._b, v._c, v._d);

	return vCopy;
}

// Overloading operator ==
//don't forget --> in c++ true is 1 and false is 0
bool vector2::operator==(const vector2& v2) {
	return _a == v2._a && _b == v2._b;
}

bool vector3::operator==(const vector3& vc3) {
	return _a == vc3._a && _b == vc3._b && _c == vc3._c;
}

bool vector4::operator==(const vector4& vc4) {
	return _a == vc4._a && _b == vc4._b && _c == vc4._c && _d == vc4._d;
}


// Overloading operator +
vector2 vector2::operator+(const vector2& v2) {
	float a = _a + v2._a;
	float b = _b + v2._b;

	vector2 auxVc(a, b);
	return auxVc;
}

vector3 vector3::operator+(const vector3& vc3) {
	float a = _a + vc3._a;
	float b = _b + vc3._b;
	float c = _c + vc3._c;

	vector3 auxVc(a, b, c);
	return auxVc;
}

vector4 vector4::operator+(const vector4& vc4) {
	float a = _a + vc4._a;
	float b = _b + vc4._b;
	float c = _c + vc4._c;
	float d = _d + vc4._d;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}


// Overloading operator -
vector2 vector2::operator-(const vector2& v2) {
	float a = _a - v2._a;
	float b = _b - v2._b;

	vector2 auxVc(a, b);
	return auxVc;
}

vector3 vector3::operator-(const vector3& vc3) {
	float a = _a - vc3._a;
	float b = _b - vc3._b;
	float c = _c - vc3._c;

	vector3 auxVc(a, b, c);
	return auxVc;
}

vector4 vector4::operator-(const vector4& vc4) {
	float a = _a - vc4._a;
	float b = _b - vc4._b;
	float c = _c - vc4._c;
	float d = _d - vc4._d;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}


// Overloading operator *
vector2 vector2::operator*(const int x) {
	float a = _a*x;
	float b = _b*x;

	vector2 auxVc(a, b);
	return auxVc;
}

vector3 vector3::operator*(const int x) {
	float a = _a * x;
	float b = _b * x;
	float c = _c * x;

	vector3 auxVc(a, b, c);
	return auxVc;
}

vector4 vector4::operator*(const int x) {
	float a = _a * x;
	float b = _b * x;
	float c = _c * x;
	float d = _d * x;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}


// Dot product (intern product)
float  vector3::dotProductVc3 (const vector3& vc3) {
	float a = _a * vc3._a;
	float b = _b * vc3._b;
	float c = _c * vc3._c;

	return a + b + c;
}

// Cross product (external product)
vector3  vector3::crossProductVc3(const vector3& vc3) {
	float a = (_b * vc3._c) - (_c * vc3._b);
	float b = (_c * vc3._a) - (_a * vc3._c);
	float c = (_a * vc3._b) - (_b * vc3._a);

	vector3 auxVc(a, b, c);
	return auxVc;
}





