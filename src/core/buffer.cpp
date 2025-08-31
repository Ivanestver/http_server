#include "core/buffer.h"

const char* Buffer::data() const
{
	return m_buf.data();
}

char* Buffer::data()
{
	return m_buf.data();
}

size_t Buffer::size() const
{
	return m_buf.size();
}

void Buffer::resize(size_t newSize)
{
	m_buf.resize(newSize);
}

void Buffer::expand(size_t additional)
{
	m_buf.resize(m_buf.size() + additional);
}

void Buffer::trunk(size_t sizeToRemove)
{
	m_buf.erase(m_buf.begin(), m_buf.begin() + sizeToRemove);
}

void Buffer::append(const void* src, size_t srcSize)
{
	expand(srcSize);
	memcpy(data() + size() - srcSize, src, srcSize);
}

void Buffer::extractTo(void* dst, size_t dstSize)
{
	memcpy(dst, data(), dstSize);
	trunk(dstSize);
}
