#include "mylibrary.h"
#include <iostream>
#include <iomanip>
#include <fstream> // For file handling

// Admin menu
void adminMenu(vector<Slot>& slots, double& hourlyPrice) {
    int option;
    cout << "\n--- Administrator Menu ---\n";
    cout << "1. Configure Slots and Parking Price\n";
    cout << "2. Generate Daily/Weekly Report\n";
    cout << "3. Go Back\n";
    cout << "Enter your choice: ";
    cin >> option;

    if (option == 1) {
        int numSlots;
        cout << "Enter the number of parking slots: ";
        cin >> numSlots;
        slots.resize(numSlots); // Adjust the size of the slots vector
        for (int i = 0; i < numSlots; ++i) {
            slots[i] = { i + 1, false, "", 0 }; // Initialize each slot
        }
        cout << "Parking slots successfully configured.\n";

        cout << "Enter the hourly parking price: ";
        cin >> hourlyPrice;
        cout << "Price set to: " << hourlyPrice << " USD/hour.\n";
    }
    else if (option == 2) {
        generateReport(slots, hourlyPrice);
        char saveToFile;
        cout << "Do you want to save this report to a file? (y/n): ";
        cin >> saveToFile;
        if (saveToFile == 'y' || saveToFile == 'Y') {
            writeReportToFile(slots, hourlyPrice);
        }
    }
    else if (option == 3) {
        return; // Go back to the main menu
    }
    else {
        cout << "Invalid choice! Please try again.\n";
    }
}

// User menu
void userMenu(vector<Slot>& slots, double hourlyPrice) {
    int option;
    cout << "\n--- User Menu ---\n";
    cout << "1. Park Vehicle\n";
    cout << "2. Exit Vehicle\n";
    cout << "3. View Parking Slot Status\n";
    cout << "4. Go Back\n";
    cout << "Enter your choice: ";
    cin >> option;

    if (option == 1) {
        // Find the first available slot
        for (Slot& slot : slots) {
            if (!slot.isOccupied) {
                cout << "Enter vehicle number: ";
                cin >> slot.vehicleNumber;
                slot.isOccupied = true;
                slot.entryTime = time(nullptr); // Record entry time
                cout << "Vehicle parked at slot " << slot.id << ".\n";
                return;
            }
        }
        cout << "All parking slots are occupied!\n";
    }
    else if (option == 2) {
        string vehicleNumber;
        cout << "Enter vehicle number: ";
        cin >> vehicleNumber;

        // Search for the vehicle by its number
        for (Slot& slot : slots) {
            if (slot.isOccupied && slot.vehicleNumber == vehicleNumber) {
                time_t currentTime = time(nullptr);
                double duration = difftime(currentTime, slot.entryTime) / 3600.0; // Calculate duration in hours
                double charge = duration * hourlyPrice;

                slot.isOccupied = false; // Free up the slot
                slot.vehicleNumber = "";
                slot.entryTime = 0;

                cout << "Vehicle exited.\n";
                cout << "Duration: " << fixed << setprecision(2) << duration << " hours\n";
                cout << "Total charge: " << fixed << setprecision(2) << charge << " USD\n";
                return;
            }
        }
        cout << "Vehicle not found!\n";
    }
    else if (option == 3) {
        displaySlots(slots);
    }
    else if (option == 4) {
        return; // Go back to the main menu
    }
    else {
        cout << "Invalid choice! Please try again.\n";
    }
}

// Generate a report
void generateReport(const vector<Slot>& slots, double hourlyPrice) {
    int occupiedSlots = 0;
    double totalRevenue = 0.0;

    // Calculate total revenue and occupied slots
    for (const Slot& slot : slots) {
        if (slot.isOccupied) {
            time_t currentTime = time(nullptr);
            double duration = difftime(currentTime, slot.entryTime) / 3600.0;
            totalRevenue += duration * hourlyPrice;
            ++occupiedSlots;
        }
    }

    // Display the report
    cout << "\n--- Report ---\n";
    cout << "Total Slots: " << slots.size() << "\n";
    cout << "Occupied Slots: " << occupiedSlots << "\n";
    cout << "Revenue: " << totalRevenue << " USD\n";
}

