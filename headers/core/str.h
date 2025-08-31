#pragma once
#include "export_decl.h"
#include "iserializable.h"
#include <iosfwd>
#include <vector>

class CORE String : public ISerializable, public IDeserializable
{
public:
	String();
	String(const char* str);
	String(const std::string& str);
	String(const String& other);
	String(String&& other) noexcept;

	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;

	String operator +(const String& other) const noexcept;
	void operator >> (std::ostream& buf) const noexcept;

	~String();

	char operator[](size_t idx) const;

	size_t length() const;
	bool is_empty() const;

	std::vector<String> split(char separator) const;
	String replace(char oldChar, char newChar) const;

	const char* data() const;

private:
	size_t getSize(const char* str) const noexcept;
	inline void allocNewStr(size_t size) noexcept;

private:
	struct Impl;
	Impl* m_impl{ nullptr };

	// Унаследовано через ISerializable
	Buffer& Serialize(Buffer& buf) const override;

	// Унаследовано через IDeserializable
	Buffer& Deserialize(Buffer& buf) override;
};

CORE std::ostream& operator <<(std::ostream& buf, const String& s);
