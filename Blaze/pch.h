#define WIN32_LEAN_AND_MEAN

#pragma warning(push, 0)

#include <Windows.h>
#include <thread>
#include <stdlib.h>
#include <fstream>
#include <filesystem>
#include <algorithm> 
#include <time.h>
#include <chrono>
#include <iostream>

#include <vector>
#include <string>
#include <map>

#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <curl/easy.h>

#pragma warning(pop)

using namespace std;
namespace cr = std::chrono;
namespace fs = std::filesystem;
using JSON = nlohmann::json;

#pragma warning(push)
#pragma warning(disable : 4081)

#include "netwrapper.h"
#include "string.h"
#include "time.h"
#include "io.h"
#include "json.h"
#include "net.h"
#include "globals.h"
#include "logger.h"
#include "libraries.h"
#include "settings.h"

#pragma warning(pop)