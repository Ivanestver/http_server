#pragma once

#include "net_core/socket.h"
#include "core/str.h"

namespace server::response_senders
{
	void SendResult(const net_core::Socket& clientSocket, const String& buffer);
	void SendBadRequest(const net_core::Socket& clientSocket);
}