#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "FreeImage.h"
#include "src/mesh/mesh.h"
#include "src/mesh/meshManager.h"
#include "src/shader/shaderManager.h"
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
<<<<<<< HEAD
#include "src/image/image.h"
#include "src/color/color.h"
=======

#include "src/image/image.h"

>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
#include "jsoncons/json.hpp"
// For convenience
using jsoncons::json;

#define CAPTION "Loading World"
#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2
#define DEGTORAD 0.0174532925
#define M_PI 3.14159265358979323846
<<<<<<< HEAD
#define ROTATIONSPEED  0.1f
#define TRANSLATIONSPEED  0.001f
=======
#define TRANSXX 0.1 //how much the piece translate, each time you press a key, in XX
#define TRANSZZ 0.1 //how much the piece translate, each time you press a key, in ZZ
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

vector4 XX_4(1, 0, 0, 1);
vector4 YY_4(0, 1, 0, 1);
<<<<<<< HEAD
vector4 ZZ_4(0, 0, 1, 1);

matrixFactory mf;
qtrn qAux;
image snapShotImage;
std::string fileLoaded;
// mouse click
int g_oldX = 0; // last coord x of mouse in window
int g_oldY = 0;	// last coord y of mouse in window
=======
matrixFactory mf;
qtrn qAux;

// mouse click
int g_oldX = 0; // last coord x of mouse in window
int g_oldY = 0;	// last coord y of mouse in window

//Camera
camera mainCamera;
vector3 eye(10.0f, 0.0f, 0.0f);
vector3 light(1.0f, 2.0f, 1.0f);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

//Camera
camera mainCamera;

//mesh;
meshManager meshM;
mesh cubeMesh;
mesh triangleMesh;
mesh parallMesh;
mesh tableMesh;

// Shader
<<<<<<< HEAD
shaderManager shaderM;
=======
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
shader cubeShader;
shader sTri1Shader, sTri2Shader, mTriShader, lTri1Shader, lTri2Shader;
shader parallShader;
shader tableShader;

// SceneGraph
sceneGraph sG;

// SceneNode
sceneNode *rootNode;
sceneNode *tableNode;
sceneNode *lightNode;
<<<<<<< HEAD
sceneNode *tangramNode, *cubeNode, *sTri1Node, *sTri2Node, 
	*lTri1Node, *lTri2Node, *mTriNode, *parallNode; // tangram and his pieces
=======
sceneNode *tangramNode, *cubeNode, *sTri1Node, *sTri2Node, *lTri1Node, *lTri2Node, *mTriNode, *parallNode; // tangram and his pieces

//Camera Quarterion rotation
// only rotates when true
bool g_rot = false;

// rotate the cam or rotate the pieces
//true -> rotate the camera, false -> rotate the pieces
bool g_camMode = true; 

//Colors
float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
float blue2[4] = { 0.0f, 0.0f, 0.5f, 1.0f };
float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
float orange[4] = { 1.0f, 0.5f, 0.1f, 1.0f };
float purple[4] = { 0.8f, 0.0f, 0.2f, 1.0f };
float pink[4] = { 1.0f, 0.5f, 0.5f, 1.0f };
float brown[4] = { 0.164f, 0.074f, 0.015f, 1.0f };
float brown2[4] = { 0.6f, 0.3f, 0.2f, 1.0f };

>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

//Texture
GLuint DiffuseTextureID;
GLuint NormalTextureID;
<<<<<<< HEAD

//Interaction
bool camMode = true; //q
bool translateMode = false;  //w
bool rotateMode = false; //e

/*						Scene Graph
*					root <----|----> camera
*						|
*					light, index:0
*			 		table, index: 0
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
*/
=======
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
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
void translatePiece(){ 
	sceneNode * nodeSelected = sG.getNodeSelected();
	vector3 vT = nodeSelected->getTranslationVector();
	matrix4x4 T = mf.translationMatrix4x4(vT);

	qtrn default_qtrn = { 1.0f, 0.0f, 0.0f, 0.0f }; //DEFAULT_QTRN	
	qtrn q = nodeSelected->getRotQtrn();
	matrix4x4 R;
<<<<<<< HEAD
	
	matrix4x4 mAux;
	R = qGLMatrix(q, mAux);  // matrix rotação devolve em row major
=======
	if (q == default_qtrn) { //if are equal the user did not rotate the piece 
		vector3 vR = nodeSelected->getRotationVector();
		double angle = nodeSelected->getAngle();

		R = mf.rotationMatrix4x4(vR, angle);
	}
	else {
		matrix4x4 mAux;
		R = qGLMatrix(q, mAux);  // matrix rotação devolve em row major
	}
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

	vector3 vS = nodeSelected->getScalingVector();
	matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

	nodeSelected->setModelMatrix(T * R * S);
}

<<<<<<< HEAD
void printHelp() {
	std::cout << "-------------------------" << "\n";
	std::cout << "Use the mouse to interact" << "\n";
	std::cout << 
		"Press Q to rotate camera\n" <<
		"Press W to move a piece\n" <<
		"Press E to rotate the piece\n" <<
		"Press R to restart the scene\n" <<
		"Press T to aproximate the angle to units\n" <<
		"Press L to rotate the paralellogram 180º in zz axe\n" <<
		"Press P to snapshot the window\n" <<
		"Press S to save the scene\n";
	std::cout << "-------------------------" << "\n";
}

