#include "core/net_funcs.h"

namespace core
{
	std::string getErrorMessage(int errorCode);

#ifdef WIN32

	std::string makeErrorMessage(const std::string& funcName, int errorCode)
	{
		return funcName + std::string{ " failed with error: " } + getErrorMessage(errorCode);
	}

	std::string getErrorMessage(int errorCode)
	{
		switch (errorCode)
		{
		case WSASYSNOTREADY:
		{
			return std::string{ "Net subsystem is unavailable." };
		}
		case WSAVERNOTSUPPORTED:
		{
			return std::string{ "Winsock.dll doesn't support the required version of sockets." };
		}
		case WSAEPROCLIM:
		{
			return std::string{ "Too much processes are in run." };
		}
		case WSAEFAULT:
		{
			return std::string{ "Wrong address." };
		}
		case WSANOTINITIALISED:
		{
			return std::string{ "WSAStartup has not been called yet." };
		}
		case WSAENETDOWN:
		{
			return std::string{ "Net is not working." };
		}
		case WSAEINPROGRESS:
		{
			return std::string{ "A blocking operation is performing." };
		}
		default:
			return std::string{ "Unknown error(." } + std::to_string(errorCode) + std::string{ ")" };
		}
	}

	std::string Startup()
	{
		WSADATA wsaData;
		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (result != 0)
			return makeErrorMessage("WSAStartup", result);
		return {};
	}

	void ZeroizeMemory(sockaddr_in_t* addr)
	{
		ZeroMemory(addr, sizeof(addr));
	}

	void InitSockAddrIn(sockaddr_in_t* addr, port_t port, AddressFamily eAF, InAddr eIA/* = InAddr::ANY*/)
	{
		ZeroizeMemory(addr);
		addr->sin_addr.s_addr = (ULONG)eIA;
		addr->sin_family = (USHORT)eAF;
		addr->sin_port = htons(port);
	}

	std::pair<Socket, std::string> CreateSocket(AddressFamily eAF, SockType eST, IPProtocol eProtocol/* = IPProtocol::UNSPEC*/)
	{
		Socket sock{ eAF, eST, eProtocol };
		if (sock.IsInvalid())
			return { std::move(sock), makeErrorMessage("Socket", WSAGetLastError()) };
		else
			return { std::move(sock), "" };
	}

	std::string Bind(const sockaddr_in_t* addr, Socket& socket)
	{
		int errorCode = bind(*socket, reinterpret_cast<const sockaddr_t*>(addr), sizeof(*addr));
		return errorCode >= 0 ? std::string{} : makeErrorMessage("Bind", WSAGetLastError());
	}

	void Listen(const Socket& server, int queueLength)
	{
		listen(*server, queueLength);
	}

	std::pair<Socket, std::string> Accept(const Socket& serverSocket, sockaddr_in_t* clientAddr)
	{
		int clientAddrSize = sizeof(*clientAddr);
		Socket clientSocket{ accept(*serverSocket, reinterpret_cast<sockaddr_t*>(clientAddr), &clientAddrSize) };
		return 
		{
			std::move(clientSocket), 
			clientSocket.IsInvalid() ? makeErrorMessage("Accept", WSAGetLastError()) : std::string{ "" }
		};
	}

	std::string ClearUp()
	{
		int result = WSACleanup();
		if (result != 0)
			return makeErrorMessage("WSACleanup", result);
		return {};
	}
#else
#endif
}