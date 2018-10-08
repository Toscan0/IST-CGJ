#pragma once
#include <tuple>

struct vector2 {
	float _a, _b;
	//std::tuple<float, float> _vc;

	vector2(float, float);
	vector2(std::tuple<float, float>);
	
	vector2 readVc2 ();
	void printVc2 ();
	
	vector2 operator= (const vector2&);
	bool operator== (const vector2&);
	vector2 operator+ (const vector2&);
	vector2 operator- (const vector2&);
	vector2 operator* (const int);
};

struct vector3 {
	float _a, _b, _c;

	vector3(float, float, float);
	vector3(std::tuple<float, float, float>);

	void readVc3();
	void printVc3();

	float dotProductVc3 (const vector3&);
	vector3 crossProductVc3(const vector3&);

	vector3 operator= (const vector3&);
	bool operator== (const vector3&);
	vector3 operator+ (const vector3&);
	vector3 operator- (const vector3&);
	vector3 operator* (const int);
};

struct vector4 {
	float _a, _b, _c, _d;

	vector4(float, float, float, float);
	vector4(std::tuple<float, float, float, float>);

	void readVc4();
	void printVc4();

	vector4 operator= (const vector4&);
	bool operator== (const vector4&);
	vector4 operator+ (const vector4&);
	vector4 operator- (const vector4&);
	vector4 operator* (const int);
};