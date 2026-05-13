#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Project Description:
// This program implements a 2D Helicopter Game using C++ and SDL2 for Windows.
// The player controls a helicopter that moves up when a key is pressed and
// moves down due to gravity when released. Random obstacles are generated,
// and collision ends the game.

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool running = true;

// Helicopter
SDL_Rect helicopter = {100, 250, 60, 30};
float velocityY = 0.0f;
const float GRAVITY = 0.5f;
const float LIFT = -1.0f;

// Obstacle
SDL_Rect obstacle = {800, 0, 60, 200};
int score = 0;

// Initialize SDL
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL Init Error\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Helicopter Game (SDL2 - Windows)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return true;
}

// Reset obstacle
void resetObstacle() {
    obstacle.x = SCREEN_WIDTH;
    obstacle.h = rand() % 300 + 100;
    obstacle.y = 0;
}

// Handle input
void handleInput(SDL_Event& e) {
    if (e.type == SDL_QUIT)
        running = false;

    if (e.type == SDL_KEYDOWN) {
        velocityY = LIFT;
    }
}

// Update game logic
void update() {
    // Gravity effect
    velocityY += GRAVITY;
    helicopter.y += (int)velocityY;

    // Move obstacle
    obstacle.x -= 4;

    if (obstacle.x + obstacle.w < 0) {
        resetObstacle();
        score++;
    }

    // Collision detection
    if (SDL_HasIntersection(&helicopter, &obstacle)) {
        running = false;
    }

    // Screen boundaries
    if (helicopter.y < 0 || helicopter.y + helicopter.h > SCREEN_HEIGHT) {
        running = false;
    }
}

// Render graphics
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Helicopter (Green)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &helicopter);

    // Obstacle (Red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &obstacle);

    SDL_RenderPresent(renderer);
}

// Cleanup
void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    srand((unsigned int)time(NULL));

    if (!initSDL())
        return 0;

    resetObstacle();

    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            handleInput(e);
        }

        update();
        render();

        SDL_Delay(16); // ~60 FPS
    }

    cout << "Game Over! Score: " << score << endl;

    closeSDL();
    return 0;
}
