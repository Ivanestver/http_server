#pragma once
#include "str_fw.h"
#include <vector>
#include <string>
#include <memory>
#include "buffer.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif


class CORE String
{
public:
	String();
	String(const char* str);
	String(const std::string& str);
	String(const String& other);
	String(String&& other) noexcept;
	String(size_t newSize);

	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;

	String operator +(const String& other) const noexcept;
	String operator +(const std::string& other) const noexcept;
	String operator +(const char other) const noexcept;
	void operator >> (std::ostream& buf) const noexcept;
	void operator << (std::istream& buf) const noexcept;

	~String();

	char operator[](size_t idx) const;

	inline size_t length() const;
	inline bool is_empty() const;

	std::vector<String> split(char separator) const;
	String replace(char oldChar, char newChar) const;
	const String substr(size_t start, size_t count) const;
	bool contains(const char c) const noexcept;
	long long find(const char c) const noexcept;

	const char* data() const;

	std::string::iterator begin();
	std::string::iterator end();

	std::string::const_iterator begin() const;
	std::string::const_iterator end() const;

private:
	size_t getSize(const char* str) const noexcept;

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

CORE std::ostream& operator <<(std::ostream& buf, const String& s);
CORE std::istream& operator >>(std::istream& buf, String& s);
CORE Buffer& operator <<(Buffer& buf, const String& s);
CORE bool operator ==(const String& left, const String& right);
CORE bool operator !=(const String& left, const String& right);
CORE bool operator <(const String& left, const String& right);

template<typename INTEGRAL>
INTEGRAL ToIntegral(const String& s)
{
	static_assert(std::is_integral_v<INTEGRAL>, "ToIntegral: INTEGRAL must be an integral type");
	INTEGRAL integral{ 0 };
	INTEGRAL n = 1;
	for (int i = (int)s.length() - 1; i >= 0; --i)
	{
		integral += (INTEGRAL)(s[i] - '0') * n;
		n *= 10;
	}
	return integral;
}

template<typename FLOATING>
FLOATING ToFloating(const String& s)
{
	static_assert(std::is_floating_point_v<FLOATING>, "ToFloating: FLOATING must be a floating point type");
	long long dotPosition = s.find('.');
	if (dotPosition == -1)
		return (FLOATING)ToIntegral<long long>(s);

	FLOATING floating{ 0.0 };
	size_t n = 1;
	// First parse base
	for (long long i = dotPosition - 1; i >= 0; ++i)
	{
		floating += (FLOATING)(s[i] - '0') * n;
		n *= 10;
	}

	// Then parse mantiss
	n = 10;
	for (long long i = dotPosition + 1; i < (long long)s.length(); ++i)
	{
		floating += (FLOATING)(s[i] - '0') * (1.0 / n);
		n *= 10;
	}
	return floating;
}

namespace std
{
	template<>
	struct hash<String>
	{
		std::size_t operator()(const String& str) const
		{
			return std::hash<std::string>{}(std::string{ str.data() });
		}
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
