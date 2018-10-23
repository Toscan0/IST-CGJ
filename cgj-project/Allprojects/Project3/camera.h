#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "src/matrix/matrixFactory/matrixFactory.h"
#include "src/matrix/matrix4x4/matrix4x4.h"
#include "src/vector/vector3/vector3.h"

struct camera {
	matrix4x4 _viewMatrix, _prespMatrix, _orthMatrix;
	vector3 _center, _lookAt;

	

	matrix4x4 makeViewMatrix(vector3&, vector3&, vector3&);

	// get & set
	matrix4x4 getViewMatrix();
	matrix4x4 getPrespMatrix();
	matrix4x4 getOrthMatrix();

	void setViewMatrix(matrix4x4&);
	void setPrespMatrix(matrix4x4&);
	void setOrthMatrix(matrix4x4&);
};