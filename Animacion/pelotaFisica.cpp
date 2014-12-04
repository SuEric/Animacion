#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

// Globals.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.
static float t = 0.0; // Time parameter.
static float h = 0.5; // Horizontal component of initial velocity.
static float v = 4.0; // Vertical component of initial velocity.
static float g = 0.2;  // Gravitational accelaration.
static char theStringBuffer[10]; // String buffer.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
    char *c;
    
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to onvert floating point to char string.
void floatToString(char * destStr, int precision, float val)
{
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}

// Write data.
void writeData(void)
{
    glColor3f(0.0, 0.0, 0.0);
    
    floatToString(theStringBuffer, 4, h);
    glRasterPos3f(-4.5, 4.5, -5.1);
    writeBitmapString((void*)font, "Componente horizontal de la velocidad inicial: ");
    writeBitmapString((void*)font, theStringBuffer);
    
    floatToString(theStringBuffer, 4, v);
    glRasterPos3f(-4.5, 4.2, -5.1);
    writeBitmapString((void*)font, "Componente vertical de la velocidad inicial: ");
    writeBitmapString((void*)font, theStringBuffer);
    
    floatToString(theStringBuffer, 4, g);
    glRasterPos3f(-4.5, 3.9, -5.1);
    writeBitmapString((void*)font, "Gravitacion: ");
    writeBitmapString((void*)font, theStringBuffer);
}

// Drawing routine.
void drawScene(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    writeData();
    
    // Place scene in frustum.
    glTranslatef(-15.0, -15.0, -25.0);
    
    // Apply equations of motion to transform sphere.
    glTranslatef(h*t, v*t - (g/2.0)*t*t, 0.0);
    
    // Sphere.
    glColor3f(0.0, 0.0, 1.0);
    glutSolidSphere(2.0, 10, 10);
    
    glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
    if (isAnimate)
    {
        t += 1.0;
    }
    glutTimerFunc(animationPeriod, animate, 1);
    glutPostRedisplay();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case ' ':
            if (isAnimate) isAnimate = 0;
            else isAnimate = 1;
            glutPostRedisplay();
            break;
        case 'r':
            isAnimate = 0;
            t = 0.0;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}


// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) v += 0.05;;
    if(key == GLUT_KEY_DOWN) if (v > 0.1) v -= 0.05;
    if(key == GLUT_KEY_RIGHT) h += 0.05;
    if(key == GLUT_KEY_LEFT) if (h > 0.1) h -= 0.05;
    if(key == GLUT_KEY_PAGE_UP) g += 0.05;
    if(key == GLUT_KEY_PAGE_DOWN) if (g > 0.1) g -= 0.05;
    
    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaccion:" << endl;
    cout << "Presiona space para detener o iniciar la animacion." << endl;
    cout << "Presiona las flechas der/izq para incrementar/decrementar la velocidad inicial horizontal." << endl;
    cout << "Presiona las flechas arriba/abajo para incrementar/decrementar la velocidad inicial vertical." << endl;
    cout << "Presiona Repag/AvPag para incrementar la aceleracion gravitacional." << endl;
    cout << "Presiona r para resetear." << endl;
}

// Main routine.
int main(int argc, char **argv)
{
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("Pelota con friccion");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(5, animate, 1);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop(); 
    
    return 0;  
}

