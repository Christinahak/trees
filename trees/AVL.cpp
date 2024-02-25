#include <iostream>

class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node() : val{0}, left{nullptr}, right{nullptr} {}
	Node(int v) : val{v}, left{nullptr}, right{nullptr} {}
};

void inTraverse(Node* root) {
	if (!root) { return; }
	inTraverse(root->left);
	std::cout << root->val << " ";
	inTraverse(root->right);
}

void preTraverse(Node* root) {
	if (!root) { return; }
	preTraverse(root->left);
	std::cout << root->val; << " ";
	preTraverse(root->right);
}

void postTraverse(Node* root) {
	if (!root) { return; }
	postTraverse(root->left);
	postTraverse(root->right);
	std::cout << root->val << " ";
}

Node* search(int key, Node* root) {
	if (!root || root->val == key) { return root; }
	if (root->val > key) { return search(key,root->left); }
	else { return search(key,root->right); }
}

int getHeight(Node* node, int sum = 0) {
	if (!node) { return -1; }
	return std::max(getHeight(node->left),getHeight(node->right)) + 1;
}

Node* getMin(Node* root) {
	if (!root || !root->left) { return root; }
	return getMin(root->left);
}

Node* getSuccessor(Node* root, Node* node) {
	if (!node) { return nullptr; }
	if (node->right) { 
		return getMin(node->right); 
	}
	Node* ancestor = root;
	Node* successor = nullptr;
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
	if (!node) { return nullptr; }
	if (node->left) { return getMax(node->left);}
	Node* ancestor = root;
	Node* predecessor = nullptr;
	while(node != ancestor) {
		if (ancestor->val < node->val) {
			predecessor = ancestor;
			ancestor = ancestor->right;
		} else {
			ancestor = ancestor->left;
		}
	}
	return predecessor;
}

int getBalanceFactor(Node* root) {
	return (getHeight(root->left) - getHeight(root->right));
}

Node* leftRotate(Node* root) { //rr
	Node* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	return tmp;
}

Node* rightRotate(Node* root) {
	Node* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	return tmp;
}

Node* insert(Node* root, int key) {
	if (!root) {
		return new Node(key);
	}
	if (root->val > key) {
		root->left = insert(root->left,key);
	} else {
		root->right = insert(root->right,key);
	}
	int bf = getBalanceFactor(root);
	if (bf < -1 && key < root->right->val) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	if (bf < -1 && key > root->right->val) {
		return leftRotate(root);
	}
	if (bf > 1 && key > root->left->val) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (bf > 1 && key < root->left->val) {
		return rightRotate(root);
	}
	return root;
}


Node* Delete(Node* root, int key) {
	if (!root) { return nullptr; }
	if (root->val < key) {
		root->right = Delete(root->right,key);
	} 
	else if (root->val > key) {
		root->left = Delete(root->left,key);
	}
	else { 
		if (!root->left) {
			Node* tmp = root->right;
			delete root;
			return tmp;
		}
		if (!root->right) {
			Node* tmp = root->left;
			delete root;
			return tmp;
		}
		else {
			Node* tmp = getMax(root->left);
			root->val = tmp->val;
			root->left = Delete(root->left,tmp->val);
		}
	}
	int bf = getBalanceFactor(root);
	if (bf < -1 && key < root->right->val) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	if (bf < -1 && key > root->right->val) {
		return leftRotate(root);
	}
	if (bf > 1 && key > root->left->val) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (bf > 1 && key < root->left->val) {
		return rightRotate(root);
	}
	return root;
}

