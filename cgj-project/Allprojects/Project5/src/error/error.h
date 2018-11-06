#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GL/glew.h"
#include "GL/freeglut.h"

static std::string errorType(GLenum type);
static std::string errorSource(GLenum source);
static std::string errorSeverity(GLenum severity);
static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar *message, const void *userParam);
void setupErrors();
static bool isOpenGLError();
void checkOpenGLError(std::string error);