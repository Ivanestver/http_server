#include "net_core/net_funcs.h"
#include <iostream>

int main()
{
	String errorMessage = net_core::Startup();
	if (!errorMessage.is_empty())
	{
		std::cout << errorMessage << std::endl;
		return 1;
	}

	auto [sock, err] = net_core::CreateSocket(AddressFamily::INET, SockType::STREAM);
	if (!err.is_empty())
	{
		std::cout << err << std::endl;
		return 1;
	}

	sockaddr_in_t addr;
	net_core::InitSockAddrIn(&addr, 8088, AddressFamily::INET);

	errorMessage = net_core::Bind(&addr, sock);
	if (!errorMessage.is_empty())
	{
		std::cout << errorMessage << std::endl;
		return 1;
	}

	net_core::Listen(sock, 0);

	while (true)
	{
		sockaddr_in_t clientAddr;
		auto [clientSock, err] = net_core::Accept(sock, &clientAddr);
		if (!err.is_empty())
		{
			std::cout << err << std::endl;
			continue;
		}

		char buffer[1024] = {0};
		int count = recv(*clientSock, buffer, sizeof(buffer) - 1, 0);
		if (count > 0)
			std::cout << buffer << std::endl << std::endl;

		char response[] = "HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html; charset=UTF-8\r\n"
			"Content-Length: 100\r\n"
			"\r\n"
			"<!DOCTYPE html>\r\n"
			"<html>\r\n"
			"<head>\r\n"
			"\t<title>Hello</title>\r\n"
			"</head>\r\n"
			"<body>\r\n"
			"\t<h1>Hello, World!</h1>\r\n"
			"</body>\r\n"
			"</html>\r\n";
		//char response[] = "answer\r";
		int iSendResult = send(*clientSock, response, strlen(response), 0);
		if (iSendResult == SOCKET_ERROR)
		{
			std::cout << "send failed with error: %d\n" << WSAGetLastError() << std::endl;
			continue;
		}
		printf("Bytes sent: %d\n", iSendResult);
	}

	net_core::ClearUp();
	return 0;
}
