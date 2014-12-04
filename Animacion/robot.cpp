#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

static int art1 = 0, art2 = 0;

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
}

void brazo(void)
{
	glScalef (2.0, 0.4, 1.0);
	glutWireCube (1.0); // Brazo
}

void antebrazo(void)
{
    glPushMatrix();
	glScalef (2.0, 0.4, 1.0);
	glutWireCube (1.0); // Antebrazo
	glPopMatrix();
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	
    glPushMatrix();
	
    glTranslatef (-1.0, 0.0, 0.0);
	glRotatef ((GLfloat) art1, 0.0, 0.0, 1.0);
	glTranslatef (-1.0, 0.0, 0.0);
	
    glPushMatrix();
    brazo();
    glPopMatrix();
    
    glTranslatef(2.0, 0.0, 0.0);
	glRotatef ((GLfloat) art2, 0.0, 0.0, 1.0);
    
    glPushMatrix();
    antebrazo();
    glPopMatrix();
    
    glPopMatrix();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 's':
			art1 = (art1 + 5) % 360;
            cout << "Articulación 1:" << art1 << endl;
			glutPostRedisplay();
			break;
		case 'S':
			art1 = (art1 - 5) % 360;
            cout << "Articulación 1:" << art1 << endl;
			glutPostRedisplay();
			break;
		case 'e':
			art2 = (art2 + 5) % 360;
            cout << "Articulación 2:" << art2 << endl;
			glutPostRedisplay();
			break;
		case 'E':
			art2 = (art2 - 5) % 360;
            cout << "Articulación 2:" << art2 << endl;
			glutPostRedisplay();
			break;
		default:
			break;
    }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Robot");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
