#include <iostream>
#include <vector>
#include <string>
#include <GL/freeglut.h>
// g++ test.cpp -o main -lGL -lGLU -lglut
// sudo ./build.sh
using namespace std;

int WINDOW_WIDTH = 500;
int WINDOW_HEIGT = 400;

void drawtext()
{

    //GET WINDOW COORDS INSTEAD OF VERTICES FOR TEXT POS
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGT);
   
    glColor3f(1.0f, 0.0f, 1.0f); //TEXT COLOR
    glRasterPos2f(WINDOW_WIDTH/3, WINDOW_HEIGT/2); // Text POSITION

    const unsigned char *text = reinterpret_cast<const unsigned char *>("text to render");
    // Use the above weird cast or just pass text to array to pass it to a pointer
    // const unsigned char textA[] = "text to render";
    // const unsigned char* text = textA;
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, text); // screen in an 18-point Helvetica font

    glPopMatrix(); //SWITCH BACK TO VERTEX
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// Clears the current window and draws a triangle.
void display()
{
    // Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);
    drawtext();
    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char **argv)
{

    // Use a single buffered window in RGB mode (as opposed to a double-buffered
    // window or color-index mode).
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Position window at (80,80)-(480,380) and give it a title.
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGT);
    glutCreateWindow("TEXT");

    // Tell GLUT that whenever the main window needs to be repainted that it
    // should call the function display().
    glutDisplayFunc(display);

    // Tell GLUT to start reading and processing events.  This function
    // never returns; the program only exits when the user closes the main
    // window or kills the process.
    glutMainLoop();
}