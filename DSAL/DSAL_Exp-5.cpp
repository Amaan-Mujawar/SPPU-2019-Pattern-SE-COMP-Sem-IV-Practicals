/*
Amaan Mujawar
COMPUTER SE B
Roll No. 56
TSSM’s PVPIT, Bavdhan, Pune
*/
/*
LAB ASSIGNMENT 5: Beginning with an empty binary search tree, Construct binary search tree by 
inserting the values in the order given. After constructing a binary tree -  
i. Insert new node  
ii. Find number of nodes in longest path from root 
iii. Minimum data value found in the tree  
iv. Change a tree so that the roles of the left and right pointers are swapped at every node  
v. Search a value
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

struct node
{
    int a;
    node *left;
    node *right;
};

class Bt
{
    node *root = NULL, *temp = NULL, *t1 = NULL, *s = NULL, *t = NULL;
    int count;

public:
    Bt() { count = 0; }

    node *create();
    void insert();
    void del();
    node *delet(node *, int);
    void find();
    void search();
    void sw();
    void swap(node *);
    void height();
    int he(node *, int);
    void disp(node *);
    void display();
    node *findmin(node *);
};

node *Bt::create()
{
    node *p = new node;
    p->left = NULL;
    p->right = NULL;

    cout << "\nEnter the data: ";
    cin >> p->a;

    return p;
}

void Bt::insert()
{
    temp = create();

    if (root == NULL)
    {
        root = temp;
    }
    else
    {
        t1 = root;

        while (t1 != NULL)
        {
            s = t1;
            if (temp->a > t1->a)
                t1 = t1->right;
            else
                t1 = t1->left;
        }

        if (temp->a > s->a)
            s->right = temp;
        else
            s->left = temp;
    }
}

void Bt::find()
{
    if (root == NULL)
    {
        cout << "\nTree does not exist.";
    }
    else
    {
        t1 = root;
        while (t1->left != NULL)
            t1 = t1->left;
        cout << "\nSmallest number: " << t1->a;

        t1 = root;
        while (t1->right != NULL)
            t1 = t1->right;
        cout << "\nLargest number: " << t1->a;
    }
}

void Bt::search()
{
    int m, f = 0;
    if (root == NULL)
    {
        cout << "\nTree does not exist.";
        return;
    }

    cout << "\nEnter data to be searched: ";
    cin >> m;

    t1 = root;
    while (t1 != NULL && t1->a != m)
    {
        if (m > t1->a)
            t1 = t1->right;
        else
            t1 = t1->left;

        if (t1 == NULL)
        {
            cout << "\nData not found";
            f = 1;
            break;
        }
    }
    if (f == 0)
        cout << "\nData found";
}

void Bt::sw()
{
    if (root == NULL)
    {
        cout << "\nTree does not exist.";
    }
    else
    {
        swap(root);
    }
}

void Bt::swap(node *q)
{
    if (q == NULL)
        return;
    swap(q->left);
    swap(q->right);
    t = q->left;
    q->left = q->right;
    q->right = t;
}

void Bt::height()
{
    count = 0;
    if (root == NULL)
    {
        cout << "\nTree does not exist.";
    }
    else
    {
        he(root, 0);
        cout << "\nHeight of the tree is " << count;
    }
}

int Bt::he(node *q, int c)
{
    if (q == NULL)
        return c;
    c++;
    int leftHeight = he(q->left, c);
    int rightHeight = he(q->right, c);
    count = max(count, max(leftHeight, rightHeight));
    return count;
}

void Bt::del()
{
    int x;
    cout << "\nEnter data to be deleted: ";
    cin >> x;
    root = delet(root, x);
}

node *Bt::delet(node *T, int x)
{
    if (T == NULL)
    {
        cout << "\nElement not found.";
        return NULL;
    }

    if (x < T->a)
    {
        T->left = delet(T->left, x);
    }
    else if (x > T->a)
    {
        T->right = delet(T->right, x);
    }
    else
    {
        if (T->left == NULL && T->right == NULL)
        {
            delete T;
            return NULL;
        }
        if (T->left == NULL)
        {
            node *temp = T->right;
            delete T;
            return temp;
        }
        if (T->right == NULL)
        {
            node *temp = T->left;
            delete T;
            return temp;
        }
        node *temp = findmin(T->right);
        T->a = temp->a;
        T->right = delet(T->right, temp->a);
    }
    return T;
}

node *Bt::findmin(node *T)
{
    while (T->left != NULL)
        T = T->left;
    return T;
}

void Bt::display()
{
    if (root == NULL)
    {
        cout << "\nTree does not exist.";
    }
    else
    {
        disp(root);
    }
}

void Bt::disp(node *q)
{
    if (q == NULL)
        return;
    cout << "\n*" << q->a;
    disp(q->left);
    disp(q->right);
}

int main()
{
    Bt b;
    int x;

    while (true)
    {
        cout << "\nEnter your choice:";
        cout << "\n1. Insert";
        cout << "\n2. Find";
        cout << "\n3. Search";
        cout << "\n4. Swap";
        cout << "\n5. Height";
        cout << "\n6. Delete";
        cout << "\n7. Display";
        cout << "\n8. Exit\n";
        cin >> x;

        switch (x)
        {
        case 1:
            b.insert();
            break;
        case 2:
            b.find();
            break;
        case 3:
            b.search();
            break;
        case 4:
            b.sw();
            break;
        case 5:
            b.height();
            break;
        case 6:
            b.del();
            break;
        case 7:
            b.display();
            break;
        case 8:
            exit(0);
        default:
            cout << "\nInvalid choice. Try again.";
        }
    }
    return 0;
}
