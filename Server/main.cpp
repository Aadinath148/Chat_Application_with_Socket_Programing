#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>


/*
*steps 
1.intialize winsock libaray
2.create the socket
3.get ip and port
4.bind the ip/port with socket
5.listen on socket
6.accept
7.recieve and send
8.closed the socket
9.clean up winsock libaray
*/

#pragma comment(lib,"ws2_32.lib")


bool Initialize()
{
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main()
{
	std::cout << "Chat Application" << std::endl;

	if (!Initialize)
	{
		std::cout << "Winsock initialization failed" << std::endl;
		return 1;
	}

	//creates socket
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSocket == INVALID_SOCKET)
	{
		std::cout << "socket creation failed" << std::endl;
		return 1;
	}

	//create address structure
	int port = 12345;
	sockaddr_in serveradd;
	serveradd.sin_family = AF_INET;
	serveradd.sin_port = htons(port);

	//convert the ipaddress (0.0.0.0) put it inside the sin_family in binary form
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveradd.sin_addr) != 1)
	{
		std::cout << "structure creation failed" << std::endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//bind 
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveradd), sizeof(serveradd)) == SOCKET_ERROR)
	{
		std::cout << "binding failed" << std::endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Listining failed" << std::endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "server has started listening on port: " << port << std::endl;

	//accept
	SOCKET clientsocket = accept(listenSocket, nullptr, nullptr);
	if (clientsocket == INVALID_SOCKET)
	{
		std::cout << "accepting client socket failed" << std::endl;
		return 1;

	}

	//recieve and send
	char buffer[4096];
	int datainbyte = recv(clientsocket, buffer, sizeof(buffer), 0);
	if (datainbyte)
	{
		std::string message(buffer, datainbyte);
		std::cout << "Message from client: " << message << std::endl;
		closesocket(clientsocket);
		closesocket(listenSocket);
		WSACleanup();
	}
	WSACleanup();
	return 0;
}