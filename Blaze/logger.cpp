#include "pch.hpp"
#include "logger.hpp"

bool Logger::is_using_custom_color = false;
Logger::COLOR Logger::global_foregronnd_color = COLOR::BRIGHT_WHITE_FOREGROUND;

void Logger::log_info(string message)
{
	if (!is_using_custom_color) set_console_color_internal(COLOR::BRIGHT_WHITE_FOREGROUND);
	printf(string("\n" + get_date_time_string() + "[INFO]:  " + message).c_str());
	if (!is_using_custom_color) set_console_color_internal(global_foregronnd_color);
}

void Logger::log_warn(string message)
{
	if (!is_using_custom_color) set_console_color_internal(COLOR::YELLOW_FOREGROUND);
	printf(string("\n" + get_date_time_string() + "[WARN]:  " + message).c_str());
	if (!is_using_custom_color) set_console_color_internal(global_foregronnd_color);
}

void Logger::log_error(string message)
{
	if (!is_using_custom_color) set_console_color_internal(COLOR::RED_FOREGROUND);
	printf(string("\n" + get_date_time_string() + "[ERROR]: " + message).c_str());
	if (!is_using_custom_color) set_console_color_internal(global_foregronnd_color);
} 

void Logger::log_info(wstring message)
{
	if (!is_using_custom_color) set_console_color_internal(COLOR::BRIGHT_WHITE_FOREGROUND);
	wprintf(wstring(L"\n" + get_date_time_wstring() + L"[INFO]:  " + message).c_str());
	if (!is_using_custom_color) set_console_color_internal(global_foregronnd_color);
}

void Logger::log_warn(wstring message)
{
	if (!is_using_custom_color) set_console_color_internal(COLOR::YELLOW_FOREGROUND);
	wprintf(wstring(L"\n" + get_date_time_wstring() + L"[WARN]:  " + message).c_str());
	if (!is_using_custom_color) set_console_color_internal(global_foregronnd_color);
}

void Logger::log_error(wstring message)
{
	if (!is_using_custom_color) set_console_color_internal(COLOR::RED_FOREGROUND);
	wprintf(wstring(L"\n" + get_date_time_wstring() + L"[ERROR]: " + message).c_str());
	if (!is_using_custom_color) set_console_color_internal(global_foregronnd_color);
}

void Logger::log_nl(int amount)
{
	if (amount < 1) amount = 1;
	for (int i = 0; i < amount; i++) printf("\n");
}

void Logger::log_divide()
{
	string divide = "";
	for (int i = 0; i < get_console_buffer_width() - 1; i++) divide += "-";
	printf(string("\n" + divide).c_str());
}

void Logger::set_global_foreground_color(COLOR color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (unsigned short)color);
	global_foregronnd_color = color;
}

/*
void Logger::set_global_background_color(COLOR color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (unsigned short)color);
}
*/

void Logger::set_console_color(COLOR color)
{
	is_using_custom_color = true;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (unsigned short)color);
}

void Logger::clear_console_color()
{
	is_using_custom_color = false;
}

void Logger::set_console_color_internal(COLOR color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (unsigned short)color);
}

void Logger::flush_log_buffer()
{
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written = 0;
	DWORD cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void Logger::log_last_error()
{
	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
	string message(messageBuffer, size);
	LocalFree(messageBuffer);
	Logger::log_error(message);
}

void Logger::wait()
{
	char c;
	cin >> std::noskipws;
	while (cin >> c) cout << c << std::endl;
}

string Logger::get_date_time_string()
{
	time_t now = cr::system_clock::to_time_t(cr::system_clock::now());
	tm current_time{};
	localtime_s(&current_time, &now);
	string year = to_string(1900 + current_time.tm_year);
	string month = current_time.tm_mon > 8 ? to_string(1 + current_time.tm_mon) : "0" + to_string(1 + current_time.tm_mon);
	string day = current_time.tm_mday > 8 ? to_string(1 + current_time.tm_mday) : "0" + to_string(1 + current_time.tm_mday);
	string hour = current_time.tm_hour != 60 ? current_time.tm_hour > 8 ? to_string(1 + current_time.tm_hour) : "0" + to_string(1 + current_time.tm_hour) : "00";
	string minute = current_time.tm_min != 60 ? current_time.tm_min > 8 ? to_string(1 + current_time.tm_min) : "0" + to_string(1 + current_time.tm_min) : "00";
	string second = current_time.tm_sec != 60 ? current_time.tm_sec > 8 ? to_string(1 + current_time.tm_sec) : "0" + to_string(1 + current_time.tm_sec) : "00";
	string millisecond = to_string((cr::duration_cast<cr::milliseconds>(cr::system_clock::now().time_since_epoch())).count()).substr(10);
	return "[" + year + "/" + month + "/" + day + " " + hour + ":" + minute + ":" + second + "." + millisecond + "]";
}

wstring Logger::get_date_time_wstring()
{
	return string_to_wstring_copy(get_date_time_string());
}

int Logger::get_console_buffer_width()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}