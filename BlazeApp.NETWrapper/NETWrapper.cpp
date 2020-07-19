#include "pch.h"

#include "NETWrapper.h"

using namespace System;
using namespace Runtime::InteropServices;

using namespace NUglify;
using namespace NUglify::Css;
using namespace NUglify::JavaScript;
using namespace NUglify::Helpers;

string minify_css(string& content)
{
	CssSettings^ css_settings = gcnew CssSettings();
	String^ source = gcnew String(content.c_str());

	css_settings->CommentMode = CssComment::None;
	css_settings->OutputMode = OutputMode::SingleLine;

	UglifyResult result = Uglify::Css(source, css_settings, nullptr);

	string rstr;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(result.Code)).ToPointer();
	rstr = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return rstr;
}

string minify_js(string& content)
{
	CodeSettings^ code_settings = gcnew CodeSettings();
	String^ source = gcnew String(content.c_str());

	code_settings->AmdSupport = true;
	code_settings->Format = JavaScriptFormat::Normal;
	code_settings->OutputMode = OutputMode::SingleLine;
	code_settings->PreserveImportantComments = false;

	UglifyResult result = Uglify::Js(source, code_settings);

	string rstr;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(result.Code)).ToPointer();
	rstr = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return rstr;
}