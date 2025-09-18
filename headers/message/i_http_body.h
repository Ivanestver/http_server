#pragma once
#include <vector>
#include <memory>
#include <string>

namespace message
{
	class IHTTPBody
	{
	public:
		virtual ~IHTTPBody() = default;

		virtual std::vector<uint8_t> ToBytes() const = 0;
		virtual std::string ToString() const = 0;
		virtual std::unique_ptr<std::istream> ToStream() const = 0;
		virtual size_t GetSize() const = 0;
		virtual bool IsEmpty() const = 0;
		virtual std::string GetMIMEType() const = 0;
	};
}
