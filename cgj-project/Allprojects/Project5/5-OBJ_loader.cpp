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
mesh parallelogramMesh;
mesh tableMesh;

//shader myShader;
shader cubeShader;
shader triangleShader;
shader parallelogramShader;
shader tableShader;

// SceneGraph
int g_x = 0; // value to translate the scene graph
sceneGraph sG;

// SceneNode
sceneNode *rootNode;
//sceneNode *STriNode, *MTriNode, *LTriNode, *parallelogramNode;
sceneNode *cTangramNode, *cubeNode; // closed tangram and his pieces
sceneNode *oTangramNode, *LTriNode, *parallelogramNode; // open tangram and his pieces
sceneNode *tableNode;

// Animation
//closed tangram starts in the middle of the table
// and change with open tangram (is in the left side of the table)
bool g_origin = true;
/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects()
{
	cubeMesh.createBufferObjects();
	triangleMesh.createBufferObjects();
	parallelogramMesh.createBufferObjects();

	tableMesh.createBufferObjects();
}

void destroyBufferObjects()
{
	cubeMesh.createBufferObjects();
	triangleMesh.createBufferObjects();
	parallelogramMesh.createBufferObjects();
	tableMesh.destroyBufferObjects();
}

/////////////////////////////////////////////////////////////////////// SCENE

void drawScene()
{
	sG.draw();
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	cubeShader.destroyShaderProgram();
	triangleShader.destroyShaderProgram();
	parallelogramShader.destroyShaderProgram();
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
		case 'L':
		case 'l':
			if (g_origin == true) {
				vector3 vT1 = learp(vector3(0, 0, 0), vector3(-1.5, 0, 0), 1);
				cTangramNode->setModelMatrix(mf.translationMatrix4x4(vT1));
				vector3 vT2 = learp(vector3(-1.5, 0, 0), vector3(0, 0, 0), 1);
				//oTangramNode->setModelMatrix(mf.translationMatrix4x4(vT2));
				
				vector4 axis = { 0.0f, 0.0f, 1.0f, 1.0f };
				qtrn q0 = qAux.qFromAngleAxis(0.0f, axis);
				qtrn q1 = qAux.qFromAngleAxis(90.0f, axis);
				qtrn qSlerp0 = qAux.qSlerp(q0, q1, 1.0f);
				matrix4x4 mAux;
				matrix4x4 mR = qGLMatrix(qSlerp0, mAux);
				oTangramNode->setModelMatrix(mR * mf.translationMatrix4x4(vT2));

				g_origin = false;
			}
			else{
				vector3 vT1 = learp(vector3(0, 0, 0), vector3(-1.5, 0, 0), 1);
				oTangramNode->setModelMatrix(mf.translationMatrix4x4(vT1));
				vector3 vT2 = learp(vector3(-1.5, 0, 0), vector3(0, 0, 0), 1);
				cTangramNode->setModelMatrix(mf.translationMatrix4x4(vT2));
				g_origin = true;
			}
			break;
	}
	//tableNode->setModelMatrix(mf.translationMatrix4x4(vector3(g_x, 0, 0)) * tableNode->getModelMatrix());
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
	mainCamera.setEye(eye);
	mainCamera.setCenter(center);
	mainCamera.setUp(up);

	// View Matrix
	mainCamera.makeViewMatrix(mainCamera.getEye(), mainCamera.getCenter(), mainCamera.getUp());
	// projection Matrix Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
	mainCamera.makePrespMatrix((M_PI / 6), (640.0f / 480.0f), 1, 10);
	
	// Mesh load
	//myMesh.createMesh(std::string("../../assets/models/cube.obj"), myShader); // cube
	//myMesh.createMesh(std::string("../../assets/models/duck.obj"), myShader); // duck
	// tangram
	cubeMesh.createMesh(std::string("../../assets/models/tangram/square.obj")); // cube
	triangleMesh.createMesh(std::string("../../assets/models/tangram/triangle.obj")); // triangle
	parallelogramMesh.createMesh(std::string("../../assets/models/tangram/parallelogram.obj")); // parallelogram
	//table
	tableMesh.createMesh(std::string("../../assets/models/table/table.obj")); // table
	
	// Shaders load
	cubeShader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/tangram_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/tangram_fs.glsl"),
		cubeMesh.getTexcoordsLoaded(),
		cubeMesh.getNormalsLoaded());
	triangleShader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/tangram_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/tangram_fs.glsl"),
		triangleMesh.getTexcoordsLoaded(),
		triangleMesh.getNormalsLoaded());
	parallelogramShader.createShaderProgram(
		std::string("../../assets/shaders/tangramShader/tangram_vs.glsl"),
		std::string("../../assets/shaders/tangramShader/tangram_fs.glsl"),
		parallelogramMesh.getTexcoordsLoaded(),
		parallelogramMesh.getNormalsLoaded());
	tableShader.createShaderProgram(
		std::string("../../assets/shaders/tableShader/table_vs.glsl"),
		std::string("../../assets/shaders/tableShader/table_fs.glsl"),
		tableMesh.getTexcoordsLoaded(),
		tableMesh.getNormalsLoaded());

	createBufferObjects();
}


