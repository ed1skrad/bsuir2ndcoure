// customer.cpp

#include "customer.h"

Customer::Customer() {
    customerId = 0;
}

int Customer::getCustomerId() const { return customerId; }
void Customer::setCustomerId(int id) { customerId = id; }

const std::string& Customer::getName() const { return name; }
void Customer::setName(const std::string& n) { name = n; }

const std::string& Customer::getSurname() const { return surname; }
void Customer::setSurname(const std::string& s) { surname = s; }

const std::string& Customer::getContactInformation() const { return contactInformation; }
void Customer::setContactInformation(const std::string& info) { contactInformation = info; }
