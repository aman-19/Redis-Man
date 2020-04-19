#include <unordered_map>
#include <vector>
#include "Node.hpp"

#ifndef AVLTree_H
#define AVLTree_H
class AVLTree{
	Node *root;

	std::unordered_map<std::string, double> ht;

	void rectifyOrd(Node *N, bool flag);

	Node* balanceNode(Node *N, double &score, std::string &value);
	Node* min_node(Node* N);
	Node* insert_node(Node* N, double &score, std::string &value, Node *pred, Node *suc);
	Node* delete_node(Node* N, double &score, std::string &value);
	Node* Make(std::vector<std::string> &data, int st, int en, Node **last);

public:
	AVLTree();

	unsigned int size();

	Node* Index(int x);

	void insert(double score, std::string value);
	void erase(double score, std::string value);

	int rank(std::string value);

	void sRange(int st, int en, std::vector<std::string> &v);
	void recMake(std::vector<std::string> &data);

	~AVLTree();	
};
#endif