#include <iostream>
#include <fstream>
#include <string>
#include <GL/freeglut.h>
// g++ test.cpp -o main -lGL -lGLU -lglut
// sudo ./build.sh
using namespace std;

int WINDOW_WIDTH = 500;
int WINDOW_HEIGT = 400;

int fps = 30;
static string ST_TEXT = "Text";
string show_uptime();
void drawtext()
{

    // GET WINDOW COORDS INSTEAD OF VERTICES FOR TEXT POS
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGT);

    glColor3f(1.0f, 0.0f, 1.0f);                       // TEXT COLOR
    glRasterPos2f(WINDOW_WIDTH / 3, WINDOW_HEIGT / 2); // Text POSITION
    const unsigned char *text = reinterpret_cast<const unsigned char *>(ST_TEXT.c_str()); // Cast to pointer
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, text); // screen in an 18-point Helvetica font

    glPopMatrix(); // SWITCH BACK TO VERTEX
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// Clears the current window and calls draw function
void display()
{
    // Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);
    drawtext();
    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();
}

void update(int i)
{
    ST_TEXT = show_uptime();
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, update, i); // recursion is needed glutTimerfunc is only called once
}

//checks file for linux uptime
string show_uptime()
{	
	auto ifs = std::ifstream("/proc/uptime");
	if( !ifs.good() ){ throw std::runtime_error("Error: unable to open uptime file "); }
	double seconds;
	ifs >> seconds; 
	uint64_t factor = 24 * 60 * 60;
	return "   Uptime in hours = " + std::to_string(seconds / ( 60 * 60));
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
    glutTimerFunc(100, update, 0);

    // Tell GLUT to start reading and processing events.  This function
    // never returns; the program only exits when the user closes the main
    // window or kills the process.
    glutMainLoop();
}