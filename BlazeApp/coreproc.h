#pragma once

void start_project_processing();

string minify_js(string(*f)(string&), string content);