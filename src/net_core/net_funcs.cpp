#include "net_core/net_funcs.h"

namespace net_core
{
	String getErrorMessage(int errorCode);

#ifdef WIN32

	String makeErrorMessage(const String& funcName, int errorCode)
	{
		return funcName + String{ " failed with error: " } + getErrorMessage(errorCode);
	}

	String getErrorMessage(int errorCode)
	{
		switch (errorCode)
		{
		case WSASYSNOTREADY:
		{
			return String{ "Net subsystem is unavailable." };
		}
		case WSAVERNOTSUPPORTED:
		{
			return String{ "Winsock.dll doesn't support the required version of sockets." };
		}
		case WSAEPROCLIM:
		{
			return String{ "Too much processes are in run." };
		}
		case WSAEFAULT:
		{
			return String{ "Wrong address." };
		}
		case WSANOTINITIALISED:
		{
			return String{ "WSAStartup has not been called yet." };
		}
		case WSAENETDOWN:
		{
			return String{ "Net is not working." };
		}
		case WSAEINPROGRESS:
		{
			return String{ "A blocking operation is performing." };
		}
		default:
			return String{ "Unknown error(." } + std::to_string(errorCode) + String{ ")" };
		}
	}

	String Startup()
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

	std::pair<Socket, String> CreateSocket(AddressFamily eAF, SockType eST, IPProtocol eProtocol/* = IPProtocol::UNSPEC*/)
	{
		Socket sock{ eAF, eST, eProtocol };
		if (sock.IsInvalid())
			return { std::move(sock), makeErrorMessage("Socket", WSAGetLastError()) };
		else
			return { std::move(sock), "" };
	}

	String Bind(const sockaddr_in_t* addr, Socket& socket)
	{
		int errorCode = bind(*socket, reinterpret_cast<const sockaddr_t*>(addr), sizeof(*addr));
		return errorCode >= 0 ? String{} : makeErrorMessage("Bind", WSAGetLastError());
	}

	void Listen(const Socket& server, int queueLength)
	{
		listen(*server, queueLength);
	}

	std::pair<Socket, String> Accept(const Socket& serverSocket, sockaddr_in_t* clientAddr)
	{
		int clientAddrSize = sizeof(*clientAddr);
		Socket clientSocket{ accept(*serverSocket, reinterpret_cast<sockaddr_t*>(clientAddr), &clientAddrSize) };
		return 
		{
			std::move(clientSocket), 
			clientSocket.IsInvalid() ? makeErrorMessage("Accept", WSAGetLastError()) : String{ "" }
		};
	}

	String ClearUp()
	{
		int result = WSACleanup();
		if (result != 0)
			return makeErrorMessage("WSACleanup", result);
		return {};
	}
#else
#endif
}