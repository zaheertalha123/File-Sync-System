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
int User::idGen()
{
	int num = 0;
	for (int j = 0; j < uName.length(); j++)
		num += uName[j];
	return num;
}

//Implementing Constructors
User::User()
{
	this->id = 0;
	this->uName = "NILL";
	this->uPassword = "NILL";
}
User::User(string uName, string uPassword)
{
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