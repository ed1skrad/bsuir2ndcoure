#include <fstream>
#include <iostream>
#include "ElectronicWatch.h"
#include "Stack.h"
#include "File.h"

template <typename T>
void objToFile(T& obj, const char* filename){
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << obj;
        outFile.close();
    }
    else {
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
    std::string outFlName = "C:\\Users\\atema\\CLionProjects\\labka5\\allStack.bin";
    Stack<ElectronicWatch> watchStack;
    ElectronicWatch watch1, watch2, watch3;
    createWatches(watch1, watch2, watch3);
    File file(outFlName.c_str());
    file.open();
    file.writeStackBin(watchStack);  // Запись стека в бинарный файл

        watchStack = file.readStackBin<ElectronicWatch>();

        while (!watchStack.isEmpty()) {
            ElectronicWatch watch = watchStack.pop();
            // Используйте методы get для вывода информации
            std::cout << "Brand: " << watch.getBrand() << ", Weight: " << watch.getWeight() << ", Price: " << watch.getPrice() << "...\n";
        }
    return 0;
}
