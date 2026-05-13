#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Text-Based Adventure Game in C++.
// The player can move between rooms, interact with objects and NPCs,
// and save the game progress using Object Oriented Programming and file handling.

// Room class
class Room {
public:
    string name;
    string description;
    int nextRoom;   // index of next room

    void show() {
        cout << "\nLocation: " << name << endl;
        cout << description << endl;
    }
};

// Player class
class Player {
public:
    string name;
    int currentRoom;
    bool hasKey;

    Player() {
        currentRoom = 0;
        hasKey = false;
    }
};

// Save game to file
void saveGame(Player p) {
    ofstream file("savegame.txt");
    file << p.name << endl;
    file << p.currentRoom << endl;
    file << p.hasKey << endl;
    file.close();
    cout << "Game Saved Successfully!\n";
}

// Load game from file
bool loadGame(Player &p) {
    ifstream file("savegame.txt");
    if (!file)
        return false;

    file >> p.name;
    file >> p.currentRoom;
    file >> p.hasKey;
    file.close();
    return true;
}

int main() {
    // Create rooms
    Room rooms[3];

    rooms[0].name = "Village";
    rooms[0].description = "You are in a small village. A path leads to a forest.";
    rooms[0].nextRoom = 1;

    rooms[1].name = "Forest";
    rooms[1].description = "You are in a dark forest. You see a key on the ground and a cave ahead.";
    rooms[1].nextRoom = 2;

    rooms[2].name = "Cave";
    rooms[2].description = "You are inside a cave. A treasure chest is here.";
    rooms[2].nextRoom = -1;

    Player player;
    string command;

    cout << "------ Text Based Adventure Game ------\n";
    cout << "1. New Game\n2. Load Game\nEnter choice: ";
    int choice;
    cin >> choice;

    if (choice == 2 && loadGame(player)) {
        cout << "Game Loaded! Welcome back " << player.name << endl;
    }
    else {
        cout << "Enter your name: ";
        cin >> player.name;
        player.currentRoom = 0;
    }

    cout << "\nType commands: go, look, take, save, exit\n";

    while (true) {
        rooms[player.currentRoom].show();

        // NPC message
        if (player.currentRoom == 1 && !player.hasKey) {
            cout << "NPC: 'Take the key, you will need it in the cave.'\n> ";
        }
        else {
            cout << "> ";
        }

        cin >> command;

        if (command == "look") {
            rooms[player.currentRoom].show();
        }

        else if (command == "go") {
            if (rooms[player.currentRoom].nextRoom != -1) {
                player.currentRoom = rooms[player.currentRoom].nextRoom;
            }
            else {
                cout << "You cannot go further.\n";
            }
        }

        else if (command == "take") {
            if (player.currentRoom == 1 && !player.hasKey) {
                player.hasKey = true;
                cout << "You picked up the key!\n";
            }
            else {
                cout << "Nothing to take here.\n";
            }
        }

        else if (command == "save") {
            saveGame(player);
        }

        else if (command == "exit") {
            cout << "Exiting Game...\n";
            break;
        }

        // Win condition
        if (player.currentRoom == 2) {
            if (player.hasKey) {
                cout << "\nYou opened the treasure chest using the key!\n";
                cout << "🎉 Congratulations! You Win the Game! 🎉\n";
                break;
            }
            else {
                cout << "The chest is locked. You need a key!\n";
            }
        }
    }

    return 0;
}
