#include <GL/glut.h>
#include <iostream>
using namespace std;

// Project Description:
// This program implements a simple Bike Race Game in C++ using Object Oriented Programming
// and OpenGL (GLUT). Two players control bikes on a race track, avoid obstacles,
// complete laps and compete to reach the finish line first.

class Bike {
public:
    float x, y;
    float speed;
    int laps;
    float r, g, b;

    Bike(float _x, float _y, float _r, float _g, float _b) {
        x = _x;
        y = _y;
        speed = 0.02f;
        laps = 0;
        r = _r; g = _g; b = _b;
    }

    void draw() {
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(x - 0.05, y - 0.05);
        glVertex2f(x + 0.05, y - 0.05);
        glVertex2f(x + 0.05, y + 0.05);
        glVertex2f(x - 0.05, y + 0.05);
        glEnd();
    }
};

// Two bikes (players)
Bike bike1(-0.5, -0.8, 1, 0, 0);   // Red bike
Bike bike2(0.5, -0.8, 0, 0, 1);    // Blue bike

// Obstacle position
float obsX = 0.0f, obsY = 0.0f;

bool gameOver = false;

// Draw race track
void drawTrack() {
    glColor3f(0.3, 0.3, 0.3);   // Road
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    // Finish line
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-1, 0.9);
    glVertex2f(1, 0.9);
    glEnd();
}

// Draw obstacle
void drawObstacle() {
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex2f(obsX - 0.05, obsY - 0.05);
    glVertex2f(obsX + 0.05, obsY - 0.05);
    glVertex2f(obsX + 0.05, obsY + 0.05);
    glVertex2f(obsX - 0.05, obsY + 0.05);
    glEnd();
}

// Collision detection
bool checkCollision(Bike &b) {
    if (abs(b.x - obsX) < 0.08 && abs(b.y - obsY) < 0.08)
        return true;
    return false;
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawTrack();
    drawObstacle();

    bike1.draw();
    bike2.draw();

    glutSwapBuffers();
}

// Update game logic
void update(int value) {
    if (gameOver) return;

    // Move bikes forward
    bike1.y += bike1.speed;
    bike2.y += bike2.speed;

    // Lap checking
    if (bike1.y > 1.0) {
        bike1.y = -1.0;
        bike1.laps++;
    }
    if (bike2.y > 1.0) {
        bike2.y = -1.0;
        bike2.laps++;
    }

    // Collision slows down
    if (checkCollision(bike1)) {
        bike1.speed = 0.01f;
    }
    if (checkCollision(bike2)) {
        bike2.speed = 0.01f;
    }

    // Win condition (3 laps)
    if (bike1.laps >= 3) {
        cout << "🎉 Player 1 Wins the Race! 🎉\n";
        gameOver = true;
    }
    if (bike2.laps >= 3) {
        cout << "🎉 Player 2 Wins the Race! 🎉\n";
        gameOver = true;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Keyboard controls
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    // Player 1 (WASD)
    case 'a': bike1.x -= 0.05; break;
    case 'd': bike1.x += 0.05; break;
    case 'w': bike1.speed += 0.005; break;
    case 's': bike1.speed -= 0.005; break;

    // Player 2 (IJKL)
    case 'j': bike2.x -= 0.05; break;
    case 'l': bike2.x += 0.05; break;
    case 'i': bike2.speed += 0.005; break;
    case 'k': bike2.speed -= 0.005; break;

    case 27: exit(0);   // ESC to exit
    }
}

// Initialize game
void init() {
    glClearColor(0, 0.5, 0, 1);   // Green background (grass)

    // Random obstacle
    obsX = 0.0f;
    obsY = 0.0f;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bike Race Game");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
