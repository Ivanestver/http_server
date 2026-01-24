#pragma once
#include "platform.h"
#include "net_core/export_decl.h"

namespace net_core
{
	class NET_CORE Socket
	{
	public:
		~Socket();
		Socket(AddressFamily eAF, SockType eST, IPProtocol eProtocol = IPProtocol::UNSPEC);
		explicit Socket(socket_t rawSocket);
		Socket(const Socket&) = delete;
		Socket(Socket&& other) noexcept;
		Socket& operator=(const Socket&) = delete;
		Socket& operator=(Socket&& other) noexcept;

		inline bool IsInvalid() const;

		socket_t operator*() const;

	private:
		socket_t m_socket;
	};
}