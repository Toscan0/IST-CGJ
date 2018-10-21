#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <algorithm>

#include "../../vector/vector4/vector4.h"



/*
	[_a _b _c _d
	 _e _f _g _h
	 _i _j _k _l
	 _m _n _o _p]

	[v1 v2 v3 C] = [v1._a v2._a v3._a v4._a
					v1._b v2._b v3._b v4._b
					v1._c v2._c v3._c v4._c
					v1._d v2._d v3._d v4._d]
	*/

struct matrix4x4 {
	float _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p;

	matrix4x4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	matrix4x4(vector4& vc1, vector4& vc2, vector4& vc3, vector4& vc4);
	matrix4x4(float lst[16]); // major column format

	float* data();

	matrix4x4 matrixRead();
	void matrixPrint();

	matrix4x4 operator= (const matrix4x4&);
	bool operator== (const matrix4x4&);
	matrix4x4 operator+ (const matrix4x4&);
	matrix4x4 operator- (const matrix4x4&);
	matrix4x4 operator* (const matrix4x4&);
	matrix4x4 operator* (const float);
	vector4 operator* (const vector4& vc);

	float detM4x4();
	matrix4x4 transposeM4x4();
};
