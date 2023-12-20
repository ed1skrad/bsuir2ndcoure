#include <fstream>
#include <iostream>
#include "ElectronicWatch.h"
#include "Stack.h"
#include "File.h"

template <typename T>
void objToFile(T& obj, const char* filename){
    std::ofstream outFile(filename, std::ios::binary); // открываем файл в бинарном режиме
    if (outFile.is_open()) {
        outFile << obj; // используем оператор для вывода объекта в файл
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}


void createWatches(ElectronicWatch& watch1, ElectronicWatch& watch2, ElectronicWatch& watch3) {
    watch1.setBrand("Apple");
    watch1.setWeight(30);
    watch1.setPrice(400);
    watch1.setBatteryCharge(85);
    watch1.setMaxCharge(100);
    watch1.setScreenBrightness(90);

    watch2.setBrand("Samsung");
    watch2.setWeight(35);
    watch2.setPrice(350);
    watch2.setBatteryCharge(80);
    watch2.setMaxCharge(90);
    watch2.setScreenBrightness(88);

    watch3.setBrand("Fitbit");
    watch3.setWeight(28);
    watch3.setPrice(150);
    watch3.setBatteryCharge(70);
    watch3.setMaxCharge(80);
    watch3.setScreenBrightness(85);
}



int main() {
    try {
        std::string outFlName = "C:\\Users\\Artem\\Desktop\\bsuir2ndcoure\\labka5\\call.bin";
        Stack<ElectronicWatch> watchStack;

        // Создаем часы и добавляем их в стек
        ElectronicWatch watch1, watch2, watch3;
        createWatches(watch1, watch2, watch3);
        watchStack.push(watch1);
        watchStack.push(watch2);
        watchStack.push(watch3);

        // Открываем файл и записываем стек в него
        File file(outFlName.c_str());
        file.open();
        std::cout << "Open";
        file.writeStackBin(watchStack);
        std::cout << "Write";

        watchStack = file.readStackBin<ElectronicWatch>();
        std::cout << "Read";

        // Проверяем, что стек не пустой и выводим данные
        if (!watchStack.isEmpty()) {
            while (!watchStack.isEmpty()) {
                ElectronicWatch watch = watchStack.pop();
                std::cout << "Brand: " << watch.getBrand() << ", Weight: " << watch.getWeight() << ", Price: " << watch.getPrice() << "...\n";
            }
        } else {
            std::cout << "Stack is empty." << std::endl;
        }

    } catch (const StackIncorrectSizeException& e) {
        std::cerr << "Incorrect stack size: " << std::endl;
        return EXIT_FAILURE;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
