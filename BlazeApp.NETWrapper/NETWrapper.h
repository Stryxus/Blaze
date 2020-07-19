#pragma once

extern "C"
{
	__declspec(dllexport) string __stdcall minify_css(string& content);
	__declspec(dllexport) string __stdcall minify_js(string& content);
}