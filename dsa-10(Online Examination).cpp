#include <iostream> 
using namespace std; 
#define MAX 20 
 
class Heap { 
    int marks[MAX]; 
    int size; 
 
public: 
    Heap() : size(0) {} 
 
    void insertHeap(int total); 
    void displayHeap(); 
    void findMax(); 
    void findMin(); 
}; 
 
void Heap::insertHeap(int total) { 
    size = total; 
    cout << "Enter marks: "; 
    for (int i = 1; i <= total; i++) { 
        cin >> marks[i]; 
        int j = i, parent = j / 2; 
        while (j > 1 && marks[j] < marks[parent]) { 
            swap(marks[j], marks[parent]); 
            j = parent; 
            parent = j / 2; 
        } 
    } 
} 
 
void Heap::displayHeap() { 
    if (size == 0) { 
        cout << "Heap is empty!" << endl; 
        return; 
    } 
    cout << "Heap representation: "; 
    for (int i = 1; i <= size; i++) { 
        cout << marks[i] << " "; 
    } 
    cout << endl; 
} 
 
void Heap::findMax() { 
    if (size == 0) { 
        cout << "Heap is empty!" << endl; 
        return; 
    } 
    int maxMark = marks[1]; 
    for (int i = 2; i <= size; i++) { 
        if (marks[i] > maxMark) maxMark = marks[i]; 
    } 
    cout << "Maximum marks: " << maxMark << endl; 
} 
 
void Heap::findMin() { 
    if (size == 0) { 
        cout << "Heap is empty!" << endl; 
        return; 
    } 
    cout << "Minimum marks: " << marks[1] << endl; 
} 
 
int main() { 
    Heap h; 
    int choice, total; 
    do { 
        cout << "\nMenu:\n"; 
        cout << "1. Read marks\n"; 
        cout << "2. Display Heap\n"; 
        cout << "3. Find Maximum Marks\n"; 
        cout << "4. Find Minimum Marks\n"; 
        cout << "5. Exit\n"; 
        cout << "Enter choice: "; 
        cin >> choice; 
 
        switch (choice) { 
            case 1: 
                cout << "Enter number of students: "; 
                cin >> total; 
                h.insertHeap(total); 
                break; 
            case 2: 
                h.displayHeap(); 
                break; 
            case 3: 
                h.findMax(); 
                break; 
            case 4: 
                h.findMin(); 
                break; 
            case 5: 
                cout << "Exiting..." << endl; 
                break; 
            default: 
                cout << "Invalid choice!" << endl; 
        } 
    } while (choice != 5); 
 
    return 0; 
}
