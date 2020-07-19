#include "pch.h"
#include "sassproc.h"

#include <sass.h>
using namespace Sass;

void convert_sass_to_css(const char* from, const char* to, const char* include_path, int precision)
{
	size_t data_size = 0;
	string data = "";
	string fileData = "";

	ifstream fileIn(from, ios_base::binary);
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

	struct Sass_Data_Context* data_ctx = sass_make_data_context(sass_copy_c_string(data.c_str()));
	struct Sass_Context* ctx = sass_data_context_get_context(data_ctx);
	struct Sass_Options* ctx_opt = sass_context_get_options(ctx);

	sass_option_set_include_path(ctx_opt, include_path);
	sass_option_set_output_style(ctx_opt, Sass_Output_Style::SASS_STYLE_COMPRESSED);
	sass_option_set_source_comments(ctx_opt, false);
	sass_option_set_source_map_contents(ctx_opt, false);
	sass_option_set_precision(ctx_opt, precision);

	const char* output = nullptr;
	if (sass_compile_data_context(data_ctx) == 0) output = sass_context_get_output_string(ctx);
	else output = sass_context_get_error_message(ctx);

	ofstream fileOut(to, ios_base::binary | ios_base::app);
	fileOut.write(output, strlen(output));
	fileOut.close();

	sass_delete_data_context(data_ctx);
}

string minify_css_interface(string(*f)(string&), string content)
{
	return (*f)(content);
}

void minify_css(const char* from)
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

	auto func = reinterpret_cast<string(*)(string&)>(get_lib_function(get_library(Globals::LIB_NET_WRAPPER), "minify_css"));
	if (func == NULL) Logger::log_last_error();
	else
	{
		string result = minify_css_interface(func, data);

		ofstream fileOut(string(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.css"), ios_base::binary | ios_base::app);
		fileOut.write(result.c_str(), result.length());
		fileOut.close();
	}
}