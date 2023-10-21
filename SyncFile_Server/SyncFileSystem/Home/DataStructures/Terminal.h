#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <conio.h>
#include <cctype>
#include <sys/stat.h>
#include <sys/types.h>
#include "UserTree.h"
#include "User.h"
#include "ConnectionHandler.h"
#include "Dirent.h"
#include "FileSystemTree.h"

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
	static string homePath;
	static string rootPath;
	string expression;
	string path;
	string currLocation;
	Commands command;
	string arguments[2];
	
	User* currentUser;
	ConnectionHandler* conn;
	
	UserTree* tree;
	FileSystemTree fsTree;

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
	bool getExpression();
	bool breakExpression(bool& isInvalidCommand, bool& isInvalidArgu, bool& isArguMiss, bool& isExpressLong,
		bool& tooManyArgu);
	void WaitForExpression(string tobeDisplayed);
	void performTask();
	void startTerminal(UserTree* tree, ConnectionHandler* connector, User* user);
};