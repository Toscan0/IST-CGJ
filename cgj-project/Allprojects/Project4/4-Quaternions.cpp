///////////////////////////////////////////////////////////////////////
//
// Using quaternions to rotate in 3D.
//
// Assignment: 1. Create a class for Quaternions.
//             2. Create a scene with a camera rotating around an 
//                object at the origin and pointing towards it. 
//                Do NOT use "gluLookAt" to create the ViewMatrix, 
//                use rotation matrices!
//             3. Gimbal lock mode ON: use Translation + Rotation 
//                matrices (e.g. Euler angles, Rodrigues’ formula).
//             4. Gimbal lock mode OFF: use Quaternions to produce a 
//                transformation matrix and avoid gimbal lock.
//             5. Switch between modes by pressing the 'g' key.
//
// (c) 2013-18 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#include "qtrn.h"

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913


/////////////////////////////////////////////////////////////////////// VECTOR



/////////////////////////////////////////////////////////////////////// QUATERNION
qtrn::qtrn() {}

qtrn::qtrn(float t, float x, float y, float z) {
	_t = t;
	_x = x;
	_y = y;
	_z = z;
}
//get
const float qtrn::getQThreshold() {
	return _qThreshold;
}

const qtrn qtrn::qFromAngleAxis(float theta, vec4 axis)
{
	vec4 axisn = vNormalize(axis);

	qtrn q;
	float a = theta * (float)DEGREES_TO_RADIANS;
	q._t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	q._x = axisn.x * s;
	q._y = axisn.y * s;
	q._z = axisn.z * s;

	qClean(q);
	return qNormalize(q);
}

const void qtrn::qToAngleAxis(const qtrn& q, float& theta, vec4& axis)
{
	qtrn qn = qNormalize(q);
	theta = 2.0f * acos(qn._t) * (float)RADIANS_TO_DEGREES;
	float s = sqrt(1.0f - qn._t*qn._t);
	if (s < _qThreshold) {
		axis.x = 1.0f;
		axis.y = 0.0f;
		axis.z = 0.0f;
		axis.w = 1.0f;
	}
	else {
		axis.x = qn._x / s;
		axis.y = qn._y / s;
		axis.z = qn._z / s;
		axis.w = 1.0f;
	}
}

const void qtrn::qClean(qtrn& q)
{
	if (fabs(q._t) < _qThreshold) q._t = 0.0f;
	if (fabs(q._x) < _qThreshold) q._x = 0.0f;
	if (fabs(q._y) < _qThreshold) q._y = 0.0f;
	if (fabs(q._z) < _qThreshold) q._z = 0.0f;
}

const float qQuadrance(const qtrn& q)
{
	return q._t*q._t + q._x*q._x + q._y*q._y + q._z*q._z;
}

const float qNorm(const qtrn& q)
{
	return sqrt(qQuadrance(q));
}

const qtrn qNormalize(const qtrn& q)
{
	float s = 1 / qNorm(q);
	return qMultiply(q, s);
}

const qtrn qConjugate(const qtrn& q)
{
	qtrn qconj = { q._t, -q._x, -q._y, -q._z };
	return qconj;
}

const qtrn qInverse(const qtrn& q)
{
	return qMultiply(qConjugate(q), 1.0f / qQuadrance(q));
}

const qtrn qAdd(const qtrn& q0, const qtrn& q1)
{
	qtrn q;
	q._t = q0._t + q1._t;
	q._x = q0._x + q1._x;
	q._y = q0._y + q1._y;
	q._z = q0._z + q1._z;
	return q;
}

const qtrn qMultiply(const qtrn& q, const float s)
{
	qtrn sq;
	sq._t = s * q._t;
	sq._x = s * q._x;
	sq._y = s * q._y;
	sq._z = s * q._z;
	return sq;
}

const qtrn qMultiply(const qtrn& q0, const qtrn& q1)
{
	qtrn q;
	q._t = q0._t * q1._t - q0._x * q1._x - q0._y * q1._y - q0._z * q1._z;
	q._x = q0._t * q1._x + q0._x * q1._t + q0._y * q1._z - q0._z * q1._y;
	q._y = q0._t * q1._y + q0._y * q1._t + q0._z * q1._x - q0._x * q1._z;
	q._z = q0._t * q1._z + q0._z * q1._t + q0._x * q1._y - q0._y * q1._x;
	return q;
}

