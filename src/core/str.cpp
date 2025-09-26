#include "core/str.h"
#include <string>
#include <type_traits>
#include <stdexcept>
#include <iostream>

struct String::Impl
{
	~Impl()
	{
		delete[] m_str;
	}

	size_t m_length{ 0 };
	char* m_str{ nullptr };
};

String::String()
	: m_impl{ new String::Impl{} }
{
	m_impl->m_str = new char[1] { '\0' };
}

String::String(const char* str)
{
	allocNewStr(getSize(str));
	std::memcpy(m_impl->m_str, str, m_impl->m_length);
}

String::String(const std::string& str)
	: String(str.data())
{
}

String::String(const String& other)
{
	*this = other;
}

String::String(String&& other) noexcept
{
	*this = std::move(other);
}

String& String::operator=(const String& other)
{
	allocNewStr(other.m_impl->m_length);
	std::memcpy(m_impl->m_str, other.m_impl->m_str, m_impl->m_length);
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	delete[] m_impl->m_str;
	m_impl->m_str = other.m_impl->m_str;
	m_impl->m_length = other.m_impl->m_length;
	other.m_impl->m_length = 0;
	other.m_impl->m_str = new char[1] { '\0' };
	return *this;
}

String String::operator+(const String& other) const noexcept
{
	const size_t newSize = m_impl->m_length + other.m_impl->m_length + 1;
	char* newS = new char[newSize];
	std::memcpy(newS, m_impl->m_str, m_impl->m_length);
	std::memcpy(newS + m_impl->m_length, other.m_impl->m_str, other.m_impl->m_length);
	newS[newSize] = '\0';
	String s{ newS };
	delete[] newS;
	return s;
}

String String::operator+(const std::string& other) const noexcept
{
	const size_t newSize = m_impl->m_length + other.length() + 1;
	char* newS = new char[newSize];
	std::memcpy(newS, m_impl->m_str, m_impl->m_length);
	std::memcpy(newS + m_impl->m_length, other.c_str(), other.length());
	newS[newSize] = '\0';
	String s{ newS };
	delete[] newS;
	return s;
}

String String::operator+(const char other) const noexcept
{
	const size_t newSize = m_impl->m_length + 1;
	char* newS = new char[newSize];
	std::memcpy(newS, m_impl->m_str, m_impl->m_length);
	newS[newSize - 1] = other;
	newS[newSize] = '\0';
	String s{ newS };
	delete[] newS;
	return s;
}

void String::operator>>(std::ostream& buf) const noexcept
{
	buf << m_impl->m_str;
}

bool String::operator <(const String& other) const noexcept
{
	size_t minSize = std::min(this->length(), other.length());
	for (size_t i = 0; i < minSize; ++i)
	{
		if ((*this)[i] < other[i])
			return true;
	}

	for (size_t i = 0; i < minSize; ++i)
	{
		if ((*this)[i] > other[i])
			return false;
	}

	return this->length() != other.length() || this->length() < other.length();
}

String::~String()
{
	delete m_impl;
}

char String::operator[](size_t idx) const
{
	if (idx >= m_impl->m_length)
		throw std::out_of_range("Index was out of bounds");
	return m_impl->m_str[idx];
}

size_t String::length() const
{
	return m_impl->m_length;
}

bool String::is_empty() const
{
	return m_impl->m_length == 0;
}

std::vector<String> String::split(char separator) const
{
	std::vector<String> substrings;
	std::vector<char> buf;
	for (size_t i = 0; i < m_impl->m_length; ++i)
	{
		if (m_impl->m_str[i] == separator)
		{
			buf.emplace_back('\0');
			substrings.emplace_back(buf.data());
			buf.clear();
		}
		else
		{
			buf.emplace_back(m_impl->m_str[i]);
		}
	}
	buf.emplace_back('\0');
	substrings.emplace_back(buf.data());
	return substrings;
}

String String::replace(char oldChar, char newChar) const
{
	char* newC = new char[m_impl->m_length + 1];
	newC[m_impl->m_length] = '\0';
	for (size_t i = 0; i < m_impl->m_length; ++i)
	{
		if (m_impl->m_str[i] == oldChar)
			newC[i] = newChar;
		else
			newC[i] = m_impl->m_str[i];
	}
	String s{ newC };
	delete[] newC;
	return s;
}

const String String::substr(size_t start, size_t count) const
{
	if (start >= count || start >= length() || count > (length() - 1 - start))
		return String{};

	std::string s;
	for (size_t i = 0; i < count; ++i)
		s += m_impl->m_str[start + i];
	return String{ s };
}

bool String::contains(const char c) const noexcept
{
	return find(c) != -1;
}

long long String::find(const char c) const noexcept
{
	for (size_t i = 0; i < m_impl->m_length; ++i)
	{
		if (m_impl->m_str[i] == c)
			return (long long)i;
	}
	
	return -1;
}

const char* String::data() const
{
	return m_impl->m_str;
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

void String::allocNewStr(size_t size) noexcept
{
	m_impl->m_length = size;
	delete[] m_impl->m_str;
	m_impl->m_str = new char[m_impl->m_length + 1];
	m_impl->m_str[m_impl->m_length] = '\0';
}

Buffer& String::Serialize(Buffer& buf) const
{
	buf << m_impl->m_length;
	buf.append(m_impl->m_str, m_impl->m_length);
	return buf;
}

Buffer& String::Deserialize(Buffer& buf)
{
	size_t size = 0;
	buf >> size;
	if (size != m_impl->m_length)
		allocNewStr(size);
	
	buf.extractTo(m_impl->m_str, m_impl->m_length);
	return buf;
}

CORE std::ostream& operator<<(std::ostream& buf, const String& s)
{
	s >> buf;
	return buf;
}

CORE bool operator==(const String& left, const String& right)
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

CORE bool operator!=(const String& left, const String& right)
{
	return !(left == right);
}
