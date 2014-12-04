//
//  Practica5.cpp
//  Animacion
//
//  Created by sueric on 25/09/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <unistd.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define largoCuerpo 1.2
#define anchoCuerpo 0.25

using namespace std;

#define PI 3.1415926535897932384626433832795

GLuint animationPeriod = 100; // Intervalo entre frames
GLuint texture[3];

float alpha = 0, beta = 0; // Rotaciones de camara
int x00, y00; // Coordenada del click

float
tx = 0, ty = 0, tz = 0, // Traslaciones escenario
sx = 0.5, sy = 0.7, sz = 0.7; // Escalados escenario

int direccionCola = 1;

float deltaCola = 0;

float RT = 0;

int R1[4] = {75,100,75,100};
int R2[4] = {5,15,5,15};

int  LoadBMP(char *filename)
{
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

void Esfera ( float radio,float longitud,float latitud  )			//cuadrico de la esfera
{
    GLUquadricObj *q = gluNewQuadric();
    gluQuadricDrawStyle ( q, GLU_FILL   );
    gluQuadricNormals   ( q, GLU_SMOOTH );
    gluQuadricTexture   ( q, GL_TRUE    );
    
    gluSphere ( q, radio, longitud, latitud );
    gluDeleteQuadric ( q );
}

void Cilindro( float baseI,float baseS,float altura, float slices, float stacks)		//cuadrico del cilindro
{
	GLUquadricObj*  q = gluNewQuadric ( );
	GLUquadricObj*  a = gluNewQuadric ( );
	GLUquadricObj*  b = gluNewQuadric ( );
    
    gluQuadricDrawStyle ( q, GLU_FILL   );
    gluQuadricNormals   ( q, GLU_SMOOTH );
    gluQuadricTexture   ( q, GL_TRUE    );
    
    gluQuadricDrawStyle ( a, GLU_FILL   );
    gluQuadricNormals   ( a, GLU_SMOOTH );
    gluQuadricTexture   ( a, GL_TRUE    );
    
    gluQuadricDrawStyle ( b, GLU_FILL   );
    gluQuadricNormals   ( b, GLU_SMOOTH );
    gluQuadricTexture   ( b, GL_TRUE    );
    
	gluQuadricOrientation(a, GLU_INSIDE);
	gluDisk(a, 0, baseI, slices, stacks);
	gluCylinder ( q, baseI, baseS, altura,slices,stacks);
	glTranslatef(0,0,altura);
	gluDisk(b, 0, baseS, slices, stacks);
	gluDeleteQuadric ( q );
	gluDeleteQuadric ( a );
	gluDeleteQuadric ( b );
}

void disco(float radioI, float radioE, float slices, float loops)		//cuadrico del disco
{
	GLUquadricObj *q = gluNewQuadric();
    
	gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);
	gluDisk(q, radioI, radioE, slices, loops); // Dibuja disco (suelo)
	gluDeleteQuadric(q);
}

void piso()
{
	GLfloat mat_ambient[] = {0.0215,0.1745,0.0215,0.55};
	GLfloat mat_diffuse[] = {0.07568,0.61424,0.07568,0.55};
	GLfloat mat_specular[]= {0.633,0.727811,0.633,0.55};
	GLfloat shininess = 96.8;
    
	glPushMatrix();
    
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf  (GL_FRONT, GL_SHININESS, shininess);
    
    glTranslatef(0,-.65,-0.5);
    glRotatef(45, 0.0, 1.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);

    disco(0.0, 30, 4,4);
	
    glPopMatrix();
}

void paredes()
{
    GLUquadricObj *q = gluNewQuadric();
    
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);
    
	glPushMatrix();
    
    glTranslatef(0,-.65,-0.5);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glRotatef(45, 0.0, 0.0, 1.0);
    gluCylinder(q, 30, 30, 30, 4, 32);
	gluDeleteQuadric(q);

	
    glPopMatrix();

}

