#include <iostream>
#include <conio.h>
#include "ConnectionBuilder.h"
#include "UserTree.h"
#include "Terminal.h"
#include "Validations.h"

using namespace std;

int main()
{
	User user;
	ConnectionBuilder connector;
	if (!connector.buildConnection())
	{
		cout << "----Exiting Application!-----" << endl;
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		Terminal* terminal;
		string choice;
		string buffer = "";
		char* buff;
		string str;
		string temp;
		string homePath;
		bool cancel = false;
		system("cls");
		cout << "-----------File Sync System-----------" << endl;
		cout << "Enter 1 To Sign Up : \n"
			<< "Enter 2 To Login : \n"
			<< "Enter 3 To Delete Account : \n"
			<< "Enter 4 To Exit Application : \n : ";
		getline(cin >> ws, choice);
		if (choice == "1")
		{
			while (true)
			{
				buffer.clear();
				system("cls");
				cout << "---------------------Sign Up Page---------------------" << endl;
				cout << "Enter You New User Name (c to Cancel) : ";
				getline(cin >> ws, str);
				if (str == "c" || str == "C")
				{
					cout << "----Account Not Created!----" << endl;
					system("pause");
					break;
				}
				if (!userNameCheck(str))
				{
					cout << "----Incorrect User Name!----\n"
						<< "-->Must Start With Alphabet Or Underscore\n"
						<< "-->Cannot Contain Special Symbols And Spaces\n"
						<< "-->Can Be Up To 20 Characters Long" << endl;
					system("pause");
					continue;
				}
				buffer += str + '+';
				str.clear();
				cout << "----Password Rules----\n"
					<< "-->Cannot Contain Spaces\n"
					<< "-->Can Be 20 Characters Long" << endl;
				while (true)
				{
					cout << "Enter Your New Password (c to Cancel) : ";
					getline(cin >> ws, str);
					if (str == "c" || str == "C")
					{
						cout << "----Account Not Created!----" << endl;
						system("pause");
						cancel = true;
						break;
					}
					if (!passwordCheck(str))
					{
						cout << "----Password Is Incorrect----\n"
							<< "-->Cannot Contain Spaces\n"
							<< "-->Can Be 20 Characters Long" << endl;
						continue;
					}
					cout << "Retype The Password (c to Cancel) : ";
					getline(cin >> ws, temp);
					if (temp == "c" || temp == "C")
					{
						cout << "----Account Not Created!----" << endl;
						system("pause");
						cancel = true;
						break;
					}
					if (str != temp)
					{

						cout << "------------------------------" << endl
							<< "----Password Didn't Match!----" << endl
							<< "------------------------------" << endl;
						continue;
					}
					break;
				}
				if (cancel)
					break;
				buffer += str + '+';
				buffer += to_string(1);
				buff = new char[buffer.length()];
				strcpy(buff, buffer.c_str());
				connector.fillBuffer(buff);
				if (!connector.sendData())
				{
					cout << "----Failed To Create Account!----" << endl;
					cout << "----Either Server Is Not Responding or Your Connection Is Down----" << endl;
					system("pause");
					exit(EXIT_FAILURE);
					break;
				}
				else
				{
					connector.emptyBuffer();
					if (connector.recieveData())
					{
						string rec = connector.getRevievedData();
						if (rec == "Created")
						{
							cout << "----Account Created Successfully!----" << endl;
							system("pause");
							break;
						}
						else if (rec == "MatchFound")
						{
							cout << "----User Already Exist!----" << endl;
							system("pause");
							continue;
						}
					}
					else
					{
						cout << "----Either Server Is Not Responding or Your Connection Is Down----" << endl;
						exit(EXIT_FAILURE);
						break;
					}
				}
			}
		}
		else if (choice == "2")
		{
			while (true)
			{
				string uName;
				string uPass;
				buffer.clear();
				connector.emptyBuffer();
				system("cls");
				cout << "----------------------Login Page---------------------" << endl;
				cout << "Enter Your User Name (c to Cancel) : ";
				getline(cin >> ws, str);
				if (str == "c" || str == "C")
				{
					cout << "----Account Not Logged In!----" << endl;
					system("pause");
					break;
				}
				if (!userNameCheck(str))
				{
					cout << "----Incorrect User Name!----\n"
						<< "-->Must Start With Alphabet Or Underscore\n"
						<< "-->Cannot Contain Special Symbols And Spaces\n"
						<< "-->Can Be Up To 20 Characters Long" << endl;
					system("pause");
					continue;
				}
				uName = str;
				buffer += str + '+';
				str.clear();
				cout << "Enter Your Password (c to Cancel) : ";
				getline(cin >> ws, str);
				if (str == "c" || str == "C")
				{
					cout << "----Account Not Logged In!----" << endl;
					system("pause");
					break;
				}
				uPass = str;
				buffer += str + '+';
				buffer += to_string(2);
				buff = new char[buffer.length()];
				strcpy(buff, buffer.c_str());
				connector.fillBuffer(buff);
				if (!connector.sendData())
				{
					cout << "----Failed To Login!----" << endl;
					cout << "----Either Server Is Not Responding or Your Connection Is Down----" << endl;
					exit(EXIT_FAILURE);
					system("pause");
					break;
				}
				if (connector.recieveData())
				{
					string rec = connector.getRevievedData();
					if (rec == "Found")
					{
						user = User(uName, uPass);
						terminal = new Terminal();
						system("cls");
						if (!connector.recieveData())
						{
							cout << "----Server Not Responding!----" << endl;
							exit(EXIT_FAILURE);
						}
						homePath = connector.getRevievedData();
						terminal->startTerminal(&connector, &user, homePath);
						cout << "----Logging Out File Sync System!----" << endl;
						system("pause");
						break;
					}
					else if (rec == "NotFound")
					{
						cout << "----User Name and Password Doesn't Match----" << endl;
						system("pause");
						continue;
					}
				}
				else
				{
					cout << "----Either Server Is Not Responding or Your Connection Is Down----" << endl;
					break;
				}
			}
		}
		else if (choice == "3")
		{
			while (true)
			{
				buffer = "";
				connector.emptyBuffer();
				system("cls");
				cout << "----------------------Delete Account Page---------------------" << endl;
				cout << "Enter User Name To Delete (c to Cancel) : ";
				getline(cin >> ws, str);
				if (!userNameCheck(str))
				{
					cout << "----Incorrect User Name!----" << endl;
					continue;
				}
				if (str == "c" || str == "C")
				{
					cout << "----Account Not Deleted!----" << endl;
					system("pause");
					break;
				}
				buffer += str + '+';
				buffer += "WrongPass+";
				buffer += to_string(3);
				cout << buffer << endl;
				buff = new char[buffer.length()];
				strcpy(buff, buffer.c_str());
				connector.fillBuffer(buff);
				if (!connector.sendData())
				{
					cout << "----Failed To Delete Account!----" << endl;
					cout << "----Either Server Is Not Responding or Your Connection Is Down----" << endl;
					exit(EXIT_FAILURE);
					system("pause");
					break;
				}
				else
				{
					connector.emptyBuffer();
					if (connector.recieveData())
					{
						string rec = connector.getRevievedData();
						if (rec == "Found")
						{
							buffer.clear();
							cout << "----Account Found!----" << endl;
							cout << "User Name : " << str << endl;
							cout << "----------------------" << endl;
							cout << "Enter Password To Confirm Deletion (c to Cancel) : ";
							str.clear();
							getline(cin >> ws, str);
							if (str == "c" || str == "C")
							{
								cout << "----Account Not Deleted!----" << endl;
								buffer = "Cancel";
								buff = new char[buffer.length()];
								strcpy(buff, buffer.c_str());
								connector.fillBuffer(buff);
								connector.sendData();
								system("pause");
								break;
							}
							buffer = str;
							buff = new char[buffer.length()];
							strcpy(buff, buffer.c_str());
							connector.fillBuffer(buff);
							connector.sendData();
							if (connector.recieveData())
							{
								str = connector.getRevievedData();
								if (str == "Succeed")
								{
									cout << "----Account Deleted Successfully!----" << endl;
									system("pause");
									break;
								}
								else if (str == "Failed")
								{
									cout << "----Password Didn't Match!----" << endl;
									cout << "----Account Not Deleted!----" << endl;
									system("pause");
								}
								else
								{
									cout << "----Account Not Deleted!----" << endl;
									cout << "----Something Went Wrong!----" << endl;
									system("pause");
								}
							}
						}
						else if (rec == "NotFound")
						{
							cout << "----User Not Exist!----" << endl;
							system("pause");
							continue;
						}
					}
					else
					{
						cout << "----Either Server Is Not Responding or Your Connection Is Down----" << endl;
						break;
					}
				}
			}
		}
		else if (choice == "4")
		{
			connector.endConnection();
			exit(EXIT_SUCCESS);
			break;
		}
		else
		{
			cout << "----Please Enter A Valid Choice!----" << endl;
			system("pause");
		}
	}
	return 0;
}