#include <iostream>
#include "Tree.h"

using namespace std;

//Implementing Constructor
Tree::Tree()
{
	this->root = NULL;
}

//Implementing Setter
void Tree::setRoot(Node* root)
{
	this->root = root;
}

//Implementing Methods
bool Tree::insert(int val)
{
	bool isInserted = false;
	root = _insert(root, val, isInserted);
	if (isInserted)
		return true;
	return false;
}
bool Tree::remove(int val)
{
	bool isRemoved = false;
	root = _remove(root, val, isRemoved);
	if (isRemoved)
		return true;
	return false;
}
int Tree::height()
{
	return _height(root);
}
bool Tree::search(int val)
{
	if (!_search(root, val))
		return false;
	return true;
}
void Tree::print()
{
	cout << "Tree Keys : " << endl;
	inOrderTraversal(root);
	cout << endl;
}
int Tree::balanceFactor()
{
	return getBalanceFactor(root);
}

//Implementing Recursive Methods
Tree::Node* Tree::_insert(Node* root, int val, bool& isInserted)
{
	if (root == NULL)
	{
		isInserted = true;
		return new Node(val);
	}
	else if (val < root->data)
		root->left = _insert(root->left, val, isInserted);
	else if (val > root->data)
		root->right = _insert(root->right, val, isInserted);
	else
	{
		cout << "Duplicate Records Not Allowed!";
		isInserted = false;
		return root;
	}
	int bfactor = getBalanceFactor(root);
	if (bfactor > 1 && val < root->left->data)
	{
		cout << "RR" << endl;
		return _rightRotate(root);
	}
	else if (bfactor < -1 && val > root->right->data)
	{
		cout << "LL" << endl;
		return _leftRotate(root);
	}
	else if (bfactor > 1 && val > root->left->data)
	{
		cout << "LR" << endl;
		root->left = _leftRotate(root->left);
		return _rightRotate(root);
	}
	else if (bfactor < -1 && val < root->right->data)
	{
		cout << "RL" << endl;
		root->right = _rightRotate(root->right);
		return _leftRotate(root);
	}
	return root;
}
Tree::Node* Tree::_remove(Node* root, int val, bool& isRemoved)
{
	if (root == NULL)
	{
		isRemoved = false;
		return NULL;
	}
	else if (val < root->data)
		root->left = _remove(root->left, val, isRemoved);
	else if (val > root->data)
		root->right = _remove(root->right, val, isRemoved);
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			isRemoved = true;
			delete(root);
			return NULL;
		}
		else if (root->left != NULL && root->right != NULL)
		{
			Node* temp = minimum(root->left);
			root->data = temp->data;
			root->right = _remove(root->left, temp->data, isRemoved);
		}
		else
		{
			Node* toDel = root;
			if (root->right == NULL)
				root = root->left;
			if (root->left == NULL)
				root = root->right;
			delete(toDel);
			isRemoved = true;
			return root;
		}
	}
	int bfactor = getBalanceFactor(root);
	if (bfactor == 2 && getBalanceFactor(root->left) >= 0)
	{
		cout << "RR" << endl;
		return _rightRotate(root);
	}
	else if (bfactor == 2 && getBalanceFactor(root->left) == -1)
	{
		cout << "LR" << endl;
		root->left = _leftRotate(root->left);
		return _rightRotate(root);
	}
	else if (bfactor == -2 && getBalanceFactor(root->right) <= 0)
	{
		cout << "LL" << endl;
		return _leftRotate(root);
	}
	else if (bfactor == -2 && getBalanceFactor(root->right) == 1)
	{
		cout << "RL" << endl;
		root->right = _rightRotate(root->right);
		return _leftRotate(root);
	}
	return root;
}
int Tree::_height(Node* root)
{
	if (root == NULL)
		return -1;
	else
	{
		int lHeight = _height(root->left);
		int RHeight = _height(root->right);
		if (lHeight > RHeight)
			return lHeight + 1;
		else
			return RHeight + 1;
	}
}
Tree::Node* Tree::_search(Node* root, int val)
{
	if (root == NULL || root->data == val)
		return root;
	else if (val < root->data)
		return _search(root->left, val);
	else
		return _search(root->right, val);
}
Tree::Node* Tree::_leftRotate(Node* root)
{
	Node* y = root->right;
	Node* T2 = y->left;
	y->left = root;
	root->right = T2;
	return y;
}
Tree::Node* Tree::_rightRotate(Node* root)
{
	Node* x = root->left;
	Node* T2 = x->right;
	x->right = root;
	root->left = T2;
	return x;
}
Tree::Node* Tree::minimum(Node* root)
{
	while (root->left != NULL)
		root = root->left;
	return root;
}
Tree::Node* Tree::maximum(Node* root)
{
	while (root->right != NULL)
		root = root->right;
	return root;
}
void Tree::inOrderTraversal(Node* root)
{
	if (root == NULL)
		return;
	inOrderTraversal(root->left);
	cout << root->data << " ";
	inOrderTraversal(root->right);
}
int Tree::getBalanceFactor(Node* root)
{
	if (root == NULL)
		return -1;
	return _height(root->left) - _height(root->right);
}