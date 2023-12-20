#ifndef LABKA5_EXCEPTION_H
#define LABKA5_EXCEPTION_H
#include <iostream>
#include <cstring>

class BaseException {
    int code;
    char msg[80]{};
public:
    BaseException();
    BaseException(int , const char[]);
    const char* getMsg() const { return msg; }
    void setMsg(const char* msg_t) { strcpy(msg, msg_t); }
    void show() const;
};

class StackIncorrectSizeException : public BaseException {
public:
    StackIncorrectSizeException() : BaseException(1, "StackIncorrectSize exception!") {}
};

class StackOverflowException : public BaseException {
public:
    StackOverflowException() : BaseException(2, "StackOverflow exception!") {}
};

class StackUnderflowException : public BaseException {
public:
    StackUnderflowException() : BaseException(3, "StackUnderFlow exception!") {}
};

class InputValidationException : public BaseException {
public:
    InputValidationException() : BaseException(4, "Incorrect input") {}
};

class ClockException : public BaseException {
public:
    ClockException() : BaseException(5, "Clock exception occurred") {}
};

class NegativeWeightException : public BaseException {
public:
    NegativeWeightException() : BaseException(6, "Weight cannot be negative") {}
};

class NegativePriceException : public BaseException {
public:
    NegativePriceException() : BaseException(7, "Price cannot be negative") {}
};

#endif
