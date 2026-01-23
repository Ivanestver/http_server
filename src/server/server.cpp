#include "server.h"
#include "net_core/net_funcs.h"
#include "parser/request_parser.h"
#include "message/http_response.h"
#include <memory>
#include "context_configure.h"
#include <array>
#include <algorithm>
#include "response_sender.h"

using namespace message;
using namespace net_core;

namespace server
{
	const message::IHTTPRequest* retrieveRequest(const net_core::Socket& clientSock)
	{
		char buffer[1024] = { 0 };
		int count = recv(*clientSock, buffer, sizeof(buffer) - 1, 0);
		if (count > 0)
			std::cout << buffer << std::endl << std::endl;
		String s{ buffer };
		parser::RequestParser requestParser{ s };
		return requestParser.Parse();
	}

	bool requestMustNotHaveBody(const String& method)
	{
		static std::array<String, 3> methodsMustHave
		{
			"POST",
			"PUT",
			"PATCH"
		};
		return std::none_of(methodsMustHave.begin(), methodsMustHave.end(), [&method](const String& s) { return s != method; });
	}

	bool contentLengthNotSuitFactualLength(const message::IHTTPRequest* request)
	{
		const IHTTPRequestStartLine* startLine = request->GetStartLine();
		if (!startLine)
			return true;

		if (requestMustNotHaveBody(startLine->GetMethod()))
			return false;

		const IHTTPHeaders* headers = request->GetHeaders();
		if (!headers || !headers->HasHeader("Content-Length"))
			return true;

		const THeaderValue contentLengthValue = headers->GetHeaderValue("Content-Length");
		const auto contentLength = ToIntegral<size_t>(contentLengthValue);

		const IHTTPBody* body = request->GetBody();
		return !body || body->GetSize() != contentLength;
	}

	void Server::respond(Socket&& refClientSocket) noexcept
	{
		Socket clientSock{ std::move(refClientSocket) };
		auto request = std::unique_ptr<const message::IHTTPRequest>{ retrieveRequest(clientSock) };
		if (!request || contentLengthNotSuitFactualLength(request.get()))
		{
			response_senders::SendBadRequest(clientSock);
			return;
		}

		const auto it = m_handlers.find(request->GetStartLine()->GetPath());
		if (it == m_handlers.end())
			return;

		message::HTTPResponse response;
		it->second(request.get(), response);
		const std::vector<uint8_t> responseRaw = response.toBytes();
		int iSendResult = send(*clientSock, (const char*)responseRaw.data(), (int)responseRaw.size(), 0);
		if (iSendResult == SOCKET_ERROR)
		{
			std::cout << "send failed with error: %d\n" << WSAGetLastError() << std::endl;
			return;
		}
		printf("Bytes sent: %d\n", iSendResult);
	}

	void Server::AddHandler(const String& path, Handler&& handler)
	{
		m_handlers.emplace(path, std::move(handler));
	}

	void Server::Run(port_t port)
	{
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

			respond(std::move(clientSock));
		}

		net_core::ClearUp();
	}
}
