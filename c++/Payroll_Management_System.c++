#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Project Description:
// This program implements a Payroll Management System in C++ using
// Object Oriented Programming, STL (vector), searching and sorting algorithms.
// It manages employee records, calculates salary, deductions and generates reports.

class Employee {
public:
    int id;
    string name;
    int hoursWorked;
    float hourlyRate;

    float grossSalary;
    float tax;
    float pf;
    float netSalary;

    void input() {
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Hours Worked: ";
        cin >> hoursWorked;
        cout << "Enter Hourly Rate: ";
        cin >> hourlyRate;
    }

    void calculateSalary() {
        grossSalary = hoursWorked * hourlyRate;
        tax = grossSalary * 0.10;   // 10% Tax
        pf  = grossSalary * 0.05;   // 5% Provident Fund
        netSalary = grossSalary - (tax + pf);
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Hours Worked: " << hoursWorked << endl;
        cout << "Hourly Rate: " << hourlyRate << endl;
        cout << "Gross Salary: " << grossSalary << endl;
        cout << "Tax: " << tax << endl;
        cout << "PF: " << pf << endl;
        cout << "Net Salary: " << netSalary << endl;
        cout << "---------------------------\n";
    }
};

// Save employee to file
void saveEmployee(Employee e) {
    ofstream file("payroll.txt", ios::app);

    file << e.id << endl;
    file << e.name << endl;
    file << e.hoursWorked << endl;
    file << e.hourlyRate << endl;
    file << e.grossSalary << endl;
    file << e.tax << endl;
    file << e.pf << endl;
    file << e.netSalary << endl;

    file.close();
}

// Load all employees from file
vector<Employee> loadEmployees() {
    vector<Employee> list;
    Employee e;
    ifstream file("payroll.txt");

    while (file >> e.id) {
        file.ignore();
        getline(file, e.name);
        file >> e.hoursWorked;
        file >> e.hourlyRate;
        file >> e.grossSalary;
        file >> e.tax;
        file >> e.pf;
        file >> e.netSalary;

        list.push_back(e);
    }

    file.close();
    return list;
}

// Add new employee
void addEmployee() {
    Employee e;
    cout << "\n--- Add Employee ---\n";
    e.input();
    e.calculateSalary();
    saveEmployee(e);

    cout << "Employee Added Successfully!\n";
}

// View all employees
void viewEmployees() {
    vector<Employee> list = loadEmployees();

    cout << "\n--- Payroll Report ---\n";

    for (auto &e : list) {
        e.display();
    }
}

// Search employee by ID
void searchEmployee() {
    vector<Employee> list = loadEmployees();
    int id;
    bool found = false;

    cout << "\nEnter Employee ID to Search: ";
    cin >> id;

    for (auto &e : list) {
        if (e.id == id) {
            cout << "\nEmployee Found:\n";
            e.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Employee Not Found!\n";
}

// Sort employees by Net Salary
void sortBySalary() {
    vector<Employee> list = loadEmployees();

    sort(list.begin(), list.end(), [](Employee a, Employee b) {
        return a.netSalary > b.netSalary;
    });

    cout << "\n--- Employees Sorted by Net Salary (High to Low) ---\n";

    for (auto &e : list) {
        e.display();
    }
}

int main() {
    int choice;

    cout << "------ Payroll Management System ------\n";

    do {
        cout << "\n1. Add Employee\n";
        cout << "2. View Payroll Report\n";
        cout << "3. Search Employee\n";
        cout << "4. Sort Employees by Salary\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            viewEmployees();
            break;
        case 3:
            searchEmployee();
            break;
        case 4:
            sortBySalary();
            break;
        case 0:
            cout << "Exiting Program...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}
