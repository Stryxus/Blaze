#include "pch.h"
#include "stringutils.h"

wstring string_to_wstring_copy(const string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

string wstring_to_string_copy(const wstring& str)
{
	_bstr_t b(str.c_str());
	const char* c = b;
	return string(c);
}

// Trim string

void left_trim(string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !isspace(ch); }));
}

void right_trim(string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !isspace(ch); }).base(), s.end());
}

void trim(string& s)
{
	left_trim(s);
	right_trim(s);
}

string left_trim_copy(string s)
{
	left_trim(s);
	return s;
}

string right_trim_copy(string s)
{
	right_trim(s);
	return s;
}

// Trim wstring

void left_trim(wstring& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !isspace(ch); }));
}

void right_trim(wstring& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !isspace(ch); }).base(), s.end());
}

void trim(wstring& s)
{
	left_trim(s);
	right_trim(s);
}

wstring left_trim_copy(wstring s)
{
	left_trim(s);
	return s;
}

wstring right_trim_copy(wstring s)
{
	right_trim(s);
	return s;
}