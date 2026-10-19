#include "var_10.h"
#include "str_ops.h"
#include <cctype>

std::size_t str_count_words (const char *s){
    if ((!s) || (s[0] == '\0')) return 0;
    std::size_t count = 0;

    bool in_word = false;
    for (std::size_t i = 0; s[i] != '\0'; ++i) {
        if (std::isspace(static_cast<unsigned char>(s[i]))) {
            if (in_word) {
                in_word = false;
            }

        } else {
            if (!in_word) {
                ++count;
                in_word = true;
            }
        }
    }
    return count;
}

bool str_find_substr(const char* s, const char* sub, int& out_pos) {
    if (!s || !sub) {
        out_pos = -1;
        return false;
    }

    std::size_t s_len = str_len(s);
    std::size_t sub_len = str_len(sub);

    if (sub_len == 0 || sub_len > s_len) {
        out_pos = -1;
        return false;
    }

    for (std::size_t i = 0; i <= s_len - sub_len; ++i) {
        bool found = true;
        for (std::size_t j = 0; j < sub_len; ++j) {
            if (s[i + j] != sub[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            out_pos = static_cast<int>(i);
            return true;
        }
    }
    out_pos = -1;
    return false;
    
}