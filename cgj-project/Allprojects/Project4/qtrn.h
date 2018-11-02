#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#include "src/matrix/matrix4x4/matrix4x4.h"
#include "src/vector/vector4/vector4.h"

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

struct qtrn {
	float _t, _x, _y, _z;

	qtrn();
	qtrn(float, float, float, float);

	const float _qThreshold = (float)1.0e-5;

	const float getQThreshold();

	const qtrn qFromAngleAxis(float theta, vector4& axis);
	const void qToAngleAxis(const qtrn& q, float& theta, vector4& axis);
	const void qClean(qtrn& q);
	friend const float qQuadrance(const qtrn& q);
	friend const float qNorm(const qtrn& q);
	friend const qtrn qNormalize(const qtrn& q);
	friend const qtrn qConjugate(const qtrn& q);
	friend const qtrn qInverse(const qtrn& q);
	//friend const qtrn qMultiply(const qtrn& q, const float s);
	//friend const qtrn qMultiply(const qtrn& q0, const qtrn& q1);
	friend matrix4x4 qGLMatrix(const qtrn& q, matrix4x4 matrix); //changed void -> matrix4x4
	const qtrn qLerp(const qtrn& q0, const qtrn& q1, float k);
	const qtrn qSlerp(const qtrn& q0, const qtrn& q1, float k);
	
	friend const void qPrint(const std::string& s, const qtrn& q);
	const void qPrintAngleAxis(const std::string& s, const qtrn& q);

	//friend const bool qEqual(const qtrn& q0, const qtrn& q1);
	friend const qtrn qAdd(const qtrn& q0, const qtrn& q1);

	const qtrn operator=(const qtrn& v);

	friend const qtrn operator- (const qtrn&, const qtrn&);
	friend const qtrn operator+ (const qtrn&, const qtrn&);
	friend const qtrn operator*(const qtrn& q, const float s);
	friend const qtrn operator*(const qtrn& q0, const qtrn& q1);
	friend const bool operator==(const qtrn& q0, const qtrn& q1);
	friend const std::ostream& operator<<(std::ostream& stream, const qtrn& q);
};