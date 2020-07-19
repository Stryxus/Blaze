#include "pch.h"
#include "blazeapp.h"

#include "libraries.h"
#include "imgproc.h"
#include "cssproc.h"

void start_project_processing()
{
	Logger::log_info("Starting...");
	Logger::log_nl(2);

	if (Settings::FORMAT_RESOURCE_DIR) 
	{
		filesystem::remove_all(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
		filesystem::create_directory(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
	}

	vector<string> directory_sub_extention_exclusion_filter{ ".scss", ".sass", ".css", ".js", ".min.css", ".min.js" };
	for (const filesystem::directory_entry& entry : filesystem::recursive_directory_iterator(Settings::SOURCE_RESOURCE_DIR))
	{
		string path = entry.path().string();
		string relative_path = path.substr(strlen(Settings::SOURCE_RESOURCE_DIR.c_str()));
		string copy_to_path = "";
		string copy_to_path_relative = "";

		bool css_bundle_created = false;

		if (is_directory(entry)) {
			copy_to_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + path.substr(strlen(Settings::SOURCE_RESOURCE_DIR.c_str()));
			for (const filesystem::directory_entry& entry2 : filesystem::recursive_directory_iterator(entry)) 
			{
				if (!is_directory(entry2) && find(directory_sub_extention_exclusion_filter.begin(), directory_sub_extention_exclusion_filter.end(), entry2.path().extension()) == directory_sub_extention_exclusion_filter.end())
				{
					Logger::log_nl();
					Logger::set_log_color(Logger::COLOR::GREEN_FOREGROUND);
					Logger::log_info("Creating Directory: [wwwroot]:" + relative_path);
					Logger::set_log_color(Logger::COLOR::BRIGHT_WHITE_FOREGROUND);
					Logger::log_divide();
					filesystem::create_directory(copy_to_path);
					break;
				}
			}
		}
		else
		{
			copy_to_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + relative_path;
			filesystem::path ctp(copy_to_path);
			if (ctp.has_extension() && ctp.extension() != "")
			{
				if (ctp.extension() == ".png")
				{
					if (json_entry_exists(Settings::FILE_CONFIGS, relative_path))
					{
						JSON file_config = Settings::FILE_CONFIGS[relative_path];

						bool enabled = false;
						if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

						if (enabled)
						{
							copy_to_path_relative = (copy_to_path.substr(0, copy_to_path.find_last_of('.')) + ".webp").substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
							Logger::log_info("Converting File:    [wwwroot]:" + copy_to_path_relative);
							convert_png_to_webp(path.c_str(), string(copy_to_path.substr(0, copy_to_path.find_last_of('.')) + ".webp").c_str(),
								static_cast<int>(file_config["width"]),
								static_cast<int>(file_config["height"]),
								static_cast<float>(file_config["quality"]));
						}
					}
					else
					{
						Logger::log_info("Copying File:       [wwwroot]:" + relative_path);
						filesystem::copy(path, copy_to_path);
					}
				}
				else if ((ctp.extension() == ".sass" || ctp.extension() == ".scss") && !css_bundle_created)
				{
					if (json_entry_exists(Settings::FILE_CONFIGS, relative_path))
					{
						JSON file_config = Settings::FILE_CONFIGS[relative_path];

						bool enabled = false;
						if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

						if (enabled)
						{
							copy_to_path_relative = (copy_to_path.substr(0, copy_to_path.find_last_of('.')) + ".min.css").substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
							Logger::log_info("Converting File:    [wwwroot]:" + copy_to_path_relative);
							convert_sass_to_css(path.c_str(), string(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.css").c_str(), 
								string(Settings::SOURCE_RESOURCE_DIR + "\\" + static_cast<string>(file_config["relativeIncludePath"])).c_str(),
								static_cast<int>(file_config["precision"]));
							css_bundle_created = true;
						}
					}
				}
				else if (ctp.extension() == ".js")
				{

				}
				else 
				{
					Logger::log_info("Copying File:       [wwwroot]:" + relative_path);
					filesystem::copy(path, copy_to_path);
				}
			}
			else
			{
				Logger::log_info("Skipping File:      [wwwroot]:" + relative_path);
			}
		}
	}
}

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