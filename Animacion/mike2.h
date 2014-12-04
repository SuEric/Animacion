//
//  mike2.h
//  Animacion
//
//  Created by sueric on 29/10/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#ifndef Animacion_mike2_h
#define Animacion_mike2_h

#include "texture.h"
#include "objetos.h"
#include "motion.h"

/**Texturas**/

#define anchoCuerpo 15.0
#define altoCuerpo 16.5

#define altoOjo 1.5
#define anchoOjo 0.5

// Colores
GLfloat vRosa[] = {1.0,0.5,0.6,1.0}; //rosa////////////////
GLfloat vVerde[] = {0.0,1.0,0.0,1.0}; //verde///////////////
GLfloat vAzul[] = {0.0,0.6,1.0,1.0}; //azul//////////////
GLfloat vMorado[] = {0.5,0.3,0.7,1.0}; //morado/////////////
GLfloat vAmarillo[] = {1.0,1.0,0.0,1.0}; //amarillo////////////
GLfloat vRojo[] = {1.0,0.0,0.0,1.0}; //rojo
GLfloat vCafe[] = {0.36,0.2,0.09,1.0}; //cafe
GLfloat vCafeClaro[] = {0.87, 0.72, 0.52}; //cafe claro
GLfloat vBlanco[] = {1.0,1.0,1.0,1.0}; //blanco///////////////
GLfloat vNaranja[] = {1.0,0.5,0.0,1.0};////naranja
GLfloat vNegro[] = {0.0,0.0,0.0}; //negro
GLfloat vGris[] = {0.6,0.6,0.6}; //gris
GLfloat vVerdeOscuro[] = {0.0, 0.4, 0.0, 1.0};
GLfloat vVerdeMike[] = {0.7372, 0.9333, 0.40784};
GLfloat vAzulMezclilla[] = {.2901, 0.4977, 0.54509};
GLfloat vVerdeAlien[] = {0.67843, 1.0, 0.18431};
GLfloat vAzulOscuro[] = {0.0, 0.0, 0.54117};

int piso,arm,arm2,arm3,arm4;
int which;/* Mov */
double angr = 45.0, waitt=0,ang=0,velh=0;


void cuerpo(void)
{
    //glDisable(GL_TEXTURE_2D); // Adios texturas
    
    glPushMatrix();
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vVerdeMike);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vVerdeMike);
    
    // Cuerpo
    glPushMatrix();
	glScalef(anchoCuerpo, altoCuerpo, anchoCuerpo);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
    
    // Hombros
    glPushMatrix();
	glTranslatef(anchoCuerpo + 2.3/2, 2.3, 0);
	glutSolidSphere(2.6, 10, 10);
	glPopMatrix();
    
    glPushMatrix();
	glTranslatef(- (anchoCuerpo + 2.3/2), 2.3, 0);
	glutSolidSphere(2.6, 10, 10);
	glPopMatrix();
    
    // Ojo
    glPushMatrix();
	glTranslatef(0, 7, 12);
	glRotatef(-22.0, 1.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 0.5);
	glutSolidSphere(7, 10, 10);
	glPopMatrix();
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vAzul);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
	
	glPushMatrix();
	glTranslatef(0, 8, 15);
	glRotatef(-22.0, 1.0, 0.0, 0.0);
	glScalef(0.9, 0.9, 0.2);
	glutSolidSphere(3, 20, 20);
	glPopMatrix();
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
	
	glPushMatrix();
	glTranslatef(0, 8.15, 15.2);
	glRotatef(-22.0, 1.0, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.2);
	glutSolidSphere(3, 20, 20);
	glPopMatrix();
    
    //LENGUA
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vRosa);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vRosa);
    
	glPushMatrix();
	glTranslatef(0, -4, 10);
	glRotatef(20, 1, 0, 0);
	glScalef(2.0, 1, 5);
	glutSolidSphere(2, 20, 20);
	glPopMatrix();
    
	//CUERNOS
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafeClaro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vCafeClaro);
    
	glPushMatrix();
	glTranslatef(8, 13, 0);
	glRotatef(-25, 0, 0, 1);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutSolidCone(1.5, 6.0, 10, 10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(-8, 13, 0);
	glRotatef(25, 0, 0, 1);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutSolidCone(1.5, 6.0, 10, 10);
	glPopMatrix();
    
    glPopMatrix();
    
}

