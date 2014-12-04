#include <stdio.h>
#include <stdlib.h>

#include "modelo2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

double velocidad = 10;
float angulos_caminado[2][6] ;
double movimiento = 0.0f;

int zoom_flag = GL_FALSE;
int rotate_flag = GL_FALSE;

float langle_count = 30, langle_count2 = 0; // Angulos derechos
float rangle_count = -30, rangle_count2 = 0; // Angulos izquierdos

float zoom = 0.0f;
int rotate = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    
    glTranslatef(0.0, 0.0, zoom);  // tran,rot = zoom
    glRotatef(rotate, 0.0, 1.0, 0.0); // rot,tran = moving
    
    dibujaBaseLegs();
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void timer()
{
    animar_base();
    glutTimerFunc(velocidad, timer, 1);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void specialInput(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            zoom += 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            zoom -= 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            rotate = (rotate + 5) % 360;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            rotate = (rotate - 5) % 360;
            glutPostRedisplay();
    }
}

void teclado(unsigned char key, int x, int y)
{
    switch(key) {
        case 'w':
            if ((velocidad+1)<1000) velocidad += 1;
            break;
        case 'q':
            if( (velocidad-1) > 3 ) velocidad -= 1;
            else if( (velocidad-0.1f) > 2 ) velocidad -= 0.1f;
            break;
        case 27:
            exit(0);
    }
}

void init()
{
    glClearColor(0.6, 0.6, 0.6, 0.0);
    glShadeModel(GL_FLAT);
    
    angulos_caminado[0][3] = langle_count;
    angulos_caminado[1][3] = rangle_count;
    
    movimiento = desplazamiento(langle_count, langle_count2, rangle_count, rangle_count);
    glutTimerFunc(velocidad, timer, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Animación Piernas");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialInput);
    glutKeyboardFunc(teclado);
    
    glutMainLoop();
    return 0;
}