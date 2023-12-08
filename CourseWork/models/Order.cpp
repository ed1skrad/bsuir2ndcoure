// order.cpp

#include "order.h"

Order::Order() : orderId(0), customerId(0), carId(0), orderTime(getCurrentTime()) {}

Order::Order(int orderId, int customerId, int carId, const std::string& orderTime)
        : orderId(orderId), customerId(customerId), carId(carId), orderTime(orderTime) {}

int Order::getOrderId() const { return orderId; }
void Order::setOrderId(int id) { orderId = id; }

int Order::getCustomerId() const { return customerId; }
void Order::setCustomerId(int id) { customerId = id; }

int Order::getCarId() const { return carId; }
void Order::setCarId(int id) { carId = id; }

const std::string& Order::getOrderTime() const { return orderTime; }
void Order::setOrderTime(const std::string& time) { orderTime = time; }

std::string Order::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::ctime(&currentTime);
    return ss.str();
}
