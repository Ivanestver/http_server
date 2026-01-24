#include "core/buffer.h"

struct Buffer::Impl
{
	std::vector<char> m_buf;
};

Buffer::Buffer()
	: m_impl{ std::make_unique<Impl>() }
{
}

Buffer::~Buffer() = default;

const char* Buffer::data() const
{
	return m_impl->m_buf.data();
}

char* Buffer::data()
{
	return m_impl->m_buf.data();
}

std::vector<uint8_t> Buffer::to_bytes() const
{
	return std::vector<uint8_t>(m_impl->m_buf.begin(), m_impl->m_buf.end());
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
	size_t realSize = std::min(sizeToRemove, m_impl->m_buf.size());
	m_impl->m_buf.erase(m_impl->m_buf.begin(), m_impl->m_buf.begin() + realSize);
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
