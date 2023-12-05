#ifndef COURSEWORK_CUSTOMER_H
#define COURSEWORK_CUSTOMER_H

#include <iostream>

class Customer {
private:
    int customerId;
    std::string name;
    std::string surname;
    std::string contactInformation;

public:
    Customer() {
        customerId = 0;
    }

    int getCustomerId() const { return customerId; }
    void setCustomerId(int id) { customerId = id; }

    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    const std::string& getSurname() const { return surname; }
    void setSurname(const std::string& s) { surname = s; }

    const std::string& getContactInformation() const { return contactInformation; }
    void setContactInformation(const std::string& info) { contactInformation = info; }
};

#endif //COURSEWORK_CUSTOMER_H
