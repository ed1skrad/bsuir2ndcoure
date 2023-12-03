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
    int order_id;
    int customer_id;
    int car_id;
    std::string order_time;

public:
    Orders() : order_id(0), customer_id(0), car_id(0), order_time(getCurrentTime()) {}

    Orders(int order_id, int customer_id, int car_id, const std::string& order_time)
            : order_id(order_id), customer_id(customer_id), car_id(car_id), order_time(order_time) {}

    int getOrderId() const { return order_id; }
    void setOrderId(int id) { order_id = id; }

    int getCustomerId() const { return customer_id; }
    void setCustomerId(int id) { customer_id = id; }

    int getCarId() const { return car_id; }
    void setCarId(int id) { car_id = id; }

    const std::string& getOrderTime() const { return order_time; }
    void setOrderTime(const std::string& time) { order_time = time; }

    std::string getCurrentTime() const {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::ctime(&currentTime);
        return ss.str();
    }
};


#endif //COURSEWORK_ORDER_H
