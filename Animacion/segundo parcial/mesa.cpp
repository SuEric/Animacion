#include <GL/glut.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
void init (void)
{
     glClearColor(1.0,1.0,1.0,1.0);       
     glMatrixMode(GL_PROJECTION);         
     gluOrtho2D(-600, 600, -600,600);          
 }

void mesa(void)
{
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
	glVertex2i(-250,200);
	glVertex2i(250,200);
	glVertex2i(250,-200);
	glVertex2i(-250,-200);
	glEnd();
	
}
void division(void)
{
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2i(0,200);
	glVertex2i(40,250);
	glVertex2i(40,250);
	glVertex2i(40,-200);
	glEnd();
}

void punto1(void)
{
	glColor3f(0,1,0);
	glPointSize(13);
	glBegin(GL_POINTS);
	glVertex2i(200,0);
	glEnd();
    glFlush();
 
}

void mesa1(void)
{
mesa();
 division();
 //punto1();
 	
}
/////
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
	boca();
	brazoder();
	brazoizq();
	piernader();
	piernaizq();
	
}
///////
void Transformaciones()
 {
 	
 	
 	
//mesa();
   
	 
	for(int i=0;i<15;i++)
    {
 
 glClear(GL_COLOR_BUFFER_BIT);
 mesa1();
 
glPushMatrix();
glTranslatef(-550,-150,0);
 pinta();
 glPopMatrix();
 
 
 glPushMatrix();
glTranslatef(550,-150,0);
glScalef(-1,1,0);
 pinta();
glPopMatrix();

 	
int x1=rand() % 300+80;
int y1=rand() % 50;

    if(i%2==0)
    {        

glPushMatrix();

glTranslatef(-x1,-y1,0);
punto1();
Sleep(300);
glPopMatrix();
}
else{
glPushMatrix();

glTranslatef(x1-120,y1,0);
punto1();
Sleep(300);
glPopMatrix();

     }

 
    }
   
   
   
 }
 
 int main()
 {
 	glutInitWindowSize(600,600);
 	glutCreateWindow("transformacione");
 	init();        
    glutDisplayFunc(Transformaciones);     //pinta lo que ordene pinta
	glutMainLoop(); 
 }
