#include "net_core/net_funcs.h"
#include <iostream>
#include "parser/request_parser.h"
#include "message/http_response.h"

int main()
{
	port_t port = 8088;
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
	net_core::InitSockAddrIn(&addr, port, AddressFamily::INET);

	errorMessage = net_core::Bind(&addr, sock);
	if (!errorMessage.is_empty())
	{
		std::cout << errorMessage << std::endl;
		return 1;
	}

	net_core::Listen(sock, 0);
	std::cout << "Started listening on " << port << std::endl;

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
		String s{ buffer };
		parser::RequestParser requestParser{ s };
		const message::IHTTPRequest* request = requestParser.Parse();

		message::HTTPResponse response;
		response.SetStatusCode(message::StatusCode::OK);
		response.SetHeader("Content-Type", "text/html; charset = UTF-8");
		auto bodyWriter = response.GetBodyWriter();
		bodyWriter.WriteLine("<!DOCTYPE html>")
			.WriteLine("<html>")
			.WriteLine("<head>")
			.WriteLine("\t<title>Hello</title>")
			.WriteLine("</head>")
			.WriteLine("<body>")
			.WriteLine("\t<h1>Hello, World!</h1>")
			.WriteLine("</body>")
			.WriteLine("</html>");
		const std::vector<uint8_t> responseRaw = response.toBytes();
		int iSendResult = send(*clientSock, (const char*)responseRaw.data(), responseRaw.size(), 0);
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
