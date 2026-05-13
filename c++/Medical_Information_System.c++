#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Medical Information System in C++.
// It stores and manages patient records, provides doctor login authentication
// and uses basic encryption to secure passwords and patient data.

// Simple encryption function (Caesar Cipher)
string encrypt(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = text[i] + 3;
    }
    return text;
}

// Simple decryption function
string decrypt(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = text[i] - 3;
    }
    return text;
}

// Doctor login authentication
bool login() {
    string username, password;
    string u = "doctor";
    string p = encrypt("1234");   // encrypted password

    cout << "\n--- Doctor Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (username == u && encrypt(password) == p) {
        cout << "Login Successful!\n";
        return true;
    }
    else {
        cout << "Invalid Login!\n";
        return false;
    }
}

// Patient class (OOPS)
class Patient {
public:
    int id;
    string name;
    int age;
    string disease;
    string labResult;

    void input() {
        cout << "Enter Patient ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Disease: ";
        getline(cin, disease);
        cout << "Enter Lab Result: ";
        getline(cin, labResult);
    }

    void display() {
        cout << "Patient ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Disease: " << disease << endl;
        cout << "Lab Result: " << labResult << endl;
        cout << "---------------------------\n";
    }
};

// Add patient record
void addPatient() {
    Patient p;
    ofstream file("patients.txt", ios::app);

    cout << "\n--- Add Patient Record ---\n";
    p.input();

    // Encrypt sensitive data before saving
    file << p.id << endl;
    file << encrypt(p.name) << endl;
    file << p.age << endl;
    file << encrypt(p.disease) << endl;
    file << encrypt(p.labResult) << endl;

    file.close();

    cout << "Patient Record Saved Successfully!\n";
}

// View all patient records
void viewPatients() {
    Patient p;
    ifstream file("patients.txt");

    cout << "\n--- Patient Records ---\n";

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.age;
        file.ignore();
        getline(file, p.disease);
        getline(file, p.labResult);

        // Decrypt data before displaying
        p.name = decrypt(p.name);
        p.disease = decrypt(p.disease);
        p.labResult = decrypt(p.labResult);

        p.display();
    }

    file.close();
}

// Search patient by ID
void searchPatient() {
    Patient p;
    int pid;
    bool found = false;

    ifstream file("patients.txt");

    cout << "\nEnter Patient ID to Search: ";
    cin >> pid;

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.age;
        file.ignore();
        getline(file, p.disease);
        getline(file, p.labResult);

        if (p.id == pid) {
            p.name = decrypt(p.name);
            p.disease = decrypt(p.disease);
            p.labResult = decrypt(p.labResult);

            cout << "\nPatient Found:\n";
            p.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Patient Record Not Found!\n";
}

int main() {
    int choice;

    cout << "------ Medical Information System ------\n";

    // Login required
    if (!login())
        return 0;

    do {
        cout << "\n1. Add Patient Record\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            viewPatients();
            break;
        case 3:
            searchPatient();
            break;
        case 0:
            cout << "Exiting System...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}
