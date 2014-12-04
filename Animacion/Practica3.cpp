//
//  Practica1.cpp
//  Primer_OpenGL
//
//  Created by sueric on 22/08/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define radioAve 15.0
#define largoAlaGrande 10.0
#define largoAlaPeque 10.0
#define codo 2.15

using namespace std;

int frame = 0, times = 0, timebase = 0;
double fps;

float alpha, beta; // Transformaciones del objeto compeleto (juego de camara)
int x2, y2, z = 0;
int controlFPS = 30;
double t = 0, dt = 0.01;
GLint gFramesPerSecond = 0;
float trans1 = -280, trans = 0, trans2 = 0, angle;

GLUquadric *qobj;

// Colores
GLfloat vRosa[] = {1.0,0.5,0.6,1.0}; // Rosa
GLfloat vVerde[] = {0.0,1.0,0.0,1.0}; // Verde
GLfloat vAzul[] = {0.0,0.6,1.0,1.0}; // Azul
GLfloat vMorado[] = {0.5,0.3,0.7,1.0}; // Morado
GLfloat vAmarillo[] = {1.0,1.0,0.0,1.0}; // Amarillo
GLfloat vRojo[] = {1.0,0.0,0.0,1.0}; //Rojo
GLfloat vCafe[] = {0.36,0.2,0.09,1.0}; // Cafe
GLfloat vCafeClaro[] = {0.87, 0.72, 0.52}; //cafe claro
GLfloat vBlanco[] = {1.0,1.0,1.0,1.0}; // Blanco
GLfloat vNaranja[] = {1.0,0.5,0.0,1.0}; // Naranja
GLfloat vNegro[] = {0.0,0.0,0.0}; // Negro
GLfloat vGris[] = {0.6,0.6,0.6}; // Gris
GLfloat vVerdeOscuro[] = {0.0,0.4,0.0,1.0}; // Verde oscuro
GLfloat vAzulMezclilla[] = {0.2901, 0.4977, 0.54509}; // Azul mezclilla
GLfloat vVerdeAlien[] = {0.67843, 1.0, 0.18431}; // Verde Alien
GLfloat vAzulOscuro[] = {0.0, 0.0, 0.54117}; // Azul oscuro

// Luces
GLfloat luz_difusa[] = {0.1, 0.1, 0.1, 1.0};
GLfloat luz_ambiente[] = {0.1, 0.1, 0.1, 1.0};
GLfloat luz_especular[] = {0.1, 0.1, 0.1, 1.0};

int gradoAnimacion = 0;
GLboolean estadoAla = false;

void cuerpo(void)
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vRojo);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vRojo);
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1.0, 0.8, 1.0);
	glutSolidSphere(radioAve, 32, 32);
    glPopMatrix();
}

void ojoIzq(void)
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vBlanco);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vBlanco);
 
    glPushMatrix();
    
	glPushMatrix();
	glTranslatef(12.5, 2.0, 5.0);
	glScalef(0.30, 0.30, 0.5);
	glutSolidSphere(7, 10, 10);
	glPopMatrix();
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafe);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vCafe);
	
	glPushMatrix();
	glTranslatef(13.45, 2.5, 8.0);
    glRotatef(45, 0.0, 1.0, 0.0);
	glScalef(0.4, 0.4, 0.2);
	glutSolidSphere(3, 20, 20);
	glPopMatrix();
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
	
	glPushMatrix();
	glTranslatef(13.5, 2.3, 8.0);
	glRotatef(-22.0, 1.0, 0.0, 0.0);
	glScalef(0.20, 0.20, 0.2);
	glutSolidSphere(3,20,20);
	glPopMatrix();
    
    glPopMatrix();
}

void ojoDer(void)
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vBlanco);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vBlanco);
    
    glPushMatrix();
    
	glPushMatrix();
	glTranslatef(12.45, -2.0, 5.0);
	glScalef(0.30, 0.30, 0.5);
	glutSolidSphere(7, 10, 10);
	glPopMatrix();
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafe);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vCafe);
	
	glPushMatrix();
	glTranslatef(13.40, -2.5, 8.0);
    glRotatef(45, 0.0, 1.0, 0.0);
	glScalef(0.4, 0.4, 0.2);
	glutSolidSphere(3, 20, 20);
	glPopMatrix();
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
	
	glPushMatrix();
	glTranslatef(13.45, -2.3, 8.0);
	glRotatef(-22.0, 1.0, 0.0, 0.0);
	glScalef(0.20, 0.20, 0.2);
	glutSolidSphere(3,20,20);
	glPopMatrix();
    
    glPopMatrix();
}

