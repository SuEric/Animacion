//
//  mike.h
//  Animacion
//
//  Created by sueric on 27/10/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#ifndef Animacion_mike_h
#define Animacion_mike_h

#include "texture.h"
#include "objetos.h"
#include "motion.h"

/**Texturas**/

#define altoCuerpo 0.8
#define anchoCuerpo 0.5

#define anchoCabeza 0.25
#define altoCabeza 0.4

#define largoBrazo 0.25
#define anchoBrazo 0.1

#define largoPierna 0.35
#define anchoPierna 0.15

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
GLfloat vVerdeMike[] = {0.7372, 0.9333, 0.40784}; // Verde mike
GLfloat vAzulMezclilla[] = {0.2901, 0.4977, 0.54509}; // Azul mezclilla
GLfloat vVerdeAlien[] = {0.67843, 1.0, 0.18431}; // Verde Alien
GLfloat vAzulOscuro[] = {0.0, 0.0, 0.54117}; // Azul oscuro

int piso,arm,arm2,arm3,arm4;
int which;/* Mov */
double angr = 45.0, waitt=0,ang=0,velh=0;
float rotTrunk[] = {-7.0, -3.0, 3.0, 7.0, 11.0, 15.0, 11.0, 7.0, 3.0, -3.0, -7.0, -11.0, -15.0, -11.0};

void cuerpo(void)
{
    glDisable(GL_TEXTURE_2D);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vRojo);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0, altoCuerpo/2 + 1.0, 0.0);
    glRotatef(rotTrunk[which], 0.0, 1.0, 0.0);
    glScalef(anchoCuerpo, altoCuerpo, anchoCuerpo/2);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