const void qGLMatrix(const qtrn& q, mat4 matrix)
{
	qtrn qn = qNormalize(q);

	float xx = qn._x * qn._x;
	float xy = qn._x * qn._y;
	float xz = qn._x * qn._z;
	float xt = qn._x * qn._t;
	float yy = qn._y * qn._y;
	float yz = qn._y * qn._z;
	float yt = qn._y * qn._t;
	float zz = qn._z * qn._z;
	float zt = qn._z * qn._t;

	matrix[0] = 1.0f - 2.0f * (yy + zz);
	matrix[1] = 2.0f * (xy + zt);
	matrix[2] = 2.0f * (xz - yt);
	matrix[3] = 0.0f;

	matrix[4] = 2.0f * (xy - zt);
	matrix[5] = 1.0f - 2.0f * (xx + zz);
	matrix[6] = 2.0f * (yz + xt);
	matrix[7] = 0.0f;

	matrix[8] = 2.0f * (xz + yt);
	matrix[9] = 2.0f * (yz - xt);
	matrix[10] = 1.0f - 2.0f * (xx + yy);
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	mClean(matrix);
}

const qtrn qtrn::qLerp(const qtrn& q0, const qtrn& q1, float k)
{
	float cos_angle = q0._x*q1._x + q0._y*q1._y + q0._z*q1._z + q0._t*q1._t;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	qtrn qi = qAdd(qMultiply(q0, k0), qMultiply(q1, k1));
	return qNormalize(qi);
}

