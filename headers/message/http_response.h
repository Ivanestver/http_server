#pragma once
#include "i_http_body.h"
#include <unordered_map>
#include "enum_status_code.h"
#include "http_headers.h"

namespace message
{
	class ResponseWriter
	{
	public:
		ResponseWriter(Buffer* buf_)
			: buf{ buf_ }
		{ }

		template<typename First, typename... Rest>
		ResponseWriter& WriteLine(First&& first, Rest&&... rest)
		{
			(*buf) << std::forward<First>(first);
			return WriteLine(std::forward<Rest>(rest)...);
		}

		template<typename First>
		ResponseWriter& WriteLine(First&& first)
		{
			(*buf) << std::forward<First>(first);
			return WriteLine();
		}

		ResponseWriter& WriteLine()
		{
			(*buf) << endline;
			return *this;
		}

	private:
		static constexpr const char endline[] = "\r\n";
		Buffer* buf;
	};

	class HTTPResponse
	{
	public:
		void SetStatusCode(StatusCode statusCode);
		void SetHeader(const THeaderKey& key, const THeaderValue& value);
		ResponseWriter GetBodyWriter();

		std::vector<uint8_t> toBytes();

	private:
		StatusCode m_statusCode{ StatusCode::OK };
		HTTPHeaders m_headers;
		Buffer m_body;
	};
}