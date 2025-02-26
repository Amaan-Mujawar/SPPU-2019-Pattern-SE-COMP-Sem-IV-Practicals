/*
Amaan Mujawar
COMPUTER SE B
Roll No. 56
TSSM’s PVPIT, Bavdhan, Pune
*/
/*
LAB ASSIGNMENT 1: Consider telephone book database of N clients.
Make use of a hash table implementation to quickly look up client's
telephone number. Make use of two collision handling techniques and
compare them using number of comparisons required to find a set of
telephone numbers.
*/

#include <iostream>
using namespace std;

class node
{
private:
    string name;
    string telephone;
    int key;

public:
    node()
    {
        key = 0;
    }
    friend class hashing;
};

int ascii_generator(string s)
{
    int sum = 0;
    for (int i = 0; s[i] != '\0'; i++)
        sum = sum + s[i];
    return sum % 100;
}

class hashing
{
private:
    node data[100];
    string n;
    string tele;
    int k, index;
    int size = 100;

public:
    hashing()
    {
        k = 0;
    }

    void create_record(string n, string tele)
    {
        k = ascii_generator(n);
        index = k % size;
        for (int j = 0; j < size; j++)
        {
            if (data[index].key == 0)
            {
                data[index].key = k;
                data[index].name = n;
                data[index].telephone = tele;
                break;
            }
            else
            {
                index = (index + 1) % size;
            }
        }
    }

    void search_record(string name)
    {
        int index1, k, flag = 0;
        k = ascii_generator(name);
        index1 = k % size;
        for (int a = 0; a < size; a++)
        {
            if (data[index1].key == k)
            {
                flag = 1;
                cout << "\nRecord found\n";
                cout << "Name :: " << data[index1].name << endl;
                cout << "Telephone :: " << data[index1].telephone << endl;
                break;
            }
            else
            {
                index1 = (index1 + 1) % size;
            }
        }
        if (flag == 0)
            cout << "Record not found.";
    }

    void delete_record(string name)
    {
        int index1, key, flag = 0;
        key = ascii_generator(name);
        index1 = key % size;
        for (int a = 0; a < size; a++)
        {
            if (data[index1].key == key)
            {
                flag = 1;
                data[index1].key = 0;
                data[index1].name = " ";
                data[index1].telephone = " ";
                cout << "Record deleted successfully." << endl;
                break;
            }
            else
            {
                index1 = (index1 + 1) % size;
            }
        }
        if (flag == 0)
            cout << "Record not found.";
    }

    void update_record(string name)
    {
        int index1, key, flag = 0;
        key = ascii_generator(name);
        index1 = key % size;
        for (int a = 0; a < size; a++)
        {
            if (data[index1].key == key)
            {
                flag = 1;
                break;
            }
            else
            {
                index1 = (index1 + 1) % size;
            }
        }
        if (flag == 1)
        {
            cout << "Enter the new telephone number:: ";
            cin >> tele;
            data[index1].telephone = tele;
            cout << "\nRecord Updated Successfully";
        }
    }

    void display_record()
    {
        cout << "\tName \t\t Telephone";
        for (int a = 0; a < size; a++)
        {
            if (data[a].key != 0)
            {
                cout << "\n\t" << data[a].name << " \t\t\t " << data[a].telephone;
            }
        }
    }
};

// MAIN
int main()
{
    hashing s;
    string name;
    string telephone;
    int choice;
    bool loop = true;

    while (loop)
    {
        cout << "\n\nTelephone book Database\n";
        cout << "1. Create Record" << endl;
        cout << "2. Display Record" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Update Record" << endl;
        cout << "5. Delete Record" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice:: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nEnter name:: ";
            cin >> name;
            cout << "Enter telephone number:: ";
            cin >> telephone;
            s.create_record(name, telephone);
            break;
        case 2:
            s.display_record();
            break;
        case 3:
            cout << "\nEnter the name:: ";
            cin >> name;
            s.search_record(name);
            break;
        case 4:
            cout << "\nEnter the name:: ";
            cin >> name;
            s.update_record(name);
            break;
        case 5:
            cout << "\nEnter the name to delete:: ";
            cin >> name;
            s.delete_record(name);
            break;
        case 6:
            loop = false;
            break;
        default:
            cout << "\nYou entered something wrong!";
            break;
        }
    }
    return 0;
}
