#include "Node.hpp"

Node::Node(){
}

Node::Node(double s, std::string x){
	score = s;
	val = x;

	count = 1;
	height = 1;

	left = right = pred = suc = nullptr;
}

int Node::getHeight(){
	return height;
}

int Node::HeightDiff(){
	return (left? left ->getHeight(): 0) - (right? right ->getHeight(): 0);
}

unsigned int Node::size(){
	return count;
}

void Node::update(){
	height = std::max(left? left ->getHeight(): 0, right? right ->getHeight(): 0) + 1;
	count = (left? left ->size():0) + (right? right ->size(): 0) + 1;
}

Node* Node::rightRotate(){
	Node *leftSub = left;
	Node *rightSub = leftSub ->right;

	left = rightSub;
	leftSub ->right = this;

	update();

	leftSub ->update();

	return leftSub;
}

Node* Node::leftRotate(){
	Node *rightSub = right;
	Node *leftSub = rightSub ->left;

	right = leftSub;
	rightSub ->left = this;

	update();

	rightSub ->update();

	return rightSub;
}

Node::~Node(){
	delete(left);
	delete(right);
}