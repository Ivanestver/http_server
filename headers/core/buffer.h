#pragma once
#include <iostream>
#include <vector>
#include <type_traits>
#include "export_decl.h"

class Buffer
{
public:
	const char* data() const;
	char* data();
	size_t size() const;
	void resize(size_t newSize);
	void expand(size_t additional);
	void trunk(size_t sizeToRemove);
	void append(const void* src, size_t srcSize);
	void extractTo(void* dst, size_t dstSize);

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
