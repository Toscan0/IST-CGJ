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
#define DEFAULT_QTRN { 1.0f, 0.0f, 0.0f, 0.0f };
#define TRANSXX 0.1 //how much the piece translate, each time you press a key, in XX
#define TRANSZZ 0.1 //how much the piece translate, each time you press a key, in ZZ

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

vector4 XX_4(1, 0, 0, 1);
vector4 YY_4(0, 1, 0, 1);
matrixFactory mf;
qtrn qAux;

// mouse click
int g_oldX = 0; // last coord x of mouse in window
int g_oldY = 0;	// last coord y of mouse in window

//Camera
camera mainCamera;
vector3 eye(0.0f, 0.0f, 5.0f);
vector3 center(0.0f, 0.0f, 0.0f);
vector3 up(0.0f, 1.0f, 0.0f);

//mesh myMesh;
mesh cubeMesh;
mesh triangleMesh;
mesh parallMesh;
mesh tableMesh;

// Shader
shader cubeShader;
shader sTri1Shader, sTri2Shader, mTriShader, lTri1Shader, lTri2Shader;
shader parallShader;
shader tableShader;

// SceneGraph
sceneGraph sG;

// SceneNode
sceneNode *rootNode;
sceneNode *tableNode;
sceneNode *tangramNode, *cubeNode, *sTri1Node, *sTri2Node, *lTri1Node, *lTri2Node, *mTriNode, *parallNode; // tangram and his pieces

//Camera Quarterion rotation
// only rotates when true
bool g_rot = false;

// rotate the cam or rotate the pieces
//true -> rotate the camera, false -> rotate the pieces
bool g_camMode = true; 

// piece selected
GLuint index; //index of the piece selected
sceneNode *nodeSelected = nullptr; // node of the piece
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

////////////////////////////////////////////////////////////////////////
// translate the piece with the values(translation, rotation and sclaing) the node have
void translatePiece() {
	vector3 vT = nodeSelected->getTranslationVector();
	matrix4x4 T = mf.translationMatrix4x4(vT);

	qtrn default_qtrn = { 1.0f, 0.0f, 0.0f, 0.0f }; //DEFAULT_QTRN	
	qtrn q = nodeSelected->getRotQtrn();
	matrix4x4 R;
	if (q == default_qtrn) { //if are equal the user did not rotate the piece 
		vector3 vR = nodeSelected->getRotationVector();
		double angle = nodeSelected->getAngle();

		R = mf.rotationMatrix4x4(vR, angle);
	}
	else {
		matrix4x4 mAux;
		R = qGLMatrix(q, mAux);  // matrix rotação devolve em row major
	}

	vector3 vS = nodeSelected->getScalingVector();
	matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

	nodeSelected->setModelMatrix(T * R * S);
}

