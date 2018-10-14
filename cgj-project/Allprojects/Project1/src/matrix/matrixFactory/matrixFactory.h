#pragma once

#include "../matrix3x3/matrix3x3.h"
#include "../matrix4x4/matrix4x4.h"

#include <math.h> //sin && cos

struct matrixFactory {

	matrix3x3 identityMatrix3x3();
	matrix3x3 dualMatrix(vector3&);
	
	matrix3x3 scalingMatrix3x3(vector3& vc);
	matrix4x4 translationMatrix3x3(vector3& vc);
	matrix3x3 rodriguez(vector3&, double);

	matrix4x4 translationMatrix4x4(vector3& vc);
	matrix4x4 scalingMatrix4x4(vector3& vc);
	matrix4x4 rotationMatrix4x4(vector3&, double);

	matrix4x4 identityMatrix4x4();
};