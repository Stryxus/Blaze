#include "pch.h"
#include "settings.h"

string Settings::sourceResourcesDir = "";
bool Settings::formatWebsiteRoot = false;
map<string, JSON> Settings::fileConfigs = {};

JSON Settings::defaultSettings =
{
	// Must be the directory to the website root of source files. They will be copied over or converted and copies over to the projects website root.
	{"sourceResourcesDir", ""},
	// Delete the destination website root before starting the copy and convert process from the source website root directory.
	{"formatWebsiteRoot", false},
	// Every file in the website root source files must be declared here before anything will be done to it.
	{"fileConfigs", {}}
};

JSON Settings::settings = nullptr;

bool Settings::get_settings()
{
	string settingsRead;
	string currentLine;
	try
	{
		ifstream settingsFile(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH);
		if (settingsFile.is_open())
		{
			while (getline(settingsFile, currentLine)) settingsRead += currentLine;
			settingsFile.close();
		}
	}
	catch (exception e)
	{
		Logger::log_error("An error has occured while reading the specified blaze-settings.json file! " + *e.what());
		getchar();
		return false;
	}
	try
	{
		Settings::settings = JSON::parse(settingsRead);

		Settings::sourceResourcesDir = Settings::settings["sourceResourcesDir"];
		Settings::formatWebsiteRoot = Settings::settings["formatWebsiteRoot"];

		Settings::fileConfigs = Settings::settings.at("fileConfigs").get<map<string, JSON>>();
	}
	catch (exception e)
	{
		Logger::log_error("An error occurred while parsing the specified blaze-settings.json file! This is most likely caused by incorrect formatting. " + *e.what());
		getchar();
		return false;
	}
	return true;
}

bool Settings::set_settings(bool setDefaultSettings)
{
	try
	{
		ofstream settingsFile(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH);
		if (settingsFile.is_open())
		{
			Settings::settings["sourceResourcesDir"] = Settings::sourceResourcesDir;
			Settings::settings["formatWebsiteRoot"] = Settings::formatWebsiteRoot;

			Settings::settings["fileConfigs"] = Settings::fileConfigs;

			if (Settings::settings.empty() || setDefaultSettings) settingsFile << Settings::defaultSettings.dump(4);
			else settingsFile << Settings::settings.dump(4);
			settingsFile.close();
		}
	}
	catch (exception e)
	{
		Logger::log_error("An error has occured while writing to the specified blaze-settings.json " + *e.what());
		getchar();
		return false;
	}
	return true;
}