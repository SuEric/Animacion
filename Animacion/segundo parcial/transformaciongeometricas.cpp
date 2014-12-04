#include <GL/glut.h>   

//RUTINA DE INICIALIZACION
void init (void)
{
     glClearColor(1.0,0.0,0.0,0.0);       
     glMatrixMode(GL_PROJECTION);         
     gluOrtho2D(-400, 600, -600,600);          
 }
 void triangulo(void)
 {
 	glBegin(GL_TRIANGLES);
 glVertex2i(270,270);
 glVertex2i(330,270);
 	glVertex2i(300,330);
 	glEnd();
 	glFlush();
 }
 void pinta(void)
 {
 	glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0,0,1);
triangulo();
glColor3f(0,1,0);
glScalef(1,-0.5,0);
triangulo();
 }
 
  int main(void)
{
    glutInitWindowSize(600,600);          
    glutCreateWindow("primitiva en opengl"); //crea la ventana de visualizacion
    init();        
    glutDisplayFunc(pinta);     //pinta lo que ordene pinta
    glutMainLoop();             //Espera Ordenes
}

