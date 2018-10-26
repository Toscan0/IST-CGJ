///////////////////////////////////////////////////////////////////////
//
// Assignment consists in the following:
//
// - Create the following changes to your scene:
//   - Make your TANs double-faced, so they can be seen from both sides.
//   - The new face of each TAN should share the same hue as the
//     original top face color but have a different level of saturation 
//     and brightness.
//
// - Add the following functionality:
//   - Create a View Matrix from (eye, center, up) parameters.
//   - Create an Orthographic Projection Matrix from (left-right, 
//     bottom-top, near-far) parameters.
//   - Create a Perspective Projection Matrix from (fovy, aspect,
//     nearZ, farZ) parameters.
//
// - Add the following dynamics to the application:
//   - Create a free 3D camera controlled by the mouse allowing to 
//     visualize the scene through all its angles.
//   - Change perspective from orthographic to perspective and back as
//     a response to pressing the key 'p'.
//
// (c) 2013-18 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include "GL/glew.h"
#include "GL/freeglut.h"

#include "src/matrix/matrix3x3/matrix3x3.h"
#include "src/matrix/matrixFactory/matrixFactory.h"
#include "src/vector/vector3/vector3.h"
#include "src/Vertex.h"
#include "src/shapes.h"
#define CAPTION "Hello Modern 3D World"

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

#define VERTICES 0
#define COLORS 1
#define M_PI 3.14159265358979323846  /* pi */

GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UboId, UniformId;
const GLuint UBO_BP = 0;

typedef GLfloat Matrix[16];
Matrix g_viewMatrix, g_orthMatrix, g_prespMatrix;
matrixFactory mf;
bool g_orth = true; // 1
const float g_a = 5.0f;
vector3 g_eye(5, 5, 5);
vector3 g_center(0, 0, 0);
vector3 g_up(0, 1, 0);

vector3 g_view = (g_center - g_eye).normalizado();

float g_cx;
float g_cy;
float g_cz;

float g_ex;
float g_ey;
float g_ez;

int old_x;
int old_y;

float g_rot = false;
GLuint VaoId, VboId[2];
GLuint VaoIdSTri, VboIdSTri[2], VaoIdSquare, VboIdSquare[2], VaoIdParall, VboIdParall[2];
GLint colorId;

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

const GLchar* VertexShader =
{
	"#version 330 core\n"

	"in vec4 in_Position;\n"
	"in vec4 in_Color;\n"
	"out vec4 ex_Color;\n"

	"uniform mat4 ModelMatrix;\n"

	"uniform SharedMatrices\n"
	"{\n"
	"	mat4 ViewMatrix;\n"
	"	mat4 ProjectionMatrix;\n"
	"};\n"

	"void main(void)\n"
	"{\n"
	"	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;\n"
	"	ex_Color = in_Color;\n"
	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 330 core\n"
	"uniform vec4 color;\n"
	"in vec4 ex_Color;\n"
	"out vec4 out_Color;\n"

	"void main(void)\n"
	"{\n"
	"	out_Color = color;\n"
	"}\n"
};

void createShaderProgram()
{
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, 0);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(ProgramId, COLORS, "in_Color");
	glLinkProgram(ProgramId);
	UniformId = glGetUniformLocation(ProgramId, "ModelMatrix");
	UboId = glGetUniformBlockIndex(ProgramId, "SharedMatrices");
	colorId = glGetUniformLocation(ProgramId, "color");
	glUniformBlockBinding(ProgramId, UboId, UBO_BP);

	glDetachShader(ProgramId, VertexShaderId);
	glDeleteShader(VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	glDeleteShader(FragmentShaderId);

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, 0);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(ProgramId, COLORS, "in_Color");

	glLinkProgram(ProgramId);

	UniformId = glGetUniformLocation(ProgramId, "ModelMatrix");
	UboId = glGetUniformBlockIndex(ProgramId, "SharedMatrices");
	colorId = glGetUniformLocation(ProgramId, "color");
	glUniformBlockBinding(ProgramId, UboId, UBO_BP);

	glDetachShader(ProgramId, VertexShaderId);
	glDeleteShader(VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	glDeleteShader(FragmentShaderId);

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

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
			//glBindBufferBase(GL_ELEMENT_ARRAY_BUFFER, UBO_BP, VboIdSTri[1]);
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
			//glBindBufferBase(GL_ELEMENT_ARRAY_BUFFER, UBO_BP, VboIdSquare[1]);
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
			//glBindBufferBase(GL_ELEMENT_ARRAY_BUFFER, UBO_BP, VboIdParall[1]);
		}
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(2, VboId);
		glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
		{
			glBufferData(GL_UNIFORM_BUFFER, sizeof(Matrix) * 2, 0, GL_STREAM_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, VboId[1]);
		}
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

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

