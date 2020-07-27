#define WIN32_LEAN_AND_MEAN

#pragma warning(push);
#pragma warning(disable : 6031);
#pragma warning(disable : 26451);
#pragma warning(disable : 28020);

#include <Windows.h>
#include <thread>
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

#pragma warning(pop);

using namespace std;
using JSON = nlohmann::json;

#pragma warning(push);
#pragma warning(disable : 4081);

#include "strutils.h"
#include "ioutils.h"
#include "jsonutils.h"
#include "globals.h"
#include "logger.h"
#include "libraries.h"
#include "settings.h"

#pragma warning(pop);