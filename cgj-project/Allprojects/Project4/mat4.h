#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "vec4.h"
#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

/////////////////////////////////////////////////////////////////////// mat4

struct mat4 {
	float _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p;
	const float _mThreshold = (float)1.0e-5;

	mat4();
	mat4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);

	const float getMThreshold();
	float* data();

	friend const vec4 mMultiply(mat4 m, vec4& v);
	//friend const void mClean(mat4 m);
	friend const void mClean(float* m);
	friend const void mPrint(const std::string s, mat4 m);
};