const Matrix ModelMatrix = {
	1.0f,  0.0f,  0.0f,  0.0f,
	0.0f,  1.0f,  0.0f,  0.0f,
	0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f
}; // Column Major

void drawScene()
{
	glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix), g_viewMatrix);
	if (g_orth == 1) {
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix) , sizeof(Matrix), g_orthMatrix);

	}
	else {
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix), sizeof(Matrix), g_prespMatrix);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Draw square (head)
	glBindVertexArray(VaoIdSquare);
	glUseProgram(ProgramId);

	glProgramUniform4fv(ProgramId, colorId, 1, pink);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M1);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, (GLvoid*)0);
	
	// Draw triangle 
	glBindVertexArray(VaoIdSTri);
	glUseProgram(ProgramId);

	// Small triangle
	// foot
	glProgramUniform4fv(ProgramId, colorId, 1, yellow);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// hand
	glProgramUniform4fv(ProgramId, colorId, 1, black);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M4);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// Medium Triangle
	// arm
	glProgramUniform4fv(ProgramId, colorId, 1, red);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M5);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// Big triangle
	// ass
	glProgramUniform4fv(ProgramId, colorId, 1, purple);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);

	// body
	glProgramUniform4fv(ProgramId, colorId, 1, blue);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M7);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);


	// Draw Parall (legs)
/*	glBindVertexArray(VaoIdParall);
	glUseProgram(ProgramId);

	glProgramUniform4fv(ProgramId, colorId, 1, green);
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, M2);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, (GLvoid*)0);*/

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

void keyboard_up(unsigned char key, int x, int y) {

	switch (key) {
	case 'P':
	case 'p':
		g_orth = !g_orth;
		break;
	}


}

void keyboard_down(unsigned char key, int x, int y) {
	unsigned long delta;
	float pos;
	switch (key) {
	case 'A':
	case 'a':
		/*delta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		pos = 0 + (0 * delta) + ((g_a / 2) / pow(delta % 10, 2));*/
		g_ex -= 1.0f;
		g_cx -= 1.0f;
		break;

	case 'W':
	case 'w':

		g_ey += 1.0f;
		g_cy += 1.0f;
		break;

	case 'S':
	case 's':

		g_ey -= 1.0f;
		g_cy -= 1.0f;
		break;

	case 'D':
	case 'd':

		g_ex += 1.0f;
		g_cx += 1.0f;
		break;
	}

	vector3 newEye(g_ex, g_ey, g_ez);
	vector3 newCenter(g_cx, g_cy, g_cz);
	g_eye = newEye;
	g_center = newCenter;
	matrix4x4 vM = mf.viewMatrix(newEye, newCenter, g_up);
	matrix4x4 vMAux = vM.transposeM4x4();
	for (int i = 0; i < 16; ++i) {
		g_viewMatrix[i] = vMAux.data()[i];
	}
}

void mouseWheel(int wheel, int direction, int x, int y) {
	if (direction == -1) {
		g_ez -= 1.0f;
		g_cz -= 1.0f;
	}
	if (direction == 1) {
		g_ez += 1.0f;
		g_cz += 1.0f;
	}
	vector3 newEye(g_ex, g_ey, g_ez);
	vector3 newCenter(g_cx, g_cy, g_cz);
	g_eye = newEye;
	g_center = newCenter;
	matrix4x4 vM = mf.viewMatrix(newEye, newCenter, g_up);
	matrix4x4 vMAux = vM.transposeM4x4();
	for (int i = 0; i < 16; ++i) {
		g_viewMatrix[i] = vMAux.data()[i];
	}
}

void OnMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_rot = true;
		old_x = x;
		old_y = y;
	}
}


