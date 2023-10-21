#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "ConnectionBuilder.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

//Constructor
ConnectionBuilder::ConnectionBuilder()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("Failed To Start Windows Socket");
		printf("Error Code : %d\n", iResult);
		getch();
		exit(EXIT_FAILURE);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("Failed To Resolve The Server");
		printf("Error Code : %d\n", iResult);
		WSACleanup();
		getch();
		exit(EXIT_FAILURE);
	}
	sendbuf = NULL;
	isRecieved = false;
	bytesRecieved = 0;
}
/*
ConnectionBuilder::ConnectionBuilder(string ip, string port)
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("Failed To Start Windows Socket");
		printf("Error Code : %d\n", iResult);
		getch();
		exit(EXIT_FAILURE);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ip, port, &hints, &result);
	if (iResult != 0)
	{
		printf("Failed To Resolve The Server");
		printf("Error Code : %d\n", iResult);
		WSACleanup();
		getch();
		exit(EXIT_FAILURE);
	}
}
*/

//Destructor
ConnectionBuilder::~ConnectionBuilder()
{
	endConnection();
}

//Method To Build Connection
bool ConnectionBuilder::buildConnection()
{
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Socket Failed!");
			printf("Error Code : %ld\n", WSAGetLastError());
			WSACleanup();
			getch();
			return false;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		getch();
		return false;
	}
	return true;
}

//Method To Fill Buffer
void ConnectionBuilder::fillBuffer(char charr[])
{
	sendbuf = charr;
}

//Method To Empty Buffer
void ConnectionBuilder::emptyBuffer()
{
	sendbuf = NULL;
}

//Method To Terminate Connection
bool ConnectionBuilder::endConnection()
{
	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("Failed To Shutdown Connection");
		printf("Error Code : %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		getch();
		return false;
	}
	return true;
}

//Method To Send Data
int ConnectionBuilder::sendData()
{
	if (sendbuf == NULL)
	{
		printf("Buffer Is Empty!");
		return false;
	}
	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("Failed To Send Data!");
		printf("Error Code : %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		getch();
		return false;
	}
	//printf("Bytes Sent: %ld\n", iResult);
	return iResult;
}

//Method To Recieve Data
bool ConnectionBuilder::recieveData()
{
	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			isRecieved = true;
			bytesRecieved = iResult;
			return true;
		}
		else if (iResult == 0)
		{
			printf("Connection closed\n");
			printf("No Data Recieved!\n");
			return false;
		}
		else
		{
			printf("Failed To Recieve Data\n");
			printf("Error Code : %d\n", WSAGetLastError());
			return false;
		}
	} while (iResult > 0);
}

//Method To Get Recieved Data
string ConnectionBuilder::getRevievedData()
{
	if (!isRecieved)
		return "";
	else
	{
		string str;
		for (int j = 0; j < bytesRecieved; j++)
		{
			str += recvbuf[j];
		}
		return str;
	}
}