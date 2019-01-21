#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include <algorithm>

struct vector2 {
	float _a, _b;

	vector2();
	vector2(float, float);
	vector2(std::tuple<float, float>);

	float* data();

	vector2 readVc2();
	void printVc2();

	vector2 operator= (const vector2&);
	bool operator== (const vector2&);
	vector2 operator+ (const vector2&);
	vector2 operator- (const vector2&);
	vector2 operator* (const float);
};