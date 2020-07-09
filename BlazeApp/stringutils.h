#pragma once

void string_to_wstring(string& str);

wstring string_to_wstring_copy(string str);

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