#include <iostream>
#include <conio.h>
#include "UserTree.h"

using namespace std;

//Implementing Constructor
UserTree::UserTree()
{
	this->root = NULL;
}

//Implementing Setter
void UserTree::setRoot(Node* root)
{
	this->root = root;
}

//Implementing Methods
bool UserTree::insert(User user)
{
	bool isInserted = false;
	root = _insert(root, user, isInserted);
	if (isInserted)
		return true;
	return false;
}
bool UserTree::remove(User user)
{
	bool isRemoved = false;
	root = _remove(root, user, isRemoved);
	if (isRemoved)
		return true;
	return false;
}
int UserTree::height()
{
	return _height(root);
}
bool UserTree::search(User user)
{
	if (!_search(root, user))
		return false;
	return true;
}
User* UserTree::getUser(User user)
{
	Node* searched = _search(root, user);
	if (!searched)
		return new User();
	else
		return &(searched->user);
}
void UserTree::print()
{
	cout << "Tree Keys : " << endl;
	inOrderTraversal(root);
	cout << endl;
}
int UserTree::balanceFactor()
{
	return getBalanceFactor(root);
}

//Implementing Recursive Methods
UserTree::Node* UserTree::_insert(Node* root, User user, bool& isInserted)
{
	if (root == NULL)
	{
		isInserted = true;
		return new Node(user);
	}
	else if (user.getID() < root->user.getID())
		root->left = _insert(root->left, user, isInserted);
	else if (user.getID() > root->user.getID())
		root->right = _insert(root->right, user, isInserted);
	else
	{
		cout << "Duplicate Records Not Allowed!" << endl;
		isInserted = false;
		return root;
	}
	int bfactor = getBalanceFactor(root);
	if (bfactor > 1 && user.getID() < root->left->user.getID())
	{
		//cout << "RR" << endl;
		return _rightRotate(root);
	}
	else if (bfactor < -1 && user.getID() > root->right->user.getID())
	{
		//cout << "LL" << endl;
		return _leftRotate(root);
	}
	else if (bfactor > 1 && user.getID() > root->left->user.getID())
	{
		//cout << "LR" << endl;
		root->left = _leftRotate(root->left);
		return _rightRotate(root);
	}
	else if (bfactor < -1 && user.getID() < root->right->user.getID())
	{
		//cout << "RL" << endl;
		root->right = _rightRotate(root->right);
		return _leftRotate(root);
	}
	return root;
}
UserTree::Node* UserTree::_remove(Node* root, User user, bool& isRemoved)
{
	if (root == NULL)
	{
		isRemoved = false;
		return NULL;
	}
	else if (user.getID() < root->user.getID())
		root->left = _remove(root->left, user, isRemoved);
	else if (user.getID() > root->user.getID())
		root->right = _remove(root->right, user, isRemoved);
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
			root->user = temp->user;
			root->right = _remove(root->left, temp->user, isRemoved);
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
		//cout << "RR" << endl;
		return _rightRotate(root);
	}
	else if (bfactor == 2 && getBalanceFactor(root->left) == -1)
	{
		//cout << "LR" << endl;
		root->left = _leftRotate(root->left);
		return _rightRotate(root);
	}
	else if (bfactor == -2 && getBalanceFactor(root->right) <= 0)
	{
		//cout << "LL" << endl;
		return _leftRotate(root);
	}
	else if (bfactor == -2 && getBalanceFactor(root->right) == 1)
	{
		//cout << "RL" << endl;
		root->right = _rightRotate(root->right);
		return _leftRotate(root);
	}
	return root;
}
int UserTree::_height(Node* root)
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
UserTree::Node* UserTree::_search(Node* root, User user)
{
	if (root == NULL || root->user.getID() == user.getID())
		return root;
	else if (user.getID() < root->user.getID())
		return _search(root->left, user);
	else
		return _search(root->right, user);
}
UserTree::Node* UserTree::_leftRotate(Node* root)
{
	Node* y = root->right;
	Node* T2 = y->left;
	y->left = root;
	root->right = T2;
	return y;
}
UserTree::Node* UserTree::_rightRotate(Node* root)
{
	Node* x = root->left;
	Node* T2 = x->right;
	x->right = root;
	root->left = T2;
	return x;
}
UserTree::Node* UserTree::minimum(Node* root)
{
	while (root->left != NULL)
		root = root->left;
	return root;
}
UserTree::Node* UserTree::maximum(Node* root)
{
	while (root->right != NULL)
		root = root->right;
	return root;
}
void UserTree::inOrderTraversal(Node* root)
{
	if (root == NULL)
		return;
	inOrderTraversal(root->left);
	root->user.printUserData();
	inOrderTraversal(root->right);
}
int UserTree::getBalanceFactor(Node* root)
{
	if (root == NULL)
		return -1;
	return _height(root->left) - _height(root->right);
}
void UserTree::saveUsers()
{
	ofstream userRecordOut("UserRecord.dat", ios::trunc | ios::binary | ios::out);
	if (userRecordOut.is_open())
	{
		stack<Node*> st;
		Node* curr = root;
		while (curr != NULL || !st.empty())
		{
			if (curr != NULL)
			{
				st.push(curr);
				curr = curr->left;
			}
			else
			{
				curr = st.top();
				st.pop();
				if (curr != NULL)
				{
					string uName = curr->user.getUserName();
					string uPass = curr->user.getPassword();
					int nameLen = (int)uName.length();
					int passLen = (int)uPass.length();
					userRecordOut.write(reinterpret_cast<char*>(&nameLen), sizeof(int));
					userRecordOut.write(uName.c_str(), nameLen);
					userRecordOut.write(reinterpret_cast<char*>(&passLen), sizeof(int));
					userRecordOut.write(uPass.c_str(), passLen);
				}
				curr = curr->right;
			}
		}
		userRecordOut << "\n";
		userRecordOut.close();
	}
	else
	{
		cout << "Failed To Open File!" << endl;
		(void)getch();
	}
}
void UserTree::loadUsers()
{
	ifstream userRecordIn("UserRecord.dat", ios::binary | ios::in);
	if (userRecordIn.is_open())
	{
		while (!userRecordIn.eof())
		{
			char* buff;
			string uName = "";
			string uPass = "";
			int nameS, passS;
			userRecordIn.read(reinterpret_cast<char*>(&nameS), sizeof(int));
			buff = new char[nameS];
			userRecordIn.read(buff, nameS);
			uName.append(buff, nameS);
			userRecordIn.read(reinterpret_cast<char*>(&passS), sizeof(int));
			buff = new char[passS];
			userRecordIn.read(buff, passS);
			uPass.append(buff, passS);
			User user(uName, uPass);
			if (user.getID() >= 0)
			{
				insert(user);
				//cout << "-------------------------------" << endl;
				//user.printUserData();
				//cout << "-------------------------------" << endl;
			}
		}
		userRecordIn.close();
	}
	else
	{
		cout << "Failed To Open File!" << endl;
		(void)getch();
	}
}