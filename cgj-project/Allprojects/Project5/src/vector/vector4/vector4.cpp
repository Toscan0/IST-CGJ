#include "vector4.h"

// -- Constructor --
vector4::vector4() {}

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


// -- Data --
float* vector4::data() {
	float* v = new float[4];

	v[0] = _a;
	v[1] = _b;
	v[2] = _c;
	v[3] = _d;

	return v;
}

const float vector4::getVTreshhold() {
	return _vThreshold;
}

// -- Read --
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
void vector4::printVc4() {
	std::cout << "(" << _a << "," << _b << "," << _c << "," << _d << ")" << "\n";
}

const void vPrint(const std::string s, const vector4& v){
	std::cout << s << " = (" << v._a << ", " << v._b << ", " << v._c << ", " << v._d << ")" << std::endl;
}

// Normalize
const vector4 vNormalize(const vector4& v){
	vector4 vn;
	float s = 1 / (v._d * sqrt(v._a*v._a + v._b*v._b + v._c*v._c));
	vn._a = v._a * s;
	vn._b = v._b * s;
	vn._c = v._c * s;
	vn._d = 1.0f;
	return vn;
}

// Overloading operator =
vector4 vector4::operator=(const vector4& v) {
	vector4 vCopy(v._a, v._b, v._c, v._d);

	return vCopy;
}


// Overloading operator ==
bool vector4::operator==(const vector4& vc4) {
	return _a == vc4._a && _b == vc4._b && _c == vc4._c && _d == vc4._d;
}

const bool vEqual(const vector4& v0, const vector4& v1){
	vector4 vecAux;
	const float vThreshold = vecAux.getVTreshhold();
	return (fabs(v0._a - v1._a) < vThreshold && fabs(v0._b - v1._b) < vThreshold &&
		fabs(v0._c - v1._c) < vThreshold && fabs(v0._d - v1._d) < vThreshold);
}

// Overloading operator +
const vector4 operator+(const vector4& vc1, const vector4& vc2) {
	float a = vc1._a + vc2._a;
	float b = vc1._b + vc2._b;
	float c = vc1._c + vc2._c;
	float d = vc1._d + vc2._d;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}


// Overloading operator -
const vector4 operator-(const vector4& vc1, const vector4& vc2) {
	float a = vc1._a - vc2._a;
	float b = vc1._b - vc2._b;
	float c = vc1._c - vc2._c;
	float d = vc1._d - vc2._d;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}


// Overloading operator *
const vector4 operator* (const vector4& vc, const float k){
	float a = vc._a * k;
	float b = vc._b * k;
	float c = vc._c * k;
	float d = vc._d * k;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}

const vector4 operator* (const float k, const vector4& vc) {
	return vc * k;
}

// learp
/*const vector4 learp(const vector4& p0, const vector4& p1, const float k) {
	if (0 <= k && k <= 1) {
		// (1-a)p0 + ap1
		return vector4(((1 - k) * p0) + ((k)* p1));
	} 
	else {
		std::cout << "Invalide k, k should be between 0 and 1.\n You use: " << k << "\n";
	}
}*/