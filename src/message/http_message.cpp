#include "message/http_message.h"

Buffer& message::HTTPMessage::Serialize(Buffer& buf) const
{
    const IHTTPStartLine* startLine = GetStartLine();
    const IHTTPHeaders* headers = GetHeaders();
    if (startLine && headers)
    {
        startLine->Serialize(buf);
        headers->Serialize(buf);
    }
    return buf;
}

Buffer& message::HTTPMessage::Deserialize(Buffer& buf)
{
    IHTTPStartLine* startLine = GetStartLine();
    IHTTPHeaders* headers = GetHeaders();
    if (startLine && headers)
    {
        startLine->Deserialize(buf);
        headers->Deserialize(buf);
    }
    return buf;
}
