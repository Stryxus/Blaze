#include "pch.h"
#include "stringutils.h"

wstring string_to_wstring(const string& str)
{
	wstring title(str.length(), L' ');
	copy(str.begin(), str.end(), back_inserter(title));
	trim(title);
	return title;
}

// Trim string

static inline void left_trim(string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !isspace(ch); }));
}

static inline void right_trim(string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !isspace(ch); }).base(), s.end());
}

static inline void trim(string& s)
{
	left_trim(s);
	right_trim(s);
}

static inline string left_trim_copy(string s)
{
	left_trim(s);
	return s;
}

static inline string right_trim_copy(string s)
{
	right_trim(s);
	return s;
}

// Trim wstring

static inline void left_trim(wstring& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !isspace(ch); }));
}

static inline void right_trim(wstring& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !isspace(ch); }).base(), s.end());
}

static inline void trim(wstring& s)
{
	left_trim(s);
	right_trim(s);
}

static inline wstring left_trim_copy(wstring s)
{
	left_trim(s);
	return s;
}

static inline wstring right_trim_copy(wstring s)
{
	right_trim(s);
	return s;
}