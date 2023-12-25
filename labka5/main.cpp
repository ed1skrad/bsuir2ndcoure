#include <fstream>
#include <iostream>
#include "ElectronicWatch.h"
#include "Stack.h"
#include "File.h"

int main() {
    Stack<ElectronicWatch> stack;
    ElectronicWatch* watch1 = new ElectronicWatch("watch1", 30, 1000, 50, 100, 10);
    ElectronicWatch* watch2 = new ElectronicWatch("watch2", 10, 2000, 75, 100, 20);

    stack.push(watch1);
    stack.push(watch2);

    File file("file.bin");
    file.writeBinary("file.bin", stack);
    Stack<ElectronicWatch> first;

    file.readBinary("file.bin", first);

    std::cout << "BINARY" << std::endl;
    first.print();

    File file_1("file.txt");
    file_1.writeText("file.txt", first);
    Stack<ElectronicWatch> third;

    file_1.readText("file.txt", third);
    std::cout << "TEXT" << std::endl;
    third.print();
    std::cout << third.peek().getBatteryCharge() << std::endl;
    std::cout << third.peek().getMaxCharge() << std::endl;
    std::cout << third.peek().getScreenBrightness() << std::endl;

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}

