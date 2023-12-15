#include "action/MainMenu.h"
#include "action/InputUtils.h"

int main() {
    Database Db;
    bool isRunning = true;
    while (isRunning) {
        displayMenu();
        int actionChoice = InputUtils::getPositiveInput<int>("");
        switch (actionChoice) {
            case 1:
                handleTaxiSelect(Db);
                break;
            case 2:
                handleBusSelect(Db);
                break;
            case 3:
                handleTrolleyBusSelect(Db);
                break;
            case 4:
                handleAdminActions(Db);
                break;
            case 0:
                isRunning = false;
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid option selected. Please try again." << std::endl;
                break;
        }
    }
    return 0;
}


