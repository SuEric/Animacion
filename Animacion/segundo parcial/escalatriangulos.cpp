//Mi primer progrma de graficacion
//Graficacion, verano 2013

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <unistd.h>

//RUTINA DE INICIALIZACION
void inicializa (void)
{
    glClearColor(0.0,0.0,0.0,0.0);       //Color de fondo RGBA (A no interesa por ahora)
    glMatrixMode(GL_PROJECTION);         //Para el tipo de matriz a usar: Proyeccion
    gluOrtho2D(-400, 400, -400,400);          //Coordenada x de 0 a 400, coordenada y de 0 a 400
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
    glVertex2i(-400,00);
    glVertex2i(-300,00);
    glVertex2i(-350,150);
    glEnd();
    
}

void display(void)
{
    glColor3f(0,1,1);
    pintaejes();
    
    for(int y=0;y<8;y++)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,0,0);
        
        glTranslated(80,0,0);
     
        triangulo();
        
        glScalef(1,-1,0);
        sleep(.3);
        glFlush();
    }
}

//RUTINA PRINCIPAL

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    
    glutInitWindowSize(800,800);      //tamaño de la ventana de visualizacion
    glutCreateWindow("TRIANGULOS- ARRIBA Y ABAJO");
    
    inicializa();
    
    glutDisplayFunc(display);     //pinta lo que ordene pinta
	glutMainLoop();             //Espera Ordenes
}

