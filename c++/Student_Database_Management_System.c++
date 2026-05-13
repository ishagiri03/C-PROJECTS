#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Student Database Management System in C++.
// It allows adding, viewing, searching and deleting student records using
// Object Oriented Programming and file handling.

class Student {
public:
    int roll;
    string name;
    string course;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "Roll Number: " << roll << endl;
        cout << "Name: " << name << endl;
        cout << "Course: " << course << endl;
        cout << "------------------------\n";
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    cout << "\n--- Add Student Record ---\n";
    s.input();

    file << s.roll << endl;
    file << s.name << endl;
    file << s.course << endl;

    file.close();

    cout << "Student Record Added Successfully!\n";
}

void viewStudents() {
    Student s;
    ifstream file("students.txt");

    cout << "\n--- Student Records ---\n";

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        getline(file, s.course);

        s.display();
    }

    file.close();
}

void searchStudent() {
    Student s;
    int r;
    bool found = false;

    ifstream file("students.txt");

    cout << "\nEnter Roll Number to Search: ";
    cin >> r;

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        getline(file, s.course);

        if (s.roll == r) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student Record Not Found!\n";
}

void deleteStudent() {
    Student s;
    int r;
    bool found = false;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Roll Number to Delete: ";
    cin >> r;

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        getline(file, s.course);

        if (s.roll != r) {
            temp << s.roll << endl;
            temp << s.name << endl;
            temp << s.course << endl;
        }
        else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student Record Deleted Successfully!\n";
    else
        cout << "Student Record Not Found!\n";
}

int main() {
    int choice;

    cout << "------ Student Database Management System ------\n";

    do {
        cout << "\n1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            viewStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            deleteStudent();
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
