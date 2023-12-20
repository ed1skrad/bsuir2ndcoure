#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <cstring>
#include <iostream>

class File {
private:
    char filename[80];
    std::fstream* fstr;

public:
    File(char* filename);
    ~File();
    int open();
    const char* getName();
    void remove();
    int del();

    // Template method for writing to a text file
    template <typename T>
    void writeText(const T& obj) {
        if (!fstr->is_open()) {
            std::cerr << "File is not open for writing.\n";
            return;
        }

        *fstr << obj;  // Write the object to the file
    }

    // Template method for reading from a text file
    template <typename T>
    void readText(T& obj) {
        if (!fstr->is_open()) {
            std::cerr << "File is not open for reading.\n";
            return;
        }

        *fstr >> obj;  // Read the object from the file
    }

    // Template method for writing to a binary file
    template <typename T>
    void writeBinary(const T& obj) {
        if (!fstr->is_open()) {
            std::cerr << "File is not open for writing.\n";
            return;
        }

        fstr->write(reinterpret_cast<const char*>(&obj), sizeof(obj));  // Write the object to the file
    }

    // Template method for reading from a binary file
    template <typename T>
    void readBinary(T& obj) {
        if (!fstr->is_open()) {
            std::cerr << "File is not open for reading.\n";
            return;
        }

        fstr->read(reinterpret_cast<char*>(&obj), sizeof(obj));  // Read the object from the file
    }
};

#endif // FILE_H