void createScene() {
	/*							Scene Graph
	*					root <----|----> camera 
	*						|				|- viewMatrix
	*			 		table				|- prespMatrix
	*						|
	*	closed tangram <----|----> open tangram	
	*		 |- cube					|- large triangle
	*									|- parallelogram
	* (because of low time, i didn't implemente the tangram and the object,
	* the cube represent the closed tangram, and large triangle and parallelogram
	* represents my figure. I used rotation and scalles in the large triangle and parallelogram 
	* to represent the work that is missing)
	*
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
	
	cTangramNode = new sceneNode(); // empty object
	cTangramNode->setName("closed tangram");
	cTangramNode->setModelMatrix(mf.identityMatrix4x4());
	cTangramNode->setModelMatrixAux(mf.identityMatrix4x4());
	tableNode->addNode(cTangramNode);

	cubeNode = new sceneNode();
	cubeNode->setName("cube");
	cubeNode->setModelMatrix(mf.identityMatrix4x4());
	cubeNode->setModelMatrixAux(mf.identityMatrix4x4());
	cubeNode->setMesh(&cubeMesh);
	cubeNode->setShader(&cubeShader);
	cTangramNode->addNode(cubeNode);

	oTangramNode = new sceneNode(); // empty object
	oTangramNode->setName("open tangram");
	oTangramNode->setModelMatrix(
		mf.translationMatrix4x4(vector3(-1.5, 0, 0)) * mf.identityMatrix4x4()
	);
	oTangramNode->setModelMatrixAux(
		mf.translationMatrix4x4(vector3(-1.5, 0, 0)) * mf.identityMatrix4x4()
	);
	tableNode->addNode(oTangramNode);

	LTriNode = new sceneNode();
	LTriNode->setName("large triangle");
	LTriNode->setModelMatrix(
		mf.rotationMatrix4x4(vector3(0, 1, 0), -(M_PI / 2)) * mL
	);
	LTriNode->setModelMatrixAux(
		mf.rotationMatrix4x4(vector3(0, 1, 0), -(M_PI / 2)) * mL
	);
	LTriNode->setMesh(&triangleMesh);
	LTriNode->setShader(&triangleShader);
	oTangramNode->addNode(LTriNode);

	parallelogramNode = new sceneNode();
	parallelogramNode->setName("parallelogram");
	parallelogramNode->setModelMatrix(mf.identityMatrix4x4());
	parallelogramNode->setModelMatrixAux(mf.identityMatrix4x4());
	parallelogramNode->setMesh(&parallelogramMesh);
	parallelogramNode->setShader(&parallelogramShader);
	oTangramNode->addNode(parallelogramNode);

	sG.setRoot(rootNode);
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCallbacks();

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