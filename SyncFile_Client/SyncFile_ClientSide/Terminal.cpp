#include <iostream>
#include <conio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <cctype>
#include "Terminal.h"

using namespace std;

//Implementing Private Methods
bool Terminal::numCheck(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
bool Terminal::aplhaCheck(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return true;
	return false;
}
bool Terminal::symbolCheck(char ch)
{
	if (!(aplhaCheck(ch) || ch == '_'))
		return true;
	return false;
}
//Implementing Constructor
Terminal::Terminal()
{
	this->expression = "";
	this->command = none;
	this->arguments[0] = "";
	this->arguments[1] = "";
	this->homePath = "";
	this->path = this->currLocation = homePath;
	this->currentUser = NULL;
	this->conn = NULL;
	this->isLoggedIn = false;
}
//Implementing Setter
void Terminal::setExpression(string expression)
{
	this->expression = expression;
}
//Implementing Getters
void Terminal::getExpression()
{
	cin.clear();
	getline(cin >> ws, expression);
}
bool Terminal::breakExpression(bool& isInvalidCommand, bool& isInvalidArgu, bool& isArguMiss, bool& isExpressLong,
	bool& tooManyArgu)
{
	memset(arguments, 0, 2);
	if (expression.length() == 0)
		return true;
	queue<string> queStr;
	stringstream ss(expression);
	string tempStr;
	while (!ss.eof())
	{
		getline(ss, tempStr, ' ');
		queStr.push(tempStr);
	}
	tempStr = queStr.front();
	queStr.pop();
	if (tempStr == "whoami")
	{
		if (queStr.empty())
		{
			command = whoami;
			return true;
		}
		tooManyArgu = true;
		return false;
	}
	else if (tempStr == "myid")
	{
		if (queStr.empty())
		{
			command = myid;
			return true;
		}
		tooManyArgu = true;
		return false;
	}
	else if (tempStr == "logout")
	{
		if (queStr.empty())
		{
			command = logout;
			return true;
		}
		tooManyArgu = true;
		return false;
	}
	else if (tempStr == "chpass")
	{
		if (queStr.empty())
		{
			command = chpass;
			return true;
		}
		tooManyArgu = true;
		return false;
	}
	else if (tempStr == "cls")
	{
		if (queStr.empty())
		{
			command = cls;
			return true;
		}
		tooManyArgu = true;
		return false;
	}
	else if (tempStr == "man")
	{
		if (queStr.empty())
		{
			command = man;
			return true;
		}
		tooManyArgu = true;
		return false;
	}
	else if (tempStr == "ls")
	{
		if (queStr.empty())
		{
			command = ls;
			return true;
		}
		tooManyArgu = true;
		return false;
	}
	else if (tempStr == "cd")
	{
		command = cd;
		if (queStr.empty())
		{
			arguments[0] = "";
			return true;
		}
	}
	else if (tempStr == "md")
		command = md;
	else if (tempStr == "rd")
		command = rd;
	else if (tempStr == "rnd")
		command = rnd;
	else if (tempStr == "cpd")
		command = cpd;
	else if (tempStr == "ctd")
		command = ctd;
	else if (tempStr == "mf")
		command = mf;
	else if (tempStr == "rf")
		command = rf;
	else if (tempStr == "rnf")
		command = rnf;
	else if (tempStr == "cpf")
		command = cpf;
	else if (tempStr == "ctf")
		command = ctf;
	else if (tempStr == "of")
		command = of;
	else if (tempStr == "vf")
		command = vf;
	else if (tempStr == "find")
		command = find;
	else
	{
		command = none;
		isInvalidCommand = true;
		return false;
	}
	if (queStr.empty())
	{
		isArguMiss = true;
		return false;
	}
	arguments[0] = queStr.front();
	queStr.pop();
	if ((command == vf || command == of || command == rf || command == mf || command == cd
		|| command == md || command == rd || command == find) && queStr.empty())
	{
		if (command == vf || command == of || command == rf || command == mf)
		{
			if (arguments[0][arguments[0].length() - 4] != '.')
			{
				isInvalidArgu = true;
				return false;
			}
		}
		return true;
	}
	else if ((command == vf || command == of || command == vf || command == rf || command == mf || command == cd
		|| command == md || command == rd) && !queStr.empty())
	{
		isExpressLong = true;
		return false;
	}
	if (queStr.empty())
	{
		cout << "Argument Missed!" << endl;
		isArguMiss = true;
		return false;
	}
	arguments[1] = queStr.front();
	queStr.pop();
	if ((command == rnd || command == cpd || command == ctd || command == rnf ||
		command == cpf || command == ctf) && queStr.empty())
	{
		if (command == rnf || command == cpf || command == ctf)
		{
			if ((arguments[1][arguments[1].length() - 4] != '.') || (arguments[0][arguments[0].length() - 4] != '.'))
			{
				isInvalidArgu = true;
				return false;
			}
			if (command == rnf)
			{
				size_t pos1 = arguments[0].find('\\');
				size_t pos2 = arguments[1].find('\\');
				if (!((pos1 == string::npos && pos2 == string::npos) ||
					(pos1 != string::npos && pos2 != string::npos)))
				{
					isInvalidArgu = true;
					return false;
				}
			}
		}
		if (command == rnd)
		{
			size_t pos1 = arguments[0].find('\\');
			size_t pos2 = arguments[1].find('\\');
			if (!((pos1 == string::npos && pos2 == string::npos) ||
				(pos1 != string::npos && pos2 != string::npos)))
			{
				isInvalidArgu = true;
				return false;
			}
		}
		return true;
	}
	else if ((command == vf || command == of || command == vf || command == rf || command == mf || command == cd
		|| command == md || command == rd) && !queStr.empty())
	{
		isExpressLong = true;
		return false;
	}
	if (!queStr.empty())
	{
		isExpressLong = true;
		return false;
	}
	return true;
}
void Terminal::WaitForExpression(string tobeDisplayed)
{
	while (isLoggedIn)
	{
		cout << path << "\\>";
		getExpression();
		bool isInvalidCommand = false;
		bool isInvalidArgu = false;
		bool isArguMiss = false;
		bool isExpressLong = false;
		bool tooManyArgu = false;
		if (breakExpression(isInvalidCommand, isInvalidArgu, isArguMiss, isExpressLong, tooManyArgu))
			performTask();
		else
		{
			if (isInvalidCommand)
				cout << "Command Not In Scope" << endl;
			else if (isArguMiss)
				cout << "Missing Argument" << endl;
			else if (isInvalidArgu)
				cout << "Invalid Argument" << endl;
			else if (isExpressLong)
				cout << "Expression Too long" << endl;
			else if (tooManyArgu)
				cout << "Too Many Arguments Given" << endl;
		}
	}
}
void Terminal::performTask()
{
	string buffer = "";
	char* buff;
	string str1, str2;
	switch (command)
	{
	case none:
		break;
	case man:
		cout << "---------------------------File Sync System---------------------------" << endl;
		cout << endl;
		cout << "--------User Commands--------" << endl;
		cout << "whoami			: Displays User Name Of Current User\n"
			<< "myid			: Displays The ID Assigned To User\n"
			<< "logout			: Command To Logout And Exit The Terminal\n"
			<< "chpass			: Command to Change Password Of Current User\n"
			<< "cls			: Deletes Previous Record And Clears The Screen\n";
		cout << endl;
		cout << "--------Directory Commands--------" << endl;
		cout << "md			: Creates A New Directory With Specified Name In Current Location\n"
			<< "rd			: Removes The Specified DIrectory If It Is Empty\n"
			<< "rnd			: Rename The Specified Directory With New Name\n"
			<< "cpd			: Copies The Directory To A Specified Location\n"
			<< "ctd			: Moves The Directory To A Specified Location\n"
			<< "cd			: Changes The Current Location To Specified Location\n";
		cout << endl;
		cout << "--------File Commands--------" << endl;
		cout << "mf			: Creates A New File With Specified Name\n"
			<< "rf			: Removes The Specified File\n"
			<< "rnf			: Rename The Specified File With New Name\n"
			<< "cpf			: Copies File To A Specified Location\n"
			<< "ctf			: Moves A File To A Specified Location\n"
			<< "of			: Opens Specified Mode in Append Mode\n"
			<< "vf			: View The Contents Of Specified File\n";
		break;
	case whoami:
		cout << "Logged In With User Name : " << currentUser->getUserName() << endl;
		break;
	case myid:
		cout << "Your ID : " << currentUser->getID() << endl;
		break;
	case logout:
		isLoggedIn = false;
		buff = new char[10];
		strcpy(buff, "Logout");
		conn->fillBuffer(buff);
		conn->sendData();
		break;
	case chpass:
		cout << "Enter Your Current Password : ";
		cin >> str1;
		if (str1 != currentUser->getPassword())
		{
			cout << "Password Didn't Match" << endl;
			return;
		}
		str1.clear();
		cout << "Type In Your New Password : ";
		cin >> str1;
		cout << "Retype The Password : ";
		cin >> str2;
		if (str1 != str2)
		{
			cout << "Password Didn't Match" << endl;
			return;
		}
		buffer += "chpass";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (conn->sendData())
		{
			if (!conn->recieveData())
			{
				cout << "Failed To Execute Command" << endl;
				return;
			}
		}
		buffer.clear();
		buffer += str1;
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (conn->sendData())
		{
			if (conn->recieveData())
			{
				str1 = conn->getRevievedData();
				if (str1 == "Succeed")
				{
					cout << "Password Changed Successfully" << endl;
					currentUser->setPassword(str1);
				}
				else
				{
					cout << "Error Occurred While Changing Password" << endl;
					return;
				}
			}
		}
		break;
	case cls:
		system("cls");
		break;
	case md:
		buffer = "md";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "InvalidCommand")
		{
			cout << "Unknown Error Occured!" << endl;
			return;
		}
		buffer = arguments[0];
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "Succeed")
			cout << "Folder Created!" << endl;
		else if (str1 == "17")
			cout << "Folder Already Exist!" << endl;
		else if (str1 == "2")
			cout << "Path Not Found!" << endl;
		else
			cout << "Unknown Error Occured!" << endl;
		break;
	case rd:
		buffer = "rd";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "InvalidCommand")
		{
			cout << "Unknown Error Occured!" << endl;
			return;
		}
		buffer = arguments[0];
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "Succeed")
			cout << "Folder Removed!" << endl;
		else if (str1 == "41")
			cout << "Folder Is Not Empty!" << endl;
		else if (str1 == "17")
			cout << "Folder Already Exist!" << endl;
		else if (str1 == "2")
			cout << "Folder Not Found" << endl;
		else
			cout << "Unknown Error Occured!" << endl;
		break;
	case rnd:
		buffer = "rnd";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "InvalidCommand")
		{
			cout << "Unknown Error Occured!" << endl;
			return;
		}
		buffer = arguments[0] + '+' + arguments[1];
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "Renamed")
			cout << "Folder Ranamed!" << endl;
		else if (str1 == "Differ")
			cout << "Paths Are Different For Both Files" << endl;
		else if (str1 == "Unknown")
			cout << "Invalid Argumentss" << endl;
		else if (str1 == "2")
			cout << "Folder Not Found!" << endl;
		else if (str1 == "17")
			cout << "Folder Already Exist With The Same Name!" << endl;
		else if (str1 == "2")
			cout << "Folder Not Found!" << endl;
		else 
			cout << "Unknown Error Occured!" << endl;
		break;
	case cpd:
		cout << "Copy Folder" << endl;
		break;
	case ctd:
		cout << "Cut Folder" << endl;
		break;
	case cd:
		buffer = "cd";
		if (arguments[0].length() == 0)
		{
			if (currLocation == "Home")
				return;
		}
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 != "ValidCommand")
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (arguments[0] == "")
			buffer = "Back";
		else
			buffer = arguments[0];
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "NotExist")
			cout << "Directory Not Found!" << endl;
		else
			this->path = this->currLocation = str1;
		break;
	case ls:
		buffer = "ls";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "2")
			cout << "Directory Not Exist!" << endl;
		else
			cout << str1;
		break;
	case mf:
		buffer = "mf";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "InvalidCommand")
		{
			cout << "Unknown Error Occured!" << endl;
			return;
		}
		buffer = arguments[0];
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "Exist")
			cout << "File Already Exist!" << endl;
		else if (str1 == "Created")
			cout << "File Created!" << endl;
		else
			cout << "Error Occur While Creating File" << endl;
		break;
	case rf:
		buffer = "rf";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "InvalidCommand")
		{
			cout << "Unknown Error Occured!" << endl;
			return;
		}
		buffer = arguments[0];
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 == "Removed")
			cout << "File Removed" << endl;
		else if (str1 == "2")
			cout << "File Not Found!" << endl;
		else
			cout << "Unknown Error Occured!" << endl;
		break;
	case rnf:
		cout << "Rename File" << endl;
		break;
	case cpf:
		cout << "Copy File" << endl;
		break;
	case ctf:
		cout << "Cut File" << endl;
		break;
	case of:
		cout << "Open File" << endl;
		break;
	case vf:
		cout << "view File" << endl;
		break;
	case find:
		buffer = "find";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 != "ValidCommand")
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		buffer = arguments[0];
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Failed To Execute Command!" << endl;
			cout << "----Server Not Responding!----" << endl;
			return;
		}
		str1 = conn->getRevievedData();
		if (str1 != "NULL")
			cout << str1 << endl;
		break;
	//0345-4262658
	}
}

void Terminal::startTerminal(ConnectionBuilder* connector, User* user, string& homePath)
{
	this->currentUser = user;
	this->conn = connector;
	this->isLoggedIn = true;
	this->homePath = homePath;
	this->path = "Home";
	this->currLocation = "Home";
	WaitForExpression(path);
}