#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "mat4.h"
#include "vec4.h"

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913





/////////////////////////////////////////////////////////////////////// QUATERNION
struct qtrn {
	float _t, _x, _y, _z;

	qtrn();
	qtrn(float, float, float, float);

	const float _qThreshold = (float)1.0e-5;

	const qtrn qFromAngleAxis(float theta, vec4 axis);
	const void qToAngleAxis(const qtrn& q, float& theta, vec4& axis);
	const void qClean(qtrn& q);
	friend const float qQuadrance(const qtrn& q);
	friend const float qNorm(const qtrn& q);
	friend const qtrn qNormalize(const qtrn& q);
	friend const qtrn qConjugate(const qtrn& q);
	friend const qtrn qInverse(const qtrn& q);
	friend const qtrn qMultiply(const qtrn& q, const float s);
	friend const qtrn qMultiply(const qtrn& q0, const qtrn& q1);
	friend const void qGLMatrix(const qtrn& q, mat4 matrix);
	const qtrn qLerp(const qtrn& q0, const qtrn& q1, float k);
	const qtrn qSlerp(const qtrn& q0, const qtrn& q1, float k);
	
	const void qPrint(const std::string& s, const qtrn& q);
	const void qPrintAngleAxis(const std::string& s, const qtrn& q);

	friend const bool qEqual(const qtrn& q0, const qtrn& q1);
	friend const qtrn qAdd(const qtrn& q0, const qtrn& q1);

	const float getQThreshold();
};
