#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include "vector.h"
/*
std::string i;
	std::cout << "write something\n";
	getline(std::cin, i);
	std::cout << "sss" << i;
	*/
// -- Constructor --
// Vector2
vector2::vector2(float a, float b) {
	_a = a;
	_b = b;
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


/*
vector2 vector2::operator=(const vector2& v2) {
	return v2;
}*/


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