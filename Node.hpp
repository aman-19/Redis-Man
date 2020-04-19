#include <string>

#ifndef NODE_H
#define NODE_H
class Node{
public:
	int height;
	unsigned int count;
	double score;
	std::string val;
	Node *left, *right, *pred, *suc;

	Node();
	Node(double s, std::string x);

	int getHeight();
	int HeightDiff();

	unsigned int size();

	void update();

	Node *rightRotate();

	Node *leftRotate();

	~Node();
};
#endif