#include "stdafx.h"
#include "Debugger.h"
#include <windows.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <Windows.h>

using namespace std;

//string applicationPath()
//{
//	vector<char> buffer(MAX_PATH);
//}
string modulePath()
{
	vector<char> buffer(MAX_PATH);
	//GetModuleFileNameA(AfxGetInstanceHandle(), &buffer[0], MAX_PATH);
	GetModuleFileNameA(NULL, &buffer[0], MAX_PATH);
	string path(&buffer[0]);
	return path.substr(0, path.rfind('\\') + 1);
}


void Debugger::writeFile(const string& text)
{
	try
	{
		auto fileName = modulePath() + "output.txt";
		fstream file(fileName, ios::out|ios::app);
		if (file.good())
		{
			file << text;
		}
		else
			write("can not open file");
	}
	catch(std::exception& e)
	{
		write(e.what());
	}
}

void Debugger::write(const std::string& notice)
{
	auto out = notice + "\n";
	OutputDebugStringA(out.c_str());
	//MessageBoxA(NULL, notice, "", 0);
	//writeFile(out);
}

void Debugger::write(const std::string& notice, size_t value)
{
	std::stringstream ss;
	ss << notice << ":" << value;
	write(ss.str());
}


void Debugger::write(const std::string& notice, const std::string& value)
{
	std::stringstream ss;
	ss << notice << ":" << value;
	write(ss.str());
}

void Debugger::write(const std::wstring& notice)
{
	MessageBox(NULL, notice.c_str(), TEXT(""), 0);
}