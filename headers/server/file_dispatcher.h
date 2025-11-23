#pragma once
#include "server/export_decl.h"
#include "core/str.h"
#include "message/i_http_request.h"
#include "message/http_response.h"

namespace server
{
	class SERVER FileDispatcher
	{
	public:
		FileDispatcher(const String& pathToFile);
		void Dispatch(const message::IHTTPRequest* request, message::HTTPResponse& response);

	private:
		String m_pathToFile;
	};
}