#include <string>

enum EngineType
{
    PETROL,
    DIESEL,
    HYBRID,
    ELECTRIC
};

class Transport{
private:
    std::string brand;
    std::string model;
    std::string color;
    EngineType engineType;

public:
    Transport(std::string brand, std::string model, std::string color, EngineType engineType) : brand(brand), model(model), color(color), engineType(engineType) {}
    ~Transport() {}

    std::string getBrand() { return brand; }
    void setBrand(std::string brand) { this->brand = brand; }

    std::string getModel() { return model; }
    void setModel(std::string model) { this->model = model; }

    std::string getColor() { return color; }
    void setColor(std::string color) { this->color = color; }

    EngineType getEngineType() { return engineType; }
    void setEngineType(EngineType engineType) { this->engineType = engineType; }
};

class PublicTransport : public Transport{
private:
    int capacity;
    std::string from;
    std::string to;
    std::string frequency;

public:
    PublicTransport(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency)
            : Transport(brand, model, color, engineType), capacity(capacity), from(from), to(to), frequency(frequency) {}
    ~PublicTransport() {}

    int getCapacity() { return capacity; }
    void setCapacity(int capacity) { this->capacity = capacity; }

    std::string getFrom() { return from; }
    void setFrom(std::string from) { this->from = from; }

    std::string getTo() { return to; }
    void setTo(std::string to) { this->to = to; }

    std::string getFrequency() { return frequency; }
    void setFrequency(std::string frequency) { this->frequency = frequency; }
};

class Bus : public PublicTransport{
private:
    bool hasContactlessPayment;

public:
    Bus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasContactlessPayment)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasContactlessPayment(hasContactlessPayment) {}

    bool getHasContactlessPayment() { return hasContactlessPayment; }
    void setHasContactlessPayment(bool hasContactlessPayment) { this->hasContactlessPayment = hasContactlessPayment; }
};

class TrolleyBus : public PublicTransport{
private:
    bool hasSockets;

public:
    TrolleyBus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasSockets)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasSockets(hasSockets) {}

    bool getHasSockets() { return hasSockets; }
    void setHasSockets(bool hasSockets) { this->hasSockets = hasSockets; }
};

enum RentCarTypes{
    ECONOMY,
    COMFORT,
    BUSINESS
};

class Taxi : public Transport{
private:
    double pricePerKil;
    double rating;
    bool hasDriver;
    bool hasWiFi;
    bool hasChildSeat;
    RentCarTypes rentCarTypes;

public:
    Taxi(std::string brand, std::string model, std::string color, EngineType engineType, double pricePerKil, double rating, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes)
            : Transport(brand, model, color, engineType), pricePerKil(pricePerKil), rating(rating), hasDriver(hasDriver), hasWiFi(hasWiFi), hasChildSeat(hasChildSeat), rentCarTypes(rentCarTypes) {}

    double getPricePerKil() { return pricePerKil; }
    void setPricePerKil(double pricePerKil) { this->pricePerKil = pricePerKil; }

    double getRating() { return rating; }
    void setRating(double rating) { this->rating = rating; }

    bool getHasDriver() { return hasDriver; }
    void setHasDriver(bool hasDriver) { this->hasDriver = hasDriver; }

    bool getHasWiFi() { return hasWiFi; }
    void setHasWiFi(bool hasWiFi) { this->hasWiFi = hasWiFi; }

    bool getHasChildSeat() { return hasChildSeat; }
    void setHasChildSeat(bool hasChildSeat) { this->hasChildSeat = hasChildSeat; }

    RentCarTypes getRentCarTypes() { return rentCarTypes; }
    void setRentCarTypes(RentCarTypes rentCarTypes) { this->rentCarTypes = rentCarTypes; }
};

class CarSharing : public Transport{
private:
    double pricePerMinute;
    bool hasInsurance;
    bool hasADS;

public:
    CarSharing(std::string brand, std::string model, std::string color, EngineType engineType, double pricePerMinute, bool hasInsurance, bool hasADS)
            : Transport(brand, model, color, engineType), pricePerMinute(pricePerMinute), hasInsurance(hasInsurance), hasADS(hasADS) {}

    double getPricePerMinute() { return pricePerMinute; }
    void setPricePerMinute(double pricePerMinute) { this->pricePerMinute = pricePerMinute; }

    bool getHasInsurance() { return hasInsurance; }
    void setHasInsurance(bool hasInsurance) { this->hasInsurance = hasInsurance; }

    bool getHasADS() { return hasADS; }
    void setHasADS(bool hasADS) { this->hasADS = hasADS; }
};