//////////////////////////////////////////////////////////////////////// Mouse/Key Eventes
void keyboard_down(unsigned char key, int x, int y) {
	switch (key) {
		case 'W':
		case 'w':
		{
			if (nodeSelected != nullptr) {
				vector3 vT = nodeSelected->getTranslationVector();
				vector3 newVT(vT._a, vT._b, vT._c + TRANSZZ);
				nodeSelected->setTranslationVector(newVT);
				translatePiece();
			}
			break;
		}
		case 'S':
		case 's':
		{
			if (nodeSelected != nullptr) {
				vector3 vT = nodeSelected->getTranslationVector();
				vector3 newVT(vT._a, vT._b, vT._c - TRANSZZ);
				nodeSelected->setTranslationVector(newVT);
				translatePiece();
			}
			break;
		}
		case 'A':
		case 'a':
			{
				if (nodeSelected != nullptr) {
					vector3 vT = nodeSelected->getTranslationVector();
					vector3 newVT(vT._a - TRANSXX, vT._b, vT._c);
					nodeSelected->setTranslationVector(newVT);
					translatePiece();
				}
				break;
			}
		case 'D':
		case 'd':
			{
				if (nodeSelected != nullptr) {
					vector3 vT = nodeSelected->getTranslationVector();
					vector3 newVT(vT._a + TRANSXX, vT._b, vT._c);
					nodeSelected->setTranslationVector(newVT);
					translatePiece();
				}
				break;
			}
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
		g_oldX = x;
		g_oldY = y;
		if (g_camMode) {
			g_rot = true;
		}
		else {
			g_rot = false;
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glReadPixels(x, WinY - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		std::cout << "index: " << index << "\n";
		
		//selected one of the pieces
		if(index >= 1 && index <=7) {
			g_camMode = false;
			
			std::vector<sceneNode*> nodes = tangramNode->getNodes();
			for (unsigned i = 0; i < nodes.size(); i++) {
				if (index == nodes[i]->getIndex()) {
					nodeSelected = nodes[i];
					std::cout << "node name" << nodeSelected->getName() << "\n";
					break;
				}
			}
			if (nodeSelected == nullptr) {
				std::cout << "Error: nodeSelected with index: " << index << " not found" << "\n";
			}
		}
		else {
			g_camMode = true;
		}

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
	if (g_rot == true && g_camMode == true) { 	// cam rotation with no Gimbal lock 
		float tetaX = (x - g_oldX); // angle to rotate in x (Deg)
		float tetaY = (y - g_oldY); // angle to rotate in y (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;

		qtrn q = mainCamera.getRotQtrn();
		//Recive the angle in deg
		q = (qAux.qFromAngleAxis(tetaX, YY_4) * q);
		q = (qAux.qFromAngleAxis(tetaY, XX_4) * q);
		mainCamera.setRotQtrn(q);
		
		matrix4x4 mAux;
		matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rotação devolve em row major

		vector3 vT(0, 0, -(mainCamera.getEye()._c));
		matrix4x4 T = mf.translationMatrix4x4(vT); // matrix translação 

		matrix4x4 vM = T * mR; // view matrix
		matrix4x4 vMT = vM.transposeM4x4(); // view matrix transposta -> column major
		mainCamera.setViewMatrix(vMT);
	}
	else if(g_rot == false && g_camMode == false){ // piece rotation
		float tetaX = (x - g_oldX); // angle to rotate in x (Deg)
		float tetaY = (y - g_oldY); // angle to rotate in y (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;

		qtrn q = nodeSelected->getRotQtrn();
		//Recive the angle in deg
		q = (qAux.qFromAngleAxis(tetaX, YY_4) * q);
		//q = (qAux.qFromAngleAxis(tetaY, XX_4) * q);
		nodeSelected->setRotQtrn(q);

		matrix4x4 mAux;
		matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rotação devolve em row major

		vector3 vT = nodeSelected->getTranslationVector();
		matrix4x4 T = mf.translationMatrix4x4(vT); // matrix translação 

		vector3 vS = nodeSelected->getScalingVector();
		matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

		matrix4x4 vM = T * mR * S; // view matrix
		//matrix4x4 vMT = vM.transposeM4x4(); // view matrix transposta -> column major
		
		nodeSelected->setModelMatrix(vM);
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
	*			 		table, index: 0				|- prespMatrix
	*						|
	*	closed tangram <----|
	*		 |- cube, index: 1
	*		 |- small triangle 1, index: 2
	*		 |- small triangle 2, index: 3
	*		 |- medium triangle, index: 4
	*		 |- large triangle 1, index: 5
	*		 |- large triangle 2, index: 6
	*		 |- parallelogram, index: 7
	*
	* For transformation the order is :  T * R * S
	*/
	sG.setCamera(&mainCamera);

	rootNode = new sceneNode(); //root node (empty object)
	rootNode->setName("root");
	rootNode->makeInitialModelMatrix();

	tableNode = new sceneNode();
	tableNode->setName("table"); 
	tableNode->setIndex(0);
	tableNode->makeInitialModelMatrix();
	tableNode->setMesh(&tableMesh);
	tableNode->setShader(&tableShader);
	rootNode->addNode(tableNode);

	tangramNode = new sceneNode(); // empty object
	tangramNode->setName("tangram");
	tangramNode->makeInitialModelMatrix();
	tableNode->addNode(tangramNode);

	cubeNode = new sceneNode();
	cubeNode->setName("cube");
	cubeNode->setIndex(1);
	cubeNode->setTranslationVector(vector3(0.2f, 0.0f, 0.0f));
	cubeNode->makeInitialModelMatrix();
	cubeNode->setMesh(&cubeMesh);
	cubeNode->setShader(&cubeShader);
	tangramNode->addNode(cubeNode);

	sTri1Node = new sceneNode();
	sTri1Node->setName("small triangle 1");
	sTri1Node->setIndex(2);
	sTri1Node->setTranslationVector(vector3(-0.2f, 0.0f, 0.2f));
	sTri1Node->makeInitialModelMatrix();
	sTri1Node->setMesh(&triangleMesh);
	sTri1Node->setShader(&sTri1Shader);
	tangramNode->addNode(sTri1Node);

	sTri2Node = new sceneNode();
	sTri2Node->setName("small triangle 2");
	sTri2Node->setIndex(3);
	sTri2Node->setTranslationVector(vector3(0.4f, 0.0f, 0.0f));
	sTri2Node->setRotationVector(vector3(0, 1, 0));
	sTri2Node->setAngle((M_PI / 2));
	sTri2Node->makeInitialModelMatrix();
	sTri2Node->setMesh(&triangleMesh);
	sTri2Node->setShader(&sTri2Shader);
	tangramNode->addNode(sTri2Node);

	mTriNode = new sceneNode();
	mTriNode->setName("medium triangle");
	mTriNode->setIndex(4);
	mTriNode->setTranslationVector(vector3(0.40, 0.0f, 0.0f));
	mTriNode->setRotationVector(vector3(0, 1, 0));
	mTriNode->setAngle(-(3 * M_PI / 4));
	mTriNode->setScalingVector(vector3(1.4f, 1.0f, 1.4f));
	mTriNode->makeInitialModelMatrix();
	mTriNode->setMesh(&triangleMesh);
	mTriNode->setShader(&mTriShader);
	tangramNode->addNode(mTriNode);

	lTri1Node = new sceneNode();
	lTri1Node->setName("large triangle 1");
	lTri1Node->setIndex(5);
	lTri1Node->setTranslationVector(vector3(0.4f, 0.0f, -0.4f));
	lTri1Node->setScalingVector(vector3(2.0f, 1.0f, 2.0f));
	lTri1Node->setRotationVector(vector3(0, 1, 0));
	lTri1Node->setAngle(M_PI);
	lTri1Node->makeInitialModelMatrix();
	lTri1Node->setMesh(&triangleMesh);
	lTri1Node->setShader(&lTri1Shader);
	tangramNode->addNode(lTri1Node);

	lTri2Node = new sceneNode();
	lTri2Node->setName("large triangle 2");
	lTri2Node->setIndex(6);
	lTri2Node->setTranslationVector(vector3(-0.4f, 0.0f, -0.4f));
	lTri2Node->setScalingVector(vector3(2.0f, 1.0f, 2.0f));
	lTri2Node->setRotationVector(vector3(0, 1, 0));
	lTri2Node->setAngle(-(M_PI / 2));
	lTri2Node->makeInitialModelMatrix();
	lTri2Node->setMesh(&triangleMesh);
	lTri2Node->setShader(&lTri2Shader);
	tangramNode->addNode(lTri2Node);

	parallNode = new sceneNode();
	parallNode->setName("parallelogram");
	parallNode->setIndex(7);
	parallNode->setTranslationVector(vector3(-0.4f, 0.0f, 0.4f));
	parallNode->makeInitialModelMatrix();
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