#include "shaders.h"

std::string shaders::readShaderFile(const char *shader_file)
{
	//open file in read mode
	std::ifstream file(shader_file);
	if (!file) {
		return std::string();
	}

	file.ignore(std::numeric_limits<std::streamsize>::max());
	auto size = file.gcount();

	if (size > 0x10000) {
		return std::string();
	}

	file.clear();
	file.seekg(0, std::ios_base::beg);

	std::stringstream sstr;
	sstr << file.rdbuf();
	file.close();

	return sstr.str();
}

void shaders::createShader(const char* vertexPath, const char* fragPath) {
	std::string vertex_source = readShaderFile(vertexPath);
	const char *vertexShader = vertex_source.c_str();

	_VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_VertexShaderId, 1, &vertexShader, 0);
	glCompileShader(_VertexShaderId);

	std::string fragment_source = readShaderFile(fragPath);
	const char *fragmentShader = fragment_source.c_str();

	_FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_FragmentShaderId, 1, &fragmentShader, 0);
	glCompileShader(_FragmentShaderId);

	_ProgramId = glCreateProgram();
	glAttachShader(_ProgramId, _VertexShaderId);
	glAttachShader(_ProgramId, _FragmentShaderId);

	glBindAttribLocation(_ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(_ProgramId, COLORS, "in_Color");

	glLinkProgram(_ProgramId);
	

	glDetachShader(_ProgramId, _VertexShaderId);
	glDeleteShader(_VertexShaderId);
	glDetachShader(_ProgramId, _FragmentShaderId);
	glDeleteShader(_FragmentShaderId);

	//checkOpenGLError("ERROR: Could not create shaders.");
}

void shaders::destroyShader(){
	glUseProgram(0);
	glDeleteProgram(_ProgramId);

	//checkOpenGLError("ERROR: Could not destroy shaders.");
}

/*
void shaders::createBuffer() {
	// Triangle
	glGenVertexArrays(1, &_VaoIdSTri);
	glBindVertexArray(_VaoIdSTri);
	{
		glGenBuffers(2, _VboIdSTri);

		glBindBuffer(GL_ARRAY_BUFFER, _VboIdSTri[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesSTri), VerticesSTri, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(VerticesSTri[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VboIdSTri[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesSTri), IndicesSTri, GL_STATIC_DRAW);
		}
	}

	// Square
	glGenVertexArrays(1, &_VaoIdSquare);
	glBindVertexArray(_VaoIdSquare);
	{
		glGenBuffers(2, _VboIdSquare);

		glBindBuffer(GL_ARRAY_BUFFER, _VboIdSquare[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesSquare), VerticesSquare, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(VerticesSquare[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VboIdSquare[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesSquare), IndicesSquare, GL_STATIC_DRAW);
		}
	}

	// Parall
	glGenVertexArrays(1, &_VaoIdParall);
	glBindVertexArray(_VaoIdParall);
	{
		glGenBuffers(2, _VboIdParall);

		glBindBuffer(GL_ARRAY_BUFFER, _VboIdParall[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesParall), VerticesParall, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(VerticesParall[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VboIdParall[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesParall), IndicesParall, GL_STATIC_DRAW);
		}
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}*/

/*
void shaders::destroyBuffer() {
	glBindVertexArray(_VaoIdSTri);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glDeleteBuffers(2, _VboIdSTri);
	glDeleteVertexArrays(1, &_VaoIdSTri);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(_VaoIdSquare);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glDeleteBuffers(2, _VboIdSquare);
	glDeleteVertexArrays(1, &_VaoIdSquare);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(_VaoIdParall);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glDeleteBuffers(2, _VboIdParall);
	glDeleteVertexArrays(1, &_VaoIdParall);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}*/


// get
/*
GLuint shaders::getVaoIdSTri(){
	return _VaoIdSTri;
}

GLuint shaders::getVboIdSTri() {
	return _VboIdSTri[2];

}

GLuint shaders::getVaoIdSquare() {
	return _VaoIdSquare;

}

GLuint shaders::getVboIdSquare() {
	return _VboIdSquare[2];

}

GLuint shaders::getVaoIdParall() {
	return _VaoIdParall;

}

GLuint shaders::getVboIdParall() {
	return _VboIdParall[2];
}*/

GLuint shaders::getVertexShaderId() {
	return _VertexShaderId;
}

GLuint shaders::getFragmentShaderId() {
	return _FragmentShaderId;
}
GLuint shaders::getProgramId() {
	return _ProgramId;
}