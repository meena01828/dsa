#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* createNode(int data) {
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* node, int data) {
    if (node == NULL)
        return createNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);
    return node;
}

void inorder(Node* node) {
    if (node == NULL)
        return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void preorder(Node* node) {
    if (node == NULL)
        return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void postorder(Node* node) {
    if (node == NULL)
        return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

int height(Node* node) {
    if (node == NULL)
        return -1;
    int l = height(node->left);
    int r = height(node->right);
    return (l > r ? l : r) + 1;
}

int minValue(Node* node) {
    if (node == NULL)
        return -1;
    while (node->left != NULL)
        node = node->left;
    return node->data;
}

int maxValue(Node* node) {
    if (node == NULL)
        return -1;
    while (node->right != NULL)
        node = node->right;
    return node->data;
}

bool search(Node* node, int data) {
    while (node != NULL) {
        if (node->data == data)
            return true;
        else if (data < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return false;
}

void mirror(Node* node) {
    if (node == NULL)
        return;
    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;

    mirror(node->left);
    mirror(node->right);
}

Node* deleteNode(Node* node, int data) {
    if (node == NULL)
        return NULL;

    if (data < node->data)
        node->left = deleteNode(node->left, data);
    else if (data > node->data)
        node->right = deleteNode(node->right, data);
    else {
        if (node->left == NULL) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = node->right;
        while (temp->left != NULL)
            temp = temp->left;

        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }
    return node;
}

void displayTraversals() {
    cout << "\nINORDER: ";
    inorder(root);
    cout << "\nPREORDER: ";
    preorder(root);
    cout << "\nPOSTORDER: ";
    postorder(root);
    cout << endl;
}

int main() {
    int choice, value, nodes;
    char cont = 'y';

    while (cont == 'y' || cont == 'Y') {
        cout << "\nMENU";
        cout << "\n1. Add Nodes";
        cout << "\n2. Display Traversals";
        cout << "\n3. Max Value";
        cout << "\n4. Min Value";
        cout << "\n5. Tree Height";
        cout << "\n6. Search";
        cout << "\n7. Mirror Tree";
        cout << "\n8. Delete Node";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "How many nodes to add? ";
                cin >> nodes;
                for (int i = 0; i < nodes; i++) {
                    cout << "Enter value: ";
                    cin >> value;
                    root = insert(root, value);
                }
                break;

            case 2:
                displayTraversals();
                break;

            case 3:
                cout << "Max value: " << maxValue(root) << endl;
                break;

            case 4:
                cout << "Min value: " << minValue(root) << endl;
                break;

            case 5:
                cout << "Tree height: " << height(root) << endl;
                break;

            case 6:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "FOUND" << endl;
                else
                    cout << "NOT FOUND" << endl;
                break;

            case 7:
                cout << "Inorder before mirroring: ";
                inorder(root);
                mirror(root);
                cout << "\nInorder after mirroring: ";
                inorder(root);
                cout << endl;
                break;

            case 8:
                cout << "Enter node to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Inorder after deletion: ";
                inorder(root);
                cout << endl;
                break;

            default:
                cout << "Invalid choice.\n";
        }

        cout << "\nEnter 'y' to continue: ";
        cin >> cont;
    }

    return 0;
}
