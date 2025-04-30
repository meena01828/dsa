#include <iostream>
#include <string>
#include <algorithm> // For max()
using namespace std;

// AVL Tree Node Structure
class Node {
public:
    string key, meaning;
    Node *left, *right;
    int height;

    Node(string k, string m) {
        key = k;
        meaning = m;
        left = right = NULL;
        height = 1;
    }
};

// AVL Tree Class
class AVL {
private:
    Node* root;

    // Utility functions
    int getHeight(Node* n) {
        return (n == NULL) ? 0 : n->height;
    }

    int getBalanceFactor(Node* n) {
        return (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T = x->right;

        x->right = y;
        y->left = T;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T = y->left;

        y->left = x;
        x->right = T;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, string key, string meaning) {
        if (node == NULL)
            return new Node(key, meaning);

        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else
            return node; // No duplicate keys allowed

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalanceFactor(node);

        // Balancing cases
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(Node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->key << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    void reverseInorder(Node* root) {
        if (root != NULL) {
            reverseInorder(root->right);
            cout << root->key << " : " << root->meaning << endl;
            reverseInorder(root->left);
        }
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string key, bool& found) {
        if (root == NULL)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key, found);
        else if (key > root->key)
            root->right = deleteNode(root->right, key, found);
        else {
            found = true;
            if (root->left == NULL || root->right == NULL) {
                Node* temp = (root->left) ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key, found);
            }
        }

        if (root == NULL)
            return root;

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    bool search(Node* root, string key) {
        if (root == NULL)
            return false;
        if (root->key == key)
            return true;
        if (key < root->key)
            return search(root->left, key);
        return search(root->right, key);
    }

public:
    AVL() {
        root = NULL;
    }

    void insert(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKey(string key) {
        bool found = false;
        root = deleteNode(root, key, found);
        if (found)
            cout << "Keyword '" << key << "' deleted successfully.\n";
        else
            cout << "Keyword '" << key << "' not found in the dictionary.\n";
    }

    void searchKey(string key) {
        if (search(root, key))
            cout << "Keyword '" << key << "' found in the dictionary.\n";
        else
            cout << "Keyword '" << key << "' not found in the dictionary.\n";
    }

    void displayAscending() {
        cout << "\nDictionary (Ascending Order):\n";
        inorder(root);
    }

    void displayDescending() {
        cout << "\nDictionary (Descending Order):\n";
        reverseInorder(root);
    }
};

int main() {
    AVL dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n********** AVL Tree Dictionary **********";
        cout << "\n1. Insert a keyword";
        cout << "\n2. Display dictionary (Ascending Order)";
        cout << "\n3. Display dictionary (Descending Order)";
        cout << "\n4. Search for a keyword";
        cout << "\n5. Delete a keyword";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear the newline left in the buffer

        switch (choice) {
            case 1:
                cout << "\nEnter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.insert(key, meaning);
                break;
            case 2:
                dict.displayAscending();
                break;
            case 3:
                dict.displayDescending();
                break;
            case 4:
                cout << "\nEnter keyword to search: ";
                getline(cin, key);
                dict.searchKey(key);
                break;
            case 5:
                cout << "\nEnter keyword to delete: ";
                getline(cin, key);
                dict.deleteKey(key);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

