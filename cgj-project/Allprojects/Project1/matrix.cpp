#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include <algorithm>

#include "matrix.h"
#include "vector.h"

// -- Constructor --
// Matrix 2x2
matrix2x2::matrix2x2(float a, float b, float c, float d) {
	_a = a;
	_b = b;
	_c = c;
	_d = d;
}

matrix2x2::matrix2x2(vector2& vc1, vector2& vc2) {
	_a = vc1._a;
	_b = vc2._a;
	_c = vc1._b;
	_d = vc2._b;
}

matrix2x2::matrix2x2(float lst[4]) {
	_a = lst[0];
	_b = lst[1];
	_c = lst[2];
	_d = lst[3];
}

// Matrix 3x3
matrix3x3::matrix3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
	_a = a;
	_b = b;
	_c = c;
	_d = d;
	_e = e;
	_f = f;
	_g = g;
	_h = h;
	_i = i;
}

matrix3x3::matrix3x3(vector3& vc1, vector3& vc2, vector3& vc3) {
	_a = vc1._a;
	_b = vc2._a;
	_c = vc3._a;
	_d = vc1._b;
	_e = vc2._b;
	_f = vc3._b;
	_g = vc1._c;
	_h = vc2._c;
	_i = vc3._c;
}

matrix3x3::matrix3x3(float lst[9] ) {
	_a = lst[0];
	_b = lst[1];
	_c = lst[2];
	_d = lst[3];
	_e = lst[4];
	_f = lst[5];
	_g = lst[6];
	_h = lst[7];
	_i = lst[8];
}

//Matrix 4x4
matrix4x4::matrix4x4(float a, float b, float c, float d, float e, float f, float g, 
	float h, float i, float j, float k, float l, float m, float n, float o, float p) {
	_a = a;
	_b = b;
	_c = c;
	_d = d;
	_e = e;
	_f = f;
	_g = g;
	_h = h;
	_i = i;
	_j = j;
	_k = k;
	_l = l;
	_m = m;
	_n = n;
	_o = o;
	_p = p;
}

matrix4x4::matrix4x4(vector4& vc1, vector4& vc2, vector4& vc3, vector4& vc4) {
	_a = vc1._a;
	_b = vc2._a;
	_c = vc3._a;
	_d = vc4._a;
	_e = vc1._b;
	_f = vc2._b;
	_g = vc3._b;
	_h = vc4._b;
	_i = vc1._c;
	_j = vc2._c;
	_k = vc3._c;
	_l = vc4._c;
	_m = vc1._d;
	_n = vc2._d;
	_o = vc3._d;
	_p = vc4._d;
}

matrix4x4::matrix4x4(float lst[16]) {
	_a = lst[0];
	_b = lst[1];
	_c = lst[2];
	_d = lst[3];
	_e = lst[4];
	_f = lst[5];
	_g = lst[6];
	_h = lst[7];
	_i = lst[8];
	_j = lst[9];
	_k = lst[10];
	_l = lst[11];
	_m = lst[12];
	_n = lst[13];
	_o = lst[14];
	_p = lst[15];
}

// -- Read --
// Matrix 2x2
matrix2x2 matrix2x2::matrixRead() {
	std::string aAux, bAux, cAux, dAux;
	float a, b, c, d;

	std::cout << "A matrix 4x4 have the structure:\n";
	std::cout << "a b\n";
	std::cout << "c d\n";
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

	matrix2x2 m (a, b, c, d);
	std::cout << "A matrix 2x2 created:\n";
	m.matrixPrint();

	return m;
}

// Matrix 3x3
matrix3x3 matrix3x3::matrixRead() {
	std::string aAux, bAux, cAux, dAux, eAux, fAux, gAux, hAux, iAux;
	float a, b, c, d, e, f, g, h, i;

	std::cout << "A matrix 4x4 have the structure:\n";
	std::cout << "a b c\n";
	std::cout << "d e f\n";
	std::cout << "g h i\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);
	std::cout << "Please introduce your c:\n";
	getline(std::cin, cAux);
	std::cout << "Please introduce your d:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your e:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your f:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your g:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your h:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your i:\n";
	getline(std::cin, dAux);

	a = std::stof(aAux);
	b = std::stof(bAux);
	c = std::stof(cAux);
	d = std::stof(dAux);
	e = std::stof(eAux);
	f = std::stof(fAux);
	g = std::stof(gAux);
	h = std::stof(hAux);
	i = std::stof(iAux);

	matrix3x3 m (a, b, c, d, e, f, g, h, i);
	std::cout << "A matrix 3x3 created:\n";
	m.matrixPrint();

	return m;
}

