#include "core/socket.h"
#include <type_traits>

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

	Socket::~Socket()
	{
		if (!IsInvalid())
			closesocket(m_socket);
	}

	Socket::Socket(socket_t rawSocket)
		: m_socket{ rawSocket }
	{
	}

	Socket::Socket(Socket&& other) noexcept
	{
		*this = std::move(other);
	}

	Socket& Socket::operator=(Socket&& other) noexcept
	{
		m_socket = other.m_socket;
		other.m_socket = invalid_socket_t;
		return *this;
	}

	bool Socket::IsInvalid() const
	{
		return m_socket == invalid_socket_t;
	}

	socket_t Socket::operator*() const
	{
		return m_socket;
	}
}
