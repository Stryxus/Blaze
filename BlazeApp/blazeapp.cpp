#include "pch.h"
#include "blazeapp.h"

string References::APP_NAME = "Blaze";
string References::APP_VERSION = "1.0.0";

string Globals::specifiedProjectDirectoryPath = "";

// Blaze Settings

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
			else settingsFile << BlazeSettings::settings.dump();
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

// Main

HMODULE nuglify;

int main(int argc, const char* argv[])
{
	SetConsoleTitle(L"Blaze - Starting...");
	MoveWindow(GetConsoleWindow(), 20, 20, 1200, 1000, TRUE);

	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written;
	DWORD cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);

	Globals::specifiedProjectDirectoryPath = string(argv[2], strlen(argv[2]));
	Globals::specifiedProjectDirectoryPath = Globals::specifiedProjectDirectoryPath.back() != '\\' ? Globals::specifiedProjectDirectoryPath + "\\blaze-settings.json" : Globals::specifiedProjectDirectoryPath + "blaze-settings.json";

	if (fileExists(Globals::specifiedProjectDirectoryPath))
	{
		cout << "Initializing..." << endl;
		cout << "Loading Dependencies..." << endl;
		nuglify = LoadLibrary(L"NUglify.dll");
		if (nuglify == nullptr)
		{
			cout << "There was an error loading the JS and CSS library NUglify! Check if NUglify.dll exists in the same directory as this exe." << endl;
			getchar();
			return -1;
		}
		cout << endl;
		cout << "Preparing data processors..." << endl;

		if (BlazeSettings::GetSettings() == -1) return -1;

		getchar();

		FreeLibrary(nuglify);
		return 1;
	}
	else
	{
		cout << "No blaze-settings.json exists in the specified project. Please check if all settings are correct being running again. Pree any key to close." << endl;
		getchar();
		FreeLibrary(nuglify);
		createFile(Globals::specifiedProjectDirectoryPath);
		return BlazeSettings::SetSettings(true);
	}
}