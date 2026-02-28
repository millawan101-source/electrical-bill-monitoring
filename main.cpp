#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

struct Appliance
{
    string name;
    double watts;
    double hours;
};

vector<Appliance> applianceList;
string dataFile = "appliances.txt";


// ================= LOAD DATA =================
void loadData()
{
    ifstream inFile(dataFile);

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


// ================= SAVE DATA =================
void saveData()
{
    ofstream outFile(dataFile);

    for (size_t i = 0; i < applianceList.size(); i++)
    {
        outFile << applianceList[i].name << "|"
                << applianceList[i].watts << "|"
                << applianceList[i].hours << endl;
    }

    outFile.close();
    cout << "Appliances saved successfully.\n";
}


// ================= ADD APPLIANCE =================
void addAppliance()
{
    Appliance item;

    cout << "Enter appliance name: ";
    getline(cin, item.name);

    cout << "Enter power (watts): ";
    cin >> item.watts;

    cout << "Enter hours used per day: ";
    cin >> item.hours;
    cin.ignore();

    applianceList.push_back(item);

    cout << "Appliance added successfully.\n";
}


// ================= DISPLAY APPLIANCES =================
void displayAppliances()
{
    if (applianceList.empty())
    {
        cout << "No appliances registered.\n";
        return;
    }

    cout << fixed << setprecision(2);

    cout << "\nNo  Name                Watts   Hours   kWh/day\n";
    cout << "------------------------------------------------\n";

    for (size_t i = 0; i < applianceList.size(); i++)
    {
        double energy = (applianceList[i].watts / 1000) * applianceList[i].hours;

        cout << i + 1 << ". "
             << setw(18) << left << applianceList[i].name
             << setw(8) << applianceList[i].watts
             << setw(8) << applianceList[i].hours
             << energy << endl;
    }
}


// ================= SEARCH =================
void searchItem()
{
    string key;
    bool found = false;

    cout << "Enter appliance name to search: ";
    getline(cin, key);

    for (size_t i = 0; i < applianceList.size(); i++)
    {
        if (applianceList[i].name.find(key) != string::npos)
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


// ================= BILL CALCULATION =================
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
    cin.ignore();

    double totalEnergy = 0;

    cout << fixed << setprecision(2);
    cout << "\nAppliance Breakdown\n";
    cout << "-----------------------------\n";

    for (size_t i = 0; i < applianceList.size(); i++)
    {
        double energy = (applianceList[i].watts / 1000) * applianceList[i].hours;
        totalEnergy += energy;

        cout << applianceList[i].name
             << " - " << energy << " kWh/day\n";
    }

    double dailyCost = totalEnergy * tariff;
    double monthlyCost = dailyCost * 30;

    cout << "\nTotal Daily Energy: " << totalEnergy << " kWh\n";
    cout << "Daily Cost: " << dailyCost << endl;
    cout << "Estimated Monthly Cost (30 days): " << monthlyCost << endl;

    char saveChoice;
    cout << "\nSave billing summary? (y/n): ";
    cin >> saveChoice;
    cin.ignore();

    if (saveChoice == 'y' || saveChoice == 'Y')
    {
        ofstream outFile("billing_summary.txt", ios::app);

        if (!outFile)
        {
            cout << "Error saving file.\n";
            return;
        }

        time_t now = time(0);
        char* dateTime = ctime(&now);

        outFile << "\n=====================================\n";
        outFile << "Billing Summary - " << dateTime;
        outFile << "-------------------------------------\n";

        for (size_t i = 0; i < applianceList.size(); i++)
        {
            double energy = (applianceList[i].watts / 1000) * applianceList[i].hours;
            outFile << applianceList[i].name
                    << " - " << energy << " kWh/day\n";
        }

        outFile << "\nTotal Daily Energy: " << totalEnergy << " kWh\n";
        outFile << "Daily Cost: " << dailyCost << endl;
        outFile << "Estimated Monthly Cost (30 days): " << monthlyCost << endl;
        outFile << "=====================================\n";

        outFile.close();

        cout << "Billing summary saved successfully.\n";
    }
}


// ================= MENU =================
void menu()
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


// ================= MAIN =================
int main()
{
    loadData();

    int option;

    while (true)
    {
        menu();
        cin >> option;
        cin.ignore();

        if (option == 1)
            addAppliance();
        else if (option == 2)
            displayAppliances();
        else if (option == 3)
            searchItem();
        else if (option == 4)
            calculateBill();
        else if (option == 5)
            saveData();
        else if (option == 6)
        {
            saveData();
            cout << "Goodbye!\n";
            break;
        }
        else
            cout << "Invalid choice.\n";
    }

    return 0;
}