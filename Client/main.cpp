#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

/*
* steps
* 1.create winsock lib
* 2.create socket
* 3.send and recieve
* 4.cleanup winsock
*/

bool initialize()
{
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main()
{


	//create winsock lib
	if (!initialize)
	{
		cout << "Winsock initialization failed" << endl;
		return 1;
	}

	//create socket
	SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listensocket == INVALID_SOCKET)
	{
		std::cout << "socket creation failed" << std::endl;
		return 1;
	}

	//send and recieve
	
	cout << "Client" << endl;
}