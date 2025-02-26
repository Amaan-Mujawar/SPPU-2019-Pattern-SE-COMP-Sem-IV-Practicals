/*
Amaan Mujawar
COMPUTER SE B
Roll No. 56
TSSM’s PVPIT, Bavdhan, Pune
*/
/*
LAB ASSIGNMENT 2: Implement all the functions of a dictionary (ADT) using hashing and 
handle collisions using chaining with / without replacement.  
Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, 
Keys must be unique  
Standard Operations: Insert(key, value), Find(key), Delete(key) 
*/

#include <iostream>
#include <string.h>

using namespace std;

struct DictionaryEntry {
    char name[30];
    char name1[30];
};

class hashing {
public:
    int n, sum, x, c, i, j;
    char na[30], na1[30];
    DictionaryEntry d[10];

    hashing() {
        for (i = 0; i < 10; i++) {
            strcpy(d[i].name, "0");
            strcpy(d[i].name1, "0");
        }
    }

    void insert();
    void search();
    void delet();
    void display();
};

void hashing::insert() {
    cout << "\nEnter no. of words: ";
    cin >> n;

    for (j = 0; j < n; j++) {
        cout << "\nEnter the word: ";
        cin >> na;
        cout << "Enter the meaning: ";
        cin >> na1;

        sum = 0;
        for (i = 0; i < strlen(na); i++) {
            sum += na[i];
        }

        x = (sum / strlen(na)) % 10;
        c = x;

        while (1) {
            if (!strcmp(d[x].name, "0")) {
                strcpy(d[x].name, na);
                strcpy(d[x].name1, na1);
                break;
            }
            x = (x + 1) % 10;
            if (c == x) {
                cout << "\nHash table is full";
                break;
            }
        }
    }
}

void hashing::search() {
    cout << "\nEnter word: ";
    cin >> na;

    sum = 0;
    for (i = 0; i < strlen(na); i++) {
        sum += (int)na[i];
    }

    x = (sum / strlen(na)) % 10;
    c = x;

    while (1) {
        if (!strcmp(d[x].name, na)) {
            cout << "\nKey: " << d[x].name << "\nMeaning: " << d[x].name1;
            break;
        }
        x = (x + 1) % 10;
        if (c == x) {
            cout << "\nWord not found";
            break;
        }
    }
}

void hashing::delet() {
    cout << "\nEnter the word to be deleted: ";
    cin >> na;

    sum = 0;
    for (i = 0; i < strlen(na); i++) {
        sum += (int)na[i];
    }

    x = (sum / strlen(na)) % 10;
    c = x;

    while (1) {
        if (!strcmp(d[x].name, na)) {
            cout << "\nKeyword " << d[x].name << " Deleted";
            strcpy(d[x].name, "0");
            strcpy(d[x].name1, "0");
            break;
        }
        x = (x + 1) % 10;
        if (c == x) {
            cout << "\nWord not found";
            break;
        }
    }
}

void hashing::display() {
    cout << "\n--- Dictionary ---";
    cout << "\nKey\tMeaning";

    for (int i = 0; i < 10; i++) {
        if (strcmp(d[i].name, "0")) {
            cout << endl << d[i].name << "\t" << d[i].name1;
        }
    }
    cout << "\n";
}

int main() {
    hashing h;
    int n, loop = 1;

    while (loop == 1) {
        cout << "\n\n--- DICTIONARY MENU ---";
        cout << "\n1. Insert";
        cout << "\n2. Display";
        cout << "\n3. Search";
        cout << "\n4. Delete";
        cout << "\n5. Exit";

        cout << "\nEnter choice: ";
        cin >> n;

        switch (n) {
            case 1:
                h.insert();
                break;
            case 2:
                h.display();
                break;
            case 3:
                h.search();
                break;
            case 4:
                h.delet();
                break;
            case 5:
                loop = 0;
                cout << "\nExiting...";
                break;
            default:
                cout << "\nYou entered something wrong";
        }
    }
    return 0;
}
