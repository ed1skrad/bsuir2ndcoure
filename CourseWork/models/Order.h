// order.h

#ifndef COURSEWORK_ORDER_H
#define COURSEWORK_ORDER_H

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include "../database/Database.h"

class Order {
private:
    int orderId;
    int customerId;
    int carId;
    std::string orderTime;

public:
    Order();
    Order(int orderId, int customerId, int carId, const std::string& orderTime);

    int getOrderId();
    void setOrderId(int orderId);

    int getCustomerId();
    void setCustomerId(int customerId);

    int getCarId();
    void setCarId(int carId);

    std::string getOrderTime();
    void setOrderTime(std::string orderTime);

    std::string getCurrentTime();

    static void printAllOrders(Database &db, int isLogged);
};

#endif // COURSEWORK_ORDER_H
