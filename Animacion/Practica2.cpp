//
//  animacionFlor.cpp
//  Animacion
//
//  Created by sueric on 25/09/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324

using namespace std;

// Variables Globales.
static float t = 0.0; // parametro de animacion
static float Xangle = 0.0, Yangle = 260.0, Zangle = 0.0; // angulos para rotar la escena.
static int isAnimate = 0; // Animacion activada?
static int animationPeriod = 10; // Intervalo de tiempo entre los frames.
static unsigned int base; // Listas de despliegue.

// Colores
GLfloat vRosa[] = {1.0, 0.5, 0.6, 1.0}; // Rosa
GLfloat vVerde[] = {0.0, 1.0, 0.0, 1.0}; // Verde
GLfloat vAzul[] = {0.0, 0.6,1.0, 1.0}; // Azul
GLfloat vMorado[] = {0.5, 0.3, 0.7, 1.0}; // Morado
GLfloat vAmarillo[] = {1.0, 1.0, 0.0,1.0}; // Amarillo
GLfloat vRojo[] = {0.8, 0.0, 0.0, 1.0}; // Rojo
GLfloat vRojo2[] = {1.0, 0.2, 0.0, 1.0}; // Rojo
GLfloat vCafe[] = {0.36, 0.2, 0.09, 1.0}; // Cafe
GLfloat vCafeClaro[] = {0.87, 0.72, 0.52}; //cafe claro
GLfloat vBlanco[] = {1.0, 1.0, 1.0, 1.0}; // Blanco
GLfloat vNaranja[] = {1.0, 0.5, 0.0, 1.0}; // Naranja
GLfloat vNegro[] = {0.0, 0.0, 0.0}; // Negro
GLfloat vGris[] = {0.6, 0.6, 0.6}; // Gris
GLfloat vVerdeOscuro[] = {0.0, 0.4, 0.0, 1.0}; // Verde oscuro
GLfloat vVerdeMike[] = {0.7372, 0.9333, 0.40784};
GLfloat vAzulMezclilla[] = {0.2901, 0.4977, 0.54509};
GLfloat vVerdeAlien[] = {0.67843, 1.0, 0.18431}; // Verde Alien
GLfloat vAzulOscuro[] = {0.0, 0.0, 0.54117}; // Azul oscuro

// Luces
GLfloat luz_difusa[] = {vRojo[0], vRojo[1], vRojo[2], vRojo[3]}; // Roja
GLfloat luz_ambiente[] = {vAmarillo[0], vAmarillo[1], vAmarillo[2], vAmarillo[3]}; // Amarilla
GLfloat luz_especular[] = {vBlanco[0], vBlanco[1], vBlanco[2], vBlanco[3]};

GLfloat posicion[] = {5, -20, -40}; // Referencia

void drawHemisphere(float radius, int longSlices, int latSlices)
{
	glutSolidSphere(radius, longSlices, latSlices);
}

void drawCircle(float radius, int numVertices)
{
    glutSolidSphere(radius, numVertices, 5);
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Fondo pantalla
    
    //PROPIEDADES DE LA ILUMINACION
	glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT2, GL_SPECULAR, luz_especular);
	glLightfv(GL_LIGHT3, GL_POSITION, posicion);
	
    //SE ACTIVAN
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    base = glGenLists(3);
    glListBase(base);
}

