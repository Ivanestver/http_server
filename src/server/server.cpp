#include "server/server.h"
#include "net_core/net_funcs.h"
#include "parser/request_parser.h"
#include "message/http_response.h"
#include <memory>
#include "context_configure.h"

namespace server
{
	void Server::AddHandler(const String& path, Handler&& handler)
	{
		m_handlers.emplace(path, std::move(handler));
	}

	void Server::Run(port_t port)
	{
		ConfigureContext();

		String errorMessage = net_core::Startup();
		if (!errorMessage.is_empty())
		{
			std::cout << errorMessage << std::endl;
			return;
		}

		auto [sock, err] = net_core::CreateSocket(AddressFamily::INET, SockType::STREAM);
		if (!err.is_empty())
		{
			std::cout << err << std::endl;
			return;
		}

		sockaddr_in_t addr;
		net_core::InitSockAddrIn(&addr, port, AddressFamily::INET);

		errorMessage = net_core::Bind(&addr, sock);
		if (!errorMessage.is_empty())
		{
			std::cout << errorMessage << std::endl;
			return;
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
			auto request = std::unique_ptr<const message::IHTTPRequest>{ requestParser.Parse() };
			if (!request)
				continue;

			const auto it = m_handlers.find(request->GetStartLine()->GetPath());
			if (it == m_handlers.end())
				continue;
			message::HTTPResponse response;
			it->second(request.get(), response);
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
	}
}
