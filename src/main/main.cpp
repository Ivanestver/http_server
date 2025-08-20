#include "core/net_funcs.h"
#include <iostream>

int main()
{
	std::string errorMessage = core::Startup();
	if (!errorMessage.empty())
	{
		std::cout << errorMessage << std::endl;
		return 1;
	}

	auto [sock, err] = core::CreateSocket(AddressFamily::INET, SockType::STREAM);
	if (!err.empty())
	{
		std::cout << err << std::endl;
		return 1;
	}

	sockaddr_in_t addr;
	core::InitSockAddrIn(&addr, 5555, AddressFamily::INET);

	errorMessage = core::Bind(&addr, sock);
	if (!errorMessage.empty())
	{
		std::cout << errorMessage << std::endl;
		return 1;
	}

	core::Listen(sock, 0);

	while (true)
	{
		sockaddr_in_t clientAddr;
		auto [clientSock, err] = core::Accept(sock, &clientAddr);
	}

	core::ClearUp();
	return 0;
}
