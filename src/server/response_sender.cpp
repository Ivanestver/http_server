#include "response_sender.h"

namespace server::response_senders
{
	void SendResult(const net_core::Socket& clientSocket, const String& buffer)
	{
		int sentResult = send(*clientSocket, buffer.data(), (int)buffer.length(), 0);
		if (sentResult == SOCKET_ERROR)
		{
			std::cout << "send failed with error: %d\n" << WSAGetLastError() << std::endl;
		}
	}

	void SendBadRequest(const net_core::Socket& clientSocket)
	{
		const String buffer = "400: Bad request";
		SendResult(clientSocket, buffer);
	}
}

