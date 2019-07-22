#include "stdafx.h"
#include "CommonUtil.h"
#include <sstream>
#include <Windows.h>
#include <IPHlpApi.h>
#include "gdi.h"

const int LEN = 4;

std::wstring CommonUtil::string_to_wstring(const std::string& str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

std::string CommonUtil::wstring_to_string(const std::wstring& wstr)
{
	std::string str;
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');
	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);
	if (nResult == 0)
	{
		return "";
	}
	return str;
}
  
std::string CommonUtil::wchar_to_ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);

	if (nLen<= 0) return std::string("");

	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;

	std::string strTemp(pszDst);
	delete [] pszDst;

	return strTemp;
}

std::wstring CommonUtil::str_to_wstr(const std::string& str)
{
	setlocale(LC_ALL, "chs");
	const char* point_to_source = str.c_str();
	size_t new_size = str.size() + 1;
	wchar_t *point_to_destination = new wchar_t[new_size];
	wmemset(point_to_destination, 0, new_size);
	mbstowcs(point_to_destination, point_to_source, new_size);
	std::wstring result = point_to_destination;
	delete[]point_to_destination;
	setlocale(LC_ALL, "C");
	return result;

}

std::string CommonUtil::len_to_network(int len)
{
	char network_len[LEN + 1] = {0};
	int nTmp = htonl(len);
	memcpy(network_len, &nTmp, sizeof(nTmp));
	return string(network_len, sizeof(nTmp));
}

void CommonUtil::byte2Hex(unsigned char bData, char hex[])
{
	int high = bData / 16, low = bData % 16;
	hex[0] = (high < 10) ? ( '0' + high) : ('A' + high - 10);
	hex[1] = (low < 10)  ? ('0' + low) : ('A' + low - 10);
}

std::string CommonUtil::string_to_utf8(const std::string & str)  
{  
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);  

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	ZeroMemory(pwBuf, nwLen * 2 + 2);  

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);  

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);  

	char * pBuf = new char[nLen + 1];  
	ZeroMemory(pBuf, nLen + 1);  

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);  

	std::string retStr(pBuf);  

	delete []pwBuf;  
	delete []pBuf;  

	pwBuf = NULL;  
	pBuf = NULL;  

	return retStr;  
}

string CommonUtil::Utf8ToGBK(string &strUtf8)
{
	int len=MultiByteToWideChar(CP_UTF8, 0,(LPCSTR)strUtf8.c_str(), -1, NULL,0);
	wchar_t * wszGBK = new wchar_t[len];
	memset(wszGBK,0,len);
	MultiByteToWideChar(CP_UTF8, 0,(LPCSTR)strUtf8.c_str(), -1, wszGBK, len); 

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK=new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL);
	delete[] szGBK;
	delete[] wszGBK;
	string strGBK = szGBK;
	return strGBK;
}


std::string CommonUtil::utf8_to_string(const std::string & str)  
{  
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);  

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	memset(pwBuf, 0, nwLen * 2 + 2);  

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);  

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);  

	char * pBuf = new char[nLen + 1];  
	memset(pBuf, 0, nLen + 1);  

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);  

	std::string retStr = pBuf;  

	delete []pBuf;  
	delete []pwBuf;  

	pBuf = NULL;  
	pwBuf = NULL;  

	return retStr;  
}  

std::string CommonUtil::get_mac()
{
	ULONG ulsize = 0;
	PIP_ADAPTER_INFO pInfo = NULL;
	int temp;
	char MacAddress[64] = {0};
	temp = GetAdaptersInfo(pInfo, &ulsize);
	pInfo = (PIP_ADAPTER_INFO)malloc(ulsize);
	temp = GetAdaptersInfo(pInfo, &ulsize);

	int iCount = 0;
	while(pInfo)
	{
		for (int i = 0; i < (int)pInfo->AddressLength; ++i)
		{
			byte2Hex(pInfo->Address[i], &MacAddress[iCount]);
			iCount += 2;
			if(i < (int)pInfo->AddressLength -1)
				MacAddress[iCount++] = ':';
			else
				MacAddress[iCount++] = 0;
		}
		//pInfo = pInfo->Next;  遍历pc机中所有的mac地址
		pInfo = NULL;    //默认值获取第一个mac地址
	}

	//	ATLTRACE("mac地址:%s\n", MacAddress);
	//std::wstring mac = SingleBytetoMultiByte(MacAddress);
	return std::string(MacAddress);

}