void mechon()
{
	glColor3f(0,0,0);
	glPushMatrix();
	glScalef(1.0, 0.6, 0.7);
    gluCylinder(p,0.5,.5,3,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0,0,2);
    glRotatef(45,0,1,0);
    glScalef(1,.5,.7);
    gluSphere(p,.5,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0,0,2);
    glRotatef(45,0,1,0);
    glScalef(1,.5,.7);
    gluCylinder(p,.5,.2,2,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(1,0,3);
    glRotatef(90,0,1,0);
    glScalef(1,.5,.7);
    gluCylinder(p,.2,0,2,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(1,0,3);
    glRotatef(90,0,1,0);
    glScalef(1,.4,.7);
    gluSphere(p,.2,15,15);
	glPopMatrix();
}

void cabello()
{
	glPushMatrix();
    gluSphere(p,.10,.100,.20);
	glPopMatrix();
    
	glPushMatrix();
    mechon();
	glPopMatrix();
    
	glPushMatrix();
    glRotatef(180,1,0,0);
    mechon();
    glPopMatrix();
    
	glPushMatrix();
    glRotatef(120,1,0,0);
    glRotatef(18,0,0,1);
    mechon();
	glPopMatrix();
	
    glPushMatrix();
    glRotatef(45,1,0,0);
    mechon();
	glPopMatrix();
    
}

void cabeza(void)
{
    glPushMatrix();
    
    glTranslatef(0.0, (altoCuerpo + 1.0), 0.0);
    glRotatef(rotTrunk[which], 0.0, 1.0, 0.0);
    // Cabeza
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vAmarillo);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    glTranslatef(0.0, (altoCabeza/2), 0.0);
    glScalef(anchoCabeza + 0.5, altoCabeza, anchoCabeza);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Ojo der
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vBlanco);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vBlanco);
    glTranslatef(-0.1, (altoCabeza/3) + (0.1), anchoCabeza/2);
    glScalef(0.06, 0.06, 0.06/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Pupila der
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
    glTranslatef(-0.1, (altoCabeza/3) + (0.1), anchoCabeza/2 + 0.06/2);
    glScalef(0.03, 0.03, 0.03/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Ojo izq
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vBlanco);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vBlanco);
    glTranslatef(0.1, (altoCabeza/3) + (0.1), anchoCabeza/2);
    glScalef(0.06, 0.06, 0.06/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Pupila izq
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
    glTranslatef(0.1, (altoCabeza/3) + (0.1), anchoCabeza/2 + 0.06/2);
    glScalef(0.03, 0.03, 0.03/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Cabello
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(135.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPopMatrix();
}

void brazoIzq()
{
    which = 1;
    glPushMatrix();
    
    glRotatef((Walk_cycle[which][3][Step]), 1.0, 0.0, 0.0);
    
    // Hombro
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafe);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    glTranslatef(anchoCuerpo/2, 0.0, 0.0);
    glScalef(0.12, 0.12, 0.12);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Brazo
    glPushMatrix();
    
    // Parte superior
    glPushMatrix();
    glTranslatef( (anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2, - (largoBrazo/2), 0.0);
    glRotatef(30.0, 0.0, 0.0, 1.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Codo
    glPushMatrix();
    glTranslatef(( (anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2 ) + anchoBrazo/2, -(largoBrazo/2) - largoBrazo/2, 0.0);
    glScalef(0.12/1.8, 0.12/1.8, 0.12/1.8);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    glTranslatef(0.0, -largoBrazo, 0.0);
    glRotatef((Walk_cycle[which][4][Step]), 1.0, 0.0, 0.0);
    
    // Antebrazo
    glPushMatrix();
    glTranslatef(( (anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2 ) + anchoBrazo/2, -largoBrazo/2, 0.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Mano
    glPushMatrix();
    glTranslatef( ((anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2 ) + anchoBrazo/2, -largoBrazo/2 - largoBrazo/2, 0.0);
    glRotatef(120, 1, 0, 0);
    glRotatef(70, 0, 0, 1);
    glScalef(0.06, 0.05, 0.06);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void brazoDer()
{
    which = 0;
    
    glPushMatrix();
    
    glRotatef((Walk_cycle[which][3][Step]), 1.0, 0.0, 0.0);
    
    // Hombro
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafe);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    glTranslatef(-anchoCuerpo/2, 0.0, 0.0);
    glScalef(0.12, 0.12, 0.12);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Brazo
    glPushMatrix();
    
    // Parte superior
    glPushMatrix();
    glTranslatef(- (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2, -(largoBrazo/2), 0.0);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Codo
    glPushMatrix();
    glTranslatef(( - (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2 ) - anchoBrazo/2, -(largoBrazo/2) - largoBrazo/2, 0.0);
    glScalef(0.12/1.8, 0.12/1.8, 0.12/1.8);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    glTranslatef(0.0, -largoBrazo, 0.0);
    glRotatef((Walk_cycle[which][4][Step]), 1.0, 0.0, 0.0);
    
    // Antebrazo
    glPushMatrix();
    glTranslatef(( - (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2 ) - anchoBrazo/2, -(largoBrazo/2), 0.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Mano
    glPushMatrix();
    glTranslatef(( - (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2 ) - anchoBrazo/2, -largoBrazo/2 - largoBrazo/2, 0.0);
    glRotatef(120, 1, 0, 0);
    glRotatef(70, 0, 0, 1);
    glScalef(0.06, 0.05, 0.06);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void piernaIzq()
{
    which = 1;
    glPushMatrix();
    
    glRotatef(Walk_cycle[which][0][Step], 1.0, 0.0, 0.0);
    
    // Parte superior
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, -largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Rodilla
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, -largoPierna - (0.12/1.6)/2, 0.0);
    glScalef(0.12/1.6, 0.12/1.6, 0.12/1.6);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslatef(0.0, -largoPierna, 0.0);
    glRotatef(Walk_cycle[which][1][Step], 1.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, - largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glTranslatef(0.0, -largoPierna, 0.0);
    glRotatef((Walk_cycle[which][2][Step]), 1.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, 0.0, -0.06);
    glRotatef(180, 0,1,1);
    glScalef(0.1, 0.3, 0.1);
    glutSolidCone(0.5, 0.6, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void piernaDer(void)
{
    which = 0;
    
    glPushMatrix();
    
    glRotatef((Walk_cycle[which][0][Step]), 1.0, 0.0, 0.0);
    
    // Parte superior
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, -largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Rodilla
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, -largoPierna - (0.12/1.6)/2, 0.0);
    glScalef(0.12/1.6, 0.12/1.6, 0.12/1.6);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Parte superior
    glPushMatrix();
    
    glTranslatef(0.0, -largoPierna, 0.0);
    glRotatef((Walk_cycle[which][1][Step]), .0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, - largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glTranslatef(0.0, -largoPierna, 0.0);
    glRotatef((Walk_cycle[which][2][Step]), 1.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, 0.0, -0.06);
    glRotatef(180, 0,1,1);
    glScalef(0.1, 0.3, 0.1);
    glutSolidCone(0.5, 0.6, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void mike(void)
{
    glTranslatef(0.0, -8.3, 0.0);
    glScalef(5.0, 5.0, 5.0);
    cuerpo();
    
    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    cabeza();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, (anchoCuerpo + 1.0) + (0.08), 0.0);
    brazoIzq();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, (anchoCuerpo + 1.0) + (0.08), 0.0);
    brazoDer();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);
    piernaIzq();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);
    piernaDer();
    glPopMatrix();
}

#endif