void alas(void)
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vRojo);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vRojo);
    
    glPushMatrix();
    
    // Ala arriba
    glPushMatrix();
    glTranslatef(0.0, radioAve, 0.0);
    glScalef(4.0, largoAlaGrande, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, radioAve + largoAlaGrande/2, 0.0);
    glutSolidSphere(codo, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, radioAve + largoAlaGrande/2, 0.0);
    glRotatef(gradoAnimacion, 1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, largoAlaPeque/2, 0.0);
    glScalef(4.0, largoAlaPeque, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Ala abajo
    glPushMatrix();
    glTranslatef(0.0, -radioAve, 0.0);
    glScalef(4.0, largoAlaGrande, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, - (radioAve + largoAlaGrande/2), 0.0);
    glutSolidSphere(codo, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, - (radioAve + largoAlaGrande/2), 0.0);
    glRotatef(-gradoAnimacion, 1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, - (largoAlaPeque/2), 0.0);
    glScalef(4.0, largoAlaPeque, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    glPopMatrix();
}

void movimientoAlas(void)
{
    trans2 += 0.01;
    
    if(trans2 < 20) {
        trans1 = 28 * cos(trans2);
        trans = 28 * sin(trans2);
    } else trans2 = 0;
    
    if (!estadoAla) {
        gradoAnimacion = (gradoAnimacion + 1) % 360; // Arriba
        if (gradoAnimacion >= 20) estadoAla = true;
    } else {
        gradoAnimacion = (gradoAnimacion - 1) % 360; // Abajo
        if (gradoAnimacion <= -20) estadoAla = false;
    }
}

void ave(void)
{
    movimientoAlas(); // Actualiza los grados
    
    cuerpo(); // Cuerpo
    
    ojoIzq(); // Ojo izq
    
    ojoDer(); // Ojo der
    
    alas(); // Alas
    
}

void keyboardInput (unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}

void ChangeSize(int w, int h)
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia pantalla
    
    glPushMatrix(); //Inicia objeto articulado
    
    glTranslatef(trans1, trans, 0.0);
    glRotatef(alpha, 1.0f, 0.0f, 0.0f); // Gira en Y
    glRotatef(beta, 0.0f, 1.0f, 0.0f); // Gira en Y
    
    ave();
    
    glPopMatrix(); //Fin objeto articulado
    
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 100; i++) {
        angle=i*2*M_PI/100;
        glVertex2f(28*cos(angle), 28*sin(angle));
    }
    glEnd();
    
    glutSwapBuffers(); // Intercambio de buffers, evita efecto de parpadeo
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    //CUADRICO
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
    
    //PROPIEDADES DE LA ILUMINACION
	glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	
    //SE ACTIVAN
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
}

void onMotion (int x, int y) {
    alpha += (y - y2);
    beta += (x - x2);
    x2 = x; y2 = y;
}

void FPS(void) {
    static GLint Frames = 0;         // Frames por milisegundos
    static GLuint Clock;             // [milliSeconds]
    static GLuint PreviousClock = 0; // [milliSeconds]
    static GLuint NextClock = 0;     // [milliSeconds]
    
    ++Frames; // incrementa frames
    Clock = glutGet(GLUT_ELAPSED_TIME); // has limited resolution, so average over 1000mS
    if ( Clock < NextClock ) return;
    
    gFramesPerSecond = Frames/1; // store the averaged number of frames per second
    
    PreviousClock = Clock;
    NextClock = Clock + 1000; // 1000mS=1S in the future
    Frames = 0;
}

void timer(int value)
{
    glutTimerFunc(1000/controlFPS, timer, ++value);
    GLfloat dt = (gFramesPerSecond > 0 ? 1.0/gFramesPerSecond : 1.0);
    t += dt;
    
    FPS();
    glutPostRedisplay();
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Objeto simple articulado");
    
    init();
    
    // Funciones a usar
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardInput);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(0, timer, 0);
    glutMotionFunc(onMotion);
    
    glutMainLoop();
    return 0;
}
