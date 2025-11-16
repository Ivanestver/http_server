#pragma once

namespace message
{
	enum class StatusCode
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

	const char* StatusCodeAsStr(StatusCode statusCode);
}