#include "shader.h"

shader::shader() {}

const std::string shader::read(const std::string& filename)
{
	std::ifstream ifile(filename);
	std::string shader_string, line;
	while (std::getline(ifile, line)) {
		shader_string += line + "\n";
	}
	return shader_string;
}

const GLuint shader::checkCompilation(const GLuint shader_id, const std::string& filename)
{
	GLint compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetShaderInfoLog(shader_id, length, &length, log);
		std::cerr << "[" << filename << "] " << std::endl << log;
		delete log;
	}
	return compiled;
}

void shader::checkLinkage(const GLuint program_id) {
	GLint linked;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		GLint length;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetProgramInfoLog(program_id, length, &length, log);
		std::cerr << "[LINK] " << std::endl << log << std::endl;
		delete log;
	}
}

//const GLuint shader::addShader(const GLuint program_id, const GLenum shader_type, const std::string& filename)
void shader::addShader(const GLenum shader_type, const std::string& filename)
{
	//create shader
	const GLuint shaderId = glCreateShader(shader_type);
	const std::string scode = read(filename);
	const GLchar* code = scode.c_str();
	glShaderSource(shaderId, 1, &code, 0);

	// compile shader
	glCompileShader(shaderId);
	checkCompilation(shaderId, filename);

	_shaders.push_back(shaderId);
}

void shader::createShaderProgram(const std::string& vs_file, const std::string& fs_file, bool texcoordsLoaded, bool mormalsLoaded)
{
	addShader(GL_VERTEX_SHADER, vs_file);
	addShader(GL_FRAGMENT_SHADER, fs_file);

	_ProgramId = glCreateProgram();

	//GLuint VertexShaderId = addShader(_ProgramId, GL_VERTEX_SHADER, vs_file);
	//GLuint FragmentShaderId = addShader(_ProgramId, GL_FRAGMENT_SHADER, fs_file);
	for (int i = 0; i < _shaders.size(); i++) {
		glAttachShader(_ProgramId, _shaders[i]);
	}

	glBindAttribLocation(_ProgramId, VERTICES, "inPosition");
	if (texcoordsLoaded)
		glBindAttribLocation(_ProgramId, TEXCOORDS, "inTexcoord");
	if (mormalsLoaded)
		glBindAttribLocation(_ProgramId, NORMALS, "inNormal");
	// Color bynd
	glBindAttribLocation(_ProgramId, COLORS, "in_Color");

	glLinkProgram(_ProgramId);
	checkLinkage(_ProgramId);

	//glDetachShader(_ProgramId, VertexShaderId);
	//glDetachShader(_ProgramId, FragmentShaderId);
	//glDeleteShader(VertexShaderId);
	//glDeleteShader(FragmentShaderId);
	for (int i = 0; i < _shaders.size(); i++) {
		glDetachShader(_ProgramId, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}

	//_ModelMatrix_UId = glGetUniformLocation(_ProgramId, "ModelMatrix");
	//_ViewMatrix_UId = glGetUniformLocation(_ProgramId, "ViewMatrix");
	//_ProjectionMatrix_UId = glGetUniformLocation(_ProgramId, "ProjectionMatrix");

	_colorId = glGetUniformLocation(_ProgramId, "color");

	checkOpenGLError("ERROR: Could not create shaders.");
}

void shader::destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(_ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

GLint shader::getUniform(const GLchar * name)
{
	std::map <const GLchar*, GLint> ::iterator it = _uniforms.find(name);
	if (it != _uniforms.end())
		return it->second;
	GLint uniformID = glGetUniformLocation(_ProgramId, name);
	_uniforms.insert(std::pair <const GLchar*, GLint>(name, uniformID));
	return uniformID;
}

void shader::Bind() const {
	glUseProgram(_ProgramId);
}

void shader::UnBind() const {
	glUseProgram(0);
}

const GLuint shader::getProgramId() {
	return _ProgramId;
}

/*const GLint shader::getModelMatrix_UId() {
	return _ModelMatrix_UId;
}

const GLint shader::getViewMatrix_UId() {
	return _ViewMatrix_UId;
}

const GLint shader::getProjectionMatrix_UId() {
	return _ProjectionMatrix_UId;
}*/

const GLuint shader::getColorId() {
	return _colorId;
}
