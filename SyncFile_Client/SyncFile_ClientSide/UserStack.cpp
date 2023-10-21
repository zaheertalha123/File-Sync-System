#include "UserStack.h"

using namespace std;

//Implementing Constructor
UserStack::UserStack()
{
	this->_top = NULL;
	this->_size = 0;
}
//Implementing Methods
bool UserStack::isEmpty()
{
	if (_top == NULL)
		return true;
	return false;
}
void UserStack::push(User user)
{
	Node* temp = new Node(user);
	temp->next = _top;
	_top = temp;
	_size++;
}
void UserStack::pop()
{
	if (!isEmpty())
	{
		Node* temp = _top;
		_top = _top->next;
		delete(temp);
		_size--;
	}
}
User UserStack::top()
{
	if (!isEmpty())
	{
		_top->user;
	}
	return User();
}
int UserStack::size()
{
	return _size;
}