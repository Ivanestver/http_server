#include "message/enum_status_code.h"
#include <unordered_map>

namespace message
{
    const char* StatusCodeAsStr(StatusCode statusCode)
    {
        static const std::unordered_map<StatusCode, const char*> m
        {
            {StatusCode::OK, "OK"},
            {StatusCode::FOUND, "Found"},
            {StatusCode::NOT_FOUND, "NotFound"}
        };
        return m.at(statusCode);
    }
}
