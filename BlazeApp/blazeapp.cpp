#include "pch.h"
#include "blazeapp.h"

#include "libraries.h"
#include "coreproc.h"

int main(int argc, const char* argv[])
{
	SetConsoleTitle(L"Blaze - Initializing...");
	MoveWindow(GetConsoleWindow(), 20, 20, 1400, 1000, TRUE);

	Logger::flush_log_buffer();
	Logger::set_log_color(Logger::COLOR::BRIGHT_WHITE_FOREGROUND);

	Globals::SPECIFIED_PROJECT_DIRECTORY_PATH = argv[1];
	Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH.back() != '\\' ? Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "\\wwwroot" : Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "wwwroot";
	Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH.back() != '\\' ? Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "\\blaze-settings.json" : Globals::SPECIFIED_PROJECT_DIRECTORY_PATH + "blaze-settings.json";

	if (fileExists(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH))
	{
		Logger::log_info("Initializing...");
		Logger::log_info("Loading Dependencies...");
		Logger::log_divide();
		load_libraries(vector<LPCWSTR> { L"NUglify.dll", L"zlibd.dll", L"libpng16d.dll" });
		SetConsoleTitle(string_to_wstring_copy("Blaze - Working on: " + Globals::SPECIFIED_PROJECT_DIRECTORY_PATH).c_str());
		Logger::log_info("Preparing data processors...");
		if (!Settings::get_settings()) return -1;
		start_project_processing();
		Logger::log_nl();
		Logger::log_divide();
		Logger::log_nl();
		Logger::log_info("Processing has finished! - Press any key to exit.");
		getchar();
		free_libraries();
		return 1;
	}
	else
	{
		Logger::log_nl();
		Logger::log_divide();
		Logger::log_nl();
		Logger::log_error("No blaze-settings.json exists in the specified path so one will be created. Pree any key to create the file and close.");
		getchar();
		free_libraries();
		createFile(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH);
		if (!Settings::set_settings(true)) return -1;
		else return 0;
	}
}