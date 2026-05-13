#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// Project Description:
// This program implements a classic Snake Game in C++ for Windows.
// It uses conio.h and windows.h for keyboard input and timing control.

class Snake {
public:
    int x, y;
    int tailX[100], tailY[100];
    int nTail;

    Snake() {
        x = 10;
        y = 10;
        nTail = 0;
    }
};

class Food {
public:
    int x, y;

    void generate() {
        x = rand() % 18 + 1;   // avoid walls
        y = rand() % 18 + 1;
    }
};

bool gameOver;
char dir;
int score = 0;
int level = 1;

Snake snake;
Food food;

// Draw game board
void draw() {
    system("cls");

    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 22; j++) {
            if (i == 0 || i == 21 || j == 0 || j == 21)
                cout << "#";
            else if (i == snake.y && j == snake.x)
                cout << "O";
            else if (i == food.y && j == food.x)
                cout << "F";
            else {
                bool printTail = false;
                for (int k = 0; k < snake.nTail; k++) {
                    if (snake.tailX[k] == j && snake.tailY[k] == i) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    cout << "Score: " << score << "   Level: " << level << endl;
    cout << "Controls: W A S D | X = Exit\n";
}

// Keyboard input
void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
        case 'a': dir = 'L'; break;
        case 'd': dir = 'R'; break;
        case 'w': dir = 'U'; break;
        case 's': dir = 'D'; break;
        case 'x': gameOver = true; break;
        }
    }
}

// Game logic
void logic() {
    // Move tail
    int prevX = snake.tailX[0];
    int prevY = snake.tailY[0];
    snake.tailX[0] = snake.x;
    snake.tailY[0] = snake.y;

    for (int i = 1; i < snake.nTail; i++) {
        int prev2X = snake.tailX[i];
        int prev2Y = snake.tailY[i];
        snake.tailX[i] = prevX;
        snake.tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move head
    switch (dir) {
    case 'L': snake.x--; break;
    case 'R': snake.x++; break;
    case 'U': snake.y--; break;
    case 'D': snake.y++; break;
    }

    // Wall collision
    if (snake.x <= 0 || snake.x >= 21 || snake.y <= 0 || snake.y >= 21)
        gameOver = true;

    // Food collision
    if (snake.x == food.x && snake.y == food.y) {
        score += 10;
        snake.nTail++;
        food.generate();

        if (score % 50 == 0)
            level++;
    }
}

int main() {
    srand(time(0));   // random seed

    gameOver = false;
    dir = 'R';
    food.generate();

    cout << "------ Welcome to Snake Game (Windows) ------\n";
    cout << "Press any key to start...";
    _getch();

    while (!gameOver) {
        draw();
        input();
        logic();

        int speed = 150 - (level * 10);
        if (speed < 40) speed = 40;   // prevent crash
        Sleep(speed);
    }

    system("cls");
    cout << "Game Over!\n";
    cout << "Final Score: " << score << endl;
    cout << "Final Level: " << level << endl;

    return 0;
}
