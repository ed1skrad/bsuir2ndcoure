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

    int getCustomerId();
    void setCustomerId(int customerId);

    std::string getName();
    void setName(std::string name);

    std::string getSurname();
    void setSurname(std::string surname);

    std::string getContactInformation();
    void setContactInformation(std::string contactInformation);
};

#endif // COURSEWORK_CUSTOMER_H
