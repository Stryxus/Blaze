#include "pch.h"
#include "coreproc.h"

#include "imgproc.h"
#include "sassproc.h"
#include "jsproc.h"

string minify_js(string(*f)(string&), string content)
{
	return (*f)(content);
}

vector<string> directory_sub_extention_exclusion_filter{ ".scss", ".sass", ".css", ".js", ".min.css", ".min.js", ".wav" };
string scss_bundle_file_path = "";
bool should_minify_css = false;
bool should_minify_js = false;

void process_file(filesystem::path& ctp, filesystem::path& extension, JSON file_config, string& path, string& relative_path, string& copy_to_path, string& copy_to_path_relative)
{
	if (extension == ".png")
	{
		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

		if (enabled)
		{
			Logger::log_info("Processing File:    [wwwroot]:" + copy_to_path_relative);
			convert_png_to_webp(path.c_str(), copy_to_path.c_str(),
				static_cast<int>(file_config["width"]),
				static_cast<int>(file_config["height"]),
				static_cast<float>(file_config["quality"]));
		}
	}
	else if (extension == ".sass" || extension == ".scss")
	{
		JSON file_config = Settings::FILE_CONFIGS[relative_path];

		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

		if (enabled)
		{
			if (scss_bundle_file_path.empty())
			{
				Logger::log_info("Processing File:    [wwwroot]:" + copy_to_path_relative);
				add_scss_for_minification(path.c_str());
				should_minify_css = true;
				scss_bundle_file_path = path;
			}
			else 
			{
				add_scss_for_minification(scss_bundle_file_path.c_str());
				should_minify_css = true;
			}
		}
	}
	else if (extension == ".css")
	{
		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

		if (enabled)
		{
			Logger::log_info("Processing File:    [wwwroot]:" + copy_to_path_relative);
			add_css_for_minification(path.c_str());
			should_minify_css = true;
		}
	}
	else if (extension == ".js")
	{
		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

		if (enabled)
		{
			Logger::log_info("Processing File:    [wwwroot]:" + copy_to_path_relative);
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

bool is_scss_bundle_compiled = false;

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
		bool isDir = is_directory(entry);
		filesystem::path ctp(isDir ? Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + path.substr(strlen(Settings::SOURCE_RESOURCE_DIR.c_str())) : Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + relative_path);
		if (isDir)
		{
			for (const filesystem::directory_entry& entry2 : filesystem::recursive_directory_iterator(entry))
			{
				if (!is_directory(entry2) && find(directory_sub_extention_exclusion_filter.begin(), directory_sub_extention_exclusion_filter.end(), entry2.path().extension()) == directory_sub_extention_exclusion_filter.end())
				{
					if (filesystem::exists(path))
					{
						if (!filesystem::exists(ctp))
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
						if (filesystem::exists(ctp))
						{
							Logger::log_info("Deleting Directory: [wwwroot]:" + relative_path);
							filesystem::remove_all(ctp);
						}
					}
					break;
				}
			}
		}
		else
		{
			filesystem::path extension;
			if (ctp.has_extension() && (extension = ctp.extension()) != "")
			{
				if (json_entry_exists(Settings::FILE_CONFIGS, relative_path) || 
					extension == ".scss" ||
					extension == ".sass" ||
					extension == ".css"
					)
				{
					if (extension == ".png")
					{
						copy_to_path = replace_copy(ctp.string(), ".png", ".webp");
						copy_to_path_relative = copy_to_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));

						if (filesystem::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, copy_to_path_relative);
						else
						{
							if (filesystem::exists(copy_to_path))
							{
								Logger::log_info("Deleting File:      [wwwroot]:" + copy_to_path_relative);
								filesystem::remove_all(copy_to_path);
							}
						}
					}
					else if (extension == ".sass" || extension == ".scss")
					{
						if (!is_scss_bundle_compiled)
						{
							is_scss_bundle_compiled = true;
							copy_to_path = ctp.string();
							copy_to_path_relative = copy_to_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));

							if (filesystem::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, copy_to_path_relative);
							else
							{
								if (filesystem::exists(copy_to_path))
								{
									Logger::log_info("Deleting File:      [wwwroot]:" + copy_to_path_relative);
									filesystem::remove_all(copy_to_path);
								}
							}
						}
						else return;
					}
					else if (extension == ".css")
					{
						copy_to_path = ctp.string();
						copy_to_path_relative = copy_to_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));

						if (filesystem::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, copy_to_path_relative);
						else
						{
							if (filesystem::exists(copy_to_path))
							{
								Logger::log_info("Deleting File:      [wwwroot]:" + copy_to_path_relative);
								filesystem::remove_all(copy_to_path);
							}
						}
					}
					else if (extension == ".js")
					{
						copy_to_path = ctp.string();
						copy_to_path_relative = copy_to_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));

						if (filesystem::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, copy_to_path_relative);
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
				else if (
						extension == ".png" || 
						extension == ".svg" || 
						extension == ".json" || 
						extension == ".txt" || 
						extension == ".woff2" || 
						extension == ".aac" || 
						extension == ".webm" || 
						extension == ".webp" || 
						extension == ".html" ||
						extension == ".js"
					)
				{
					Logger::log_info("Copying File:       [wwwroot]:" + relative_path);
					filesystem::copy(path, ctp.string());
				}
			}
		}
	}
}

bool first_loop = true;

void start_project_processing()
{
	if (Settings::FORMAT_RESOURCE_DIR)
	{
		filesystem::remove_all(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
		filesystem::create_directory(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
	}

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

		is_scss_bundle_compiled = false;

		if (should_minify_css || should_minify_js)
		{
			Logger::log_nl();
			Logger::log_divide();
			Logger::log_nl();

			if (should_minify_css)
			{
				string css_bundle_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.css";
				Logger::log_info("Compiling File:     [wwwroot]:" + css_bundle_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str())));
				minify_css(css_bundle_path.c_str(), replace_copy(string(Settings::SOURCE_RESOURCE_DIR + "\\" + Settings::SCSS_INCLUDE_DIR), "\\", "/").c_str(), Settings::SCSS_PRECISION);
				should_minify_css = false;
			}

			if (should_minify_js)
			{
				string js_bundle_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.js";
				Logger::log_info("Compiling File:     [wwwroot]:" + js_bundle_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str())));
				minify_js(js_bundle_path.c_str());
				should_minify_js = false;
			}

			if (first_loop)
			{
				Logger::log_nl();
				Logger::log_divide();
				Logger::log_nl();
				Logger::log_info("Now listening for file changes...");
				Logger::log_nl(2);
			}
		}
		else if (first_loop)
		{
			Logger::log_nl();
			Logger::log_divide();
			Logger::log_nl();
			Logger::log_info("Now listening for file changes...");
			Logger::log_nl(2);
		}

		first_loop = false;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}