// order.h

#ifndef COURSEWORK_ORDER_H
#define COURSEWORK_ORDER_H

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

class Order {
private:
    int orderId;
    int customerId;
    int carId;
    std::string orderTime;

public:
    Order();
    Order(int orderId, int customerId, int carId, const std::string& orderTime);

    int getOrderId() const;
    void setOrderId(int id);

    int getCustomerId() const;
    void setCustomerId(int id);

    int getCarId() const;
    void setCarId(int id);

    const std::string& getOrderTime() const;
    void setOrderTime(const std::string& time);

    std::string getCurrentTime() const;
};

#endif // COURSEWORK_ORDER_H