// Display the status of all parking slots
void displaySlots(const vector<Slot>& slots) {
    cout << "\n--- Parking Slot Status ---\n";
    for (const Slot& slot : slots) {
        cout << "Slot " << slot.id << ": ";
        if (slot.isOccupied)
            cout << "OCCUPIED (Vehicle: " + slot.vehicleNumber + ")" << "\n";
        else
            cout << "AVAILABLE" << "\n";
    }
}

// Writes the report to a file
void writeReportToFile(const vector<Slot>& slots, double rate) {
    ofstream reportFile("parking_report.txt");
    if (!reportFile) {
        cerr << "Error opening file to write report.\n";
        return;
    }

    reportFile << "--- Parking Report ---\n";
    reportFile << "Total Slots: " << slots.size() << "\n";

    int occupiedSlots = 0;
    double totalRevenue = 0.0;

    // Calculate revenue and occupied slots
    for (const Slot& slot : slots) {
        if (slot.isOccupied) {
            time_t currentTime = time(nullptr);
            double duration = difftime(currentTime, slot.entryTime) / 3600.0;
            totalRevenue += duration * rate;
            ++occupiedSlots;
        }
    }

    reportFile << "Occupied Slots: " << occupiedSlots << "\n";
    reportFile << "Revenue: " << totalRevenue << " USD\n";

    reportFile.close(); // Close the file
    cout << "Report successfully written to parking_report.txt.\n";
}
#include <ctime>

// Generates a daily report based on current date
void generateDailyReport(const vector<Slot>& slots, double rate) {
    // Get the current date
    time_t now = time(nullptr);
    tm* currentTime = localtime(&now);
    int currentDay = currentTime->tm_mday;
    int currentMonth = currentTime->tm_mon;
    int currentYear = currentTime->tm_year;

    int occupiedSlots = 0;
    double totalRevenue = 0.0;

    // Calculate daily revenue and occupied slots
    for (const Slot& slot : slots) {
        if (slot.isOccupied) {
            // Check if the vehicle was parked today
            tm* entryTime = localtime(&slot.entryTime);
            if (entryTime->tm_mday == currentDay &&
                entryTime->tm_mon == currentMonth &&
                entryTime->tm_year == currentYear) {

                time_t currentTime = time(nullptr);
                double duration = difftime(currentTime, slot.entryTime) / 3600.0; // Hours
                totalRevenue += duration * rate;
                ++occupiedSlots;
            }
        }
    }

    // Print the report
    cout << "\n--- Daily Report ---\n";
    cout << "Date: " << (currentMonth + 1) << "/" << currentDay << "/" << (1900 + currentYear) << "\n";
    cout << "Total Slots: " << slots.size() << "\n";
    cout << "Occupied Slots Today: " << occupiedSlots << "\n";
    cout << "Revenue Today: " << fixed << setprecision(2) << totalRevenue << " USD\n";

    // Save the report to a file
    ofstream reportFile("daily_report.txt");
    if (reportFile) {
        reportFile << "--- Daily Report ---\n";
        reportFile << "Date: " << (currentMonth + 1) << "/" << currentDay << "/" << (1900 + currentYear) << "\n";
        reportFile << "Total Slots: " << slots.size() << "\n";
        reportFile << "Occupied Slots Today: " << occupiedSlots << "\n";
        reportFile << "Revenue Today: " << totalRevenue << " USD\n";
        reportFile.close();
        cout << "Daily report saved to daily_report.txt.\n";
    }
    else {
        cerr << "Error: Could not write to daily_report.txt.\n";
    }
}
