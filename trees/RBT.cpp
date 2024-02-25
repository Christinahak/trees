#include <iostream>

enum class COLOR { RED, BLACK };
class Node {
public:
	Node() 
		: left{nullptr}
		, right{nullptr}
		, parent{nullptr}
		, m_val{}
	        , m_color{COLOR::RED}
		{}
	Node(int key) 
		: m_val(key)
		, left {nullptr}
		, right {nullptr}
		, parent {nullptr}
		, m_color {COLOR::RED}
		{}
	Node* left;
	Node* right;
	Node* parent;
	int m_val;
	COLOR m_color;
};

class RBT {
public:
	RBT();
	void insert(Node* node);	
private:
	void leftRotate(Node* node);
	void rightRotate(Node* node);
	void insertFixUp(Node* node);
	Node* nil;
	Node* root;
};

RBT::RBT() 
	: nil{new Node(0)}
	, root {new Node(0)}
	{
		nil->m_color = COLOR::BLACK;
		root->m_color = COLOR::RED;
	}

void RBT::leftRotate(Node* x) {
	Node* y = x->right;
	x->right = y->left;
	if (y->left != nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nil) {
		y->m_color = COLOR::BLACK;
		root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	x->parent = y;
	y->left = x;
}

void RBT::rightRotate(Node* x) {
	Node* y = x->left;
	x->left = y->right;
	if (y->right != nil) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nil) {
		y->m_color = COLOR::BLACK;
		root = y;
	} else if ( x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	x->parent = y;
	y->right = x;
}

void RBT::insert(Node* node) {
	Node* y = nil;
	Node* x = root;
	while (x != nil) {
		y = x;
		if (node->m_val < x->m_val) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	node->parent = y;
	if (y == nil) {
		node->m_color = COLOR::BLACK;
		root = node;
	} else if (node->m_val < y->m_val) {
		y->left = node;
	} else {
		y->right = node;
	}
	if (node->parent->parent == nil) {
		return;  //nothing should be fixed here
	}
	insertFixUp(node);
}


void RBT::insertFixUp(Node* z) {
	while (z->parent->m_color == COLOR::RED) {
		if (z->parent == z->parent->parent->left) {
			Node* uncle = z->parent->parent->right;
			if (uncle->m_color == COLOR::RED) {
				z->parent->m_color = COLOR::BLACK;
				uncle->m_color = COLOR::BLACK;
				z->parent->parent->m_color = COLOR::RED;
				z = z->parent->parent;
			}
			else {
				if (z = z->parent->right) {
					z = z->parent;
					leftRotate(z);
				}
				z->parent->m_color = COLOR::BLACK;
				z->parent->parent->m_color = COLOR::RED;
				rightRotate(z->parent->parent);
			}
		}
		else { 
			Node* uncle = z->parent->parent->left;
			if (uncle->m_color == COLOR::RED) {
				z->parent->m_color = COLOR::BLACK;
				uncle->m_color = COLOR::BLACK;
				z->parent->parent->m_color = COLOR::RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);
				}
				z->parent->m_color = COLOR::BLACK;
				z->parent->parent->m_color = COLOR::RED;
				leftRotate(z->parent->parent);
			}
		}
		root->m_color = COLOR::BLACK;
	}

}


