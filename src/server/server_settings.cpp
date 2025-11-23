#include "server/server_settings.h"
#include "server.h"
#include "core/buffer.h"
#include "context_configure.h"

namespace server
{
	Server server;

	void AddHandler(const String& path, Handler&& handler)
	{
		server.AddHandler(path, std::move(handler));
	}

	void Run(port_t port, int argc, char* argv[])
	{
		if (!argv)
			throw std::exception("No args");

		String pathToExe{ argv[0] };
#if WIN32
		std::vector<String> parts = pathToExe.split('\\');
#else
		std::vector<String> parts = pathToExe.split('/');
#endif
		pathToExe = parts[0] + '/';
		for (size_t i = 1; i < parts.size() - 1; ++i)
			pathToExe = pathToExe + (parts[i] + '/');

		ConfigureContext(pathToExe);
		server.Run(port);
	}
}