#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Login and Registration System in C++.
// It allows new users to register by saving their username and password in a file
// and existing users to login by verifying their credentials from the file.

void registerUser() {
    string username, password;

    cout << "\n--- User Registration ---\n";
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    // Save data into file
    ofstream file("users.txt", ios::app);

    file << username << " " << password << endl;

    file.close();

    cout << "Registration Successful!\n";
}

bool loginUser() {
    string username, password, u, p;

    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");

    // Check credentials from file
    while (file >> u >> p) {
        if (u == username && p == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

int main() {
    int choice;

    cout << "------ Login and Registration System ------\n";

    do {
        cout << "\n1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;

        case 2:
            if (loginUser()) {
                cout << "Login Successful! Welcome User.\n";
            }
            else {
                cout << "Login Failed! Invalid Username or Password.\n";
            }
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
