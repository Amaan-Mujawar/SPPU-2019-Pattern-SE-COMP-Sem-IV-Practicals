/*
Amaan Mujawar
COMPUTER SE B
Roll No. 56
TSSM’s PVPIT, Bavdhan, Pune
*/
/*
LAB ASSIGNMENT 8: Given sequence k = k1 < … <kn of n sorted keys, with a search probability pi 
for each key ki . Build the Binary search tree that has the least search cost given the access 
probability for each key?
*/


#include<iostream>
using namespace std;

void con_obst();
void print(int, int);

float a[20], b[20], wt[20][20], c[20][20];
int r[20][20], n;

int main() {
    cout << "\n******* PROGRAM FOR OBST *******\n";
    cout << "\nEnter the number of keys: ";
    cin >> n;

    cout << "\nEnter the probabilities for successful search (p[i]):\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "] = ";
        cin >> a[i];
    }

    cout << "\nEnter the probabilities for unsuccessful search (q[i]):\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "] = ";
        cin >> b[i];
    }

    con_obst();
    print(0, n);
    cout << endl;

    return 0;
}

void con_obst() {
    int i, j, k, l;

    for (i = 0; i < n; i++) {
        c[i][i] = 0.0;
        r[i][i] = 0;
        wt[i][i] = b[i];

        wt[i][i + 1] = b[i] + b[i + 1] + a[i + 1];
        c[i][i + 1] = wt[i][i + 1];
        r[i][i + 1] = i + 1;
    }

    c[n][n] = 0.0;
    r[n][n] = 0;
    wt[n][n] = b[n];

    for (i = 2; i <= n; i++) {
        for (j = 0; j <= n - i; j++) {
            wt[j][j + i] = wt[j][j + i - 1] + a[j + i] + b[j + i];
            c[j][j + i] = 9999; 

            for (l = j + 1; l <= j + i; l++) {
                float cost = c[j][l - 1] + c[l][j + i];
                if (cost < c[j][j + i]) {
                    c[j][j + i] = cost;
                    r[j][j + i] = l;
                }
            }

            c[j][j + i] += wt[j][j + i];
        }
    }

    cout << "\nOptimal BST constructed.";
    cout << "\nTotal weight (w[0][" << n << "]) = " << wt[0][n];
    cout << "\nMinimum cost (c[0][" << n << "]) = " << c[0][n];
    cout << "\nRoot of OBST (r[0][" << n << "]) = " << r[0][n] << endl;
}

void print(int l1, int r1) {
    if (l1 >= r1)
        return;

    int root = r[l1][r1];
    if (r[l1][root - 1] != 0)
        cout << "\nLeft child of " << root << " is " << r[l1][root - 1];
    if (r[root][r1] != 0)
        cout << "\nRight child of " << root << " is " << r[root][r1];

    print(l1, root - 1);
    print(root, r1);
}
