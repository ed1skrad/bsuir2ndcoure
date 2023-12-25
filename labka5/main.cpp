#include <fstream>
#include <iostream>
#include <string>
#include "ElectronicWatch.h"
#include "Stack.h"
#include "File.h"
#include "InputUtils.h"

void printMenu() {
    std::cout << "1. Add watch\n";
    std::cout << "2. Remove watch\n";
    std::cout << "3. Print watches\n";
    std::cout << "4. Save to binary file and remove from stack\n";
    std::cout << "5. Load from binary file and add to stack\n";
    std::cout << "6. Save to text file and remove from stack\n";
    std::cout << "7. Load from text file and add to stack\n";
    std::cout << "8. Exit\n";
}

int main() {
    Stack<ElectronicWatch> stack(10); // Изменено для соответствия вашей реализации стека
    Stack<ElectronicWatch> tempStack(10); // Изменено для соответствия вашей реализации стека
    int choice;
    std::string brand;
    int weight, price, batteryCharge, maxCharge, screenBrightness;
    File file("file.bin");
    File file_1("file.txt");

    do {
        printMenu();
        choice = InputUtils::getPositiveInput<int>("Enter your choice: ");

        switch (choice) {
            case 1:
                int numWatches;
                numWatches = InputUtils::getPositiveInput<int>("Enter the number of watches you want to create: ");
                for (int i = 0; i < numWatches; i++) {
                    brand = InputUtils::getStringInput("Enter watch brand for watch " + std::to_string(i+1) + ": ");
                    weight = InputUtils::getPositiveInput<int>("Enter weight for watch " + std::to_string(i+1) + ": ");
                    price = InputUtils::getPositiveInput<int>("Enter price for watch " + std::to_string(i+1) + ": ");
                    batteryCharge = InputUtils::getPositiveInput<int>("Enter battery charge for watch " + std::to_string(i+1) + ": ");
                    maxCharge = InputUtils::getPositiveInput<int>("Enter max charge for watch " + std::to_string(i+1) + ": ");
                    screenBrightness = InputUtils::getPositiveInput<int>("Enter screen brightness for watch " + std::to_string(i+1) + ": ");
                    stack.push(ElectronicWatch(brand.c_str(), weight, price, batteryCharge, maxCharge, screenBrightness));
                }
                break;

            case 2:
                stack.pop();
                break;
            case 3:
                stack.print();
                break;
            case 4:
                file.writeBinary("file.bin", stack);
                stack.pop();
                break;
            case 5:
                file.readBinary("file.bin", tempStack);
                while (!tempStack.isEmpty()) {
                    stack.push(tempStack.peek());
                    tempStack.pop();
                }
                std::cout << "Deserialized objects from binary file and added to stack:\n";
                stack.print();
                break;
            case 6:
                file_1.writeText("file.txt", stack);
                stack.pop();
                break;
            case 7:
                file_1.readText("file.txt", tempStack);
                while (!tempStack.isEmpty()) {
                    stack.push(tempStack.peek());
                    tempStack.pop();
                }
                std::cout << "Deserialized objects from text file and added to stack:\n";
                stack.print();
                break;
            case 8:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
