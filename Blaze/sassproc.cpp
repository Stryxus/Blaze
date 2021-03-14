#include "pch.hpp"
#include "sassproc.hpp"

#include <sass.h>
using namespace Sass;

string scss_data = "";
string css_data = "";

void add_scss_for_minification(const char* from)
{
	string fileData = "";

	ifstream fileIn(from, ios_base::binary);
	if (fileIn.is_open())
	{
		while (!fileIn.eof())
		{
			fileIn >> fileData;
			scss_data += fileData;
		}
	}
	fileIn.close();
}

void add_css_for_minification(const char* from)
{
	string fileData = "";

	ifstream fileIn(from, ios_base::binary);
	if (fileIn.is_open())
	{
		while (!fileIn.eof())
		{
			fileIn >> fileData;
			css_data += fileData;
		}
	}
	fileIn.close();
}

void minify_css(const char* to, const char* include_path, int precision)
{
	struct Sass_Data_Context* data_ctx = sass_make_data_context(sass_copy_c_string(scss_data.c_str()));
	scss_data.clear();
	struct Sass_Context* ctx = sass_data_context_get_context(data_ctx);
	struct Sass_Options* ctx_opt = sass_context_get_options(ctx);

	if (!string(include_path).empty()) sass_option_set_include_path(ctx_opt, include_path);
	sass_option_set_output_style(ctx_opt, Sass_Output_Style::SASS_STYLE_COMPRESSED);
	sass_option_set_source_comments(ctx_opt, false);
	sass_option_set_source_map_contents(ctx_opt, false);
	sass_option_set_precision(ctx_opt, precision);

	const char* output = nullptr;
	bool error = false;
	if (sass_compile_data_context(data_ctx) == 0) output = sass_context_get_output_string(ctx);
	else
	{
		output = sass_context_get_error_message(ctx);
		error = true;
	}

	if (fs::exists(to)) fs::remove_all(to);

	if (!error)
	{
		ofstream fileOut(to, ios_base::binary);
		fileOut.write(output, strlen(output));
		if (!css_data.empty())
		{
			string result = DotNetWrapper::DOTNET_MINIFY_CSS(css_data);
			css_data.clear();
			fileOut.write(result.c_str(), result.length());
		}
		fileOut.close();
	}
	else Logger::log_error(output);
	sass_delete_data_context(data_ctx);
}
