#pragma once
#include "User.h"

using namespace std;

class UserStack
{
private:
	struct Node
	{
		User user;
		Node* next;
		Node() : next(NULL)
		{}
		Node(User user) : user(user), next(NULL)
		{}
	};
	Node* _top;
	int _size;
public:
	//Constructor
	UserStack();
	//Methods
	bool isEmpty();
	void push(User user);
	void pop();
	User top();
	int size();
};