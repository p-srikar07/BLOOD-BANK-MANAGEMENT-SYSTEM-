#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// ======================================================
// TEMPLATE FUNCTION
// Purpose: Displays a value of any basic data type
// ======================================================
template <class T>
void displayValue(T value)
{
    cout << value;
}


// ======================================================
// BASE CLASS : BloodBank
// Purpose: Stores donor details and blood stock
// ======================================================
class BloodBank
{
protected:

    static const int MAX_DONORS = 20;

    // Donor details
    string donorName[MAX_DONORS];
    int donorAge[MAX_DONORS];
    string donorGroup[MAX_DONORS];
    string donorPhone[MAX_DONORS];

    // Number of registered donors
    int donorCount;

    // Blood groups
    string bloodGroups[8];

    // Available blood units
    int bloodStock[8];


public:

    // ==================================================
    // CONSTRUCTOR
    // Purpose: Initializes blood groups and stock
    // ==================================================
    BloodBank()
    {
        donorCount = 0;

        bloodGroups[0] = "A+";
        bloodGroups[1] = "A-";
        bloodGroups[2] = "B+";
        bloodGroups[3] = "B-";
        bloodGroups[4] = "AB+";
        bloodGroups[5] = "AB-";
        bloodGroups[6] = "O+";
        bloodGroups[7] = "O-";

        // Initially all blood stock is zero
        for (int i = 0; i < 8; i++)
        {
            bloodStock[i] = 0;
        }

        // Load previously saved data
        loadData();
    }


    // ==================================================
    // FUNCTION: findBloodGroup
    // Purpose: Finds the position of a blood group
    // ==================================================
    int findBloodGroup(string group)
    {
        for (int i = 0; i < 8; i++)
        {
            if (bloodGroups[i] == group)
            {
                return i;
            }
        }

        return -1;
    }


