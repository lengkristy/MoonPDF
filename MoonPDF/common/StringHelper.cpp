#include "../stdafx.h"
#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include "StringHelper.h"

StringHelper::StringHelper()
{
}

StringHelper::~StringHelper()
{
}

string StringHelper::Wstring2String(wstring wstr)
{
	LPCWSTR pwszSrc = wstr.c_str();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
		return std::string("");

	char* pszDst = new char[nLen];
	if (!pszDst)
		return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	std::string str(pszDst);
	delete[] pszDst;
	pszDst = NULL;

	return str;
}

wstring StringHelper::String2Wstring(string str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

long StringHelper::GetStringMemLength(const char *ch)
{
	long count = 0;
	if (ch == NULL)
	{
		return count;
	}
	while (ch[count] != '\0')
	{
		count++;
	}
	return count;
}

long StringHelper::GetStringMemLength(const wchar_t *ch)
{
	return sizeof(wchar_t) * wcslen(ch) + sizeof(wchar_t);
}

long StringHelper::AnalysisJsonValue(TCHAR* json, TCHAR* inKey, TCHAR* outVaule)
{
	long outLenth = 0;
	//首先获取name的长度
	int length = lstrlen(inKey);
	int i = 0;
	int j = 0;
	while (json[i] != _T('\0'))
	{
		if (json[i] == inKey[j] && j < length) //字符串匹配
		{
			i++; j++;
		}
		else
		{
			i++;
			if (length == j)
				break;
			else
				j = 0;
		}
	}
	int k = 0;
	i = i + 2;
	//开始查询值
	while (json[i] != _T('\0'))
	{
		if (json[i] == _T('"'))
			break;
		else
		{
			outVaule[k] += json[i];
			k++;
		}
		i++;
	}
	return outLenth;
}

int StringHelper::SubString(wchar_t* tCh, int startPos, int length, wchar_t* outSubStr)
{
	int j = 0;
	for (int i = startPos; i < startPos + length + 1; i++)
	{
		outSubStr[j] = tCh[i];
		j++;
	}
	//	outSubStr[j] = _T('\0');
	return j--;
}

BOOL StringHelper::IsEmpty(TCHAR* tCh)
{
	if (tCh == NULL)
		return true;
	BOOL flag = false;
	int i = 0;
	while (tCh[i] != '\0')
	{
		i++;
	}
	if (i == 0)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

//判断字符串是否为空
BOOL StringHelper::IsEmpty(char* tCh)
{
	if (tCh == NULL)
		return true;
	BOOL flag = false;
	int i = 0;
	while (tCh[i] != '\0')
	{
		i++;
	}
	if (i == 0)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}


BOOL StringHelper::Equals(TCHAR* source, TCHAR* desc)
{
	BOOL flag = true;
	int i = 0;
	while (source[i] != '\0')
	{
		if (source[i] != desc[i])
		{
			flag = false;
			break;
		}
		i++;
	}
	if (desc[i] != '\0')
	{
		flag = false;
	}
	return flag;
}

BOOL StringHelper::Equals(char* source, char* desc)
{
	BOOL flag = true;
	int i = 0;
	while (source[i] != '\0')
	{
		if (source[i] != desc[i])
		{
			flag = false;
			break;
		}
		i++;
	}
	if (desc[i] != '\0')
	{
		flag = false;
	}
	return flag;
}

long StringHelper::GetStringTCHARMemLength(const wchar_t* ch)
{
	int size = sizeof(wchar_t) * lstrlen(ch) + sizeof(wchar_t);
	return size;
}

TCHAR* StringHelper::Trim(TCHAR* pCh)
{
	long length = GetStringTCHARMemLength(pCh);
	TCHAR* pChArray = new TCHAR[length];
	memset(pChArray, 0, length);
	memcpy(pChArray, pCh, length);
	memset(pCh, 0, length);
	//去掉首空格
	int j = 0;
	for (int i = 0; i < lstrlen(pChArray); i++)
	{
		if (pChArray[i] == _T(' ') && j == 0)
		{
			continue;
		}
		else
		{
			pCh[j] = pChArray[i];
			j++;
		}
	}
	//去掉尾空格
	memset(pChArray, 0, length);
	memcpy(pChArray, pCh, length);
	memset(pCh, 0, length);
	j = 0;
	for (int i = lstrlen(pChArray) - 1; i >= 0; i--)
	{
		if (pChArray[i] == _T(' ') && j == 0)
		{
			continue;
		}
		else
		{
			pCh[j] = pChArray[i];
			j++;
		}
	}
	//字符串cpy
	memset(pChArray, 0, length);
	memcpy(pChArray, pCh, length);
	memset(pCh, 0, length);
	j = 0;
	for (int i = lstrlen(pChArray) - 1; i >= 0; i--)
	{
		pCh[j] = pChArray[i];
		j++;
	}
	delete[] pChArray;
	return pCh;
}

//将UTF-8转到Unicode
long StringHelper::UTF8ToUnicode(char* cUTF8, wchar_t wcUnicode[])
{
	if (cUTF8 == NULL || wcUnicode == NULL)
		return 0;
	long length = 0;
	string sUTF8 = cUTF8;
	length = MultiByteToWideChar(CP_UTF8, 0, sUTF8.c_str(), -1, NULL, 0);
	return MultiByteToWideChar(CP_UTF8, 0, sUTF8.c_str(), -1, (LPWSTR)wcUnicode, length);
}

//将字符串小写转成大写
long StringHelper::ToUpper(char* lower, char* upper)
{
	if (lower == NULL && upper == NULL)
		return 0;
	long length = 0;
	int i = 0;
	while (lower[i] != '\0')
	{
		if (lower[i] <= 122 && lower[i] >= 97)
		{
			upper[i] = lower[i] - 32;
			length++;//实际转化的个数
		}
		else
		{
			upper[i] = lower[i];
		}
		i++;
	}
	return length;
}

wstring StringHelper::ANSIToUnicode(const string& str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	wstring  rt;
	rt = (wchar_t*)pUnicode;
	delete  pUnicode;

	return  rt;
}

string StringHelper::UnicodeToANSI(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

string StringHelper::UnicodeToUTF8(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

wstring StringHelper::UTF8ToUnicode(const string& str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	wstring  rt;
	rt = (wchar_t*)pUnicode;
	delete  pUnicode;

	return  rt;
}

//字符串分割
vector< string> StringHelper::split(string str, string pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

string& StringHelper::trim(std::string &s)
{
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

string& StringHelper::string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
	std::string::size_type pos = 0;
	std::string::size_type srclen = strsrc.size();
	std::string::size_type dstlen = strdst.size();

	while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
	return strBig;
}

//获取随机数,bits随机数的个数
string StringHelper::GetRandomNumber(int bits)
{
	string str = "";
	char buf[2] = { 0 };
	for (int i = 0; i < bits; i++)
	{
		int rd = rand() % 10;
		sprintf_s(buf, "%d", rd);
		str += buf;
		memset(buf, 0, 2);
	}
	return str;
}

/* {{{ URL编码，提取自PHP
*	用法：string urlencode(string str_source)
*	说明：仅不编码 -_. 其余全部编码，空格会被编码为 +
*/
string StringHelper::UrlEncode(string &str_source)
{
	char const *in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	string out_str;
	register unsigned char c;
	unsigned char *to, *start;
	unsigned char const *from, *end;
	unsigned char hexchars[] = "0123456789ABCDEF";

	from = (unsigned char *)in_str;
	end = (unsigned char *)in_str + in_str_len;
	start = to = (unsigned char *)malloc(3 * in_str_len + 1);

	while (from < end) {
		c = *from++;

		if (c == ' ') {
			*to++ = '+';
		}
		else if ((c < '0' && c != '-' && c != '.') ||
			(c < 'A' && c > '9') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z')) {
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
		}
		else {
			*to++ = c;
		}
	}
	*to = 0;

	out_str_len = to - start;
	out_str = (char *)start;
	free(start);
	return out_str;
}

string StringHelper::UrlDecode(string &str_source)
{
	char const *in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	string out_str;
	char *str;

	str = _strdup(in_str);
	char *dest = str;
	char *data = str;

	while (in_str_len--) {
		if (*data == '+') {
			*dest = ' ';
		}
		else if (*data == '%' && in_str_len >= 2 && isxdigit((int) *(data + 1))
			&& isxdigit((int) *(data + 2))) {
			*dest = (char)htoi(data + 1);
			data += 2;
			in_str_len -= 2;
		}
		else {
			*dest = *data;
		}
		data++;
		dest++;
	}
	*dest = '\0';
	out_str_len = dest - str;
	out_str = str;
	free(str);
	return out_str;
}

int StringHelper::htoi(char *s)
{
	int value;
	int c;

	c = ((unsigned char *)s)[0];
	if (isupper(c))
		c = tolower(c);
	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

	c = ((unsigned char *)s)[1];
	if (isupper(c))
		c = tolower(c);
	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

	return (value);
}

/**
* 判断字符串是否以start开头
*/
bool StringHelper::startswith(const std::string& str, const std::string& start)
{
	int srclen = str.size();
	int startlen = start.size();
	if (srclen >= startlen)
	{
		string temp = str.substr(0, startlen);
		if (temp == start)
			return true;
	}

	return false;
}

/**
* 判断字符串是否以end字符串结束
*/
bool StringHelper::endswith(const std::string& str, const std::string& end)
{
	int srclen = str.size();
	int endlen = end.size();
	if (srclen >= endlen)
	{
		string temp = str.substr(srclen - endlen, endlen);
		if (temp == end)
			return true;
	}

	return false;
}