#include <iostream>
#include <cstring>
using namespace std;

class Flight {
private:
    int am[10][10];               // Adjacency matrix
    char city_index[10][10];      // Stores city names
    int city_count;

    int getCityIndex(const char* name); // Helper to get or insert city index

public:
    Flight();
    void create();
    void display() const;
};

Flight::Flight() : city_count(0) {
    memset(am, 0, sizeof(am)); // Initialize adjacency matrix
    for (int i = 0; i < 10; ++i)
        strcpy(city_index[i], "xx");
}

// Returns index of city; adds it if not present
int Flight::getCityIndex(const char* name) {
    for (int i = 0; i < city_count; ++i) {
        if (strcmp(city_index[i], name) == 0)
            return i;
    }
    if (city_count < 10) {
        strcpy(city_index[city_count], name);
        return city_count++;
    }
    return -1; // No space left
}

void Flight::create() {
    char s[10], d[10], choice;
    int wt;

    do {
        cout << "\nEnter Source City: ";
        cin >> s;
        cout << "Enter Destination City: ";
        cin >> d;

        int si = getCityIndex(s);
        int di = getCityIndex(d);

        if (si == -1 || di == -1) {
            cout << "City limit reached. Cannot add more cities.\n";
            return;
        }

        cout << "Enter Distance from " << s << " to " << d << ": ";
        cin >> wt;
        am[si][di] = wt;

        cout << "Do you want to add more flights? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void Flight::display() const {
    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < city_count; ++i)
        cout << city_index[i] << "\t";
    cout << "\n";

    for (int i = 0; i < city_count; ++i) {
        cout << city_index[i] << "\t";
        for (int j = 0; j < city_count; ++j)
            cout << am[i][j] << "\t";
        cout << "\n";
    }
}

int main() {
    Flight f;
    int choice;

    do {
        cout << "\n***** Flight Main Menu *****";
        cout << "\n1. Create Flight Graph";
        cout << "\n2. Display Adjacency Matrix";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: f.create(); break;
            case 2: f.display(); break;
            case 3: return 0;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (true);
}

