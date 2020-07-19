#include "pch.h"
#include "ioutils.h"

bool file_exists(const string& file_path)
{
	struct stat buffer;
	return stat(file_path.c_str(), &buffer) == 0;
}

void create_file(const string& file_path)
{
	ofstream(file_path).close();
}