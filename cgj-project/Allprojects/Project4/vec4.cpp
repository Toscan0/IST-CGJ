#include "vec4.h"

vec4::vec4(){}

vec4::vec4(float x, float y, float z, float w) {
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

const float vec4::getVTreshhold() {
	return _vThreshold;
}

const vec4 vNormalize(const vec4& v)
{
	vec4 vn;
	float s = 1 / (v._w * sqrt(v._x*v._x + v._y*v._y + v._z*v._z));
	vn._x = v._x * s;
	vn._y = v._y * s;
	vn._z = v._z * s;
	vn._w = 1.0f;
	return vn;
}

const void vPrint(const std::string s, const vec4& v)
{
	std::cout << s << " = (" << v._x << ", " << v._y << ", " << v._z << ", " << v._w << ")" << std::endl;
}

const bool vEqual(const vec4& v0, const vec4& v1)
{
	vec4 vecAux;
	const float vThreshold = vecAux.getVTreshhold();
	return (fabs(v0._x - v1._x) < vThreshold && fabs(v0._y - v1._y) < vThreshold &&
		fabs(v0._z - v1._z) < vThreshold && fabs(v0._w - v1._w) < vThreshold);
}