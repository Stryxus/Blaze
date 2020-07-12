#include "pch.h"
#include "logger.h"

void Logger::log_info(string message)
{
	printf(string("\n" + get_date_time_string() + "[INFO]:  " + message).c_str());
}

void Logger::log_warn(string message)
{
	printf(string("\n" + get_date_time_string() + "[WARN]:  " + message).c_str());
}

void Logger::log_error(string message)
{
	printf(string("\n" + get_date_time_string() + "[ERROR]: " + message).c_str());
}

void Logger::log_info(wstring message)
{
	wprintf(wstring(L"\n" + get_date_time_wstring() + L"[INFO]:  " + message).c_str());
}

void Logger::log_warn(wstring message)
{
	wprintf(wstring(L"\n" + get_date_time_wstring() + L"[WARN]:  " + message).c_str());
}

void Logger::log_error(wstring message)
{
	wprintf(wstring(L"\n" + get_date_time_wstring() + L"[ERROR]: " + message).c_str());
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

void Logger::set_log_color(COLOR color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
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

string Logger::get_date_time_string()
{
	time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm currentTime{};
	localtime_s(&currentTime , &now);
	string year = to_string(1900 + currentTime.tm_year);
	string month = currentTime.tm_mon > 8 ? to_string(1 + currentTime.tm_mon) : "0" + to_string(1 + currentTime.tm_mon);
	string day = currentTime.tm_mday > 8 ? to_string(1 + currentTime.tm_mday) : "0" + to_string(1 + currentTime.tm_mday);
	string hour = currentTime.tm_hour != 60 ? currentTime.tm_hour > 8 ? to_string(1 + currentTime.tm_hour) : "0" + to_string(1 + currentTime.tm_hour) : "00";
	string minute = currentTime.tm_min != 60 ? currentTime.tm_min > 8 ? to_string(1 + currentTime.tm_min) : "0" + to_string(1 + currentTime.tm_min) : "00";
	string second = currentTime.tm_sec != 60 ? currentTime.tm_sec > 8 ? to_string(1 + currentTime.tm_sec) : "0" + to_string(1 + currentTime.tm_sec) : "00";
	string millisecond = to_string((chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch())).count()).substr(0, 3);
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