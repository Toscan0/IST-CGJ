#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../matrix/matrixFactory/matrixFactory.h"
#include "../matrix/matrix4x4/matrix4x4.h"
#include "../vector/vector3/vector3.h"
#include "../qtrn/qtrn.h"

class camera {
	protected:
		matrix4x4 _viewMatrix, _prespMatrix, _orthMatrix;
		vector3 _center, _eye, _view, _up;
		qtrn _q = { 1.0f, 0.0f, 0.0f, 0.0f }; //quarterion resposible for viewMatrix rotation

	public:
		camera();
		
		const matrix4x4 makeViewMatrix(const vector3&, const vector3&, const vector3&);
		const matrix4x4 makePrespMatrix(const float fovy, const float aspect, const float n, const float f);
		
		// get & set
		const matrix4x4 getViewMatrix();
		void setViewMatrix(matrix4x4&);

		const matrix4x4 getPrespMatrix();
		void setPrespMatrix(matrix4x4&);

		const matrix4x4 getOrthMatrix();
		void setOrthMatrix(matrix4x4&);

		const vector3 getCenter();
		void setCenter(vector3&);

		const vector3 getView();
		void setView(vector3&);

		const vector3 getUp();
		void setUp(vector3&);

		const vector3 getEye();
		void setEye(vector3&);	

		const qtrn getRotQtrn();
		void setRotQtrn(const qtrn&);
};