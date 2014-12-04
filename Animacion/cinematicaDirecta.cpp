//
//  animacionElefante.cpp
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
#include <GLUI/glui.h>

#pragma comment (lib, "glui32.lib")

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

// Variables
int deltaBase = 0, delta1, delta2, delta3, delta4, delta5, delta6; // deltas 6gdl, deltaBase = 0
float matriz_rotar[16];
float deltaXY[2];
float deltaZ;

// Renderizado del robot
// base,soporte,elemento 1 2 3 4
void base() {
	glPushMatrix();
    glScalef (0.2 ,3.0 ,3.0 );
    glColor3d(.6,.6,.6);
    glutSolidCube(1.0);
	glPopMatrix();
}

void soporte() {
	
	glPushMatrix();
    
    glTranslatef(-1.0,0,0);
    
    glPushMatrix();
    glScalef (0.2 ,1.5 ,1.5);
    glColor3d(0.3,0.2,.5);
    glRotatef(120,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (0.2 ,1.5 ,1.5);
    glColor3d(0.3,0.2,.5);
    glRotatef(240,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (0.2 ,1.5 ,1.5);
    glColor3d(0.3,0.2,.5);
    glRotatef(0,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
	glPopMatrix();
    
	glPushMatrix();
    
    glPushMatrix();
    glScalef (2.7 ,1.0 ,1.0);
    glColor3d(.6,.6,.6);
    glRotatef(120,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (2.7 ,1.0 ,1.0);
    glColor3d(.6,.6,.6);
    glRotatef(240,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (2.7 ,1.0 ,1.0);
    glColor3d(.6,.6,.6);
    glRotatef(0,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
	glPopMatrix();
}

void elemento1()
{
	glPushMatrix();
    
    glTranslatef(0,0,1.0);
    glScalef(1.2 ,1.5,1);
    glColor3d(.45,.45,.45);
    glutSolidCube(1.0);
	glPopMatrix();
    
	glPushMatrix();
    
    glRotatef(90,0,1,0);
    
    glPushMatrix();
    glScalef (2.0 ,.7 ,.7);
    glColor3d(0.25,0.15,.45);
    glRotatef(120,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (2.0 ,.7 ,.7);
    glColor3d(0.3,0.2,.5);
    glRotatef(240,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (2.0 ,.7 ,.7);
    glColor3d(0.3,0.2,.5);
    glRotatef(0,1,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    
	glPopMatrix();
	
}

void elemento2() {
    glPushMatrix();
    
	glPushMatrix();
    glScalef (.7,5.0,.7);
    glColor3d(0.3,0.2,.5);
    glRotatef(0,1,0,0);
    glutSolidCube(1.0);
	glPopMatrix();
    
	glPushMatrix();
    glScalef (.5,5.05,.5);
    glColor3d(0,0,0);
    glRotatef(0,1,0,0);
    glutSolidCube(1.0);
	glPopMatrix();
    
	glPushMatrix();
    glColor3d(0.3,0.2,.5);
    glutSolidCube(0.5);
	glPopMatrix();
    glPopMatrix();
}

void elemento3(){
	glPushMatrix();
    
    glPushMatrix();
    glColor3d(0.3,0.2,.5);
    glScalef(1,1.5,1);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0.3,0);
    glScalef(1.3,.3,1.3);
    glColor3d(0.3,0.2,.5);
    glutSolidSphere(0.4,50,50);
    glPopMatrix();
    
	glPopMatrix();
}

void elemento4() {
	glPushMatrix();
    
    glRotatef(90,0,0,1);
    
    glPushMatrix();
    glScalef (2 ,.7 ,.7);
    glColor3d(.3,.3,.3);
    glRotatef(120,1,0,0);
    glutSolidCube(.5);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (2,.7 ,.7);
    glColor3d(.3,.3,.3);
    glRotatef(240,1,0,0);
    glutSolidCube(.5);
    glPopMatrix();
    
    glPushMatrix();
    glScalef (2 ,.7 ,.7);
    glColor3d(.3,.3,.3);
    glRotatef(0,1,0,0);
    glutSolidCube(.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(.7,.3,0);
    glScalef (2.0,.5,1.5);
    glColor3d(0.3,0.2,.5);
    glutSolidCube(.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(.7,-.3,0);
    glScalef (2.0,.5,1.5);
    glColor3d(0.3,0.2,.5);
    glutSolidCube(.3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.5,0,0);
    glScalef (.5 ,1,1);
    glColor3d(0.25,0.15,.45);
    glutSolidCube(.5);
    glPopMatrix();
     
	glPopMatrix();
}

// Funcion display, se llama n veces
void display (void) {
	glClearColor (0,0,0,0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glPushMatrix();
	glMultMatrixf(matriz_rotar); // Multiplica la matriz actual por la matriz de nuestra cinematica
	
    glTranslatef (deltaXY[1], deltaXY[0], deltaZ);
    
    // rotate deltaBase en X y la dibuja
	glRotatef (deltaBase, 1, 0, 0);
	base(); // Renderizado base
    
    // Rotate del delta1
	glTranslatef(1.25, 0.0, 0.0);
	glRotatef(delta1, 1.0, 0.0, 0.0);
	soporte();
    
    // Rotate delta2 en Z
	glTranslatef (1.5, 0, .4);
	glRotatef(-delta2, 0, 0, 1);
	elemento1();
    
    // Translate delta3 en Y
	glTranslatef (-1.3, 0.7, -0.3);
	glTranslated (1.3, float(float(delta3)/15), 1.3);
	elemento2();
    
    // Rotate delta4 en X
	glTranslatef (0, 2.5, 0);
	glRotatef(-delta4, 1, 0, 0);
	elemento3();
    
    // Rotate delta5 en Y y traslate delta6 en Y
	glTranslatef (0.0, 0.6 , 0.0);
	glTranslatef(0, float(float(delta6)/10), 0);
	glRotatef(-delta5, 0, 1, 0);
	elemento4();
    
	glPopMatrix();
    
	glFlush();
	glutSwapBuffers();
}

// Funcion init
void init (void) {
    
    glClearColor(0,0,0,0); // Fondo negro
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
void TeclaEspecial (int Key, int x, int y) {
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
void Accion (int Reset) {
    // Reset todas las variables
	if (Reset) {
		spnArticulacion1->set_int_val (0);
		spnArticulacion2->set_int_val (0);
		spnArticulacion3->set_int_val (0);
		spnArticulacion4->set_int_val (0);
		spnArticulacion5->set_int_val (0);
		spnArticulacion6->set_int_val (0);
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
	}
    // Salida programa
	else
		exit (0);
}

int main(int argc, char **argv)
{
    // Inits
    glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Doble buffer, depth y RGB colors
    
    // Ventana
	glutInitWindowPosition (80, 120);
	glutInitWindowSize (700, 500);
	int ventana_principal = glutCreateWindow ("Robot Stanford");
    
	GLUI_Master.set_glutIdleFunc (NULL); // Funcion iddle (nada)
    
    // Creacion GLUI en la parte bottom de la ventana GLUT (principal)
	GLUI *glui_subwin = GLUI_Master.create_glui_subwindow (ventana_principal, GLUI_SUBWINDOW_BOTTOM);
    
    // Creacion de los Spinners con sus valores limites
	spnArticulacion1 = glui_subwin->add_spinner( "Pieza 1:", GLUI_SPINNER_INT, &delta1);
	spnArticulacion1->set_int_limits( -90, 90, GLUI_LIMIT_CLAMP);
    
	spnArticulacion2 = glui_subwin->add_spinner( "Pieza 2:", GLUI_SPINNER_INT, &delta2);
	spnArticulacion2->set_int_limits( -45, 90, GLUI_LIMIT_CLAMP);
    
	spnArticulacion3 = glui_subwin->add_spinner( "Pieza 3:", GLUI_SPINNER_INT, &delta3);
	spnArticulacion3->set_int_limits( -30, 30, GLUI_LIMIT_CLAMP);
    
	glui_subwin->add_column (false); // Salto a la siguiente columna
    
	spnArticulacion4 = glui_subwin->add_spinner( "Pieza 4:", GLUI_SPINNER_INT, &delta4);
	spnArticulacion4->set_int_limits( -75, 75, GLUI_LIMIT_CLAMP);
    
	spnArticulacion5 = glui_subwin->add_spinner( "Pieza 5 (rota):", GLUI_SPINNER_INT, &delta5);
	spnArticulacion5->set_int_limits( -120, 120, GLUI_LIMIT_CLAMP);
    
	spnArticulacion6 = glui_subwin->add_spinner( "Pieza 5 (traslada):", GLUI_SPINNER_INT, &delta6);
	spnArticulacion6->set_int_limits( -2, 2, GLUI_LIMIT_CLAMP);
    
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