void cuerpo(void)
{
    GLUquadricObj *qobj = gluNewQuadric();
    GLdouble incremento = 0.05;
    
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, GL_TRUE);
    
    glPushMatrix();
    
    glPushMatrix();
    for (float i = 0; i < 0.6; i += incremento) {
        glTranslatef(0.1, 0.0, 0.0);
        
        if (i < 0.25) {
            glPushMatrix();
            gluSphere(qobj, 0.1 + i, 32, 32);
            glPopMatrix();
            
            glPushMatrix();
            glRotatef(90.0, 0.0, 1.0, 0.0);
            gluCylinder(qobj, 0.05, 0.1 + i, 0.1, 30, 30);
            glPopMatrix();
        }
        else {
            if (i >= 0.25 && i <= .35) {
                //cout << "MENSAJE" << endl;
                
                glPushMatrix();
                gluSphere(qobj, 0.3, 32, 32);
                glPopMatrix();
                
                glPushMatrix();
                glRotatef(90.0, 0.0, 1.0, 0.0);
                gluCylinder(qobj, 0.05, 0.3, 0.1, 32, 32);
                glPopMatrix();
            }
            else {
                glPushMatrix();
                gluSphere(qobj, 0.65 - i, 32, 32);
                glPopMatrix();
                
                glPushMatrix();
                glRotatef(90.0, 0.0, 1.0, 0.0);
                gluCylinder(qobj, 0.65 - i, 0.05, 0.1, 30, 30);
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
    
    glTranslatef(0.4, 0.0, 0.0);
    
    glPushMatrix();
    for (int i = 0; i < 10; i ++) {
        glTranslatef(-0.1, 0.0, 0.0);
        
        if (i < 7) {
            glRotatef(-10.0, 0.0, 0.0, 1.0);
            
            glPushMatrix();
            gluSphere(qobj, 0.15, 32, 32);
            glPopMatrix();
            
            glPushMatrix();
            glRotatef(90.0, 0.0, 1.0, 0.0);
            gluCylinder(qobj, 0.15, 0.05, 0.1, 30, 30);
            glPopMatrix();
        }
        else {
            glRotatef(10.0, 0.0, 0.0, 1.0);
            
            glPushMatrix();
            gluSphere(qobj, 0.15, 32, 32);
            glPopMatrix();
            
            glPushMatrix();
            glRotatef(90.0, 0.0, 1.0, 0.0);
            gluCylinder(qobj, 0.15, 0.05, 0.1, 30, 30);
            glPopMatrix();
        }
    }
    glPopMatrix();
    
    glPopMatrix();
}

void cola(void)
{
    GLUquadricObj *qobj = gluNewQuadric();
    GLdouble incremento = 0.01;
    
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, GL_TRUE);
    
    glPushMatrix();
    
    glTranslatef(largoCuerpo, -0.2, 0.0);
    glRotatef(deltaCola, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.2, 0.0);
    glScalef(15.5, 1.3, 1.0);
    
    glPushMatrix();
    for (float i = 0; i < 0.05; i += incremento) {
        
        glTranslatef(0.01, 0.0, 0.0);
        
        glPushMatrix();
        glScalef(0.2, 1.0, 1.0);
        gluSphere(qobj, 0.08 - i, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.08 - i, 0.02, 0.005, 30, 30);
        glPopMatrix();
    }
    glPopMatrix();
    
    glPopMatrix();
}

void pata1(int R1, int R2)
{
    GLUquadricObj *qobj = gluNewQuadric();
    
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, GL_TRUE);
    
    glPushMatrix();
    
    glTranslatef(largoCuerpo/2.5, -anchoCuerpo, anchoCuerpo/1.5);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    
    glPushMatrix();
    for (int i = 0; i < 2; i ++) {
        glTranslatef(-0.1, 0.0, 0.0);
        glRotatef(20.0, 0.0, 1.0, 0.0);
        
        glPushMatrix();
        gluSphere(qobj, 0.08, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.08, 0.05, 0.1, 30, 30);
        glPopMatrix();
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.18, 0.0, 0.05);
    for (int i = 0; i < 6; i++) {
        glTranslatef(-0.1, 0.0, 0.0);
        
        glPushMatrix();
        gluSphere(qobj, 0.08, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.08, 0.05, 0.05, 30, 30);
        glPopMatrix();
    }
    glPopMatrix();
    
    glPopMatrix();
}

void pata2(int R1, int R2)
{
    GLUquadricObj *qobj = gluNewQuadric();
    
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, GL_TRUE);
    
    glPushMatrix();
    
    glTranslatef(largoCuerpo/2.5, -anchoCuerpo, -anchoCuerpo/1.5);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    
    glPushMatrix();
    for (int i = 0; i < 2; i ++) {
        glTranslatef(-0.1, 0.0, 0.0);
        glRotatef(-20.0, 0.0, 1.0, 0.0);
        
        glPushMatrix();
        gluSphere(qobj, 0.08, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.08, 0.05, 0.1, 30, 30);
        glPopMatrix();
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.18, 0.0, -0.05);
    for (int i = 0; i < 6; i++) {
        glTranslatef(-0.1, 0.0, 0.0);
        
        glPushMatrix();
        gluSphere(qobj, 0.08, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.08, 0.05, 0.05, 30, 30);
        glPopMatrix();
    }
    glPopMatrix();
    
    glPopMatrix();
}

