#pragma once
#include "core/str.h"

namespace message
{
	enum class StatusCode : unsigned short
	{
		// Informational responses
		// Successful responses
		OK = 200,
		// Redirection responses
		FOUND = 302,
		// Client error responses
		NOT_FOUND = 404,
		// Server error responses
	};

	String StatusCodeAsStr(StatusCode statusCode);
}