// customer.cpp

#include "customer.h"

Customer::Customer() {
    customerId = 0;
}

int Customer::getCustomerId() {
    return customerId;
}
void Customer::setCustomerId(int customerId) {
    this->customerId = customerId;
}

std::string Customer::getName() {
    return name;
}
void Customer::setName(std::string name) {
    this->name = name;
}

std::string Customer::getSurname() {
    return surname;
}
void Customer::setSurname(std::string surname) {
    this->surname = surname;
}

std::string Customer::getContactInformation()  {
    return contactInformation;
}
void Customer::setContactInformation(std::string contactInformation) {
    this->contactInformation = contactInformation;
}
