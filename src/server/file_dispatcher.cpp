#include "server/file_dispatcher.h"
#include <fstream>

namespace server
{
	FileDispatcher::FileDispatcher(const String& pathToFile)
		: m_pathToFile{ pathToFile }
	{
	}

	void FileDispatcher::Dispatch(const message::IHTTPRequest* request, message::HTTPResponse& response)
	{
		if (!request)
			throw std::invalid_argument{ "Request is undefined" };

		std::ifstream in{ m_pathToFile.data() };
		if (!in.is_open())
		{
			Buffer buf;
			buf << "No such file: " << m_pathToFile;
			throw std::ios_base::failure{ buf.data() };
		}

		message::ResponseWriter writer = response.GetBodyWriter();
		std::string line;
		while (std::getline(in, line))
			writer.WriteLine(line);
	}
}