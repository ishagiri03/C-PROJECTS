#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Inventory Management System in C++ using
// Object Oriented Programming and file handling. It allows the user to add,
// view, search, update and delete product records from the inventory.

class Product {
public:
    int id;
    string name;
    int quantity;
    float price;

    void input() {
        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: ";
        cin >> price;
    }

    void display() {
        cout << "Product ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Price: " << price << endl;
        cout << "--------------------------\n";
    }
};

// Add new product
void addProduct() {
    Product p;
    ofstream file("inventory.txt", ios::app);

    cout << "\n--- Add Product ---\n";
    p.input();

    file << p.id << endl;
    file << p.name << endl;
    file << p.quantity << endl;
    file << p.price << endl;

    file.close();

    cout << "Product Added Successfully!\n";
}

// View all products
void viewProducts() {
    Product p;
    ifstream file("inventory.txt");

    cout << "\n--- Inventory Records ---\n";

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.quantity;
        file >> p.price;

        p.display();
    }

    file.close();
}

// Search product by ID
void searchProduct() {
    Product p;
    int pid;
    bool found = false;

    ifstream file("inventory.txt");

    cout << "\nEnter Product ID to Search: ";
    cin >> pid;

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.quantity;
        file >> p.price;

        if (p.id == pid) {
            cout << "\nProduct Found:\n";
            p.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Product Not Found!\n";
}

// Update product record
void updateProduct() {
    Product p;
    int pid;
    bool found = false;

    ifstream file("inventory.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Product ID to Update: ";
    cin >> pid;

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.quantity;
        file >> p.price;

        if (p.id == pid) {
            cout << "\nEnter New Details:\n";
            p.input();
            found = true;
        }

        temp << p.id << endl;
        temp << p.name << endl;
        temp << p.quantity << endl;
        temp << p.price << endl;
    }

    file.close();
    temp.close();

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (found)
        cout << "Product Updated Successfully!\n";
    else
        cout << "Product Not Found!\n";
}

// Delete product
void deleteProduct() {
    Product p;
    int pid;
    bool found = false;

    ifstream file("inventory.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Product ID to Delete: ";
    cin >> pid;

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.quantity;
        file >> p.price;

        if (p.id != pid) {
            temp << p.id << endl;
            temp << p.name << endl;
            temp << p.quantity << endl;
            temp << p.price << endl;
        }
        else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (found)
        cout << "Product Deleted Successfully!\n";
    else
        cout << "Product Not Found!\n";
}

int main() {
    int choice;

    cout << "------ Inventory Management System ------\n";

    do {
        cout << "\n1. Add Product\n";
        cout << "2. View All Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            viewProducts();
            break;
        case 3:
            searchProduct();
            break;
        case 4:
            updateProduct();
            break;
        case 5:
            deleteProduct();
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
