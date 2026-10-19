#include <iostream>
#include <limits>
#include <new>
#include "str_ops.h"
#include "var_10.h"
#include "buff.h"

int main() {
    char* current_string = nullptr;
    int choise;

    while (true) {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Enter a string\n";
        std::cout << "2. Print a string\n";
        std::cout << "3. Count len of a string\n";
        std::cout << "4. Copy a string and print it\n";
        std::cout << "5. Substring in a string\n";
        std::cout << "0. Exit\n\n";

        if (!(std::cin >> choise)) {
            if (std::cin.eof()) {
                str_delete(current_string);
                return 0;
            }

            std::cout << "Invalid input. Enter a menu number\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch(choise){
            case(0):
                str_delete(current_string);
                return 0;
            
            case(1): {
                str_delete(current_string);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Enter a string: ";

                char* buffer = read_str();

                if (!buffer) {
                    std::cout << "Memory allocation failed\n";
                    break;
                }

                if(std::cin.fail()) {
                    std::cout << "Input error\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    str_delete(buffer);
                    break;
                }

                current_string = buffer;
                std::cout << "String stored successfully\n";
                break;
            }

            case(2):
                std::cout << "String: ";
                str_print(current_string);
                std::cout << "\n";
                break;

            case(3):
                if (current_string) {
                    std::cout << "Length: " << str_len(current_string) << "\n";
                } else {
                    std::cout << "Not string available" << "\n";
                }
                break;

            case(4):{
                if (!current_string) {
                    std::cout << "No string to copy\n";
                    break;
                }

                size_t len = str_len(current_string);
                char* buf = new (std::nothrow) char[len + 1];
                if (!buf) {
                    std::cout << "Memory allocation failed\n";
                    break;
                }

                str_copy(buf, current_string);
                std::cout << "Copy: ";
                str_print(buf);
                std::cout << "\n";
                delete[] buf;
                buf = nullptr;
                break;
            }
            case (5): {
                if (!current_string || str_len(current_string) == 0) {
                    std::cout << "Empty string\n";
                    break;
                }
                std::cout << "Word count: " << str_count_words(current_string) << "\n";

                std::cout << "Enter substring to search: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                char* sub_buf = read_str();
                if (!sub_buf) {
                    std::cout << "Memory allocation failed\n";
                    break;
                }
                if (str_len(sub_buf) == 0) {
                    std::cout << "Empty substring\n";
                    str_delete(sub_buf);
                    break;
                }

                int pos = -1;
                if (str_find_substr(current_string, sub_buf, pos)) {
                    std::cout << "Found at position: " << pos << "\n";
                } else {
                    std::cout << "Substring not found\n";
                }
                str_delete(sub_buf);
                break;
            }
            default:
            std::cout << "Choose a number 0-5 \n";   
        }
    }
}