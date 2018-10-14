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
matrix3x3 matrixFactory::scalingMatrix3x3(vector3& vc) {

	matrix3x3 s (vc._a, 0, 0, 0, vc._b, 0, 0, 0, vc._c);
	
	return s;
}

matrix4x4 matrixFactory::scalingMatrix4x4(vector3& vc) {

	matrix4x4 mS (vc._a, 0, 0, 0,
				0,vc._b, 0, 0, 
				0, 0, vc._c, 0,
				0, 0, 0, 1);

	return mS;
}

// Translação matrix
matrix4x4 matrixFactory::translationMatrix3x3(vector3& vc) {

	matrix4x4 mTr (1, 0, 0, vc._a, 0, 1, 0, vc._b, 0, 0, 1, vc._c, 0, 0, 0, 1);

	return mTr;
}

matrix4x4 matrixFactory::translationMatrix4x4(vector3& vc) {
	matrix4x4 m(1, 0, 0, vc._a,
		0, 1, 0, vc._b,
		0, 0, 1, vc._c,
		0, 0, 0, 1);
	
	return m;
}


// Translação matrix
matrix4x4 matrixFactory::rotationMatrix4x4(vector3& v, double x) {
	matrix3x3 r = rodriguez(v, x);

	matrix4x4 mR (r._a, r._b, r._c, 0,
		r._d, r._e, r._f, 0,
		r._g, r._h, r._i, 0,
		0, 0, 0, 1);

	return mR;
}






// Rodriguez Formula ( R(x) = I + sen(x)A + (1 - cos(x))A^2 )
matrix3x3 matrixFactory::rodriguez(vector3& v, double x) {
	matrix3x3 i = identityMatrix3x3();
	matrix3x3 dual = dualMatrix(v);
	matrix3x3 dualQ = dual * dual;

	matrix3x3 r = (i + (dual * sin(x)) + (dualQ * (1 - cos(x))));
	
	return r;
}

