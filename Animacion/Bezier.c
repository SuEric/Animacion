#include "stdio.h"
#include "GLUT/glut.h"

int a,b;

int w = 1024;
int h = 600;


int posy(int y)
{
    y = h-y;
	
    return y;
}


void ini(){
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,w,0,h);
	
}


void Bezier(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5);
    float PuntosdeControl[7][3]={
        {411.0,posy(249.0),0.0},
        {505.0,posy(274.0),0.0},
        {597.0,posy(239.0),0.0},
        {620.0,posy(137.0),0.0},
        {518.0,posy(84.0),0.0},
        {414.0,posy(150.0),0.0},
        {412.0,posy(248.0),0.0}};
    
    glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,7,*PuntosdeControl);
    glEnable(GL_MAP1_VERTEX_3);
    glMapGrid1f(100,0.0,1.0);
    glColor3f(1,0,0);
    glEvalMesh1(GL_LINE,0,100);
    glDisable(GL_MAP1_VERTEX_3);
    
    
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(w-5,h-60);
    glutCreateWindow("Curvas de Bezier");
    
    ini();
    glutDisplayFunc(Bezier);
    glutMainLoop();
	
	
}
