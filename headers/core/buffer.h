#pragma once
#include <iostream>
#include <vector>
#include <type_traits>

class Buffer
{
public:
	const char* data() const
	{
		return m_buf.data();
	}

	char* data()
	{
		return m_buf.data();
	}

	size_t size() const
	{
		return m_buf.size();
	}

	void resize(size_t newSize)
	{
		m_buf.resize(newSize);
	}

	void expand(size_t additional)
	{
		m_buf.resize(m_buf.size() + additional);
	}

	void trunk(size_t sizeToRemove)
	{
		m_buf.erase(m_buf.begin(), m_buf.begin() + sizeToRemove);
	}

	void append(const void* src, size_t srcSize)
	{
		expand(srcSize);
		memcpy(data() + size() - srcSize, src, srcSize);
	}

	void extractTo(void* dst, size_t dstSize)
	{
		memcpy(dst, data(), dstSize);
		trunk(dstSize);
	}

private:
	std::vector<char> m_buf;
};

template<typename T>
Buffer& operator <<(Buffer& buf, T value)
{
	static_assert(std::is_fundamental_v<T>, "Buffer::operator<<: T must be a primitive-like type. Overload it if needed");
	buf.append(&value, sizeof(value));
	return buf;
}

template<typename T>
Buffer& operator >>(Buffer& buf, T& value)
{
	static_assert(std::is_fundamental_v<T>, "Buffer::operator>>: T must be a primitive-like type. Overload it if needed");
	buf.extractTo(&value, sizeof(value));
	return buf;
}

Buffer& operator <<(Buffer& buf, const std::string& s)
{
	buf << s.size();
	buf.append(s.data(), s.size());
	return buf;
}

Buffer& operator >>(Buffer& buf, std::string& s)
{
	size_t size = 0;
	buf >> size;
	char* b = new char[size + 1];
	b[size] = '\0';
	buf.extractTo(b, size);
	s.assign(b);
	delete[] b;
	b = nullptr;
	return buf;
}
