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
<<<<<<< HEAD
=======
}
/*
void camera::setCenter(vector3& center) {
	_center = center;
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
}

const vector3 camera::getEye() {
	return _eye;
}

void camera::setEye(vector3& eye) {
	_eye = eye;
}

const vector3 camera::getLight() {
	return _light;
}
*/

const qtrn camera::getqView() {
	return _qview;
}

<<<<<<< HEAD
=======
void camera::setEye(vector3& eye) {
	_eye = eye;
}

const vector3 camera::getLight() {
	return _light;
}

const qtrn camera::getqView() {
	return _qview;
}

>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
void camera::setLight(vector3& light) {
	_light = light;
}