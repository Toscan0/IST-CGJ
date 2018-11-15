#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <algorithm>

struct vector4 {
	float _a, _b, _c, _d;
	const float _vThreshold = (float)1.0e-5;

	vector4();
	vector4(float, float, float, float);
	vector4(std::tuple<float, float, float, float>);

	float* data();
	const float getVTreshhold();

	vector4 readVc4();
	void printVc4();

	friend const vector4 vNormalize(const vector4&);
	friend const void vPrint(const std::string s, const vector4& v);
	friend const bool vEqual(const vector4& v0, const vector4& v1);

	vector4 operator= (const vector4&);
	bool operator== (const vector4&);
	//vector4 operator+ (const vector4&);
	//vector4 operator- (const vector4&);
	//vector4 operator* (const float);

	friend const vector4 operator+ (const vector4&, const vector4&);
	friend const vector4 operator- (const vector4&, const vector4&);
	friend const vector4 operator* (const vector4&, const float);
	friend const vector4 operator* (const float, const vector4&);

	friend const vector4 learp(const vector4 p0, const vector4 p1,const float k);
};