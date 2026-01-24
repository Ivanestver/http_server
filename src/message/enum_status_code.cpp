#include "message/enum_status_code.h"
#include <unordered_map>

namespace message
{
    String StatusCodeAsStr(StatusCode statusCode)
    {
        static const std::unordered_map<StatusCode, String> m
        {
            {StatusCode::OK, "OK"},
            {StatusCode::FOUND, "Found"},
            {StatusCode::NOT_FOUND, "NotFound"}
        };
        return m.at(statusCode);
    }
}
