#include "ConnectionHandler.h"

using namespace std;

//Constructor
ConnectionHandler::ConnectionHandler()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("Failed To Setup Windows Socket!\n");
		printf("Error Code : %d\n", iResult);
		exit(EXIT_FAILURE);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("Failed To Resolve The Server!\n");
		printf("Error Code : %d\n", iResult);
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	sendbuf = NULL;
	isRecieved = false;
	bytesRecieved = 0;
	bytesSent = 0;
}
//Destructor
ConnectionHandler::~ConnectionHandler()
{
	endConnection();
	closesocket(ClientSocket);
	WSACleanup();
}

//Method To Setup Socket
bool ConnectionHandler::createSocket()
{
	// Create a SOCKET for the server to listen for client connections.
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("Failed To Create Socket!\n");
		printf("Error Code : %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("Failed To Bind Socket!\n");
		printf("Error Code : %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}

	freeaddrinfo(result);
	return true;
}

//Method To Listen For Clients
bool ConnectionHandler::listenClient()
{
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("Falied To Listen For Client!\n");
		printf("Error Code : %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}
}
//Method To Accept Client
bool ConnectionHandler::acceptClient()
{
	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("Failed To Accept Client!\n");
		printf("Error Code : %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}
	return true;
}

//Method To Close Socket
void ConnectionHandler::closeSocket()
{
	closesocket(ListenSocket);
}

//Method To Recieve Data
bool ConnectionHandler::recieveData()
{
	do {
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			isRecieved = true;
			bytesRecieved = iResult;
			return true;
		}
		else if (iResult == 0)
		{
			printf("Connection closing...\n");
			isRecieved = false;
			return false;
		}
		else
		{
			printf("Failed To Recieve Data!\n");
			printf("Errir Code : %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return false;;
		}

	} while (iResult > 0);
}

//Method To Fill Send Buffer
void ConnectionHandler::fillSentBuffer(char arr[])
{
	sendbuf = arr;
}

//Method To Empty Send Buffer
void ConnectionHandler::emptySendBuffer()
{
	sendbuf = NULL;
}

//Method To Send Data
bool ConnectionHandler::sendData()
{
	if (sendbuf == NULL)
	{
		printf("Buffer Is Empty!");
		return false;
	}
	// Send an initial buffer
	iSendResult = send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iSendResult == SOCKET_ERROR)
	{
		printf("Failed To Send Data!");
		printf("Error Code : %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		getch();
		return false;
	}
	//printf("Bytes Sent: %ld\n", iResult);
	return true;
}

//Method TO Shutdown Connection
bool ConnectionHandler::endConnection()
{
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("Failed To Shutdown Connection!\n");
		printf("Error Code : %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return false;
	}
	//cout << "Closing Connection!" << endl;
	return true;
}

//Method To Get Recieved Data
string ConnectionHandler::getRevievedDat()
{
	if (!isRecieved)
		return "";
	else
	{
		string str = "";
		for (int j = 0; j < bytesRecieved; j++)
		{
			str += recvbuf[j];
		}
		return str;
	}
}

//Method To Clear Recieve Buffer
void ConnectionHandler::clearRecieveBuffer()
{
	memset(recvbuf, 0, sizeof(recvbuf));
}