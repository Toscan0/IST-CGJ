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
#include "../shaders/shaders.h"

typedef struct {
	GLfloat x, y, z;
} Vertex;

typedef struct {
	GLfloat u, v;
} Texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Normal;

class mesh{
	protected:
		std::vector <Vertex> _Vertices, _vertexData;
		std::vector <Texcoord> _Texcoords, _texcoordData;
		std::vector <Normal> _Normals, _normalData;
		std::vector <unsigned int> _vertexIdx, _texcoordIdx, _normalIdx;

	public:
		mesh();

		const void createMesh(const std::string& filename, shaders& myShader);

		void parseVertex(std::stringstream& sin);
		void parseTexcoord(std::stringstream& sin);
		void parseNormal(std::stringstream& sin);
		void parseFace(std::stringstream& sin);
		void parseLine(std::stringstream& sin);
		void loadMeshData(const std::string& filename, shaders& myShader);
		void processMeshData(shaders& myShader);
		void freeMeshData();

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
};

