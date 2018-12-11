#include "Client.h"



Client::Client(string server, int port)
{
	cout << "Client Init Starting..." << endl;
	serverAddress = server;
	listeningPort = port;

	socketVersion = MakeWord(2, 2);
	int result = WSAStartup(socketVersion, &socketData);
	if (result != 0)	{
		cerr << "Failure to start winsock : " << result << endl;
		WSACleanup();
		return null;
	}
	cout << "WinSock initalised..." << endl;


	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "Failure to initialise socket: " << WSAGetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return null;
	}
	cout << "Socket initialised..." << endl;


	socketHint.sin_family = AF_INET;
	socketHint.sin_port = htons(listeningPort);
	inet_pton(AF_INET, serverAddress.c_str(), &socketHint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&socketHint, sizeof(socketHint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Failure to connect to server: " << WSAGetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return null;
	}
	cout << "Socket connected..." << endl;
	cout << "Client Init Completed" << endl;
}

Client::~Client()
{
	if (clientSocket != null)
	{
		closesocket(clientSocket);
	}
	WSACleanup();
}

Client::Run()
{
	do {
		ZeroMemory(buf, (1024 * 1024));
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived > 0)
		{
			string message = BuildMessage();
			if (message != null) {
				//we got a message bois lets do something with it
			}
		}
	} while{alive};
}

Client::Send(string input)
{
	int sendResult = send(clientSocket, input.c_str(), input.size() + 1, 0);
	if (sendResult == SOCKET_ERROR)
	{
		//uhh we fucked up yeh
	}
}

string Client::BuildMessage()
{

	int response = 1, totalBytes = 0;
	string message;
	bool delimiterNotFound = true;

	while (delimiterNotFound) {
		result = recv(clientSocket, &buff[totalBytes], sizeof(buff) - totalBytes - 1, 0);
		if (result == -1) {
			cerr << "Failure to fetch message: " << WSAGetLastError() << endl;
			return null;
		}		
		totalBytes += response;
		buff[totalBytes] = '\0';
		delimiterNotFound = (strchr(buff, "delimiter") != 0);
	}
	return string(buff, 0, totalBytes);
}



