#pragma once

#include "matrix.h"

struct matrixFactory {

	matrix3x3 identityMatrix3x3();
	matrix3x3 dualMatrix(vector3&);
	
	matrix3x3 scalingMatrix3x3(matrix3x3 m, vector3& vc);
	matrix3x3 translationMatrix3x3(matrix3x3 m, vector3& vc);
	matrix3x3 rotationMatrix3x3(matrix3x3 m, vector3& vc);

	matrix4x4 identityMatrix4x4();
};