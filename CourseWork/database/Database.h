//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_DATABASE_H
#define COURSEWORK_DATABASE_H
#include <iostream>
#include "pqxx/pqxx"

class Database {
private:
    pqxx::connection C;

public:
    Database() : C("dbname=CourseWorkDb user=postgres password=aboba hostaddr=127.0.0.1 port=5432") {
        if (C.is_open()) {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            throw std::runtime_error("Failed to open database");
        }
    }

    ~Database() {
    }

    pqxx::result executeQuery(const std::string& query) {
        pqxx::nontransaction N(C);
        return N.exec(query);
    }
};


#endif //COURSEWORK_DATABASE_H