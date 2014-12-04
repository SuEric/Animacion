//
//  Practica5.cpp
//  Animacion
//
//  Created by sueric on 25/09/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;
#include <math.h>

#include <GLUI/GLUI.h>

#pragma comment (lib, "glui32.lib")

#define PI 3.141592654

// Medidas de las partes
// del robot
#define baseHeight 0.25
#define soporteHeight 4.0

#define elemento1Length 3.5
#define elemento1Heigth 0.5

#define elemento2Length 5.0
#define elemento2Heigth 2.5
#define elemento2Width 0.7

#define elemento3Heigth 2.0
#define elemento3Width 0.7

#define largoEje3y4 2.7

#define elemento4Width 0.30

#define elemento5Height 0.10
#define elemento5Width 0.10

GLUquadric *quadrico1;
GLUquadric *quadrico2;
GLUquadric *quadrico3;

// Luces a usar (usar DEPTH)
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

// Materials
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

// Spinners GLUI
GLUI_Spinner *spnArticulacion1;
GLUI_Spinner *spnArticulacion2;
GLUI_Spinner *spnArticulacion3;
GLUI_Spinner *spnArticulacion4;
GLUI_Spinner *spnArticulacion5;
GLUI_Spinner *spnArticulacion6;

// Esfera de rotacion del robot boton
GLUI_Rotation *Rotaciones;

// Translaciones GLUI
GLUI_Translation *TransXY;
GLUI_Translation *TransZ;

// Botones GLUI
GLUI_Button *btnReset;
GLUI_Button *btnSalir;

// ListBox para inversa
GLUI_Listbox *lista_inversa;
int seleccion_inversa = 0;

// Variables
int deltaBase = 0, delta1, delta2, delta3, delta4, delta5, delta6; // deltas 6gdl, deltaBase = 0
float matriz_rotar[16]; // Matriz homogenea que contiene la cinematica directa
float deltaXY[2];
float deltaZ;

float conf1[3];


float a2 = 0.5 + 2.7;
float a3 = 0.0;
float d3 = elemento2Width/2;
float d4 = largoEje3y4;

float c1 = cos(delta1);
float c2 = cos(delta2);
float c3 = cos(delta3);
float c4 = cos(delta4);
float c5 = cos(delta5);
float c6 = cos(delta6);

float s1 = sin(delta1);
float s2 = sin(delta2);
float s3 = sin(delta3);
float s4 = sin(delta4);
float s5 = sin(delta5);
float s6 = sin(delta6);

float cinematica[4][4];

float c23(void)
{
    return c2*c3 - s2*s3;
}

float s23(void)
{
    return c2*s3 + s2*c3;
}

void cinematica_puma(void)
{    
    cinematica[0][0] = c1 *
                        (
                        c23() * ( c4*c5*c6 - s4*s5 ) - s23()*s5*c5
                        ) + s1 * ( s4*c5*c6 + c4*s6);
    cinematica[0][1] = c1 *
                        (
                        c23() * (-c4*c5*s6 - s4*c6) + s23()*s5*s6
                        ) + s1 * (c4*c6 - s4*c5*s6);
    cinematica[0][2] = -c1 *
                        (
                            c23()*c4*s5 + s23()*c5
                        ) - s1*s4*s5;
    cinematica[0][3] = c1 *
                        (
                            a2*c2 + a3*c23() - d4*s23()
                        ) - d3*s1;
    
    cinematica[1][0] = s1 *
                        (
                         c23() * (c4*c5*c6 - s4*s6) - s23()*s5*c6 - c1*(s4*c5*c6 + c4*s6)
                        );
    cinematica[1][1] = s1 *
                        (
                            c23() * (-c4*c5*s6 - s4*c6) + s23()*s5*s6
                        ) - c1 * (c4*c6 - s4*c5*s6);
    cinematica[1][2] = -s1 *
                        (
                            c23()*c4*s5 + s23()*c5
                        ) + c1*s4*s5;
    cinematica[1][3] = s1 * (a2*c2 + a3*c23() - d4*s23()) - d3*s1;
    
    cinematica[2][0] = -s23() * ( c4*c5*c6 - s4*s6) - c23()*s5*c6;
    cinematica[2][1] = -s23() * ( -c4*c5*c6 - s4*c6) + c23()*s5*s6;
    cinematica[2][2] = s23()*c4*s5 - c23()*c5;
    cinematica[2][3] = -a3*s23() - a2*s2 - d4*c23();

    cinematica[3][0] = 0;
    cinematica[3][1] = 0;
    cinematica[3][2] = 0;
    cinematica[3][3] = 1;
}

