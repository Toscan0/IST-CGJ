#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <algorithm>

#include "../matrix2x2/matrix2x2.h"
#include "../../vector/vector3/vector3.h"

/*
	[_a _b _c
	 _d _e _f
	 _g _h _i]

	[v1 v2 v3] = [v1._a v2._a v3._a
				  v1._b v2._b v3._b
				  v1._c v2._c v3._c]
	*/

struct matrix3x3 {
	float _a, _b, _c, _d, _e, _f, _g, _h, _i;

	matrix3x3(float, float, float, float, float, float, float, float, float);
	matrix3x3(vector3& vc1, vector3& vc2, vector3& vc3);
	matrix3x3(float lst[9]); // major column format

	float* data();

	matrix3x3 matrixRead();
	void matrixPrint();


	matrix3x3 operator= (const matrix3x3&);
	bool operator== (const matrix3x3&);
	matrix3x3 operator+ (const matrix3x3&);
	matrix3x3 operator- (const matrix3x3&);
	matrix3x3 operator* (const matrix3x3&);
	friend matrix3x3 operator*(const matrix3x3, const float);
	friend matrix3x3 operator* (const float, const matrix3x3);
	//matrix3x3 operator* (const float);
	vector3 operator* (const vector3& vc);

	float detM3x3();
	matrix3x3 transposeM3x3();
	matrix3x3 inverseM3x3();
};