#ifndef __DEBUGGER__H
#define __DEBUGGER__H

#include <string>
#include <sstream>

class Debugger
{
private:
	Debugger();
public:
	static void write(const std::string& notice);
	static void write(const std::string&, size_t);
	static void write(const std::string&, const std::string&);
	static void writeFile(const std::string&);

	template<typename A, typename B>
	static void write(const std::string& notice, const A& value1, const std::string& notice2, const B& value2)
	{
		stringstream ss;
		ss << notice << ":" << value1 << " " << notice2 << ":" << value2;
		write(ss.str());
	}

	template<typename A, typename B, typename C>
	static void write(const std::string& notice1, const A& value1, const std::string& notice2, const B& value2, const std::string& notice3, const C& value3)
	{
		stringstream ss;
		ss << notice1 << ":" << value1
			<< " " << notice2 << ":" << value2
			<< " " << notice3 << ":" << value3;
		write(ss.str());
	}

	template<typename A, typename B, typename C, typename D>
	static void write(const std::string& notice1, const A& value1, const std::string& notice2, const B& value2, const std::string& notice3, const C& value3, const std::string& notice4, const D& value4)
	{
		stringstream ss;
		ss << notice1 << ":" << value1
			<< " " << notice2 << ":" << value2
			<< " " << notice3 << ":" << value3
			<< " " << notice4 << ":" << value4;
		write(ss.str());
	}


	static void write(const std::wstring& notice);

	template<typename T>
	static void write(const std::wstring notice, const T& value)
	{
		std::wstringstream ws;
		ws << notice << ":" << value;
		write(ws.str());
	}

};
#endif//__DEBUGGER__H