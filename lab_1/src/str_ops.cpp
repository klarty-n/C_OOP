#include "str_ops.h"
#include <iostream>

std::size_t str_len(const char* s) {
    if (!s) return 0;
    std::size_t len = 0;
    while (s[len] != '\0') ++len;
    return len;
}

void str_copy(char* dst, const char* src) {
    if (!dst || !src) return;
    std::size_t i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

char* str_alloc(const char* src) {
    if (!src) return nullptr;
    std::size_t len = str_len(src);
    char* buf = new char[len + 1];
    str_copy(buf, src);
    return buf;
}

void str_delete(char*& s) {
    delete[] s;
    s = nullptr;
}

void str_print(const char* s) {
    if (!s) {
        std::cout << "null";
        return;
    }
    std::cout << s;
}