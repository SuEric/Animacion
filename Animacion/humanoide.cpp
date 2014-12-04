//
//  humanoide.cpp
//  Animacion
//
//  Created by sueric on 25/09/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.1415926535897932384626433832795

float
    alpha, beta, // Rotacion escenario
    sx = 1, sy = 1, sz = 1; // Escalados escenario
int xx, yy; // Posicion mouse click

// Quadrico y texturas
GLUquadricObj *qObj;
GLuint  texture_id[6];

GLfloat ctrlpoints1[3][3][3] = {
	{ {-0.05, 0.0, 0.1}, {0.0, 0.0, 0.1}, {0.05, 0.0, 0.1} },
	{ {-0.05, 0.1, 0.0}, {0.0, 0.1, 0.0}, {0.05, 0.1, 0.0} },
	{ {-0.03, 0.0, -0.15}, {0.0, 0.0, -0.15}, {-0.03, 0.0, -0.15} },
};

GLfloat ctrlpoints2[3][5][3] = {
	{{ -0.2, 0.0, 0.1}, { 0.1, 0.2, 0.0}, { 0.0, -0.2, 0.0}, { 0.0, 0.15, 0.0}, { 0.2, 0.0, 0.1}},
	{{ -0.15, 0.1, 0.0}, { -0.05, 0.15, -0.3}, { 0.0, 0.1, 0.2}, { 0.0, 0.15, -0.3}, { 0.05, 0.1, 0.0}},
	{{ 0.05, 0.25, 0.0}, { 0.05, 0.25, 0.0}, { 0.05, 0.25, 0.0}, { 0.05, 0.25, 0.0}, { 0.05, 0.25, 0.0}},
};

GLfloat ctrlpoints3[3][5][3] = {
	{{ -0.2, 0.0, 0.1}, { 0.0, 0.2, 0.0}, { 0.0, -0.2, 0.0}, { -0.1, 0.15, 0.0}, { 0.2, 0.0, 0.1}},
	{{ -0.05, 0.1, 0.0}, { 0.0, 0.15, -0.3}, { 0.0, 0.1, 0.2}, { 0.05, 0.15, -0.3}, { 0.15, 0.1, 0.0}},
	{{ -0.05, 0.25, 0.0}, { -0.05, 0.25, 0.0}, { -0.05, 0.25, 0.0}, { -0.05, 0.25, 0.0}, { -0.05, 0.25, 0.0}},
};

// Rotaciones piernas y Trunk
float rotLeg_up[] =  {30.0, 15.0, 0.0, -15.0, -30.0, -40.0, -30.0, -20.0, -15.0, -10.0, -5.0, 0.0, 10.0, 20.0};
float rotLeg_down[] = {5.0, 30.0, 60.0, 60.0, 50.0, 30.0, 20.0, 20.0, 10.0, 10.0, 5.0, 5.0, 5.0, 5.0};
float rotTrunk[] = {-7.0, -3.0, 3.0, 7.0, 11.0, 15.0, 11.0, 7.0, 3.0, -3.0, -7.0, -11.0, -15.0, -11.0};

int ndx_ll = 0, ndx_rl = 7, max_flex = 14; // rotaciones y max flexibilidad en piernas
float rot = 0.0, trans_x = 0.0, trans_z = 0.0;

int  LoadBMP(char *filename){
#define SAIR    {fclose(fp_arquivo); return -1;}
#define CTOI(C) (*(int*)&C)
    GLubyte     *image;
    GLubyte     Header[0x54];
    GLuint      DataPos, imageSize;
    GLsizei     Width,Height;
    int t, i;
    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE * fp_arquivo = fopen(filename,"rb");
    if (!fp_arquivo)
        return -1;
    if (fread(Header,1,0x36,fp_arquivo)!=0x36)
        SAIR;
    if (Header[0]!='B' || Header[1]!='M')
        SAIR;
    if (CTOI(Header[0x1E])!=0)
        SAIR;
    if (CTOI(Header[0x1C])!=24)
        SAIR;
    // Recupera los atributos de la altura y ancho de la imagen
    Width   = CTOI(Header[0x12]);
    Height  = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
    imageSize=Width*Height*3;
    // Llama a la imagen
    image = (GLubyte *) malloc ( imageSize );
    int retorno;
    retorno = fread(image,1,imageSize,fp_arquivo);
    if (retorno !=imageSize){ free (image); SAIR; }
    // Invierte los valores de R y B
    for ( i = 0; i < imageSize; i += 3 ){
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
    }
    // Tratamiento de textura para OpenGL
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    fclose (fp_arquivo);
    free (image);
    return 1;
}

