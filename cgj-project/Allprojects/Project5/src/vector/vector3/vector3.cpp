#include "vector3.h"

// -- Constructor --
vector3::vector3() {

}

// -- Constructor --
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


// -- Data --
float* vector3::data() {
	float* v = new float[3];

	v[0] = _a;
	v[1] = _b;
	v[2] = _c;

	return v;
}


// -- Read --
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

	vector3 v(a, b, c);
	std::cout << "The vector " << "(" << a << ", " << b << ", " << c << ") " << "was created\n";

	return v;
}


// -- Print --
void vector3::printVc3() {
	std::cout << "(" << _a << "," << _b << "," << _c << ")" << "\n";
}


// -- Norma --
float vector3::norma() {
	float s = pow(_a, 2) + pow(_b, 2) + pow(_c, 2);
	float n = sqrt(s);
	return n;
}

// -- Normalizado --
const vector3 vector3::normalizado() {
	float n = norma();
	float a = _a / n;
	float b = _b / n;
	float c = _c / n;

	vector3 v(a, b, c);
	return v;
}


// Overloading operator =
const vector3 vector3::operator=(const vector3& v) {
	_a = v._a;
	_b = v._b;
	_c = v._c;
	return *this;
}


// Overloading operator ==
const bool vector3::operator==(const vector3& vc3) {
	float a = abs(_a - vc3._a);
	float b = abs(_b - vc3._b);
	float c = abs(_c - vc3._c);
	float e = (1e-5);
	if ((a < e) && (b < e) && (c < e)) {
		return true;
	}
	return false;
	//return _a == vc3._a && _b == vc3._b && _c == vc3._c;
}


// Overloading operator +
const vector3 operator+(const vector3& v1, const vector3& v2) {
	float a = v1._a + v2._a;
	float b = v1._b + v2._b;
	float c = v1._c + v2._c;

	vector3 auxVc(a, b, c);
	return auxVc;
}


// Overloading operator -
const vector3 operator-(const vector3& v1, const vector3& v2) {
	float a = v1._a - v2._a;
	float b = v1._b - v2._b;
	float c = v1._c - v2._c;

	vector3 auxVc(a, b, c);
	return auxVc;
}


// Overloading operator *
const vector3 operator*(const vector3& v, const float x) {
	float a = v._a * x;
	float b = v._b * x;
	float c = v._c * x;

	vector3 auxVc(a, b, c);
	return auxVc;
}

const vector3 operator*(const float x,const vector3& v) {
	return v * x;
}

// -- Dot Product (Intern Product) --
float dot(const vector3& v1, const vector3& v2) {
	float a = v1._a * v2._a;
	float b = v1._b * v2._b;
	float c = v1._c * v2._c;

	return a + b + c;
}


// -- Cross product (external product) --
vector3 cross(const vector3& v1, const vector3& v2) {
	float a = (v1._b * v2._c) - (v1._c * v2._b);
	float b = (v1._c * v2._a) - (v1._a * v2._c);
	float c = (v1._a * v2._b) - (v1._b * v2._a);

	vector3 auxVc(a, b, c);
	return auxVc;
}

// learp
const vector3 learp(const vector3& p0, const vector3& p1, const float k) {
	if (0 <= k && k <= 1) {
		// (1-a)p0 + ap1
		float aux = 1 - k;
		vector3 v1 = aux * p0;
		vector3 v2 = k * p1;
		vector3 v3 = v1 + v2;
		return v3;
	}
	else {
		std::cout << "Invalide k, k should be between 0 and 1.\n You use: " << k << "\n";
	}
}