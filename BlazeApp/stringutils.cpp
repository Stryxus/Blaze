#include "pch.h"
#include "stringutils.h"

wstring stringTowstring(const string& str)
{
	wstring title(str.length(), L' ');
	copy(str.begin(), str.end(), back_inserter(title));
	return title;
}