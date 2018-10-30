#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <algorithm>

struct vector3 {
	float _a, _b, _c;
	vector3();
	vector3(float, float, float);
	vector3(std::tuple<float, float, float>);

	float* data();

	vector3 readVc3();
	void printVc3();

	float norma();
	const vector3 normalizado();

	const vector3 operator= (const vector3&);
	const bool operator== (const vector3&);
	//const vector3 operator+ (const vector3&);
	//const vector3 operator- (const vector3&);
	const vector3 operator* (const float);

	friend float dot(const vector3&, const vector3&);
	friend  vector3 cross(const vector3&, const vector3&);

	friend const vector3 operator- (const vector3&, const vector3&);
	friend const vector3 operator+ (const vector3&, const vector3&);
};