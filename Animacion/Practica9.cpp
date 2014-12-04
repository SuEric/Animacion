#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

#define anchoVentana 1000
#define altoVentana 800

// Colores
GLfloat vRosa[] = {1.0,0.5,0.6,1.0}; // Rosa
GLfloat vVerde[] = {0.0,1.0,0.0,1.0}; // Verde
GLfloat vAzul[] = {0.0,0.6,1.0,1.0}; // Azul
GLfloat vMorado[] = {0.5,0.3,0.7,1.0}; // Morado
GLfloat vAmarillo[] = {1.0,1.0,0.0,1.0}; // Amarillo
GLfloat vRojo[] = {1.0,0.0,0.0,1.0}; //Rojo
GLfloat vCafe[] = {0.36,0.2,0.09,1.0}; // Cafeani
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

// Luces
GLfloat luz_difusa[] = {0.1, 0.1, 0.1, 1.0};
GLfloat luz_ambiente[] = {0.1, 0.1, 0.1, 1.0};
GLfloat luz_especular[] = {0.1, 0.1, 0.1, 1.0};
GLfloat posicion[] = {0.0, 3.0, 45.0}; // Referencia

float alpha = 0, beta = 0; // Rotaciones de camara
int x00, y00; // Coordenada del click

float
tx = 0, ty = 0, tz = 0, // Traslaciones escenario
sx = 0.5, sy = 0.7, sz = 0.7; // Escalados escenario

GLUquadric *qobj;

void disco(float radioI, float radioE, float slices, float loops)		//cuadrico del disco
{
	GLUquadricObj *q = gluNewQuadric();
    
	gluQuadricDrawStyle (q, GLU_FILL);
	gluQuadricNormals   (q, GLU_SMOOTH);
	gluQuadricTexture   (q, GL_TRUE);
	gluDisk(q, radioI, radioE, slices, loops); // Dibuja disco (suelo)
	gluDeleteQuadric(q);
}

void piso(void)
{
	glPushMatrix();
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
    
    glRotatef(45, 0.0, 1.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    
    disco(0.0, 4.5, 4,4);
	
    glPopMatrix();
    
}

void pie_pequeno(void)
{
    glPushMatrix();
    glPopMatrix();
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 3.0f, 10.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia pantalla
    
    // Traslates, rotates y scales
    // de todo el escenario
	glTranslatef(tx, ty, tz); // tx,ty,tz nunca cambian (es el origen)
	glRotatef(alpha, 1.0f, 0.0f, 0.0f); // Rotate X escenario
	glRotatef(beta, 0.0f, 1.0f, 0.0f); // Rotate Y escenario
    glScalef(sx, sy, sz); // Escalado escenario
    
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    piso();
    glPopMatrix();
    
    glPushMatrix(); //Inicia pie pequeño
    
    pie_pequeno();
    
    glPopMatrix(); //Fin pie pequeño
    
    glutSwapBuffers(); // Intercambio de buffers, evita efecto de parpadeo
}

void onMouse(int button, int state, int x, int y)
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) x00= x; y00 = y; // Captura posicion del click
}

void onMotion(int x, int y)
{
	alpha = (alpha + (y - y00)); // Rotacion en X
	beta = (beta + (x - x00)); // Rotacion en Y
	x00 = x; y00 = y; // Actualiza posicion raton apretado
    
	glutPostRedisplay(); // Redibujado (no hay diferencia)
}

void init(void) //SE PINTA EL FONDO Y DECLARA LA ILUMINACION
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
	
	//CUADRICO
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
    
    //PROPIEDADES DE LA ILUMINACION
	glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);
	
    //SE ACTIVAN
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
}

void teclado (unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case '+':
            sx += 0.2;
            sy += 0.2;
            sz += 0.2;
            break;
        case '-':
            sx-=.2;
            sy-=.2;
            sz-=.2;
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
	glutInitWindowSize(anchoVentana, altoVentana);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("nnn");
	
    init();
	
    glutDisplayFunc(display);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion); // Giro de camara con mouse
	glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(teclado);
	
    glutMainLoop();
	
    return 0;
}