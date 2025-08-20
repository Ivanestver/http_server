#pragma once

#include "core/socket.h"
#include <string>

namespace core
{
	std::string Startup();
	void ZeroizeMemory(sockaddr_in_t* addr);
	void InitSockAddrIn(sockaddr_in_t* addr, port_t port, AddressFamily eAF, InAddr eIA = InAddr::ANY);
	std::pair<Socket, std::string> CreateSocket(AddressFamily eAF, SockType eST, IPProtocol eProtocol = IPProtocol::UNSPEC);
	std::string Bind(const sockaddr_in_t* addr, Socket& socket);
	void Listen(const Socket& server, int queueLength);
	std::pair<Socket, std::string> Accept(const Socket& serverSocket, sockaddr_in_t* clientAddr);
	std::string ClearUp();
}
