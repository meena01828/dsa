#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const char* FILENAME = "employee.txt";

// Helper function to split a line into fields
void parseRecord(const string& line, string& id, string& name, string& desig, string& salary) {
    int pos1 = line.find('|');
    int pos2 = line.find('|', pos1 + 1);
    int pos3 = line.find('|', pos2 + 1);
    int pos4 = line.find('|', pos3 + 1);

    id = line.substr(0, pos1);
    name = line.substr(pos1 + 1, pos2 - pos1 - 1);
    desig = line.substr(pos2 + 1, pos3 - pos2 - 1);
    salary = line.substr(pos3 + 1, pos4 - pos3 - 1);
}

void addEmployee() {
    ofstream outFile(FILENAME, ios::app);
    if (!outFile) {
        cout << "Error opening file.\n";
        return;
    }

    string id, name, desig, salary;
    cout << "Enter Employee ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Designation: ";
    getline(cin, desig);
    cout << "Enter Salary: ";
    cin >> salary;

    outFile << id << "|" << name << "|" << desig << "|" << salary << "|\n";
    outFile.close();

    cout << "Employee added successfully.\n";
}

void displayAllEmployees() {
    ifstream inFile(FILENAME);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }

    string line, id, name, desig, salary;
    cout << "\n--- All Employee Records ---\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(20) << "Designation"
         << setw(10) << "Salary" << endl;
    cout << "------------------------------------------------------------\n";

    while (getline(inFile, line)) {
        if (line.empty() || line[0] == '*') continue;
        parseRecord(line, id, name, desig, salary);
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(20) << desig
             << setw(10) << salary << endl;
    }

    inFile.close();
}

void searchEmployee() {
    ifstream inFile(FILENAME);
    if (!inFile) {
        cout << "Error opening file.\n";
        return;
    }

    string searchID;
    cout << "Enter Employee ID to search: ";
    cin >> searchID;

    string line, id, name, desig, salary;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty() || line[0] == '*') continue;
        parseRecord(line, id, name, desig, salary);

        if (id == searchID) {
            cout << "\nEmployee Found:\n";
            cout << "ID: " << id << "\nName: " << name
                 << "\nDesignation: " << desig << "\nSalary: " << salary << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found.\n";
    }

    inFile.close();
}

void deleteEmployee() {
    string deleteID;
    cout << "Enter Employee ID to delete: ";
    cin >> deleteID;

    fstream file(FILENAME, ios::in | ios::out);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    string line, id, name, desig, salary;
    long pos = 0;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '*') {
            pos = file.tellg();
            continue;
        }

        parseRecord(line, id, name, desig, salary);
        if (id == deleteID) {
            file.seekp(pos);
            file.put('*');  // mark line as deleted
            found = true;
            cout << "Employee with ID " << deleteID << " deleted.\n";
            break;
        }
        pos = file.tellg();
    }

    if (!found) {
        cout << "Employee not found.\n";
    }

    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n----- Employee Management System -----\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee by ID\n";
        cout << "3. Search Employee by ID\n";
        cout << "4. Display All Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: deleteEmployee(); break;
            case 3: searchEmployee(); break;
            case 4: displayAllEmployees(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

