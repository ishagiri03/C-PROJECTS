#include <iostream>
#include <string>
using namespace std;

// Project Description:
// This program implements a simple Hangman Game in C++ using Object Oriented Programming.
// The player guesses a hidden word letter by letter within limited attempts.
// The program tracks progress and displays hangman stages.

class Hangman {
private:
    string secretWord;
    string guessedWord;
    int attempts;

public:
    Hangman(string word) {
        secretWord = word;
        guessedWord = string(word.length(), '_');
        attempts = 6;   // Total chances
    }

    // Display current progress
    void displayWord() {
        cout << "\nWord: ";
        for (char c : guessedWord)
            cout << c << " ";
        cout << endl;
    }

    // Display hangman figure (text based)
    void displayHangman() {
        cout << "\nAttempts left: " << attempts << endl;

        switch (attempts) {
        case 6:
            cout << " \n \n \n \n";
            break;
        case 5:
            cout << "  O\n \n \n";
            break;
        case 4:
            cout << "  O\n  |\n";
            break;
        case 3:
            cout << "  O\n /|\n";
            break;
        case 2:
            cout << "  O\n /|\\\n";
            break;
        case 1:
            cout << "  O\n /|\\\n /\n";
            break;
        case 0:
            cout << "  O\n /|\\\n / \\\n";
            break;
        }
    }

    // Guess a letter
    bool guessLetter(char ch) {
        bool correct = false;

        for (int i = 0; i < secretWord.length(); i++) {
            if (secretWord[i] == ch) {
                guessedWord[i] = ch;
                correct = true;
            }
        }

        if (!correct) {
            attempts--;
        }

        return correct;
    }

    // Check win condition
    bool isWon() {
        return guessedWord == secretWord;
    }

    // Check lose condition
    bool isLost() {
        return attempts == 0;
    }

    void play() {
        char ch;

        cout << "------ Welcome to Hangman Game ------\n";

        while (!isWon() && !isLost()) {
            displayHangman();
            displayWord();

            cout << "Enter a letter: ";
            cin >> ch;

            if (guessLetter(ch)) {
                cout << "Correct Guess!\n";
            }
            else {
                cout << "Wrong Guess!\n";
            }
        }

        if (isWon()) {
            cout << "\nCongratulations! You guessed the word: " << secretWord << endl;
        }
        else {
            displayHangman();
            cout << "\nGame Over! The word was: " << secretWord << endl;
        }
    }
};

int main() {
    // Secret word (can be randomized later)
    Hangman game("computer");
    game.play();

    return 0;
}
