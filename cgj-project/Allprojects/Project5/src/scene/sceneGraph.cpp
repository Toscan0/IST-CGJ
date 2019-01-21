#include "sceneGraph.h"

sceneGraph::sceneGraph() {}

sceneGraph::sceneGraph(camera* camera) {
	this->setCamera(camera);
}

void sceneGraph::setCamera(camera* c) {
	_camera = c;
}

camera* sceneGraph::getCamera() {
	return _camera;
}

<<<<<<< HEAD
=======
/*void sceneGraph::setShader(shader* s) {
	_shader = s;
}
shader* sceneGraph::getShader() {
	return _shader;
}*/

>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
void sceneGraph::setRoot(sceneNode *r) {
	_root = r;
}

sceneNode* sceneGraph::getRoot() {
	return _root;
}

const GLuint sceneGraph::getIndex() {
	return _index;
}

void sceneGraph::setIndex(GLuint index) {
	_index = index;
}

sceneNode* sceneGraph::getNodeSelected() {
	return _nodeSelected;
}

void sceneGraph::setNodeSelected(sceneNode* nodeSelected) {
	_nodeSelected = nodeSelected;
}

void sceneGraph::draw() {
	_root->draw(*_camera, _index);
<<<<<<< HEAD
	_root->drawPicked(*_camera, _index);
=======
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
}