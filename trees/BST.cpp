#include <iostream>
#include <queue>
#include <stack>

class Node {
public:
	Node()  :val{}
		,left{nullptr}
		,right{nullptr} { }
	Node(int val) 
		: val{val} 
		, left{nullptr}
		, right{nullptr} { }
	Node(int val, Node* right, Node* left) 
		: val{val}
		, left{left}
		, right{right} { }
	~Node() {
		val = 0;
		delete left;
		delete right;
	}
	int val;
	Node* left;
	Node* right;
};

void inTraverse(Node* root) {
	if (!root) { return; }
	inTraverse(root->left);
	std::cout << root->val << " ";
	inTraverse(root->right);
}

void inTraverseIt(Node* root) {
	std::stack<Node*> s;
	Node* current = root;
	while (current != nullptr || !s.empty()) {
		while (current) {
			s.push(current);
			current = current->left;
		}
		current = s.top();
		s.pop();
		std::cout << current->val << " ";
		current = current->right;
	}
}

void preTraverse(Node* root) {
	if(!root) { return; }
	std::cout << root->val << " ";
	preTraverse(root->left);
	preTraverse(root->right);
}
void postTraverse(Node* root) {
	if(!root) { return; }
	postTraverse(root);
	postTraverse(root);
	std::cout << root->val << " ";
}

void levelOrder(Node* root) {
	std::queue<Node*> qu;
	qu.push(root);
	int size = qu.size();
	while (!qu.empty()) {
		for (int i = 0; i < size; ++i) {
			Node* tmp = qu.front();
			std::cout << tmp->val << " ";
			qu.pop();
			if (tmp->left) {
				qu.push(tmp->left);
			}
			if (tmp->right) {
				qu.push(tmp->right);
			}
		}
		size = qu.size();
		std::cout << '\n';
	}

}

void insert1(Node* root,int key) {
	Node* node = new Node(key);
	Node* y = nullptr;
	while(root) {
		y = root;
		if (key < root->val) {
			root = root->left;
		} else {
			root = root->right;
		}
	}
	if (!y) {
		root = node;
	} else if (key < y->val) {
		y->left = node;
	} else {
		y->right = node;
	}
}

Node* insert2(Node* root, int val) {
	if (!root) {
		return new Node(val);
	}
	if (root->val > val) {
		root->left = insert2(root->left,val);
	}
	else {
		root->right = insert2(root->right,val);
	}
	return root;
}

Node* getMin(Node* root) {
	while(root && root->left) {
		root = root->left;
	}
	return root;	
}

Node* getMax(Node* root) {
	while(root && root->right) {
		root = root->right;
	}
	return root;
}

Node* search(Node* root, int key) {
    if (!root || root->val == key) { return root; }
    if (root->val > key) { return search(root->left, key); }
    else { return search(root->right, key); }
}

int getHeight(Node* node) {
    if (!node || !(node->right) && !(node->left)) { return 0; }
    return std::max(getHeight(node->left),getHeight(node->right)) + 1;
}

Node* Delete1(Node* node, int key) {
	if (!node) { return nullptr; }
	if (node->val < key) {
		node->right = Delete1(node->right,key);
	} 
	else if (node->val > key) {
		node->left = Delete1(node->left,key);
	}
	else { 
		if (!node->left) {
			Node* tmp = node->right;
			delete node;
			return tmp;
		}
		else if (!node->right) {
			Node* tmp = node->left;
			delete node;
			return tmp;
		}
		else {
			Node* tmp = getMax(node->left);
			node->val = tmp->val;
			node->left = Delete1(node->left,tmp->val);
		}
	}
	return node;
}

Node* Delete2(Node* root, int val) {
	if (!root) {
		return root;
	}
	if (root->val > val) {
		root->left = Delete2(root->left,val);
	} else if (root->val < val) {
		root->right = Delete2(root->right,val);
	} else {
		if (!root->right) {
			Node* tmp = root->left;
			delete root;
			return tmp;
		} else if (!root->left) {
			Node* tmp = root->right;
			delete root;
			return tmp;
		} else {
			Node* tmp = getMin(root->right);
			root->val = tmp->val;
			root->right = Delete2(root->right, tmp->val);
		}
	}
	return root;

}

Node* getSuccessor(Node* root, Node* node) {
	if (!node) {
		return nullptr;
	}
	if (node->right) {
		return getMin(node->right);
	}
	Node* successor = nullptr;
	Node* ancestor = root;
	while (ancestor != node) {
		if (ancestor->val > node->val) {
			successor = ancestor;
			ancestor = ancestor->left;
		} else {
			ancestor = ancestor->right;
		} 
	}
	return successor;
}

Node* getPredecessor(Node* root, Node* node) {
	if (!node) {
		return nullptr;
	}
	if (node->left) {
		return getMax(node->left);
	}
	Node* predecessor = nullptr;
	Node* ancestor = root; 
	while (ancestor != node) {
		if (ancestor->val < node->val) {
			predecessor = ancestor;
			ancestor = ancestor->right;
		} else {
			ancestor = ancestor->left;
		}
	}
	return predecessor;
}

int main() {
	Node* root = new Node(15);
	insert1(root,44);
	insert1(root,1);
	insert1(root,3);
	insert1(root,36);
	insert1(root,56);
	insert1(root,5);
	insert1(root,12);
	insert1(root,8);
	Node* n1 = search(root,3);
	std::cout << "3 suc: "<< getSuccessor(root,n1)->val << std::endl;

	Node* n2 = search(root,36);
	std::cout << "36 suc: "<<getSuccessor(root,n2)->val << std::endl;


	Delete2(root,15);

	Node* n3 = search(root,12);

	std::cout << " suc 12 :" << getSuccessor(root,n3)->val << std::endl;


	//levelOrder(root);

	//inTraverse(root);
	//std::cout << std::endl;
	//Delete(root,14);
	//inTraverse(root);
	//std::cout << getMin(root)->val;
//	preTraverse(root);
//	std::cout << getMin(root)->val << std::endl;
//	std::cout << getMax(root)->val << std::endl;
	
}
