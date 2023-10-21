#ifndef CONNECTIONBUILDER
#define CONNECTIONBUILDER
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;

class ConnectionBuilder
{
private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char *sendbuf;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	bool isRecieved;
	int bytesRecieved;
public:
	//Constructor
	ConnectionBuilder();
	//ConnectionBuilder(string ip, string port);
	//Destructor
	~ConnectionBuilder();
	//Method To Build Connection
	bool buildConnection();
	//Method To Fill Buffer
	void fillBuffer(char charr[]);
	//Method To Empty Buffer
	void emptyBuffer();
	//Method To Terminate Connection
	bool endConnection();
	//Method To Send Data
	int sendData();
	//Method To Receive Data
	bool recieveData();
	//Method To Get Received Data
	string getRevievedData();
};

#endif