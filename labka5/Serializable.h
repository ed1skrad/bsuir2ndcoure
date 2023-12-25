//
// Created by atema on 25.12.2023.
//

#ifndef LABKA5_SERIALIZABLE_H
#define LABKA5_SERIALIZABLE_H
#pragma once
#include <fstream>
#include <iostream>
class Serializable {
public:
    virtual void serialize(std::ofstream& file) {}
    virtual void deserialize(std::ifstream& file) {}
};
#endif //LABKA5_SERIALIZABLE_H
