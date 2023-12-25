#ifndef LABSCPP_FILEPROC_H
#define LABSCPP_FILEPROC_H

#include "cstring"
#include "fstream"
#include "Serializable.h"
class File {
    char filename[80];
    std::fstream* fstr;
    int maxpos;
    void updateMaxPos();
public:
    File(const char* filename);
    ~File();
    int open();
    const char* getName();

    template<class T>
    void writeText(std::string path, T& data);

    void writeBinary(std::string path, Serializable& data);
    template<class T>
    void readText(std::string path, T& data);

    void readBinary(std::string path, Serializable& data);

    void remote();
    int del();
};

File::File(const char* filename_t) {
    strncpy(filename, filename_t, 80);
    fstr = new std::fstream;
}

File::~File() {
    if (fstr->is_open()) {
        fstr->close();
    }
    delete fstr;
}

int File::open() {
    fstr->open(filename, std::ios::in | std::ios::out | std::ios::trunc);
    if (!fstr->is_open()) return -1;
    return 0;
}

const char* File::getName() {
    return this->filename;
}

template<class T>
void File::writeText(std::string path, T& data) {
    std::ofstream file(path);
    if (!file.good())
        throw std::runtime_error("Unable to open file");
    file << data;
    file.close();
}

void File::writeBinary(std::string path, Serializable& data) {
    std::ofstream file(path, std::ios::binary);
    if (!file.good())
        throw std::runtime_error("Unable to open file");
    data.serialize(file);
    file.close();
}

template<class T>
void File::readText(std::string path, T& data) {
    std::ifstream file(path);
    if (!file.good())
        throw std::runtime_error("Unable to open file");
    file >> data;
    file.close();
}

void File::readBinary(std::string path, Serializable& data) {
    std::ifstream file(path, std::ios::binary);
    if (!file.good())
        throw std::runtime_error("Unable to open file");
    data.deserialize(file);
    file.close();
}


#endif
