#include "pch.h"
#include "ioutils.h"

bool fileExists(const string& filePath)
{
	struct stat buffer;
	return stat(filePath.c_str(), &buffer) == 0;
}

void createFile(const string& filePath)
{
	ofstream(filePath).close();
}