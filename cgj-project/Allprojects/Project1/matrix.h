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
	matrix2x2 (vector2& vc1, vector2& vc2);
	matrix2x2 (float lst[4]); // major column format

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

	matrix3x3 (float, float, float, float, float, float, float, float, float);
	matrix3x3 (vector3& vc1, vector3& vc2, vector3& vc3);
	matrix3x3 (float lst [9]); // major column format

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



struct matrix4x4 {
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
	float _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p;

	matrix4x4 (float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	matrix4x4 (vector4& vc1, vector4& vc2, vector4& vc3, vector4& vc4);
	matrix4x4 (float lst[16]); // major column format

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