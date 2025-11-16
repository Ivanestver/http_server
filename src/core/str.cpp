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
	: m_impl{ new String::Impl{} }
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

String& String::operator=(const String& other)
{
	m_impl->m_str = other.m_impl->m_str;
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	delete m_impl;
	m_impl = other.m_impl;
	other.m_impl = nullptr;
	return *this;
}

String String::operator+(const String& other) const noexcept
{
	return this->operator+(other.m_impl->m_str);
}

String String::operator+(const std::string& other) const noexcept
{
	String s;
	size_t thisLength = length();
	s.m_impl->m_str.resize(thisLength + other.length());
	for (size_t i = 0; i < thisLength; ++i)
		s.m_impl->m_str[i] = m_impl->m_str[i];

	for (size_t i = 0; i < other.length(); ++i)
		s.m_impl->m_str[thisLength + i] = other[i];

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

String::~String()
{
	delete m_impl;
}

char String::operator[](size_t idx) const
{
	if (idx >= m_impl->m_str.size())
		throw std::out_of_range("Index was out of bounds");
	return m_impl->m_str[idx];
}

size_t String::length() const
{
	return m_impl->m_str.length();
}

bool String::is_empty() const
{
	return m_impl->m_str.empty();
}

std::vector<String> String::split(char separator) const
{
	std::vector<String> substrings;
	std::vector<char> buf;
	for (size_t i = 0; i < m_impl->m_str.size(); ++i)
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
	String s;
	s.m_impl->m_str.resize(this->length());
	for (size_t i = 0; i < length(); ++i)
	{
		if (m_impl->m_str[i] == oldChar)
			s.m_impl->m_str[i] = newChar;
		else
			s.m_impl->m_str[i] = m_impl->m_str[i];
	}
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

void String::allocNewStr(size_t size) noexcept
{
	m_impl->m_str.resize(size);
}

Buffer& String::Serialize(Buffer& buf) const
{
	buf << (int)length();
	for (char c : m_impl->m_str)
		buf << c;
	return buf;
}

Buffer& String::Deserialize(Buffer& buf)
{
	return buf;
}

CORE std::ostream& operator<<(std::ostream& buf, const String& s)
{
	s >> buf;
	return buf;
}

CORE std::istream& operator>>(std::istream& buf, const String& s)
{
	s << buf;
	return buf;
}

CORE Buffer& operator <<(Buffer& buf, const String& s)
{
	return buf << s.data();
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

CORE bool operator<(const String& left, const String& right)
{
	size_t minSize = std::min(left.length(), right.length());
	for (size_t i = 0; i < minSize; ++i)
	{
		if (left[i] == right[i])
			continue;

		if (left[i] > right[i])
			return false;

		return true;
	}
	if (left.length() == right.length())
		return false;
	return left.length() < right.length();
}
