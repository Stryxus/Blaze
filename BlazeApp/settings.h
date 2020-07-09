#pragma once

class Settings
{
public:
	static JSON defaultSettings;
	static JSON settings;

	static int GetSettings();
	static int SetSettings(bool setDefaultSettings = false);
};