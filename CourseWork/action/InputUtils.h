#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>
#include <iostream>
#include <numeric>

class InputUtils {
public:
    template <typename T>
    static T getPositiveInput(const std::string &prompt) {
        T value;
        std::string input;

        while (true) {
            std::cout << prompt;

            std::getline(std::cin, input);

            try {
                size_t pos = 0;
                value = std::stod(input, &pos);

                if (pos == input.length() && value > 0) {
                    break;
                } else {
                    std::cout << "Error: Input is not a positive number. Please try again." << std::endl;
                }
            } catch (std::invalid_argument&) {
                std::cout << "Error: Input is not a number. Please try again." << std::endl;
            } catch (std::out_of_range&) {
                std::cout << "Error: Input is too large. Please try again." << std::endl;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return value;
    }

    static std::string getStringInput(const std::string &prompt) {
        std::string input;

        while (true) {
            std::cout << prompt;

            std::getline(std::cin, input);

            if (!std::cin.fail()) {
                break;
            } else {
                std::cout << "Error: Input failed. Please try again." << std::endl;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return input;
    }
};

#endif // INPUT_UTILS_H
