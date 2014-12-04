#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <unistd.h>

#include <GLUI/GLUI.h>

const int anchoVentana = 800;
const int altoVentana = 600;
const float aspectRatio = anchoVentana/altoVentana;

// Spinner para deltas
GLUI_Spinner *spinner1;
GLUI_Spinner *spinner2;

GLUI_Button *btnReset;
GLUI_Button *btnSalir;

// Rotaciones de cinemática
GLuint delta1 = 0;
GLuint delta2 = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void brazo(float largo)
{
    glPushMatrix();
    glScalef(largo, 0.5, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
}

void robot(void)
{
    glColor3f(0.6, 0.6, 0.6);

    glPushMatrix();
    
    // Brazo1
    glRotatef(delta1, 0.0, 0.0, 1.0); // spinner
    brazo(2.0);
    
    // Brazo2
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(delta2, 0.0, 0.0, 1.0); // spinner
    glTranslatef(2.0, 0.0, 0.0);
    brazo(2.0);
    
    glPopMatrix();
}

void display(void)
{
    // Proyección de la cámara
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspectRatio, 1.0f, 100.0f);
    
    // Camara (Escena completa)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0f, 10.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    robot();
    
    glutSwapBuffers();
}

void Accion (int Reset) {
	if (Reset) { // Reset todas las variables
		spinner1->set_int_val (0);
		spinner2->set_int_val (0);
		delta1 = 0;
		delta2 = 0;
	}
	else // Salida programa
		exit (0);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(anchoVentana, altoVentana);      //tamaÒo de la ventana de visualizacion
    
    GLuint ventana_principal = glutCreateWindow("Transformaciones");
    
    GLUI_Master.set_glutIdleFunc (NULL); // Funcion iddle (nada)
    
    // Creacion GLUI en la parte bottom de la ventana GLUT (principal)
	GLUI *glui_subwin = GLUI_Master.create_glui_subwindow (ventana_principal, GLUI_SUBWINDOW_BOTTOM);
    
    spinner1 = glui_subwin->add_spinner( "Pieza 1:", GLUI_SPINNER_INT, &delta1);
	spinner1->set_int_limits(0, 90, GLUI_LIMIT_CLAMP);
    
	spinner2 = glui_subwin->add_spinner( "Pieza 2:", GLUI_SPINNER_INT, &delta2);
	spinner2->set_int_limits( 0, 90, GLUI_LIMIT_CLAMP);
    
    glui_subwin->add_column(false);
    
    // Botones comunes con su funcion
	btnReset = glui_subwin->add_button ("Reset", 1, Accion);
	btnSalir = glui_subwin->add_button ("Salir", 0, Accion);
    
    // Le dice a glui donde esta los graficos principales (ventana principal)
	glui_subwin->set_main_gfx_window (ventana_principal);
    
    init();
    
    glutDisplayFunc(display);     //pinta lo que ordene pinta
    
	glutMainLoop();             //Espera Ordenes
    return 0;
}