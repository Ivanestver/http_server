#pragma once

#include "core/str.h"
#include "net_core/socket.h"
#include "net_core/export_decl.h"

namespace net_core
{
	NET_CORE String Startup();
	NET_CORE void ZeroizeMemory(sockaddr_in_t* addr);
	NET_CORE void InitSockAddrIn(sockaddr_in_t* addr, port_t port, AddressFamily eAF, InAddr eIA = InAddr::ANY);
	NET_CORE std::pair<Socket, String> CreateSocket(AddressFamily eAF, SockType eST, IPProtocol eProtocol = IPProtocol::UNSPEC);
	NET_CORE String Bind(const sockaddr_in_t* addr, Socket& socket);
	NET_CORE void Listen(const Socket& server, int queueLength);
	NET_CORE std::pair<Socket, String> Accept(const Socket& serverSocket, sockaddr_in_t* clientAddr);
	NET_CORE String ClearUp();
}
