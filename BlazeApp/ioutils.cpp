#include "pch.h"
#include "ioutils.h"

bool fileExists(const string& file_path)
{
	struct stat buffer;
	return stat(file_path.c_str(), &buffer) == 0;
}

void createFile(const string& file_path)
{
	ofstream(file_path).close();
}