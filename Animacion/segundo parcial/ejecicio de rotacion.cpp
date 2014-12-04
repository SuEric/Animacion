//ROTACION

//Graficacion, verano 2013

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

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

void lineas(void)
{
 	glBegin(GL_LINES);
    glVertex2i(300,250);
    glVertex2i(300,150);
    
    glVertex2i(350,200);
    glVertex2i(250,200);
    glEnd();
    //	glFlush();
}

void t2DD(void)
{
    int y,x1,y1;
    
    
    for(y=0; y<10; y++) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        x1 = rand() % 2;
        y1 = rand() % 2;
        
        cout << "X1: " << x1 << endl;
        cout << "X1: " << x1 << endl;
        
        //glColor3f(x1,y1,1);
        
        glTranslatef(10.0, 0.0, 0.0);
        //lineas(); // Dibuja la X
        
        glRotatef(40.0, 0.0, 0.0, 1.0); // Rota en Z
        sleep(.3);
        
        glFlush();
    }
}
void display(void)
{
    
    //t2DD();
    
    int y,x1,y1;
    for(y=0;y<10;y++)
    {
        x1=rand() % 2;
        y1=rand() % 2;
        glClear(GL_COLOR_BUFFER_BIT);
        
        glTranslated(10,0,0);
        glColor3f(0,x1,y1);
        
        lineas();
        
        glRotatef(-40,0,0,1);
        sleep(.3);
        glFlush();
        
    }
}

//RUTINA PRINCIPAL

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);      //tamaño de la ventana de visualizacion
    glutCreateWindow("ROTACION");
    
    init();        
    
    glutDisplayFunc(display);     //pinta lo que ordene pinta
	glutMainLoop();             //Espera Ordenes
}

