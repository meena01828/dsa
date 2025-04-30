#include <iostream> 
#include <limits.h> 
using namespace std; 
 
class Tree { 
private: 
    int a[20][20], v, e; 
    bool visited[20]; 
 
public: 
    Tree(); 
    void input(); 
    void display() const; 
    void minimum() const; 
}; 
 
Tree::Tree() { 
    v = 0; 
    e = 0; 
    for (int i = 0; i < 20; i++) { 
        visited[i] = false; 
        for (int j = 0; j < 20; j++) { 
            a[i][j] = INT_MAX; // Initialize with a large value 
        } 
    } 
} 
 
void Tree::input() { 
    cout << "Enter the number of branches: "; 
    cin >> v; 
    cout << "\nEnter the number of connections: "; 
    cin >> e; 
 
    for (int i = 0; i < e; i++) { 
        int l, u, w; 
        cout << "Enter the end branches of connection (1-based index): "; 
        cin >> l >> u; 
        cout << "Enter the phone company charge for this connection: "; 
        cin >> w; 
        a[l - 1][u - 1] = a[u - 1][l - 1] = w; 
    } 
} 
 
void Tree::display() const { 
    cout << "\nAdjacency Matrix:" << endl; 
    for (int i = 0; i < v; i++) { 
        for (int j = 0; j < v; j++) { 
            if (a[i][j] == INT_MAX) 
                cout << "INF "; 
            else 
                cout << a[i][j] << " "; 
        } 
        cout << endl; 
    } 
} 
 
void Tree::minimum() const { 
    int total = 0; 
    bool mstSet[20] = {false}; 
    int parent[20]; 
    int key[20]; 
 
    for (int i = 0; i < v; i++) { 
        key[i] = INT_MAX; 
        parent[i] = -1; 
    } 
 
    key[0] = 0; 
 
    for (int count = 0; count < v - 1; count++) { 
        int min = INT_MAX, u; 
        for (int i = 0; i < v; i++) { 
            if (!mstSet[i] && key[i] < min) { 
                min = key[i]; 
                u = i; 
            } 
        } 
 
        mstSet[u] = true; 
 
        for (int i = 0; i < v; i++) { 
            if (a[u][i] != INT_MAX && !mstSet[i] && a[u][i] < key[i]) { 
                parent[i] = u; 
                key[i] = a[u][i]; 
            } 
        } 
    } 
 
    cout << "\nMinimum Cost Connections:" << endl; 
    for (int i = 1; i < v; i++) { 
        cout << "Branch " << parent[i] + 1 << " -> " << i + 1 << " with charge: " << 
a[i][parent[i]] << endl; 
        total += a[i][parent[i]]; 
    } 
    cout << "\nMinimum Total Cost: " << total << endl; 
} 
 
int main() { 
    Tree t; 
    int ch; 
    do { 
        cout << "\n===== PRIM'S ALGORITHM ====="; 
        cout << "\n1. Input\n2. Display\n3. Find Minimum Spanning Tree\n4. Exit"; 
        cout << "\nEnter your choice: "; 
        cin >> ch; 
 
        switch (ch) { 
            case 1: 
                t.input(); 
                break; 
            case 2: 
                t.display(); 
                break; 
            case 3: 
                t.minimum(); 
                break; 
            case 4: 
                cout << "Exiting program..." << endl; 
                break; 
            default: 
cout << "Invalid choice! Please try again."; 
} 
} while (ch != 4); 
return 0; 
}  
