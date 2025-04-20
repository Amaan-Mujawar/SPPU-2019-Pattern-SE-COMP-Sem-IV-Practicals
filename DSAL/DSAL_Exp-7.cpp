/*
Amaan Mujawar
COMPUTER SE B
Roll No. 56
TSSM’s PVPIT, Bavdhan, Pune
*/
/*
LAB ASSIGNMENT 7: There are flight paths between cities. If there is a flight between city A 
and city B then there is an edge between the cities. The cost of the edge can be the time that 
flight take to reach city B from A, or the amount of fuel used for the journey. Represent this 
as a graph. The node can be represented by airport name or name of the city. Use adjacency list 
representation of the graph or use adjacency matrix representation of the graph. Check whether 
the graph is connected or not. Justify the storage representation used.
*/

#include<iostream>
#include<queue>
using namespace std;

int adj_mat[50][50] = {0};  
int visited[50] = {0};     

void dfs(int s, int n, string arr[]) {
    visited[s] = 1;
    cout << arr[s] << " ";
    for (int i = 0; i < n; i++) {
        if (adj_mat[s][i] && !visited[i]) {
            dfs(i, n, arr);
        }
    }
}

void bfs(int s, int n, string arr[]) {
    bool visited_bfs[50] = {false};
    queue<int> bfsq;

    visited_bfs[s] = true;
    bfsq.push(s);

    while (!bfsq.empty()) {
        int v = bfsq.front();
        bfsq.pop();
        cout << arr[v] << " ";

        for (int i = 0; i < n; i++) {
            if (adj_mat[v][i] && !visited_bfs[i]) {
                visited_bfs[i] = true;
                bfsq.push(i);
            }
        }
    }
}

int main() {
    int n, u;

    cout << "Enter number of cities: ";
    cin >> n;

    string cities[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter city #" << i << " (Airport Code): ";
        cin >> cities[i];
    }

    cout << "\nYour cities are:\n";
    for (int i = 0; i < n; i++) {
        cout << "City #" << i << ": " << cities[i] << endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                adj_mat[i][j] = 0;
            } else {
                cout << "Enter distance between " << cities[i] << " and " << cities[j] << ": ";
                cin >> adj_mat[i][j];
                adj_mat[j][i] = adj_mat[i][j];
            }
        }
    }

    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < n; i++)
        cout << cities[i] << "\t";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
        for (int j = 0; j < n; j++)
            cout << adj_mat[i][j] << "\t";
        cout << endl;
    }

    cout << "\nEnter starting vertex (index): ";
    cin >> u;

    cout << "\nDFS: ";
    dfs(u, n, cities);

    cout << "\nBFS: ";
    bfs(u, n, cities);

    cout << endl;
    return 0;
}