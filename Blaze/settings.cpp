#include "pch.h"
#include "settings.h"

string Settings::SOURCE_RESOURCE_DIR = "";
bool Settings::FORMAT_RESOURCE_DIR = false;
string Settings::SCSS_INCLUDE_DIR = "";
int Settings::SCSS_PRECISION = 3;
vector<string> Settings::JS_DEPENDENCY_LINKS = {};
vector<string> Settings::IGNORE_DIRECTORIES = {};
vector<string> Settings::IGNORE_FILES = {};
vector<string> Settings::IGNORE_EXTENSIONS = {};
map<string, JSON> Settings::FILE_CONFIGS = {};

JSON Settings::default_settings =
{
	// Must be the directory to the website root of source files. They will be copied over or converted and copies over to the projects website root.
	{"sourceResourcesDir", SOURCE_RESOURCE_DIR},
	// Delete the destination website root before starting the copy and convert process from the source website root directory.
	{"formatWebsiteRoot", FORMAT_RESOURCE_DIR},
	{"scssIncludeDirectory", SCSS_INCLUDE_DIR},
	{"scssPrecision", SCSS_PRECISION},
	// Links to all javascript dependencies for download
	{"jsDependencyLinks", JS_DEPENDENCY_LINKS},
	{"ignore_directories", IGNORE_DIRECTORIES},
	{"ignore_files", IGNORE_FILES},
	{"ignore_extensions", IGNORE_EXTENSIONS},
	// Every file in the website root source files must be declared here before anything will be done to it.
	{"fileConfigs", FILE_CONFIGS}
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
		Settings::settings = JSON::parse(settingsRead);
	}
	catch (exception e)
	{
		Logger::log_error("An error has occured while reading the specified blaze-settings.json file! " + *e.what());
		Logger::wait();
		return false;
	}

	try 
	{
		Settings::SOURCE_RESOURCE_DIR = Settings::settings["sourceResourcesDir"];
	}
	catch (exception e)
	{
		Logger::log_error("sourceResourceDir was not set! Cannot continue! " + *e.what());
		Logger::wait();
		return false;
	}

	try
	{
		Settings::FORMAT_RESOURCE_DIR = Settings::settings["formatWebsiteRoot"];
	}
	catch (exception e)
	{ }

	try
	{
		Settings::SCSS_INCLUDE_DIR = Settings::settings["scssIncludeDirectory"];
	}
	catch (exception e)
	{ }

	try
	{
		Settings::SCSS_PRECISION = Settings::settings["scssPrecision"];
	}
	catch (exception e)
	{ }

	try
	{
		Settings::JS_DEPENDENCY_LINKS = Settings::settings["jsDependencyLinks"].get<vector<string>>();
	}
	catch (exception e)
	{ }

	try
	{
		Settings::IGNORE_DIRECTORIES = Settings::settings["ignored_directories"].get<vector<string>>();
	}
	catch (exception e)
	{ }

	try
	{
		Settings::IGNORE_FILES = Settings::settings["ignore_files"].get<vector<string>>();
	}
	catch (exception e)
	{ }

	try
	{
		Settings::IGNORE_EXTENSIONS = Settings::settings["ignore_extensions"].get<vector<string>>();
	}
	catch (exception e)
	{ }

	try
	{
		Settings::FILE_CONFIGS = Settings::settings.at("fileConfigs").get<map<string, JSON>>();
	}
	catch (exception e)
	{ }

	return true;
}

bool Settings::set_settings(bool setDefaultSettings)
{
	/*
	try
	{
		ofstream settingsFile(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH);
		if (settingsFile.is_open())
		{
			Settings::settings["sourceResourcesDir"] = Settings::SOURCE_RESOURCE_DIR;
			Settings::settings["formatWebsiteRoot"] = Settings::FORMAT_RESOURCE_DIR;
			Settings::settings["scssIncludeDirectory"] = Settings::SCSS_INCLUDE_DIR;
			Settings::settings["scssPrecision"] = Settings::SCSS_PRECISION;
			Settings::settings["blacklistedDirectories"] = Settings::BLACKLISTED_DIRECTORIES;
			Settings::settings["jsDependencyLinks"] = Settings::JS_DEPENDENCY_LINKS;

			Settings::settings["fileConfigs"] = Settings::FILE_CONFIGS;

			if (Settings::settings.empty() || setDefaultSettings) settingsFile << Settings::default_settings.dump(4);
			else settingsFile << Settings::settings.dump(4);
			settingsFile.close();
		}
	}
	catch (exception e)
	{
		Logger::log_error("An error has occured while writing to the specified blaze-settings.json " + *e.what());
		Logger::wait();
		return false;
	}
	*/
	return true;
}