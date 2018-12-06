#include "camera.h"


camera::camera() {}

const matrix4x4 camera::makeViewMatrix(const vector3& eye, const vector3& center, const vector3& up) {
	typedef GLfloat Matrix[16];
	Matrix ViewMatrix;
	matrixFactory mf;
	
	matrix4x4 vM = mf.viewMatrix(eye, center, up);
	matrix4x4 vMAux = vM.transposeM4x4();

	setViewMatrix(vMAux);

	return vMAux;
}

const matrix4x4 camera::makePrespMatrix(const float fovy, const float aspect,
	const float n, const float f) {
	typedef GLfloat Matrix[16];
	Matrix ViewMatrix;
	matrixFactory mf;
	
	matrix4x4 mP = mf.prespMatrix(fovy, aspect, n, f); // matrix prespetiva
	matrix4x4 mPAux = mP.transposeM4x4();

	setPrespMatrix(mPAux);

	return mPAux;
}



const matrix4x4 camera::getViewMatrix() {
	return _viewMatrix;
}
const matrix4x4 camera::getPrespMatrix() {
	return _prespMatrix;
}
const matrix4x4 camera::getOrthMatrix() {
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


void camera::setCenter(vector3& center) {
	_center = center;
}

void camera::setView(vector3& view) {
	_view = view;
}

void camera::setUp(vector3& up) {
	_up = up;
}

const vector3 camera::getCenter() {
	return _center;
}

const vector3 camera::getView() {
	return _view;
}

const vector3 camera::getUp() {
	return _up;
}

const vector3 camera::getEye() {
	return _eye;
}

void camera::setEye(vector3& eye) {
	_eye = eye;
}


const qtrn camera::getRotQtrn() {
	return _q;
}

void camera::setRotQtrn(const qtrn& q){
	_q = q;
}