void pie()
{
	glPushMatrix();
    
	glRotatef(10, 0, 1, 0);
    
    // Pie
	glPushMatrix();
	glScalef(1,0.4,2);
	glutSolidSphere(5,10,10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(-2.2, 0, 5.5);
	glRotatef(-20, 0, 1, 0);
	glScalef(0.4, 0.4, 1);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(-0, 0, 5.5);
	glScalef(0.4, 0.4, 1);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.2, 0, 5.5);
	glRotatef(20, 0, 1, 0);
	glScalef(0.4, 0.4, 1);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();
    
    // Uñas
    glPushMatrix();
    
	glRotatef(10, 0, 1, 0);
    
	glPushMatrix();
	glTranslatef(0, 0, 8.5);
	glutSolidCone(1,4, 10, 10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(3.2, 0, 8.5);
	glRotatef(20, 0, 1, 0);
	glutSolidCone(1, 4, 10, 10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(-3.2, 0, 8.5);
	glRotatef(-20, 0, 1, 0);
	glutSolidCone(1, 4, 10, 10);
	glPopMatrix();
    
	glPopMatrix();
    
	glPushMatrix();
    
	glRotatef(-10, 0, 1, 0);
    
	glPushMatrix();
	glTranslatef(0, 0, 8.5);
	glutSolidCone(1,4, 10, 10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(3.2, 0, 8.5);
	glRotatef(20, 0, 1, 0);
	glutSolidCone(1,4, 10, 10);
	glPopMatrix();
    
	glPopMatrix();
}
//pierna izquierda
void piernaI()
{
    which = 1;
    
    glPushMatrix();
	
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vVerdeMike);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vVerdeMike);
    
    glRotatef(Walk_cycle[which][0][Step], 1.0, 0.0, 0.0);
	
    // Parte sup
    glPushMatrix();
	glTranslatef(5, -17, 0);
	glRotatef(-5, 1, 0, -1);
	glScalef(0.4, 6, 0.4);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1,5, 20, 20);
	glPopMatrix();
    
    // falta translate cinematico
    glRotatef(Walk_cycle[which][1][Step], 1.0, 0.0, 0.0);
    
    // Rodilla
    glPushMatrix();
	glTranslatef(5.3, -23, 0.5);
	glutSolidSphere(2.3, 10, 10);
	glPopMatrix();
	   
    // Parte inf
    glPushMatrix();
	glTranslatef(5, -27, 0);
	glRotatef(5, 1,0, -1);
	glScalef(0.4, 5, 0.4);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1, 5, 20, 20);
	glPopMatrix();
    
    glTranslatef(6,-31,5);
    glRotatef((Walk_cycle[which][2][Step]), 1.0, 0.0, 0.0);
    
    pie();
    
    glPopMatrix();
}

//pierna derecha
void piernaD(void)
{
    which = 0;
    
    glPushMatrix();
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vVerdeMike);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vVerdeMike);
    
    glRotatef((Walk_cycle[which][0][Step]), 1.0, 0.0, 0.0);
    
    // Parte superior
    glPushMatrix();
	glTranslatef(-5, -17,0);
	glRotatef(-5,1,0,1);
	glScalef(0.4, 6, 0.4);
	glRotatef(90,1,0,0);
	glutSolidTorus(1,5,20,20);
	glPopMatrix();
    
    // Rodilla
    glPushMatrix();
	glTranslatef(-5.3,-23,.5);
	glutSolidSphere(2.3,10,10);
	glPopMatrix();
    
    glTranslatef(0.0, -16.5, 0.0);
    // falta translate cinematico
    glRotatef((Walk_cycle[which][1][Step]), 1.0, 0.0, 0.0);
    
    // Parte inferior
	glPushMatrix();
	glTranslatef(-5, -(altoCuerpo/2 + 6/2), 0);
	glRotatef(5, 1, 0, 1);
	glScalef(0.4, 5, 0.4);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1, 5, 20, 20);
	glPopMatrix();
    
    glTranslatef(-5, -15.5, 5);
    glRotatef((Walk_cycle[which][2][Step]), 1.0, 0.0, 0.0);
    
    pie();
    
    glPopMatrix();
	
}

