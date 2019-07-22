#include "StdAfx.h"
#include "CodeConverter.h"
#include <Windows.h>
#include <vector>

CodeConverter::CodeConverter(void)
{
}


CodeConverter::~CodeConverter(void)
{
}


std::wstring CodeConverter::AnsiToUtf16(const std::string& ansi)
{
    int length = ::MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, NULL, 0);
	std::vector<wchar_t> buffer(length + 1);
    ::MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, &buffer[0], length);
	return &buffer[0];
}

std::string CodeConverter::Utf16ToAnsi(const std::wstring& unicode)
{
	int length = ::WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
	std::vector<char> buffer(length + 1);
	::WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), -1, &buffer[0], length, NULL, NULL);
	return &buffer[0];
}