#include "Terminal.h"

using namespace std;
//Implementing Static Variables
string Terminal::homePath = "Z:\\SyncFileSystem\\SyncFileSystem\\Home";
string Terminal::rootPath = "Z:\\SyncFileSystem\\SyncFileSystem";


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
	this->path = "Home\\";
	this->conn = NULL;
	this->currentUser = NULL;
	this->tree = NULL;
	this->isLoggedIn = false;
	this->currLocation = "Home";
	this->fsTree.loadFileSystem();
}
//Implementing Setter
void Terminal::setExpression(string expression)
{
	this->expression = expression;
}
//Implementing Getters
bool Terminal::getExpression()
{
	cout << "----Waiting For Command By : " << currentUser->getUserName()  << " ----"<< endl;
	if (conn->recieveData())
	{
		setExpression(conn->getRevievedDat());
		if (expression == "Logout")
		{
			cout << "Logging Out User : " << currentUser->getUserName() << endl;
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}
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
}
void Terminal::WaitForExpression(string tobeDisplayed)
{
	while (isLoggedIn)
	{
		if (!getExpression())
			return;
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
				cout << "Too Many Arguments" << endl;
		}
	}
}
void Terminal::performTask()
{
	FILE* file;
	DIR* dir;
	dirent* en;
	string buffer, str1, str2, cnd;
	stringstream ss(str1);
	size_t pos, pos2;
	Node* tempNode;
	char* buff;
	int res, len, len2;
	switch (command)
	{
	case none:
		buffer = "InvalidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Send Data" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
		}
		break;
	case man:
		cout << "---------------------------File Sync System---------------------------" << endl;
		cout << endl;
		cout << "--------User Commands--------" << endl;
		cout << "whoami			: Displays User Name Of Current User\n"
			<< "myid			: Displays The ID Assigned To User\n"
			<< "logout			: Command To Logout And Exit The Terminal\n"
			<< "chpass			: Command to Change Password Of Current User\n"
			<< "cls				: Deletes Previous Record And Clears The Screen\n";
		cout << endl;
		cout << "--------Directory Commands--------" << endl;
		cout << "md		 : Creates A New Directory With Specified Name In Current Location\n"
			<< "rm		: Removes The Specified DIrectory If It Is Empty\n"
			<< "rnd		: Rename The Specified Directory With New Name\n"
			<< "cpd		: Copies The Directory To A Specified Location\n"
			<< "ctd		: Moves The Directory To A Specified Location\n"
			<< "cd		: Changes The Current Location To Specified Location\n";
		cout << endl;
		cout << "--------File Commands--------" << endl;
		cout << "mf		: Creates A New File With Specified Name\n"
			<< "rf	   : Removes The Specified File\n"
			<< "rnf	   : Rename The Specified File With New Name\n"
			<< "cpf    : Copies File To A Specified Location\n"
			<< "ctf    : Moves A File To A Specified Location\n"
			<< "of     : Opens Specified Mode in Append Mode\n"
			<< "vf	   : View The Contents Of Specified File\n";
		break;
	case whoami:
		cout << "Who Am I" << endl;
		break;
	case myid:
		cout << "My ID" << endl;
		break;
	case logout:
		cout << "Logout User" << endl;
		break;
	case chpass:
		cout << "----Waiting For The New Password----" << endl;
		buffer = "OK";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Change Password" << endl;
			break;
		}
		if (conn->recieveData())
		{
			str1 = conn->getRevievedDat();
			currentUser->setPassword(str1);
			buffer = "Succeed";
			buff = new char[buffer.length()];
			strcpy(buff, buffer.c_str());
			conn->fillSentBuffer(buff);
			conn->sendData();
			tree->saveUsers();
		}
		break;
	case cls:
		system("cls");
		break;
	case md:
		buffer = "ValidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		arguments[0] = conn->getRevievedDat();
		cnd = currLocation + "\\" + arguments[0];
		cout << cnd << endl;
		res = mkdir(cnd.c_str());
		if (res == -1)
		{
			buffer = to_string(errno);
		}
		else
		{
			buffer = "Succeed";
		}
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		break;
	case rd:
		buffer = "ValidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		arguments[0] = conn->getRevievedDat();
		cnd = currLocation + "\\" + arguments[0];
		res = rmdir(cnd.c_str());
		if (res == -1)
		{
			buffer = to_string(errno);
		}
		else
		{
			buffer = "Succeed";
		}
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		break;
	case rnd:
		buffer = "ValidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		str1 = conn->getRevievedDat();
		ss << str1;
		pos = 0;
		while (!ss.eof())
			getline(ss, arguments[pos++], '+');
		pos = arguments[0].find('\\');
		pos2 = arguments[1].find('\\');
		if (pos == string::npos || pos2 == string::npos)
		{
			cnd = currLocation + '\\' + arguments[0];
			str2 = currLocation + '\\' + arguments[1];
			res = rename(cnd.c_str(), str2.c_str());
			if (res == 0)
				buffer = "Renamed";
			else
				buffer = to_string(errno);
		}
		else if (pos == string::npos || pos2 == string::npos)
		{
			len = arguments[0].length();
			for (res = len - 1, len2 = 0; arguments[0][res] != '\\'; res--, len2++)
			{}
			len = len - len2 - 1;
			str1 = arguments[0].substr(0, len);
			
			len = arguments[1].length();
			for (res = len - 1, len2 = 0; arguments[1][res] != '\\'; res--, len2++)
			{}
			len = len - len2 - 1;
			str2 = arguments[1].substr(0, len);
			if (str1 != str2)
				buffer = "Differ";
			else
			{
				cnd = rootPath + '\\' + arguments[0];
				str2 = rootPath + '\\' + arguments[1];
				res = rename(cnd.c_str(), str2.c_str());
				if (res == 0)
					buffer = "Renamed";
				else
					buffer = to_string(errno);
			}
		}
		else
			buffer = "Unknown";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		break;
	case cpd:
		cout << "Copy Folder" << endl;
		break;
	case ctd:
		cout << "Cut Folder" << endl;
		break;
	case cd:
		buffer = "ValidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		arguments[0] = conn->getRevievedDat();
		pos = arguments[0].find('\\');
		if (arguments[0] == "Back")
		{
			len = currLocation.length();
			for (res = len - 1, len2 = 0; currLocation[res] != '\\'; res--, len2++)
			{}
			len = len - len2 - 1;
			currLocation = currLocation.substr(0, len);
			buffer = currLocation;
		}
		else if (pos == string::npos)
		{
			str1 = rootPath + '\\' + currLocation + '\\' + arguments[0];
			dir = opendir(str1.c_str());
			if (dir == NULL)
				buffer = "NotExist";
			else
			{
				closedir(dir);
				currLocation = currLocation + '\\' + arguments[0];
				buffer = currLocation;
			}
		}
		else
		{
			str1 = rootPath + '\\' + arguments[0];
			dir = opendir(str1.c_str());
			if (dir == NULL)
				buffer = "NotExist";
			else
			{
				closedir(dir);
				currLocation = arguments[0];
				buffer = currLocation;
			}
		}
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		break;
	case ls:
		dir = NULL;
		en = NULL;
		buffer = "";
		dir = opendir(currLocation.c_str());
		if (dir)
		{
			while ((en = readdir(dir)) != NULL)
			{
				if (((string)en->d_name == ".") || ((string)en->d_name == ".."))
					continue;
				if (en->d_type == DT_DIR)
					buffer = buffer + "FOLD\t";
				else
					buffer = buffer + "FILE\t";
				buffer = buffer + en->d_name + "\n";
			}
			closedir(dir);
		}
		else
			buffer += to_string(errno);
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		break;
	case mf:
		buffer = "ValidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		arguments[0] = conn->getRevievedDat();
		cnd = currLocation + "\\" + arguments[0];
		file = fopen(cnd.c_str(), "r");
		if (file != NULL)
		{
			buffer = "Exist";
			fclose(file);
		}
		else
		{
			file = fopen(cnd.c_str(), "w");
			fclose(file);
			buffer = "Created";
		}
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		break;
	case rf:
		buffer = "ValidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		arguments[0] = conn->getRevievedDat();
		cnd = currLocation + "\\" + arguments[0];
		res = remove(cnd.c_str());
		if (res != -1)
			buffer = "Removed";
		else
			buffer = to_string(errno);
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
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
		buffer = "ValidCommand";
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		if (!conn->recieveData())
		{
			cout << "Client Not Responding" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		arguments[0] = conn->getRevievedDat();
		if (arguments[0][arguments[0].length() - 4] == '.')
		{
			str1 = "";
			len = arguments[0].length() - 4;
			for (int j = 0; j < len; j++)
			{
				str1 += arguments[0][j];
			}
			cout << str1 << endl;
		}
		else
			str1 = arguments[0];
		tempNode = fsTree.getSearchResults(FileSystem(str1, "NULL"));
		if (tempNode == NULL)
			buffer = "NULL";
		else
		{
			buffer = "";
			while (tempNode != NULL)
			{
				buffer += tempNode->fs.getFileNameWE() + '\t' + tempNode->fs.getExtension()
					+ '\t' + tempNode->fs.getValidLocation() + '\n';
				tempNode = tempNode->next;
			}
		}
		buff = new char[buffer.length()];
		strcpy(buff, buffer.c_str());
		conn->fillSentBuffer(buff);
		if (!conn->sendData())
		{
			cout << "Failed To Communicate With Client" << endl;
			cout << "----Client Disconnected----" << endl;
			isLoggedIn = false;
			return;
		}
		break;
	}
}

void Terminal::startTerminal(UserTree* tree, ConnectionHandler* connector, User* user)
{
	this->currentUser = user;
	this->conn = connector;
	this->isLoggedIn = true;
	this->tree = tree;
	WaitForExpression(path);
}
