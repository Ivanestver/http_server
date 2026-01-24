#include "core/str.h"
#include <string>
#include <type_traits>
#include <stdexcept>
#include <iostream>

struct String::Impl
{
	std::string m_str;
};

String::String()
	: m_impl{ std::make_unique<Impl>() }
{
}

String::String(const char* str)
	: String()
{
	m_impl->m_str.assign(str);
}

String::String(const std::string& str)
	: String(str.data())
{
}

String::String(const String& other)
	: String()
{
	*this = other;
}

String::String(String&& other) noexcept
	: String()
{
	*this = std::move(other);
}

String::String(size_t newSize)
	: String()
{
	m_impl->m_str.resize(newSize);
}

String& String::operator=(const String& other)
{
	m_impl->m_str = other.m_impl->m_str;
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	m_impl.reset(other.m_impl.release());
	return *this;
}

String String::operator+(const String& other) const noexcept
{
	return this->operator+(other.m_impl->m_str);
}

String String::operator+(const std::string& other) const noexcept
{
	String s;
	s.m_impl->m_str.reserve(this->length() + other.size());
	s.m_impl->m_str.append(this->m_impl->m_str).append(other);
	return s;
}

String String::operator+(const char other) const noexcept
{
	String s;
	s.m_impl->m_str = m_impl->m_str + other;
	return s;
}

void String::operator>>(std::ostream& buf) const noexcept
{
	buf << (int)length();
	for (char c : m_impl->m_str)
		buf << c;
}

void String::operator<<(std::istream& buf) const noexcept
{
	int size{ 0 };
	buf >> size;
	m_impl->m_str.resize(size);
	for (int i = 0; i < size; ++i)
	{
		char c;
		buf >> c;
		m_impl->m_str[i] = c;
	}
}

String::~String() = default;

char String::operator[](size_t idx) const
{
	if (idx >= m_impl->m_str.size())
		throw std::out_of_range("Index is out of bounds");
	return m_impl->m_str[idx];
}

inline size_t String::length() const
{
	return m_impl->m_str.length();
}

inline bool String::is_empty() const
{
	return m_impl->m_str.empty();
}

std::vector<String> String::split(char separator) const
{
	std::vector<String> substrings;
	std::vector<char> buf;
	for (char c : m_impl->m_str)
	{
		if (c == separator)
		{
			buf.emplace_back('\0');
			substrings.emplace_back(buf.data());
			buf.clear();
		}
		else
		{
			buf.emplace_back(c);
		}
	}
	buf.emplace_back('\0');
	substrings.emplace_back(buf.data());
	return substrings;
}

String String::replace(char oldChar, char newChar) const
{
	String s{ this->length() };
	for (size_t i = 0; i < length(); ++i)
	{
		if (m_impl->m_str[i] == oldChar)
			s.m_impl->m_str[i] = newChar;
		else
			s.m_impl->m_str[i] = this->m_impl->m_str[i];
	}
	return s;
}

const String String::substr(size_t start, size_t count) const
{
	if (start >= length())
		return String{};

	String s{ count };
	size_t realCount = std::min(count, length() - 1 - start);
	for (size_t i = 0; i < realCount; ++i)
		s.m_impl->m_str[i] = this->m_impl->m_str[start + i];
	return s;
}

bool String::contains(const char c) const noexcept
{
	return find(c) != -1;
}

long long String::find(const char c) const noexcept
{
	return m_impl->m_str.find(c);
}

const char* String::data() const
{
	return m_impl->m_str.c_str();
}

std::string::iterator String::begin()
{
	return m_impl->m_str.begin();
}

std::string::iterator String::end()
{
	return m_impl->m_str.end();
}

std::string::const_iterator String::begin() const
{
	return m_impl->m_str.begin();
}

std::string::const_iterator String::end() const
{
	return m_impl->m_str.end();
}

size_t String::getSize(const char* str) const noexcept
{
	constexpr int maxsize = 1'048'576;
	size_t size = 0;
	while (size < maxsize)
	{
		if (str[size] == '\0')
			break;
		size++;
	}
	return size;
}

std::ostream& operator<<(std::ostream& buf, const String& s)
{
	s >> buf;
	return buf;
}

std::istream& operator>>(std::istream& buf, const String& s)
{
	s << buf;
	return buf;
}

Buffer& operator <<(Buffer& buf, const String& s)
{
	return buf << s.data();
}

bool operator==(const String& left, const String& right)
{
	if (left.length() != right.length())
		return false;

	for (size_t i = 0; i < left.length(); ++i)
	{
		if (left[i] != right[i])
			return false;
	}

	return true;
}

bool operator!=(const String& left, const String& right)
{
	return !(left == right);
}

bool operator<(const String& left, const String& right)
{
	const size_t leftLength = left.length();
	const size_t rightLength = right.length();
	size_t minSize = std::min(leftLength, rightLength);
	for (size_t i = 0; i < minSize; ++i)
	{
		if (left[i] == right[i])
			continue;

		if (left[i] > right[i])
			return false;

		return true;
	}
	return leftLength < rightLength;
}
