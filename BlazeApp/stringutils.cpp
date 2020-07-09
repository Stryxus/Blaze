#include "pch.h"
#include "stringutils.h"

void string_to_wstring(string& str)
{
	wstring title(str.length(), L' ');
	copy(str.begin(), str.end(), back_inserter(title));
	trim(title);
}

wstring string_to_wstring_copy(string str)
{
	wstring title(str.length(), L' ');
	copy(str.begin(), str.end(), back_inserter(title));
	trim(title);
	return title;
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