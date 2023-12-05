//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_ORDER_H
#define COURSEWORK_ORDER_H

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

class Orders {
private:
    int orderId;
    int customerId;
    int carId;
    std::string orderTime;

public:
    Orders() : orderId(0), customerId(0), carId(0), orderTime(getCurrentTime()) {}

    Orders(int orderId, int customerId, int carId, const std::string& orderTime)
            : orderId(orderId), customerId(customerId), carId(carId), orderTime(orderTime) {}

    int getOrderId() const { return orderId; }
    void setOrderId(int id) { orderId = id; }

    int getCustomerId() const { return customerId; }
    void setCustomerId(int id) { customerId = id; }

    int getCarId() const { return carId; }
    void setCarId(int id) { carId = id; }

    const std::string& getOrderTime() const { return orderTime; }
    void setOrderTime(const std::string& time) { orderTime = time; }

    std::string getCurrentTime() const {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::ctime(&currentTime);
        return ss.str();
    }
};

#endif //COURSEWORK_ORDER_H
