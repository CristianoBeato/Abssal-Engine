
#include "precompiled.h"
#pragma hdrstop

#include "string.h"

btString UnicodeToString(const btUnicodeString & strIn)
{
	if (!strIn.length()) 
		return "\0";

	btString temp(strIn.length(), (btChar)0);
	std::use_facet< std::ctype<btUnicodeChar> >(std::locale()).narrow(&strIn[0], &strIn[0] + strIn.length(), ' ', &temp[0]);
	return temp;
}

btUnicodeString StringToUnicode(const btString & strIn)
{
	if (!strIn.length())
		return L"\0";


	btUnicodeString temp(strIn.length(), (wchar_t)0);
	std::use_facet< std::ctype<btUnicodeChar> >(std::locale()).widen(&strIn[0], &strIn[0] + strIn.length(), &temp[0]);
	return temp;
}

void ToUpper(btUnicodeString & str)
{

}

void ToUpper(btString & str)
{
}

void Strip(btUnicodeString & str, const btUnicodeString & chars)
{
}

void Strip(btString & str, const btString & chars)
{
}

bool StringCompare(const btString stra, const btString strb)
{
	return std::strcmp(stra.c_str(), strb.c_str()) == 0;
}
