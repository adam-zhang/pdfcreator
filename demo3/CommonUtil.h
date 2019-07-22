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
	//string ������������תwstring ����
	std::wstring string_to_wstring(const std::string&);    
	//wstringתstring
	std::string  wstring_to_string(const std::wstring&);
	 //������������
	std::string wchar_to_ansi(LPCWSTR);  
	//string��������תwstring ����
	//std::wstring AsciiToUnicode(const std::string& str); 
	std::wstring str_to_wstr(const std::string&); 
	//���糤��
	std::string len_to_network(int);
	//stringתUTF8
	std::string string_to_utf8(const std::string&);
	string Utf8ToGBK(string &strUtf8);

	LPCWSTR string_to_LPCWSTR(std::string& );
	//utf8תstring
	std::string utf8_to_string(const std::string&);
	//byteת16����
	void byte2Hex(unsigned char bData, char hex[]);
	//intתstring
	std::string int_to_string(int);
	//��ȡmac
	std::string get_mac();	
	//�ָ��ַ���
	void SplitString(const string& s, vector<string>& v, const string& c); 
	//�滻
	void replace_all(std::string&, const std::string&, const std::string&);
	//����ֵ
	std::string parse_value(const std::string& param, const std::string&);
	//ͳ�ƿո���
	int count_space(std::string str_in);
	//��ȡ�ǿո��ַ�
	std::string substring2blank(const std::string& str_in);
	//�ļ�ת��Ϊ�ַ���
	const std::string get_file_string(const std::string filepath);

	bool get_encoder_clsid(const WCHAR* format, CLSID* pClsid);
	//����guid
	std::string GuidToString(const GUID &guid);
	GUID CreateGuid();
}

#endif