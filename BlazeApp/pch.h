#pragma warning(disable : 6031);
#pragma warning(disable : 4081);

#define WIN32_LEAN_AND_MEAN

using namespace std;

#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <clocale>
#include <locale>

#include <vector>
#include <string>

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

#include "ioutils.h"
#include "stringutils.h"