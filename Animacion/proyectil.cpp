#include <iostream>
#include <cmath>
#include <GL/glut.h>

#define PI 3.141592654
#define g 9.8

float x_init, y_init, z_init;
float rho, theta;
float V;

void Dibujar_Grid(GLfloat GridScale, GLfloat XSteps, GLfloat ZSteps)
{
    GLfloat zExtent, xExtent;
    GLfloat xLocal, zLocal;
    int loopX, loopZ;
    
    glBegin(GL_LINES);
    zExtent = GridScale*ZSteps;
    for(loopX = -XSteps; loopX <= XSteps; loopX++) {
        xLocal = GridScale*loopX;
        glVertex3f(xLocal, 0.0, -zExtent);
        glVertex3f(xLocal, 0.0,  zExtent);
    }
    xExtent = GridScale * XSteps;
    for(loopZ = -ZSteps; loopZ <= ZSteps; loopZ++) {
        zLocal = GridScale * loopZ;
        glVertex3f(-xExtent, 0.0, zLocal);
        glVertex3f(xExtent, 0.0, zLocal);
    }
    glEnd();
}

void Dibujar_VectorTiro(void)
{
    float x, y, z;
    float l;
    
    l = 1.0;
    x = l*sin(rho)*sin(theta);
    y = l*cos(rho);
    z = l*sin(rho)*cos(theta);
    x_init = x;
    y_init = y;
    z_init = z;
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(x, y, z);
    glEnd();
}

void Dibujar_Ejes(void)
{
    glBegin(GL_LINES);
    //eje X
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    //eje Y
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    //eje Z
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void Dibujar_Trayectoria(void)
{
    float x_pos, y_pos, z_pos;
    float Vx, Vy, Vz;
    float t, dt;
    
    x_pos = x_init;
    y_pos = y_init;
    z_pos = z_init;
    Vx = V*sin(rho)*sin(theta);
    Vy = V*cos(rho);
    Vz = V*sin(rho)*cos(theta);
    t = 0.0;
    dt = 0.02;
    
    glBegin(GL_POINTS);
    while (y_pos >= 0) {
        x_pos = Vx*t + x_init;
        y_pos = Vy*t - 0.5*g*t*t + y_init;
        z_pos = Vz*t + z_init;
        glVertex3f(x_pos, y_pos, z_pos);
        t = t+dt;
	};
    glEnd();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(2.0);
    rho = PI/4.0;
    theta = PI/8.0;
    V = 10.0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(2.0, 2.0, -3.0, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    
    glLineWidth(1.0);
    glColor3f(0.5, 0.5, 0.5);
    Dibujar_Grid(1.0, 20.0, 20.0);
    
    glColor3f (1.0, 1.0, 0.0);
    Dibujar_Ejes();
    
    glLineWidth(2.0);
    glColor3f (1.0, 0.0, 0.0);
    Dibujar_VectorTiro();
    
    glColor3f (1.0, 1.0, 1.0);
    Dibujar_Trayectoria();
    
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h)
{
    if (!h) return;
    glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: exit(0);
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Tiro en 3D");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}