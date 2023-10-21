#pragma once

using namespace std;

class Tree
{
private:
	struct Node
	{
		int data;
		Node* left;
		Node* right;
		Node() : data(0), left(NULL), right(NULL)
		{}
		Node(int data) : data(data), left(NULL), right(NULL)
		{}
	};
	Node* root;
	//Recursive Method
	Node* _insert(Node* root, int val, bool& isInserted);
	Node* _remove(Node* root, int val, bool& isRemoved);
	int _height(Node* root);
	Node* _search(Node* root, int val);
	Node* _leftRotate(Node* root);
	Node* _rightRotate(Node* root);
	Node* minimum(Node* root);
	Node* maximum(Node* root);
	void inOrderTraversal(Node* root);
	int getBalanceFactor(Node* root);
public:
	//Default Constructor
	Tree();
	//Setter
	void setRoot(Tree::Node* root);
	//Methods
	bool insert(int val);
	bool remove(int val);
	int height();
	bool search(int val);
	void print();
	int balanceFactor();
};