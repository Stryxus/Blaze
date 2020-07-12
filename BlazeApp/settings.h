#pragma once

class Settings
{
public:
	static bool get_settings();
	static bool set_settings(bool setDefaultSettings = false);

	static string sourceResourcesDir;
	static bool formatWebsiteRoot;
	static bool forceOverwrite;
	static map<string, JSON> fileConfigs;

private:
	static JSON defaultSettings;
	static JSON settings;
};