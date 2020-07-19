#include "pch.h"
#include "libraries.h"

map<string, HMODULE> modules;

void load_libraries(vector<string> library_names)
{
	for (string name : library_names) modules.emplace(name, LoadLibrary(string_to_wstring_copy(name).c_str()));
}

HMODULE get_library(string& lib_name)
{
	return modules[lib_name];
}

void* get_lib_function(HMODULE& lib, string function_name)
{
	return (void*)GetProcAddress(lib, function_name.c_str());
}

void free_libraries()
{
	for (auto const& [key, val] : modules) FreeLibrary(val);
}