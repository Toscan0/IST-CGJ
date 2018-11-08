#include "mesh.h"

mesh::mesh() {}

void mesh::parseVertex(std::stringstream& sin)
{
	Vertex v;
	sin >> v.x >> v.y >> v.z;
	_vertexData.push_back(v);
}

void mesh::parseTexcoord(std::stringstream& sin)
{
	Texcoord t;
	sin >> t.u >> t.v;
	_texcoordData.push_back(t);
}

void mesh::parseNormal(std::stringstream& sin)
{
	Normal n;
	sin >> n.nx >> n.ny >> n.nz;
	_normalData.push_back(n);
}

void mesh::parseFace(std::stringstream& sin)
{
	std::string token;
	for (int i = 0; i < 3; i++) {
		std::getline(sin, token, '/');
		if (token.size() > 0) _vertexIdx.push_back(std::stoi(token));
		std::getline(sin, token, '/');
		if (token.size() > 0) _texcoordIdx.push_back(std::stoi(token));
		std::getline(sin, token, ' ');
		if (token.size() > 0) _normalIdx.push_back(std::stoi(token));
	}
}

void mesh::parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void mesh::loadMeshData(const std::string& filename, shaders& myShader)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) {
		std::stringstream sin = std::stringstream(line);
		parseLine(sin);
	}
	myShader.setTexcoordsLoaded((_texcoordIdx.size() > 0));
	myShader.setNormalsLoaded((_normalIdx.size() > 0));
}

void mesh::processMeshData(shaders& myShader)
{
	for (unsigned int i = 0; i < _vertexIdx.size(); i++) {
		unsigned int vi = _vertexIdx[i];
		Vertex v = _vertexData[vi - 1];
		_Vertices.push_back(v);
		if (myShader.getTexcoordsLoaded()) {
			unsigned int ti = _texcoordIdx[i];
			Texcoord t = _texcoordData[ti - 1];
			_Texcoords.push_back(t);
		}
		if (myShader.getNormalsLoaded()) {
			unsigned int ni = _normalIdx[i];
			Normal n = _normalData[ni - 1];
			_Normals.push_back(n);
		}
	}
}

void mesh::freeMeshData()
{
	_vertexData.clear();
	_texcoordData.clear();
	_normalData.clear();
	_vertexIdx.clear();
	_texcoordIdx.clear();
	_normalIdx.clear();
}

const void mesh::createMesh(const std::string& filename, shaders& myShader)
{
	loadMeshData(filename, myShader);
	processMeshData(myShader);
	freeMeshData();
}

// get
const std::vector<Vertex> mesh::getVertices() {
	return _Vertices;
}

const std::vector<Vertex> mesh::getVertexData() {
	return _vertexData;
}

const std::vector<Texcoord> mesh::getTexcoords() {
	return _Texcoords;
}

const std::vector<Texcoord> mesh::getTexcoordData() {
	return _texcoordData;
}

const std::vector<Normal> mesh::getNormals() {
	return _Normals;
}

const std::vector<Normal> mesh::getNormalData() {
	return _normalData;
}

const std::vector<unsigned int> mesh::getVertexID() {
	return _vertexIdx;
}

const std::vector<unsigned int> mesh::getTexcoodIdx() {
	return _texcoordIdx;
}

const std::vector<unsigned int> mesh::getNormalIdx() {
	return _normalIdx;
}