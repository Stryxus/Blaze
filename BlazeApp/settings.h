#pragma once

class Settings
{
public:
	static bool get_settings();
	static bool set_settings(bool setDefaultSettings = false);

	static string SOURCE_RESOURCE_DIR;
	static bool FORMAT_RESOURCE_DIR;
	static string SCSS_INCLUDE_DIR;
	static int SCSS_PRECISION;
	static vector<string> JS_DEPENDENCY_LINKS;
	static vector<string> IGNORE_DIRECTORIES;
	static vector<string> IGNORE_EXTENSIONS;
	static map<string, JSON> FILE_CONFIGS;

private:
	static JSON default_settings;
	static JSON settings;
};