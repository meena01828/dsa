#include<iostream>
#include <vector> 
#include <limits> 
using namespace std; 
 
class OBST { 
    int n; 
    vector<float> p, q; 
    vector<vector<float> > weight, cost; 
    vector<vector<int> > root; 
 
public: 
    void input(); 
    void construct(); 
    void printTree(int, int); 
    void displayResults(); 
}; 
 
void OBST::input() { 
    cout << "\n**** PROGRAM FOR OPTIMAL BINARY SEARCH TREE (OBST) ******\n"; 
    cout << "\nEnter the number of keys: "; 
    cin >> n; 
    p.resize(n + 1); 
    q.resize(n + 1); 
    weight.assign(n + 1, vector<float>(n + 1, 0)); 
    cost.assign(n + 1, vector<float>(n + 1, 0)); 
    root.assign(n + 1, vector<int>(n + 1, 0)); 
 
    cout << "\nEnter probabilities for successful search:\n"; 
    for (int i = 1; i <= n; i++) { 
        cout << "p[" << i << "]: "; 
        cin >> p[i]; 
    } 
    cout << "\nEnter probabilities for unsuccessful search:\n"; 
    for (int i = 0; i <= n; i++) { 
        cout << "q[" << i << "]: "; 
        cin >> q[i]; 
    } 
} 
 
void OBST::construct() { 
    for (int i = 0; i <= n; i++) { 
        weight[i][i] = q[i]; 
        cost[i][i] = 0; 
        root[i][i] = 0; 
    } 
 
    for (int len = 1; len <= n; len++) { 
        for (int i = 0; i <= n - len; i++) { 
            int j = i + len; 
            weight[i][j] = weight[i][j - 1] + p[j] + q[j]; 
            cost[i][j] = numeric_limits<float>::max(); 
 
            for (int r = i + 1; r <= j; r++) { 
                float temp_cost = cost[i][r - 1] + cost[r][j] + weight[i][j]; 
                if (temp_cost < cost[i][j]) { 
                    cost[i][j] = temp_cost; 
                    root[i][j] = r; 
                } 
            } 
        } 
    } 
} 
 
void OBST::printTree(int i, int j) { 
    if (i >= j) return; 
    cout << "\nRoot of subtree spanning " << i << " to " << j << " is: " << root[i][j]; 
    if (root[i][j] - 1 >= i) 
        cout << "\n Left child of " << root[i][j] << " is: " << root[i][root[i][j] - 1]; 
    if (root[i][j] < j) 
        cout << "\n Right child of " << root[i][j] << " is: " << root[root[i][j]][j]; 
    printTree(i, root[i][j] - 1); 
    printTree(root[i][j], j); 
} 
 
void OBST::displayResults() { 
    cout << "\nOptimal BST construction results:"; 
    cout << "\nTotal weight: " << weight[0][n]; 
    cout << "\nTotal cost: " << cost[0][n]; 
    cout << "\nRoot node: " << root[0][n]; 
    printTree(0, n); 
    cout << "\n"; 
} 
 
int main() { 
    OBST tree; 
    tree.input(); 
    tree.construct(); 
    tree.displayResults(); 
    return 0; 
} 
 
 
