#include "message/http_message.h"

Buffer& message::HTTPMessage::Serialize(Buffer& buf) const
{
    const IHTTPStartLine* startLine = GetStartLine();
    const IHTTPHeaders* headers = GetHeaders();
    const IHTTPBody* body = GetBody();
    if (startLine && headers && body)
    {
        startLine->Serialize(buf);
        headers->Serialize(buf);
        body->Serialize(buf);
    }
    return buf;
}

Buffer& message::HTTPMessage::Deserialize(Buffer& buf)
{
    IHTTPStartLine* startLine = GetStartLine();
    IHTTPHeaders* headers = GetHeaders();
    IHTTPBody* body = GetBody();
    if (startLine && headers && body)
    {
        startLine->Deserialize(buf);
        headers->Deserialize(buf);
        body->Deserialize(buf);
    }
    return buf;
}
