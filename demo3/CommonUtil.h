#ifndef  __CommonUtil__
#define  __CommonUtil__

//#include<atlbase.h>
//#include<atlconv.h>
#include <string>
#include <vector>
#ifdef WIN32
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif

# pragma comment(lib,"Iphlpapi.lib")

using namespace std;


namespace CommonUtil
{
	//string 中有中文乱码转wstring 中文
	std::wstring string_to_wstring(const std::string&);    
	//wstring转string
	std::string  wstring_to_string(const std::wstring&);
	 //参数带有中文
	std::string wchar_to_ansi(LPCWSTR);  
	//string中有中文转wstring 中文
	//std::wstring AsciiToUnicode(const std::string& str); 
	std::wstring str_to_wstr(const std::string&); 
	//网络长度
	std::string len_to_network(int);
	//string转UTF8
	std::string string_to_utf8(const std::string&);
	string Utf8ToGBK(string &strUtf8);

	LPCWSTR string_to_LPCWSTR(std::string& );
	//utf8转string
	std::string utf8_to_string(const std::string&);
	//byte转16进制
	void byte2Hex(unsigned char bData, char hex[]);
	//int转string
	std::string int_to_string(int);
	//获取mac
	std::string get_mac();	
	//分割字符串
	void SplitString(const string& s, vector<string>& v, const string& c); 
	//替换
	void replace_all(std::string&, const std::string&, const std::string&);
	//查找值
	std::string parse_value(const std::string& param, const std::string&);
	//统计空格数
	int count_space(std::string str_in);
	//截取非空格字符
	std::string substring2blank(const std::string& str_in);
	//文件转换为字符串
	const std::string get_file_string(const std::string filepath);

	bool get_encoder_clsid(const WCHAR* format, CLSID* pClsid);
	//生成guid
	std::string GuidToString(const GUID &guid);
	GUID CreateGuid();
}

#endif