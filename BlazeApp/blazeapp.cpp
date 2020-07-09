#include "pch.h"
#include "blazeapp.h"
#include "settings.h"

void start_project_processing()
{
	string sourceDir(Settings::settings["sourceResourcesDir"]);
	bool purgeWWWROOT(Settings::settings["formatWebsiteRoot"]);

	if (purgeWWWROOT) 
	{
		filesystem::remove_all(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
		filesystem::create_directory(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
	}

	for (const filesystem::directory_entry& entry : filesystem::recursive_directory_iterator(sourceDir))
	{
		string path = entry.path().string();
		string copyToPath = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + path.substr(strlen(sourceDir.c_str()));
		cout << "Creating Directory: " + copyToPath << endl;
		if (is_directory(entry)) filesystem::create_directory(copyToPath); 
	}

	for (const filesystem::directory_entry& entry : filesystem::recursive_directory_iterator(sourceDir))
	{
		string path = entry.path().string();
		string copyToPath = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + path.substr(strlen(sourceDir.c_str()));
		cout << "Copying File: " + copyToPath << endl;
		if (!is_directory(entry)) filesystem::copy(path, copyToPath);
	}
}














HMODULE nuglify;

int main(int argc, const char* argv[])
{
	setlocale(LC_ALL, "");
	SetConsoleTitle(L"Blaze - Initializing...");
	MoveWindow(GetConsoleWindow(), 20, 20, 1400, 1000, TRUE);

	/*Clear Console******************************************************************************/
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written;
	DWORD cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
	/*******************************************************************************************/

	Globals::SPECIFIED_PROJECT_DIRECTORY_PATH = argv[1];
	Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH.back() != '\\' ? Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "\\wwwroot" : Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "wwwroot";
	Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH.back() != '\\' ? Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "\\blaze-settings.json" : Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "blaze-settings.json";

	if (fileExists(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH))
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
		SetConsoleTitle(string_to_wstring_copy("Blaze - Working on: " + Globals::SPECIFIED_PROJECT_DIRECTORY_PATH).c_str());
		cout << endl;
		cout << "Preparing data processors..." << endl;
		if (Settings::GetSettings() == -1) return -1;
		start_project_processing();
		getchar();
		FreeLibrary(nuglify);
		return 1;
	}
	else
	{
		cout << "No blaze-settings.json exists in the specified path so one will be created. Pree any key to create the file and close." << endl;
		getchar();
		FreeLibrary(nuglify);
		createFile(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH);
		return Settings::SetSettings(true);
	}
}