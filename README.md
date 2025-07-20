#  Parking Management System

A simple C++ based console application for managing a parking lot system. It supports both administrative and user functionalities including slot configuration, vehicle parking, billing, and report generation.

## 📁 Project Structure

```
.
├── main.cpp          # Entry point of the application
├── mylibrary.h       # Header file with structure and function declarations
├── mylibrary.cpp     # Function definitions for all system features
```

## 🛠️ Features

- **Admin Mode:**
  - Configure total parking slots
  - Set hourly parking price
  - Generate daily/weekly reports
  - Save reports to a file

- **User Mode:**
  - Park vehicle (assign to an available slot)
  - Exit vehicle (calculate parking fee)
  - View parking slot status

- **Report Generation:**
  - Daily revenue report (`daily_report.txt`)
  - General parking status report (`parking_report.txt`)

## Requirements

- C++ compiler supporting C++11 or newer

##  How to Compile and Run

```bash
g++ main.cpp mylibrary.cpp -o parking_app
./parking_app
```

##  Data Structures

- `Slot` struct:
  ```cpp
  struct Slot {
      int id;
      bool isOccupied;
      string vehicleNumber;
      time_t entryTime;
  };
  ```

## 📄 Output Files

- `daily_report.txt`: Daily summary of parking occupancy and revenue
- `parking_report.txt`: General summary (can be triggered by admin)
