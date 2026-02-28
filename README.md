# Electrical Load Monitoring System

A simple C++ console application that helps track household appliances and estimate electricity consumption and cost.

---

## Overview

This project allows users to:

- Register electrical appliances
- View all saved appliances
- Search for a specific appliance
- Calculate daily and monthly electricity cost
- Save appliance data to a file
- Save billing summaries with timestamps

It is designed as a basic file-handling and data management project using C++.

---

## Features

- Store appliance name, power rating (watts), and usage hours per day
- Automatically calculate energy usage in kWh/day
- Estimate electricity bill based on user-entered tariff
- Save and load data using text files
- Append billing history with date and time

---

## Files Used

- `appliances.txt` → Stores registered appliance data  
- `billing_summary.txt` → Stores saved billing calculations  

These files are created automatically if they do not exist.

---

## How It Works

Energy is calculated using:

```
Energy (kWh/day) = (Watts / 1000) × Hours used per day
```

Cost is calculated using:

```
Daily Cost = Total kWh × Tariff
Monthly Cost = Daily Cost × 30
```

---

## How to Compile and Run

### Using g++

```bash
g++ main.cpp -o load_monitor
./load_monitor
```

Make sure you have a C++ compiler installed (like MinGW or GCC).

---

## Menu Options

1. Register Appliance  
2. View Appliances  
3. Search Appliance  
4. Calculate Bill  
5. Save Appliances  
6. Exit  

The program automatically loads saved data when it starts.

---

## Example

If you enter:

- Appliance: Fan  
- Power: 75 watts  
- Hours per day: 8  

Energy used:

```
(75 / 1000) × 8 = 0.6 kWh/day
```

---

## Concepts Used

- Structures (`struct`)
- Vectors
- File handling (`ifstream`, `ofstream`)
- Loops
- Functions
- Time and date handling
- Basic formatting (`iomanip`)

---

## Author
Selassie

Student project for practicing C++ fundamentals and file handling.

---

## Notes

- Data is stored using `|` as a separator.
- Billing summary is appended, not overwritten.
- Always choose option 5 or exit properly to save data.

---

Simple, practical, and useful for learning core C++ concepts.