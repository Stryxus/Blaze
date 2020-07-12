#pragma once

class Logger
{
public:
	enum COLOR
	{
		BLUE_FOREGROUND = 1,
		GREEN_FOREGROUND = 2,
		CYAN_FOREGROUND = 3,
		RED_FOREGROUND = 4,
		MAGENTA_FOREGROUND = 5,
		YELLOW_FOREGROUND = 6,
		WHITE_FOREGROUND = 7,
		BLACK_FOREGROUND = 8,

		BRIGHT_BLUE_FOREGROUND = 9,
		BRIGHT_GREEN_FOREGROUND = 10,
		BRIGHT_CYAN_FOREGROUND = 11,
		BRIGHT_RED_FOREGROUND = 12,
		BRIGHT_MAGENTA_FOREGROUND = 13,
		BRIGHT_YELLOW_FOREGROUND = 14,
		BRIGHT_WHITE_FOREGROUND = 15,
		BRIGHT_BLACK_FOREGROUND = 16,

		/*
		BLUE_BACKGROUND = 17,
		GREEN_BACKGROUND = 18,
		CYAN_BACKGROUND = 19,
		RED_BACKGROUND = 20,
		MAGENTA_BACKGROUND = 21,
		YELLOW_BACKGROUND = 22,
		WHITE_BACKGROUND = 23,
		BLACK_BACKGROUND = 24,

		BRIGHT_BLUE_BACKGROUND = 25,
		BRIGHT_GREEN_BACKGROUND = 26,
		BRIGHT_CYAN_BACKGROUND = 27,
		BRIGHT_RED_BACKGROUND = 28,
		BRIGHT_MAGENTA_BACKGROUND = 29,
		BRIGHT_YELLOW_BACKGROUND = 30,
		BRIGHT_WHITE_BACKGROUND = 31,
		BRIGHT_BLACK_BACKGROUND = 32
		*/
	};

	static void log_info(string message);
	static void log_warn(string message);
	static void log_error(string message);
	static void log_info(wstring message);
	static void log_warn(wstring message);
	static void log_error(wstring message);
	static void log_nl(int amount = 1);
	static void log_divide();

	static void set_log_color(COLOR color);

	static void flush_log_buffer();

private:
	static string get_date_time_string();
	static wstring get_date_time_wstring();
	static int get_console_buffer_width();
};