#pragma once
#include "buffer.h"

class CORE ISerializable
{
public:
	virtual ~ISerializable() = default;

	virtual Buffer& Serialize(Buffer& buf) const = 0;
};

class CORE IDeserializable
{
public:
	virtual ~IDeserializable() = default;

	virtual Buffer& Deserialize(Buffer& buf) = 0;
};