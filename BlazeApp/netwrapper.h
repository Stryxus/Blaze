#pragma once

class DotNetWrapper
{
public:
	static string DOTNET_MINIFY_JS(string content);
	static string DOTNET_MINIFY_CSS(string content);
	static string DOTNET_DOWNLOAD_STRING(string content);
};