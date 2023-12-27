#ifndef COURSEWORK_EXCEPTION_H
#define COURSEWORK_EXCEPTION_H

#include <cstring>
#include <iostream>

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

class RouteNotFoundException : public BaseException {
public:
    RouteNotFoundException() : BaseException(8, "Route not found!") {}
};

class RouteNameException : public BaseException {
public:
    RouteNameException() : BaseException(9, "Invalid route name!") {}
};

class RouteStopsException : public BaseException {
public:
    RouteStopsException() : BaseException(10, "Invalid stops for the route!") {}
};

#endif //COURSEWORK_EXCEPTION_H
