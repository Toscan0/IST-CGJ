#include "qtrn.h"

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
	q._x = axisn._x * s;
	q._y = axisn._y * s;
	q._z = axisn._z * s;

	qClean(q);
	return qNormalize(q);
}

const void qtrn::qToAngleAxis(const qtrn& q, float& theta, vec4& axis)
{
	qtrn qn = qNormalize(q);
	theta = 2.0f * acos(qn._t) * (float)RADIANS_TO_DEGREES;
	float s = sqrt(1.0f - qn._t*qn._t);
	if (s < _qThreshold) {
		axis._x = 1.0f;
		axis._y = 0.0f;
		axis._z = 0.0f;
		axis._w = 1.0f;
	}
	else {
		axis._x = qn._x / s;
		axis._y = qn._y / s;
		axis._z = qn._z / s;
		axis._w = 1.0f;
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

	//mClean(matrix);
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