void initializeGL(void){
	qObj = gluNewQuadric();
	gluQuadricDrawStyle( qObj, GLU_FILL);
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture( qObj, GL_TRUE);
    
	GLfloat ambiente[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat difusa[] = {0.6, 0.5, 0.4, 1.0};
	GLfloat especular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat posicion[] = {10.0, 10.0, 10.0, 1.0};
    
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    
	glPixelStorei (GL_UNPACK_ALIGNMENT, 6);
	glGenTextures (6, texture_id);
	glBindTexture (GL_TEXTURE_2D, texture_id[0]);
	LoadBMP ("abdmn.bmp");
	glBindTexture (GL_TEXTURE_2D, texture_id[1]);
	LoadBMP ("pech1.bmp");
	glBindTexture (GL_TEXTURE_2D, texture_id[2]);
	LoadBMP ("pech2.bmp");
	glBindTexture (GL_TEXTURE_2D, texture_id[3]);
	LoadBMP ("abdmn2.bmp");
	glBindTexture (GL_TEXTURE_2D, texture_id[4]);
	LoadBMP ("abdmn3.bmp");
	glBindTexture (GL_TEXTURE_2D, texture_id[5]);
	LoadBMP ("backg.bmp");
}

void headHuman(){
	glColor3f(0.0,1.0,0.8);
	glPushMatrix();
    glTranslatef(0.0, 0.275, -0.015);
    gluSphere(qObj, 0.133, 15, 15);
	glPopMatrix();
    
	glColor3f(0.95,0.8,0.65);
	glPushMatrix();
    glScalef(1.5, 1.0, 0.8);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.1, 0.04, 0.05, 15, 1);
	glPopMatrix();
	glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.06, 0.06, 0.15, 15, 1);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.0, 0.27, -0.01);
    gluSphere(qObj, 0.13, 15, 15);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.0, 0.17, 0.04);
    gluSphere(qObj, 0.09, 15, 15);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.0, 0.09, 0.11);
    glRotatef(-130, 1.0, 0.0, 0.0);
    glScalef(1.2, 1.0, 1.0);
    gluCylinder(qObj, 0.02, 0.06, 0.05, 15, 1);
    glScalef(1.0, 1.0, 0.5);
    gluSphere(qObj, 0.02, 15, 15);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.0, 0.26, 0.07);
    glRotatef(50, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.0, 0.02, 0.1, 3, 1);
	glPopMatrix();
	//Ojos
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
    glTranslatef(-0.04, 0.23, 0.083);
    glScalef(1.0, 0.7, 1.0);
    gluSphere(qObj, 0.03, 15, 15);
    glTranslatef(0.08, 0.0, 0.0);
    gluSphere(qObj, 0.03, 15, 15);
	glPopMatrix();
}

