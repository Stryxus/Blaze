#include "pch.h"
#include "blazeapp.h"
#include "settings.h"

#include "imageproc.h"

void start_project_processing()
{
	cout << "Starting..." << endl << endl;

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
		string relativePath = path.substr(strlen(sourceDir.c_str()));
		string copyToPath = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + relativePath;

		filesystem::path ctp(copyToPath);
		if (ctp.has_extension() && ctp.extension() != "")
		{
			// Only support PNG for now
			if (ctp.extension() == ".png")
			{
				if (Settings::settings["fileConfigs"].find(relativePath) != Settings::settings["fileConfigs"].end())
				{
					auto &config = Settings::settings["fileConfigs"][relativePath];

					bool enabled = false;
					if (config.find("enabled") != config.end()) enabled = static_cast<bool>(config["enabled"]);

					if (enabled) 
					{
						cout << "Converting: " + relativePath << endl;
						convert_to_webp(path.c_str(), string(copyToPath.substr(0, copyToPath.find_last_of('.')) + ".webp").c_str(), static_cast<int>(config["width"]), static_cast<int>(config["height"]), static_cast<float>(config["quality"]));
					}
				}
			}
			else
			{
				cout << "Copying File: " + relativePath << endl;
				if (!is_directory(entry)) filesystem::copy(path, copyToPath);
			}
		}
		else
		{
			cout << "Copying File: " + relativePath << endl;
			if (!is_directory(entry)) filesystem::copy(path, copyToPath);
		}
	}
}


HMODULE zlib;
HMODULE libpng;
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
		nuglify = LoadLibrary(L"zlibd.dll");
		nuglify = LoadLibrary(L"libpng16d.dll");
		nuglify = LoadLibrary(L"NUglify.dll");
		if (nuglify == nullptr)
		{
			cout << "There was an error loading the JS and CSS library NUglify! Check if NUglify.dll exists in the same directory as this exe." << endl;
			getchar();
			return -1;
		}
		SetConsoleTitle(string_to_wstring_copy("Blaze - Working on: " + Globals::SPECIFIED_PROJECT_DIRECTORY_PATH).c_str());
		cout << endl << "Preparing data processors..." << endl;
		if (Settings::GetSettings() == -1) return -1;
		start_project_processing();
		getchar();
		FreeLibrary(zlib);
		FreeLibrary(libpng);
		FreeLibrary(nuglify);
		return 1;
	}
	else
	{
		cout << "No blaze-settings.json exists in the specified path so one will be created. Pree any key to create the file and close." << endl;
		getchar();
		FreeLibrary(zlib);
		FreeLibrary(libpng);
		FreeLibrary(nuglify);
		createFile(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH);
		return Settings::SetSettings(true);
	}
}