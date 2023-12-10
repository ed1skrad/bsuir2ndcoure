//
// Created by atema on 09.12.2023.
//

#ifndef COURSEWORK_INPUTVALIDATIONEXCEPTION_H
#define COURSEWORK_INPUTVALIDATIONEXCEPTION_H
#include <iostream>
class InputValidationException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input. Please enter a valid value.";
    }
};

#endif //COURSEWORK_INPUTVALIDATIONEXCEPTION_H
