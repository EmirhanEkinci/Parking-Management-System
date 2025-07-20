#pragma once
#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Structure to represent a parking slot
struct Slot {
    int id;                  // Unique ID for the slot
    bool isOccupied;         // True if the slot is occupied
    string vehicleNumber;   // Vehicle number parked in the slot
    time_t entryTime;        // Entry time of the vehicle
};

// Function declarations
/**
 * Admin menu for managing parking slots and rates.
 * Precondition: Slots vector is initialized.
 * Postcondition: Slots are configured, and the parking rate is updated.
 */
void adminMenu(vector<Slot>& slots, double& rate);

/**
 * User menu for parking, exiting vehicles, and checking slot status.
 * Precondition: Slots vector is initialized, rate is set.
 * Postcondition: Slot states are updated based on user actions.
 */
void userMenu(vector<Slot>& slots, double rate);

/**
 * Generates a daily or weekly report on occupancy and revenue.
 * Precondition: Slots vector is initialized, rate is set.
 * Postcondition: Report is displayed to the console.
 */
void generateReport(const vector<Slot>& slots, double rate);

/**
 * Displays the current status of all parking slots.
 * Precondition: Slots vector is initialized.
 * Postcondition: No changes are made; status is shown on the console.
 */
void displaySlots(const vector<Slot>& slots);

/**
 * Writes the generated report to a file.
 * Precondition: Slots vector is initialized, rate is set.
 * Postcondition: A report file is created or updated with the current data.
 */
void writeReportToFile(const vector<Slot>& slots, double rate);

void generateDailyReport(const vector<Slot>& slots, double rate);
#endif
