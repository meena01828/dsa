#include <iostream>
#include <string>
using namespace std;

struct node {
    string k;  
    string m;  

    node *left, *right;
};

class dict {
public:
    node *root;
    dict() { root = NULL; }

    void create();
    void insert(node *&, node *);
    void disp(node *);
    bool search(node *, const string &, int &);
    bool update(node *, const string &);
    node* del(node *, const string &);
    node* min(node *);
};

void dict::create() {
    int ch;
    do {
        node *temp = new node;
        cout << "\nEnter Keyword: ";
        cin >> temp->k;
        cout << "Enter Meaning: ";
        cin >> temp->m;
        temp->left = temp->right = NULL;
        insert(root, temp);
        cout << "\nAdd more? (1: Yes / 0: No): ";
        cin >> ch;
    } while (ch == 1);
}

void dict::insert(node *&r, node *temp) {
    if (r == NULL) {
        r = temp;
        return;
    }
    if (temp->k < r->k)
        insert(r->left, temp);
    else
        insert(r->right, temp);
}

void dict::disp(node *r) {
    if (r) {
        disp(r->left);
        cout << "\nKeyword: " << r->k << " | Meaning: " << r->m;
        disp(r->right);
    }
}

bool dict::search(node *r, const string &key, int &compCount) {
    while (r) {
        compCount++;
        if (key == r->k)
            return true;
        r = (key < r->k) ? r->left : r->right;
    }
    return false;
}

bool dict::update(node *r, const string &key) {
    while (r) {
        if (key == r->k) {
            cout << "Enter New Meaning: ";
            cin >> r->m;
            return true;
        }
        r = (key < r->k) ? r->left : r->right;
    }
    return false;
}

node* dict::del(node *r, const string &key) {
    if (!r) return NULL;
    if (key < r->k)
        r->left = del(r->left, key);
    else if (key > r->k)
        r->right = del(r->right, key);
    else {
        if (!r->left) {
            node *temp = r->right;
            delete r;
            return temp;
        } else if (!r->right) {
            node *temp = r->left;
            delete r;
            return temp;
        }
        node *temp = min(r->right);
        r->k = temp->k;
        r->m = temp->m;
        r->right = del(r->right, temp->k);
    }
    return r;
}

node* dict::min(node *r) {
    while (r && r->left)
        r = r->left;
    return r;
}

int main() {
    dict d;
    int ch;
    string key;

    do {
        cout << "\nMenu\n1. Create\n2. Display\n3. Search\n4. Update\n5. Delete\nEnter Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                d.create();
                break;

            case 2:
                if (!d.root)
                    cout << "\nDictionary is Empty.";
                else
                    d.disp(d.root);
                break;

            case 3:
            {
                if (!d.root) {
                    cout << "\nDictionary is Empty.";
                    break;
                }
                cout << "Enter Keyword to Search: ";
                cin >> key;
                int comparisons = 0;
                if (d.search(d.root, key, comparisons))
                    cout << "Keyword Found in " << comparisons << " comparisons.";
                else
                    cout << "Keyword Not Found.";
                break;
            }

            case 4:
                if (!d.root) {
                    cout << "\nDictionary is Empty.";
                    break;
                }
                cout << "Enter Keyword to Update: ";
                cin >> key;
                if (d.update(d.root, key))
                    cout << "Meaning Updated.";
                else
                    cout << "Keyword Not Found.";
                break;

            case 5:
                if (!d.root) {
                    cout << "\nDictionary is Empty.";
                    break;
                }
                cout << "Enter Keyword to Delete: ";
                cin >> key;
                d.root = d.del(d.root, key);
                cout << "Deletion Complete.";
                break;

            default:
                cout << "Invalid Choice!";
        }
    } while (ch >= 1 && ch <= 5);

    return 0;
}
