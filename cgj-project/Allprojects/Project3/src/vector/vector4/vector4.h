#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <algorithm>

struct vector4 {
	float _a, _b, _c, _d;

	vector4(float, float, float, float);
	vector4(std::tuple<float, float, float, float>);

	float* data();

	vector4 readVc4();
	void printVc4();

	vector4 operator= (const vector4&);
	bool operator== (const vector4&);
	vector4 operator+ (const vector4&);
	vector4 operator- (const vector4&);
	vector4 operator* (const float);
};