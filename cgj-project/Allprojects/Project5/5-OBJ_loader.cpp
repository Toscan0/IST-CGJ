///////////////////////////////////////////////////////////////////////
//
//  Loading OBJ mesh from external file
//
//	Final individual assignment:
//	1.	Create classes: Scene, Camera and Mesh (that loads a mesh from
//		a Wavefront OBJ file to an indexed format) and build a small
//		scenegraph of your tangram scene (you may create more 
//		classes if needed).
//	2.	Create a ground object and couple the tangram figure to the
//		ground. Press keys to move the ground about: the tangram
//		figure must follow the ground.
//	3.	Animate between closed puzzle (initial square) and tangram
//		figure by pressing a key.
//	4.	Spherical camera interaction through mouse. It should be
//		possible to interact while animation is playing.
//
//	Team assignment:
//	Pick your team (2 elements from one same lab) for the team
//	assignment you will be working until the end of the semester,
//	and register it online.
//
// (c) 2013-18 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "src/mesh/mesh.h"
#include "src/shaders/shaders.h"
#include "src/error/error.h"
#include "src/camera/camera.h"
#include "src/vector/vector3/vector3.h"
#include "src/vector/vector4/vector4.h"
#include "src/matrix/matrix3x3/matrix3x3.h"
#include "src/matrix/matrix4x4/matrix4x4.h"
#include "src/qtrn/qtrn.h"

#define CAPTION "Loading World"
#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

GLuint VaoId;

mesh myMesh;
shaders myShader;

bool g_rot = true;
int g_oldX = 0;
int g_oldY = 0;
camera c;
matrixFactory mf;
bool g_gimbalLock = true;

