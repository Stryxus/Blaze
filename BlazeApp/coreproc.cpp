#include "pch.h"
#include "coreproc.h"

#include "imgproc.h"
#include "sassproc.h"
#include "jsproc.h"

string minify_js(string(*f)(string&), string content)
{
	return (*f)(content);
}

vector<string> directory_sub_extention_exclusion_filter{ ".scss", ".sass", ".css", ".js", ".min.css", ".min.js" };
string scss_bundle_file_path = "";
bool should_minify_css = false;
bool should_minify_js = false;

void process_file(filesystem::path& ctp, string& path, string& relative_path, string& copy_to_path, string& copy_to_path_relative)
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
	else if (ctp.extension() == ".sass" || ctp.extension() == ".scss")
	{
		if (json_entry_exists(Settings::FILE_CONFIGS, relative_path) && scss_bundle_file_path.empty())
		{
			JSON file_config = Settings::FILE_CONFIGS[relative_path];

			bool enabled = false;
			if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

			if (enabled)
			{
				copy_to_path_relative = copy_to_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
				Logger::log_info("Converting File:    [wwwroot]:" + copy_to_path_relative);
				add_scss_for_minification(path.c_str());
				should_minify_css = true;
				scss_bundle_file_path = path;
			}
		}
		else if (!scss_bundle_file_path.empty())
		{
			Logger::log_info("Converting File:    [wwwroot]:" + scss_bundle_file_path);
			add_scss_for_minification(scss_bundle_file_path.c_str());
			should_minify_css = true;
		}
	}
	else if (ctp.extension() == ".css")
	{
		if (json_entry_exists(Settings::FILE_CONFIGS, relative_path))
		{
			JSON file_config = Settings::FILE_CONFIGS[relative_path];

			bool enabled = false;
			if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

			if (enabled)
			{
				copy_to_path_relative = copy_to_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
				Logger::log_info("Converting File:    [wwwroot]:" + copy_to_path_relative);
				add_css_for_minification(path.c_str());
				should_minify_css = true;
			}
		}
	}
	else if (ctp.extension() == ".js")
	{
		if (json_entry_exists(Settings::FILE_CONFIGS, relative_path))
		{
			JSON file_config = Settings::FILE_CONFIGS[relative_path];

			bool enabled = false;
			if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

			if (enabled)
			{
				copy_to_path_relative = copy_to_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
				Logger::log_info("Converting File:    [wwwroot]:" + copy_to_path_relative);
				add_js_for_minification(path.c_str());
				should_minify_js = true;
			}
		}
		else
		{
			Logger::log_info("Copying File:       [wwwroot]:" + relative_path);
			filesystem::copy(path, copy_to_path);
		}
	}
	else
	{
		Logger::log_info("Copying File:       [wwwroot]:" + relative_path);
		filesystem::copy(path, copy_to_path);
	}
}

void process_entry(const filesystem::directory_entry& entry)
{
	string path = replace_copy(entry.path().string(), "\\", "/");
	string relative_path = path.substr(strlen(Settings::SOURCE_RESOURCE_DIR.c_str()));
	string copy_to_path = "";
	string copy_to_path_relative = "";

	bool is_blacklisted = false;

	for (string s : Settings::BLACKLISTED_DIRECTORIES)
	{
		if (is_blacklisted = path.find(s) != string::npos) break;
	}

	if (!is_blacklisted)
	{
		if (is_directory(entry))
		{
			copy_to_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + path.substr(strlen(Settings::SOURCE_RESOURCE_DIR.c_str()));
			filesystem::path ctp(copy_to_path);
			for (const filesystem::directory_entry& entry2 : filesystem::recursive_directory_iterator(entry))
			{
				if (!is_directory(entry2) && find(directory_sub_extention_exclusion_filter.begin(), directory_sub_extention_exclusion_filter.end(), entry2.path().extension()) == directory_sub_extention_exclusion_filter.end())
				{
					if (filesystem::exists(path))
					{
						if (!filesystem::exists(copy_to_path))
						{
							Logger::log_nl();
							Logger::set_log_color(Logger::COLOR::GREEN_FOREGROUND);
							Logger::log_info("Creating Directory: [wwwroot]:" + relative_path);
							Logger::set_log_color(Logger::COLOR::BRIGHT_WHITE_FOREGROUND);
							Logger::log_divide();
							filesystem::create_directory(ctp);
						}
					}
					else
					{
						if (filesystem::exists(copy_to_path))
						{
							Logger::log_info("Deleting Directory: [wwwroot]:" + copy_to_path_relative);
							filesystem::remove_all(copy_to_path);
						}
					}
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
				if (json_entry_exists(Settings::FILE_CONFIGS, relative_path))
				{
					JSON file_config = Settings::FILE_CONFIGS[relative_path];
					if (filesystem::exists(path))
					{
						if (filesystem::exists(copy_to_path))
						{
							if (filesystem::last_write_time(path) != filesystem::last_write_time(copy_to_path)) process_file(ctp, path, relative_path, copy_to_path, copy_to_path_relative);
						}
						else process_file(ctp, path, relative_path, copy_to_path, copy_to_path_relative);
					}
					else
					{
						if (filesystem::exists(copy_to_path))
						{
							Logger::log_info("Deleting File:      [wwwroot]:" + copy_to_path_relative);
							filesystem::remove_all(copy_to_path);
						}
					}
				}
			}
		}
	}
}

void start_project_processing()
{
	if (Settings::FORMAT_RESOURCE_DIR)
	{
		filesystem::remove_all(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
		filesystem::create_directory(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
	}

	Logger::log_info("Listening for file changes...");
	Logger::log_nl();

	unordered_map<string, filesystem::file_time_type> path_access_times;

	while (TRUE) 
	{
		for (const filesystem::directory_entry& entry : filesystem::recursive_directory_iterator(Settings::SOURCE_RESOURCE_DIR))
		{
			string path = entry.path().string();
			if (path_access_times.find(path) != path_access_times.end())
			{
				filesystem::file_time_type last_write;
				if ((last_write = filesystem::last_write_time(entry)) != path_access_times[path])
				{
					process_entry(entry);
					path_access_times[path] = last_write;
				}
			}
			else 
			{
				process_entry(entry);
				path_access_times[path] = filesystem::last_write_time(entry);
			}
		}

		if (should_minify_css) 
		{
			string css_bundle_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.css";
			if (filesystem::exists(css_bundle_path)) filesystem::remove_all(css_bundle_path);
			minify_css(css_bundle_path.c_str(), replace_copy(string(Settings::SOURCE_RESOURCE_DIR + "\\" + Settings::SCSS_INCLUDE_DIR), "\\", "/").c_str(), Settings::SCSS_PRECISION);
			should_minify_css = false;
		}

		if (should_minify_js) 
		{
			string js_bundle_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.js";
			if (filesystem::exists(js_bundle_path)) filesystem::remove_all(js_bundle_path);
			minify_js(js_bundle_path.c_str());
			should_minify_js = false;
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}