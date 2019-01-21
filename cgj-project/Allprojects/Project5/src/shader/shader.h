#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include "GL/glew.h"
#include "../error/error.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2
#define COLORS 3

class shader {
	protected:
		GLuint _ProgramId;
		std::vector<GLuint> _shaders;
		std::map <const GLchar*, GLint> _uniforms;

	public:	
		shader();
		
		const std::string read(const std::string& filename);
		const GLuint checkCompilation(const GLuint shader_id, const std::string& filename);
		void checkLinkage(const GLuint program_id);
		void addShader(const GLenum shader_type, const std::string& filename);
		void createShaderProgram(const std::string& vs_file, const std::string& fs_file, bool texcoordsLoaded, bool mormalsLoaded);
		void destroyShaderProgram();

		void Bind() const;
		void UnBind() const;

		// get & set
		const GLuint getProgramId();
		GLint getUniform(const GLchar* name);
};
