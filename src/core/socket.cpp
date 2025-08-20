#include "core/socket.h"

socket_t invalid_socket_t = INVALID_SOCKET;

namespace core
{
	Socket::Socket(AddressFamily eAF, SockType eST, IPProtocol eProtocol)
	{
#ifdef WIN32
		m_socket = socket((int)eAF, (int)eST, (int)eProtocol);
#else
#endif
	}

	Socket::Socket(socket_t rawSocket)
		: m_socket{ rawSocket }
	{
	}

	bool Socket::IsInvalid() const
	{
		return m_socket != invalid_socket_t;
	}

	socket_t Socket::operator*() const
	{
		return m_socket;
	}
}
