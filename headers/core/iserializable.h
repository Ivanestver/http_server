#pragma once
#include "buffer.h"

class ISerializable
{
public:
	virtual ~ISerializable() = default;

	virtual Buffer& Serialize(Buffer& buf) const = 0;
};

class IDeserializable
{
public:
	virtual ~IDeserializable() = default;

	virtual Buffer& Deserialize(Buffer& buf) = 0;
};