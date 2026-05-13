#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Project Description:
// This program implements a simple Chess Game with AI in C++ using Object Oriented Programming.
// It displays an 8x8 chess board, allows player moves and computer (AI) moves.
// The AI selects random valid moves. The game ends when a king is captured.

class Chess {
private:
    char board[8][8];
    bool playerTurn;   // true = player, false = computer

public:
    Chess() {
        playerTurn = true;
        initializeBoard();
    }

    // Initialize chess board
    void initializeBoard() {
        char initial[8][8] = {
            {'r','n','b','q','k','b','n','r'},
            {'p','p','p','p','p','p','p','p'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'P','P','P','P','P','P','P','P'},
            {'R','N','B','Q','K','B','N','R'}
        };

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board[i][j] = initial[i][j];
    }

    // Display board
    void displayBoard() {
        cout << "\n  0 1 2 3 4 5 6 7\n";
        for (int i = 0; i < 8; i++) {
            cout << i << " ";
            for (int j = 0; j < 8; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Check if king still exists
    bool kingExists(char king) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] == king)
                    return true;
        return false;
    }

    // Make a move
    void movePiece(int x1, int y1, int x2, int y2) {
        board[x2][y2] = board[x1][y1];
        board[x1][y1] = '.';
    }

    // Player move
    void playerMove() {
        int x1, y1, x2, y2;

        cout << "\nEnter your move (fromX fromY toX toY): ";
        cin >> x1 >> y1 >> x2 >> y2;

        // Basic validation
        if (board[x1][y1] >= 'A' && board[x1][y1] <= 'Z') {
            movePiece(x1, y1, x2, y2);
        }
        else {
            cout << "Invalid Move! Try again.\n";
            playerMove();
        }
    }

    // Computer (AI) move - random move
    void computerMove() {
        int x1, y1, x2, y2;

        srand(time(0));

        while (true) {
            x1 = rand() % 8;
            y1 = rand() % 8;
            x2 = rand() % 8;
            y2 = rand() % 8;

            // AI moves only lowercase pieces (computer side)
            if (board[x1][y1] >= 'a' && board[x1][y1] <= 'z') {
                movePiece(x1, y1, x2, y2);
                cout << "\nComputer moved from (" << x1 << "," << y1 
                     << ") to (" << x2 << "," << y2 << ")\n";
                break;
            }
        }
    }

    // Main game loop
    void play() {
        cout << "------ Welcome to Chess Game with AI ------\n";
        cout << "You are WHITE (Capital Letters)\n";
        cout << "Computer is BLACK (Small Letters)\n";

        while (true) {
            displayBoard();

            // Player turn
            cout << "\nYour Turn:\n";
            playerMove();

            // Check if black king is captured
            if (!kingExists('k')) {
                displayBoard();
                cout << "\n🎉 You Win! Black King is captured. 🎉\n";
                break;
            }

            // Computer turn
            cout << "\nComputer's Turn...\n";
            computerMove();

            // Check if white king is captured
            if (!kingExists('K')) {
                displayBoard();
                cout << "\n😢 You Lose! White King is captured. 😢\n";
                break;
            }
        }
    }
};

int main() {
    Chess game;
    game.play();
    return 0;
}
