#pragma once
#include <cstddef>

std::size_t str_count_words(const char* s);
bool str_find_substr(const char* s, const char* sub, int& out_pos);