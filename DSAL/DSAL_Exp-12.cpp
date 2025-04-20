/* 
Amaan Mujawar 
COMPUTER SE B 
Roll No. 56 
TSSM’s PVPIT, Bavdhan, Pune 
*/ 
/* 
LAB ASSIGNMENT 12: Company maintains employee information as employee ID, name, 
designation and salary. Allow user to add, delete information of employee. Display 
information of particular employee. If employee does not exist an appropriate message 
is displayed. If it is, then the system displays the employee details. Use index 
sequential file to maintain the data. 
*/ 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

const string fileName = "Employee.dat";

class Employee {
private:
    int EmpID;
    string EmpName, Post, Department;
    float Salary;

public:
    void ReadData();
    void DisplayRecord() const;
    int GetID() const;
    string GetDepartment() const;

    // Binary serialization functions
    void WriteToFile(ofstream& out) const;
    void ReadFromFile(ifstream& in);
};

void Employee::ReadData() {
    cout << "\nEnter Employee ID: ";
    cin >> EmpID;
    cin.ignore();

    cout << "Enter Employee Name: ";
    getline(cin, EmpName);

    cout << "Enter Post: ";
    getline(cin, Post);

    cout << "Enter Department: ";
    getline(cin, Department);

    cout << "Enter Salary: ";
    cin >> Salary;
}

void Employee::DisplayRecord() const {
    cout << setw(5) << EmpID
         << setw(15) << EmpName
         << setw(15) << Post
         << setw(15) << Department
         << setw(10) << Salary << endl;
}

int Employee::GetID() const {
    return EmpID;
}

string Employee::GetDepartment() const {
    return Department;
}

void Employee::WriteToFile(ofstream& out) const {
    out.write((char*)&EmpID, sizeof(EmpID));
    size_t len;

    len = EmpName.size();
    out.write((char*)&len, sizeof(len));
    out.write(EmpName.c_str(), len);

    len = Post.size();
    out.write((char*)&len, sizeof(len));
    out.write(Post.c_str(), len);

    len = Department.size();
    out.write((char*)&len, sizeof(len));
    out.write(Department.c_str(), len);

    out.write((char*)&Salary, sizeof(Salary));
}

void Employee::ReadFromFile(ifstream& in) {
    size_t len;
    char buffer[100];

    in.read((char*)&EmpID, sizeof(EmpID));

    in.read((char*)&len, sizeof(len));
    in.read(buffer, len); buffer[len] = '\0';
    EmpName = buffer;

    in.read((char*)&len, sizeof(len));
    in.read(buffer, len); buffer[len] = '\0';
    Post = buffer;

    in.read((char*)&len, sizeof(len));
    in.read(buffer, len); buffer[len] = '\0';
    Department = buffer;

    in.read((char*)&Salary, sizeof(Salary));
}

void AddEmployee() {
    Employee emp;
    emp.ReadData();

    // Check if ID exists
    ifstream fin(fileName, ios::binary);
    Employee temp;
    bool exists = false;

    while (fin.peek() != EOF && fin) {
        temp.ReadFromFile(fin);
        if (temp.GetID() == emp.GetID()) {
            exists = true;
            break;
        }
    }
    fin.close();

    if (exists) {
        cout << "Employee ID already exists. Try another.\n";
        return;
    }

    ofstream fout(fileName, ios::binary | ios::app);
    emp.WriteToFile(fout);
    fout.close();
    cout << "Employee added successfully!\n";
}

void SearchEmployee() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    ifstream fin(fileName, ios::binary);
    Employee e;
    bool found = false;

    while (fin.peek() != EOF && fin) {
        e.ReadFromFile(fin);
        if (e.GetID() == id) {
            cout << "\nEmployee Found:\n";
            cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post"
                 << setw(15) << "Department" << setw(10) << "Salary" << endl;
            e.DisplayRecord();
            found = true;
            break;
        }
    }
    fin.close();

    if (!found)
        cout << "Employee with ID " << id << " not found.\n";
}

void ListByDepartment() {
    string dept;
    cout << "Enter department: ";
    cin.ignore();
    getline(cin, dept);

    ifstream fin(fileName, ios::binary);
    Employee e;
    bool found = false;

    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post"
         << setw(15) << "Department" << setw(10) << "Salary" << endl;

    while (fin.peek() != EOF && fin) {
        e.ReadFromFile(fin);
        if (e.GetDepartment() == dept) {
            e.DisplayRecord();
            found = true;
        }
    }
    fin.close();

    if (!found)
        cout << "No employees found in " << dept << " department.\n";
}

void DisplayAll() {
    ifstream fin(fileName, ios::binary);
    Employee e;
    int count = 0;

    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post"
         << setw(15) << "Department" << setw(10) << "Salary" << endl;

    while (fin.peek() != EOF && fin) {
        e.ReadFromFile(fin);
        e.DisplayRecord();
        count++;
    }
    fin.close();

    cout << count << " record(s) found.\n";
}

void UpdateEmployee() {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    ifstream fin(fileName, ios::binary);
    vector<Employee> employees;
    Employee e;
    bool found = false;

    while (fin.peek() != EOF && fin) {
        e.ReadFromFile(fin);
        if (e.GetID() == id) {
            cout << "Current record:\n";
            e.DisplayRecord();
            cout << "\nEnter new details:\n";
            e.ReadData();
            found = true;
        }
        employees.push_back(e);
    }
    fin.close();

    if (!found) {
        cout << "Employee not found.\n";
        return;
    }

    ofstream fout(fileName, ios::binary);
    for (const auto& emp : employees)
        emp.WriteToFile(fout);
    fout.close();

    cout << "Record updated successfully.\n";
}

void DeleteEmployee() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream fin(fileName, ios::binary);
    vector<Employee> employees;
    Employee e;
    bool found = false;

    while (fin.peek() != EOF && fin) {
        e.ReadFromFile(fin);
        if (e.GetID() != id) {
            employees.push_back(e);
        } else {
            found = true;
        }
    }
    fin.close();

    if (!found) {
        cout << "Employee not found.\n";
        return;
    }

    ofstream fout(fileName, ios::binary);
    for (const auto& emp : employees)
        emp.WriteToFile(fout);
    fout.close();

    cout << "Record deleted successfully.\n";
}

int main() {
    char choice;

    do {
        cout << "\n====== Employee Management Menu ======\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee by ID\n";
        cout << "3. List Employees by Department\n";
        cout << "4. Display All Employees\n";
        cout << "5. Update Employee\n";
        cout << "6. Delete Employee\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': AddEmployee(); break;
            case '2': SearchEmployee(); break;
            case '3': ListByDepartment(); break;
            case '4': DisplayAll(); break;
            case '5': UpdateEmployee(); break;
            case '6': DeleteEmployee(); break;
            case '7': cout << "Exiting...\n"; exit(0);
            default: cout << "Invalid choice.\n";
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
