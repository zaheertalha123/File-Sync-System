#ifndef USER
#define USER
#pragma once
#include <string>

using namespace std;

class User
{
private:
	static int num;
	//Private Members
	int id;
	string uName;
	string uPassword;
	//Private Methods
	bool numCheck(char ch);
	bool aplhaCheck(char ch);
	bool symbolCheck(char ch);
public:
	//Constructors
	User();
	User(string uName, string uPassword);
	//Setter
	void setID();
	void setUserName(string uName);
	void setPassword(string uPass);
	int idGen();
	//Getter
	int getID();
	string getUserName();
	string getPassword();
	//Methods
	void printUserData();
	//void showTerminal();
};

#endif