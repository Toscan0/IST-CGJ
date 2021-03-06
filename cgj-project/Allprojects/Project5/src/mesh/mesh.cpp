#include "mesh.h"

mesh::mesh() {}

const void mesh::createMesh(const std::string& filename)
{
	loadMeshData(filename);
	processMeshData();
	if (_TexcoordsLoaded)
		computeTangBitang();
	freeMeshData();
}

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

void mesh::loadMeshData(const std::string& filename)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) {
		std::stringstream sin = std::stringstream(line);
		parseLine(sin);
	}
	_TexcoordsLoaded = (_texcoordIdx.size() > 0);
	_NormalsLoaded = (_normalIdx.size() > 0);
}

void mesh::processMeshData()
{
	for (unsigned int i = 0; i < _vertexIdx.size(); i++) {
		unsigned int vi = _vertexIdx[i];
		Vertex v = _vertexData[vi - 1];
		_Vertices.push_back(v);
		if (_TexcoordsLoaded) {
			unsigned int ti = _texcoordIdx[i];
			Texcoord t = _texcoordData[ti - 1];
			_Texcoords.push_back(t);
		}
		if (_NormalsLoaded) {
			unsigned int ni = _normalIdx[i];
			Normal n = _normalData[ni - 1];
			_Normals.push_back(n);
		}
	}
}

void mesh::computeTangBitang()
{
	for (unsigned int i = 0; i < _Vertices.size(); i += 3) {

		// Shortcuts for vertices
		Vertex & v0 = _Vertices[i + 0];
		Vertex & v1 = _Vertices[i + 1];
		Vertex & v2 = _Vertices[i + 2];

		// Shortcuts for UVs
		Texcoord & uv0 = _Texcoords[i + 0];
		Texcoord & uv1 = _Texcoords[i + 1];
		Texcoord & uv2 = _Texcoords[i + 2];

		// Edges of the triangle : position delta
		Vertex deltaPos1 = v1 - v0;
		Vertex deltaPos2 = v2 - v0;

		// UV delta
		Texcoord deltaUV1 = uv1 - uv0;
		Texcoord deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.u * deltaUV2.v - deltaUV1.v * deltaUV2.u);
		Vertex tangent = (deltaPos1 * deltaUV2.v - deltaPos2 * deltaUV1.v)*r;
		Vertex bitangent = (deltaPos2 * deltaUV1.u - deltaPos1 * deltaUV2.u)*r;

		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later
		_Tangents.push_back(tangent);
		_Tangents.push_back(tangent);
		_Tangents.push_back(tangent);

		// Same thing for bitangents
		_Bitangents.push_back(bitangent);
		_Bitangents.push_back(bitangent);
		_Bitangents.push_back(bitangent);
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

void mesh::draw() {
	glBindVertexArray(_VaoId);	
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_Vertices.size());
	glUseProgram(0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not draw scene.");
}

void mesh::createBufferObjects()
{
	GLuint VboVertices, VboTexcoords, VboNormals, VboTangent, VboBitangent;

	glGenVertexArrays(1, &_VaoId);
	glBindVertexArray(_VaoId);
	{
		glGenBuffers(1, &VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
		glBufferData(GL_ARRAY_BUFFER, _Vertices.size() * sizeof(Vertex), &_Vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		if (_TexcoordsLoaded)
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, _Texcoords.size() * sizeof(Texcoord), &_Texcoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);

			glGenBuffers(1, &VboTangent);
			glBindBuffer(GL_ARRAY_BUFFER, VboTangent);
			glBufferData(GL_ARRAY_BUFFER, _Tangents.size() * sizeof(Vertex), &_Tangents[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TANGENTS);
			glVertexAttribPointer(TANGENTS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

			glGenBuffers(1, &VboBitangent);
			glBindBuffer(GL_ARRAY_BUFFER, VboBitangent);
			glBufferData(GL_ARRAY_BUFFER, _Bitangents.size() * sizeof(Vertex), &_Bitangents[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(BITANGENTS);
			glVertexAttribPointer(BITANGENTS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}
		if (_NormalsLoaded)
		{
			glGenBuffers(1, &VboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
			glBufferData(GL_ARRAY_BUFFER, _Normals.size() * sizeof(Normal), &_Normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboVertices);
	glDeleteBuffers(1, &VboTexcoords);
	glDeleteBuffers(1, &VboNormals);
	glDeleteBuffers(1, &VboTangent);
	glDeleteBuffers(1, &VboBitangent);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void mesh::destroyBufferObjects(){
	glBindVertexArray(_VaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(TEXCOORDS);
	glDisableVertexAttribArray(NORMALS);
	glDisableVertexAttribArray(TANGENTS);
	glDisableVertexAttribArray(BITANGENTS);
	glDeleteVertexArrays(1, &_VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
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

const GLuint mesh::getVaoId() {
	return _VaoId;
}

const bool mesh::getTexcoordsLoaded() {
	return _TexcoordsLoaded;
}

const bool mesh::getNormalsLoaded() {
	return _NormalsLoaded;
}