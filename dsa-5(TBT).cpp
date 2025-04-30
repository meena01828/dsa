#include <iostream>
using namespace std;

class node {
public:
    int data;
    int lth, rth; // Thread flags
    node *left, *right;
};

class TBT {
    node *root, *head;

public:
    TBT() {
        head = new node;
        head->left = head->right = head;
        head->lth = 1; // No left subtree initially
        head->rth = 0; // Right always points to itself
        root = NULL;
    }

    void create();
    void preorder();
    void inorder();
private:
    node* inorderSucc(node*);
};

void TBT::create() {
    char ch;
    do {
        node* curr = new node;
        cout << "\nEnter the data: ";
        cin >> curr->data;
        curr->lth = curr->rth = 1;
        curr->left = curr->right = NULL;

        if (!root) {
            root = curr;
            root->left = root->right = head;
            head->left = root;
            head->lth = 0;
        } else {
            node* temp = root;
            while (true) {
                if (curr->data < temp->data) {
                    if (temp->lth) {
                        curr->left = temp->left;
                        curr->right = temp;
                        temp->lth = 0;
                        temp->left = curr;
                        break;
                    }
                    temp = temp->left;
                } else {
                    if (temp->rth) {
                        curr->right = temp->right;
                        curr->left = temp;
                        temp->rth = 0;
                        temp->right = curr;
                        break;
                    }
                    temp = temp->right;
                }
            }
        }

        cout << "\nDo you want to continue (Y/N)? ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void TBT::preorder() {
    node* temp = root;
    int flag = 0;

    while (temp != head) {
        if (flag == 0)
            cout << temp->data << " ";

        if (temp->lth == 0 && flag == 0) {
            temp = temp->left;
        } else if (temp->rth == 0) {
            temp = temp->right;
            flag = 0;
        } else {
            temp = temp->right;
            flag = 1;
        }
    }
}

void TBT::inorder() {
    node* temp = head;
    while ((temp = inorderSucc(temp)) != head)
        cout << temp->data << " ";
}

node* TBT::inorderSucc(node* temp) {
    node* p = temp->right;
    while (temp->rth == 0 && p->lth == 0)
        p = p->left;
    return p;
}

int main() {
    TBT t;
    cout << "\nCreate a binary tree:";
    t.create();
    cout << "\nPreorder traversal is: ";
    t.preorder();
    cout << "\nInorder traversal is: ";
    t.inorder();
    return 0;
}

