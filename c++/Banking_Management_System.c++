#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Banking Management System in C++ using
// Object Oriented Programming and file handling. It allows creating accounts,
// depositing money, withdrawing money, transferring money and viewing account details.

class Account {
public:
    int accNo;
    string name;
    float balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void display() {
        cout << "Account Number: " << accNo << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Balance: " << balance << endl;
        cout << "---------------------------\n";
    }
};

// Save account to file
void saveAccount(Account a) {
    ofstream file("bank.txt", ios::app);

    file << a.accNo << endl;
    file << a.name << endl;
    file << a.balance << endl;

    file.close();
}

// Create new account
void newAccount() {
    Account a;
    cout << "\n--- Create New Account ---\n";
    a.createAccount();
    saveAccount(a);

    cout << "Account Created Successfully!\n";
}

// View all accounts
void viewAccounts() {
    Account a;
    ifstream file("bank.txt");

    cout << "\n--- All Bank Accounts ---\n";

    while (file >> a.accNo) {
        file.ignore();
        getline(file, a.name);
        file >> a.balance;

        a.display();
    }

    file.close();
}

// Deposit money
void deposit() {
    Account a;
    int acc;
    float amount;
    bool found = false;

    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Account Number: ";
    cin >> acc;
    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    while (file >> a.accNo) {
        file.ignore();
        getline(file, a.name);
        file >> a.balance;

        if (a.accNo == acc) {
            a.balance += amount;
            found = true;
            cout << "Amount Deposited Successfully!\n";
        }

        temp << a.accNo << endl;
        temp << a.name << endl;
        temp << a.balance << endl;
    }

    file.close();
    temp.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (!found)
        cout << "Account Not Found!\n";
}

// Withdraw money
void withdraw() {
    Account a;
    int acc;
    float amount;
    bool found = false;

    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Account Number: ";
    cin >> acc;
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    while (file >> a.accNo) {
        file.ignore();
        getline(file, a.name);
        file >> a.balance;

        if (a.accNo == acc) {
            if (a.balance >= amount) {
                a.balance -= amount;
                found = true;
                cout << "Amount Withdrawn Successfully!\n";
            }
            else {
                cout << "Insufficient Balance!\n";
                found = true;
            }
        }

        temp << a.accNo << endl;
        temp << a.name << endl;
        temp << a.balance << endl;
    }

    file.close();
    temp.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (!found)
        cout << "Account Not Found!\n";
}

// Search account
void searchAccount() {
    Account a;
    int acc;
    bool found = false;

    ifstream file("bank.txt");

    cout << "\nEnter Account Number to Search: ";
    cin >> acc;

    while (file >> a.accNo) {
        file.ignore();
        getline(file, a.name);
        file >> a.balance;

        if (a.accNo == acc) {
            cout << "\nAccount Found:\n";
            a.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Account Not Found!\n";
}

// Transfer money
void transferMoney() {
    Account a;
    int fromAcc, toAcc;
    float amount;
    bool foundFrom = false, foundTo = false;

    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Sender Account Number: ";
    cin >> fromAcc;
    cout << "Enter Receiver Account Number: ";
    cin >> toAcc;
    cout << "Enter Amount to Transfer: ";
    cin >> amount;

    while (file >> a.accNo) {
        file.ignore();
        getline(file, a.name);
        file >> a.balance;

        if (a.accNo == fromAcc) {
            if (a.balance >= amount) {
                a.balance -= amount;
                foundFrom = true;
            }
            else {
                cout << "Insufficient Balance in Sender Account!\n";
                foundFrom = true;
            }
        }
        else if (a.accNo == toAcc) {
            a.balance += amount;
            foundTo = true;
        }

        temp << a.accNo << endl;
        temp << a.name << endl;
        temp << a.balance << endl;
    }

    file.close();
    temp.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (foundFrom && foundTo)
        cout << "Money Transferred Successfully!\n";
    else
        cout << "Transfer Failed! Account not found.\n";
}

int main() {
    int choice;

    cout << "------ Banking Management System ------\n";

    do {
        cout << "\n1. Create New Account\n";
        cout << "2. View All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transfer Money\n";
        cout << "6. Search Account\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            newAccount();
            break;
        case 2:
            viewAccounts();
            break;
        case 3:
            deposit();
            break;
        case 4:
            withdraw();
            break;
        case 5:
            transferMoney();
            break;
        case 6:
            searchAccount();
            break;
        case 0:
            cout << "Exiting Banking System...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}
