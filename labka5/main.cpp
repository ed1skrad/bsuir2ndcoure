#include <iostream>
#include <numeric>
#include "Watch.h"
#include "Clock.h"
#include "FitnessTracker.h"
#include "WallClock.h"
#include <chrono>
#include "Stack.h"
#include "File.h"

using namespace std;

template <typename T>
T getPositiveIntegerInput(const std::string &prompt) {
    T value;
    while (true) {
        try {
            std::cout << prompt;
            std::cin >> value;

            if (std::cin.fail() || value <= 0) {
                throw InputValidationException();
            } else {
                return value;
            }
        } catch (const InputValidationException& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            e.show();
        }
    }
}

int getLabNumber(int value) {
    while (true) {
        try {
            std::cout << "Enter lab number: 1 - Classes | 2 - Stack\n";
            std::cin >> value;

            if (std::cin.fail() || value <= 0 || value > 2) {
                throw InputValidationException();
            } else {
                return value;
            }
        } catch (const InputValidationException& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            e.show();
        }
    }
}

int main() {
    int choice = getLabNumber(choice);
    try {
        int choice;
        cout << "Select the type of watch you want to create:\n";
        cout << "1. WallClock\n";
        cout << "2. Watch\n";
        cout << "3. FitnessTracker\n";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You entered an invalid value. Please try again.\n";
            return 0;
        }

        switch (choice) {
            case 1: {
                Stack<WallClock> stack;
                File textFile("wallClocks.txt");
                textFile.open();
                stack.push(textFile);

                File binaryFile("wallClocks.dat");
                binaryFile.open();
                Stack.push(binaryFile);

                char brand[50];
                int weight;
                int price;
                char bodyMaterial[50];
                int numberOfGears;
                char glassType[50];
                bool pendulum;
                char fasteningMaterial[50];

                cout << "Enter brand: ";
                cin.ignore();
                cin.getline(brand, 50);

                try {
                    std::cout << "Enter weight: ";
                    std::cin >> weight;
                    if (weight <= 0) {
                        throw NegativeWeightException();
                    }
                } catch (const NegativeWeightException &e) {
                    e.show();
                }

                try {
                    std::cout << "Enter price: ";
                    std::cin >> price;
                    if (price <= 0) {
                        throw NegativePriceException();
                    }
                } catch (const NegativePriceException &e) {
                    e.show();
                }

                cout << "Enter the body material: ";
                cin.ignore();
                cin.getline(bodyMaterial, 50);

                numberOfGears = getPositiveIntegerInput<int>("Enter the number of gears: ");

                cout << "Enter the type of glass: ";
                cin.ignore();
                cin.getline(glassType, 50);

                pendulum = getPositiveIntegerInput<int>("Is there a pendulum (1 - yes, 0 - no): ");
                if (pendulum != 0 && pendulum != 1) {
                    cout << "Invalid input. Please enter 1 for 'yes' or 0 for 'no' pendulum.\n";
                    return 0;
                }

                cout << "Enter the mounting material: ";
                cin.ignore();
                cin.getline(fasteningMaterial, 50);

                WallClock wallClock(brand, weight, price, bodyMaterial, numberOfGears, glassType, pendulum,
                                    fasteningMaterial);
                cout << "A WallClock has been created with brand " << wallClock.getBrand()
                     << ", weight " << wallClock.getWeight()
                     << ", price " << wallClock.getPrice()
                     << ", body material: " << wallClock.getBodyMaterial()
                     << ", number of gears: " << wallClock.getNumberOfGears()
                     << ", glass type: " << wallClock.getGlassType()
                     << ", pendulum: " << (wallClock.getPendulum() ? "yes" : "no")
                     << ", fastening material: " << wallClock.getFasteningMaterial()
                     << ".\n";
                auto currentTime = std::chrono::system_clock::now();
                std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
                cout << "Current time: " << std::ctime(&time) << endl;
                break;
            }
            case 2: {

                char brand[50];
                int weight;
                int price;
                char bodyMaterial[50];
                int numberOfGears;
                char glassType[50];
                bool selfWinding;
                int strapDiameter;

                cout << "Enter brand: ";
                cin.ignore();
                cin.getline(brand, 50);

                weight = getPositiveIntegerInput<int>("Enter weight: ");
                price = getPositiveIntegerInput<int>("Enter price: ");

                cout << "Enter the body material: ";
                cin.ignore();
                cin.getline(bodyMaterial, 50);

                numberOfGears = getPositiveIntegerInput<int>("Enter the number of gears: ");

                cout << "Enter the type of glass: ";
                cin.ignore();
                cin.getline(glassType, 50);

                selfWinding = getPositiveIntegerInput<int>("Is there automatic winding (1 - yes, 0 - no): ");
                if (selfWinding != 0 && selfWinding != 1) {
                    cout << "Invalid input. Please enter 1 for 'yes' or 0 for 'no' for automatic winding.\n";
                    return 0;
                }
                strapDiameter = getPositiveIntegerInput<int>("Enter the strap diameter: ");

                Watch watch(brand, weight, price, bodyMaterial, numberOfGears, glassType, selfWinding,
                            strapDiameter);
                cout << "A Watch has been created with brand " << watch.getBrand()
                     << ", weight " << watch.getWeight()
                     << ", price " << watch.getPrice()
                     << ", body material: " << watch.getBodyMaterial()
                     << ", number of gears: " << watch.getNumberOfGears()
                     << ", glass type: " << watch.getGlassType()
                     << ", self winding: " << (watch.getSelfWinding() ? "yes" : "no")
                     << ", strap diameter: " << watch.getStrapDiameter()
                     << ".\n";
                auto currentTime = std::chrono::system_clock::now();
                std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
                cout << "Current time: " << std::ctime(&time) << endl;
                break;
            }
            case 3: {
                char brand[50];
                int weight;
                int price;
                int batteryCharge;
                int maxCharge;
                int screenBrightness;
                int distance;
                bool heartRateMonitor;

                cout << "Enter brand: ";
                cin.ignore();
                cin.getline(brand, 50);

                weight = getPositiveIntegerInput<int>("Enter weight: ");
                price = getPositiveIntegerInput<int>("Enter price: ");

                batteryCharge = getPositiveIntegerInput<int>("Enter the battery charge: ");
                maxCharge = getPositiveIntegerInput<int>("Enter the maximum battery charge: ");
                screenBrightness = getPositiveIntegerInput<int>("Enter screen brightness: ");
                distance = getPositiveIntegerInput<int>("Enter the distance: ");
                heartRateMonitor = getPositiveIntegerInput<int>(
                        "Is there a heart rate monitor (1 - yes, 0 - no): ");

                FitnessTracker fitnessTracker(brand, weight, price, batteryCharge, maxCharge, screenBrightness,
                                              distance, heartRateMonitor);
                cout << "A FitnessTracker has been created with brand " << fitnessTracker.getBrand()
                     << ", weight " << fitnessTracker.getWeight()
                     << ", price " << fitnessTracker.getPrice()
                     << ", battery charge: " << fitnessTracker.getBatteryCharge()
                     << ", max charge: " << fitnessTracker.getMaxCharge()
                     << ", screen brightness: " << fitnessTracker.getScreenBrightness()
                     << ", distance: " << fitnessTracker.getDistance()
                     << ", heart rate monitor: " << (fitnessTracker.getHeartRateMonitor() ? "yes" : "no")
                     << ".\n";

                auto currentTime = std::chrono::system_clock::now();
                std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
                cout << "Current time: " << std::ctime(&time) << endl;

                break;
            }
            default:
                cout << "Wrong choice. Please choose 1, 2, or 3.\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
