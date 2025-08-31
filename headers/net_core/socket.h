#pragma once
#include "platform.h"

namespace net_core
{
	class Socket
	{
	public:
		Socket(AddressFamily eAF, SockType eST, IPProtocol eProtocol = IPProtocol::UNSPEC);
		explicit Socket(socket_t rawSocket);
		Socket(const Socket&) = delete;
		Socket(Socket&& other) noexcept;

		~Socket();

		Socket& operator=(const Socket&) = delete;
		Socket& operator=(Socket&& other) noexcept;

		bool IsInvalid() const;

		socket_t operator*() const;

	private:
		socket_t m_socket;
	};
}