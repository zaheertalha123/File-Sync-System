#ifndef CONNECTIONHANDLER
#define CONNECTIONHANDLER
#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <conio.h>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;

class ConnectionHandler
{
private:
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	char* sendbuf;
	int sendbuflen = DEFAULT_BUFLEN;
	bool isRecieved;
	int bytesRecieved;
	int bytesSent;
public:
	//Constructor
	ConnectionHandler();
	//Destructor
	~ConnectionHandler();
	//Method To Setup Socket
	bool createSocket();
	//Method To Listen For Clients
	bool listenClient();
	//Method To Accept Client
	bool acceptClient();
	//Method To Close Socket
	void closeSocket();
	//Method To Receive Data
	bool recieveData();
	//Method To Fill Send Buffer
	void fillSentBuffer(char arr[]);
	//Method To Empty Send Buffer
	void emptySendBuffer();
	//Method To Send Data
	bool sendData();
	//Method TO Shutdown Connection
	bool endConnection();
	//Method To Get Recieved Data
	string getRevievedDat();
	//Method To Clear Recieve Buffer
	void clearRecieveBuffer();
};

#endif