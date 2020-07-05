#include "pch.h"

#include "blazeapp.h"

using namespace std;

HMODULE nuglify;

int main(int argc, const char* argv[]) 
{
	cout << "Initializing..." << endl;
	nuglify = LoadLibrary(L"NUglify.dll");
	if (nuglify == NULL)
	{
		cout << "There was an error loading the JS and CSS library NUglify!" << endl;
		getchar();
		return -1;
	}
	getchar();
	return 1;
}