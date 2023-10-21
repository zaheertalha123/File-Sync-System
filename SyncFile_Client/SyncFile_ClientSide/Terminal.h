#ifndef TERMINAL
#define TERMINAL
#pragma once
#include <string>
#include <sstream>
#include <queue>
#include "ConnectionBuilder.h"
#include "User.h"

using namespace std;

class Terminal
{
private:
	enum Commands
	{
		//Nothing
		none,
		//Commands For Folders
		//Make Folder
		md, 
		//Remove Folder
		rd,
		//Rename Folder
		rnd,
		//Copy Folder
		cpd,
		//Cut Folder
		ctd,
		//Change Folder
		cd,
		//Commands For Files
		//List All Files And Subfolders
		ls,
		//Make File
		mf,
		//Remove File
		rf,
		//Rename File
		rnf,
		//Copy File
		cpf,
		//Cut File
		ctf,
		//Open File
		of,
		//View File
		vf,
		//Commands For User
		//Name Of User
		whoami,
		//ID Of User
		myid,
		//Change Password
		chpass,
		//Logout Account
		logout,
		//Clear Screen
		cls,
		//Manual Page
		man,
		//Searching
		find
	};
	//Data Members
	string homePath;
	string expression;
	string path;
	string currLocation;

	Commands command;
	string arguments[2];
	User* currentUser;
	ConnectionBuilder* conn;
	bool isLoggedIn;

	//Private Methods
	bool numCheck(char ch);
	bool aplhaCheck(char ch);
	bool symbolCheck(char ch);
public:
	//Constructor
	Terminal();
	//Setter
	void setExpression(string expression);
	//Getters
	void getExpression();
	bool breakExpression(bool& isInvalidCommand, bool& isInvalidArgu, bool& isArguMiss, bool& isExpressLong,
		bool& tooManyArgu);
	void WaitForExpression(string tobeDisplayed);
	void performTask();
	void startTerminal(ConnectionBuilder* connector, User* user, string& homePath);
};

#endif