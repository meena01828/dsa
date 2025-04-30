#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 10

struct employee {
    string name;
    long int employee_id;
    string designation;
    int salary;
};

int num = -1;
employee emp[MAX];

void insert() {
    if (num < MAX - 1) {
        num++;
        cout << "\nEnter the information of the Employee\n";
        cout << "Employee ID: ";
        cin >> emp[num].employee_id;
        cout << "Name: ";
        cin >> emp[num].name;
        cout << "Designation: ";
        cin >> emp[num].designation;
        cout << "Salary: ";
        cin >> emp[num].salary;
        cout << " Employee record added successfully.\n";
    } else {
        cout << "Employee Table is Full.\n";
    }
}

void deleteIndex(int i) {
    for (int j = i; j < num; j++) {
        emp[j] = emp[j + 1];
    }
}

void displayAllRecords() {
    if (num == -1) {
        cout << " No records present!\n";
        return;
    }

    cout << endl
         << setw(5) << "ID"
         << setw(10) << "NAME"
         << setw(18) << "DESIGNATION"
         << setw(10) << "SALARY\n";

    for (int i = 0; i <= num; i++) {
        cout << setw(5) << emp[i].employee_id
             << setw(10) << emp[i].name
             << setw(18) << emp[i].designation
             << setw(10) << emp[i].salary << endl;
    }
}

void deleteRecord() {
    int employee_id;
    bool found = false;
    cout << "Enter the Employee ID to Delete Record: ";
    cin >> employee_id;

    for (int i = 0; i <= num; i++) {
        if (emp[i].employee_id == employee_id) {
            deleteIndex(i);
            num--;
            found = true;
            cout << " Employee record with ID " << employee_id << " deleted successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << " Employee record with ID " << employee_id << " not found.\n";
    }
}

void searchRecord() {
    int employee_id;
    cout << "Enter the Employee ID to Search Record: ";
    cin >> employee_id;

    for (int i = 0; i <= num; i++) {
        if (emp[i].employee_id == employee_id) {
            cout << "\n Employee Found:\n";
            cout << setw(5) << "ID"
                 << setw(10) << "NAME"
                 << setw(18) << "DESIGNATION"
                 << setw(10) << "SALARY\n";

            cout << setw(5) << emp[i].employee_id
                 << setw(10) << emp[i].name
                 << setw(18) << emp[i].designation
                 << setw(10) << emp[i].salary << endl;
            return;
        }
    }

    cout << " Employee record not found.\n";
}

int main() {
    int option = 0;

    while (option != 5) {
        cout << "\n----- Employee Management System -----\n";
        cout << "1. Insert New Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Delete Record\n";
        cout << "4. Search Record by Employee ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: insert(); break;
            case 2: displayAllRecords(); break;
            case 3: deleteRecord(); break;
            case 4: searchRecord(); break;
            case 5: cout << "\n*** Exiting Employee Management System ***\n"; break;
            default: cout << " Enter a valid option!\n"; break;
        }
    }

    return 0;
}

