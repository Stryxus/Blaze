#include "pch.h"
#include "jsproc.h"

string minify_js_interface(string(*f)(string&), string content)
{
	return (*f)(content);
}

map<int, string> js_ordered_content;

void add_js_for_minification(const char* from, int order)
{
	string fileData = "";
	ifstream fileIn(string(from), ios_base::binary);
	if (fileIn.is_open())
	{
		js_ordered_content.insert(make_pair(order, ""));
		while (!fileIn.eof())
		{
			fileIn >> fileData;
			js_ordered_content[order] += fileData + " ";
		}
	}
	fileIn.close();
}

void minify_js(const char* to)
{
	auto func = reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "minify_js"));
	if (func == NULL) Logger::log_last_error();
	else
	{
		string js_data = "";
		for (auto const& [key, val] : js_ordered_content) js_data += val;
		string result = minify_js_interface(func, js_data);
		if (filesystem::exists(to)) filesystem::remove_all(to);
		ofstream fileOut(to, ios_base::binary);
		fileOut.write(result.c_str(), result.length());
		fileOut.close();
	}
	js_ordered_content.clear();
}