std::string CommonUtil::int_to_string(int num)
{
	ostringstream stream;

	stream<<num;  //n为int类型

	return stream.str();

}

void CommonUtil::SplitString(const string& s, std::vector<std::string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while(string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2-pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void CommonUtil::replace_all(std::string& source, const std::string& old, const std::string& newvalue)
{
	int pos = 0;
	while ((pos = source.find(old, pos)) != source.npos)
	{
		source.replace(pos, old.length(), newvalue);
		pos += newvalue.length();
	}
}

LPCWSTR CommonUtil::string_to_LPCWSTR(std::string& str)
{
	size_t size = str.length();
	wchar_t *buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0,str.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = '\0';  //确保以 '\0' 结尾 
	return buffer;
}

std::string CommonUtil::parse_value(const std::string& param, const std::string& name)
{
	size_t begin_pos = param.find(name);
	if(begin_pos != std::string::npos)
	{
		size_t end_pos = param.find("&", begin_pos);
		if(end_pos != std::string::npos)
		{
			std::string trade_type = param.substr(begin_pos+name.size()+1, end_pos-begin_pos-name.size()-1);
			return trade_type;
		}
		else{
			std::string trade_type = param.substr(begin_pos+name.size()+1);
			return trade_type;
		}
	}

	return "";
}


int CommonUtil::count_space(std::string str_in){
	int count = 0;
	for(size_t i = 0; i<str_in.size(); i++){
		if(str_in[i] == ' '){
			count++;
		}
		else{
			break;
		}
	}
	return count;
}

std::string CommonUtil::substring2blank(const std::string& str_in){
	std::string result;
	std::size_t found = str_in.find(" ");
	if(found>0){
		result = str_in.substr(0,found);
		return result;
	}
	return "";
}

const std::string CommonUtil::get_file_string(const std::string filepath)
{
	std::string str;
	FILE *fp;
	fp = fopen(filepath.c_str(), "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		int file_size;
		file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char *tmp = new char[file_size + 1];
		tmp[file_size] = '\0';
		fread(tmp, file_size, sizeof(char), fp);
		fclose(fp);
		str.append(tmp, file_size);
		delete[]tmp;
	}
	return str;
}

bool CommonUtil::get_encoder_clsid(const WCHAR* format, CLSID* pClsid)  
{  
	UINT num = 0, size = 0;  

	Gdiplus::GetImageEncodersSize(&num, &size);  
	if(size == 0)  
		return false;  // Failure  

	Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));  

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);  
	bool found = false;  
	for (UINT ix = 0; !found && ix < num; ++ix)   
	{  
		if (_wcsicmp(pImageCodecInfo[ix].MimeType, format) == 0)   
		{  
			*pClsid = pImageCodecInfo[ix].Clsid;  
			found = true;  
			break;  
		}  
	}  

	free(pImageCodecInfo);  
	return found;  
	return 0;
}

GUID CommonUtil::CreateGuid()
{
	GUID guid;
#ifdef WIN32
	CoCreateGuid(&guid);
#else
	uuid_generate(reinterpret_cast<unsigned char *>(&guid));
#endif
	return guid;
}

std::string CommonUtil::GuidToString(const GUID &guid)
{
	char buf[64] = {0};
#ifdef __GNUC__
	snprintf(
#else // MSVC
	_snprintf_s(
#endif
		buf,
		sizeof(buf),
		"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return std::string(buf);
}