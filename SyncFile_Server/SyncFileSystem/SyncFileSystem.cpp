#include <iostream>
#include <conio.h>
#include <string>
#include <queue>
#include <sys/stat.h>
#include "Tree.h"
#include "Dirent.h"
#include "Terminal.h"
#include "ConnectionHandler.h"
#include "UserTree.h"
#include "Validations.h"

using namespace std;

int main()
{
	UserTree userTree;
	userTree.loadUsers();
	while (true)
	{
		ConnectionHandler connector;
		connector.createSocket();
		connector.listenClient();
		while (true)
		{
			cout << "Started To Accept Clients!" << endl;
			if (connector.acceptClient())
			{
				while (true)
				{
					connector.emptySendBuffer();
					cout << "Waiting For Data To Receive!" << endl;
					if (connector.recieveData())
					{
						Terminal terminal;
						string homePath = "Z:\\SyncFileSystem\\SyncFileSystem\\Home";
						User* user;
						string str = connector.getRevievedDat();
						stringstream ss(str);
						string uName;
						string uPass;
						string ch;
						for (int j = 0; !ss.eof(); j++)
						{
							if (j == 0)
								getline(ss, uName, '+');
							else if (j == 1)
								getline(ss, uPass, '+');
							else if (j == 2)
								getline(ss, ch, '+');
						}
						int choice = stoi(ch);
						cout << uName << endl;
						cout << uPass << endl;
						char buff[15];
						char* tempBuff;
						memset(buff, 0, 10);
						switch (choice)
						{
						case 1:
							cout << "----Signing Up For New Account!----" << endl;
							cout << "New User Name : " << uName << endl;
							if (userTree.insert(User(uName, uPass)))
							{
								cout << "----New User Created!----" << endl;
								userTree.saveUsers();
								strcpy(buff, "Created");
							}
							else
							{
								cout << "----User Already Exist!----" << endl;
								strcpy(buff, "MatchFound");
							}
							connector.fillSentBuffer(buff);
							connector.sendData();
							break;
						case 2:
							cout << "----Logging In----" << endl;
							cout << "User Trying To Login : " << uName << endl;
							user = userTree.getUser(User(uName, uPass));
							if (user->getUserName() == uName && user->getPassword() == uPass)
							{
								cout << "----User Found!----" << endl;
								strcpy(buff, "Found");
								connector.fillSentBuffer(buff);
								connector.sendData();
								tempBuff = new char[homePath.length()];
								strcpy(tempBuff, homePath.c_str());
								connector.fillSentBuffer(tempBuff);
								connector.sendData();
								terminal.startTerminal(&userTree, &connector, user);
							}
							else
							{
								cout << "----User Not Found!----" << endl;
								strcpy(buff, "NotFound");
								connector.fillSentBuffer(buff);
								connector.sendData();
							}
							
							break;
						case 3:
							cout << "----Deleting Account----" << endl;
							cout << "User Trying To Delete Account : " << uName << endl;
							user = userTree.getUser(User(uName, uPass));
							if (user->getUserName() == uName)
							{
								cout << "----User Found!----" << endl;
								strcpy(buff, "Found");
							}
							else
							{
								cout << "----User Not Found!----" << endl;
								strcpy(buff, "NotFound");
								connector.fillSentBuffer(buff);
								connector.sendData();
								break;
							}
							connector.fillSentBuffer(buff);
							connector.sendData();
							connector.clearRecieveBuffer();
							cout << "----Waiting For User To Confirm Deletion!----" << endl;
							if (connector.recieveData())
							{
								uPass = connector.getRevievedDat();
								if (user->getPassword() == uPass)
								{
									if (userTree.remove(*user))
									{
										cout << "----Account Deleted Successfully!----" << endl;
										strcpy(buff, "Succeed");
										connector.fillSentBuffer(buff);
										connector.sendData();
										userTree.saveUsers();
									}
								}
								else if (uPass == "Cancel")
									cout << "----Deletion Process Canceled----" << endl;
								else if (user->getPassword() != uPass)
								{
									cout << "----Wrong Password Account Not Deleted!----" << endl;
									strcpy(buff, "Failed");
									connector.fillSentBuffer(buff);
									connector.sendData();
								}
							}
							break;
						default:
							strcpy(buff, "Garbage");
							connector.sendData();
							break;
						}
					}
					else
						break;
				}
			}
			else
				break;
		}
	}

	(void)getch();
	return 0;
}
