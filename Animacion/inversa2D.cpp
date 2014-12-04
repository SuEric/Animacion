//
//  inversa2D.cpp
//  Animacion
//
//  Created by sueric on 25/09/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <strstream>
#include <iomanip>

#include "link_list.h"
#include "link.h"
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

// Tamaño ventana
#define WIDTH  800
#define HEIGHT 600

// Ancho y Height actual
int currentWidth  = WIDTH;
int currentHeight = HEIGHT;

Color colors[6] = {
                        {1.0f, 1.0f, 1.0f, 1.0f},
                        {6.0f, 6.0f, 0.0f, 1.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f},
                        {1.0f, 0.0f, 0.0f, 1.0f},
                        {0.0, 1.0, 1.0, 1.0},
                        {1.0f, 0.5f, 0.0f, 1.0f}
                    };

// Posiciones mouse, normalizado a [0,1].
double xMouse = 0.5;
double yMouse = 0.5;

// Limites de vista del frustum
float nearPlane =  1.0;
float farPlane  = 1000.0;

// Angulo de vision
double viewing_angle = 40.0;

// Rotaciones camara
double alpha = 0;
double beta = 0;

link_list l; // Lista de nuestros links

Vector2f targetPoint = Vector2f::Zero(); // Coordenada del nuevo target

void generateLinks(void)
{
    for (int i = 1; i <= 6; i++) {
        Link *l = new Link(colors[i-1]);
        ::l.addLink(l);
    }
}

void display ()
{
    glEnable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Translate y rotate escena
    glTranslatef(0, 0, -200);
    glRotatef(-90, 1, 0, 0);
    
    // Rotates X, Y normalizados
    beta = 180.0 * xMouse;
    alpha = 180.0 * yMouse;
    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
    
    l.draw();
    
    // Esfera, nuestro target!
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0, -targetPoint(1), targetPoint(0));
    glutSolidSphere(2.0f, 8, 8);
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void timer(int i)
{
    l.update();
    
    if(l.isTargetResolved()) {
        targetPoint = l.getPointWithinRange();
        l.moveToPoint(targetPoint);
    }
    
    glutTimerFunc(10, timer, i);
    glutPostRedisplay();
}

void mouseMovement (int mx, int my)
{
    // Normalización de coordenadas mouse
    xMouse = 1 - double(mx) / double(currentWidth);
    yMouse = 1 - double(my) / (double(currentHeight) - 10);
    
    cout << "X normalizado: " << xMouse << endl;
    cout << "Y normalizado: " << yMouse << endl;
    
    glutPostRedisplay();
}

void reshape (int newWidth, int newHeight)
{
    // Necesarios para el mouseMovement
    currentWidth = newWidth;
    currentHeight = newHeight;
    
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(viewing_angle, GLfloat(newWidth) / GLfloat(newHeight), nearPlane, farPlane);
}

void teclado (unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
    }
}

void init(void)
{
    glClearColor(0.6, 0.6, 0.6, 0.0);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    // Luces
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Componente Alpha
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    
    GLfloat global_ambient[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glLightModelfv(GL_AMBIENT_AND_DIFFUSE, global_ambient);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowSize(currentWidth, currentHeight);
    glutCreateWindow("Cinematica Inversa 2D");
    
    generateLinks();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMotionFunc(mouseMovement);
    glutTimerFunc(5, timer, 0);
    
    init();
    
    glutMainLoop();
    
    return 0;
}