void cleanup() // call once when you exit program
{
    gluDeleteQuadric(quadrico1);
    gluDeleteQuadric(quadrico2);
    gluDeleteQuadric(quadrico3);
}

void base()
{
    glPushMatrix();
    
    glColor3f(0.6, 0.6, 0.6);
    
	glPushMatrix();
    glScalef(0.5, 3.0 , 3.0);
    glutSolidSphere(0.5, 32, 32);
	glPopMatrix();
    
    glColor3f(0.4, 0.4, 0.4);
    
    // Cilindro
    glPushMatrix();
    glTranslatef(baseHeight, 0.0, 0.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadrico1, 0.8, 0.8, soporteHeight, 32, 32);
    glPopMatrix();
    
    glColor3f(0.3, 0.3, 0.3);
    
    // Tapa
    glPushMatrix();
    glTranslatef(soporteHeight + baseHeight, 0.0, 0.0);
    glScalef (0.5, 2.6, 2.6);
    glutSolidSphere(0.3, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
}

void elemento1()
{
    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);

    // Cilindro
    glPushMatrix();
    glTranslatef(soporteHeight + baseHeight, 0.0, 0.0);
    gluCylinder(quadrico2, 0.5, 0.5, elemento1Length, 32, 32);
    glPopMatrix();
    
    glColor3f(0.6, 0.6, 0.6);
    
    // Tapa
    glPushMatrix();
    glTranslatef(baseHeight + soporteHeight, 0.0, 0.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef (0.2, 2.4, 2.4);
    glutSolidSphere(0.2, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
}

void elemento2()
{
    glPushMatrix();
    
    glTranslatef(-(elemento2Heigth/2), elemento2Length/6, elemento2Width/2);
    
    glColor3f(1.0, 1.0, 1.0);
    
    // Parte inicial
    glPushMatrix();
    glScalef(2.5, 0.8, elemento2Width);
    glTranslatef(0.4, -2.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Inclinacion superior
    glPushMatrix();
    glRotatef(11.7, 0.0, 0.0, 1.0);
    glScalef(1.0, 3.5, elemento2Width);
    glTranslatef(1.44, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Relleno
    glPushMatrix();
    glScalef(0.7, 1.0, elemento2Width);
    glTranslatef(1.4, -0.7, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Inclinacion inferior
    glPushMatrix();
    glRotatef(-11.7, 0.0, 0.0, 1.0);
    glScalef(1.0, 3.5, elemento2Width);
    glTranslatef(0.53, 0.1, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glColor3f(1.0, 1.0, 1.0);
    
    // Parte final 
    glPushMatrix();
    glScalef(1.05, 0.8, elemento2Width);
    glTranslatef(0.95, 2.9, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

void elemento3()
{
	glPushMatrix();
    
    glTranslatef(-elemento3Heigth/2, 0.0, 0.0);
    
    glColor3f(1.0, 1.0, 1.0);
    
    glPushMatrix();
    glScalef(elemento2Heigth, elemento2Width, elemento2Width);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-elemento3Heigth/2, 0.0, 0.0);
    glScalef(0.8, .2, .2);
    glutSolidCube(1.0);
    glPopMatrix();
    
	glPopMatrix();
}

void elemento4()
{
	glPushMatrix();
 
    glTranslatef(0.0, 0.0, -elemento4Width/2);
    
    glColor3f(0.6, 0.6, 0.6);
    
    glPushMatrix();
    gluCylinder(quadrico3, elemento4Width, elemento4Width, elemento4Width, 32, 32);
    glPopMatrix();
    
    // Tapas
    glPushMatrix();
    glScalef (1.0, 1.0, 0.2);
    glutSolidSphere(elemento4Width, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, elemento4Width);
    glScalef (1.0, 1.0, 0.2);
    glutSolidSphere(elemento4Width, 32, 32);
    glPopMatrix();
    
	glPopMatrix();
}

void elemento5(void)
{

    glPushMatrix();
    
    glTranslatef(-elemento5Height/2, 0.0, 0.0);
    
    glColor3f(0.6, 0.6, 0.6);
    
    glPushMatrix();
    glScalef(elemento5Height, elemento5Width, elemento5Width);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-elemento5Width/2, 0.0, 0.0);
    glScalef(0.2, 1.0, 1.0);
    glutSolidSphere(elemento5Width, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
}

// Funcion display, se llama n veces
void display (void)
{
	glClearColor (0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch (seleccion_inversa) {
        case 0:
            glPushMatrix();
            
            glMultMatrixf(matriz_rotar); // Rotacion con boton de rotación GLUI
            
            glTranslatef (deltaXY[1], deltaXY[0], deltaZ); // Movimiento con las flechas GLUI
            
            /*  Aca empieza la parte
             de la cinemática directa
             */
            
            base(); // Renderizado base
            
            glRotatef(delta1, 0.0, 0.0, 0.0);
            elemento1();
            
            glTranslatef(baseHeight + soporteHeight + elemento1Heigth/2, 0.0, elemento1Length);
            glRotatef(-delta2, 0.0, 0.0, 1.0);
            elemento2();
            
            glTranslatef(0.0, 0.5 + 2.7, -elemento2Width/2);
            glRotatef(delta3, 0.0, 0.0, 1.0);
            elemento3();
            
            glTranslatef(-largoEje3y4, 0.0, 0.0);
            glRotatef(delta4, 1.0, 0.0, 0.0);
            elemento4();
            
            glTranslatef(-elemento4Width, 0.0, 0.0);
            glRotatef(delta5, 0.0, 0.0, 1.0);
            elemento5();
            
            glPopMatrix();
            break;
            
        case 1:
            glPushMatrix();
            
            glMultMatrixf(matriz_rotar); // Rotacion con boton de rotación GLUI
            
            glTranslatef (deltaXY[1], deltaXY[0], deltaZ); // Movimiento con las flechas GLUI
            
            glPushMatrix();
            glTranslatef(conf1[0], conf1[1], conf1[2]);
            glScalef(0.2, 0.2, 0.2);
            glutSolidSphere(1.0, 32, 32);
            glPopMatrix();
            
            /*  Aca empieza la parte
             de la cinemática directa
             */
            
            base(); // Renderizado base
            
            glRotatef(delta1, 0.0, 0.0, 0.0);
            elemento1();
            
            glTranslatef(baseHeight + soporteHeight + elemento1Heigth/2, 0.0, elemento1Length);
            glRotatef(-delta2, 0.0, 0.0, 1.0);
            elemento2();
            
            glTranslatef(0.0, 0.5 + 2.7, -elemento2Width/2);
            glRotatef(delta3, 0.0, 0.0, 1.0);
            elemento3();
            
            glTranslatef(-largoEje3y4, 0.0, 0.0);
            glRotatef(delta4, 1.0, 0.0, 0.0);
            elemento4();
            
            glTranslatef(-elemento4Width, 0.0, 0.0);
            glRotatef(delta5, 0.0, 0.0, 1.0);
            elemento5();
            
            glPopMatrix();
            break;
            
        case 2:
            glPushMatrix();
            
            glMultMatrixf(matriz_rotar); // Rotacion con boton de rotación GLUI
            
            glTranslatef (deltaXY[1], deltaXY[0], deltaZ); // Movimiento con las flechas GLUI
            
            glPushMatrix();
            glTranslatef(conf1[0], conf1[1], conf1[2]);
            glScalef(0.2, 0.2, 0.2);
            glutSolidSphere(1.0, 32, 32);
            glPopMatrix();
            
            /*  Aca empieza la parte
             de la cinemática directa
             */
            
            base(); // Renderizado base
            
            glRotatef(delta1, 0.0, 0.0, 0.0);
            elemento1();
            
            glTranslatef(baseHeight + soporteHeight + elemento1Heigth/2, 0.0, elemento1Length);
            glRotatef(-delta2, 0.0, 0.0, 1.0);
            elemento2();
            
            glTranslatef(0.0, 0.5 + 2.7, -elemento2Width/2);
            glRotatef(delta3, 0.0, 0.0, 1.0);
            elemento3();
            
            glTranslatef(-largoEje3y4, 0.0, 0.0);
            glRotatef(delta4, 1.0, 0.0, 0.0);
            elemento4();
            
            glTranslatef(-elemento4Width, 0.0, 0.0);
            glRotatef(delta5, 0.0, 0.0, 1.0);
            elemento5();
            
            glPopMatrix();
            break;
            
        case 3:
            glPushMatrix();
            
            glMultMatrixf(matriz_rotar); // Rotacion con boton de rotación GLUI
            
            glTranslatef (deltaXY[1], deltaXY[0], deltaZ); // Movimiento con las flechas GLUI
            
            glPushMatrix();
            glTranslatef(conf1[0], conf1[1], conf1[2]);
            glScalef(0.2, 0.2, 0.2);
            glutSolidSphere(1.0, 32, 32);
            glPopMatrix();
            
            /*  Aca empieza la parte
             de la cinemática directa
             */
            
            base(); // Renderizado base
            
            glRotatef(delta1, 0.0, 0.0, 0.0);
            elemento1();
            
            glTranslatef(baseHeight + soporteHeight + elemento1Heigth/2, 0.0, elemento1Length);
            glRotatef(-delta2, 0.0, 0.0, 1.0);
            elemento2();
            
            glTranslatef(0.0, 0.5 + 2.7, -elemento2Width/2);
            glRotatef(delta3, 0.0, 0.0, 1.0);
            elemento3();
            
            glTranslatef(-largoEje3y4, 0.0, 0.0);
            glRotatef(delta4, 1.0, 0.0, 0.0);
            elemento4();
            
            glTranslatef(-elemento4Width, 0.0, 0.0);
            glRotatef(delta5, 0.0, 0.0, 1.0);
            elemento5();
            
            glPopMatrix();
            break;
    }
    
	glFlush();
	glutSwapBuffers();
}

// Funcion init
void init (void)
{    
    glClearColor(0,0,0,0); // Fondo negro
    
    quadrico1 = gluNewQuadric();
    gluQuadricNormals(quadrico1, GLU_SMOOTH);
    quadrico2 = gluNewQuadric();
    gluQuadricNormals(quadrico2, GLU_SMOOTH);
    quadrico3 = gluNewQuadric();
    gluQuadricNormals(quadrico3, GLU_SMOOTH);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    // Luces
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    // Materials
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glClearDepth (1.0);
	glMatrixMode (GL_PROJECTION);
	gluPerspective (50.0, 1.0, 1.0, 100.0);
	glMatrixMode (GL_MODELVIEW);
    gluLookAt (14.0, 8.0, 8.0, -5.0, -5.0, 0.0, 1.0, 0.0, 0.0);
	glRotatef (90, 1, 0, 0);
    
    // Reset deltas
	delta1 = 0;
	delta2 = 0;
	delta3 = 0;
	delta4 = 0;
	delta5 = 0;
	delta6 = 0;
}

// Rotaciones con el teclado para girar el robot
void TeclaEspecial (int Key, int x, int y)
{
	switch (Key) {
	 	case GLUT_KEY_UP:   glRotatef (3.0, 0.0, 1.0, 0.0);
            break;
	 	case GLUT_KEY_DOWN: glRotatef (3.0, 0.0, -1.0, 0.0);
            break;
		case GLUT_KEY_LEFT: glRotatef (3.0, -1.0, 0.0, 0.0);
            break;
		case GLUT_KEY_RIGHT:glRotatef (3.0, 1.0, 0.0, 0.0);
            break;
    }
	glutPostRedisplay();
}

// Reset y exit del programa
void Accion (int Reset)
{
    // Reset todas las variables
	if (Reset) {
		spnArticulacion1->set_int_val (0);
		spnArticulacion2->set_int_val (0);
		spnArticulacion3->set_int_val (0);
		spnArticulacion4->set_int_val (0);
		spnArticulacion5->set_int_val (0);
		Rotaciones->reset();
		TransXY->set_x (0);
		TransXY->set_y (0);
		TransZ->set_z (0);
		delta1 = 0;
		delta2 = 0;
		delta3 = 0;
		delta4 = 0;
		delta5 = 0;
		delta6 = 0;
        conf1[0] = 0.0;
        conf1[1] = 0.0;
        conf1[2] = 0.0;
        seleccion_inversa = 0;
	}
    // Salida programa
	else {
        cleanup();
		exit (0);
    }
}

void inversa(int op)
{
    if (op == 1) {
        switch (lista_inversa->get_int_val()) {
            case 1:
                cout << "Dibujando esfera 1..." << endl;
                Accion(1);
                conf1[0] = 0.0;
                conf1[1] = 3.0;
                conf1[2] = 3.0;
                seleccion_inversa = 1;
                break;
            case 2:
                cout << "Dibujando esfera 2..." << endl;
                Accion(1);
                conf1[0] = 0.0;
                conf1[1] = 4.0;
                conf1[2] = -3.0;
                seleccion_inversa = 2;
                break;
            case 3:
                cout << "Dibujando esfera 3..." << endl;
                Accion(1);
                conf1[0] = 6.0;
                conf1[1] = 3.0;
                conf1[2] = 3.0;
                seleccion_inversa = 3;
                break;
        }
    }
    
    float px = conf1[0];
    float py = conf1[1];
    float pz = conf1[2];
    float px2 = powf(px, 2.0);
    float py2 = powf(py, 2.0);
    
    float d3 = elemento2Width/2;
    float d32 = powf(d3, 2.0);
    
    float a2 = 0.5 + 2.7;
    float a22 = powf(a2, 2.0);
    
    float a3 = elemento2Width/2;
    float a32 = powf(a3, 2.0);
    
    float d4 = largoEje3y4;
    float d42 = powf(d4, 2.0);
    
    float k = (px2 + py2 + px2 - a22 - a32 - d32 - d42) / 2*a2;
    float k2 = powf(k, 2.0);
    
    
    delta1 = - (atan2f(py, px) * 180 / PI ) - ( atan2(d3, sqrt(px2 + py2 - d32)) * 180 / PI );
    delta3 = ((atan2f(0.0, largoEje3y4) * 180 / PI) - ( atan2f(k, sqrt(a32 + d42 - k2)) * 180 / PI));
    
    s1 = sin(delta1);
    s3 = sin(delta3);
    
    c1 = cos(delta1);
    c3 = cos(delta3);
    
    float delta23 = atan2f( (-a3 - a2*c3)*pz - (c1*px + s1*py)*(d4 - a2*s3), (a2*s3 - d4)*pz - (a3 + a2*c3) * (c1*px + s1*py)) * 180/PI;
    
    delta2 = - (delta23 - delta3);
    
    s2 = sin(delta2);
    c2 = cos(delta2);
    
    cinematica_puma();
    
    delta4 =  (atan2f(cinematica[0][2]*s1 + cinematica[1][2]*c1, -cinematica[0][2]*c1*c23() - cinematica[1][2]*s1*c23() + cinematica[2][2]*s23() ) * 180/PI);
    
    s4 = sin(delta4);
    c4 = cos(delta4);
    
    delta5 = (atan2f(s5, c5));
    
    //delta1 = (atan2f(px, py) * 180 / PI ) - ( atan2(d3, sqrt(py2 + px2 - d32)) * 180 / PI );

    spnArticulacion1->set_int_val (delta1);
    spnArticulacion2->set_int_val (delta2);
    spnArticulacion3->set_int_val (delta3);
    spnArticulacion4->set_int_val (delta4);
    spnArticulacion5->set_int_val (delta5);
    
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    // Inits
    glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Doble buffer, depth y RGB colors
    
    // Ventana
	glutInitWindowPosition (80, 120);
	glutInitWindowSize (1000, 800);
	int ventana_principal = glutCreateWindow ("Robot Stanford");
    
	GLUI_Master.set_glutIdleFunc (NULL); // Funcion iddle (nada)
    
    // Creacion GLUI en la parte bottom de la ventana GLUT (principal)
	GLUI *glui_subwin = GLUI_Master.create_glui_subwindow (ventana_principal, GLUI_SUBWINDOW_BOTTOM);
    
    // Creacion de los Spinners con sus valores limites
	spnArticulacion1 = glui_subwin->add_spinner( "Pieza 1:", GLUI_SPINNER_INT, &delta1);
	spnArticulacion1->set_int_limits( -90, 90, GLUI_LIMIT_CLAMP);
    
	spnArticulacion2 = glui_subwin->add_spinner( "Pieza 2:", GLUI_SPINNER_INT, &delta2);
	spnArticulacion2->set_int_limits( -90, 90, GLUI_LIMIT_CLAMP);
    
	spnArticulacion3 = glui_subwin->add_spinner( "Pieza 3:", GLUI_SPINNER_INT, &delta3);
	spnArticulacion3->set_int_limits( -90, 90, GLUI_LIMIT_CLAMP);
    
	glui_subwin->add_column (false); // Salto a la siguiente columna
    
	spnArticulacion4 = glui_subwin->add_spinner( "Pieza 4:", GLUI_SPINNER_INT, &delta4);
	spnArticulacion4->set_int_limits( -95, 95, GLUI_LIMIT_CLAMP);
    
	spnArticulacion5 = glui_subwin->add_spinner( "Pieza 5 (Pinzas rota)", GLUI_SPINNER_INT, &delta5);
	spnArticulacion5->set_int_limits( -90, 90, GLUI_LIMIT_CLAMP);
    
    // Espacio de 3 columnas
	glui_subwin->add_column (false);
	glui_subwin->add_column (true);
	glui_subwin->add_column (false);
    
    
    // Creacion esfera rotacion boton y la resetea
	Rotaciones = glui_subwin->add_rotation ("Vista", matriz_rotar);
	Rotaciones->reset();
    
	glui_subwin->add_column (false); // Salto de columna
    
    // Creacion boton traslacion en X,Y (GLUI_TRANSLATION_XY)
	TransXY = glui_subwin->add_translation ("Mover XY", GLUI_TRANSLATION_XY, deltaXY);
    
	glui_subwin->add_column (false); // Salto de columna
    
    // Creacion boton traslacion Z
	TransZ  = glui_subwin->add_translation ("Mover Z",  GLUI_TRANSLATION_Z,  &deltaZ);
    
    // Espacio de 3 columnas
	glui_subwin->add_column (false);
	glui_subwin->add_column (true);
	glui_subwin->add_column (false);
    
    // List box de cinematica inversa
    lista_inversa = glui_subwin->add_listbox("Cinemática inversa", &seleccion_inversa, 1, inversa);
    lista_inversa->add_item(0, "Seleccione inversa");
    lista_inversa->add_item(1, "Inversa 1");
    lista_inversa->add_item(2, "Inversa 2");
    lista_inversa->add_item(3, "Inversa 3");
    
    glui_subwin->add_column (false);
    
    // Botones comunes con su funcion
	btnReset = glui_subwin->add_button ("Reset", 1, Accion);
	btnSalir = glui_subwin->add_button ("Salir", 0, Accion);
    
    // Le dice a glui donde esta los graficos principales (ventana principal)
	glui_subwin->set_main_gfx_window (ventana_principal);
    
	init(); // init
    
    // Funciones glut
	glutSpecialFunc (TeclaEspecial);
	glutDisplayFunc(display);
    
	glutMainLoop();
    
	return 0;
}