void printMode(std::string str) {
	std::cout << str + " mode activated!" << "\n";
	std::cout << "Use mouse to interact" << "\n";
	std::cout << "Press i to see help!" << "\n";
}
//////////////////////////////////////////////////////////////////////// SAVE SCENE IN JSON
//from nodes the only info that changes is the translaction vectores and rotation vectores
//so its only info need to be saved, the other is copied from the default json
json saveNodes(json j) {
	vector3 vT;
	qtrn q;
	//save vectores
	// json::array{ "JPEG","PSD","TIFF","DNG" };
	
	vT = cubeNode->getTranslationVector();
	j["nodes"]["tangram"]["cube"]["tV"] = json::array{ vT._a, vT._b, vT._c };
	q = cubeNode->getRotQtrn();
	j["nodes"]["tangram"]["cube"]["qtrn"] = json::array{ q._t, q._x, q._y, q._z };

	vT = sTri1Node->getTranslationVector();
	j["nodes"]["tangram"]["small_triangle_1"]["tV"] = json::array{ vT._a, vT._b, vT._c };
	q = sTri1Node->getRotQtrn();
	j["nodes"]["tangram"]["small_triangle_1"]["qtrn"] = json::array{ q._t, q._x, q._y, q._z };

	vT = sTri2Node->getTranslationVector();
	j["nodes"]["tangram"]["small_triangle_2"]["tV"] = json::array{ vT._a, vT._b, vT._c };
	q = sTri2Node->getRotQtrn();
	j["nodes"]["tangram"]["small_triangle_2"]["qtrn"] = json::array{ q._t, q._x, q._y, q._z };

	vT = mTriNode->getTranslationVector();
	j["nodes"]["tangram"]["medium_triangle"]["tV"] = json::array{ vT._a, vT._b, vT._c };
	q = mTriNode->getRotQtrn();
	j["nodes"]["tangram"]["medium_triangle"]["qtrn"] = json::array{ q._t, q._x, q._y, q._z };

	vT = lTri1Node->getTranslationVector();
	j["nodes"]["tangram"]["large_triangle_1"]["tV"] = json::array{ vT._a, vT._b, vT._c };
	q = lTri1Node->getRotQtrn();
	j["nodes"]["tangram"]["large_triangle_1"]["qtrn"] = json::array{ q._t, q._x, q._y, q._z };

	vT = lTri2Node->getTranslationVector();
	j["nodes"]["tangram"]["large_triangle_2"]["tV"] = json::array{ vT._a, vT._b, vT._c };
	q = lTri2Node->getRotQtrn();
	j["nodes"]["tangram"]["large_triangle_2"]["qtrn"] = json::array{ q._t, q._x, q._y, q._z };

	vT = parallNode->getTranslationVector();
	j["nodes"]["tangram"]["parallelogram"]["tV"] = json::array{ vT._a, vT._b, vT._c };
	q = parallNode->getRotQtrn();
	j["nodes"]["tangram"]["parallelogram"]["qtrn"] = json::array{ q._t, q._x, q._y, q._z };

	return j;
}

