#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

float alpha, beta;
int x0, y0;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1,1,1);
	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
	
	glPushMatrix();
	glScalef (1,0.1,0.7);
	glutWireCube(1.0);
	glPopMatrix();

	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(-0.4,-0.25,0.25);
	glScalef (0.1,0.4,0.1);
	glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4,-0.25,-0.25);
	glScalef (0.1,0.4,0.1);
	glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4,-0.25,-0.25);
	glScalef (0.1,0.4,0.1);
	glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4,-0.25,0.25);
	glScalef (0.1,0.4,0.1);
	glutWireCube(1.0);
	glPopMatrix();

	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(-0.4,0.13,-0.25);
	glutWireTeapot(0.10);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void onMouse(int button, int state, int x, int y) 
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) 
	{
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Objeto compuesto");
	glutDisplayFunc(display);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	
    glutMainLoop();
    return 0;
}