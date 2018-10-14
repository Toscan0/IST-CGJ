#include "matrix2x2.h"

// -- Constructor --
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
	_b = lst[2];
	_c = lst[1];
	_d = lst[3];
}


// -- Data --
float* matrix2x2::data() {
	float* m = new float[4];

	m[0] = _a;
	m[1] = _b;
	m[2] = _c;
	m[3] = _d;

	return m;
}

// -- Read --
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

	matrix2x2 m(a, b, c, d);
	std::cout << "A matrix 2x2 created:\n";
	m.matrixPrint();

	return m;
}


// -- Print --
void matrix2x2::matrixPrint() {
	std::cout << "\n";
	std::cout << "[ " << _a << " " << _b << " ]" << "\n";
	std::cout << "[ " << _c << " " << _d << " ]" << "\n";
	std::cout << "\n";
}


// -- Overloading = -
matrix2x2 matrix2x2::operator= (const matrix2x2& m) {
	matrix2x2 mCopy(m._a, m._b, m._c, m._d);

	return m;
}


// -- Overloading == --
bool matrix2x2::operator==(const matrix2x2& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d;
}


// -- Overloading + --
matrix2x2 matrix2x2::operator+(const matrix2x2& m1) {
	float a = _a + m1._a;
	float b = _b + m1._b;
	float c = _c + m1._c;
	float d = _d + m1._d;

	matrix2x2 m(a, b, c, d);

	return m;
}


// -- Overloading - --
matrix2x2 matrix2x2::operator-(const matrix2x2& m1) {
	float a = _a - m1._a;
	float b = _b - m1._b;
	float c = _c - m1._c;
	float d = _d - m1._d;

	matrix2x2 m(a, b, c, d);

	return m;
}


// -- Overloading * --
// Scalar
matrix2x2 matrix2x2::operator*(const float x) {
	float a = _a * x;
	float b = _b * x;
	float c = _c * x;
	float d = _d * x;

	matrix2x2 m(a, b, c, d);

	return m;
}

// Another matrix2x2
matrix2x2 matrix2x2::operator*(const matrix2x2& m1) {
	float a = (_a * m1._a) + (_b * m1._c);
	float b = (_a * m1._b) + (_b * m1._d);
	float c = (_c * m1._a) + (_d * m1._c);
	float d = (_c * m1._b) + (_d * m1._d);

	matrix2x2 m(a, b, c, d);

	return m;
}

// By a vector
vector2 matrix2x2::operator* (const vector2& vc) {
	float a = (_a * vc._a) + (_b * vc._b);
	float b = (_c * vc._a) + (_d * vc._b);

	vector2 res(a, b);
	return res;
}


// -- Determinant --
float matrix2x2::detM2x2() {
	return (_a * _d) - (_b * _c);
}


// -- Transpose --
matrix2x2 matrix2x2::transposeM2x2() {

	matrix2x2 mAux(_a, _c, _b, _d);

	return mAux;
}


// -- Inverse --
matrix2x2 matrix2x2::inverseM2x2() {
	float det = detM2x2();
	if (det == 0) {
		throw "Matrix dosen't have inverse\n";
	}
	else {
		float k = 1 / det;
		matrix2x2 mAux(_d, -_b, -_c, _a);
		return mAux * k;
	}
}