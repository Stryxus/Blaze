#include "pch.h"
#include "netwrapper.h"

//

string DotNetWrapper::DOTNET_MINIFY_JS(string& content)
{
	return (*reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "minify_js")))(content);
}

string DotNetWrapper::DOTNET_MINIFY_CSS(string& content)
{
	return (*reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "minify_css")))(content);
}

//

void DotNetWrapper::DOTNET_CONVERT_VIDEO_TO_WEBM(string& input_path, string& output_path, int& bitrate)
{
	(*reinterpret_cast<void(*)(string&, string&, int&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "convert_video_to_webm")))(input_path, output_path, bitrate);
}

//