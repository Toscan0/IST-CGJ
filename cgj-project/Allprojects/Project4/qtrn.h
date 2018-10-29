#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

typedef struct {
	float x, y, z, w;
} vec4;

const float vThreshold = (float)1.0e-5;

const vec4 vNormalize(const vec4& v)
{
	vec4 vn;
	float s = 1 / (v.w * sqrt(v.x*v.x + v.y*v.y + v.z*v.z));
	vn.x = v.x * s;
	vn.y = v.y * s;
	vn.z = v.z * s;
	vn.w = 1.0f;
	return vn;
}

const void vPrint(const std::string s, const vec4& v)
{
	std::cout << s << " = (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
}

const bool vEqual(const vec4& v0, const vec4& v1)
{
	return (fabs(v0.x - v1.x) < vThreshold && fabs(v0.y - v1.y) < vThreshold &&
		fabs(v0.z - v1.z) < vThreshold && fabs(v0.w - v1.w) < vThreshold);
}

/////////////////////////////////////////////////////////////////////// mat4

typedef float mat4[16]; // column major
const float mThreshold = (float)1.0e-5;

const vec4 mMultiply(mat4 m, vec4& v)
{
	vec4 r;
	r.x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w;
	r.y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w;
	r.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w;
	r.w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w;
	return r;
}

const void mClean(mat4 m)
{
	for (int i = 0; i < 16; i++) {
		if (fabs(m[i]) < mThreshold) m[i] = 0.0f;
	}
}

const void mPrint(const std::string s, const mat4 m)
{
	std::cout << s << " =" << std::endl;
	std::cout << std::fixed << std::setprecision(3) << "| ";
	std::cout.width(6); std::cout << m[0] << " ";
	std::cout.width(6); std::cout << m[4] << " ";
	std::cout.width(6); std::cout << m[8] << " ";
	std::cout.width(6); std::cout << m[12] << " |" << std::endl << "| ";
	std::cout.width(6); std::cout << m[1] << " ";
	std::cout.width(6); std::cout << m[5] << " ";
	std::cout.width(6); std::cout << m[9] << " ";
	std::cout.width(6); std::cout << m[13] << " |" << std::endl << "| ";
	std::cout.width(6); std::cout << m[2] << " ";
	std::cout.width(6); std::cout << m[6] << " ";
	std::cout.width(6); std::cout << m[10] << " ";
	std::cout.width(6); std::cout << m[14] << " |" << std::endl << "| ";
	std::cout.width(6); std::cout << m[3] << " ";
	std::cout.width(6); std::cout << m[7] << " ";
	std::cout.width(6); std::cout << m[11] << " ";
	std::cout.width(6); std::cout << m[15] << " |" << std::endl;
}

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