void brazoD()
{
    which=0;
    
    glPushMatrix();
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vVerdeMike);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vVerdeMike);
	
    glRotatef((Walk_cycle[which][3][Step]), 1.0, 0.0, 0.0);
    
    // Parte superior
	glPushMatrix();
    glRotatef(80.0, 0.0, 0.0, 1.0);
    glTranslatef(-(6/2 + 2.3), anchoCuerpo + 2.6/2, 0);
	glScalef(6, 0.4, 0.4);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(1, 5, 20, 20);
	glPopMatrix();
    
    glTranslatef(5, -22, -3.0);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    
    // Codo
	glPushMatrix();
	glTranslatef(-27, 3, 0);
	glutSolidSphere(2.2, 10, 10);
	glPopMatrix();
    
    glTranslatef(0.0, 3, 0.0);
    glRotatef((Walk_cycle[which][4][Step]), 1.0, 0.0, 0.0);
    
    // Parte inferior
    glPushMatrix();
	glTranslatef(-24, 0, 7);
	glRotatef(20, 0, 1, 0);
	glScalef(0.4, 0.4, 8);
	glutSolidTorus(1, 5, 20, 20);
	glPopMatrix();
    
    // Mano
    glPushMatrix();
	
    glTranslatef(-21, 0, 16);
    
	glPushMatrix();
	glutSolidSphere(3, 10, 10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(0.6, -1.3, 1.2);
	glRotatef(90,1,0,0);
	glutSolidTorus(1,1, 20, 20);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(.6, 0, 1.2);
	glRotatef(90,1, 0, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(.6, 1.3, 1.22);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(-1.2, 2.5, 0);
	glRotatef(15, 1, 0, -1);
	glScalef(1, 4, 1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
    
	glPopMatrix();
    
    glPopMatrix();
}

void brazoI()
{
    which = 1;
    
    glPushMatrix();
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vVerdeMike);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vVerdeMike);
    
   	glRotatef((Walk_cycle[which][3][Step]), 1.0, 0.0, 0.0);
    
    // Parte superior
	glPushMatrix();
    glRotatef(100.0, 0.0, 0.0, 1.0);
    glTranslatef(-(6/2 + 2.3), - (anchoCuerpo + 2.6/2), 0);
	glScalef(6, 0.4, 0.4);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(1, 5, 20, 20);
	glPopMatrix();
    
    glTranslatef(40, -22, -3.0);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    
    // Codo
	glPushMatrix();
	glTranslatef(-26, 3, 0);
	glutSolidSphere(2.2, 10, 10);
	glPopMatrix();
    
    glTranslatef(0.0, 3, 0.0);
    glRotatef((Walk_cycle[which][4][Step]), 1.0, 0.0, 0.0);
    
    // Parte inferior
    glPushMatrix();
	glTranslatef(-24, 0, 7);
	glRotatef(20, 0, 1, 0);
	glScalef(0.4, 0.4, 8);
	glutSolidTorus(1, 5, 20, 20);
	glPopMatrix();
    
    // Mano
    glPushMatrix();
	
    glTranslatef(-21, 0, 16);
    
	glPushMatrix();
	glutSolidSphere(3, 10, 10);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(0.6, -1.3, 1.2);
	glRotatef(90,1,0,0);
	glutSolidTorus(1,1, 20, 20);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(.6, 0, 1.2);
	glRotatef(90,1, 0, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(.6, 1.3, 1.22);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();
    
	glPushMatrix();
	glTranslatef(-1.2, 2.5, 0);
	glRotatef(15, 1, 0, -1);
	glScalef(1, 4, 1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
    
	glPopMatrix();
    
    glPopMatrix();
	
}

void mike()
{
    glPushMatrix();
    
    glScalef(0.2, 0.2, 0.2); // Escala mas pequeño
    
    cuerpo();
    
    glPushMatrix();
    // Falta translate cinematico
    brazoI();
    glPopMatrix();
    
    glPushMatrix();
    // Falta translate cinematico
    brazoD();
    glPopMatrix();
    
    glPushMatrix();
	piernaD();
    glPopMatrix();
    
    /*
    glPushMatrix();
    piernaI();
    glPopMatrix();*/
    
    glPopMatrix();
}

#endif
