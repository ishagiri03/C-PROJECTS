#include <iostream>
#include <fstream>
using namespace std;

// Project Description:
// This program implements a Tic-Tac-Toe game in C++ using Object Oriented Programming.
// Two players take turns placing X and O on a 3x3 board. The program checks for win,
// draw conditions and saves the game result into a file.

class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;

public:
    TicTacToe() {
        currentPlayer = 'X';

        // Initialize board with numbers
        char ch = '1';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ch++;
            }
        }
    }

    // Display the board
    void displayBoard() {
        cout << endl;
        for (int i = 0; i < 3; i++) {
            cout << " ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "---+---+---" << endl;
        }
        cout << endl;
    }

    // Switch player
    void switchPlayer() {
        if (currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }

    // Place move on board
    bool makeMove(int choice) {
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (choice < 1 || choice > 9)
            return false;

        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer;
            return true;
        }
        else {
            return false;
        }
    }

    // Check win condition
    bool checkWin() {
        // Rows & Columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer &&
                board[i][1] == currentPlayer &&
                board[i][2] == currentPlayer)
                return true;

            if (board[0][i] == currentPlayer &&
                board[1][i] == currentPlayer &&
                board[2][i] == currentPlayer)
                return true;
        }

        // Diagonals
        if (board[0][0] == currentPlayer &&
            board[1][1] == currentPlayer &&
            board[2][2] == currentPlayer)
            return true;

        if (board[0][2] == currentPlayer &&
            board[1][1] == currentPlayer &&
            board[2][0] == currentPlayer)
            return true;

        return false;
    }

    // Check draw condition
    bool checkDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O')
                    return false;
            }
        }
        return true;
    }

    // Save result to file
    void saveResult(string result) {
        ofstream file("tictactoe_result.txt", ios::app);
        file << result << endl;
        file.close();
    }

    // Play the game
    void playGame() {
        int choice;
        bool gameOver = false;

        cout << "------ Welcome to Tic-Tac-Toe Game ------\n";

        while (!gameOver) {
            displayBoard();
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> choice;

            if (!makeMove(choice)) {
                cout << "Invalid Move! Try again.\n";
                continue;
            }

            // Check for win
            if (checkWin()) {
                displayBoard();
                cout << "🎉 Player " << currentPlayer << " Wins! 🎉\n";

                string result = "Winner: Player ";
                result += currentPlayer;
                saveResult(result);

                gameOver = true;
            }
            // Check for draw
            else if (checkDraw()) {
                displayBoard();
                cout << "Game Draw!\n";

                saveResult("Result: Draw");

                gameOver = true;
            }
            else {
                switchPlayer();
            }
        }

        cout << "Game Result Saved in file: tictactoe_result.txt\n";
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}

