#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <algorithm>

struct vector3 {
	float _a, _b, _c;

	vector3(float, float, float);
	vector3(std::tuple<float, float, float>);

	float* data();

	vector3 readVc3();
	void printVc3();

	float norma();
	vector3 normalizado();

	vector3 operator= (const vector3&);
	bool operator== (const vector3&);
	vector3 operator+ (const vector3&);
	vector3 operator- (const vector3&);
	vector3 operator* (const float);

	friend float dot(const vector3&, const vector3&);
	friend vector3 cross(const vector3&, const vector3&);
};