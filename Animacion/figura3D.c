#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

float alpha, beta;
int x0, y0;

void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT); // Limpia buffers
    
	glMatrixMode(GL_PROJECTION); // Afecto la matriz de proyección
	glLoadIdentity(); // Le asigno a la matriz de proyección la matriz por default
    
	gluPerspective(20.0f, 1.0f, 1.0f, 10.0f); // Establezco como es la perspectiva

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f);
	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
	glutWireCube(0.5);
	//glFlush(); // Mandar a pintar
	glutSwapBuffers();
}
void onMouse(int button, int state, int x, int y) 
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) {
		x0 = x; y0 = y;
		}
}

void onMotion(int x, int y) 
{
	alpha = (alpha + (y - y0));
	beta = (beta + (x - x0));
	x0 = x; y0 = y;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
    glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("Uso del mouse");
    
	glutDisplayFunc(display);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	
    glutMainLoop();
    
    return 0;
}