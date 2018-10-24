#include "matrix3x3.h"


// -- Constructor --
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

matrix3x3::matrix3x3(float lst[9]) {
	_a = lst[0];
	_b = lst[3];
	_c = lst[6];
	_d = lst[1];
	_e = lst[4];
	_f = lst[7];
	_g = lst[2];
	_h = lst[5];
	_i = lst[8];
}


// -- Data --
float* matrix3x3::data() {
	float* m = new float[9];

	m[0] = _a;
	m[1] = _b;
	m[2] = _c;
	m[3] = _d;
	m[4] = _e;
	m[5] = _f;
	m[6] = _g;
	m[7] = _h;
	m[8] = _i;

	return m;
}


// -- Read --
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

	matrix3x3 m(a, b, c, d, e, f, g, h, i);
	std::cout << "A matrix 3x3 created:\n";
	m.matrixPrint();

	return m;
}


// -- Print --
void matrix3x3::matrixPrint() {
	std::cout << "\n";
	std::cout << "[ " << _a << " " << _b << " " << _c << " ]" << "\n";
	std::cout << "[ " << _d << " " << _e << " " << _f << " ]" << "\n";
	std::cout << "[ " << _g << " " << _h << " " << _i << " ]" << "\n";
	std::cout << "\n";
}

// -- Overloading = -
matrix3x3 matrix3x3::operator= (const matrix3x3& m) {
	_a = m._a;
	_b = m._b;
	_c = m._c;
	_d = m._d;
	_e = m._e;
	_f = m._f;
	_g = m._g;
	_h = m._h;
	_i = m._i;

	return *this;
}


// -- Overloading == --
bool matrix3x3::operator==(const matrix3x3& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d && _e == m1._e && _f == m1._f && _g == m1._g && _h == m1._h && _i == m1._i;
}


// -- Overloading + --
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

	matrix3x3 m(a, b, c, d, e, f, g, h, i);

	return m;
}


// -- Overloading - --
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
// Scalar
matrix3x3 operator*(const matrix3x3 m, const float x) {
	float a = m._a * x;
	float b = m._b * x;
	float c = m._c * x;
	float d = m._d * x;
	float e = m._e * x;
	float f = m._f * x;
	float g = m._g * x;
	float h = m._h * x;
	float i = m._i * x;

	matrix3x3 m1(a, b, c, d, e, f, g, h, i);

	return m1;
}

matrix3x3 operator* (const float x, const matrix3x3 m) {
	return m * x;
}

// Another matrix3x3
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

// By a vector
vector3 matrix3x3::operator* (const vector3& vc) {
	float a = (_a * vc._a) + (_b * vc._b) + (_c * vc._c);
	float b = (_d * vc._a) + (_e * vc._b) + (_f * vc._c);
	float c = (_g * vc._a) + (_h * vc._b) + (_i * vc._c);

	vector3 res(a, b, c);
	return res;
}


// -- Determinant --
float matrix3x3::detM3x3() {
	float x, y, z;

	matrix2x2 m1(_e, _f, _h, _i);
	matrix2x2 m2(_d, _f, _g, _i);
	matrix2x2 m3(_d, _e, _g, _h);

	x = (_a * (m1.detM2x2()));
	y = (_b * (m2.detM2x2()));
	z = (_c * (m3.detM2x2()));

	return x - y + z;
}


// -- Transpose --
matrix3x3 matrix3x3::transposeM3x3() {

	matrix3x3 mAux(_a, _d, _g, _b, _e, _h, _c, _f, _i);

	return mAux;
}


// -- Inverse --
matrix3x3 matrix3x3::inverseM3x3() {
	float det = detM3x3();
	if (det == 0) {
		throw "Matrix dosen't have inverse\n";
	}
	else {
		matrix3x3 mT = transposeM3x3();
		float a, b, c, d, e, f, g, h, i; //det of minor matrices
		//minor matrices
		matrix2x2 m1(mT._e, mT._f, mT._h, mT._i);
		matrix2x2 m2(mT._d, mT._f, mT._g, mT._i);
		matrix2x2 m3(mT._d, mT._e, mT._g, mT._h);
		matrix2x2 m4(mT._b, mT._c, mT._h, mT._i);
		matrix2x2 m5(mT._a, mT._c, mT._g, mT._i);
		matrix2x2 m6(mT._a, mT._b, mT._g, mT._h);
		matrix2x2 m7(mT._b, mT._c, mT._e, mT._f);
		matrix2x2 m8(mT._a, mT._c, mT._d, mT._f);
		matrix2x2 m9(mT._a, mT._b, mT._d, mT._e);

		a = m1.detM2x2();
		b = m2.detM2x2();
		c = m3.detM2x2();
		d = m4.detM2x2();
		e = m5.detM2x2();
		f = m6.detM2x2();
		g = m7.detM2x2();
		h = m8.detM2x2();
		i = m9.detM2x2();

		matrix3x3 adj(a, -b, c, -d, e, -f, g, -h, i); // matrix adj

		float k = 1 / det;
		matrix3x3 inv = adj * k;

		return inv;
	}
}