// Matrix 4x4
matrix4x4 matrix4x4::matrixRead() {
	std::string aAux, bAux, cAux, dAux, eAux, fAux, gAux, hAux, iAux, jAux, kAux, lAux, mAux, nAux, oAux, pAux;
	float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	std::cout << "A matrix 4x4 have the structure:\n";
	std::cout << "a b c d\n";
	std::cout << "e f g h\n";
	std::cout << "i j k l\n";
	std::cout << "m n o p\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);
	std::cout << "Please introduce your c:\n";
	getline(std::cin, cAux);
	std::cout << "Please introduce your d:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your e:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your f:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your g:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your h:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your i:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your j:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your k:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your l:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your m:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your n:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your o:\n";
	getline(std::cin, dAux);

	a = std::stof(aAux);
	b = std::stof(bAux);
	c = std::stof(cAux);
	d = std::stof(dAux);
	e = std::stof(eAux);
	f = std::stof(fAux);
	g = std::stof(gAux);
	h = std::stof(hAux);
	i = std::stof(iAux);
	j = std::stof(jAux);
	k = std::stof(kAux);
	l = std::stof(lAux);
	m = std::stof(mAux);
	n = std::stof(nAux);
	o = std::stof(oAux);
	p = std::stof(pAux);

	matrix4x4 mR (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
	std::cout << "A matrix 4x4 created:\n";
	mR.matrixPrint();

	return mR;
}

// -- Print --
// Matrix 2x2
void matrix2x2::matrixPrint() {
	std::cout << "\n";
	std::cout << "[ " << _a << " " << _b << " ]" << "\n";
	std::cout << "[ " << _c << " " << _d << " ]" << "\n";
	std::cout << "\n";
}

void matrix3x3::matrixPrint() {
	std::cout << "\n";
	std::cout << "[ " << _a << " " << _b << " " << _c << " ]" << "\n";
	std::cout << "[ " << _d << " " << _e << " " << _f << " ]" << "\n";
	std::cout << "[ " << _g << " " << _h << " " << _i << " ]" << "\n";
	std::cout << "\n";
}

void matrix4x4::matrixPrint() {
	std::cout << "\n";
	std::cout << "[ " << _a << " " << _b << " " << _c << " " << _d << " ]" << "\n";
	std::cout << "[ " << _e << " " << _f << " " << _g << " " << _h << " ]" << "\n";
	std::cout << "[ " << _i << " " << _j << " " << _k << " " << _l << " ]" << "\n";
	std::cout << "[ " << _m << " " << _n << " " << _o << " " << _p << " ]" << "\n";
	std::cout << "\n";
}

// -- Overloading == --
// Matrix 2x2
bool matrix2x2::operator==(const matrix2x2& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d;
}

bool matrix3x3::operator==(const matrix3x3& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d && _e == m1._e && _f == m1._f && _g == m1._g && _h == m1._h && _i == m1._i;
}

bool matrix4x4::operator==(const matrix4x4& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d 
		&& _e == m1._e && _f == m1._f && _g == m1._g && _h == m1._h 
		&& _i == m1._i && _j == m1._j && _k == m1._k && _l == m1._l
		&& _m == m1._m && _n == m1._n && _o == m1._o && _p == m1._p;
}
// -- Overloading + --
// Matrix 2x2
matrix2x2 matrix2x2::operator+(const matrix2x2& m1) {
	float a = _a + m1._a;
	float b = _b + m1._b;
	float c = _c + m1._c;
	float d = _d + m1._d;

	matrix2x2 m (a, b, c, d);

	return m;
}

// Matrix 3x3
matrix3x3 matrix3x3::operator+(const matrix3x3& m1) {
	float a = _a + m1._a;
	float b = _b + m1._b;
	float c = _c + m1._c;
	float d = _d + m1._d;
	float e = _e + m1._e;
	float f = _f + m1._f;
	float g = _g + m1._g;
	float h = _h + m1._h;
	float i = _i + m1._i;

	matrix3x3 m (a, b, c, d, e, f, g, h, i);

	return m;
}

// Matrix 4x4
matrix4x4 matrix4x4::operator+(const matrix4x4& m1) {
	float a = _a + m1._a;
	float b = _b + m1._b;
	float c = _c + m1._c;
	float d = _d + m1._d;
	float e = _e + m1._e;
	float f = _f + m1._f;
	float g = _g + m1._g;
	float h = _h + m1._h;
	float i = _i + m1._i;
	float j = _j + m1._j;
	float k = _k + m1._k;
	float l = _l + m1._l;
	float m = _m + m1._m;
	float n = _n + m1._n;
	float o = _o + m1._o;
	float p = _p + m1._p;

	matrix4x4 mSoma (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mSoma;
}

// -- Overloading - --
// Matrix 2x2
matrix2x2 matrix2x2::operator-(const matrix2x2& m1) {
	float a = _a - m1._a;
	float b = _b - m1._b;
	float c = _c - m1._c;
	float d = _d - m1._d;

	matrix2x2 m(a, b, c, d);

	return m;
}

// Matrix 3x3
matrix3x3 matrix3x3::operator-(const matrix3x3& m1) {
	float a = _a - m1._a;
	float b = _b - m1._b;
	float c = _c - m1._c;
	float d = _d - m1._d;
	float e = _e - m1._e;
	float f = _f - m1._f;
	float g = _g - m1._g;
	float h = _h - m1._h;
	float i = _i - m1._i;

	matrix3x3 m(a, b, c, d, e, f, g, h, i);

	return m;
}

// Matrix 4x4
matrix4x4 matrix4x4::operator-(const matrix4x4& m1) {
	float a = _a - m1._a;
	float b = _b - m1._b;
	float c = _c - m1._c;
	float d = _d - m1._d;
	float e = _e - m1._e;
	float f = _f - m1._f;
	float g = _g - m1._g;
	float h = _h - m1._h;
	float i = _i - m1._i;
	float j = _j - m1._j;
	float k = _k - m1._k;
	float l = _l - m1._l;
	float m = _m - m1._m;
	float n = _n - m1._n;
	float o = _o - m1._o;
	float p = _p - m1._p;

	matrix4x4 mSub(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mSub;
}

// -- Overloading * --
// Matrix 2x2 by a scalar
matrix2x2 matrix2x2::operator*(const float x) {
	float a = _a * x;
	float b = _b * x;
	float c = _c * x;
	float d = _d * x;

	matrix2x2 m(a, b, c, d);

	return m;
}

// Matrix 3x3 by a scalar
matrix3x3 matrix3x3::operator*(const float x) {
	float a = _a * x;
	float b = _b * x;
	float c = _c * x;
	float d = _d * x;
	float e = _e * x;
	float f = _f * x;
	float g = _g * x;
	float h = _h * x;
	float i = _i * x;

	matrix3x3 m(a, b, c, d, e, f, g, h, i);

	return m;
}

// Matrix 4x4 by a scalar
matrix4x4 matrix4x4::operator*(const float x) {
	float a = _a * x;
	float b = _b * x;
	float c = _c * x;
	float d = _d * x;
	float e = _e * x;
	float f = _f * x;
	float g = _g * x;
	float h = _h * x;
	float i = _i * x;
	float j = _j * x;
	float k = _k * x;
	float l = _l * x;
	float m = _m * x;
	float n = _n * x;
	float o = _o * x;
	float p = _p * x;

	matrix4x4 mMut(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mMut;
}

// Matrix 2x2 by another matrix2x2
matrix2x2 matrix2x2::operator*(const matrix2x2& m1) {
	float a = (_a * m1._a) + (_b * m1._c);
	float b = (_a * m1._b) + (_b * m1._d);
	float c = (_c * m1._a) + (_d * m1._c);
	float d = (_c * m1._b) + (_d * m1._d);

	matrix2x2 m (a, b, c, d);

	return m;
}

// Matrix 3x3 by another matrix3x3
matrix3x3 matrix3x3::operator*(const matrix3x3& m1) {
	float a = (_a * m1._a) + (_b * m1._d) + (_c * m1._g);
	float b = (_a * m1._b) + (_b * m1._e) + (_c * m1._h);
	float c = (_a * m1._c) + (_b * m1._f) + (_c * m1._i);
	float d = (_d * m1._a) + (_e * m1._d) + (_f * m1._g);
	float e = (_d * m1._b) + (_e * m1._e) + (_f * m1._h);
	float f = (_d * m1._c) + (_e * m1._f) + (_f * m1._i);
	float g = (_g * m1._a) + (_h * m1._d) + (_i * m1._g);
	float h = (_g * m1._b) + (_h * m1._e) + (_i * m1._h);
	float i = (_g * m1._c) + (_h * m1._f) + (_i * m1._i);
	
	matrix3x3 m(a, b, c, d, e, f, g, h, i);

	return m;
}

// Matrix 4x4 by another matrix4x4
matrix4x4 matrix4x4::operator*(const matrix4x4& m1) {
	float a = (_a * m1._a) + (_b * m1._e) + (_c * m1._i) + (_d * m1._m);
	float b = (_a * m1._b) + (_b * m1._f) + (_c * m1._j) + (_d * m1._n);
	float c = (_a * m1._c) + (_b * m1._g) + (_c * m1._k) + (_d * m1._o);
	float d = (_a * m1._d) + (_b * m1._h) + (_c * m1._l) + (_d * m1._p);

	float e = (_e * m1._a) + (_f * m1._e) + (_g * m1._i) + (_h * m1._m);
	float f = (_e * m1._b) + (_f * m1._f) + (_g * m1._j) + (_h * m1._n);
	float g = (_e * m1._c) + (_f * m1._g) + (_g * m1._k) + (_h * m1._o);
	float h = (_e * m1._d) + (_f * m1._h) + (_g * m1._l) + (_h * m1._p);

	float i = (_i * m1._a) + (_j * m1._e) + (_k * m1._i) + (_l * m1._m);
	float j = (_i * m1._b) + (_j * m1._f) + (_k * m1._j) + (_l * m1._n);
	float k = (_i * m1._c) + (_j * m1._g) + (_k * m1._k) + (_l * m1._o);
	float l = (_i * m1._d) + (_j * m1._h) + (_k * m1._l) + (_l * m1._p);

	float m = (_m * m1._a) + (_n * m1._e) + (_o * m1._i) + (_p * m1._m);
	float n = (_m * m1._b) + (_n * m1._f) + (_o * m1._j) + (_p * m1._n);
	float o = (_m * m1._c) + (_n * m1._g) + (_o * m1._k) + (_p * m1._o);
	float p = (_m * m1._d) + (_n * m1._h) + (_o * m1._l) + (_p * m1._p);

	matrix4x4 mMut(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mMut;
}


// Matrix 2x2 by a vector 
vector2 matrix2x2::operator* (const vector2& vc) {
	float a = (_a * vc._a) + (_b * vc._b);
	float b = (_c * vc._a) + (_d * vc._b);

	vector2 res (a, b);
	return res;
}

// Matrix 3x3 by a vector 
vector3 matrix3x3::operator* (const vector3& vc) {
	float a = (_a * vc._a) + (_b * vc._b) + (_c * vc._c);
	float b = (_d * vc._a) + (_e * vc._b) + (_f * vc._c);
	float c = (_g * vc._a) + (_h * vc._b) + (_i * vc._c);

	vector3 res (a, b, c);
	return res;
}
// Matrix 4x4 by a vector
vector4 matrix4x4::operator* (const vector4& vc) {
	float a = (_a * vc._a) + (_b * vc._b) + (_c * vc._c) + (_d * vc._d);
	float b = (_e * vc._a) + (_f * vc._b) + (_g * vc._c) + (_h * vc._d);
	float c = (_i * vc._a) + (_j * vc._b) + (_k * vc._c) + (_l * vc._d);
	float d = (_m * vc._a) + (_n * vc._b) + (_o * vc._c) + (_p * vc._d);

	vector4 res(a, b, c, d);
	return res;
}

// -- Determinant --
// Matrix 2x2
float matrix2x2::detM2x2() {
	return (_a * _d) - (_b * _c);
}

// Matrix 3x3
float matrix3x3::detM3x3() {
	float x, y, z;

	matrix2x2 m1 (_e, _f, _h, _i);
	matrix2x2 m2 (_d, _f, _g, _i);
	matrix2x2 m3 (_d, _e, _g, _h);

	x = (_a * (m1.detM2x2()));
	y = (_b * (m2.detM2x2()));
	z = (_c * (m3.detM2x2()));

	return x - y + z;
}

// Matrix 4x4
float matrix4x4::detM4x4() {
	
	return ((_a * _f * _k * _p) - (_a * _f * _l * _o) - (_a * _g * _j * _p) + (_a * _g * _l * _n) + (_a * _h * _j * _o) - (_a * _h * _k * _n)
			- (_b * _e * _k * _p) + (_b * _e * _l * _o) + (_b * _g * _i * _p) - (_b * _g * _l * _m) - (_b * _h * _i * _o) + (_b * _h * _k * _m)
			+ (_c * _e * _j * _p) - (_c * _e * _l * _n) - (_c * _f * _i * _p) + (_c * _f * _l * _m) + (_c * _h * _i * _n) - (_c * _h * _j * _m)
			- (_d * _e * _j * _o) + (_d * _e * _k * _n) + (_d * _f * _i * _o) - (_d * _f * _k * _m) - (_d * _g * _i * _n) + (_d * _g * _j * _m));
}

// -- Transpose --
// Matrix 2x2
matrix2x2 matrix2x2::transposeM2x2() {

	matrix2x2 mAux(_a, _c, _b, _d);

	return mAux;
}

// Matrix 3x3
matrix3x3 matrix3x3::transposeM3x3() {

	matrix3x3 mAux(_a, _d, _g, _b, _e, _h, _c, _f, _i);

	return mAux;
}

// Matrix 4x4
matrix4x4 matrix4x4::transposeM4x4() {

	matrix4x4 mAux(_a, _e, _i, _m, _b, _f, _j, _n, _c, _g, _k, _o, _d, _h, _l, _p);

	return mAux;
}

// -- Inverse --
// Matrix 2x2
matrix2x2 matrix2x2::inverseM2x2() {
	float det = detM2x2();
	if (det == 0) {
		std::cout << "Matrix dosen't have inverse\n";
	}
	else {
		float k = 1 / det;
		matrix2x2 mAux (_d, -_b, -_c, _a);
		return mAux * k;
	}
}

// Matrix 3x3

matrix3x3 matrix3x3::inverseM3x3() {
	float det = detM3x3();
	if (det == 0) {
		std::cout << "Matrix dosen't have inverse\n";
	}
	else {
		float a, b, c, d, e, f, g, h, i; //det of minor matrices
		//minor matrices
		matrix2x2 m1 (_e, _f, _h, _i); 
		matrix2x2 m2 (_d, _f, _g, _i);
		matrix2x2 m3 (_d, _e, _g, _h);
		matrix2x2 m4 (_b, _c, _h, _i);
		matrix2x2 m5 (_a, _c, _g, _i);
		matrix2x2 m6 (_a, _b, _g, _h);
		matrix2x2 m7 (_b, _c, _e, _f);
		matrix2x2 m8 (_a, _c, _d, _f);
		matrix2x2 m9 (_a, _b, _d, _e);

		a = m1.detM2x2();
		b = m2.detM2x2();
		c = m3.detM2x2();
		d = m4.detM2x2();
		e = m5.detM2x2();
		f = m6.detM2x2();
		g = m7.detM2x2();
		h = m8.detM2x2();
		i = m9.detM2x2();

		matrix3x3 adj (a, -b, c, -d, e, -f, g, -h, i); // matrix adj
		
		float k = 1 / det;
		matrix3x3 inv = adj * k;

		return inv;
	}
}