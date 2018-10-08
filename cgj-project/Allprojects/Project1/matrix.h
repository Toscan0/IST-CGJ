#pragma once
#include <tuple>

#include "vector.h"

struct matrix2x2{
	/*
	[_a _b
	 _c _d]
	
	[v1 v2] = [v1._a v2._a
			   v1._b v2._b]
	*/
	float _a, _b, _c, _d;

	matrix2x2 (float, float, float, float);
	matrix2x2 (std::tuple<float, float>, std::tuple<float, float>);
	matrix2x2(vector2& vc1, vector2& vc2);

	matrix2x2 matrixRead();
	void matrixPrint();

	matrix2x2 operator= (const matrix2x2&);
	bool operator== (const matrix2x2&);
	matrix2x2 operator+ (const matrix2x2&);
	matrix2x2 operator- (const matrix2x2&);
	matrix2x2 operator* (const matrix2x2&);
	matrix2x2 operator* (const float);
	matrix2x2 operator* (const vector2& vc);

	float detM2x2();
	matrix2x2 inverseM2x2();
	matrix2x2 transposeM2x2();
};


struct matrix3x3 {
	/*
	[_a _b _c
	 _d _e _f
	 _g _h _i]

	[v1 v2 v3] = [v1._a v2._a v3._a
			      v1._b v2._b v3._b
				  v1._c v2._c v3._c]
	*/
	float _a, _b, _c, _d, _e, _f, _g, _h, _i;

	matrix3x3(float, float, float, float, float, float, float, float, float);
	matrix3x3(vector3& vc1, vector3& vc2, vector3& vc3);

	matrix3x3 matrixRead();
	void matrixPrint();

	matrix3x3 operator= (const matrix3x3&);
	bool operator== (const matrix3x3&);
	matrix3x3 operator+ (const matrix3x3&);
	matrix3x3 operator- (const matrix3x3&);
	matrix3x3 operator* (const matrix3x3&);
	matrix3x3 operator* (const float);
	matrix2x2 operator* (const vector3& vc);

	float detM3x3();
	matrix3x3 transposeM3x3();
	matrix3x3 inverseM3x3();
};