#include "matrix.h"
#include "matrixFactory.h"

// Identity Matrix
// Matrix 3x3
matrix3x3 matrixFactory::identityMatrix3x3() {
	
	matrix3x3 ind(1, 0, 0, 
				0, 1, 0, 
				0, 0, 1);

	return ind;
}

// Matrix 4x4
matrix4x4 matrixFactory::identityMatrix4x4() {

	matrix4x4 ind(1, 0, 0, 0, 
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1); 

	return ind;
}

// Dual Matrix
// Matrix 3x3
matrix3x3 matrixFactory::dualMatrix(vector3& vc) {

	matrix3x3 dual (0, -vc._c, vc._b, vc._c, 0, -vc._a, -vc._b, vc._a, 0);

	return dual;
}

// Scaling matrix
// Matrix 3x3
matrix3x3 matrixFactory::scalingMatrix3x3(matrix3x3 m, vector3& vc) {

	matrix3x3 s (vc._a, 0, 0, 0, vc._b, 0, 0, 0, vc._c);
	matrix3x3 res = s * m;
	
	return res;
}

// Translação matrix
/*
matrix3x3 matrixFactory::translationMatrix3x3(matrix3x3 m, vector3& vc) {

	matrix4x4 T (1, 0, 0, vc._a, 0, 1, 0, vc._b,  0, 0, 1, vc._c, 0, 0, 0, 1);

	matrix3x3 res = s * m;

	return res;
}*/
