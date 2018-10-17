#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <algorithm>

#include "../../vector/vector2/vector2.h"
/*
	[_a _b
	 _c _d]

	[v1 v2] = [v1._a v2._a
			   v1._b v2._b]
	*/

struct matrix2x2 {
	float _a, _b, _c, _d;

	matrix2x2(float, float, float, float);
	matrix2x2(vector2& vc1, vector2& vc2);
	matrix2x2(float lst[4]); // major column format

	float* data();

	matrix2x2 matrixRead();
	void matrixPrint();

	matrix2x2 operator= (const matrix2x2&);
	bool operator== (const matrix2x2&);
	matrix2x2 operator+ (const matrix2x2&);
	matrix2x2 operator- (const matrix2x2&);
	matrix2x2 operator* (const matrix2x2&);
	matrix2x2 operator* (const float);
	vector2 operator* (const vector2& vc);

	float detM2x2();
	matrix2x2 inverseM2x2();
	matrix2x2 transposeM2x2();
};
