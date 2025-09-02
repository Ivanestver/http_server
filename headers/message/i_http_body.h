#pragma once
#include "core/iserializable.h"

class IHTTPBody :  public ISerializable, public IDeserializable
{
public:
	virtual ~IHTTPBody() = default;

	virtual std::vector<char> GetRawData() const = 0;
	virtual void SetRawData(const std::vector<char>& rawData) = 0;
};