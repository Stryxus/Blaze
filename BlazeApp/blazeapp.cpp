#include "pch.h"
#include "blazeapp.h"

using namespace std;

HMODULE nuglify;

int main(int argc, const char* argv[]) 
{
	SetConsoleTitle(L"Blaze - Starting...");
	MoveWindow(GetConsoleWindow(), 20, 20, 1200, 1000, TRUE);

	cout << "Initializing..." << endl;
	cout << "Loading Dependencies..." << endl;
	nuglify = LoadLibrary(L"NUglify.dll");
	if (nuglify == NULL)
	{
		cout << "There was an error loading the JS and CSS library NUglify! Check if NUglify.dll exists in the same directory as this exe." << endl;
		getchar();
		return -1;
	}
	cout << endl;
	cout << "Preparing data processors..." << endl;

	cout << argv[2] << endl;

	if (GetFileAttributes((LPCWSTR)argv[2]) == INVALID_FILE_ATTRIBUTES)
	{
		// Do stuff
	}
	else 
	{
		// Create default json file
		cout << "No blaze-settings.json exists in the specified project. Please check if all settings are correct being running again." << endl;
		getchar();
		return -1;
	}

	getchar();


	FreeLibrary(nuglify);
	return 1;
}