#pragma once
#include <cstddef>

char* str_alloc(const char* src);
std::size_t str_len(const char* s);
void str_copy(char* dst, const char* src);
void str_delete(char*& s);
void str_print(const char* s);