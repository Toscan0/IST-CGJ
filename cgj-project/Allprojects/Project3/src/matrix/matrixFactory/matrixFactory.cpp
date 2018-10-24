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

	matrix4x4 mTr (1, 0, 0, vc._a, 
				   0, 1, 0, vc._b, 
				   0, 0, 1, vc._c, 
				   0, 0, 0, 1);

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
	vector3 vNormalizado = v.normalizado();
	matrix3x3 i = identityMatrix3x3();
	matrix3x3 dual = dualMatrix(v);
	matrix3x3 dualQ = dual * dual;

	matrix3x3 r = (i + (dual * sin(x)) + (dualQ * (1 - cos(x))));
	
	return r;
}

matrix4x4 matrixFactory::viewMatrix(vector3& eye, vector3& center, vector3& up) {
	vector3 view = center - eye;

	float vNorma = view.norma();
	vector3 v = view * (1 / vNorma);

	vector3 side = cross(v,  up);
	
	float sideNorma = side.norma();

	vector3 s = side * (1 / sideNorma);

	vector3 u = cross(s, v);

	matrix4x4 mR (s._a, s._b, s._c, 0,
		u._a, u._b, u._c, 0,
		-v._a, -v._a, -v._c, 0,
		0, 0, 0, 1);

	matrix4x4 mT (1, 0, 0, -eye._a,
		0, 1, 0, -eye._b,
		0, 0, 1, -eye._c,
		0, 0, 0, 1);
	
	matrix4x4 viewMatrix = mR * mT;

	return viewMatrix;
}

matrix4x4 matrixFactory::orthMatrix(float l, float r, float t, float b, float n, float f) {
	matrix4x4 mOrth((2 / (r - l)), 0, 0, -((r + l) / (r - l)),
					0, (2 / (t - b)), 0, -((t + b) / (t - b)),
					0, 0, -(2 / (f - n)), -((f + n) / (f - n)),
					0, 0, 0, 1);
	
	return mOrth;
}

matrix4x4 matrixFactory::prespMatrix(float fovy, float aspect, float n, float f) {
	float teta = (fovy / 2.0f);
	float d = (1.0f / (tan(teta)));

	matrix4x4 mPresp( (d / aspect), 0, 0, 0,
		0, d, 0, 0,
		0, 0, -((f + n) / (f - n)), -((2 * f * n) / (f - n)),
		0, 0, -1, 0);

	return mPresp;
}