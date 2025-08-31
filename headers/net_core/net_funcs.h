#pragma once

#include "core/str.h"
#include "net_core/socket.h"
#include <string>

namespace net_core
{
	String Startup();
	void ZeroizeMemory(sockaddr_in_t* addr);
	void InitSockAddrIn(sockaddr_in_t* addr, port_t port, AddressFamily eAF, InAddr eIA = InAddr::ANY);
	std::pair<Socket, String> CreateSocket(AddressFamily eAF, SockType eST, IPProtocol eProtocol = IPProtocol::UNSPEC);
	String Bind(const sockaddr_in_t* addr, Socket& socket);
	void Listen(const Socket& server, int queueLength);
	std::pair<Socket, String> Accept(const Socket& serverSocket, sockaddr_in_t* clientAddr);
	String ClearUp();
}
