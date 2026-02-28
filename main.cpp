#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

struct Appliance
{
    string name;
    double watts;
    double hours;
};

vector<Appliance> applianceList;
string fileName = "appliances.txt";


// ================= LOAD FROM FILE =================
void loadAppliances()
{
    ifstream inFile(fileName);

    if (!inFile)
        return;

    Appliance item;

    while (getline(inFile, item.name, '|'))
    {
        inFile >> item.watts;
        inFile.ignore();
        inFile >> item.hours;
        inFile.ignore();

        applianceList.push_back(item);
    }

    inFile.close();
}


// ================= MENU =================
void showMenu()
{
    cout << "\n===== Electrical Load Monitoring System =====\n";
    cout << "1. Register Appliance\n";
    cout << "2. View Appliances\n";
    cout << "3. Search Appliance\n";
    cout << "4. Calculate Bill\n";
    cout << "5. Save Appliances\n";
    cout << "6. Exit\n";
    cout << "Choose option: ";
}


// ================= REGISTER =================
void addAppliance()
{
    Appliance item;

    cin.ignore();
    cout << "Enter appliance name: ";
    getline(cin, item.name);

    cout << "Enter power (watts): ";
    cin >> item.watts;

    cout << "Enter hours used per day: ";
    cin >> item.hours;

    applianceList.push_back(item);

    cout << "Appliance added successfully.\n";
}


// ================= VIEW =================
void displayAppliances()
{
    if (applianceList.empty())
    {
        cout << "No appliances registered.\n";
        return;
    }

    cout << fixed << setprecision(2);

    for (int i = 0; i < applianceList.size(); i++)
    {
        double energy = (applianceList[i].watts / 1000) * applianceList[i].hours;

        cout << applianceList[i].name << " | "
             << applianceList[i].watts << "W | "
             << applianceList[i].hours << " hrs | "
             << energy << " kWh/day\n";
    }
}


// ================= SEARCH =================
void searchAppliance()
{
    if (applianceList.empty())
    {
        cout << "No appliances available.\n";
        return;
    }

    cin.ignore();
    string keyword;
    cout << "Enter appliance name to search: ";
    getline(cin, keyword);

    bool found = false;

    for (int i = 0; i < applianceList.size(); i++)
    {
        if (applianceList[i].name.find(keyword) != string::npos)
        {
            double energy = (applianceList[i].watts / 1000) * applianceList[i].hours;

            cout << applianceList[i].name << " | "
                 << applianceList[i].watts << "W | "
                 << applianceList[i].hours << " hrs | "
                 << energy << " kWh/day\n";

            found = true;
        }
    }

    if (!found)
        cout << "Appliance not found.\n";
}


// ================= CALCULATE BILL =================
void calculateBill()
{
    if (applianceList.empty())
    {
        cout << "No appliances available.\n";
        return;
    }

    double tariff;
    cout << "Enter tariff per kWh: ";
    cin >> tariff;

    double totalEnergy = 0;

    for (int i = 0; i < applianceList.size(); i++)
    {
        double energy = (applianceList[i].watts / 1000) * applianceList[i].hours;
        totalEnergy += energy;
    }

    double dailyCost = totalEnergy * tariff;
    double monthlyCost = dailyCost * 30;

    cout << fixed << setprecision(2);

    cout << "\nTotal Daily Energy: " << totalEnergy << " kWh\n";
    cout << "Daily Cost: " << dailyCost << endl;
    cout << "Estimated Monthly Cost (30 days): " << monthlyCost << endl;

    char choice;
    cout << "\nSave billing summary? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        ofstream outFile("billing_summary.txt", ios::app);

        time_t now = time(0);
        char* dateTime = ctime(&now);

        outFile << "\n==============================\n";
        outFile << "Billing Summary - " << dateTime;
        outFile << "------------------------------\n";

        for (int i = 0; i < applianceList.size(); i++)
        {
            double energy = (applianceList[i].watts / 1000) * applianceList[i].hours;
            outFile << applianceList[i].name
                    << " - " << energy << " kWh/day\n";
        }

        outFile << "\nTotal Daily Energy: " << totalEnergy << " kWh\n";
        outFile << "Daily Cost: " << dailyCost << endl;
        outFile << "Estimated Monthly Cost (30 days): " << monthlyCost << endl;
        outFile << "==============================\n";

        outFile.close();

        cout << "Billing summary saved successfully.\n";
    }
}


// ================= SAVE TO FILE =================
void saveAppliances()
{
    ofstream outFile(fileName);

    for (int i = 0; i < applianceList.size(); i++)
    {
        outFile << applianceList[i].name << "|"
                << applianceList[i].watts << "|"
                << applianceList[i].hours << endl;
    }

    outFile.close();
    cout << "Appliances saved successfully.\n";
}


// ================= MAIN =================
int main()
{
    loadAppliances();

    int choice;

    while (true)
    {
        showMenu();
        cin >> choice;

        if (choice == 1)
            addAppliance();
        else if (choice == 2)
            displayAppliances();
        else if (choice == 3)
            searchAppliance();
        else if (choice == 4)
            calculateBill();
        else if (choice == 5)
            saveAppliances();
        else if (choice == 6)
        {
            saveAppliances();
            cout << "Goodbye!\n";
            break;
        }
        else
            cout << "Invalid choice.\n";
    }

    return 0;
}
