#include <SDL.h>
#include <iostream>
#include <ctime>
using namespace std;

// Project Description:
// This program implements a Minesweeper Game using C++ and SDL2.
// The game uses a 9x9 grid with randomly placed mines.
// Numbers indicate nearby mines and clicking on a mine ends the game.

const int GRID = 9;
const int CELL_SIZE = 50;
const int WINDOW_SIZE = GRID * CELL_SIZE;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int board[GRID][GRID];       // -1 = mine, >=0 = number
bool revealed[GRID][GRID];
bool gameOver = false;

// Initialize board
void initBoard() {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < GRID; i++)
        for (int j = 0; j < GRID; j++) {
            board[i][j] = 0;
            revealed[i][j] = false;
        }

    // Place mines
    int mines = 10;
    while (mines) {
        int x = rand() % GRID;
        int y = rand() % GRID;
        if (board[x][y] != -1) {
            board[x][y] = -1;
            mines--;
        }
    }

    // Calculate numbers
    for (int i = 0; i < GRID; i++) {
        for (int j = 0; j < GRID; j++) {
            if (board[i][j] == -1) continue;

            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = i + dx, ny = j + dy;
                    if (nx >= 0 && ny >= 0 && nx < GRID && ny < GRID)
                        if (board[nx][ny] == -1)
                            count++;
                }
            }
            board[i][j] = count;
        }
    }
}

// Draw grid
void drawGrid() {
    for (int i = 0; i < GRID; i++) {
        for (int j = 0; j < GRID; j++) {
            SDL_Rect cell = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };

            if (revealed[i][j]) {
                if (board[i][j] == -1)
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Mine
                else
                    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            }

            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

// Reveal cell
void revealCell(int row, int col) {
    if (row < 0 || col < 0 || row >= GRID || col >= GRID) return;
    if (revealed[row][col]) return;

    revealed[row][col] = true;

    if (board[row][col] == -1) {
        gameOver = true;
        cout << "Game Over! You hit a mine.\n";
    }
}

// Main game loop
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Minesweeper Game (SDL2)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_SIZE, WINDOW_SIZE,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initBoard();

    SDL_Event e;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_MOUSEBUTTONDOWN && !gameOver) {
                int x = e.button.x / CELL_SIZE;
                int y = e.button.y / CELL_SIZE;
                revealCell(y, x);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawGrid();

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
