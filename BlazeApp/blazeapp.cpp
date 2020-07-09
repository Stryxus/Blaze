#include "pch.h"
#include "blazeapp.h"
#include "settings.h"

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

	Globals::specifiedProjectDirectoryPath = argv[1];
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
		SetConsoleTitle(string_to_wstring_copy("Blaze - Working on: " + Globals::specifiedProjectDirectoryPath).c_str());
		cout << endl;
		cout << "Preparing data processors..." << endl;

		if (BlazeSettings::GetSettings() == -1) return -1;

		getchar();

		FreeLibrary(nuglify);
		return 1;
	}
	else
	{
		cout << "No blaze-settings.json exists in the specified path so one will be created. Pree any key to create the file and close." << endl;
		getchar();
		FreeLibrary(nuglify);
		createFile(Globals::specifiedProjectDirectoryPath);
		return BlazeSettings::SetSettings(true);
	}
}