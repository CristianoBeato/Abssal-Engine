
#ifndef _STRING_H_
#define _STRING_H_

#include "sys/sys_types.h"

#if 1
//typedef char	btChar;
typedef	char	btChar;
typedef wchar_t	btUnicodeChar;

typedef std::wstring	btUnicodeString;
typedef std::string		btString;
#else
//typedef char	btChar;
typedef char	btChar;
typedef Sint16	btUnicodeChar;

typedef std::basic_string<btUnicodeChar, std::char_traits<btUnicodeChar>, std::allocator<btUnicodeChar>>	btUnicodeString;
typedef std::basic_string<btChar, std::char_traits<btChar>, std::allocator<btChar>>							btString;
#endif

static btString UnicodeToString(const btUnicodeString & strIn);
static btUnicodeString StringToUnicode(const btString & strIn);
static void ToUpper(btUnicodeString & str);
static void ToUpper(btString & str);
static void Strip(btUnicodeString & str, const btUnicodeString & chars);
static void Strip(btString & str, const btString & chars);

extern bool	StringCompare(const btString stra, const btString  strb);

template<typename T> 
void Replace(T & str, const T & strFind, const T & strReplace);

template<typename T>
inline void Replace(T & str, const T & strFind, const T & strReplace)
{
	size_t pos = 0;
	while ((pos = str.find(strFind, pos)) != T::npos)
	{
		str.replace(pos, strFind.length(), strReplace);
		pos += strReplace.length();
	}
}
#endif // !_STRING_H_

