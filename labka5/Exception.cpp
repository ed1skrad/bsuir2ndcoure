#include "Exception.h"
#include <cstring>
#include <iostream>

BaseException::BaseException() : code(0) {}

BaseException::BaseException(int code_t, const char* msg_t) : code(code_t) {
    strcpy(msg, msg_t);
}

void BaseException::show() const {
    std::cout << "Error: " << code << " " << msg << std::endl;
}
