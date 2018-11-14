#include "sceneNode.h"

sceneNode::sceneNode() {}

void sceneNode::setModelMatrix(const matrix4x4 &modelMatrix) {
	_modelMatrix = modelMatrix;
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

void sceneNode::addNode(sceneNode* node) {
	_nodes.push_back(node);
}

const std::vector<sceneNode*> sceneNode::getNodes() {
	return _nodes;
}

void sceneNode::draw(const matrix4x4& modelMatrix, camera& cam) {
	if (_mesh != nullptr) {
		_mesh->draw(modelMatrix * modelMatrix, *_shader, cam);
	}
	for (int i = 0; i < _nodes.size(); i++) {
		sceneNode* nextNode = _nodes[i];
		mesh nextNodeMesh = *(nextNode->getMesh());
		matrix4x4 nextNodeModelMatrix = nextNode->getModelMatrix();
		shader nextNodeShader = *(nextNode->getShader());
		nextNodeMesh.draw(modelMatrix * nextNodeModelMatrix, nextNodeShader, cam);
		/*if (nextNode->getNodes().size > 0) {
			sceneNode* nextNextNode = _nodes[i];
			mesh nextNextNodeMesh = *(nextNextNode->getMesh());
			matrix4x4 nextNextNodeModelMatrix = nextNextNode->getModelMatrix();
			shader nextNextNodeShader = *(nextNextNode->getShader());
			nextNextNodeMesh.draw(nextNextNodeModelMatrix, nextNextNodeShader, cam);
		}*/
	}
	
}