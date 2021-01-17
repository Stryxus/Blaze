#pragma once

void add_scss_for_minification(const char* from);
void add_css_for_minification(const char* from);
void minify_css(const char* to, const char* includePath, int precision);