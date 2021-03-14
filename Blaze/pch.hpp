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

#include "netwrapper.hpp"
#include "string.hpp"
#include "time.hpp"
#include "io.hpp"
#include "json.hpp"
#include "net.hpp"
#include "globals.hpp"
#include "logger.hpp"
#include "libraries.hpp"
#include "settings.hpp"

#pragma warning(pop)