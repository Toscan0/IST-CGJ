#include "camera.h"


camera::camera() {}

void camera::makeViewMatrix() {
	matrixFactory mf;
	vector3 tran(0, 0, -(_eye.norma()));
	_T = mf.translationMatrix4x4(tran);
	_qview = qtrn(1, 0, 0, 0); // convert view em qtrn
}

const matrix4x4 camera::makePrespMatrix(const float fovy, const float aspect, const float n, const float f) {

	matrixFactory mf;
	
	matrix4x4 mP = mf.prespMatrix(fovy, aspect, n, f); // matrix prespetiva
	matrix4x4 mPAux = mP.transposeM4x4();

	setPrespMatrix(mPAux);

	return mPAux;
}

const matrix4x4 camera::getViewMatrix() {
	matrix4x4 mAux;
	matrix4x4 R = qGLMatrix(_qview, mAux);  // matrix rotação devolve em row major
	matrix4x4 TR = _T * R;
	matrix4x4 rTR = TR.transposeM4x4();
	return rTR;
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

void camera::setqView(qtrn& view) {
	_qview = view;
}
/*
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
*/

const vector3 camera::getEye() {
	return _eye;
}

void camera::setEye(vector3& eye) {
	_eye = eye;
}

const vector3 camera::getLight() {
	return _light;
}

const qtrn camera::getqView() {
	return _qview;
}

void camera::setLight(vector3& light) {
	_light = light;
}