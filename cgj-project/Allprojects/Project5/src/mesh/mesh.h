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

typedef struct Vertex {
	GLfloat x, y, z;
	Vertex() {}
	Vertex(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	Vertex operator - (const Vertex &v)  const { return Vertex(x - v.x, y - v.y, z - v.z); }
	Vertex operator * (GLfloat c)     const { return Vertex(x*c, y*c, z*c); }
};

typedef struct Texcoord {
	GLfloat u, v;
	Texcoord() {}
	Texcoord(GLfloat u, GLfloat v) : u(u), v(v) {}
	Texcoord operator - (const Texcoord &t)  const { return Texcoord(u - t.u, v - t.v); }
};

typedef struct {
	GLfloat nx, ny, nz;
} Normal;

typedef GLfloat Matrix[16];

class mesh{
	protected:
		#define VERTICES 0
		#define TEXCOORDS 1
		#define NORMALS 2
		#define TANGENTS 3
		#define BITANGENTS 4

		GLuint _VaoId;
		bool _TexcoordsLoaded, _NormalsLoaded;

		std::vector <Vertex> _Vertices, _vertexData, _Tangents, _Bitangents;
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
		void computeTangBitang();
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