void hairHuman(){
	glColor3f(0.0,1.0,0.8);
	glPushMatrix();
    glTranslatef(0.0, 0.68, 0.0);
    glRotatef(-15, 0.0, 1.0, 0.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(-0.035, 0.68, -0.025);
    glRotatef(-35, 0.0, 1.0, 0.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.5, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(-0.05, 0.68, -0.05);
    glRotatef(-60, 0.0, 1.0, 0.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.5, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0.06, 0.68, -0.05);
    glRotatef(35, 0.0, 1.0, 0.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.5, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.07, 0.675, -0.07);
    glRotatef(65, 0.0, 1.0, 0.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.5, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.07, 0.685, -0.11);
    glRotatef(85, 0.0, 1.0, 0.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.5, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(-0.02, 0.24, -0.3);
    glRotatef(170, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(2.5, 1.5, 3.5);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.07, 0.27, -0.28);
    glRotatef(150, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(2.0, 1.0, 3.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.1, 0.3, -0.25);
    glRotatef(120, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(2.0, 1.0, 3.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(0.11, 0.55, -0.17);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.0, 1.5);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(-0.07, 0.21, -0.21);
    glRotatef(-170, 0.0, 1.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(2.5, 1.5, 3.5);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(-0.14, 0.24, -0.24);
    glRotatef(-150, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(2.5, 1.5, 3.5);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(-0.15, 0.3, -0.2);
    glRotatef(-150, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(2.0, 1.0, 3.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(-0.15, 0.3, -0.15);
    glRotatef(-120, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(2.0, 1.0, 3.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(-0.12, 0.55, -0.08);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(80, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.0, 1.5);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2, 0, 1, /**/9, /**/3, &ctrlpoints1[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
}

void armHuman(int ndx){
	glColor3f(0.95,0.8,0.65);
    
    // Rotacion de movimiento brazos
	glRotatef(rotLeg_up[ndx], 1.0, 0.0, 0.0);
	
    glPushMatrix();
    
    gluSphere(qObj, 0.07, 15, 15);
    
    glColor3f(0.4,0.3,0.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.07, 0.04, 0.35, 15, 1);
    
    glTranslatef(0.0, 0.0, 0.35);
    gluSphere(qObj, 0.04, 15, 15);
    glRotatef(-40, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.04, 0.03, 0.3, 15, 1);
    
    glTranslatef(0.0, 0.0, 0.3);
    
    glPushMatrix();
    glScalef(0.5, 1.0, 1.5);
    gluSphere(qObj, 0.04, 15, 15);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, -0.025, 0.0);
    gluCylinder(qObj, 0.015, 0.005, 0.13, 15, 1);
    glTranslatef(0.0, 0.015, 0.0);
    gluCylinder(qObj, 0.015, 0.005, 0.13, 15, 1);
    glTranslatef(0.0, 0.015, 0.0);
    gluCylinder(qObj, 0.015, 0.005, 0.13, 15, 1);
    glTranslatef(0.0, 0.015, 0.0);
    gluCylinder(qObj, 0.015, 0.005, 0.13, 15, 1);
    glRotatef(-20, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.015, 0.005, 0.1, 15, 1);
    glPopMatrix();
	
    glPopMatrix();
}

void wings(){
	glColor3f(0.4,0.3,0.5);
	
	glPushMatrix();
    glRotatef(-50, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(-0.8, -0.2, 0.0);
    glScalef(2.0, 2.0, 2.0);
    glRotatef(30, 1.0, 0.0, 0.0);
    glRotatef(40, 1.0, 1.0, 0.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, /**/5, 0, 1, /**/15, /**/3, &ctrlpoints2[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.15, 0.0);
    glRotatef(-85, 0.0, 1.0, 0.0);
    glRotatef(35, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.03, 0.01, 0.6, 15, 1);
    glPopMatrix();
	glPopMatrix();
    
	glPushMatrix();
    glRotatef(50, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.8, -0.2, 0.0);
    glScalef(2.0, 2.0, 2.0);
    glRotatef(30, 1.0, 0.0, 0.0);
    glRotatef(-30, 0.0, 1.0, 0.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, /**/5, 0, 1, /**/15, /**/3, &ctrlpoints3[0][0][0]);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.15, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef(27, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.03, 0.01, 0.6, 15, 1);
    glPopMatrix();
	glPopMatrix();
}

void trunkHuman(){
	glColor3f(0.95,0.8,0.65);
	
    //abdomen
	glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
    glTranslatef(0.0, -0.13, -0.02);
    glRotatef(30, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.0, 0.7);
    gluSphere(qObj, 0.15, 15, 15);
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
    
	glRotatef(rotTrunk[ndx_ll], 0.0, 1.0, 0.0);
	glRotatef(-15, 1.0, 0.0, 0.0);
    
	//Cabeza
	glPushMatrix();
    glRotatef(-rotTrunk[ndx_ll], 0.0, 1.0, 0.0);
    glRotatef(15, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.40, -0.1);
    headHuman();
	glPopMatrix();
	
    //Cabello
	glPushMatrix();
    glRotatef(-rotTrunk[ndx_ll], 0.0, 1.0, 0.0);
    glRotatef(15, 1.0, 0.0, 0.0);
    hairHuman();
	glPopMatrix();
	
    //Brazo derecho
	glPushMatrix();
    glRotatef(15, 1.0, 0.0, 0.0);
    glTranslatef(0.23, 0.34, -0.1);
    armHuman(ndx_rl);
	glPopMatrix();
    
    // Brazo izquierdo
	glPushMatrix();
    glRotatef(15, 1.0, 0.0, 0.0);
    glTranslatef(-0.23, 0.34, -0.1);
    armHuman(ndx_ll);
	glPopMatrix();
    
	//Alas de la cintura
    glPushMatrix();
    wings();
	glPopMatrix();
	glPushMatrix();
    //Alas de la cabeca
    glRotatef(-rotTrunk[ndx_ll], 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.7, 0.2);
    glScalef(0.4, 0.4, 0.4);
    wings();
	glPopMatrix();
    
	glColor3f(0.95,0.8,0.65);
	
    glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glScalef(1.0, 1.0, 0.7);
    glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
    gluSphere(qObj, 0.13, 15, 15);
    
    glRotatef(-90, 1.0, 0.0, 0.0);
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
    gluCylinder(qObj, 0.13, 0.18, 0.2, 15, 1);
    glDisable(GL_TEXTURE_2D);
    
    glTranslatef(0.0, 0.0, 0.2);
    gluCylinder(qObj, 0.18, 0.12, 0.2, 15, 1);
    
    glPushMatrix();
    glTranslatef(0.0, 0.01, 0.08);
    glRotatef(30, 1.0, 0.0, 0.0);
    gluSphere(qObj, 0.18, 15, 15);
    glPopMatrix();
    
    glScalef(2.0, 1.3, 1.0);
    glTranslatef(0.04, 0.01, 0.15);
    gluSphere(qObj, 0.1, 15, 15);
    
    glTranslatef(-0.08, 0.0, 0.0);
    gluSphere(qObj, 0.1, 15, 15);
    
	glPopMatrix();
    
	glPushMatrix();
    
    glPushMatrix();
    glTranslatef(-0.09, 0.2, 0.13);
    glRotatef(-150, 1.0, 0.0, 0.0);
    glRotatef(15, 0.0, 1.0, 0.0);
    gluCylinder(qObj, 0.04, 0.11, 0.1, 15, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.09, 0.2, 0.13);
    glRotatef(-150, 1.0, 0.0, 0.0);
    glRotatef(-15, 0.0, 1.0, 0.0);
    gluCylinder(qObj, 0.04, 0.11, 0.1, 15, 1);
    glPopMatrix();
    
    //Pechos
    glScalef(0.9, 1.0, 0.8);
    glTranslatef(-0.1, 0.2, 0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    gluSphere(qObj, 0.1, 15, 15);
    glTranslatef(0.2, 0.0, 0.0);
    glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    gluSphere(qObj, 0.1, 15, 15);
    glDisable(GL_TEXTURE_2D);
    
	glPopMatrix();
}

void leftLegHuman(){
	glColor3f(0.9,0.8,1.0);
	glPushMatrix();
    glScalef(1.0, 1.3, 1.2);
    glTranslatef(0.0, -0.04, -0.01);
    gluSphere(qObj, 0.12, 15, 15);
	glPopMatrix();
    
	glPushMatrix();
    // Parte superior
    glScalef(1.0, 1.0, 1.2);
    
    glTranslatef(0.02, -0.04, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.1, 0.06, 0.5, 15, 1);
    glTranslatef(0.0, 0.0, 0.5);
    
    // Parte inferior
    gluSphere(qObj, 0.06, 15, 15);
    
    glRotatef(rotLeg_down[ndx_ll], 1.0, 0.0, 0.0);
    
    gluCylinder(qObj, 0.06, 0.04, 0.4, 15, 1);
    
    // Pantorrilla
    glPushMatrix();
    glTranslatef(0.0, -0.01, 0.15);
    glScalef(1.0, 1.0, 2.5);
    gluSphere(qObj, 0.065, 15, 15);
    glPopMatrix();
    
    // Pie
    glColor3f(0.4,0.3,0.5);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.4);
    gluSphere(qObj, 0.04, 15, 15);
    glTranslatef(0.0, 0.0, 0.06);
    glScalef(1.0, 1.0, 1.2);
    gluSphere(qObj, 0.05, 15, 15);
    
    glPushMatrix();
    glRotatef(-60, 1.0, 0.0, 0.0);
    glScalef(1.8, 1.0, 1.0);
    gluCylinder(qObj, 0.03, 0.03, 0.1, 15, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.08, 0.05);
    glRotatef(-80, 1.0, 0.0, 0.0);
    glScalef(1.8, 1.0, 1.0);
    gluCylinder(qObj, 0.03, 0.01, 0.13, 15, 1);
    glPopMatrix();
    
    //Tacón
    glPushMatrix();
    glTranslatef(0.0, -0.02, 0.0);
    gluCylinder(qObj, 0.03, 0.01, 0.08, 15, 1);
    glPopMatrix();
    glPopMatrix();
    
    // Sujetador (pie)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.3);
    glScalef(1.0, 1.0, 1.5);
    gluSphere(qObj, 0.05, 15, 15);
    glTranslatef(0.03, 0.0, 0.0);
    glRotatef(180, 1.0, 0.0, 0.0);
    glRotatef(30, 0.0, 1.0, 0.0);
    glScalef(0.5, 1.0, 1.0);
    gluCylinder(qObj, 0.04, 0.0, 0.15, 10, 1);
    glPopMatrix();
	glPopMatrix();
}

void rightLegHuman(){
	glColor3f(0.95,0.8,0.65);
	glPushMatrix();
    glScalef(1.0, 1.3, 1.2);
    glTranslatef(0.0, -0.04, -0.01);
    gluSphere(qObj, 0.12, 15, 15);
	glPopMatrix();
	glPushMatrix();
    // Parte superior
    glColor3f(0.4,0.3,0.5);
    glScalef(1.0, 1.0, 1.2);
    
    glTranslatef(-0.015, -0.04, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(qObj, 0.1, 0.06, 0.5, 15, 1);
    glTranslatef(0.0, 0.0, 0.5);
    
    // Parte inferior
    gluSphere(qObj, 0.06, 15, 15);
    
    glRotatef(rotLeg_down[ndx_rl], 1.0, 0.0, 0.0);
    
    gluCylinder(qObj, 0.06, 0.04, 0.4, 15, 1);
    
    // Pantorrilla
    glPushMatrix();
    glTranslatef(0.0, -0.01, 0.15);
    glScalef(1.0, 1.0, 2.5);
    gluSphere(qObj, 0.065, 15, 15);
    glPopMatrix();
    
    // Pie
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.4);
    gluSphere(qObj, 0.04, 15, 15);
    glTranslatef(0.0, 0.0, 0.06);
    glScalef(1.0, 1.0, 1.2);
    gluSphere(qObj, 0.05, 15, 15);
    
    glPushMatrix();
    glRotatef(-60, 1.0, 0.0, 0.0);
    glScalef(1.8, 1.0, 1.0);
    gluCylinder(qObj, 0.03, 0.03, 0.1, 15, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.08, 0.05);
    glRotatef(-80, 1.0, 0.0, 0.0);
    glScalef(1.8, 1.0, 1.0);
    gluCylinder(qObj, 0.03, 0.01, 0.13, 15, 1);
    glPopMatrix();
    
    // Tacón
    glPushMatrix();
    glTranslatef(0.0, -0.02, 0.0);
    gluCylinder(qObj, 0.03, 0.01, 0.08, 15, 1);
    glPopMatrix();
    glPopMatrix();
    
    // Sujetador (pie)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.3);
    glScalef(1.0, 1.0, 1.5);
    gluSphere(qObj, 0.05, 15, 15);
    glTranslatef(-0.03, 0.0, 0.0);
    glRotatef(180, 1.0, 0.0, 0.0);
    glRotatef(-30, 0.0, 1.0, 0.0);
    glScalef(0.5, 1.0, 1.0);
    gluCylinder(qObj, 0.04, 0.0, 0.15, 10, 1);
    glPopMatrix();
	glPopMatrix();
}

// Renderizado
void myDisplay(){
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glPushMatrix();
    
    // Juego de camara
    //glTranslatef(0.0, 0.0, 0.0);
    glTranslatef(-trans_x, 0.0, -4.0);
    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);
    
    //glScalef(sx, sy, sz); // Escalado escenario
    
    glColor3f(0.9, 0.9, 0.9);
    glBindTexture(GL_TEXTURE_2D, texture_id[5]);
    
    //Suelo
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0, 0); glVertex3f(-6.0,-0.9,2);
    glTexCoord2f(1, 0); glVertex3f(6.0,-0.9,2);
    glTexCoord2f(1, 1); glVertex3f(6.0,-0.9,-10);
    glTexCoord2f(0, 1); glVertex3f(-6.0,-0.9,-10);
    glEnd();
    
    glColor3f(1.0,1.0,1.0);
    
    //Fondo frontal
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0, 0); glVertex3f(-6.0,-0.9,-10);
    glTexCoord2f(1, 0); glVertex3f(6.0,-0.9,-10);
    glTexCoord2f(1, 1); glVertex3f(6.0,5.0,-10);
    glTexCoord2f(0, 1); glVertex3f(-6.0,5.0,-10);
    
    //Fondo lateral izquierdo
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0, 0); glVertex3f(-6.0,-0.9,2);
    glTexCoord2f(1, 0); glVertex3f(-6.0,-0.9,-10);
    glTexCoord2f(1, 1); glVertex3f(-6.0,5.0,-10);
    glTexCoord2f(0, 1); glVertex3f(-6.0,5.0,2);
    
    //Fondo lateral derecho
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(1, 0); glVertex3f(6.0,-0.9,-10);
    glTexCoord2f(0, 0); glVertex3f(6.0,-0.9,2);
    glTexCoord2f(0, 1); glVertex3f(6.0,5.0,2);
    glTexCoord2f(1, 1); glVertex3f(6.0,5.0,-10);
    glEnd();
    
    glDisable( GL_TEXTURE_2D );
    
    glTranslatef(trans_x, 0.35, -trans_z);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef(rot, 0.0, 1.0, 0.0);
    
    //tronco
    glPushMatrix();
    trunkHuman();
    glPopMatrix();
    
    //Piernas
    glPushMatrix();
    glTranslatef(0.08, -0.16, -0.05);
    glRotatef(rotLeg_up[ndx_ll], 1.0, 0.0, 0.0);
    leftLegHuman();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.08, -0.16, -0.05);
    glRotatef(rotLeg_up[ndx_rl], 1.0, 0.0, 0.0);
    rightLegHuman();
    glPopMatrix();
	glPopMatrix();
    
	glFlush();
	glutSwapBuffers();
}

// Redimensionado escenario de ventana
void reshape( int w, int h )
{
	glViewport( 0, 0, w, h );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Funcion pasiva
void myIdle()
{
    glutPostRedisplay();
}

void onMouse(int button, int state, int x, int y)
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) {
        xx = x; yy = y;
    }
}

// Juego de camara
void onMotion(int x, int y)
{
	alpha = (alpha + (y - yy));
	beta = (beta + (x - xx));
	xx = x; yy = y;
    
	glutPostRedisplay();
}

void keyboard(int key, int z, int y)
{
	float tmp_trans;
    
	switch(key){
		case GLUT_KEY_LEFT: //Rotación del personaje
			rot += 5;
            
			//ModificaciÛn del grado de rotaciÛn de las piernas
			ndx_ll++;
			ndx_ll %= max_flex;
			ndx_rl++;
			ndx_rl %= max_flex;
            
			glutPostRedisplay();
			break;
            
		case GLUT_KEY_RIGHT: //Rotación del personaje
			rot-=5;
            
			//Modificación del grado de rotación de las piernas
			ndx_ll++;
			ndx_ll %= max_flex;
			ndx_rl++;
			ndx_rl %= max_flex;
            
			glutPostRedisplay();
			break;
            
		case GLUT_KEY_UP: // Translación del personaje
			tmp_trans = trans_x;
			trans_x += cos(rot * PI/180)*0.1;
			
            if( !(trans_x<5.0 && trans_x>-5.0) ) trans_x = tmp_trans;

			tmp_trans = trans_z;
			trans_z += sin(rot * PI/180)*0.1;
			
            if( !(trans_z >- 1.0 && trans_z < 9.0) ) trans_z = tmp_trans;
            
			// Modificación del grado de rotación de las piernas
			ndx_ll++;
			ndx_ll %= max_flex;
			ndx_rl++;
			ndx_rl %= max_flex;
            
			glutPostRedisplay();
			break;
	}
}

// Salida con ESC
void tecladoInput(unsigned char key, int x, int y)
{
    switch (key) {
        case '+':	sx += .2;
            sy += .2;
            sz += .2;
            break;
            
		case '-':	sx -= .2;
            sy -= .2;
            sz -= .2;
            break;
            
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Modelado y locomoción de un humanoide");
    
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
    glutReshapeFunc(reshape);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
    glutKeyboardFunc(tecladoInput);
	glutSpecialFunc(keyboard);
    
	initializeGL();
    
	glutMainLoop();
    return 0;
}