#pragma once

namespace NETWrapper {

	public ref class Wrapper
	{
	public:
		static string minify_css(string& content);
		static string minify_js(string& content);
	};
}