vector3 XX(1, 0, 0);
vector3 YY(0, 1, 0);
vector4 XX_4(1, 0, 0, 1);
vector4 YY_4(0, 1, 0, 1);
//vector3 vT(0, 0, -5);
matrix4x4 Rx;
matrix4x4 Ry;
qtrn q = { 1.0f, 0.0f, 0.0f, 0.0f };

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects()
{
	GLuint VboVertices, VboTexcoords, VboNormals;

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(1, &VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
		std::cout << myMesh.getVertices().size()  << "  myMesh.getVertices().size()\n";
		std::cout << &myMesh.getVertices() << "  &myMesh.getVertices()\n";
		std::cout << &myMesh.getVertices()[0] << "  &myMesh.getVertices()[0]\n";
		glBufferData(GL_ARRAY_BUFFER, myMesh.getVertices().size() * sizeof(Vertex), &myMesh.getVertices()[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		if (myShader.getTexcoordsLoaded())
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, myMesh.getTexcoords().size() * sizeof(Texcoord), &myMesh.getTexcoords()[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
		}
		if (myShader.getNormalsLoaded())
		{
			glGenBuffers(1, &VboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
			glBufferData(GL_ARRAY_BUFFER, myMesh.getNormals().size() * sizeof(Normal), &myMesh.getNormals()[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboVertices);
	glDeleteBuffers(1, &VboTexcoords);
	glDeleteBuffers(1, &VboNormals);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects()
{
	glBindVertexArray(VaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(TEXCOORDS);
	glDisableVertexAttribArray(NORMALS);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE

typedef GLfloat Matrix[16];

const Matrix I = {
	1.0f,  0.0f,  0.0f,  0.0f,
	0.0f,  1.0f,  0.0f,  0.0f,
	0.0f,  0.0f,  1.0f,  0.0f,
	0.0f,  0.0f,  0.0f,  1.0f
};

const Matrix ModelMatrix = {
	1.0f,  0.0f,  0.0f,  0.0f,
	0.0f,  1.0f,  0.0f,  0.0f,
	0.0f,  0.0f,  1.0f,  0.0f,
	0.0f,  0.0f,  0.0f,  1.0f
}; // Column Major

// Eye(5,5,5) Center(0,0,0) Up(0,1,0)
const Matrix ViewMatrix1 = {
	0.70f, -0.41f,  0.58f,  0.00f,
	0.00f,  0.82f,  0.58f,  0.00f,
   -0.70f, -0.41f,  0.58f,  0.00f,
	0.00f,  0.00f, -8.70f,  1.00f
}; // Column Major

// Eye(-5,-5,-5) Center(0,0,0) Up(0,1,0)
const Matrix ViewMatrix2 = {
   -0.70f, -0.41f, -0.58f,  0.00f,
	0.00f,  0.82f, -0.58f,  0.00f,
	0.70f, -0.41f, -0.58f,  0.00f,
	0.00f,  0.00f, -8.70f,  1.00f
}; // Column Major

// Orthographic LeftRight(-2,2) TopBottom(-2,2) NearFar(1,10)
const Matrix ProjectionMatrix1 = {
	0.50f,  0.00f,  0.00f,  0.00f,
	0.00f,  0.50f,  0.00f,  0.00f,
	0.00f,  0.00f, -0.22f,  0.00f,
	0.00f,  0.00f, -1.22f,  1.00f
}; // Column Major

// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
const Matrix ProjectionMatrix2 = {
	2.79f,  0.00f,  0.00f,  0.00f,
	0.00f,  3.73f,  0.00f,  0.00f,
	0.00f,  0.00f, -1.22f, -1.00f,
	0.00f,  0.00f, -2.22f,  0.00f
}; // Column Major

void drawScene()
{
	glBindVertexArray(VaoId);
	glUseProgram(myShader.getProgramId());

	glUniformMatrix4fv(myShader.getModelMatrix_UId(), 1, GL_FALSE, ModelMatrix);
	matrix4x4 vM = c.getViewMatrix();
	Matrix viewMatrix;
	for (int i = 0; i < 16; ++i) {
		viewMatrix[i] = vM.data()[i];
	}
	glUniformMatrix4fv(myShader.getViewMatrix_UId(), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(myShader.getProjectionMatrix_UId(), 1, GL_FALSE, ProjectionMatrix2);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)myMesh.getVertices().size());

	glUseProgram(0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	myShader.destroyShaderProgram();
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

//////////////////////////////////////////////////////////////////////// Mouse/Key Eventes

void keyboard_down(unsigned char key, int x, int y) {
	switch (key) {
	case 'G':
	case 'g':
		g_gimbalLock = !g_gimbalLock;
		break;
	}
}

void mouseWheel(int wheel, int direction, int x, int y) {
	if (direction == -1) {
		vector3 newEye(c.getEye()._a, c.getEye()._b, c.getEye()._c - 1);
		c.setEye(newEye);
		c.makeViewMatrix(newEye, c.getCenter(), c.getUp());
	}
	if (direction == 1) {
		vector3 newEye(c.getEye()._a, c.getEye()._b, c.getEye()._c + 1);
		c.setEye(newEye);
		c.makeViewMatrix(newEye, c.getCenter(), c.getUp());
	}


}

void OnMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_rot = true;
		g_oldX = x;
		g_oldY = y;
	}
}


void OnMouseMove(int x, int y) {
	if (g_rot == true) {
		float tetaX = (x - g_oldX); // angle to rotate in x (Deg)
		float tetaY = (y - g_oldY); // angle to rotate in y (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;
		if (g_gimbalLock == true) {
			std::cout << "\n" << "GIMBAL LOCK ON" << "\n";

			Rx = mf.rotationMatrix4x4(YY, tetaX * 0.0174532925) * Rx;
			Ry = mf.rotationMatrix4x4(XX, tetaY * 0.0174532925) * Ry;
			matrix4x4 R = Ry * Rx;

			vector3 vT(0, 0, -(c.getEye()._c));
			matrix4x4 T = mf.translationMatrix4x4(vT);  // matrix transla��o

			matrix4x4 vM = T * R; // view matrix em row major
			matrix4x4 vMT = vM.transposeM4x4(); // view matrix transposta -> column major
			c.setViewMatrix(vMT);

		}
		else { // Gimbal lock false
			std::cout << "\n" << "GIMBAL LOCK OFF" << "\n";
			qtrn qAux;

			//Recive the angle in deg
			q = (qAux.qFromAngleAxis(tetaX, YY_4) * q);
			q = (qAux.qFromAngleAxis(tetaY, XX_4) * q);

			matrix4x4 mAux;
			matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rota��o devolve em row major

			vector3 vT(0, 0, -(c.getEye()._c));
			matrix4x4 T = mf.translationMatrix4x4(vT); // matrix transla��o 

			matrix4x4 vM = T * mR; // view matrix
			matrix4x4 vMT = vM.transposeM4x4(); // view matrix transposta -> column major
			c.setViewMatrix(vMT);
		}
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

	//Mine
	glutKeyboardFunc(keyboard_down);
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
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

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
	vector3 eye(0.0f, 0.0f, 5.0f);
	vector3 center(0.0f, 0.0f, 0.0f);
	vector3 up(0.0f, 1.0f, 0.0f);

	c.setEye(eye);
	c.setCenter(center);
	c.setUp(up);

	c.makeViewMatrix(c.getEye(), c.getCenter(), c.getUp());
	
	// gimbal lock rotation
	Rx = mf.identityMatrix4x4();
	Ry = mf.identityMatrix4x4();

	// Mesh load
	std::string objToLoad = std::string("../../assets/models/ex.obj");
	myMesh.createMesh(objToLoad, myShader);

	// Shaders load
	myShader.createShaderProgram(std::string("../../assets/shaders/cube_vs.glsl"),
		std::string("../../assets/shaders/cube_fs.glsl"));
	
	createBufferObjects();
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCallbacks();

	myInit();
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////