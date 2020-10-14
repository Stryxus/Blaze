#include "pch.h"
#include "jsproc.h"

map<int, string> js_ordered_content;
vector<string> currently_cached_dependencies;
string js_dependencies;

void add_js_for_minification(const char* from, int order)
{
	js_ordered_content.insert(make_pair(order, from));
}

void minify_js(const char* to)
{
	for (string s : Settings::JS_DEPENDENCY_LINKS) 
	{
		if (find(currently_cached_dependencies.begin(), currently_cached_dependencies.end(), s) != currently_cached_dependencies.end() == false) 
		{
			Logger::set_log_color(Logger::COLOR::WHITE_FOREGROUND);
			Logger::log_info("Downloading JS:     " + s);
			Logger::set_log_color(Logger::COLOR::BRIGHT_WHITE_FOREGROUND);
			js_dependencies += DotNetWrapper::DOTNET_DOWNLOAD_STRING(s);
		}
	}
	currently_cached_dependencies = Settings::JS_DEPENDENCY_LINKS;
	string js_data = js_dependencies;
	for (auto const& [key, val] : js_ordered_content) 
	{
		string fileData;
		ifstream fileIn(string(js_ordered_content[key]), ios_base::binary);
		if (fileIn.is_open())
		{
			while (!fileIn.eof())
			{
				string data;
				fileIn >> data;
				fileData += data + " ";
			}
		}
		fileIn.close();
		js_data += fileData + " ";
	}
	string result = DotNetWrapper::DOTNET_MINIFY_JS(js_data);
	if (fs::exists(to)) fs::remove_all(to);
	ofstream fileOut(to, ios_base::binary);
	fileOut.write(result.c_str(), result.length());
	fileOut.close();
}