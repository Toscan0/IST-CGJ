///////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a triangle in Modern OpenGL.
// A "hello world" of Modern OpenGL.
//
// Assignment : Create Shader Abstraction 
//					(e.g. check compilation/linkage for errors, read from file) 
//			  : Manage Multiple Drawable Entities (using your vertex and matrix classes)
//              Draw a set of 7 TANs (i.e. TANGRAM shapes) of different colors: 
//              (1) 3 different TAN geometric shapes at the origin:
//					- right triangle
//					- square
//					- parallelogram
//              (2) 7 TANs of different colors put together to form a shape of your choice:
//					- 2 big right triangles
//					- 1 medium right triangle
//					- 2 small right triangles
//					- 1 square
//					- 1 parallelogram;
//
// (c) 2013-18 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>


#include "GL/glew.h"
#include "GL/freeglut.h"

#include "src/matrix/matrix4x4/matrix4x4.h"
#include "src/matrix/matrixFactory/matrixFactory.h"

#include "src/shapes.h"
#include "src/shaders/shaders.h"

#define CAPTION "Hello Modern 2D World"

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

#define VERTICES 0
#define COLORS 1
#define M_PI 3.14159265358979323846  /* pi */

GLuint VaoIdSTri, VboIdSTri[2], VaoIdSquare, VboIdSquare[2], VaoIdParall, VboIdParall[2];
GLint UniformId, colorId;
shaders s;

/////////////////////////////////////////////////////////////////////// ERRORS

