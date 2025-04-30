#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  // Required for stringstream
using namespace std;

class Student {
public:
    int roll;
    string name, division, address;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        getline(cin, division);
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() {
        cout << "\nRoll No: " << roll << "\nName: " << name << "\nDivision: " << division << "\nAddress: " << address << "\n";
    }

    int getRoll() {
        return roll;
    }
};

int toInt(string str) {
    stringstream ss(str);
    int num;
    ss >> num;
    return num;
}

void addStudent() {
    Student s;
    s.input();

    ofstream file("students.txt", ios::app);
    file << s.getRoll() << "," << s.name << "," << s.division << "," << s.address << "\n";
    file.close();
    cout << "Student record added.\n";
}

void displayAllStudents() {
    ifstream file("students.txt");
    string line;
    bool found = false;
    cout << "\n==== Student Records ====\n";
    while (getline(file, line)) {
        int pos1 = line.find(",");
        int roll = toInt(line.substr(0, pos1));
        string rest = line.substr(pos1 + 1);

        int pos2 = rest.find(",");
        int pos3 = rest.find(",", pos2 + 1);

        string name = rest.substr(0, pos2);
        string division = rest.substr(pos2 + 1, pos3 - pos2 - 1);
        string address = rest.substr(pos3 + 1);

        cout << "\nRoll No: " << roll;
        cout << "\nName: " << name;
        cout << "\nDivision: " << division;
        cout << "\nAddress: " << address << "\n";
        found = true;
    }
    file.close();

    if (!found) {
        cout << "No student records found.\n";
    }
}

void searchStudent() {
    int searchRoll;
    bool found = false;
    cout << "Enter roll number to search: ";
    cin >> searchRoll;

    ifstream file("students.txt");
    string line;
    while (getline(file, line)) {
        int pos1 = line.find(",");
        int roll = toInt(line.substr(0, pos1));
        if (roll == searchRoll) {
            string rest = line.substr(pos1 + 1);
            int pos2 = rest.find(",");
            int pos3 = rest.find(",", pos2 + 1);

            string name = rest.substr(0, pos2);
            string division = rest.substr(pos2 + 1, pos3 - pos2 - 1);
            string address = rest.substr(pos3 + 1);

            cout << "\nStudent Found:\n";
            cout << "Roll No: " << roll << "\nName: " << name << "\nDivision: " << division << "\nAddress: " << address << "\n";
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Student with roll number " << searchRoll << " not found.\n";
    }
}

void deleteStudent() {
    int deleteRoll;
    bool found = false;
    cout << "Enter roll number to delete: ";
    cin >> deleteRoll;

    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    string line;

    while (getline(inFile, line)) {
        int pos1 = line.find(",");
        int roll = toInt(line.substr(0, pos1));

        if (roll != deleteRoll) {
            outFile << line << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "Student with roll number " << deleteRoll << " deleted successfully.\n";
    } else {
        cout << "Student with roll number " << deleteRoll << " not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== Student Information System =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student by Roll Number";
        cout << "\n4. Delete Student by Roll Number";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayAllStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
