#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include "GL/glew.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

class shaders {
	protected:
		bool _TexcoordsLoaded, _NormalsLoaded;
		GLuint _ProgramId;
		GLint _ModelMatrix_UId, _ViewMatrix_UId, _ProjectionMatrix_UId;
	
	public:	
		shaders();
		
		const std::string read(const std::string& filename);
		const GLuint checkCompilation(const GLuint shader_id, const std::string& filename);
		void checkLinkage(const GLuint program_id);
		const GLuint addShader(const GLuint program_id, 
			const GLenum shader_type, const std::string& filename);
		void createShaderProgram(const std::string& vs_file, const std::string& fs_file);
		void destroyShaderProgram();

		// get & set
		const bool getTexcoordsLoaded(); 
		const bool getNormalsLoaded();
		const void setTexcoordsLoaded(const bool texCoordsLoaded);
		const void setNormalsLoaded(const bool normalsLoaded);
};
