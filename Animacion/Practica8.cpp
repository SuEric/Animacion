#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#define largoBrazo 4.0

float espacioTrabajo = largoBrazo * 6;

int anchoVentana = 800;
int altoVentana = 800;

int isAnimate = false;
static int animationPeriod = 25; // Invertavlo entre frames

float x00 = 0, y00 = 0; // Coordenada del click para inversa

float delta[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Directa

float deltaInv[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};   // Inversa

GLUquadric *qobj; // quadrico

// Angulos por inversa
void computeAngles(void)
{
	float distancia = sqrt(x00*x00 + y00*y00);   //distance from base to target
	float len = 4.0;  //link length;
	float n = 6.0;   //number of links
	float beta = 0.0,  betaPrev;  // initial condition
	float diff = 1000.0;  //A large value
	float numerator, denominator;
    float pi2 = 3.141593*0.5;
    float toDeg = 180.0/3.141593;
	float angle1, angle2;
    
    if(espacioTrabajo < distancia) deltaInv[0] = atan2(y00, x00) * toDeg;
    else {
        if(espacioTrabajo < pi2 * distancia) beta = pi2;  //Initial condition
		else beta = 3.0 * pi2;
        
        // Newton Modificado
 		while (diff > 0.0001) {
		    betaPrev = beta;
		    numerator = len * sin(betaPrev*0.5) - distancia * sin(betaPrev*0.5/n);
		    denominator = len*0.5 * cos(betaPrev*0.5) - distancia*0.5 * cos(betaPrev*0.5/n)/n;
		    beta = betaPrev - (numerator/denominator);
		    diff = fabs(beta - betaPrev);
	    }
        
		angle1 = atan2(y00, x00) + (pi2 - beta*0.5);
		angle2 = (pi2 - beta*0.5/n);
        
		deltaInv[0] = (angle1-angle2) * toDeg;
		for	(int i = 1; i < 6; i++) deltaInv[i] = beta*toDeg/n;
    
    }
}

void objetivo(void)
{
    glColor3f(0.0, 0.0, 0.0);
	
    glLineWidth(5.0);

	glBegin(GL_LINES);
    glVertex2d(x00-0.2, y00);
    glVertex2d(x00+0.2, y00);
    glVertex2d(x00, y00-0.2);
    glVertex2d(x00, y00+0.2);
	glEnd();
}

void base(void)
{
    glColor3f(0.0, 0.0, 0.0);
    
	glBegin(GL_POLYGON);
	glVertex2d( -2, 0);
	glVertex2d( -2, -1);
 	glVertex2d( 2, -1);
  	glVertex2d( 2, 0);
	glEnd();
}

void areaTotal(void)
{
    glColor4f(0.0, 0.0, 0.0, 0.2);
    
    glPushMatrix();
    gluSphere(qobj, espacioTrabajo, 32, 32);
    glPopMatrix();
}

void areaTrabajo(int brazo)
{
    switch (brazo) {
        case 0:
            glColor4f(1.0, 0.0, 0.0, 0.2);
            break;
        case 1:
            glColor4f(0.0, 1.0, 0.0, 0.2);
            break;
        case 2:
            glColor4f(1.0, 0.0, 1.0, 0.2);
            break;
        case 3:
            glColor4f(0.5, 0.5, 0.0, 0.2);
            break;
        case 4:
            glColor4f(1.0, 0.0, 1.0, 0.2);
            break;
        case 5:
            glColor4f(0.0, 0.0, 0.0, 0.2);
            break;
    }
    
    glPushMatrix();
    glTranslatef(largoBrazo/2, 0.0, 0.0);
    gluSphere(qobj, largoBrazo/2, 32, 32);
    glPopMatrix();
}

void brazo(int brazo)
{
	switch (brazo) {
        case 0:
            glColor3f(1.0, 0.0, 0.0);
            break;
        case 1:
            glColor3f(0.0, 1.0, 0.0);
            break;
        case 2:
            glColor3f(1.0, 0.0, 1.0);
            break;
        case 3:
            glColor3f(0.5, 0.5, 0.0);
            break;
        case 4:
            glColor3f(1.0, 0.0, 1.0);
            break;
        case 5:
            glColor3f(0.0, 0.0, 0.0);
            break;
    }
    
    glRotatef(delta[brazo], 0.0, 0.0, 1.);
    
	glBegin(GL_POLYGON);
    glVertex2f(0.0, -0.5);
    glVertex2f(largoBrazo, -0.5);
    glVertex2f(largoBrazo, 0.5);
    glVertex2f(0.0, 0.5);
	glEnd();
    
}

void roboto2D(void)
{
    base(); // Base
    areaTotal();
    
    // Brazos
    brazo(0);
    areaTrabajo(0);
    
	for(int i = 1; i < 6; i++) {
		glTranslatef(largoBrazo, 0.0, 0.0);
		brazo(i);
        areaTrabajo(i);
	}
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	objetivo();
    
    roboto2D();
    
	glutSwapBuffers();
    glFlush();
}

void init(void)
{
    glClearColor(0.6, 0.6, 0.6, 0.0);
    
    qobj = gluNewQuadric();
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-25.0, 25.0, -25., 25.);
}

void mouse(int b, int s, int x, int y)
{
	if(b == GLUT_LEFT_BUTTON && s == GLUT_DOWN){
		x00 = (float)(x*50)/anchoVentana - 25.0;
		y00 = (float)(altoVentana-y)*50.0/altoVentana - 25.0;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
            delta[0] = delta[0] + 10;
            glutPostRedisplay();
            break;
        case 'Q':
            delta[0] = delta[0] - 10;
            glutPostRedisplay();
            break;
            
        case 'w':
            delta[1] = delta[1] + 10;
            glutPostRedisplay();
            break;
        case 'W':
            delta[1] = delta[1] - 10;
            glutPostRedisplay();
            break;
            
        case 'e':
            delta[2] = delta[2] + 10;
            glutPostRedisplay();
            break;
        case 'E':
            delta[2] = delta[2] - 10;
            glutPostRedisplay();
            break;
            
        case 'r':
            delta[3] = delta[3] + 10;
            glutPostRedisplay();
            break;
        case 'R':
            delta[3] = delta[3] - 10;
            glutPostRedisplay();
            break;
            
        case 't':
            delta[4] = delta[4] + 10;
            glutPostRedisplay();
            break;
        case 'T':
            delta[4] = delta[4] - 10;
            glutPostRedisplay();
            break;
            
        case 'y':
            delta[5] = delta[5] + 10;
            glutPostRedisplay();
            break;
        case 'Y':
            delta[5] = delta[5] - 10;
            glutPostRedisplay();
            break;
            
        case ' ':
			computeAngles();
            if(isAnimate) isAnimate = 0;                        //inversa...
            else isAnimate = 1;
            break;
            
        case 27:
            exit(0);
            break;
    }
}

// Animacion inversa
void inversa()
{
    for (int i = 0; i < 6; i++) {
        if(delta[i] > deltaInv[i])
            delta[i]--;
        if(delta[i] < deltaInv[i])
            delta[i]++;
    }
    glutPostRedisplay();
    
}

void reshape(int ancho, int alto)
{
	anchoVentana = ancho;
	altoVentana = alto;
	glViewport(0, 0, ancho, alto);
}

void animate(int someValue)
{
    if (isAnimate) inversa();
    glutTimerFunc(animationPeriod, animate, 1);
}

int main( int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(anchoVentana, altoVentana);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Viborita 2D");
    
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(5, animate, 1);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    
    init();
    
    glutMainLoop();
    return 0;
}
