#include "core/buffer.h"

struct Buffer::Impl
{
	std::vector<char> m_buf;
};

Buffer::Buffer()
	: m_impl{ new Buffer::Impl{} }
{
}

Buffer::~Buffer()
{
	delete m_impl;
	m_impl = nullptr;
}

const char* Buffer::data() const
{
	return m_impl->m_buf.data();
}

char* Buffer::data()
{
	return m_impl->m_buf.data();
}

size_t Buffer::size() const
{
	return m_impl->m_buf.size();
}

void Buffer::resize(size_t newSize)
{
	m_impl->m_buf.resize(newSize);
}

void Buffer::expand(size_t additional)
{
	m_impl->m_buf.resize(m_impl->m_buf.size() + additional);
}

void Buffer::trunk(size_t sizeToRemove)
{
	m_impl->m_buf.erase(m_impl->m_buf.begin(), m_impl->m_buf.begin() + sizeToRemove);
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