void OnMouseMove(int x, int y) {
	if (g_rot == true) {
		float x_aux = (x - old_x) * 0.005; // angle to rotate in x 
		float y_aux = (y - old_y) * 0.005; // angle to rotate in y

		old_x = (float)x;
		old_y = (float)y;


		g_view = (g_center - g_eye);
		g_view = g_view.normalizado();
		g_up = g_up.normalizado();

		matrix4x4 mRot = mf.rotationMatrix4x4(g_up, x_aux);
		matrix3x3 mRot_3x3(mRot._a, mRot._b, mRot._c, mRot._e, mRot._f, mRot._g, mRot._i, mRot._j, mRot._k);

		g_view = (mRot_3x3 * g_view);
		vector3 side = cross(g_view, g_up);
		mRot = mf.rotationMatrix4x4(side, y_aux);
		matrix3x3 mRot_3x31(mRot._a, mRot._b, mRot._c, mRot._e, mRot._f, mRot._g, mRot._i, mRot._j, mRot._k);
		g_view = (mRot_3x31 * g_view);

		g_up = (mRot_3x31 * g_up);

		vector3 c = (g_eye + g_view);

		matrix4x4 vM = mf.viewMatrix(g_eye, c, g_up);
		matrix4x4 vMAux = vM.transposeM4x4();
		for (int i = 0; i < 16; ++i) {
			g_viewMatrix[i] = vMAux.data()[i];
		}

		g_center = c;
		g_cx = g_center._a;
		g_cy = g_center._b;
		g_cz = g_center._c;
	}
}
/////////////////////////////////////////////////////////////////////// SETUP
void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

	glutKeyboardFunc(keyboard_down);
	glutKeyboardUpFunc(keyboard_up);

	glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);
	glutMouseWheelFunc(mouseWheel);

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
	GLenum result = glewInit();
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

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void myInit() {
	float Fovy = M_PI / 6;
	float aspect = 640.0f / 480.0f;
	float n = 1;
	float f = 10;
	float left = -2;
	float right = 2;
	float top = 2;
	float bottom = -2;


	g_cx = g_center._a;
	g_cy = g_center._b;
	g_cz = g_center._c;

	g_ex = g_eye._a;
	g_ey = g_eye._b;
	g_ez = g_eye._c;

	matrix4x4 vM = mf.viewMatrix(g_eye, g_center, g_up);
	matrix4x4 vMAux = vM.transposeM4x4();
	for (int i = 0; i < 16; ++i) {
		g_viewMatrix[i] = vMAux.data()[i];
	}


	matrix4x4 prespM = mf.prespMatrix(Fovy, aspect, 1, 10);
	matrix4x4 prespMAux = prespM.transposeM4x4();
	for (int i = 0; i < 16; ++i) {
		g_prespMatrix[i] = prespMAux.data()[i];
	}


	matrix4x4 orthM = mf.orthMatrix(left, right, top, bottom, n, f);
	matrix4x4 orthMMAux = orthM.transposeM4x4();
	for (int i = 0; i < 16; ++i) {
		g_orthMatrix[i] = orthMMAux.data()[i];
	}

	matrixFactory mf;

	vector3 vM2(1.05, 1.05, 1.05);
	matrix4x4 mM = mf.scalingMatrix4x4(vM2);
	/*vector3 vL(2, 2, 2);
	matrix4x4 mL = mf.scalingMatrix4x4(vL);*/

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
	matrix4x4 mR2 = mf.rotationMatrix4x4(v2, ((M_PI) / 2));
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


	/*std::cout << ViewMatrix1[0] << ViewMatrix1[1] << ViewMatrix1[2] << ViewMatrix1[3] << "\n";
	std::cout << ViewMatrix1[4] << ViewMatrix1[5] << ViewMatrix1[6] << ViewMatrix1[7] << "\n";
	std::cout << ViewMatrix1[8] << ViewMatrix1[9] << ViewMatrix1[10] << ViewMatrix1[11] << "\n";
	std::cout << ViewMatrix1[12] << ViewMatrix1[13] << ViewMatrix1[14] << ViewMatrix1[15] << "\n";*/
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
/*

bool testViewMatrix() {
	matrixFactory mf;
	vector3 eye(5, 5, 5);
	vector3 center(0, 0, 0);
	vector3 up(0, 1, 0);
	matrix4x4 vM = mf.viewMatrix(eye, center, up);
	matrix4x4 vMtest(0.7, 0, -0.7, 0, -0.41, 0.82, -0.41, 0, 0.58, 0.58, 0.58, -8.7, 0, 0, 0, 1);
	bool x = vM == vMtest;
	return x;
}//	std::cout << testViewMatrix() << std::endl;

bool testPrespMatrix() {
	matrixFactory mf;
	float Fovy = M_PI / 6;
	float aspect = 640.0f / 480.0f;
	float n = 1;
	float f = 10;
	matrix4x4 prespM = mf.prespMatrix(Fovy, aspect, n, f);
	matrix4x4 prespMtest(2.79f, 0.00f, 0.00f, 0.00f,
		0.00f, 3.73f, 0.00f, 0.00f,
		0.00f, 0.00f, -1.22f, -2.22f,
		0.00f, 0.00f, -1.00f, 0.00f);
	prespM.matrixPrint();
	bool x = prespM == prespMtest;

	return x;
}

bool testOrthMatrix() {
	matrixFactory mf;
	float left = -2;
	float right = 2;
	float top = -2;
	float bottom = 2;
	float n = 1;
	float f = 10;
	matrix4x4 orthM = mf.orthMatrix(left, right, top, bottom, n, f);
	matrix4x4 orthMtest(0.50, 0, 0, 0,
						 0, 0.50, 0, 0,
						 0, 0, -0.22, -1.22,
						 0, 0, 0, 1);
	bool x = orthM == orthMtest;
	orthM.matrixPrint();
	return x;
}

*/