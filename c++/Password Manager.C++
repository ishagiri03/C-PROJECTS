#include <windows.h>
#include <fstream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Password Manager using C++ and Windows GUI.
// Usernames and passwords are encrypted before saving to file and decrypted on demand.
// A master password is required to access the application.

#define ID_ADD 1
#define ID_SHOW 2

string MASTER_PASSWORD = "admin123";
string FILE_NAME = "passwords.dat";

// Simple XOR Encryption / Decryption
string encryptDecrypt(string data) {
    char key = 'K';  // encryption key
    for (int i = 0; i < data.size(); i++) {
        data[i] = data[i] ^ key;
    }
    return data;
}

// Save credentials
void saveData(string user, string pass) {
    ofstream file(FILE_NAME, ios::app);
    file << encryptDecrypt(user) << "|" << encryptDecrypt(pass) << endl;
    file.close();
}

// Load credentials
string loadData() {
    ifstream file(FILE_NAME);
    string line, result = "";

    while (getline(file, line)) {
        int pos = line.find("|");
        string user = encryptDecrypt(line.substr(0, pos));
        string pass = encryptDecrypt(line.substr(pos + 1));
        result += "User: " + user + "  Password: " + pass + "\n";
    }

    file.close();
    return result;
}

// Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    static HWND hUser, hPass;

    switch (msg) {
    case WM_CREATE:
        CreateWindow("STATIC", "Username:", WS_VISIBLE | WS_CHILD,
                     20, 20, 80, 20, hwnd, NULL, NULL, NULL);

        hUser = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100, 20, 150, 20, hwnd, NULL, NULL, NULL);

        CreateWindow("STATIC", "Password:", WS_VISIBLE | WS_CHILD,
                     20, 50, 80, 20, hwnd, NULL, NULL, NULL);

        hPass = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
                             100, 50, 150, 20, hwnd, NULL, NULL, NULL);

        CreateWindow("BUTTON", "Add", WS_VISIBLE | WS_CHILD,
                     20, 90, 80, 25, hwnd, (HMENU)ID_ADD, NULL, NULL);

        CreateWindow("BUTTON", "Show", WS_VISIBLE | WS_CHILD,
                     120, 90, 80, 25, hwnd, (HMENU)ID_SHOW, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wp) == ID_ADD) {
            char user[50], pass[50];
            GetWindowText(hUser, user, 50);
            GetWindowText(hPass, pass, 50);

            saveData(user, pass);
            MessageBox(hwnd, "Data Saved Successfully!", "Success", MB_OK);
        }

        if (LOWORD(wp) == ID_SHOW) {
            string data = loadData();
            MessageBox(hwnd, data.c_str(), "Stored Passwords", MB_OK);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

// Login Window
bool authenticate() {
    char input[50];
    cout << "Enter Master Password: ";
    cin >> input;
    return input == MASTER_PASSWORD;
}

// Main Function
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    if (!authenticate()) {
        MessageBox(NULL, "Invalid Master Password!", "Access Denied", MB_OK);
        return 0;
    }

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "PasswordManager";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("PasswordManager", "Password Manager",
                             WS_OVERLAPPEDWINDOW,
                             300, 200, 300, 180,
                             NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
