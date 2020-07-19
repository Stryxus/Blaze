#pragma once

void load_libraries(vector<const string> library_names);
HMODULE get_library(const string lib_name);
void* get_lib_function(HMODULE lib, string function_name);
void free_libraries();