#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "src/matrix/matrixFactory/matrixFactory.h"
#include "src/matrix/matrix4x4/matrix4x4.h"
#include "src/vector/vector3/vector3.h"

class camera {
	protected:
		matrix4x4 _viewMatrix, _prespMatrix, _orthMatrix;
		vector3 _center, _eye, _view, _up;
	
	public:
		camera();
		//camera(vector3&, vector3&);
		matrix4x4 makeViewMatrix(vector3&, vector3&, vector3&);

		// get & set
		matrix4x4 getViewMatrix();
		matrix4x4 getPrespMatrix();
		matrix4x4 getOrthMatrix();

		void setViewMatrix(matrix4x4&);
		void setPrespMatrix(matrix4x4&);
		void setOrthMatrix(matrix4x4&);

		

		vector3 getCenter();
		vector3 getView();
		vector3 getUp();
		vector3 getEye();

		void setCenter(vector3&);
		void setView(vector3&);
		void setUp(vector3&);
		void setEye(vector3&);
};