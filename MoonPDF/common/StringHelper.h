#pragma once
#include <string>
#include <vector>
using namespace std;



class StringHelper {
public:
	StringHelper();
	~StringHelper();
public:
	//将wstring转换成string
	static string Wstring2String(wstring wstr);
	//将string转换成wstring
	static wstring String2Wstring(string str);
	//字符串截取
	static int SubString(wchar_t* tCh, int startPos, int length, wchar_t* outSubStr);
	//将UTF-8转到Unicode
	static long UTF8ToUnicode(char* cUTF8, wchar_t wcUnicode[]);
	//将字符串小写转成大写
	static long ToUpper(char* lower, char* upper);
	static wstring ANSIToUnicode(const string& str);
	static string UnicodeToUTF8(const wstring& str);
	static wstring UTF8ToUnicode(const string& str);
	static string UnicodeToANSI(const wstring& str);
public:
	//获取字符串的长度，占用的内存字节长度,并且带\0结尾符
	static long GetStringMemLength(const char *ch);
	//获取字符串的长度,占用的内存字节长度,并且带\0结尾符
	static long GetStringMemLength(const wchar_t *ch);
	//获取字符串的长度，占用的内存字节长度,并且带\0结尾符
	static long GetStringTCHARMemLength(const wchar_t* ch);
public:
	//解析JSON通过名称获取值，JSON如:{},只有一个对象
	static long AnalysisJsonValue(TCHAR* json, TCHAR* inKey, TCHAR* outVaule);
	//判断字符串是否为空
	static BOOL IsEmpty(TCHAR* tCh);
	//判断字符串是否为空
	static BOOL IsEmpty(char* tCh);
	//字符串比较
	static BOOL Equals(TCHAR* source, TCHAR* desc);
	//字符串比较
	static BOOL Equals(char* source, char* desc);
	//去掉收尾空格
	static TCHAR* Trim(TCHAR* pCh);
	//字符串分割
	static vector< string> split(string str, string pattern);
	//去掉首尾空格
	static string& trim(std::string &s);
	//字符串替换
	static string& string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst);
	//获取随机数,bits随机数的个数
	static string GetRandomNumber(int bits);
	/* {{{ URL编码，提取自PHP
	*	用法：string urlencode(string str_source)
	*	说明：仅不编码 -_. 其余全部编码，空格会被编码为 +
	*/
	static string UrlEncode(string &str_source);

	/* {{{ URL解码，提取自PHP 5.2.17
	*	用法：string urldecode(string str_source)
	*	时间：2012-8-14 By Dewei
	*/
	static string UrlDecode(string &str_source);

	static int htoi(char *s);

	/**
	* 判断字符串是否以start开头
	*/
	static bool startswith(const std::string& str, const std::string& start);

	/**
	* 判断字符串是否以end字符串结束
	*/
	static bool endswith(const std::string& str, const std::string& end);
};