static std::string errorType(GLenum type)
{
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:				return "error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	return "deprecated behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	return "undefined behavior";
	case GL_DEBUG_TYPE_PORTABILITY:			return "portability issue";
	case GL_DEBUG_TYPE_PERFORMANCE:			return "performance issue";
	case GL_DEBUG_TYPE_MARKER:				return "stream annotation";
	case GL_DEBUG_TYPE_OTHER_ARB:			return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static std::string errorSource(GLenum source)
{
	switch (source) {
	case GL_DEBUG_SOURCE_API:				return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "window system";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "shader compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:		return "third party";
	case GL_DEBUG_SOURCE_APPLICATION:		return "application";
	case GL_DEBUG_SOURCE_OTHER:				return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static std::string errorSeverity(GLenum severity)
{
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:			return "high";
	case GL_DEBUG_SEVERITY_MEDIUM:			return "medium";
	case GL_DEBUG_SEVERITY_LOW:				return "low";
	case GL_DEBUG_SEVERITY_NOTIFICATION:	return "notification";
	default:								exit(EXIT_FAILURE);
	}
}

static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar *message, const void *userParam)
{
	std::cerr << "ERROR:" << std::endl;
	std::cerr << "  source:     " << errorSource(source) << std::endl;
	std::cerr << "  type:       " << errorType(type) << std::endl;
	std::cerr << "  severity:   " << errorSeverity(severity) << std::endl;
	std::cerr << "  debug call: " << std::endl << message << std::endl << std::endl;
}

void setupErrors()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(error, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
	// params: source, type, severity, count, ids, enabled
}

static bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

static void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////// SHADERs
GLuint getId(GLuint programId, const char* name) {
	GLuint id = glGetUniformLocation(programId, name);
	return id;
}

void createShaderProgram()
{	
	s.createShader("shaders_files/vertexSh.glsl", "shaders_files/fragmentSh.glsl");

	UniformId = getId(s.getProgramId(), "Matrix");
	colorId = getId(s.getProgramId(), "color");
}

void destroyShaderProgram()
{
	s.destroyShader();
}

void createAux(GLuint VaoId, GLuint VboId, Vertex vert) {
	/*glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(2, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesSTri), VerticesSTri, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(VerticesSTri[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesSTri), IndicesSTri, GL_STATIC_DRAW);
		}
	}*/
}

void createBufferObjects()
{
	/// Triangle
	glGenVertexArrays(1, &VaoIdSTri);
	glBindVertexArray(VaoIdSTri);
	{
		glGenBuffers(2, VboIdSTri);

		glBindBuffer(GL_ARRAY_BUFFER, VboIdSTri[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesSTri), VerticesSTri, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(VerticesSTri[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboIdSTri[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesSTri), IndicesSTri, GL_STATIC_DRAW);
		}
	}

	// Square
	glGenVertexArrays(1, &VaoIdSquare);
	glBindVertexArray(VaoIdSquare);
	{
		glGenBuffers(2, VboIdSquare);

		glBindBuffer(GL_ARRAY_BUFFER, VboIdSquare[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesSquare), VerticesSquare, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(VerticesSquare[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboIdSquare[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesSquare), IndicesSquare, GL_STATIC_DRAW);
		}
	}

	// Parall
	glGenVertexArrays(1, &VaoIdParall);
	glBindVertexArray(VaoIdParall);
	{
		glGenBuffers(2, VboIdParall);

		glBindBuffer(GL_ARRAY_BUFFER, VboIdParall[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesParall), VerticesParall, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(VerticesParall[0].XYZW));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboIdParall[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesParall), IndicesParall, GL_STATIC_DRAW);
		}
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyAux(GLuint VaoId, GLuint VboId) {
	glBindVertexArray(VaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glDeleteBuffers(2, &VboId);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void destroyBufferObjects()
{
	
	destroyAux(VaoIdSTri, *VboIdSTri);
	destroyAux(VaoIdSquare, *VboIdSquare);
	destroyAux(VaoIdParall, *VboIdParall);

	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE
void drawAux(GLuint VaoId, GLuint ProgramId, GLint UniformId, GLint colorShader, float* color) {
	float x[4];
	for (int i = 0; i < 4; ++i) {
		x[i] = color[i];
	}
	// Draw square (head)
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	glProgramUniform4fv(ProgramId, colorShader, 1, x);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
}

void drawScene()
{	
	// Draw square (head)
	glBindVertexArray(VaoIdParall);
	glUseProgram(s.getProgramId());

	glProgramUniform4fv(s.getProgramId(), colorId, 1, pink);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// Draw Parall (legs)
	glBindVertexArray(VaoIdParall);
	glUseProgram(s.getProgramId());

	glProgramUniform4fv(s.getProgramId(), colorId, 1, green);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// Draw triangle 
	glBindVertexArray(VaoIdSTri);
	glUseProgram(s.getProgramId());

	// Small triangle
	// foot
	glProgramUniform4fv(s.getProgramId(), colorId, 1, yellow);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M3);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	
	// hand
	glProgramUniform4fv(s.getProgramId(), colorId, 1, black);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M4);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	
	// Medium Triangle
	// arm
	glProgramUniform4fv(s.getProgramId(), colorId, 1, red);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M5);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// Big triangle
	// ass
	glProgramUniform4fv(s.getProgramId(), colorId, 1, purple);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M6);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// body
	glProgramUniform4fv(s.getProgramId(), colorId, 1, blue);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M7);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glUseProgram(0);
	glBindVertexArray(0);
	
	checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks() 
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	setupErrors();
}

void checkOpenGLInfo()
{
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL()
{
	checkOpenGLInfo();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void setupGLEW() 
{
	glewExperimental = GL_TRUE;
	GLenum result = glewInit() ; 
	if (result != GLEW_OK) { 
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	} 
	GLenum err_code = glGetError();
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextFlags(GLUT_DEBUG);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if(WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void myInit() {
	matrixFactory mf;

	vector3 vM(1.05, 1.05, 1.05);
	matrix4x4 mM = mf.scalingMatrix4x4(vM);
	/*vector3 vL(2, 2, 2);
	matrix4x4 mL = mf.scalingMatrix4x4(vL);
	mL.matrixPrint();*/
	// T * R * S
	matrix4x4 mi = mf.identityMatrix4x4();
	for (int i = 0; i < 16; ++i) {
		I[i] = mi.data()[i];
	}

	//Squad (head)
	vector3 v1(0, 0, 1);
	vector3 vT1(0.17, 0.08, 0);
	matrix4x4 mR1 = mf.rotationMatrix4x4(v1, (M_PI / 4));
	matrix4x4 mT1 = mf.translationMatrix4x4(vT1);
	matrix4x4 m1 = mT1 * mR1 * mi;
	for (int i = 0; i < 16; ++i) {
		M1[i] = m1.data()[i];
	}

	// Parallelogram (Legs)
	vector3 v2(1, 0, 1);
	vector3 vT2(-0.29, -0.49, 0);
	matrix4x4 mR2 = mf.rotationMatrix4x4(v2, ( (M_PI) / 2));
	matrix4x4 mT2 = mf.translationMatrix4x4(vT2);
	matrix4x4 m2 = mT2 * mR2* mi;
	for (int i = 0; i < 16; ++i) {
		M2[i] = m2.data()[i];
	}

	// Small triangle (foot)
	vector3 v3(0, 0, 1);
	vector3 vT3(-0.54, -0.49, 0);
	matrix4x4 mR3 = mf.rotationMatrix4x4(v3, M_PI);
	matrix4x4 mT3 = mf.translationMatrix4x4(vT3);
	matrix4x4 m3 = mT3 * mR3 * mi;
	for (int i = 0; i < 16; ++i) {
		M3[i] = m3.data()[i];
	}

	// Small triangle (hand)
	vector3 v4(0, 0, 1);
	vector3 vT4(-0.20, 0.075, 0);
	matrix4x4 mR4 = mf.rotationMatrix4x4(v4, (M_PI / 4));
	matrix4x4 mT4 = mf.translationMatrix4x4(vT4);
	matrix4x4 m4 = mT4 * mR4 * mi;
	for (int i = 0; i < 16; ++i) {
		M4[i] = m4.data()[i];
	}

	// Medium triangle (Arm)
	vector3 v5(0, 0, 1);
	vector3 vT5(-0.015, -0.1, 0);
	matrix4x4 mR5 = mf.rotationMatrix4x4(v5, (M_PI / 4));
	matrix4x4 mT5 = mf.translationMatrix4x4(vT5);
	matrix4x4 m5 = mT5 * mR5 * mM;
	for (int i = 0; i < 16; ++i) {
		M5[i] = m5.data()[i];
	}

	// Big triangle (ass)
	vector3 vT(0, -0.4, 0);
	matrix4x4 mT = mf.translationMatrix4x4(vT);
	matrix4x4 m6 = mT * mL;
	for (int i = 0; i < 16; ++i) {
		M6[i] = m6.data()[i];
	}

	// Big triangle (body)
	vector3 v7(0, 0, -1);
	vector3 vT7(0.17, -0.335, 0);
	matrix4x4 mT7 = mf.translationMatrix4x4(vT7);
	matrix4x4 mR7 = mf.rotationMatrix4x4(v7, (M_PI / (4)));
	matrix4x4 m7 = mT7 * mR7 * mL;
	for (int i = 0; i < 16; ++i) {
		M7[i] = m7.data()[i];
	}


	/*
	std::cout << M5[0] << M5[1] << M5[2] << M5[3] << "\n";
	std::cout << M5[4] << M5[5] << M5[6] << M5[7] << "\n";
	std::cout << M5[8] << M5[9] << M5[10] << M5[11] << "\n";
	std::cout << M5[12] << M5[13] << M5[14] << M5[15] << "\n";*/
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	
	myInit();

		
	setupCallbacks();
	createShaderProgram();
	createBufferObjects();
}

int main(int argc, char* argv[])
{	
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////