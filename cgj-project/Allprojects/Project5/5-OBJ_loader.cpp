#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "src/mesh/mesh.h"
#include "src/shader/shader.h"
#include "src/error/error.h"
#include "src/camera/camera.h"
#include "src/vector/vector3/vector3.h"
#include "src/vector/vector4/vector4.h"
#include "src/matrix/matrix3x3/matrix3x3.h"
#include "src/matrix/matrix4x4/matrix4x4.h"
#include "src/qtrn/qtrn.h"
#include "src/scene/sceneGraph.h"
#include "src/scene/sceneNode.h"

#include "jsoncons/json.hpp"
// For convenience
using jsoncons::json;

#define CAPTION "Loading World"
#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2
#define DEGTORAD 0.0174532925
#define M_PI 3.14159265358979323846

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;
int g_oldX = 0; // last coord x of mouse in window
int g_oldY = 0;	// last coord y of mouse in window

vector3 eye(0.0f, 0.0f, 5.0f);
vector3 center(0.0f, 0.0f, 0.0f);
vector3 up(0.0f, 1.0f, 0.0f);

//Quarterion rotation
qtrn qAux;
bool g_rot = false;
vector4 XX_4(1, 0, 0, 1);
vector4 YY_4(0, 1, 0, 1);
qtrn q = { 1.0f, 0.0f, 0.0f, 0.0f };

camera mainCamera;
matrixFactory mf;

//mesh myMesh;
mesh cubeMesh;
mesh triangleMesh;
mesh parallMesh;
mesh tableMesh;

//shader myShader;
shader cubeShader;
shader sTri1Shader, sTri2Shader, mTriShader, lTri1Shader, lTri2Shader;
shader parallShader;
shader tableShader;

// SceneGraph
int g_x = 0; // value to translate the scene graph
sceneGraph sG;

// SceneNode
sceneNode *rootNode;
sceneNode *tableNode;
sceneNode *tangramNode, *cubeNode, *sTri1Node, *sTri2Node, *lTri1Node, *lTri2Node, *mTriNode, *parallNode; // tangram and his pieces

//stencil buffer
unsigned char stencilData[8];
/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects()
{
	cubeMesh.createBufferObjects();
	triangleMesh.createBufferObjects();
	parallMesh.createBufferObjects();

	tableMesh.createBufferObjects();
}

void destroyBufferObjects()
{
	cubeMesh.createBufferObjects();
	triangleMesh.createBufferObjects();
	parallMesh.createBufferObjects();
	tableMesh.destroyBufferObjects();
}

/////////////////////////////////////////////////////////////////////// SCENE


void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	sG.draw();
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	cubeShader.destroyShaderProgram();
	sTri1Shader.destroyShaderProgram();
	sTri2Shader.destroyShaderProgram();
	mTriShader.destroyShaderProgram();
	lTri2Shader.destroyShaderProgram();
	lTri2Shader.destroyShaderProgram();
	parallShader.destroyShaderProgram();
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
		case 'A':
		case 'a':
			g_x--;
			tableNode->setModelMatrix(mf.translationMatrix4x4(vector3(g_x, 0, 0)) * mf.identityMatrix4x4());
			break;
		case 'D':
		case 'd':
			g_x++;
			tableNode->setModelMatrix(mf.translationMatrix4x4(vector3(g_x, 0, 0)) * mf.identityMatrix4x4());
			break;
	}
}

void mouseWheel(int wheel, int direction, int x, int y) {
	if (direction == -1) {
		vector3 newEye(mainCamera.getEye()._a, mainCamera.getEye()._b, mainCamera.getEye()._c - 1);
		mainCamera.setEye(newEye);
		mainCamera.makeViewMatrix(newEye, mainCamera.getCenter(), mainCamera.getUp());
	}
	if (direction == 1) {
		vector3 newEye(mainCamera.getEye()._a, mainCamera.getEye()._b, mainCamera.getEye()._c + 1);
		mainCamera.setEye(newEye);
		mainCamera.makeViewMatrix(newEye, mainCamera.getCenter(), mainCamera.getUp());
	}


}

void OnMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_rot = true;
		g_oldX = x;
		g_oldY = y;
	}
	else {
		g_rot = false;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		GLuint index;
		glReadPixels(x, WinY - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		std::cout << "index: " << index << "\n";
		
		GLfloat red;
		GLfloat green;
		GLfloat blue;
		glReadPixels(x, WinY - y - 1, 1, 1, GL_RED, GL_FLOAT, &red);
		glReadPixels(x, WinY - y - 1, 1, 1, GL_GREEN, GL_FLOAT, &green);
		glReadPixels(x, WinY - y - 1, 1, 1, GL_BLUE, GL_FLOAT, &blue);
		std::cout << "color(RGB): " << "(" << red << ", " << green << ", " << blue << ")" << "\n";
	}
}


void OnMouseMove(int x, int y) {
	if (g_rot == true) { 	// Gimbal lock false
		float tetaX = (x - g_oldX); // angle to rotate in x (Deg)
		float tetaY = (y - g_oldY); // angle to rotate in y (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;

		//Recive the angle in deg
		q = (qAux.qFromAngleAxis(tetaX, YY_4) * q);
		q = (qAux.qFromAngleAxis(tetaY, XX_4) * q);

		matrix4x4 mAux;
		matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rotação devolve em row major

		vector3 vT(0, 0, -(mainCamera.getEye()._c));
		matrix4x4 T = mf.translationMatrix4x4(vT); // matrix translação 

		matrix4x4 vM = T * mR; // view matrix
		matrix4x4 vMT = vM.transposeM4x4(); // view matrix transposta -> column major
		mainCamera.setViewMatrix(vMT);
	}
	else {
		
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
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
	mainCamera.setEye(eye);
	mainCamera.setCenter(center);
	mainCamera.setUp(up);

	// View Matrix
	mainCamera.makeViewMatrix(mainCamera.getEye(), mainCamera.getCenter(), mainCamera.getUp());
	// projection Matrix Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
	mainCamera.makePrespMatrix((M_PI / 6), (640.0f / 480.0f), 1, 10);

	// Mesh load
	// tangram
	cubeMesh.createMesh(std::string("../../assets/models/tangram/square.obj")); // cube
	triangleMesh.createMesh(std::string("../../assets/models/tangram/triangle.obj")); // triangle
	parallMesh.createMesh(std::string("../../assets/models/tangram/parallelogram.obj")); // parallelogram
	//table
	tableMesh.createMesh(std::string("../../assets/models/table/table.obj")); // table

	// Shaders load
	cubeShader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/cube/cube_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/cube/cube_fs.glsl"),
		cubeMesh.getTexcoordsLoaded(),
		cubeMesh.getNormalsLoaded());
	sTri1Shader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/sTri1/sTri1_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/sTri1/sTri1_fs.glsl"),
		triangleMesh.getTexcoordsLoaded(),
		triangleMesh.getNormalsLoaded());
	sTri2Shader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/sTri2/sTri2_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/sTri2/sTri2_fs.glsl"),
		triangleMesh.getTexcoordsLoaded(),
		triangleMesh.getNormalsLoaded());
	mTriShader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/mTri/mTri_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/mTri/mTri_fs.glsl"),
		triangleMesh.getTexcoordsLoaded(),
		triangleMesh.getNormalsLoaded());
	lTri1Shader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/lTri1/lTri1_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/lTri1/lTri1_fs.glsl"),
		triangleMesh.getTexcoordsLoaded(),
		triangleMesh.getNormalsLoaded());
	lTri2Shader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/lTri2/lTri2_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/lTri2/lTri2_fs.glsl"),
		triangleMesh.getTexcoordsLoaded(),
		triangleMesh.getNormalsLoaded());
	parallShader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/parall/parall_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/parall/parall_fs.glsl"),
		parallMesh.getTexcoordsLoaded(),
		parallMesh.getNormalsLoaded());
	tableShader.createShaderProgram(
		std::string("../../assets/shaders/tableShader/table_vs.glsl"),
		std::string("../../assets/shaders/tableShader/table_fs.glsl"),
		tableMesh.getTexcoordsLoaded(),
		tableMesh.getNormalsLoaded());

	createBufferObjects();
}


