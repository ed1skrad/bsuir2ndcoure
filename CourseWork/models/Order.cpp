// order.cpp

#include <vector>
#include "order.h"
#include "../database/Database.h"

Order::Order() : orderId(0), customerId(0), carId(0), orderTime(getCurrentTime()) {}

Order::Order(int orderId, int customerId, int carId, const std::string& orderTime)
        : orderId(orderId), customerId(customerId), carId(carId), orderTime(orderTime) {}

int Order::getOrderId() {
    return orderId;
}
void Order::setOrderId(int orderId) {
    this->orderId = orderId;
}

int Order::getCustomerId() {
    return customerId;
}
void Order::setCustomerId(int customerId) {
    this->customerId = customerId;
}

int Order::getCarId() {
    return carId;
}

void Order::setCarId(int carId){
    this->carId = carId;
}

std::string Order::getOrderTime() {
    return orderTime;
}

void Order::setOrderTime(std::string orderTime) {
    this->orderTime = orderTime;
}

std::string Order::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::ctime(&currentTime);
    return ss.str();
}

void Order::printAllOrders(Database& db, int isLogged) {
    pqxx::result result = db.executeQuery("SELECT * FROM orders");

    std::cout << "All Orders:" << std::endl;
    for (auto row : result) {
        std::cout << "Order ID: " << row["order_id"].as<int>() << ", Customer ID: " << row["customer_id"].as<int>()
                  << ", Car ID: " << row["car_id"].as<int>() << ", Order Time: " << row["order_time"].as<std::string>() << std::endl;
    }
}
