
#include <GL/glut.h> 
void init (void)
{
     glClearColor(1.0,1.0,1.0,1.0);       
     glMatrixMode(GL_PROJECTION);         
     gluOrtho2D(-600, 600, -600,600);          
 }
 
 void pintatriangulo()
 {
 	glBegin(GL_TRIANGLES);
 	glVertex2i(100,100);
 	glVertex2i(400,100);
 	glVertex2i(250,500);
 	glEnd();
 	glFlush();
 }
 void Transformaciones()
 {
 glClear(GL_COLOR_BUFFER_BIT);
 
 glPushMatrix();
 glColor3f(0,1,0); 
 pintatriangulo();
 
 glColor3f(0,0,1);
 glTranslatef(100,10,0);
 pintatriangulo();
 
  glPopMatrix();
 
 glColor3f(0,0,0); 
 glTranslatef(90,5,0);
 pintatriangulo();
 }
 
 int main()
 {
 	glutInitWindowSize(600,600);
 	glutCreateWindow("transformacione");
 	init();        
    glutDisplayFunc(Transformaciones);     //pinta lo que ordene pinta
	glutMainLoop(); 
 }
