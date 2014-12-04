//ROTACION

//Graficacion, verano 2013
#include <GL/glut.h>   //archivo cabecera OpenGL, glu, glut
#include <stdlib.h>
/*glRotatef
positovo contrariodelreloj
negativo 
PRIMERO ANGULO, 0,0,1*/
//RUTINA DE INICIALIZACION
void init (void)
{
     glClearColor(1.0,0.0,0.0,0.0);       
     glMatrixMode(GL_PROJECTION);         
     gluOrtho2D(-400, 600, -600,600);          
 }
 
 //RUTINA QUE PINTA
 void pintaejes(void)
 {
 glBegin(GL_LINES);
 glVertex2i(-400,0);
 glVertex2i(400,0);
  glVertex2i(0,-400);
  glVertex2i(0,400);
   glEnd();
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
glRotatef(-45,0,0,1);
triangulo();
 }
 
 
 void t2D(void)
 {
      
  
   int y;
  //glColor3f(0,1,1);
    //pintaejes();
  
for(y=0;y<8;y++)
{
	 
glClear(GL_COLOR_BUFFER_BIT);	 
glTranslated(80,0,0);
      glColor3f(1,0,0);
    triangulo();
 
 glScalef(1,-1,0);
    Sleep(300);
   
   
      glFlush();
}
}     

//RUTINA PRINCIPAL

int main(void)
{
    glutInitWindowSize(800,800);      //tamaño de la ventana de visualizacion
    glutCreateWindow("ROTACION");
    init();        
    glutDisplayFunc(pinta);     //pinta lo que ordene pinta
	glutMainLoop();             //Espera Ordenes
}
            
