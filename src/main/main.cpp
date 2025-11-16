#include <iostream>
#include "server/server.h"

int main()
{
	port_t port = 8088;
	server::Server server;

	server.AddHandler("/", [](const message::IHTTPRequest* request, message::HTTPResponse& response)
		{
			response.SetStatusCode(message::StatusCode::OK);
			response.SetHeader("Content-Type", "text/html; charset = UTF-8");
			auto bodyWriter = response.GetBodyWriter();
			bodyWriter.WriteLine("<!DOCTYPE html>")
				.WriteLine("<html>")
				.WriteLine("<head>")
				.WriteLine("\t<title>Hello</title>")
				.WriteLine("</head>")
				.WriteLine("<body>")
				.WriteLine("\t<h1>Hello, World!</h1>")
				.WriteLine("</body>")
				.WriteLine("</html>");
		});

	server.Run(port);
	return 0;
}
