#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

static GLsizei width, height;

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glViewport(0, 0, width/2.0,  height);
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 10.0, 0.0);
    glVertex3f(40.0, 10.0, 0.0);
    glVertex3f(40.0, 40.0, 0.0);
    glVertex3f(10.0, 40.0, 0.0);
    glEnd();
    glViewport(width/2.0, 0, width/2.0, height);
    
    glColor3f(0.0, 0.0, 1.0);
    float angle;
    int i;
    glBegin(GL_LINE_LOOP);
    for(i = 0; i < 30; ++i)
    {
        angle = 2 * PI * i / 30;
        glVertex2f(50.0 + cos(angle) * 40.0, 50.0 + sin(angle) * 40.0);
    }
    glEnd();
    
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex3f(0.1, 0.0, 0.0);
    glVertex3f(0.1, 100.0, 0.0);
    glEnd();
    glLineWidth(1.0);
    
    glFlush();
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    width = w;
    height = h;
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Viewports");
    
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop(); 
    
    return 0;  
}