void pata3(int R1, int R2)
{
    //pata3
    
    glPushMatrix();
    
    glPushMatrix();
    
    glTranslatef(.5,-.25,1.85);
    glRotatef(R1,1,0,0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glRotatef(-20.0, 1.0, 0.0, 0.0);
    glScalef(0.3, 0.4, 0.4);
    
    Cilindro(0.4, 0.25, 1.2, 20, 20);
    
    glPushMatrix();
    glScalef(1,1.05,.75);
    Esfera(.25,25,20);
    glPopMatrix();
    
    glTranslatef(0,0,-.1);
    glRotatef(R2,1,0,0);
    Cilindro(.25,.25,1.2,20,20);
    
    glTranslatef(0,.01,0);
    glScalef(1,1.1,.5);
    Esfera(.25,25,20);
    
    glPopMatrix();
    
    glPopMatrix();
}

void pata4(void)
{
    GLUquadricObj *qobj = gluNewQuadric();
    
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, GL_TRUE);
    
    glPushMatrix();
    
    glTranslatef(largoCuerpo/1.5, -anchoCuerpo, anchoCuerpo/1.5);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    
    glPushMatrix();
    for (int i = 0; i < 2; i ++) {
        glTranslatef(-0.1, 0.0, 0.0);
        glRotatef(20.0, 0.0, 1.0, 0.0);
        
        glPushMatrix();
        gluSphere(qobj, 0.08, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.08, 0.05, 0.1, 30, 30);
        glPopMatrix();
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.18, 0.0, 0.05);
    for (int i = 0; i < 6; i++) {
        glTranslatef(-0.1, 0.0, 0.0);
        
        glPushMatrix();
        gluSphere(qobj, 0.08, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.08, 0.05, 0.05, 30, 30);
        glPopMatrix();
    }
    glPopMatrix();
    
    glPopMatrix();
}

void pie_pequeno(void)
{
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    cuerpo();
    
    pata2(R1[1],R2[1]);
	pata3(R1[2],R2[2]);
    
    cola();
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 3.0f, 10.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // Traslates, rotates y scales
    // de todo el escenario
	glTranslatef(tx, ty, tz); // tx,ty,tz nunca cambian (es el origen)
	glRotatef(alpha, 1.0f, 0.0f, 0.0f); // Rotate X escenario
	glRotatef(beta, 0.0f, 1.0f, 0.0f); // Rotate Y escenario
    glScalef(sx, sy, sz); // Escalado escenario
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
	piso(); // Dibuja piso
	
    //glBindTexture(GL_TEXTURE_2D, texture[1]);
    //paredes();
    
    glTranslatef(0.0, 0.5, 0.0);
    pie_pequeno();
    
	glFlush();
	glutSwapBuffers();
}

void init(void)
{
    GLfloat light_ambient[] = {0.35, 0.25, 0.75, 1.0};
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat light_position[] = {0.0, 0, 1, 0.0};
    
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
    
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glShadeModel (GL_SMOOTH);
    
	glClearColor (0.6, 0.6, 0.6, 0.0);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glClearDepth (1.0);
    
    glEnable(GL_COLOR_MATERIAL);
    
    // Texturas
    glEnable(GL_TEXTURE_2D);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(2, texture);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    if (LoadBMP("jungle.bmp") == -1) cout << "ERROR" << endl;
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    if (LoadBMP("jungle.bmp") == -1) cout << "ERROR" << endl;
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    if (LoadBMP("piel_cuello_largo.bmp") == -1) cout << "ERROR2" << endl;
}

void teclado(char unsigned key, int x, int y)
{
    switch(key)
	{
		case '+':
            sx += 0.2;
            sy += 0.2;
            sz += 0.2;
            break;
            
		case '-':
            sx -= 0.2;
            sy -= 0.2;
            sz -= 0.2;
            break;
            
		case 27:
			exit(0);
			break;
            
		default:
			break;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport (0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
    
	if (w <= h)
		glOrtho(-2.2,2.2,-2.2 * (GLfloat)h / (GLfloat)w, 2.2 * (GLfloat)h/(GLfloat)w, -4.4,4.4);
	else
		glOrtho(-2.2 * (GLfloat)w / (GLfloat)h, 2.2 * (GLfloat)w/(GLfloat)h,-2.2,2.2, -4.4,4.4);
    
	glMatrixMode(GL_MODELVIEW);
}

void onMotion(int x, int y)
{
	alpha = (alpha + (y - y00)); // Rotacion en X
	beta = (beta + (x - x00)); // Rotacion en Y
	x00 = x; y00 = y; // Actualiza posicion raton apretado
    
	glutPostRedisplay(); // Redibujado (no hay diferencia)
}

void onMouse(int button, int state, int x, int y)
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) x00= x; y00 = y; // Captura posicion del click
}

void animate(int v)
{
    if (deltaCola >= 60) direccionCola = 1;
    if (deltaCola <= -60) direccionCola = 0;
    
    if (direccionCola == 0) deltaCola += 5;
    if (direccionCola == 1) deltaCola -= 5;
    
    glutTimerFunc(animationPeriod, animate, 1);
    
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(950, 750);
    glutInitWindowPosition(40,10);
    glutCreateWindow("Elefante");
	
    //glutFullScreen();
	init();
	
    glutDisplayFunc(display);			//llama funcion display
	glutReshapeFunc(reshape);
	glutKeyboardFunc(teclado);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion); // Giro de camara con mouse
    glutTimerFunc(5, animate, 1);
	
	glutMainLoop();
    return 0;
}