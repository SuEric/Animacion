//ROTACION

//Graficacion, verano 2013
#include <GL/glut.h>   //archivo cabecera OpenGL, glu, glut
#include <stdlib.h>
#include <math.h> 


void init (void)
{
     glClearColor(1.0,1.0,1.0,1.0);       
     glMatrixMode(GL_PROJECTION);         
     gluOrtho2D(-400, 600, -600,600);          
 }
 
 void espalda(void)
 {
 	glColor3f(0,1,1);
 	glBegin(GL_LINES);
 	glVertex2i(200,80);
 	glVertex2i(200,180);
 		glEnd();
 }
 
 void piernaizq(void)
 {
 		glColor3f(0,1,1);
 	glBegin(GL_LINES);
 	glVertex2i(200,80);
 	glVertex2i(280,95);
 	glEnd();
 }
 
 void piernader(void)
 {
 		glColor3f(0,1,1);
 	glBegin(GL_LINES);
 	glVertex2i(200,80);
 	glVertex2i(240,65);
 		glEnd();
 }
 
 void brazoizq(void)
 {
 		glColor3f(0,1,1);
 	glBegin(GL_LINES);
 	glVertex2i(200,160);
 	glVertex2i(240,160);
 		glEnd();
 }
 
 void brazoder(void)
 {
 		glColor3f(0,1,1);
 	glBegin(GL_LINES);
 	glVertex2i(200,155);
 	glVertex2i(260,155);
 		glEnd();
 }
void ojo(void)
{
	glPointSize(4);
	glColor3f(0,0,0);
 	glBegin(GL_POINTS);
 	glVertex2i(210,210);

 		glEnd();
}
 void cabeza(void)
 {
      double radio=20.0;
     int n=500;
     double tela, Incremento, x, y;
     Incremento=2*M_PI/n;
     glPointSize(1);
     
     for(int i=0;i<=n;i++)
     {
     	//for(int j=0;j<=radio;j++)
     //	{
     	
     	tela=i*Incremento;
     	x=radio*cos(tela);
     	y=radio*sin(tela);
     	
     	glBegin(GL_POINTS);
     	glVertex2d(x+200,y+200);
     	glEnd();
     //}
     }
     
}     

void boca(void)
{
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	
	glVertex2i(200,190);
	glVertex2i(210,190);
	glEnd();
}

void pinta(void)
{
	espalda();
	cabeza();
	ojo();
	//boca();
	
	brazoizq();
	piernader();
	piernaizq();
	
} 
void brazoder2(void)
{
	glBegin(GL_LINES);
	glVertex2i(200,155);
	glVertex2i(260,170);
	glEnd();
}
void boca2(void)
{
	glBegin(GL_LINES);
	glVertex2i(210,190);
	glVertex2i(220,190);
	glEnd();
}

void t2D(void)
 {
 		
   int i;
  
    
    for(i=1;i<16;i++)
    {
    glClear(GL_COLOR_BUFFER_BIT);
    pinta();
    Sleep(1500);
    if((i%2)==0)
	{
    brazoder();
    boca();
    }
    else
    {
    	brazoder2();
		boca2();
	}
     Sleep(600);
	glFlush();

	}
}
   
  


//RUTINA PRINCIPAL

int main(void)
{
    glutInitWindowSize(800,800);      //tama�o de la ventana de visualizacion
    glutCreateWindow("ROTACION");
    init();        
    glutDisplayFunc(t2D);     //pinta lo que ordene pinta
	glutMainLoop();             //Espera Ordenes
}
            
