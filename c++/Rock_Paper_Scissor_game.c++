#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Project Description:
// This program implements the Rock Paper Scissor game between user and computer.
// The user selects Rock, Paper or Scissor and the computer generates a random choice.
// Based on the rules, the winner is displayed.

int main() {
    int userChoice, computerChoice;

    // Initialize random number generator
    srand(time(0));

    cout << "------ Rock Paper Scissor Game ------\n";
    cout << "Enter your choice:\n";
    cout << "1. Rock\n";
    cout << "2. Paper\n";
    cout << "3. Scissor\n";
    cin >> userChoice;

    // Generate random choice for computer (1 to 3)
    computerChoice = (rand() % 3) + 1;

    // Display user choice
    if (userChoice == 1)
        cout << "You chose: Rock\n";
    else if (userChoice == 2)
        cout << "You chose: Paper\n";
    else if (userChoice == 3)
        cout << "You chose: Scissor\n";
    else {
        cout << "Invalid Choice!";
        return 0;
    }

    // Display computer choice
    if (computerChoice == 1)
        cout << "Computer chose: Rock\n";
    else if (computerChoice == 2)
        cout << "Computer chose: Paper\n";
    else
        cout << "Computer chose: Scissor\n";

    // Decide the winner
    cout << "\nResult: ";

    if (userChoice == computerChoice) {
        cout << "Match Draw!";
    }
    else if ((userChoice == 1 && computerChoice == 3) ||
             (userChoice == 2 && computerChoice == 1) ||
             (userChoice == 3 && computerChoice == 2)) {
        cout << "Congratulations! You Win!";
    }
    else {
        cout << "Computer Wins!";
    }

    return 0;
}
