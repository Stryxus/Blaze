#include "pch.h"
#include "jsproc.h"

string minify_js_interface(string(*f)(string&), string content)
{
	return (*f)(content);
}

void minify_js(const char* from)
{
	size_t data_size = 0;
	string data = "";
	string fileData = "";

	ifstream fileIn(string(from), ios_base::binary);
	if (fileIn.is_open())
	{
		while (!fileIn.eof())
		{
			fileIn >> fileData;
			data += fileData;
		}
		data = data.substr(0, (data.length() - 1) - (fileData.length() - 1));
	}
	fileIn.close();

	auto func = reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "minify_js"));
	if (func == NULL) Logger::log_last_error();
	else
	{
		string result = minify_js_interface(func, data);

		ofstream fileOut(string(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.js"), ios_base::binary | ios_base::app);
		fileOut.write(result.c_str(), result.length());
		fileOut.close();
	}
}