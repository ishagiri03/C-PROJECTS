#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

// Project Description:
// This program implements a simple 2D Ball Game using C++ and OpenGL (GLUT).
// The player controls a ball using arrow keys and collects points by touching objects.
// The game includes collision detection and scoring system.

float ballX = 0.0f, ballY = 0.0f;
float speed = 0.05f;

float objX = 0.5f, objY = 0.5f;
int score = 0;

// Draw circle (ball or object)
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416f / 180;
        glVertex2f(cx + cos(angle) * r, cy + sin(angle) * r);
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Ball
    glColor3f(0.0f, 0.0f, 1.0f);
    drawCircle(ballX, ballY, 0.08f);

    // Draw Collectible Object
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(objX, objY, 0.05f);

    glutSwapBuffers();
}

// Collision detection
bool checkCollision() {
    float distance = sqrt(pow(ballX - objX, 2) + pow(ballY - objY, 2));
    return distance < 0.13f;
}

// Update logic
void update(int value) {
    if (checkCollision()) {
        score++;
        cout << "Score: " << score << endl;

        objX = (rand() % 200 - 100) / 100.0f;
        objY = (rand() % 200 - 100) / 100.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Keyboard input
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    ballY += speed; break;
    case GLUT_KEY_DOWN:  ballY -= speed; break;
    case GLUT_KEY_LEFT:  ballX -= speed; break;
    case GLUT_KEY_RIGHT: ballX += speed; break;
    }
}

// Initialize OpenGL
void init() {
    glClearColor(0, 0, 0, 1);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Ball Game - OpenGL");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