void drawScene(void)
{
    // Parameters controlling the configuration of the plant and flower as functions of the animation parameter t
    // t is used to linearly interpolate between the start and end value of each configuration parameter.
    float angleFirstSegment = (1-t)*60.0 + t*80.0; // Angle of first plant segment interpolating between 60 and 90.
    float angleSecondSegment = (1-t)*-30.0 + t*-20.0; // Angle of second plant segment.
    float angleThirdSegment = (1-t)*-30.0 + t*-20.0; // Angle of third plant segment.
    float angleFourthSegment = (1-t)*-30.0 + t*-20.0; // Angle of fourth plant segment.
    float hemisphereScaleFactor = (1-t)*0.1 + t*0.75; // Factor scaling the circular base of the hemisphere.
    float petalAspectRatio = (1 - t)*0.1 + t*1.0; // Factor scaling petal circle to make it an ellipse.
    float petalOpenAngle = (1 - t)*-10.0 + t*-60.0; // Angle at which the petal is  open.
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, -10.0, -30.0);
    
    // Stem segment display list.
    glNewList(base, GL_COMPILE);
    glColor3f(0.0, 1.0, 0.0);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vVerdeOscuro);
    glLightfv(GL_LIGHT1, GL_AMBIENT, vVerdeMike);
    glLightfv(GL_LIGHT2, GL_SPECULAR, vBlanco);
    
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);
    glEnd();
    glEndList();
    
    // Sepalo display list.
    glNewList(base + 1, GL_COMPILE);
    glPushMatrix();
    
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(hemisphereScaleFactor, 1.0, hemisphereScaleFactor); // Se le da la forma hemi-eliptico
    
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vRojo2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, vRojo);
    glLightfv(GL_LIGHT2, GL_SPECULAR, vBlanco);
    
    drawHemisphere(2.0, 6, 6); // Se dibuja el sepalo
    
    glPopMatrix();
    glEndList();
    
    // Petalo display list.
    glNewList(base + 2, GL_COMPILE);
    glPushMatrix();
    
    glTranslatef(2.0, 0.0, 2.0 * hemisphereScaleFactor); // Se traslada y se pega al sepalo
    
    glTranslatef(-2.0, 0.0, 0.0);
    glRotatef(petalOpenAngle, 0.0, 1.0, 0.0); // El petalo se abre a un dado angulo
    glTranslatef(2.0, 0.0, 0.0);
    
    glScalef(1.4, petalAspectRatio, 0.2); // Se aplasta el circulo para convertirse en elipse
    
    // Iluminación para los petalo
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vAmarillo);
    glLightfv(GL_LIGHT1, GL_AMBIENT, vAmarillo);
    glLightfv(GL_LIGHT2, GL_SPECULAR, vBlanco);
    
    drawCircle(2.0, 10); // Se dibujan los petalos
    
    glPopMatrix();
    glEndList();
    // End petal display list.
    
    // Rotate scene.
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);
    
    // First stem segment.
    glRotatef(angleFirstSegment, 0.0, 0.0, 1.0);
    glCallList(base);
    
    // Second stem segment.
    glTranslatef(5.0, 0.0, 0.0);
    glRotatef(angleSecondSegment, 0.0, 0.0, 1.0);
    glCallList(base);
    
    // Third stem segment.
    glTranslatef(5.0, 0.0, 0.0);
    glRotatef(angleThirdSegment, 0.0, 0.0, 1.0);
    glCallList(base);
    
    // Fourth stem segment.
    glTranslatef(5.0, 0.0, 0.0);
    glRotatef(angleFourthSegment, 0.0, 0.0, 1.0);
    glCallList(base);
    
    // Sepal.
    glTranslatef(7.0, 0.0, 0.0);
    glCallList(base + 1);
    // First petal.
    glPushMatrix();
    glRotatef(30.0, 1.0, 0.0, 0.0);
    glCallList(base + 2);
    glPopMatrix();
    
    // Second petal.
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glCallList(base + 2);
    glPopMatrix();
    
    // Third petal.
    glPushMatrix();
    glRotatef(150.0, 1.0, 0.0, 0.0);
    glCallList(base + 2);
    glPopMatrix();
    
    // Fourth petal.
    glPushMatrix();
    glRotatef(210.0, 1.0, 0.0, 0.0);
    glCallList(base + 2);
    glPopMatrix();
    
    // Fifth petal.
    glPushMatrix();
    glRotatef(270.0, 1.0, 0.0, 0.0);
    glCallList(base+2);
    glPopMatrix();
    
    // Sixth petal.
    glPushMatrix();
    glRotatef(330.0, 1.0, 0.0, 0.0);
    glCallList(base + 2);
    glPopMatrix();
    
    glutSwapBuffers();
}

void animate(int value)
{
    if (isAnimate) {
        t += 0.01;
        if (t >= 1.0) isAnimate = 0;
    }
    glutTimerFunc(animationPeriod, animate, 1);
    glutPostRedisplay();
}

void resize(int w, int h)
{
    glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y)
{
    switch(key) {
        case 27:
            exit(0);
            break;
        case ' ':
            if (isAnimate) isAnimate = 0;
            else isAnimate = 1;
            glutPostRedisplay();
            break;
        case 127:
            if (isAnimate) isAnimate = 0;
            t = 0.0;
            glutPostRedisplay();
            break;
        case 'x':
            Xangle += 5.0;
            if (Xangle > 360.0) Xangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'X':
            Xangle -= 5.0;
            if (Xangle < 0.0) Xangle += 360.0;
            glutPostRedisplay();
            break;
        case 'y':
            Yangle += 5.0;
            if (Yangle > 360.0) Yangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Y':
            Yangle -= 5.0;
            if (Yangle < 0.0) Yangle += 360.0;
            glutPostRedisplay();
            break;
        case 'z':
            Zangle += 5.0;
            if (Zangle > 360.0) Zangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Z':
            Zangle -= 5.0;
            if (Zangle < 0.0) Zangle += 360.0;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void interaccion(void)
{
    cout << "Interaccion:" << endl;
    cout << "Presiona espace para cambiar la animacion (si o no)." << endl;
    cout << "Presiona suprimir para resetear." << endl;
    cout << "Presiona las teclas x, X, y, Y, z, Z para rotar la escena." << endl;
}

int main(int argc, char **argv)
{
    interaccion();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("Ejemplo de una flor");
    
    init();
    
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(5, animate, 1);
    glutMainLoop();
    
    return 0;
}