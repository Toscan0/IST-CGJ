#include "camera.h"



matrix4x4 camera::makeViewMatrix(vector3& eye, vector3& center, vector3& up) {
	typedef GLfloat Matrix[16];
	Matrix ViewMatrix;
	matrixFactory mf;
	matrix4x4 vM = mf.viewMatrix(eye, center, up);
	matrix4x4 vMAux = vM.transposeM4x4();

	setViewMatrix(vMAux);

	return vMAux;
}




matrix4x4 camera::getViewMatrix() {
	return _viewMatrix;
}
matrix4x4 camera::getPrespMatrix() {
	return _prespMatrix;
}
matrix4x4 camera::getOrthMatrix() {
	return _orthMatrix;
}


void camera::setViewMatrix(matrix4x4& m) {
	_viewMatrix = m;
}

void camera::setPrespMatrix(matrix4x4& m) {
	_prespMatrix = m;
}

void camera::setOrthMatrix(matrix4x4& m) {
	_orthMatrix = m;
}