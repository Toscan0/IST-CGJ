#include "sceneNode.h"

sceneNode::sceneNode() {}

void sceneNode::setModelMatrixAux(const matrix4x4 &modelMatrixAux) {
	_modelMatrixAux = modelMatrixAux;
}

const matrix4x4 sceneNode::getModelMatrixAux() {
	return _modelMatrixAux;
}

void sceneNode::setModelMatrix(const matrix4x4 &modelMatrix) {
	_modelMatrix = modelMatrix;
	// if is a parent node you need to updated the model matrix of his sons
	for (int i = 0; i < _nodes.size(); i++) {
		sceneNode* nextNode = _nodes[i];
		nextNode->setModelMatrix(modelMatrix *  nextNode->getModelMatrixAux());
	}
}

const matrix4x4 sceneNode::getModelMatrix() {
	return _modelMatrix;
}

void sceneNode::setMesh(mesh* m) {
	_mesh = m;
}

const mesh* sceneNode::getMesh() {
	return _mesh;
}

void sceneNode::setShader(shader* s) {
	_shader = s;
}

const shader* sceneNode::getShader() {
	return _shader;
}

void sceneNode::setName(std::string name) {
	_name = name;
}

const std::string sceneNode::getName() {
	return _name;
}


void sceneNode::addNode(sceneNode* node) {
	node->setModelMatrix(_modelMatrix * node->getModelMatrix());
	_nodes.push_back(node);
}

const std::vector<sceneNode*> sceneNode::getNodes() {
	return _nodes;
}

void sceneNode::draw(camera& cam) {
	if (_mesh != nullptr) {
		_mesh->draw(_modelMatrix, *_shader, cam);
	}
	for (int i = 0; i < _nodes.size(); i++) {
		sceneNode* nextNode = _nodes[i];
		matrix4x4 nextNodeModelMatrix = nextNode->getModelMatrix();
		nextNode->draw(cam);
	}
	
}