#pragma once
#include "core/iserializable.h"
#include <any>

class IHTTPStartLine : public ISerializable, IDeserializable
{
public:
	enum class Property
	{
		Unknown,
		Method,
		Target,
		Protocol,
		StatusCode,
		StatusCodeText
	};

public:
	virtual ~IHTTPStartLine() = default;

	virtual std::any GetProperty(IHTTPStartLine::Property property) const = 0;
	virtual void SetProperty(IHTTPStartLine::Property property, const std::any& propertyValue) = 0;
};
