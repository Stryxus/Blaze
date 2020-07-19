#pragma once

void load_libraries(vector<string> library_names);
HMODULE get_library(string lib_name);
void* get_lib_function(HMODULE lib, string function_name);
void free_libraries();