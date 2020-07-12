#pragma warning(disable : 6031);
#pragma warning(disable : 4081);

#define WIN32_LEAN_AND_MEAN

using namespace std;

#include <Windows.h>
#include <stdlib.h>
#include <fstream>
#include <filesystem>
#include <algorithm> 
#include <time.h>
#include <chrono>

#include <vector>
#include <string>
#include <map>

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

#include "globals.h"
#include "logger.h"
#include "settings.h"
#include "ioutils.h"
#include "stringutils.h"
#include "jsonutils.h"