    // ==================================================
    // DONOR MODULE
    // Purpose: Registers a new blood donor
    // ==================================================
    void addDonor()
    {
        if (donorCount >= MAX_DONORS)
        {
            cout << "\nDonor limit reached!\n";
            return;
        }

        cout << "\n========== ADD DONOR ==========\n";

        // Clear input buffer
        cin.ignore(1000, '\n');

        cout << "Enter Donor Name: ";
        getline(cin, donorName[donorCount]);

        if (donorName[donorCount].empty())
        {
            cout << "Name cannot be empty!\n";
            return;
        }

        // Get donor age
        cout << "Enter Age: ";

        if (!(cin >> donorAge[donorCount]))
        {
            cout << "Invalid age! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        // Basic age validation
        if (donorAge[donorCount] < 18)
        {
            cout << "Donor must be 18 or above.\n";
            return;
        }

        // Get blood group
        cout << "Enter Blood Group (A+ A- B+ B- AB+ AB- O+ O-): ";
        cin >> donorGroup[donorCount];

        int index = findBloodGroup(donorGroup[donorCount]);

        if (index == -1)
        {
            cout << "Invalid blood group!\n";
            return;
        }

        // Get phone number
        cout << "Enter Phone Number: ";
        cin >> donorPhone[donorCount];

        // Get donated units
        int units;

        cout << "Enter Blood Units Donated: ";

        if (!(cin >> units))
        {
            cout << "Invalid units! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        if (units <= 0)
        {
            cout << "Units must be greater than zero.\n";
            return;
        }

        // Add units to blood stock
        bloodStock[index] += units;

        // Increase donor count
        donorCount++;

        // Save updated information
        saveData();

        cout << "\nDonor added successfully!\n";
        cout << "Blood stock updated successfully!\n";
    }


    // ==================================================
    // DONOR MODULE
    // Purpose: Displays all donor records
    // ==================================================
    void displayDonors()
    {
        cout << "\n========== DONOR RECORDS ==========\n";

        if (donorCount == 0)
        {
            cout << "No donor records available.\n";
            return;
        }

        for (int i = 0; i < donorCount; i++)
        {
            cout << "\nDonor " << i + 1 << endl;

            cout << "Name        : "
                 << donorName[i] << endl;

            cout << "Age         : "
                 << donorAge[i] << endl;

            cout << "Blood Group : "
                 << donorGroup[i] << endl;

            cout << "Phone       : "
                 << donorPhone[i] << endl;
        }
    }


    // ==================================================
    // INVENTORY MODULE
    // Purpose: Adds blood units to existing stock
    // ==================================================
    void addBlood()
    {
        string group;
        int units;

        cout << "\n========== ADD BLOOD STOCK ==========\n";

        cout << "Enter Blood Group: ";
        cin >> group;

        int index = findBloodGroup(group);

        if (index == -1)
        {
            cout << "Invalid blood group!\n";
            return;
        }

        cout << "Enter Number of Units: ";

        if (!(cin >> units))
        {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        if (units <= 0)
        {
            cout << "Units must be greater than zero.\n";
            return;
        }

        // Update stock
        bloodStock[index] += units;

        // Save updated stock
        saveData();

        cout << "Blood stock updated successfully!\n";
    }


    // ==================================================
    // INVENTORY MODULE
    // Purpose: Displays current blood stock
    // ==================================================
    void displayStock()
    {
        cout << "\n========== BLOOD STOCK ==========\n";

        for (int i = 0; i < 8; i++)
        {
            cout << bloodGroups[i]
                 << " : "
                 << bloodStock[i]
                 << " units\n";
        }
    }


    // ==================================================
    // RECIPIENT MODULE
    // Purpose: Searches for required blood
    // ==================================================
    void searchBlood()
    {
        string group;

        cout << "\n========== SEARCH BLOOD ==========\n";

        cout << "Enter Required Blood Group: ";
        cin >> group;

        int index = findBloodGroup(group);

        if (index == -1)
        {
            cout << "Invalid blood group!\n";
            return;
        }

        if (bloodStock[index] > 0)
        {
            cout << "\nBlood Group: ";
            displayValue(group);

            cout << "\nAvailable Units: ";
            displayValue(bloodStock[index]);

            cout << endl;
        }
        else
        {
            cout << "Blood is currently unavailable.\n";
        }
    }


    // ==================================================
    // RECIPIENT MODULE
    // Purpose: Processes a blood request
    // ==================================================
    void requestBlood()
    {
        string group;
        int units;

        cout << "\n========== BLOOD REQUEST ==========\n";

        cout << "Enter Required Blood Group: ";
        cin >> group;

        int index = findBloodGroup(group);

        if (index == -1)
        {
            cout << "Invalid blood group!\n";
            return;
        }

        cout << "Enter Required Units: ";

        if (!(cin >> units))
        {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        if (units <= 0)
        {
            cout << "Units must be greater than zero.\n";
            return;
        }

        // Check whether enough blood is available
        if (bloodStock[index] >= units)
        {
            // Reduce requested units
            bloodStock[index] -= units;

            // Save updated stock
            saveData();

            cout << "\nBlood request processed successfully!\n";
            cout << "Remaining "
                 << group
                 << " Units: "
                 << bloodStock[index]
                 << endl;
        }
        else
        {
            cout << "\nInsufficient blood stock!\n";
            cout << "Available Units: "
                 << bloodStock[index]
                 << endl;
        }
    }


    // ==================================================
    // FILE HANDLING
    // Purpose: Saves donor details and blood stock
    // ==================================================
    void saveData()
    {
        // Save donor records
        ofstream donorFile("donors.txt");

        if (!donorFile)
        {
            cout << "Error: Cannot open donors.txt\n";
            return;
        }

        for (int i = 0; i < donorCount; i++)
        {
            donorFile << donorName[i] << endl;
            donorFile << donorAge[i] << endl;
            donorFile << donorGroup[i] << endl;
            donorFile << donorPhone[i] << endl;
        }

        donorFile.close();


        // Save blood stock
        ofstream stockFile("stock.txt");

        if (!stockFile)
        {
            cout << "Error: Cannot open stock.txt\n";
            return;
        }

        for (int i = 0; i < 8; i++)
        {
            stockFile << bloodGroups[i]
                      << " "
                      << bloodStock[i]
                      << endl;
        }

        stockFile.close();
    }


    // ==================================================
    // FILE HANDLING
    // Purpose: Loads previously saved information
    // ==================================================
    void loadData()
    {
        // Load donor records
        ifstream donorFile("donors.txt");

        if (donorFile)
        {
            while (donorCount < MAX_DONORS)
            {
                string tempName;
                int tempAge;
                string tempGroup;
                string tempPhone;

                if (!getline(donorFile, tempName))
                    break;

                if (!(donorFile >> tempAge))
                    break;

                donorFile.ignore(1000, '\n');

                if (!getline(donorFile, tempGroup))
                    break;

                if (!getline(donorFile, tempPhone))
                    break;

                // Validate saved data
                if (tempName.empty())
                    continue;

                if (tempAge < 18)
                    continue;

                if (findBloodGroup(tempGroup) == -1)
                    continue;

                donorName[donorCount] = tempName;
                donorAge[donorCount] = tempAge;
                donorGroup[donorCount] = tempGroup;
                donorPhone[donorCount] = tempPhone;

                donorCount++;
            }

            donorFile.close();
        }


        // Load blood stock
        ifstream stockFile("stock.txt");

        if (stockFile)
        {
            string group;
            int units;

            while (stockFile >> group >> units)
            {
                int index = findBloodGroup(group);

                if (index != -1 && units >= 0)
                {
                    bloodStock[index] = units;
                }
            }

            stockFile.close();
        }
    }
};


// ======================================================
// DERIVED CLASS : Admin
// Purpose: Demonstrates inheritance
// ======================================================
class Admin : public BloodBank
{
public:

    // Constructor
    Admin() : BloodBank()
    {
    }


    // ==================================================
    // ADMIN MODULE
    // Purpose: Allows admin to view system records
    // ==================================================
    void adminMenu()
    {
        int choice;

        do
        {
            cout << "\n========== ADMIN MODULE ==========\n";

            cout << "1. View Donors\n";
            cout << "2. View Blood Stock\n";
            cout << "3. Back\n";

            cout << "Enter Choice: ";

            if (!(cin >> choice))
            {
                cout << "Invalid input! Enter a number.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch (choice)
            {
                case 1:
                    displayDonors();
                    break;

                case 2:
                    displayStock();
                    break;

                case 3:
                    cout << "Returning to Main Menu...\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }

        } while (choice != 3);
    }
};


// ======================================================
// DONOR MENU
// Purpose: Controls donor operations
// ======================================================
void donorMenu(Admin &bank)
{
    int choice;

    do
    {
        cout << "\n========== DONOR MODULE ==========\n";

        cout << "1. Add Donor\n";
        cout << "2. Display Donors\n";
        cout << "3. Back\n";

        cout << "Enter Choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                bank.addDonor();
                break;

            case 2:
                bank.displayDonors();
                break;

            case 3:
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);
}


// ======================================================
// INVENTORY MENU
// Purpose: Controls inventory operations
// ======================================================
void inventoryMenu(Admin &bank)
{
    int choice;

    do
    {
        cout << "\n========== INVENTORY MODULE ==========\n";

        cout << "1. Add Blood Units\n";
        cout << "2. Display Blood Stock\n";
        cout << "3. Back\n";

        cout << "Enter Choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                bank.addBlood();
                break;

            case 2:
                bank.displayStock();
                break;

            case 3:
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);
}


// ======================================================
// RECIPIENT MENU
// Purpose: Controls recipient operations
// ======================================================
void recipientMenu(Admin &bank)
{
    int choice;

    do
    {
        cout << "\n========== RECIPIENT MODULE ==========\n";

        cout << "1. Search Blood\n";
        cout << "2. Request Blood\n";
        cout << "3. Back\n";

        cout << "Enter Choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                bank.searchBlood();
                break;

            case 2:
                bank.requestBlood();
                break;

            case 3:
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);
}


// ======================================================
// MAIN FUNCTION
// Purpose: Controls the complete system
// ======================================================
int main()
{
    // Create Admin object
    Admin bank;

    int choice;

    do
    {
        cout << "\n\n========================================\n";
        cout << "       BLOOD BANK MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Donor Module\n";
        cout << "2. Inventory Module\n";
        cout << "3. Recipient Module\n";
        cout << "4. Admin Module\n";
        cout << "5. Exit\n";

        cout << "\nEnter Choice: ";

        // Handle invalid input
        if (!(cin >> choice))
        {
            cout << "Invalid input! Please enter a number.\n";

            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

        // Main menu
        switch (choice)
        {
            case 1:
                donorMenu(bank);
                break;

            case 2:
                inventoryMenu(bank);
                break;

            case 3:
                recipientMenu(bank);
                break;

            case 4:
                bank.adminMenu();
                break;

            case 5:
                cout << "\nThank you for using Blood Bank Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
