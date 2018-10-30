#include "mat4.h"

mat4::mat4(){}

mat4::mat4(float a, float b, float c, float d, float e, float f, float g,
	float h, float i, float j, float k, float l, float m, float n, float o, float p) {
	_a = a;
	_b = b;
	_c = c;
	_d = d;
	_e = e;
	_f = f;
	_g = g;
	_h = h;
	_i = i;
	_j = j;
	_k = k;
	_l = l;
	_m = m;
	_n = n;
	_o = o;
	_p = p;
}

const float mat4::getMThreshold() {
	return _mThreshold;
}

float* mat4::data() {
	float* m = new float[16];

	m[0] = _a;
	m[1] = _e;
	m[2] = _i;
	m[3] = _m;
	m[4] = _b;
	m[5] = _f;
	m[6] = _j;
	m[7] = _n;
	m[8] = _c;
	m[9] = _g;
	m[10] = _k;
	m[11] = _o;
	m[12] = _d;
	m[13] = _h;
	m[14] = _l;
	m[15] = _p;

	return m;
}

const vec4 mMultiply(mat4 m4, vec4& v)
{
	vec4 r;
	float* m = m4.data();
	r._x = m[0] * v._x + m[4] * v._y + m[8] * v._z + m[12] * v._w;
	r._y = m[1] * v._x + m[5] * v._y + m[9] * v._z + m[13] * v._w;
	r._z = m[2] * v._x + m[6] * v._y + m[10] * v._z + m[14] * v._w;
	r._w = m[3] * v._x + m[7] * v._y + m[11] * v._z + m[15] * v._w;
	return r;
}
/*
const void mClean(mat4 m4)
{
	mat4 mAux;
	float* m = m4.data();
	const float mThreshold = mAux.getMThreshold();
	for (int i = 0; i < 16; i++) {
		if (fabs(m[i]) < mThreshold) m[i] = 0.0f;
	}
}*/

const void mClean(float* m)
{
	mat4 mAux;
	const float mThreshold = mAux.getMThreshold();
	for (int i = 0; i < 16; i++) {
		if (fabs(m[i]) < mThreshold) m[i] = 0.0f;
	}
}

const void mPrint(const std::string s, mat4 m4)
{
	float* m = m4.data();
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


