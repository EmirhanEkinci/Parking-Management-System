#include "mylibrary.h"
#include <iostream>
#include <vector>

int main() {
    vector<Slot> slots;        // List of parking slots
    double hourlyPrice = 0.0;       // Hourly parking price

    int choice;
    do {
        // Main menu
        cout << "\n--- Parking Management System ---\n";
        cout << "1. Admin Mode\n";
        cout << "2. User Mode\n";
        cout << "3. Generate daily report\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user input for menu navigation
        switch (choice) {
        case 1:
            adminMenu(slots, hourlyPrice); // Call administrator menu
            break;
        case 2:
            userMenu(slots, hourlyPrice); // Call user menu
            break;
        case 3:
            generateDailyReport(slots, hourlyPrice);
            break;
        case 4:
            std::cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3); // Repeat until the user chooses to exit

    return 0;
}
