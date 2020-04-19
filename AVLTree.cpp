#include "AVLTree.hpp"

void AVLTree::rectifyOrd(Node *N, bool flag = true){
	if(flag){
		if(N ->pred)
			N ->pred ->suc = N ->suc;
		if(N ->suc)
			N ->suc ->pred = N ->pred;
	}
	else{
		if(N ->pred)
			N ->pred ->suc = N;
		if(N ->suc)
			N ->suc ->pred = N;
	}
}

Node* AVLTree::balanceNode(Node *N, double &score, std::string &value){
	int balance = N ->HeightDiff();

	if(balance > 1){
		if(N ->left && N ->left ->HeightDiff() < 0)
			N ->left = N ->left ->leftRotate();

		return N ->rightRotate();
	}

	else if(balance < -1){
		if(N ->right && N ->right ->HeightDiff() > 0)
			N ->right = N ->right ->rightRotate();

		return N ->leftRotate();
	}

	return N;
}

Node* AVLTree::min_node(Node* N){
	Node* cur = N;

	while(cur ->left != nullptr)
		cur = cur ->left;

	return cur;
}

Node* AVLTree::insert_node(Node* N, double &score, std::string &value, Node *pred, Node *suc){
	if(N == nullptr){
		Node *temp = new Node(score, value);
		temp ->pred = pred;
		temp ->suc = suc;

		rectifyOrd(temp, false);
		return temp;
	}

	if(score < N ->score || (score == N ->score && value < N ->val))
		N ->left = insert_node(N ->left, score, value, pred, N);

	else if(score > N ->score || (score == N ->score && value > N ->val))
		N ->right = insert_node(N ->right, score, value, N, suc);

	N ->update();
	
	return balanceNode(N, score, value);
}

Node* AVLTree::delete_node(Node* N, double &score, std::string &value){
	if(N == nullptr)
		return N;

	if(score < N ->score || (score == N ->score && value < N ->val))
		N ->left = delete_node(N ->left, score, value);

	else if(score > N ->score || (score == N ->score && value > N ->val))
		N ->right = delete_node(N ->right, score, value);

	else{
		if(N ->right == nullptr || N ->left == nullptr){
			Node *temp = N ->left? N ->left : N ->right;

			if(temp == nullptr){
				temp = N;
				N = nullptr;
			}
			else{
				rectifyOrd(N);
				N ->left = N ->right = nullptr;

				std::swap(N, temp);
			}

			delete(temp);
		}
		else{
			Node* temp = min_node(N ->right);

			N ->val = temp ->val;
			N ->score = temp ->score;

			N ->right = delete_node(N ->right, N ->score, N ->val);
		}
	}

	if(N == nullptr)
		return N;

	N ->update();

	return balanceNode(N, score, value);
}

Node* AVLTree::Make(std::vector<std::string> &data, int st, int en, Node **last){
	if(en < st)
		return nullptr;

	int mid = (st + en)/2;
	mid += mid%2;

	Node *temp = new Node(stod(data[mid]), data[mid+1]);

	temp ->left = Make(data, st, mid-1, last);

	if(*last){
		(*last) ->suc = temp;
		temp ->pred = (*last);
	}

	(*last) = temp;

	temp ->right = Make(data, mid+2, en, last);

	temp ->update();

	ht[temp ->val] = temp ->score;
}

Node* AVLTree::Index(int x){
	++x;
	int c;

	Node *temp = root;

	while(x && temp){
		c = 0;

		if(temp ->left)
			c = temp ->left ->size();

		if(c >= x)
			temp = temp ->left;
		else if(c+1 == x)
			return temp;
		else{
			x -= c+1;
			temp = temp ->right;
		}
	}

	return temp;
}

AVLTree::AVLTree(){
	root = nullptr;
}

unsigned int AVLTree::size(){
	return root? root ->size(): 0;
}

void AVLTree::insert(double score, std::string value){
	if(ht.count(value))
		erase(ht[value], value);

	ht[value] = score;
	root = insert_node(root, score, value, nullptr, nullptr);
}

void AVLTree::erase(double score, std::string value){
	if(ht.count(value)){
		root = delete_node(root, score, value);
		ht.erase(value);
	}
}

int AVLTree::rank(std::string value){
	if(ht.count(value) == 0)
		return -1;

	Node *temp = root;

	double score = ht[value];

	int pos = 0;

	while(temp && (temp ->score != score || temp ->val != value)){
		if(temp ->score > score || (temp ->score == score && temp ->val > value))
			temp = temp ->left;
		else{
			++pos;
			if(temp ->left)
				pos += temp ->left ->size();

			temp = temp ->right;
		}
	}

	if(temp == root){
		if(temp ->left)
			pos += temp ->left ->size();
	}

	return pos;
}

void AVLTree::sRange(int st, int en, std::vector<std::string> &v){
	Node *temp = Index(st);

	while(st++ <= en && temp){
		v.push_back(temp ->val);

		temp = temp ->suc;
	}
}

void AVLTree::recMake(std::vector<std::string> &data){
	if(root)
		return;

	Node *last;

	root = Make(data, 0, data.size()-1, &last);
}

AVLTree::~AVLTree(){
	delete(root);
	ht.clear();
}