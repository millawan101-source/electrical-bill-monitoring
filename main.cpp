#include <iostream>
#include <vector>

using namespace std;

struct Appliance
{
    string name;
    double watts;
    double hours;
};

vector<Appliance> applianceList;


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


// ================= MAIN =================
int main()
{
    int choice;

    while (true)
    {
        showMenu();
        cin >> choice;

        if (choice == 1)
        {
            addAppliance();
        }
        else if (choice == 6)
        {
            cout << "Goodbye!\n";
            break;
        }
        else
        {
            cout << "Feature not implemented yet.\n";
        }
    }

    return 0;
}
