#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define PI			3.14159
#define MAXPUNTOS	150
#define m			20
#define k			0.03
#define g			9.80665

double t[MAXPUNTOS+1];
double u1[MAXPUNTOS+1], u2[MAXPUNTOS+1], u3[MAXPUNTOS+1], u4[MAXPUNTOS+1];

double f1(double t, double u1, double u2, double u3, double u4)
{
    return (u2);
}

double f2(double t, double u1, double u2, double u3, double u4)
{
    return (-(k/m)*sqrt(u2*u2 + u4*u4)*u2);
}

double f3(double t, double u1, double u2, double u3, double u4)
{
    return (u4);
}

double f4(double t, double u1, double u2, double u3, double u4)
{
    return (-g-(k/m)*sqrt(u2*u2 + u4*u4)*u4);
}

void RK4(double tinicial, double tfinal,
		 double u1_inicial, double u2_inicial,
		 double u3_inicial, double u4_inicial,
		 int n)
{
    double k1, k2, k3, k4;
    double l1, l2, l3, l4;
    double d1, d2, d3, d4;
    double q1, q2, q3, q4;
    double h;
    int i;
    
    h=(tfinal-tinicial)/n;
    t[0]=tinicial;
    u1[0]=u1_inicial;
    u2[0]=u2_inicial;
    u3[0]=u3_inicial;
    u4[0]=u4_inicial;
    for (i=0; i<n; i++)
	{
        k1=h*f1(t[i], u1[i], u2[i], u3[i], u4[i]);
        l1=h*f2(t[i], u1[i], u2[i], u3[i], u4[i]);
        d1=h*f3(t[i], u1[i], u2[i], u3[i], u4[i]);
        q1=h*f4(t[i], u1[i], u2[i], u3[i], u4[i]);
        
        k2=h*f1(t[i]+h/2.0, u1[i]+k1/2.0, u2[i]+l1/2.0, u3[i]+d1/2.0, u4[i]+q1/2.0);
        l2=h*f2(t[i]+h/2.0, u1[i]+k1/2.0, u2[i]+l1/2.0, u3[i]+d1/2.0, u4[i]+q1/2.0);
        d2=h*f3(t[i]+h/2.0, u1[i]+k1/2.0, u2[i]+l1/2.0, u3[i]+d1/2.0, u4[i]+q1/2.0);
        q2=h*f4(t[i]+h/2.0, u1[i]+k1/2.0, u2[i]+l1/2.0, u3[i]+d1/2.0, u4[i]+q1/2.0);
        
        k3=h*f1(t[i]+h/2.0, u1[i]+k2/2.0, u2[i]+l2/2.0, u3[i]+d2/2.0, u4[i]+q2/2.0);
        l3=h*f2(t[i]+h/2.0, u1[i]+k2/2.0, u2[i]+l2/2.0, u3[i]+d2/2.0, u4[i]+q2/2.0);
        d3=h*f3(t[i]+h/2.0, u1[i]+k2/2.0, u2[i]+l2/2.0, u3[i]+d2/2.0, u4[i]+q2/2.0);
        q3=h*f4(t[i]+h/2.0, u1[i]+k2/2.0, u2[i]+l2/2.0, u3[i]+d2/2.0, u4[i]+q2/2.0);
        
        k4=h*f1(t[i]+h, u1[i]+k3, u2[i]+l3, u3[i]+d3, u4[i]+q3);
        l4=h*f2(t[i]+h, u1[i]+k3, u2[i]+l3, u3[i]+d3, u4[i]+q3);
        d4=h*f3(t[i]+h, u1[i]+k3, u2[i]+l3, u3[i]+d3, u4[i]+q3);
        q4=h*f4(t[i]+h, u1[i]+k3, u2[i]+l3, u3[i]+d3, u4[i]+q3);
        
        u1[i+1]=u1[i]+(1.0/6.0)*(k1 + 2.0*k2 + 2.0*k3+ k4);
        u2[i+1]=u2[i]+(1.0/6.0)*(l1 + 2.0*l2 + 2.0*l3+ l4);
        u3[i+1]=u3[i]+(1.0/6.0)*(d1 + 2.0*d2 + 2.0*d3+ d4);
        u4[i+1]=u4[i]+(1.0/6.0)*(q1 + 2.0*q2 + 2.0*q3+ q4);
        
        t[i+1]=t[i] + h;
	}
}

void Condiciones_Iniciales(double to, double tf,
                           double xo, double yo,
						   double V, double angulo)
{
    double Vox, Voy;
    
    angulo=PI*angulo/180.0;
    Vox=V*cos(angulo);
    Voy=V*sin(angulo);
    RK4(to, tf, xo, Vox, yo, Voy, MAXPUNTOS);
}

void init(void)
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
}

void display(void)
{
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );
    glLoadIdentity();
    
    glColor3f(0.0, 1.0, 0.5);
    glBegin(GL_LINES);
	glVertex2f(-40.0, 0.0);
	glVertex2f(700.0, 0.0);
	glVertex2f(0.0, -40.0);
	glVertex2f(0.0, 700.0);
    glEnd();
    
    glColor3f(1.0, 1.0, 0.5);
    glBegin(GL_LINE_STRIP);
    for (i=0; i<MAXPUNTOS; i++)
        glVertex2f(u1[i], u3[i]);
    glEnd();
    glFlush ();
}

void reshape (int w, int h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-40.0, 700.0, -40.0, 700.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (350, 350); 
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Trayectoria de un Proyectil");
    
    Condiciones_Iniciales(0.0, 22.0, 0.0, 0.0, 200.0, 65.0);
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}