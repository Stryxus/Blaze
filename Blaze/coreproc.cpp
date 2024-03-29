#include "pch.hpp"
#include "coreproc.hpp"

#include "imgproc.hpp"
#include "sassproc.hpp"
#include "jsproc.hpp"

string minify_js(string(*f)(string&), string content)
{
	return (*f)(content);
}

string scss_bundle_file_path = "";
string current_base_directory = "";
bool is_scss_bundle_compiled = false;
bool should_minify_css = false;
bool should_minify_js = false;
bool first_loop = true;

void using_directory_check(string& copy_to_path)
{
	string cpt_base = "";
	if ((cpt_base = replace_copy(copy_to_path.substr(0, copy_to_path.find_last_of("/")), Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT, "")) != current_base_directory)
	{
		Logger::log_nl();
		Logger::set_console_color(Logger::COLOR::GREEN_FOREGROUND);
		Logger::log_info("Using Directory:    [wwwroot]:" + cpt_base);
		Logger::clear_console_color();
		Logger::log_divide();
		current_base_directory = cpt_base;
	}
}

void copy_file(string& path, string& copy_to_path, string& relative_path)
{
	using_directory_check(copy_to_path);
	Logger::log_info("Copying File:       [wwwroot]:" + relative_path + " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
	fs::copy(path, copy_to_path);
}

void process_file(fs::path& ctp, fs::path& extension, JSON file_config, string& path, string& relative_path, string& copy_to_path, string& copy_to_path_relative)
{
	if (extension == ".png")
	{
		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

		if (enabled)
		{
			cr::high_resolution_clock clock;
			cr::steady_clock::time_point start_time;
			cr::steady_clock::time_point end_time;

			string format;
			if (json_entry_exists(file_config, "format")) format = static_cast<string>(file_config["format"]);

			if (!format.empty() && format == "webp") 
			{
				copy_to_path = replace_copy(ctp.string(), ".png", ".webp");
				using_directory_check(copy_to_path);
				Logger::log_info("Processing File:    [wwwroot]:" + copy_to_path_relative + " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
				start_time = clock.now();
				convert_png_to_webp(path.c_str(), copy_to_path.c_str(),
					static_cast<int>(file_config["width"]),
					static_cast<int>(file_config["height"]),
					static_cast<float>(file_config["quality"]));
				end_time = clock.now();
			}
			else 
			{
				copy_to_path = replace_copy(ctp.string(), ".png", ".webp");
				using_directory_check(copy_to_path);
				Logger::log_info("Processing File:    [wwwroot]:" + copy_to_path_relative + " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
				start_time = clock.now();
				convert_png_to_avif(path.c_str(), copy_to_path.c_str(),
					static_cast<int>(file_config["width"]),
					static_cast<int>(file_config["height"]),
					static_cast<float>(file_config["quality"]));
				end_time = clock.now();
			}

			Logger::set_console_color(Logger::COLOR::BRIGHT_GREEN_FOREGROUND);
			Logger::log_info("Processed File:     [wwwroot]:" + replace_copy(copy_to_path_relative, ".png", format == "webp" ? ".webp" : ".png") + 
																				" | Time Taken: " + milliseconds_to_time_string(cr::duration_cast<cr::milliseconds>(end_time - start_time)) 
																				+ " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(copy_to_path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
			Logger::clear_console_color();
		}
	}
	else if (extension == ".sass" || extension == ".scss")
	{
		copy_to_path = ctp.string();
		JSON file_config = Settings::FILE_CONFIGS[relative_path];

		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

		if (enabled || !scss_bundle_file_path.empty())
		{
			if (scss_bundle_file_path.empty())
			{
				using_directory_check(copy_to_path);
				Logger::log_info("Indexing File Data: [wwwroot]:" + copy_to_path_relative + " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
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
		copy_to_path = ctp.string();

		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);

		if (enabled)
		{
			using_directory_check(copy_to_path);
			Logger::log_info("Indexing File Data: [wwwroot]:" + copy_to_path_relative + " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
			add_scss_for_minification(path.c_str());
			should_minify_css = true;
		}
	}
	else if (extension == ".js")
	{
		copy_to_path = ctp.string();

		bool enabled = false;
		if (json_entry_exists(file_config, "enabled")) enabled = static_cast<bool>(file_config["enabled"]);
		int order = -1;
		if (json_entry_exists(file_config, "order")) order = static_cast<int>(file_config["order"]);

		if (enabled)
		{
			if (order != -1) 
			{
				using_directory_check(copy_to_path);
				Logger::log_info("Indexing File Data: [wwwroot]:" + copy_to_path_relative + " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
				add_js_for_minification(path.c_str(), order);
				should_minify_js = true;
			}
			else 
			{
				Logger::log_error("File: " + path + " does not include an order value in blaze-settings.json. Ignoring...");
			}
		}
	}
	else copy_file(path, copy_to_path, relative_path);
}

void process_entry(const fs::directory_entry& entry)
{
	string path = replace_copy(entry.path().string(), "\\", "/");
	string relative_path = path.substr(strlen(Settings::SOURCE_RESOURCE_DIR.c_str()));
	string copy_to_path = "";
	string copy_to_path_relative = "";

	bool is_blacklisted = false;

	vector<string> ignored;
	ignored.insert(ignored.end(), Settings::IGNORE_DIRECTORIES.begin(), Settings::IGNORE_DIRECTORIES.end());
	ignored.insert(ignored.end(), Settings::IGNORE_FILES.begin(), Settings::IGNORE_FILES.end());
	for (string s : ignored)
	{
		if (is_blacklisted = path.find(s) != string::npos) break;
	}

	if (!is_blacklisted)
	{
		bool is_dir = is_directory(entry);
		fs::path ctp(is_dir ? Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + path.substr(strlen(Settings::SOURCE_RESOURCE_DIR.c_str())) : Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + relative_path);
		string ctps(ctp.string());
		string ctps_relative(ctps.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str())));

		if (is_dir)
		{
			if (fs::exists(path))
			{
				for (const fs::directory_entry& entry2 : fs::recursive_directory_iterator(entry))
				{
					if (!is_directory(entry2) && find(Settings::IGNORE_EXTENSIONS.begin(), Settings::IGNORE_EXTENSIONS.end(), entry2.path().extension()) == Settings::IGNORE_EXTENSIONS.end())
					{
						if (fs::exists(path) && !fs::exists(ctp))
						{
							Logger::log_nl();
							Logger::set_console_color(Logger::COLOR::MAGENTA_FOREGROUND);
							Logger::log_info("Creating Directory: [wwwroot]:" + relative_path);
							Logger::clear_console_color();
							fs::create_directory(ctp);
						}
						break;
					}
				}
			}
		}
		else
		{
			fs::path extension;
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
						if (fs::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, ctps_relative);
					}
					else if (extension == ".sass" || extension == ".scss")
					{
						if (!is_scss_bundle_compiled)
						{
							if (first_loop && !json_entry_exists(Settings::FILE_CONFIGS, relative_path)) return;
							is_scss_bundle_compiled = true;
							if (fs::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, ctps_relative);
						}
						else return;
					}
					else if (extension == ".css")
					{
						if (fs::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, ctps_relative);
					}
					else if (extension == ".js")
					{
						if (fs::exists(path)) process_file(ctp, extension, Settings::FILE_CONFIGS[relative_path], path, relative_path, copy_to_path, ctps_relative);
					}
				}
				else copy_file(path, ctps, relative_path);
			}
		}
	}
}

void start_project_processing()
{
	if (Settings::FORMAT_RESOURCE_DIR)
	{
		fs::remove_all(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
		fs::create_directory(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT);
	}

	unordered_map<string, fs::file_time_type> path_access_times;

	while (TRUE) 
	{
		for (const fs::directory_entry& entry : fs::recursive_directory_iterator(Settings::SOURCE_RESOURCE_DIR)) 
		{
			string path = entry.path().string();
			if (path_access_times.find(path) != path_access_times.end())
			{
				fs::file_time_type last_write;
				if ((last_write = fs::last_write_time(entry)) != path_access_times[path])
				{
					process_entry(entry);
					path_access_times[path] = last_write;
				}
			}
			else
			{
				process_entry(entry);
				path_access_times[path] = fs::last_write_time(entry);
			}
		}

		is_scss_bundle_compiled = false;

		if (should_minify_css || should_minify_js)
		{
			Logger::log_nl();
			if (should_minify_css)
			{
				string css_bundle_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.css";
				string css_bundle_path_alt = css_bundle_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
				Logger::set_console_color(Logger::COLOR::BRIGHT_BLUE_FOREGROUND);
				Logger::log_info("Compiling File:     [wwwroot]:" + css_bundle_path_alt);
				Logger::clear_console_color();
				cr::high_resolution_clock clock;
				cr::steady_clock::time_point start_time = clock.now();
				minify_css(css_bundle_path.c_str(), replace_copy(string(Settings::SOURCE_RESOURCE_DIR + "\\" + Settings::SCSS_INCLUDE_DIR), "\\", "/").c_str(), Settings::SCSS_PRECISION);
				cr::steady_clock::time_point end_time = clock.now();
				long long result_time = cr::duration_cast<cr::milliseconds>(end_time - start_time).count();
				should_minify_css = false;
				Logger::set_console_color(Logger::COLOR::BRIGHT_GREEN_FOREGROUND);
				Logger::log_info("SCSS Compiled:      [wwwroot]:" + css_bundle_path_alt + " | Time Taken: " + milliseconds_to_time_string(cr::duration_cast<cr::milliseconds>(end_time - start_time)) 
																						+ " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(css_bundle_path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
				Logger::clear_console_color();
				Logger::log_nl();
			}

			if (should_minify_js)
			{
				string js_bundle_path = Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT + "/bundle.min.js";
				string js_bundle_path_alt = js_bundle_path.substr(strlen(Globals::SPECIFIED_PROJECT_DIRECTORY_PATH_WWWROOT.c_str()));
				Logger::set_console_color(Logger::COLOR::BRIGHT_BLUE_FOREGROUND);
				Logger::log_info("Compiling File:     [wwwroot]:" + js_bundle_path_alt);
				Logger::clear_console_color();
				cr::high_resolution_clock clock;
				cr::steady_clock::time_point start_time = clock.now();
				minify_js(js_bundle_path.c_str());
				cr::steady_clock::time_point end_time = clock.now();
				long long result_time = cr::duration_cast<cr::milliseconds>(end_time - start_time).count();
				should_minify_js = false;
				Logger::set_console_color(Logger::COLOR::BRIGHT_GREEN_FOREGROUND);
				Logger::log_info("JS Compiled:        [wwwroot]:" + js_bundle_path_alt + " | Time Taken: " + milliseconds_to_time_string(cr::duration_cast<cr::milliseconds>(end_time - start_time)) 
																					   + " [" + to_string(convert_data_magnitude_in_bytes_copy(fs::file_size(js_bundle_path), BYTE_MAGNITUDE::BYTE, BYTE_MAGNITUDE::KILO_BYTE)) + " KB]");
				Logger::clear_console_color();
				Logger::log_nl();
			}

			if (first_loop)
			{
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
		this_thread::sleep_for(cr::milliseconds(500));
	}
}