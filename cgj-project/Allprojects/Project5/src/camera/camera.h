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
		vector3 _light, _eye; // , _view, _center, _up;
		qtrn _qview;
	
	public:
		camera();
		matrix4x4 _T;
		void makeViewMatrix();
		const matrix4x4 makePrespMatrix(const float fovy, const float aspect, const float n, const float f);
		// get & set
		const matrix4x4 getViewMatrix();
		const matrix4x4 getPrespMatrix();
		const matrix4x4 getOrthMatrix();

		void setViewMatrix(matrix4x4&);
		void setPrespMatrix(matrix4x4&);
		void setOrthMatrix(matrix4x4&);

		

		//const vector3 getCenter();
		const qtrn getqView();
		//const vector3 getView();
		//const vector3 getUp();
		const vector3 getEye();
		const vector3 getLight();

		//void setCenter(vector3&);
		void setqView(qtrn&);
		//void setView(vector3&);
		//void setUp(vector3&);
		void setEye(vector3&);
		void setLight(vector3&);
};