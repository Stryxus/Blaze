#include "pch.h"
#include "jsonutils.h"

bool json_entry_exists(JSON json, string key)
{
	return json.find(key) != json.end();
}