#include <iostream>
#include <new>


char *read_str(){
    std::size_t capacity = 16;
    std::size_t size= 0;

    char *buf = new (std::nothrow) char[capacity];
    if (!buf) {
        return nullptr;
    }

    char ch;

    while(std::cin.get(ch)){
        if (ch == '\n'){
            break;
        }
        if (size + 1 >= capacity){
            std::size_t new_capacity = capacity *2;

            char* new_buf = new (std::nothrow) char[new_capacity];
            if (!new_buf){
                delete[] buf;
                // buf = nullptr;
                return nullptr;
            }
            for (std::size_t i = 0; i< size; i++){
                new_buf[i] = buf[i];
            }

            delete[] buf;
            buf = new_buf;
            capacity = new_capacity;
        }
        
        buf[size] = ch;
        ++size;
    }

    buf[size] = '\0';
    return buf;
}
