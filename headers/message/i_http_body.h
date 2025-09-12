#pragma once
#include "core/iserializable.h"
#include <istream>

class IHTTPBody : public ISerializable, public IDeserializable
{
public:
	virtual ~IHTTPBody() = default;

	virtual std::vector<char> ToBytes() const = 0;
	virtual String ToString() const = 0;
	virtual std::unique_ptr<std::istream> ToStream() const = 0;
	virtual size_t GetSize() const = 0;
	virtual bool IsEmpty() const = 0;
	virtual String GetContentType() const = 0;
};