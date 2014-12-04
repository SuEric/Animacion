//
//  boids_3D.cpp
//  Animacion
//
//  Created by sueric on 14/11/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "boids_3D.h"

// Variables de camara y mouse
float alpha = 0, beta = 0; // Rotaciones de camara
int x00, y00; // Coordenada del click

const double PI = 3.141592654, d2r = PI / 180.0,r2d = 180.0 / PI;

vector<objeto> flock; // boids

void inicializarBoids(void)
{
    
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 3.0f, 10.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia pantalla
    
	glRotatef(alpha, 1.0f, 0.0f, 0.0f); // Rotate X escenario
	glRotatef(beta, 0.0f, 1.0f, 0.0f); // Rotate Y escenario
    
    glColor3f(1.0, 0.0, 0.0);
    
    // Triangulos
	glPushMatrix();
	for (int i = 0; i < flock.size(); i++) {
        flock[i].mover();
		dibuja(flock[i]);
	}
	glPopMatrix();
    
    glFlush();
	glutSwapBuffers();
}

void resize(int w, int h)
{
    GLfloat nRange = 80.0f;
    
    if(h == 0) h = 1;
    
    glViewport(0, 0, w, h); // Punto de visión
    
    glMatrixMode(GL_PROJECTION); // Modo de matriz
    glLoadIdentity(); // Carga matriz
    
    if (w <= h) glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    
    glMatrixMode(GL_MODELVIEW); // Modo matriz
    glLoadIdentity(); // Pone matriz

}

void onMouse(int button, int state, int x, int y)
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) x00 = x; y00 = y; // Captura posicion del click
}

void onMotion(int x, int y)
{
	alpha = (alpha + (y - y00)); // Rotacion en X
	beta = (beta + (x - x00)); // Rotacion en Y
	x00 = x; y00 = y; // Actualiza posicion raton apretado
    
	glutPostRedisplay(); // Redibujado (no hay diferencia)
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}

void animate(int a)
{
    
}

void init(void)
{
    glClearColor(0.6, 0.6, 0.6, 1.0);
    
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
	glPushMatrix();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("Ejemplo de una flor");
    
    init();
    
    inicializarBoids();
    
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutKeyboardFunc(keyboard);
    
    glutTimerFunc(5, animate, 1); // animacion
    
    glutMainLoop();
    
    return 0;
}