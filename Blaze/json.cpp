#include "pch.hpp"
#include "json.hpp"

bool json_entry_exists(JSON json, string key)
{
	return json.find(key) != json.end();
}