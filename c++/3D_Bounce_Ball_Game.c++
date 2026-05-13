#include <GL/glut.h>     // freeGLUT for Windows
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Project Description:
// This program implements a simple 3D Bounce Ball Game using C++ and OpenGL (GLUT).
// A ball moves in a 3D box, bounces from walls, and the player can control its movement.
// The game includes basic physics, scoring and keyboard interaction.
// This version is fully compatible with Windows OS.

float ballX = 0.0f, ballY = 0.0f, ballZ = 0.0f;
float velX = 0.02f, velY = 0.03f, velZ = 0.02f;
int score = 0;

// Draw text on screen (2D)
void drawText(float x, float y, const string& text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// Draw the ball
void drawBall() {
    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);
    glColor3f(1.0f, 0.2f, 0.2f);   // Red ball
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
}

// Draw 3D box (walls)
void drawBox() {
    glColor3f(0.6f, 0.6f, 0.6f);
    glutWireCube(3.0);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera setup
    gluLookAt(0, 0, 6,   0, 0, 0,   0, 1, 0);

    drawBox();
    drawBall();

    // Switch to 2D for score display
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1, 1, 1);
    drawText(10, 570, "Score: " + to_string(score));

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

// Update ball movement and physics
void update(int value) {
    ballX += velX;
    ballY += velY;
    ballZ += velZ;

    // Bounce from walls
    if (ballX > 1.4f || ballX < -1.4f) {
        velX = -velX;
        score++;
    }
    if (ballY > 1.4f || ballY < -1.4f) {
        velY = -velY;
        score++;
    }
    if (ballZ > 1.4f || ballZ < -1.4f) {
        velZ = -velZ;
        score++;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);   // ~60 FPS
}

// Keyboard controls
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': velY += 0.01f; break;
    case 's': velY -= 0.01f; break;
    case 'a': velX -= 0.01f; break;
    case 'd': velX += 0.01f; break;
    case 'q': velZ += 0.01f; break;
    case 'e': velZ -= 0.01f; break;
    case 27: exit(0); // ESC key
    }
}

// OpenGL initialization
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Bounce Ball Game (Windows)");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
