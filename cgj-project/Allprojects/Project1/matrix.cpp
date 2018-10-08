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

matrix2x2::matrix2x2(std::tuple<float, float> vc1, std::tuple<float, float> vc2) {
	_a = std::get<0>(vc1);
	_b = std::get<0>(vc2);
	_c = std::get<1>(vc1);
	_d = std::get<1>(vc2);
}

matrix2x2::matrix2x2(vector2& vc1, vector2& vc2) {
	_a = vc1._a;
	_b = vc2._a;
	_c = vc1._b;
	_d = vc2._b;
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
// -- Read --

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


// -- Overloading == --
// Matrix 2x2
bool matrix2x2::operator==(const matrix2x2& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d;
}

bool matrix3x3::operator==(const matrix3x3& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d && _e == m1._e && _f == m1._f && _g == m1._g && _h == m1._h && _i == m1._i;
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

// Matrix 2x2 by another matrix2x2
matrix2x2 matrix2x2::operator*(const matrix2x2& m1) {
	float a = (_a * m1._a) + (_b * m1._c);
	float b = (_a * m1._b) + (_b * m1._d);
	float c = (_c * m1._a) + (_d * m1._c);
	float d = (_c * m1._b) + (_d * m1._d);

	matrix2x2 m (a, b, c, d);

	return m;
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

