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
			string dependency = download(s);
			string dependencyLength = to_string(convert_data_magnitude_in_bytes_copy(dependency.length(), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE));
			Logger::set_console_color(Logger::COLOR::WHITE_FOREGROUND);
			Logger::log_info("Downloaded JS:      " + s + " [" + dependencyLength.substr(0, static_cast<int>(dependencyLength.find_first_of(".") + 3)) + " KB]");
			Logger::clear_console_color();
			js_dependencies += dependency;
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