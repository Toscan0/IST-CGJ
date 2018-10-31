#include "mat4.h"

const vec4 mMultiply(mat4 m, vec4& v)
{
	vec4 r;
	r._x = m[0] * v._x + m[4] * v._y + m[8] * v._z + m[12] * v._w;
	r._y = m[1] * v._x + m[5] * v._y + m[9] * v._z + m[13] * v._w;
	r._z = m[2] * v._x + m[6] * v._y + m[10] * v._z + m[14] * v._w;
	r._w = m[3] * v._x + m[7] * v._y + m[11] * v._z + m[15] * v._w;
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