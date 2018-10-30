#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../matrix/matrixFactory/matrixFactory.h"
#include "../matrix/matrix4x4/matrix4x4.h"
#include "../vector/vector3/vector3.h"

class camera {
	protected:
		matrix4x4 _viewMatrix, _prespMatrix, _orthMatrix;
		vector3 _center, _eye, _view, _up;
	
	public:
		camera();
		//camera(vector3&, vector3&);
		const matrix4x4 makeViewMatrix(const vector3&, const vector3&, const vector3&);

		// get & set
		const matrix4x4 getViewMatrix();
		const matrix4x4 getPrespMatrix();
		const matrix4x4 getOrthMatrix();

		void setViewMatrix(matrix4x4&);
		void setPrespMatrix(matrix4x4&);
		void setOrthMatrix(matrix4x4&);

		

		const vector3 getCenter();
		const vector3 getView();
		const vector3 getUp();
		const vector3 getEye();

		void setCenter(vector3&);
		void setView(vector3&);
		void setUp(vector3&);
		void setEye(vector3&);
};