const qtrn qtrn::qSlerp(const qtrn& q0, const qtrn& q1, float k)
{
	float angle = acos(q0._x*q1._x + q0._y*q1._y + q0._z*q1._z + q0._t*q1._t);
	float k0 = sin((1 - k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	qtrn qi = qAdd(qMultiply(q0, k0), qMultiply(q1, k1));
	return qNormalize(qi);
}

const bool qEqual(const qtrn& q0, const qtrn& q1)
{
	qtrn q;
	float qThreshold = q.getQThreshold();
	return (fabs(q0._t - q1._t) < qThreshold && fabs(q0._x - q1._x) < qThreshold &&
		fabs(q0._y - q1._y) < qThreshold && fabs(q0._z - q1._z) < qThreshold);
}

const void qtrn::qPrint(const std::string& s, const qtrn& q)
{
	std::cout << s << " = (" << q._t << ", " << q._x << ", " << q._y << ", " << q._z << ")" << std::endl;
}

const void qtrn::qPrintAngleAxis(const std::string& s, const qtrn& q)
{
	std::cout << s << " = [" << std::endl;

	float thetaf;
	vec4 axis_f;
	qToAngleAxis(q, thetaf, axis_f);
	std::cout << "  angle = " << thetaf << std::endl;
	vPrint("  axis", axis_f);
	std::cout << "]" << std::endl;
}

///////////////////////////////////////////////////////////////////////

#define HEADER(X) std::cout<<std::endl<<(X)<<std::endl<<std::endl;
/*
void qtest1()
{
	HEADER("TEST 1 : Rotation of 90 degrees about the y-axis")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q = qFromAngleAxis(90.0f, axis);
	qPrint("   q", q);

	qtrn vi = { 0.0f, 7.0f, 0.0f, 0.0f };
	qPrint("  vi", vi);

	qtrn qe = { 0.0f, 0.0f, 0.0f, -7.0f };
	qPrint("  qe", qe);

	qtrn qinv = qInverse(q);
	qClean(qinv);
	qPrint("qinv", qinv);

	qtrn qf = qMultiply(qMultiply(q, vi), qinv);
	qPrint("  qf", qf);

	assert(qEqual(qf, qe));
}

void qtest2()
{
	HEADER("TEST 2 : Rotation of 90 degrees about the y-axis with matrix")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q = qFromAngleAxis(90.0f, axis);
	qPrint(" q", q);

	vec4 vi = { 7.0f, 0.0f, 0.0f, 1.0f };
	vPrint("vi", vi);

	vec4 ve = { 0.0f, 0.0f, -7.0f, 1.0f };
	vPrint("ve", ve);

	mat4 m;
	qGLMatrix(q, m);
	mPrint(" M", m);

	vec4 vf = mMultiply(m, vi);
	vPrint("vf", vf);

	assert(vEqual(vf, ve));
}

void qtest3()
{
	HEADER("TEST 3 : Yaw 900 = Roll 180 + Pitch 180")

		vec4 axis_x = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4 axis_y = { 0.0f, 1.0f, 0.0f, 1.0f };
	vec4 axis_z = { 0.0f, 0.0f, 1.0f, 1.0f };

	qtrn qyaw900 = qFromAngleAxis(900.0f, axis_y);
	qPrint("  qyaw900", qyaw900);

	qtrn qroll180 = qFromAngleAxis(180.0f, axis_x);
	qPrint(" qroll180", qroll180);
	qtrn qpitch180 = qFromAngleAxis(180.0f, axis_z);
	qPrint("qpitch180", qpitch180);
	qtrn qrp = qMultiply(qpitch180, qroll180);
	qPrint("      qrp", qrp);
	qtrn qpr = qMultiply(qroll180, qpitch180);
	qPrint("      qpr", qpr);

	qtrn qi = { 0.0f, 1.0f, 0.0f, 0.0f }; // x-axis
	qPrint("       qi", qi);
	qtrn qe = { 0.0f, -1.0f, 0.0f, 0.0f };
	qPrint("       qe", qe);

	qtrn qyaw900inv = qInverse(qyaw900);
	qtrn qfy = qMultiply(qMultiply(qyaw900, qi), qyaw900inv);
	qPrint("       qy", qfy);
	assert(qEqual(qe, qfy));

	qtrn qrpinv = qInverse(qrp);
	qtrn qfrp = qMultiply(qMultiply(qrp, qi), qrpinv);
	qPrint("     qfrp", qfrp);
	assert(qEqual(qe, qfrp));

	qtrn qprinv = qInverse(qpr);
	qtrn qfpr = qMultiply(qMultiply(qpr, qi), qprinv);
	qPrint("     qfpr", qfpr);
	assert(qEqual(qe, qfpr));
}

void qtest4()
{
	HEADER("TEST 4: Q <-> (angle, axis)")

		float thetai = 45.0f;
	vec4 axis_i = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q = qFromAngleAxis(thetai, axis_i);
	std::cout << thetai << " ";
	vPrint("axis_i", axis_i);

	float thetaf;
	vec4 axis_f;
	qToAngleAxis(q, thetaf, axis_f);
	std::cout << thetaf << " ";
	vPrint("axis_f", axis_f);

	assert(fabs(thetai - thetaf) < qThreshold && vEqual(axis_i, axis_f));
}

void qtest5()
{
	HEADER("TEST 5: LERP")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q0 = qFromAngleAxis(0.0f, axis);
	qPrint("       q0", q0);
	qtrn q1 = qFromAngleAxis(90.0f, axis);
	qPrint("       q1", q1);
	qtrn qe = qFromAngleAxis(30.0f, axis);
	qPrint("       qe", qe);

	qtrn qLerp0 = qLerp(q0, q1, 0.0f);
	qPrint("  lerp(0)", qLerp0);
	assert(qEqual(qLerp0, q0));

	qtrn qLerp1 = qLerp(q0, q1, 1.0f);
	qPrint("  lerp(1)", qLerp1);
	assert(qEqual(qLerp1, q1));

	qtrn qlerp = qLerp(q0, q1, 1 / 3.0f);
	qPrint("lerp(1/3)", qlerp);
	qPrintAngleAxis("lerp(1/3)", qlerp);

	assert(qEqual(qlerp, qe) == 0);
}

void qtest6()
{
	HEADER("TEST 6: SLERP")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q0 = qFromAngleAxis(0.0f, axis);
	qPrint("        q0", q0);
	qtrn q1 = qFromAngleAxis(90.0f, axis);
	qPrint("        q1", q1);
	qtrn qe = qFromAngleAxis(30.0f, axis);
	qPrint("        qe", qe);

	qtrn qSlerp0 = qSlerp(q0, q1, 0.0f);
	qPrint("  slerp(0)", qSlerp0);
	assert(qEqual(qSlerp0, q0));

	qtrn qSlerp1 = qSlerp(q0, q1, 1.0f);
	qPrint("  slerp(1)", qSlerp1);
	assert(qEqual(qSlerp1, q1));

	qtrn qslerp = qSlerp(q0, q1, 1 / 3.0f);
	qPrint("slerp(1/3)", qslerp);
	qPrintAngleAxis("slerp(1/3)", qslerp);

	assert(qEqual(qslerp, qe));
}*/

///////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	/*qtest1();
	qtest2();
	qtest3();
	qtest4();
	qtest5();
	qtest6();*/

	std::cout << std::endl << "Press <return>.";
	std::cin.ignore(1);
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////