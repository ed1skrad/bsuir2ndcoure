// customer.h

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
    Customer();

    int getCustomerId() const;
    void setCustomerId(int id);

    const std::string& getName() const;
    void setName(const std::string& n);

    const std::string& getSurname() const;
    void setSurname(const std::string& s);

    const std::string& getContactInformation() const;
    void setContactInformation(const std::string& info);
};

#endif // COURSEWORK_CUSTOMER_H