void restartScene(std::string file) {
	// Read from stream
	std::ifstream is(file);
	json j = json::parse(is);

	qtrn q;


	//tableNode->makeInitialModelMatrix();

	//tangramNode->makeInitialModelMatrix();

	cubeNode->setScalingVector(
		vector3(j["nodes"]["tangram"]["cube"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["cube"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["cube"]["sV"][2].as_double())
	);
	cubeNode->setTranslationVector(
		vector3(j["nodes"]["tangram"]["cube"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["cube"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["cube"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][3].as_double()) };
	cubeNode->setRotQtrn(q);
	cubeNode->makeInitialModelMatrix();

	sTri1Node->setScalingVector(
		vector3(j["nodes"]["tangram"]["small_triangle_1"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["small_triangle_1"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["small_triangle_1"]["sV"][2].as_double())
	);
	sTri1Node->setTranslationVector(
		vector3(j["nodes"]["tangram"]["small_triangle_1"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["small_triangle_1"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["small_triangle_1"]["tV"][2].as_double())
	);
	vector3 a(j["nodes"]["tangram"]["small_triangle_1"]["tV"][0].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["tV"][1].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["tV"][2].as_double());
	q = { static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][3].as_double()) };
	sTri1Node->setRotQtrn(q);
	sTri1Node->makeInitialModelMatrix();

	sTri2Node->setScalingVector(
		vector3(j["nodes"]["tangram"]["small_triangle_2"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["small_triangle_2"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["small_triangle_2"]["sV"][2].as_double())
	);
	sTri2Node->setTranslationVector(
		vector3(j["nodes"]["tangram"]["small_triangle_2"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["small_triangle_2"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["small_triangle_2"]["tV"][2].as_double()));
	q = { static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][3].as_double()) };
	sTri2Node->setRotQtrn(q);
	sTri2Node->makeInitialModelMatrix();

	mTriNode->setScalingVector(
		vector3(j["nodes"]["tangram"]["medium_triangle"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["sV"][2].as_double())
	);
	mTriNode->setTranslationVector(
		vector3(j["nodes"]["tangram"]["medium_triangle"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][3].as_double()) };
	mTriNode->setRotQtrn(q);
	mTriNode->makeInitialModelMatrix();

	lTri1Node->setScalingVector(
		vector3(j["nodes"]["tangram"]["large_triangle_1"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["sV"][2].as_double())
	);
	lTri1Node->setTranslationVector(
		vector3(j["nodes"]["tangram"]["large_triangle_1"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][3].as_double()) };
	lTri1Node->setRotQtrn(q);
	lTri1Node->makeInitialModelMatrix();

	lTri2Node->setScalingVector(
		vector3(j["nodes"]["tangram"]["large_triangle_2"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["sV"][2].as_double())
	);
	lTri2Node->setTranslationVector(
		vector3(j["nodes"]["tangram"]["large_triangle_2"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][3].as_double()) };
	lTri2Node->setRotQtrn(q);
	lTri2Node->makeInitialModelMatrix();

	parallNode->setScalingVector(
		vector3(j["nodes"]["tangram"]["parallelogram"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["sV"][2].as_double())
	);
	parallNode->setTranslationVector(
		vector3(j["nodes"]["tangram"]["parallelogram"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][3].as_double()) };
	parallNode->setRotQtrn(q);
	parallNode->makeInitialModelMatrix();

}
void saveScene(std::string filePath) {
	json j;

	std::ifstream is("../../assets/json/defaultLoad.json");
	json jParsed = json::parse(is);

	j = saveNodes(jParsed);
	
	// Write to stream -> creates the file if doesn't exist
	std::ofstream os(filePath);
	os << j;

	std::cout << "Scene saved in file: " << filePath << "\n";
}
//////////////////////////////////////////////////////////////////////// Mouse/Key Eventes
void keyboard_down(unsigned char key, int x, int y) {
	switch (key) {
		case 'I':
		case 'i':
		{
			printHelp();
			break;
		}
		case 'Q':
		case 'q':
		{
			printMode("Camera");
			camMode = true;
			translateMode = false;
			rotateMode = false;
			break;
		}
		case 'W':
		case 'w':
		{
			printMode("Translation");
			camMode = false;
			translateMode = true;
			rotateMode = false;
			break;
		}
		case 'E':
		case 'e':
		{
			printMode("Rotation");
			camMode = false;
			translateMode = false;
			rotateMode = true;
			break;
		}
		case 'R':
		case 'r':
		{
			restartScene(fileLoaded);
			break;
		}
		case 'L':
		case 'l':
		{
			sceneNode* nodeSelected = sG.getNodeSelected();
			if (nodeSelected != nullptr && nodeSelected->getName() == "parallelogram") {
				qtrn q = nodeSelected->getRotQtrn();
				//Recive the angle in deg
				q = (qAux.qFromAngleAxis(180, ZZ_4) * q);
				nodeSelected->setRotQtrn(q);

				matrix4x4 mAux;
				matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rotação devolve em row major

				vector3 vT = nodeSelected->getTranslationVector();
				vector3 vTAux(vT._a, vT._b, vT._c);
				matrix4x4 T = mf.translationMatrix4x4(vTAux); // matrix translação 
				nodeSelected->setTranslationVector(vTAux);

				vector3 vS = nodeSelected->getScalingVector();
				matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

				matrix4x4 vM = T * mR * S; // view matrix -> row major

				nodeSelected->setModelMatrix(vM);
			}
			break;
		}
		case 'T':
		case 't':
		{
			sceneNode* nodeSelected = sG.getNodeSelected();
			if (nodeSelected != nullptr) {
				qtrn q = nodeSelected->getRotQtrn();
				
				//get the aproximated angle value in Deg
				float thetaf;
				vector4 axis_f;
				qAux.qToAngleAxis(q, thetaf, axis_f);
				int theta = round(thetaf);
				
				q = (qAux.qFromAngleAxis(theta, axis_f) );
				nodeSelected->setRotQtrn(q);

				matrix4x4 mAux;
				matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rotação devolve em row major

				vector3 vT = nodeSelected->getTranslationVector();
				vector3 vTAux(vT._a, vT._b, vT._c);
				matrix4x4 T = mf.translationMatrix4x4(vTAux); // matrix translação 

				vector3 vS = nodeSelected->getScalingVector();
				matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

				matrix4x4 vM = T * mR * S; // view matrix -> row major

				nodeSelected->setModelMatrix(vM);
			}
			break;
		}
		case 'S':
		case 's':
		{
			saveScene("../../assets/json/savedScene.json");
			break;
		}
		case 'P':
		case 'p':
		{
			snapShotImage.snapShot(WinX, WinY);
			break;
		}
=======
//////////////////////////////////////////////////////////////////////// Mouse/Key Eventes
void keyboard_down(unsigned char key, int x, int y) {
	switch (key) {
		case 'W':
		case 'w':
		{	
			sceneNode* nodeSelected = sG.getNodeSelected();
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
			sceneNode* nodeSelected = sG.getNodeSelected();
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
				sceneNode* nodeSelected = sG.getNodeSelected();
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
				sceneNode* nodeSelected = sG.getNodeSelected();
				if (nodeSelected != nullptr) {
					vector3 vT = nodeSelected->getTranslationVector();
					vector3 newVT(vT._a + TRANSXX, vT._b, vT._c);
					nodeSelected->setTranslationVector(newVT);
					translatePiece();
				}
				break;
			}
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	}
}

void mouseWheel(int wheel, int direction, int x, int y) {
	const float MaxSpeed = 0.5f;
	vector3 vec(1, 0, 0);

	if (direction == 1) {
		vector3 newEye = mainCamera.getEye() - vec * MaxSpeed;
		mainCamera.setEye(newEye);
		vector3 tran(0, 0, -(newEye.norma()));
		mainCamera._T = mf.translationMatrix4x4(tran);
	}
	if (direction == -1) {
		vector3 newEye = mainCamera.getEye() + vec * MaxSpeed;
		mainCamera.setEye(newEye);
		vector3 tran(0, 0, -(newEye.norma()));
		mainCamera._T = mf.translationMatrix4x4(tran);
	}
}

void OnMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_oldX = x;
		g_oldY = y;
<<<<<<< HEAD
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_oldX = x;
		g_oldY = y;
=======
		if (g_camMode) {
			g_rot = true;
		}
		else {
			g_rot = false;
		}
	}
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

		GLuint index;
		glReadPixels(x, WinY - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
<<<<<<< HEAD
=======
		//std::cout << "index: " << index << "\n";
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
		sG.setIndex(index);

		GLfloat red;
		GLfloat green;
		GLfloat blue;
		glReadPixels(x, WinY - y - 1, 1, 1, GL_RED, GL_FLOAT, &red);
		glReadPixels(x, WinY - y - 1, 1, 1, GL_GREEN, GL_FLOAT, &green);
		glReadPixels(x, WinY - y - 1, 1, 1, GL_BLUE, GL_FLOAT, &blue);
<<<<<<< HEAD

		//selected one of the pieces
		if(index >= 1 && index <=7) {
=======
		//std::cout << "color(RGB): " << "(" << red << ", " << green << ", " << blue << ")" << "\n";

		//selected one of the pieces
		if(index >= 1 && index <=7) {
			g_camMode = false;
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
			
			std::vector<sceneNode*> nodes = tangramNode->getNodes();
			for (unsigned i = 0; i < nodes.size(); i++) {
				if (index == nodes[i]->getIndex()) {
<<<<<<< HEAD
					sG.setNodeSelected(nodes[i]);
					/*std::cout << "Selected: " << nodes[i]->getName() <<
						" with index: " << index <<
						" and color(RGB): " << "(" << red << ", " << green << ", " << blue << ")" << "\n"; */
=======
					//nodeSelected = nodes[i];
					sG.setNodeSelected(nodes[i]);
					std::cout << "Selected: " << nodes[i]->getName() << 
						" with index: " << index << 
						" and color(RGB): " << "(" << red << ", " << green << ", " << blue << ")" << "\n";
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
					break;
				}
			}
			if (sG.getNodeSelected() == nullptr) {
				std::cout << "Error: nodeSelected with index: " << index << " not found" << "\n";
			}
		}
<<<<<<< HEAD
=======
		else {
			g_camMode = true;
		}
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	}
}

void OnMouseMove(int x, int y) {
<<<<<<< HEAD
	if (camMode == true && translateMode == false && rotateMode == false) { // cam rotation with no Gimbal lock 
=======
	if (g_rot == true && g_camMode == true) { 	// cam rotation with no Gimbal lock 
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
		float tetaX = (x - g_oldX); // angle to rotate in x (Deg)
		float tetaY = (y - g_oldY); // angle to rotate in y (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;

		const float RotationSpeed = 0.3f;

		//Recive the angle in deg
		qtrn qyy = qAux.qFromAngleAxis(tetaX*RotationSpeed, YY_4);   // yy4 or YY_4
		qtrn qxx = qAux.qFromAngleAxis(tetaY*RotationSpeed, XX_4);
		qtrn q = qyy * qxx * mainCamera.getqView();
		mainCamera.setqView(q);
	}
	else if(g_rot == false && g_camMode == false){ // piece rotation
		float tetaX = (x - g_oldX); // angle to rotate in x (Deg)
		float tetaY = (y - g_oldY); // angle to rotate in y (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;

		sceneNode* nodeSelected = sG.getNodeSelected();
		qtrn q = nodeSelected->getRotQtrn();
		//Recive the angle in deg
<<<<<<< HEAD
		qtrn qyy = qAux.qFromAngleAxis(tetaX * ROTATIONSPEED, YY_4);  
		qtrn qxx = qAux.qFromAngleAxis(tetaY * ROTATIONSPEED, XX_4);
		qtrn q = qyy * qxx * mainCamera.getqView();
		mainCamera.setqView(q);
	}
	else if (camMode == false && translateMode == true && rotateMode == false) { // piece translation
		float deltaX = (x - g_oldX) * TRANSLATIONSPEED; // translate in x (Deg)
		float deltaZ = (y - g_oldY) * TRANSLATIONSPEED; // translate in Z (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;

		sceneNode* nodeSelected = sG.getNodeSelected();
		if (nodeSelected != nullptr) {
			vector3 vT = nodeSelected->getTranslationVector();
			vector3 newVT(vT._a + deltaX, vT._b, vT._c + deltaZ);
			nodeSelected->setTranslationVector(newVT);
			translatePiece();
		}
	}
	else if(camMode == false && translateMode == false && rotateMode == true){ // piece rotation
		float tetaX = (x - g_oldX) * ROTATIONSPEED; // angle to rotate in x (Deg)
		float tetaY = (y - g_oldY) * ROTATIONSPEED; // angle to rotate in y (Deg)
		g_oldX = (float)x;
		g_oldY = (float)y;
=======
		q = (qAux.qFromAngleAxis(tetaX, YY_4) * q);
		//q = (qAux.qFromAngleAxis(tetaY, XX_4) * q);
		nodeSelected->setRotQtrn(q);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

		sceneNode* nodeSelected = sG.getNodeSelected();
		if (nodeSelected != nullptr) {
			qtrn q = nodeSelected->getRotQtrn();
			//Recive the angle in deg
			q = (qAux.qFromAngleAxis(tetaX, YY_4) * q);
			//q = (qAux.qFromAngleAxis(tetaY, XX_4) * q);
			nodeSelected->setRotQtrn(q);

<<<<<<< HEAD
			matrix4x4 mAux;
			matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rotação devolve em row major

			vector3 vT = nodeSelected->getTranslationVector();
			matrix4x4 T = mf.translationMatrix4x4(vT); // matrix translação 

			vector3 vS = nodeSelected->getScalingVector();
			matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

			matrix4x4 vM = T * mR * S; // view matrix -> row major

			nodeSelected->setModelMatrix(vM);
		}
=======
		vector3 vT = nodeSelected->getTranslationVector();
		matrix4x4 T = mf.translationMatrix4x4(vT); // matrix translação 

		vector3 vS = nodeSelected->getScalingVector();
		matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

		matrix4x4 vM = T * mR * S; // view matrix -> row major
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
		
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

<<<<<<< HEAD
///////////////////////////////////////////////////////////////LOADS
void loadCamera(std::string file, json j) {
	if (j.contains("camera"))
	{
		int eye0 = j["camera"]["eye"][0].as_int();
		int eye1 = j["camera"]["eye"][1].as_int();
		int eye2 = j["camera"]["eye"][2].as_int();
		vector3 eye(eye0, eye1, eye2);
		mainCamera.setEye(eye);
		int light0 = j["camera"]["light"][0].as_int();
		int light1 = j["camera"]["light"][1].as_int();
		int light2 = j["camera"]["light"][2].as_int();
		vector3 light(light0, light1, light2);
		mainCamera.setLight(light);
		// View Matrix
		mainCamera.makeViewMatrix();
		// projection Perspective
		if (j["camera"].contains("perspective")) {
			int fovy = j["camera"]["perspective"]["Fovy"].as_int();
			int aspectNum = j["camera"]["perspective"]["Aspect"][0].as_int();
			int aspectDen = j["camera"]["perspective"]["Aspect"][1].as_int();
			int nearZ = j["camera"]["perspective"]["NearZ"].as_int();
			int farZ = j["camera"]["perspective"]["FarZ"].as_int();
			mainCamera.makePrespMatrix((fovy * DEGTORAD), (aspectNum / aspectDen), nearZ, farZ);
		}
		else
		{
			std::cerr << "ERROR:" << std::endl;
			std::cerr << "  source:     " << file << std::endl;
			std::cerr << "  type:       " << "file does not contain the key perspective" << std::endl;
			exit(EXIT_FAILURE);
		}

	}
	else
	{
		std::cerr << "ERROR:" << std::endl;
		std::cerr << "  source:     " << file << std::endl;
		std::cerr << "  type:       " << "file does not contain the key camera" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void loadMesh(std::string file, json j) {
	if (j.contains("mesh")) {
		// tangram
		cubeMesh.createMesh(j["mesh"]["cubeMesh"].as<std::string>());
		triangleMesh.createMesh(j["mesh"]["triangleMesh"].as<std::string>());
		parallMesh.createMesh(j["mesh"]["parallMesh"].as<std::string>());
		//table
		tableMesh.createMesh(j["mesh"]["tableMesh"].as<std::string>());

		meshM.insertMesh("cubeMesh", &cubeMesh);
		meshM.insertMesh("triangleMesh", &triangleMesh);
		meshM.insertMesh("parallMesh", &parallMesh);
		meshM.insertMesh("tableMesh", &tableMesh);
	}
	else
	{
		std::cerr << "ERROR:" << std::endl;
		std::cerr << "  source:     " << file << std::endl;
		std::cerr << "  type:       " << "file does not contain the key mesh" << std::endl;
		exit(EXIT_FAILURE);
	}

}

void loadShader(std::string file, json j) {
	std::string vsPath;
	std::string fsPath;
	std::string associatedMesh;
	mesh* meshAux;
	if (j.contains("shader")) {
		vsPath = j["shader"]["cubeShader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["cubeShader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["cubeShader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		cubeShader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());

		vsPath = j["shader"]["sTri1Shader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["sTri1Shader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["sTri1Shader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		sTri1Shader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());

		vsPath = j["shader"]["sTri2Shader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["sTri2Shader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["sTri2Shader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		sTri2Shader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());

		vsPath = j["shader"]["mTriShader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["mTriShader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["mTriShader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		mTriShader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());

		vsPath = j["shader"]["lTri1Shader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["lTri1Shader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["lTri1Shader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		lTri1Shader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());

		vsPath = j["shader"]["lTri2Shader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["lTri2Shader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["lTri2Shader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		lTri2Shader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());

		vsPath = j["shader"]["parallShader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["parallShader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["parallShader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		parallShader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());

		vsPath = j["shader"]["tableShader"]["vertexShader"].as<std::string>();
		fsPath = j["shader"]["tableShader"]["fragShader"].as<std::string>();
		associatedMesh = j["shader"]["tableShader"]["mesh"].as<std::string>();
		meshAux = meshM.getMeshByName(associatedMesh);
		tableShader.createShaderProgram(
			vsPath,
			fsPath,
			meshAux->getTexcoordsLoaded(),
			meshAux->getNormalsLoaded());
		
		shaderM.insertShader("cubeShader", &cubeShader);
		shaderM.insertShader("sTri1Shader", &sTri1Shader);
		shaderM.insertShader("sTri2Shader", &sTri2Shader);
		shaderM.insertShader("mTriShader", &mTriShader);
		shaderM.insertShader("lTri1Shader", &lTri1Shader);
		shaderM.insertShader("lTri2Shader", &lTri2Shader);
		shaderM.insertShader("parallShader", &parallShader);
		shaderM.insertShader("tableShader", &tableShader);
		createBufferObjects();
	}
	else
	{
		std::cerr << "ERROR:" << std::endl;
		std::cerr << "  source:     " << file << std::endl;
		std::cerr << "  type:       " << "file does not contain the key shader" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void loadScene(std::string file, json j) {
	color c;
	qtrn q;
=======
void myInit() {
	mainCamera.setEye(eye);
	mainCamera.setLight(light);

	// View Matrix
	mainCamera.makeViewMatrix();
	// projection Matrix Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
	mainCamera.makePrespMatrix((M_PI / 6), (640.0f / 480.0f), 1, 20);

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
	*					root <----|------->      camera
	*						|	
						light, index: -1			
	*			 		table, index: 0				
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
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	sG.setCamera(&mainCamera);

	rootNode = new sceneNode(); //root node (empty object)
	rootNode->setName("root");
	rootNode->makeInitialModelMatrix();

	lightNode = new sceneNode();
<<<<<<< HEAD
	lightNode->setName(j["nodes"]["light"]["name"].as<std::string>());
	lightNode->setIndex(j["nodes"]["light"]["index"].as_int());
	lightNode->setTranslationVector(vector3(j["nodes"]["light"]["tV"][0].as_double(),
		j["nodes"]["light"]["tV"][1].as_double(),
		j["nodes"]["light"]["tV"][2].as_double())
	);
	lightNode->makeInitialModelMatrix();
	lightNode->setMesh(meshM.getMeshByName(j["nodes"]["light"]["mesh"].as<std::string>()));	
	lightNode->setShader(shaderM.getShaderByName(j["nodes"]["light"]["shader"].as<std::string>()));
	lightNode->setColor(c.getColorByName(j["nodes"]["light"]["color"].as<std::string>()));
	rootNode->addNode(lightNode);

	tableNode = new sceneNode();
	tableNode->setName(j["nodes"]["table"]["name"].as<std::string>());
	tableNode->setIndex(j["nodes"]["table"]["index"].as_int());
	tableNode->makeInitialModelMatrix();
	tableNode->setMesh(meshM.getMeshByName(j["nodes"]["table"]["mesh"].as<std::string>()));
	tableNode->setShader(shaderM.getShaderByName(j["nodes"]["table"]["shader"].as<std::string>()));
	tableNode->setTextures(DiffuseTextureID, NormalTextureID);  // add textures
	tableNode->setColor(c.getColorByName(j["nodes"]["table"]["color"].as<std::string>()));
=======
	lightNode->setName("light");
	lightNode->setIndex(0);
	lightNode->setTranslationVector(light);
	lightNode->makeInitialModelMatrix();
	lightNode->setMesh(&cubeMesh);
	lightNode->setShader(&cubeShader);
	lightNode->setColor(pink);
	rootNode->addNode(lightNode);

	tableNode = new sceneNode();
	tableNode->setName("table"); 
	tableNode->setIndex(0);
	tableNode->makeInitialModelMatrix();
	tableNode->setMesh(&tableMesh);
	tableNode->setShader(&tableShader);
	tableNode->setTextures(DiffuseTextureID, NormalTextureID);  // add textures
	tableNode->setColor(brown);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	rootNode->addNode(tableNode);
	
	tangramNode = new sceneNode(); // empty object
	tangramNode->setName("tangram");
	tangramNode->makeInitialModelMatrix();
	tableNode->addNode(tangramNode);

	cubeNode = new sceneNode();
<<<<<<< HEAD
	cubeNode->setName(j["nodes"]["tangram"]["cube"]["name"].as<std::string>());
	cubeNode->setIndex(j["nodes"]["tangram"]["cube"]["index"].as_int());
	cubeNode->setScalingVector(
		vector3(j["nodes"]["tangram"]["cube"]["sV"][0].as_double(),
		j["nodes"]["tangram"]["cube"]["sV"][1].as_double(),
		j["nodes"]["tangram"]["cube"]["sV"][2].as_double())
	);
	cubeNode->setTranslationVector(
		vector3 (j["nodes"]["tangram"]["cube"]["tV"][0].as_double(),
		j["nodes"]["tangram"]["cube"]["tV"][1].as_double(),
		j["nodes"]["tangram"]["cube"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["cube"]["qtrn"][3].as_double()) };
	cubeNode->setRotQtrn(q);
	cubeNode->makeInitialModelMatrix();
	cubeNode->setMesh(meshM.getMeshByName(j["nodes"]["tangram"]["cube"]["mesh"].as<std::string>()));
	cubeNode->setShader(shaderM.getShaderByName(j["nodes"]["tangram"]["cube"]["shader"].as<std::string>()));
	cubeNode->setColor(c.getColorByName(j["nodes"]["tangram"]["cube"]["color"].as<std::string>()));
	tangramNode->addNode(cubeNode);

	sTri1Node = new sceneNode();
	sTri1Node->setName(j["nodes"]["tangram"]["small_triangle_1"]["name"].as<std::string>());
	sTri1Node->setIndex(j["nodes"]["tangram"]["small_triangle_1"]["index"].as_int());
	sTri1Node->setScalingVector(
		vector3 (j["nodes"]["tangram"]["small_triangle_1"]["sV"][0].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["sV"][1].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["sV"][2].as_double())
	);
	sTri1Node->setTranslationVector(
		vector3 (j["nodes"]["tangram"]["small_triangle_1"]["tV"][0].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["tV"][1].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["tV"][2].as_double())
	);
	vector3 a(j["nodes"]["tangram"]["small_triangle_1"]["tV"][0].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["tV"][1].as_double(),
		j["nodes"]["tangram"]["small_triangle_1"]["tV"][2].as_double());
	q = { static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_1"]["qtrn"][3].as_double()) };
	sTri1Node->setRotQtrn(q);
	sTri1Node->makeInitialModelMatrix();
	sTri1Node->setMesh(meshM.getMeshByName(j["nodes"]["tangram"]["small_triangle_1"]["mesh"].as<std::string>()));
	sTri1Node->setShader(shaderM.getShaderByName(j["nodes"]["tangram"]["small_triangle_1"]["shader"].as<std::string>()));
	sTri1Node->setColor(c.getColorByName(j["nodes"]["tangram"]["small_triangle_1"]["color"].as<std::string>()));
	tangramNode->addNode(sTri1Node);

	sTri2Node = new sceneNode();
	sTri2Node->setName(j["nodes"]["tangram"]["small_triangle_2"]["name"].as<std::string>());
	sTri2Node->setIndex(j["nodes"]["tangram"]["small_triangle_2"]["index"].as_int());
	sTri2Node->setScalingVector(
		vector3 (j["nodes"]["tangram"]["small_triangle_2"]["sV"][0].as_double(),
		j["nodes"]["tangram"]["small_triangle_2"]["sV"][1].as_double(),
		j["nodes"]["tangram"]["small_triangle_2"]["sV"][2].as_double())
	);
	sTri2Node->setTranslationVector(
		vector3 (j["nodes"]["tangram"]["small_triangle_2"]["tV"][0].as_double(),
		j["nodes"]["tangram"]["small_triangle_2"]["tV"][1].as_double(),
		j["nodes"]["tangram"]["small_triangle_2"]["tV"][2].as_double()));
	q = { static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["small_triangle_2"]["qtrn"][3].as_double()) };
	sTri2Node->setRotQtrn(q);
	sTri2Node->makeInitialModelMatrix();
	sTri2Node->setMesh(meshM.getMeshByName(j["nodes"]["tangram"]["small_triangle_2"]["mesh"].as<std::string>()));
	sTri2Node->setShader(shaderM.getShaderByName(j["nodes"]["tangram"]["small_triangle_2"]["shader"].as<std::string>()));
	sTri2Node->setColor(c.getColorByName(j["nodes"]["tangram"]["small_triangle_2"]["color"].as<std::string>()));
=======
	cubeNode->setName("cube");
	cubeNode->setIndex(1);
	cubeNode->setScalingVector(vector3(1.0f, 2.0f, 1.0f));
	cubeNode->setTranslationVector(vector3(0.2f, 0.0f, 0.0f));
	cubeNode->makeInitialModelMatrix();
	cubeNode->setMesh(&cubeMesh);
	cubeNode->setShader(&cubeShader);
	cubeNode->setColor(yellow);
	tangramNode->addNode(cubeNode);

	sTri1Node = new sceneNode();
	sTri1Node->setName("small triangle 1");
	sTri1Node->setIndex(2);
	sTri1Node->setScalingVector(vector3(1.0f, 2.0f, 1.0f));
	sTri1Node->setTranslationVector(vector3(-0.2f, 0.0f, 0.2f));
	sTri1Node->makeInitialModelMatrix();
	sTri1Node->setMesh(&triangleMesh);
	sTri1Node->setShader(&sTri1Shader);
	sTri1Node->setColor(blue);
	tangramNode->addNode(sTri1Node);

	sTri2Node = new sceneNode();
	sTri2Node->setName("small triangle 2");
	sTri2Node->setIndex(3);
	sTri2Node->setScalingVector(vector3(1.0f, 2.0f, 1.0f));
	sTri2Node->setTranslationVector(vector3(0.4f, 0.0f, 0.0f));
	sTri2Node->setRotationVector(vector3(0, 1, 0));
	sTri2Node->setAngle((M_PI / 2));
	sTri2Node->makeInitialModelMatrix();
	sTri2Node->setMesh(&triangleMesh);
	sTri2Node->setShader(&sTri2Shader);
	sTri2Node->setColor(brown2);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	tangramNode->addNode(sTri2Node);

	mTriNode = new sceneNode();
<<<<<<< HEAD
	mTriNode->setName(j["nodes"]["tangram"]["medium_triangle"]["name"].as<std::string>());
	mTriNode->setIndex(j["nodes"]["tangram"]["medium_triangle"]["index"].as_int());
	mTriNode->setScalingVector(
		vector3(j["nodes"]["tangram"]["medium_triangle"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["sV"][2].as_double())
	);
	mTriNode->setTranslationVector(
		vector3(j["nodes"]["tangram"]["medium_triangle"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["medium_triangle"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["medium_triangle"]["qtrn"][3].as_double()) };
	mTriNode->setRotQtrn(q);
	mTriNode->makeInitialModelMatrix();
	mTriNode->setMesh(meshM.getMeshByName(j["nodes"]["tangram"]["medium_triangle"]["mesh"].as<std::string>()));
	mTriNode->setShader(shaderM.getShaderByName(j["nodes"]["tangram"]["medium_triangle"]["shader"].as<std::string>()));
	mTriNode->setColor(c.getColorByName(j["nodes"]["tangram"]["medium_triangle"]["color"].as<std::string>()));
=======
	mTriNode->setName("medium triangle");
	mTriNode->setIndex(4);
	mTriNode->setTranslationVector(vector3(0.40, 0.0f, 0.0f));
	mTriNode->setRotationVector(vector3(0, 1, 0));
	mTriNode->setAngle(-(3 * M_PI / 4));
	mTriNode->setScalingVector(vector3(1.4f, 2.0f, 1.4f));
	mTriNode->makeInitialModelMatrix();
	mTriNode->setMesh(&triangleMesh);
	mTriNode->setShader(&mTriShader);
	mTriNode->setColor(orange);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	tangramNode->addNode(mTriNode);
	
	lTri1Node = new sceneNode();
<<<<<<< HEAD
	lTri1Node->setName(j["nodes"]["tangram"]["large_triangle_1"]["name"].as<std::string>());
	lTri1Node->setIndex(j["nodes"]["tangram"]["large_triangle_1"]["index"].as_int());
	lTri1Node->setScalingVector(
		vector3(j["nodes"]["tangram"]["large_triangle_1"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["sV"][2].as_double())
	);
	lTri1Node->setTranslationVector(
		vector3(j["nodes"]["tangram"]["large_triangle_1"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_1"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_1"]["qtrn"][3].as_double()) };
	lTri1Node->setRotQtrn(q);
	lTri1Node->makeInitialModelMatrix();
	lTri1Node->setMesh(meshM.getMeshByName(j["nodes"]["tangram"]["large_triangle_1"]["mesh"].as<std::string>()));
	lTri1Node->setShader(shaderM.getShaderByName(j["nodes"]["tangram"]["large_triangle_1"]["shader"].as<std::string>()));
	lTri1Node->setColor(c.getColorByName(j["nodes"]["tangram"]["large_triangle_1"]["color"].as<std::string>()));
	tangramNode->addNode(lTri1Node);

	lTri2Node = new sceneNode();
	lTri2Node->setName(j["nodes"]["tangram"]["large_triangle_2"]["name"].as<std::string>());
	lTri2Node->setIndex(j["nodes"]["tangram"]["large_triangle_2"]["index"].as_int());
	lTri2Node->setScalingVector(
		vector3(j["nodes"]["tangram"]["large_triangle_2"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["sV"][2].as_double())
	);
	lTri2Node->setTranslationVector(
		vector3(j["nodes"]["tangram"]["large_triangle_2"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["large_triangle_2"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["large_triangle_2"]["qtrn"][3].as_double()) };
	lTri2Node->setRotQtrn(q);
	lTri2Node->makeInitialModelMatrix();
	lTri2Node->setMesh(meshM.getMeshByName(j["nodes"]["tangram"]["large_triangle_2"]["mesh"].as<std::string>()));
	lTri2Node->setShader(shaderM.getShaderByName(j["nodes"]["tangram"]["large_triangle_2"]["shader"].as<std::string>()));
	lTri2Node->setColor(c.getColorByName(j["nodes"]["tangram"]["large_triangle_2"]["color"].as<std::string>()));
=======
	lTri1Node->setName("large triangle 1");
	lTri1Node->setIndex(5);
	lTri1Node->setTranslationVector(vector3(0.4f, 0.0f, -0.4f));
	lTri1Node->setScalingVector(vector3(2.0f, 2.0f, 2.0f));
	lTri1Node->setRotationVector(vector3(0, 1, 0));
	lTri1Node->setAngle(M_PI);
	lTri1Node->makeInitialModelMatrix();
	lTri1Node->setMesh(&triangleMesh);
	lTri1Node->setShader(&lTri1Shader);
	lTri1Node->setColor(green);
	tangramNode->addNode(lTri1Node);

	lTri2Node = new sceneNode();
	lTri2Node->setName("large triangle 2");
	lTri2Node->setIndex(6);
	lTri2Node->setTranslationVector(vector3(-0.4f, 0.0f, -0.4f));
	lTri2Node->setScalingVector(vector3(2.0f, 2.0f, 2.0f));
	lTri2Node->setRotationVector(vector3(0, 1, 0));
	lTri2Node->setAngle(-(M_PI / 2));
	lTri2Node->makeInitialModelMatrix();
	lTri2Node->setMesh(&triangleMesh);
	lTri2Node->setShader(&lTri2Shader);
	lTri2Node->setColor(red);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	tangramNode->addNode(lTri2Node);
	
	parallNode = new sceneNode();
<<<<<<< HEAD
	parallNode->setName(j["nodes"]["tangram"]["parallelogram"]["name"].as<std::string>());
	parallNode->setIndex(j["nodes"]["tangram"]["parallelogram"]["index"].as_int());
	parallNode->setScalingVector(
		vector3(j["nodes"]["tangram"]["parallelogram"]["sV"][0].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["sV"][1].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["sV"][2].as_double())
	);
	parallNode->setTranslationVector(
		vector3(j["nodes"]["tangram"]["parallelogram"]["tV"][0].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["tV"][1].as_double(),
			j["nodes"]["tangram"]["parallelogram"]["tV"][2].as_double())
	);
	q = { static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][0].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][1].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][2].as_double()),
	 static_cast<float> (j["nodes"]["tangram"]["parallelogram"]["qtrn"][3].as_double()) };
	parallNode->setRotQtrn(q);
	parallNode->makeInitialModelMatrix();
	parallNode->setMesh(meshM.getMeshByName(j["nodes"]["tangram"]["parallelogram"]["mesh"].as<std::string>()));
	parallNode->setShader(shaderM.getShaderByName(j["nodes"]["tangram"]["parallelogram"]["shader"].as<std::string>()));
	parallNode->setColor(c.getColorByName(j["nodes"]["tangram"]["parallelogram"]["color"].as<std::string>()));
=======
	parallNode->setName("parallelogram");
	parallNode->setIndex(7);
	parallNode->setTranslationVector(vector3(-0.4f, 0.0f, 0.4f));
	parallNode->setScalingVector(vector3(1.0f, 2.0f, 1.0f));
	parallNode->makeInitialModelMatrix();
	parallNode->setMesh(&parallMesh);
	parallNode->setShader(&parallShader);
	parallNode->setColor(blue2);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	tangramNode->addNode(parallNode);


	sG.setRoot(rootNode);
}

<<<<<<< HEAD
void readJSONFile(std::string file) {
	std::cout << "\n--- Load JSON file: " << file << " ---\n";
=======
///////////////////////////////////////////////////////////////LOADS
void readJSONFile() {
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
	// Read from stream
	std::ifstream is(file);
	json j = json::parse(is);

	// Pretty print
	//std::cout << "(1)\n" << pretty_print(j) << "\n\n";

<<<<<<< HEAD
	loadCamera(file, j);
	loadMesh(file, j);
	loadShader(file, j);
	loadScene(file, j);
=======
	if (j.contains("tangram"))
	{
		std::string price = j["tangram"]["small_triangle_1"]["name"].as<std::string>();
		//std::cout << price;
	}
	else
	{
		//std::cout << "n/a";
	}
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

	std::cout << "--- Load End! ---\n";
}

void loadImage() {
	std::cout << "\n--- Load Images ---\n";
	FreeImage_Initialise(true);
	
	DiffuseTextureID = image::loadTexture("../../assets/images/noise2.png");
	NormalTextureID = image::loadTexture("../../assets/images/wood_nm1.jpg");

	FreeImage_DeInitialise();
	std::cout << "--- Load End! ---\n";
}


////////////////////////////////////////////////////////////////////////////////// CREATE SCENE
bool is_file_exist(const char *fileName)
{
	std::ifstream infile(fileName);
	//true 1, false 0
	return infile.good();
}

<<<<<<< HEAD
void createScene() {
	std::string str;

	loadImage();
	
	bool fileExist = is_file_exist("../../assets/json/savedScene.json");
	//std::cout << fileExist << "\n";
	if (fileExist == true) {
		std::cout << "\nIf you want to continues working in the saved Scene press y\n" <<
					 "If wants to start over press n" << "\n";
		std::cin >> str;
		if (str == "y") {
			fileLoaded = "../../assets/json/savedScene.json";
		}
		else {
			fileLoaded = "../../assets/json/defaultLoad.json";
		}
	}
	else {
		fileLoaded = "../../assets/json/defaultLoad.json";
	}
	readJSONFile(fileLoaded);
}
=======
void loadImage() {
	FreeImage_Initialise(true);
	
	DiffuseTextureID = image::loadTexture("../../assets/images/wood.jpg");
	NormalTextureID = image::loadTexture("../../assets/images/wood_nm1.jpg");

	FreeImage_DeInitialise();
}

>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
////////////////////////////////////////////////////////////////////////////////// INIT
void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCallbacks();
<<<<<<< HEAD
=======
	
	readJSONFile();
	loadImage();
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

	createScene();
}

int main(int argc, char* argv[])
{
	init(argc, argv);	
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////