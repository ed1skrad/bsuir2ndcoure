#ifndef COURSEWORK_CUSTOMER_H
#define COURSEWORK_CUSTOMER_H
#include <iostream>

class Customer {
private:
    int customer_id;
    std::string name;
    std::string surname;
    std::string contact_information;

public:
    Customer() {
        customer_id = 0;
    }

    int getCustomerId() const { return customer_id; }
    void setCustomerId(int id) { customer_id = id; }

    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    const std::string& getSurname() const { return surname; }
    void setSurname(const std::string& s) { surname = s; }

    const std::string& getContactInformation() const { return contact_information; }
    void setContactInformation(const std::string& info) { contact_information = info; }
};
#endif
