#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class Client {

public:
	
	Client(string server, int port);	
	~Client();
	Run();
	Send(string input);
	string BuildMessage();

public:
	string serverAddress;
	int listeningPort;
	WSAData socketData;
	WORD socketVersion;
	SOCKET clientSocket;
	sockaddr_in socketHint;
	bool alive;
	char buf[1024 * 1024];
};