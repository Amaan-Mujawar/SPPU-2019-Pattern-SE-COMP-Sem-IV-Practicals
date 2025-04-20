/*
Amaan Mujawar
COMPUTER SE B
Roll No. 56
TSSM’s PVPIT, Bavdhan, Pune
*/
/*
LAB ASSIGNMENT 9: A Dictionary stores keywords & its meanings. Provide facility for adding new 
keywords, deleting keywords, updating values of any entry. Provide facility to display whole 
data sorted in ascending/ Descending order. Also find how many maximum comparisons may require 
for finding any keyword. Use Height balance tree and find the complexity for finding a keyword. 
*/

#include<iostream>
#include<string.h>
using namespace std;

class avl {
    char word[20], mean[50];
    avl *left, *right;
    int ht;

public:
    avl* create(avl* root);
    avl* insert(avl* root, char word[], char mean[]);
    void display(avl*);
    int height(avl*);
    avl* rotateright(avl*);
    avl* rotateleft(avl*);
    int BF(avl*);
    avl* Delete(avl*, char*);
    avl* RR(avl*);
    avl* LL(avl*);
    avl* LR(avl*);
    avl* RL(avl*);
    avl* mirror(avl*);
    avl* update(avl*);
};

int avl::height(avl* root) {
    if (!root) return 0;
    int lh = root->left ? 1 + root->left->ht : 0;
    int rh = root->right ? 1 + root->right->ht : 0;
    return max(lh, rh);
}

int avl::BF(avl* root) {
    if (!root) return 0;
    int lh = root->left ? 1 + root->left->ht : 0;
    int rh = root->right ? 1 + root->right->ht : 0;
    return lh - rh;
}

avl* avl::rotateright(avl* x) {
    avl* y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

avl* avl::rotateleft(avl* x) {
    avl* y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

avl* avl::RR(avl* T) {
    return rotateleft(T);
}

avl* avl::LL(avl* T) {
    return rotateright(T);
}

avl* avl::LR(avl* T) {
    T->left = rotateleft(T->left);
    return rotateright(T);
}

avl* avl::RL(avl* T) {
    T->right = rotateright(T->right);
    return rotateleft(T);
}

avl* avl::insert(avl* root, char w[], char m[]) {
    if (!root) {
        root = new avl;
        strcpy(root->word, w);
        strcpy(root->mean, m);
        root->left = root->right = NULL;
        root->ht = 0;
        return root;
    }

    if (strcmp(w, root->word) > 0) {
        root->right = insert(root->right, w, m);
        if (BF(root) == 2) {
            if (strcmp(w, root->right->word) > 0)
                root = RR(root);
            else
                root = RL(root);
        }
    }
    else if (strcmp(w, root->word) < 0) {
        root->left = insert(root->left, w, m);
        if (BF(root) == -2) {
            if (strcmp(w, root->left->word) < 0)
                root = LL(root);
            else
                root = LR(root);
        }
    }

    root->ht = height(root);
    return root;
}

avl* avl::create(avl* root) {
    int n;
    char w[20], m[50];
    cout << "\nEnter the number of words: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter word " << i + 1 << ": ";
        cin >> w;
        cout << "Enter its meaning: ";
        cin >> m;
        root = insert(root, w, m);
    }

    return root;
}

void avl::display(avl* root) {
    if (root) {
        display(root->left);
        cout << "\n" << root->word << " :: " << root->mean << " (BF = " << BF(root) << ")";
        display(root->right);
    }
}

avl* avl::Delete(avl* T, char* w) {
    if (!T) {
        cout << "\nWord not found.";
        return NULL;
    }

    if (strcmp(w, T->word) > 0) {
        T->right = Delete(T->right, w);
        if (BF(T) == 2) {
            if (BF(T->left) >= 0)
                T = LL(T);
            else
                T = LR(T);
        }
    }
    else if (strcmp(w, T->word) < 0) {
        T->left = Delete(T->left, w);
        if (BF(T) == -2) {
            if (BF(T->right) <= 0)
                T = RR(T);
            else
                T = RL(T);
        }
    }
    else {
        if (T->right) {
            avl* p = T->right;
            while (p->left)
                p = p->left;
            strcpy(T->word, p->word);
            strcpy(T->mean, p->mean);
            T->right = Delete(T->right, p->word);
            if (BF(T) == 2) {
                if (BF(T->left) >= 0)
                    T = LL(T);
                else
                    T = LR(T);
            }
        }
        else {
            avl* temp = T->left;
            delete T;
            return temp;
        }
    }

    T->ht = height(T);
    return T;
}

avl* avl::update(avl* root) {
    char w[20], m[50];
    avl* temp = root;

    cout << "\nEnter the word to update: ";
    cin >> w;
    cout << "Enter the new meaning: ";
    cin >> m;

    while (temp) {
        if (strcmp(w, temp->word) == 0) {
            strcpy(temp->mean, m);
            cout << "Meaning updated successfully.\n";
            break;
        }
        if (strcmp(w, temp->word) < 0)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (!temp)
        cout << "Word not found.\n";

    return root;
}

avl* avl::mirror(avl* temp) {
    if (!temp) return NULL;
    avl* p = new avl;
    strcpy(p->word, temp->word);
    strcpy(p->mean, temp->mean);
    p->left = mirror(temp->right);
    p->right = mirror(temp->left);
    return p;
}

int main() {
    int ch;
    char z;
    avl d, *root = NULL, *root1 = NULL;
    char w[20], m[50];

    cout << "********** AVL Tree Dictionary **********\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Create\n2. Insert\n3. Delete\n4. Display (Ascending)\n5. Update\n6. Display (Descending)\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                root = d.create(root);
                break;
            case 2:
                cout << "\nEnter word: ";
                cin >> w;
                cout << "Enter meaning: ";
                cin >> m;
                root = d.insert(root, w, m);
                break;
            case 3:
                cout << "\nEnter word to delete: ";
                cin >> w;
                root = d.Delete(root, w);
                break;
            case 4:
                cout << "\nWords in Ascending Order:\n";
                d.display(root);
                break;
            case 5:
                root = d.update(root);
                break;
            case 6:
                cout << "\nWords in Descending Order:\n";
                root1 = d.mirror(root);
                d.display(root1);
                break;
            case 7:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

        if (ch != 7) {
            cout << "\nDo you want to continue? (y/n): ";
            cin >> z;
        }

    } while (z == 'y' || z == 'Y');

    return 0;
}
