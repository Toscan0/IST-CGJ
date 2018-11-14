#pragma once

#include "../matrix3x3/matrix3x3.h"
#include "../matrix4x4/matrix4x4.h"

#include <math.h>
#define PI 3.14159265

struct matrixFactory {

	// matrix3xx3
	static const matrix3x3 identityMatrix3x3();
	static const matrix3x3 dualMatrix(const vector3&);
	
	static const matrix3x3 scalingMatrix3x3(const vector3& vc);
	static const matrix4x4 translationMatrix3x3(const vector3& vc);
	static const matrix3x3 rodriguez(const vector3&,const double);

	// matrix4x4
	static const matrix4x4 identityMatrix4x4();

	static const matrix4x4 translationMatrix4x4(const vector3& vc);
	static const matrix4x4 scalingMatrix4x4(const vector3& vc);
	static const matrix4x4 rotationMatrix4x4(const vector3&, const  double);

	static const matrix4x4 viewMatrix(const vector3&, const vector3&, const vector3&);
	static const matrix4x4 orthMatrix(const float, const  float, const  float, const  float, 
		const  float, const float);
	static const matrix4x4 prespMatrix(const float, const float, const float, const float);
};