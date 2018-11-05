#pragma once

#include "../matrix3x3/matrix3x3.h"
#include "../matrix4x4/matrix4x4.h"

#include <math.h>
#define PI 3.14159265

struct matrixFactory {

	// matrix3xx3
	static matrix3x3 identityMatrix3x3();
	static matrix3x3 dualMatrix(vector3&);
	
	static matrix3x3 scalingMatrix3x3(vector3& vc);
	static matrix4x4 translationMatrix3x3(vector3& vc);
	static matrix3x3 rodriguez(vector3&, double);

	// matrix4x4
	static matrix4x4 identityMatrix4x4();

	static matrix4x4 translationMatrix4x4(vector3& vc);
	static matrix4x4 scalingMatrix4x4(vector3& vc);
	static matrix4x4 rotationMatrix4x4(vector3&, double);

	const static matrix4x4 viewMatrix(const vector3&, const vector3&, const vector3&);
	static matrix4x4 orthMatrix(float, float, float, float, float, float);
	static matrix4x4 prespMatrix(float, float, float, float);
};