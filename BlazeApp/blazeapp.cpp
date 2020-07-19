#include "pch.h"
#include "blazeapp.h"

#include "imgproc.h"
#include "cssproc.h"

void start_project_processing()
{
	Logger::log_info("Starting...");
	Logger::log_nl(2);

	if (Settings::formatWebsiteRoot) 
	{
		filesystem::remove_all(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
		filesystem::create_directory(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
	}

	vector<string> directorySubExtentionExclusionFilter{ ".scss", ".sass", ".css", ".js", ".min.css", ".min.js" };
	for (const filesystem::directory_entry& entry : filesystem::recursive_directory_iterator(Settings::sourceResourcesDir))
	{
		string path = entry.path().string();
		string relativePath = path.substr(strlen(Settings::sourceResourcesDir.c_str()));
		string copyToPath = "";
		string copyToPathRelative = "";

		bool cssBundleCreated = false;

		if (is_directory(entry)) {
			copyToPath = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + path.substr(strlen(Settings::sourceResourcesDir.c_str()));
			for (const filesystem::directory_entry& entry2 : filesystem::recursive_directory_iterator(entry)) 
			{
				if (!is_directory(entry2) && find(directorySubExtentionExclusionFilter.begin(), directorySubExtentionExclusionFilter.end(), entry2.path().extension()) == directorySubExtentionExclusionFilter.end())
				{
					Logger::log_nl();
					Logger::set_log_color(Logger::COLOR::GREEN_FOREGROUND);
					Logger::log_info("Creating Directory: [wwwroot]:" + relativePath);
					Logger::set_log_color(Logger::COLOR::BRIGHT_WHITE_FOREGROUND);
					Logger::log_divide();
					filesystem::create_directory(copyToPath);
					break;
				}
			}
		}
		else
		{
			copyToPath = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + relativePath;
			filesystem::path ctp(copyToPath);
			if (ctp.has_extension() && ctp.extension() != "")
			{
				if (ctp.extension() == ".png")
				{
					if (json_entry_exists(Settings::fileConfigs, relativePath))
					{
						JSON fileConfig = Settings::fileConfigs[relativePath];

						bool enabled = false;
						if (json_entry_exists(fileConfig, "enabled")) enabled = static_cast<bool>(fileConfig["enabled"]);

						if (enabled)
						{
							copyToPathRelative = (copyToPath.substr(0, copyToPath.find_last_of('.')) + ".webp").substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
							Logger::log_info("Converting File:    [wwwroot]:" + copyToPathRelative);
							convert_png_to_webp(path.c_str(), string(copyToPath.substr(0, copyToPath.find_last_of('.')) + ".webp").c_str(),
								static_cast<int>(fileConfig["width"]),
								static_cast<int>(fileConfig["height"]),
								static_cast<float>(fileConfig["quality"]));
						}
					}
					else
					{
						Logger::log_info("Copying File:       [wwwroot]:" + relativePath);
						filesystem::copy(path, copyToPath);
					}
				}
				else if ((ctp.extension() == ".sass" || ctp.extension() == ".scss") && !cssBundleCreated)
				{
					if (json_entry_exists(Settings::fileConfigs, relativePath))
					{
						JSON fileConfig = Settings::fileConfigs[relativePath];

						bool enabled = false;
						if (json_entry_exists(fileConfig, "enabled")) enabled = static_cast<bool>(fileConfig["enabled"]);

						if (enabled)
						{
							copyToPathRelative = (copyToPath.substr(0, copyToPath.find_last_of('.')) + ".min.css").substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
							Logger::log_info("Converting File:    [wwwroot]:" + copyToPathRelative);
							convert_sass_to_css(path.c_str(), string(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.css").c_str(), 
								string(Settings::sourceResourcesDir + "\\" + static_cast<string>(fileConfig["relativeIncludePath"])).c_str(),
								static_cast<int>(fileConfig["precision"]));
							cssBundleCreated = true;
						}
					}
				}
				else if (ctp.extension() == ".js")
				{

				}
				else 
				{
					Logger::log_info("Copying File:       [wwwroot]:" + relativePath);
					filesystem::copy(path, copyToPath);
				}
			}
			else
			{
				Logger::log_info("Skipping File:      [wwwroot]:" + relativePath);
			}
		}
	}
}

HMODULE nuglify;
HMODULE zlib;
HMODULE libpng;

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
		nuglify = LoadLibrary(L"NUglify.dll");
		zlib = LoadLibrary(L"zlibd.dll");
		libpng = LoadLibrary(L"libpng16d.dll");
		if (nuglify == nullptr)
		{
			Logger::log_error("There was an error loading NUglify! Check if NUglify.dll exists in the same directory as this exe.");
			getchar();
			return -1;
		}
		if (zlib == nullptr)
		{
			Logger::log_error("There was an error loading zlib! Check if zlibd.dll exists in the same directory as this exe.");
			getchar();
			return -1;
		}
		if (libpng == nullptr)
		{
			Logger::log_error("There was an error loading libpng! Check if libpng16d.dll exists in the same directory as this exe.");
			getchar();
			return -1;
		}
		SetConsoleTitle(string_to_wstring_copy("Blaze - Working on: " + Globals::SPECIFIED_PROJECT_DIRECTORY_PATH).c_str());
		Logger::log_info("Preparing data processors...");
		if (!Settings::get_settings()) return -1;
		start_project_processing();
		Logger::log_nl();
		Logger::log_divide();
		Logger::log_nl();
		Logger::log_info("Processing has finished! - Press any key to exit.");
		getchar();
		FreeLibrary(nuglify);
		FreeLibrary(zlib);
		FreeLibrary(libpng);
		return 1;
	}
	else
	{
		Logger::log_nl();
		Logger::log_divide();
		Logger::log_nl();
		Logger::log_error("No blaze-settings.json exists in the specified path so one will be created. Pree any key to create the file and close.");
		getchar();
		FreeLibrary(nuglify);
		FreeLibrary(zlib);
		FreeLibrary(libpng);
		createFile(Globals::SPECIFIED_PROJECT_DIRECTORY_SETTINGS_JSON_PATH);
		if (!Settings::set_settings(true)) return -1;
		else return 0;
	}
}