#pragma once
#include "core/iserializable.h"
#include "core/str_fw.h"

class IHTTPHeaders : public ISerializable, IDeserializable
{
public:
	virtual ~IHTTPHeaders() = default;

	virtual const String GetHeader(const String& header) const = 0;
};
