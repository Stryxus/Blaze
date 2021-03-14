#include "pch.hpp"
#include "string.hpp"

wstring string_to_wstring_copy(const string& str)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring wstrTo(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size);
	return wstrTo;
}

string wstring_to_string_copy(const wstring& str)
{
	int size = WideCharToMultiByte(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0, NULL, NULL);
	string strTo(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, &str[0], (int)str.size(), &strTo[0], size, NULL, NULL);
	return strTo;
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

// Misc

void replace(string& s, string look_for, string replace_with)
{
	size_t start_pos = 0;
	while ((start_pos = s.find(look_for, start_pos)) != string::npos) {
		s.replace(start_pos, look_for.length(), replace_with);
		start_pos += replace_with.length();
	}
}

string replace_copy(string s, string look_for, string replace_with)
{
	size_t start_pos = 0;
	while ((start_pos = s.find(look_for, start_pos)) != string::npos) {
		s.replace(start_pos, look_for.length(), replace_with);
		start_pos += replace_with.length();
	}
	return s;
}