#include "pch.h"
#include "libraries.h"

vector<HMODULE> modules;

void load_libraries(vector<LPCWSTR> library_names)
{
	for (LPCWSTR name : library_names) LoadLibrary(name);
}

void free_libraries()
{
	for (HMODULE m : modules) FreeLibrary(m);
}