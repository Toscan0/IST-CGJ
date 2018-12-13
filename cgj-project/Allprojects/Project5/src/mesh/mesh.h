#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../matrix/matrixFactory/matrixFactory.h"
#include "../matrix/matrix4x4/matrix4x4.h"
#include "../vector/vector3/vector3.h"
#include "../shader/shader.h"
#include "../camera/camera.h"

typedef struct {
	GLfloat x, y, z;
} Vertex;

typedef struct {
	GLfloat u, v;
} Texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Normal;

typedef GLfloat Matrix[16];

const Matrix I = {
			1.0f,  0.0f,  0.0f,  0.0f,
			0.0f,  1.0f,  0.0f,  0.0f,
			0.0f,  0.0f,  1.0f,  0.0f,
			0.0f,  0.0f,  0.0f,  1.0f
};

/*const Matrix ModelMatrix = {
	1.0f,  0.0f,  0.0f,  0.0f,
	0.0f,  1.0f,  0.0f,  0.0f,
	0.0f,  0.0f,  1.0f,  0.0f,
	0.0f,  0.0f,  0.0f,  1.0f
}; // Column Major
*/
/*
// Eye(5,5,5) Center(0,0,0) Up(0,1,0)
const Matrix ViewMatrix1 = {
	0.70f, -0.41f,  0.58f,  0.00f,
	0.00f,  0.82f,  0.58f,  0.00f,
   -0.70f, -0.41f,  0.58f,  0.00f,
	0.00f,  0.00f, -8.70f,  1.00f
}; // Column Major

// Eye(-5,-5,-5) Center(0,0,0) Up(0,1,0)
const Matrix ViewMatrix2 = {
   -0.70f, -0.41f, -0.58f,  0.00f,
	0.00f,  0.82f, -0.58f,  0.00f,
	0.70f, -0.41f, -0.58f,  0.00f,
	0.00f,  0.00f, -8.70f,  1.00f
}; // Column Major
*/
// Orthographic LeftRight(-2,2) TopBottom(-2,2) NearFar(1,10)
const Matrix ProjectionMatrix1 = {
	0.50f,  0.00f,  0.00f,  0.00f,
	0.00f,  0.50f,  0.00f,  0.00f,
	0.00f,  0.00f, -0.22f,  0.00f,
	0.00f,  0.00f, -1.22f,  1.00f
}; // Column Major
/*
// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
const Matrix ProjectionMatrix2 = {
	2.79f,  0.00f,  0.00f,  0.00f,
	0.00f,  3.73f,  0.00f,  0.00f,
	0.00f,  0.00f, -1.22f, -1.00f,
	0.00f,  0.00f, -2.22f,  0.00f
}; // Column Major
*/

class mesh{
	protected:
		#define VERTICES 0
		#define TEXCOORDS 1
		#define NORMALS 2

		GLuint _VaoId;
		bool _TexcoordsLoaded, _NormalsLoaded;

		std::vector <Vertex> _Vertices, _vertexData;
		std::vector <Texcoord> _Texcoords, _texcoordData;
		std::vector <Normal> _Normals, _normalData;
		std::vector <unsigned int> _vertexIdx, _texcoordIdx, _normalIdx;		

	public:
		mesh();

		const void createMesh(const std::string& filename);

		void parseVertex(std::stringstream& sin);
		void parseTexcoord(std::stringstream& sin);
		void parseNormal(std::stringstream& sin);
		void parseFace(std::stringstream& sin);
		void parseLine(std::stringstream& sin);
		void loadMeshData(const std::string& filename);
		void processMeshData();
		void freeMeshData();
		
		void draw();
		
		void createBufferObjects();
		void destroyBufferObjects();

		// get & set
		const std::vector<Vertex> getVertices();
		const std::vector<Vertex> getVertexData();
		const std::vector<Texcoord> getTexcoords();
		const std::vector<Texcoord> getTexcoordData();
		const std::vector<Normal> getNormals();
		const std::vector<Normal> getNormalData();
		const std::vector<unsigned int> getVertexID();
		const std::vector<unsigned int> getTexcoodIdx();
		const std::vector<unsigned int> getNormalIdx();
		
		const GLuint getVaoId();
		const bool getTexcoordsLoaded();
		const bool getNormalsLoaded();
};

