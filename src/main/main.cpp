#include <iostream>
#include "server/context.h"
#include "net_core/platform.h"
#include "server/server_settings.h"

using namespace server;

int main(int argc, char* argv[])
{
	port_t port = 8088;

	server::AddHandler("/", [](const message::IHTTPRequest* request, message::HTTPResponse& response)
		{
			response.SetHeader("Content-Type", "text/html; charset = UTF-8");
			try
			{
				response.SetStatusCode(message::StatusCode::OK);
				server::GetContext()->MakeFileDispatcher("index.html")->Dispatch(request, response);
			}
			catch (const std::exception& e)
			{
				response.GetBodyWriter().WriteLine(e.what());
				response.SetStatusCode(message::StatusCode::NOT_FOUND);
			}
		}
	);

	server::Run(port, argc, argv);
	return 0;
}
