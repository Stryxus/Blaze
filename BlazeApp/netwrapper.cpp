#include "pch.h";
#include "netwrapper.h";

string DotNetWrapper::DOTNET_MINIFY_JS(string content)
{
	return (*reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "minify_js")))(content);
}

string DotNetWrapper::DOTNET_MINIFY_CSS(string content)
{
	return (*reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "minify_css")))(content);
}

string DotNetWrapper::DOTNET_DOWNLOAD_STRING(string content)
{
	return (*reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "download_data")))(content);
}