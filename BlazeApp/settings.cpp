#include "pch.h"
#include "settings.h"

JSON BlazeSettings::defaultSettings =
{
	// Must be the directory to the website root of source files. They will be copied over or converted and copies over to the projects website root.
	{"sourceResourcesDir", ""},
	// Overwrite files that already exist.
	{"forceOverwrite", false},
	// Delete the destination website root before starting the copy and convert process from the source website root directory.
	{"formatWebsiteRoot", false},
	// Every file in the website root source files must be declared here before anything will be done to it.
	{"fileConfigs", {}}
};

JSON BlazeSettings::settings = nullptr;

int BlazeSettings::GetSettings()
{
	string settingsRead;
	string currentLine;
	try
	{
		ifstream settingsFile(Globals::specifiedProjectDirectoryPath);
		if (settingsFile.is_open())
		{
			while (getline(settingsFile, currentLine)) settingsRead += currentLine;
			settingsFile.close();
		}
	}
	catch (exception e)
	{
		cout << "An error has occured while reading the specified blaze-settings.json file! " + *e.what() << endl;
		getchar();
		return -1;
	}
	try
	{
		BlazeSettings::settings = JSON::parse(settingsRead);
	}
	catch (exception e)
	{
		cout << "An error occurred while parsing the specified blaze-settings.json file! This is most likely caused by incorrect formatting. " + *e.what() << endl;
		getchar();
		return -1;
	}
	return 0;
}

int BlazeSettings::SetSettings(bool setDefaultSettings)
{
	try
	{
		ofstream settingsFile(Globals::specifiedProjectDirectoryPath);
		if (settingsFile.is_open())
		{
			if (BlazeSettings::settings.empty() || setDefaultSettings) settingsFile << BlazeSettings::defaultSettings.dump();
			else settingsFile << BlazeSettings::settings.dump(4);
			settingsFile.close();
		}
	}
	catch (exception e)
	{
		cout << "An error has occured while writing to the specified blaze-settings.json " + *e.what() << endl;
		getchar();
		return -1;
	}
	return 0;
}