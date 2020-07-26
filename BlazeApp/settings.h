#pragma once

class Settings
{
public:
	static bool get_settings();
	static bool set_settings(bool setDefaultSettings = false);

	static string SOURCE_RESOURCE_DIR;
	static bool FORMAT_RESOURCE_DIR;
	static vector<string> BLACKLISTED_DIRECTORIES;
	static map<string, JSON> FILE_CONFIGS;

private:
	static JSON default_settings;
	static JSON settings;
};