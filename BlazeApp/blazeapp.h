#pragma once

class References
{
public:
	static string APP_NAME;
	static string APP_VERSION;
};

class Globals
{
public:
	static string specifiedProjectDirectoryPath;
};

class BlazeSettings
{
public:
	static JSON defaultSettings;
	static JSON settings;

	static int GetSettings();
	static int SetSettings(bool setDefaultSettings = false);
};

int main(int argc, const char* argv[]);