#pragma once

#include <string>

class CodeConverter
{
public:
	CodeConverter(void);

	~CodeConverter(void);
private:
public:
	static std::wstring AnsiToUtf16(const std::string& ansi);
	static std::string Utf16ToAnsi(const std::wstring&);
	static std::wstring Utf8ToUtf16(const std::string& utf8);
	static std::string Utf16ToUtf8(const std::wstring& utf16);
	static std::string AnsiToUtf8(const std::string&);
	static std::string Utf8ToAnsi(const std::string&);
};

