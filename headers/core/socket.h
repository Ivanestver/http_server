#pragma once
#include "platform.h"

namespace core
{
	class Socket
	{
	public:
		Socket(AddressFamily eAF, SockType eST, IPProtocol eProtocol = IPProtocol::UNSPEC);
		explicit Socket(socket_t rawSocket);
		bool IsInvalid() const;

		socket_t operator*() const;

	private:
		socket_t m_socket;
	};
}