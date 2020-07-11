#pragma once

wstring string_to_wstring_copy(const string& str);

string wstring_to_string_copy(const wstring& str);

// Trim string

void left_trim(string& s);

void right_trim(string& s);

void trim(string& s);

string left_trim_copy(string s);

string right_trim_copy(string s);

// Trim wstring

void left_trim(wstring& s);

void right_trim(wstring& s);

void trim(wstring& s);

wstring left_trim_copy(wstring s);

wstring right_trim_copy(wstring s);