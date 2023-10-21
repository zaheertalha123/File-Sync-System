#include <iostream>
#include "User.h"

using namespace std;

//Implementing Private Methods
bool User::numCheck(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
bool User::aplhaCheck(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return true;
	return false;
}
bool User::symbolCheck(char ch)
{
	if (!(aplhaCheck(ch) || ch == '_'))
		return true;
	return false;
}

//Implementing Constructors
User::User()
{
	this->uName = "NILL";
	this->uPassword = "NILL";
	this->id = idGen();
}
User::User(string uName, string uPassword)
{
	this->id = idGen();
	this->uName = uName;
	this->uPassword = uPassword;
	this->id = idGen();
}

//Implementing Setter
void User::setID()
{
	this->id = idGen();
}
void User::setUserName(string uName)
{
	this->uName = uName;
}
void User::setPassword(string uPass)
{
	this->uPassword = uPass;
}
int User::idGen()
{
	int id = 0;
	for (int j = 0; j < (int)uName.length(); j++)
		id += uName[j];
	return id;
}

//Implementing Getter
int User::getID()
{
	return this->id;
}
string User::getUserName()
{
	return this->uName;
}
string User::getPassword()
{
	return this->uPassword;
}

//Implementing Methods
void User::printUserData()
{
	cout << "User ID : " << this->id << endl
		<< "User Name : " << this->uName << endl
		<< "User Password : " << this->uPassword << endl;
}
