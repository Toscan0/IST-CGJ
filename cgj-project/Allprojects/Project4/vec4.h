#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

/////////////////////////////////////////////////////////////////////// VECTOR
struct vec4{
	float _x, _y, _z, _w;
	const float _vThreshold = (float)1.0e-5;

	vec4();
	vec4(float, float, float, float);

	const float getVTreshhold();

	friend const vec4 vNormalize(const vec4& v);
	friend const void vPrint(const std::string s, const vec4& v);
	friend const bool vEqual(const vec4& v0, const vec4& v1);
};