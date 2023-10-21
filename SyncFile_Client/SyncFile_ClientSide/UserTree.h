#pragma once
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stack>
#include "User.h"

using namespace std;

class UserTree
{
private:
	struct Node
	{
		User user;
		Node* left;
		Node* right;
		Node() : left(NULL), right(NULL)
		{}
		Node(User user) : user(user), left(NULL), right(NULL)
		{}
	};
	Node* root;
	//Recursive Method
	Node* _insert(Node* root, User user, bool& isInserted);
	Node* _remove(Node* root, User user, bool& isRemoved);
	int _height(Node* root);
	Node* _search(Node* root, User user);
	Node* _leftRotate(Node* root);
	Node* _rightRotate(Node* root);
	Node* minimum(Node* root);
	Node* maximum(Node* root);
	void inOrderTraversal(Node* root);
	int getBalanceFactor(Node* root);
public:
	//Default Constructor
	UserTree();
	//Setter
	void setRoot(Node* root);
	//Methods
	bool insert(User user);
	bool remove(User user);
	int height();
	bool search(User user);
	User getUser(User user);
	void print();
	int balanceFactor();
};