void createScene() {
	/*						Scene Graph
	*					root <----|----> camera
	*						|				|- viewMatrix
	*			 		table				|- prespMatrix
	*						|
	*	closed tangram <----|
	*		 |- cube
	*		 |- small triangle 1
	*		 |- small triangle 2
	*		 |- medium triangle
	*		 |- big triangle 1
	*		 |- big triangle 2
	*		 |- parallelogram
	*
	* For transformation the order is :  T * R * S
	*/

	vector3 vM(1.5f, 1.0f, 1.5f);
	matrix4x4 mM = mf.scalingMatrix4x4(vM); // smal to medium
	vector3 vL(2.0f, 1.0f, 2.0f);
	matrix4x4 mL = mf.scalingMatrix4x4(vL); // smal to large

	sG.setCamera(&mainCamera);

	rootNode = new sceneNode(); //root node (empty object)
	rootNode->setName("root");
	rootNode->setModelMatrix(mf.identityMatrix4x4());
	rootNode->setModelMatrixAux(mf.identityMatrix4x4());

	tableNode = new sceneNode();
	tableNode->setName("table"); 
	tableNode->setModelMatrix(mf.identityMatrix4x4());
	tableNode->setModelMatrixAux(mf.identityMatrix4x4());
	tableNode->setMesh(&tableMesh);
	tableNode->setShader(&tableShader);
	rootNode->addNode(tableNode);

	tangramNode = new sceneNode(); // empty object
	tangramNode->setName("tangram");
	tangramNode->setModelMatrix(mf.identityMatrix4x4());
	tangramNode->setModelMatrixAux(mf.identityMatrix4x4());
	tableNode->addNode(tangramNode);

	cubeNode = new sceneNode();
	cubeNode->setName("cube");
	cubeNode->setModelMatrix(mf.translationMatrix4x4(vector3(0.2f, 0.0f, 0.0f)) * mf.identityMatrix4x4());
	cubeNode->setModelMatrixAux(mf.translationMatrix4x4(vector3(0.2f, 0.0f, 0.0f)) * mf.identityMatrix4x4());
	cubeNode->setMesh(&cubeMesh);
	cubeNode->setShader(&cubeShader);
	tangramNode->addNode(cubeNode);

	sTri1Node = new sceneNode();
	sTri1Node->setName("small triangle 1");
	sTri1Node->setModelMatrix(mf.translationMatrix4x4(vector3(-0.2f, 0.0f, 0.2f)) * mf.identityMatrix4x4());
	sTri1Node->setModelMatrixAux(mf.translationMatrix4x4(vector3(-0.2f, 0.0f, 0.2f)) * mf.identityMatrix4x4());
	sTri1Node->setMesh(&triangleMesh);
	sTri1Node->setShader(&sTri1Shader);
	tangramNode->addNode(sTri1Node);

	sTri2Node = new sceneNode();
	sTri2Node->setName("small triangle 2");
	sTri2Node->setModelMatrix(
		mf.translationMatrix4x4(vector3(0.4f, 0.0f, -0.0f)) * 
		mf.rotationMatrix4x4(vector3(0, 1, 0), (M_PI/2)) * 
		mf.identityMatrix4x4()
	);
	sTri2Node->setModelMatrixAux(
		mf.translationMatrix4x4(vector3(0.4f, 0.0f, -0.0f)) *
		mf.rotationMatrix4x4(vector3(0, 1, 0), (M_PI / 2)) *
		mf.identityMatrix4x4()
	);
	sTri2Node->setMesh(&triangleMesh);
	sTri2Node->setShader(&sTri2Shader);
	tangramNode->addNode(sTri2Node);

	mTriNode = new sceneNode();
	mTriNode->setName("medium triangle");
	mTriNode->setModelMatrix(
		mf.translationMatrix4x4(vector3(0.40, 0.0f, 0.0f)) *
		mf.rotationMatrix4x4(vector3(0, 1, 0), -(3 * M_PI / 4)) *
		mf.scalingMatrix4x4(vector3(1.4f, 1.0f, 1.4f))
	);
	mTriNode->setModelMatrixAux(
		mf.translationMatrix4x4(vector3(0.40, 0.0f, 0.0f)) *
		mf.rotationMatrix4x4(vector3(0, 1, 0), -(3 * M_PI / 4)) *
		mf.scalingMatrix4x4(vector3(1.4f, 1.0f, 1.4f))
	);
	mTriNode->setMesh(&triangleMesh);
	mTriNode->setShader(&mTriShader);
	tangramNode->addNode(mTriNode);

	lTri1Node = new sceneNode();
	lTri1Node->setName("large triangle 1");
	lTri1Node->setModelMatrix(
		mf.translationMatrix4x4(vector3(0.4f, 0.0f, -0.4f)) *
		mf.rotationMatrix4x4(vector3(0, 1, 0), M_PI) *
		mf.scalingMatrix4x4(vector3(2.0f, 1.0f, 2.0f))
	);
	lTri1Node->setModelMatrixAux(
		mf.translationMatrix4x4(vector3(0.4f, 0.0f, -0.4f)) *
		mf.rotationMatrix4x4(vector3(0, 1, 0), M_PI) *
		mf.scalingMatrix4x4(vector3(2.0f, 1.0f, 2.0f))
	);
	lTri1Node->setMesh(&triangleMesh);
	lTri1Node->setShader(&lTri1Shader);
	tangramNode->addNode(lTri1Node);

	lTri2Node = new sceneNode();
	lTri2Node->setName("large triangle 2");
	lTri2Node->setModelMatrix(
		mf.translationMatrix4x4(vector3(-0.4f, 0.0f, -0.4f)) *
		mf.rotationMatrix4x4(vector3(0, 1, 0), -(M_PI / 2)) *
		mf.scalingMatrix4x4(vector3(2.0f, 1.0f, 2.0f))
	);
	lTri2Node->setModelMatrixAux(
		mf.translationMatrix4x4(vector3(-0.4f, 0.0f, -0.4f)) *
		mf.rotationMatrix4x4(vector3(0, 1, 0), -(M_PI / 2)) *
		mf.scalingMatrix4x4(vector3(2.0f, 1.0f, 2.0f))
	);
	lTri2Node->setMesh(&triangleMesh);
	lTri2Node->setShader(&lTri2Shader);
	tangramNode->addNode(lTri2Node);

	parallNode = new sceneNode();
	parallNode->setName("parallelogram");
	parallNode->setModelMatrix(mf.translationMatrix4x4(vector3(-0.4f, 0.0f, 0.4f)));
	parallNode->setModelMatrixAux(mf.translationMatrix4x4(vector3(-0.4f, 0.0f, 0.4f)));
	parallNode->setMesh(&parallMesh);
	parallNode->setShader(&parallShader);
	tangramNode->addNode(parallNode);
	
	sG.setRoot(rootNode);
}

void readJSONFile() {
	// Read from stream
	std::ifstream is("../../assets/json/defaultLoad.json");
	json j = json::parse(is);

	// Pretty print
	std::cout << "(1)\n" << pretty_print(j) << "\n\n";

	if (j.contains("tangram"))
	{
		std::string price = j["tangram"]["small_triangle_1"]["name"].as<std::string>();
		std::cout << price;
	}
	else
	{
		std::cout << "n/a";
	}

	j["tangram"]["small_triangle_1"]["name"] = "lllllll";

	// Write to stream
	std::ofstream os("../../assets/json/savedScene.json");
	os << j;
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCallbacks();
	
	readJSONFile();

	myInit();
	createScene();
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////