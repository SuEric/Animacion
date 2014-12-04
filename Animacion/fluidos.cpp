#include <iostream>
#include <cmath>

#include <GL/glut.h>

#define	MAXPUNTOS	100
#define PI	3.1415926
#define g	9.81
#define coef_viscosidad	17.6e-6


double t[MAXPUNTOS+1], u1[MAXPUNTOS+1], u2[MAXPUNTOS+1];
double masa_fluido, masa_cuerpo, coef_friccion;

void init_parametros(void)
{
    double radio_cuerpo;
    double densidad_fluido;
    double densidad_cuerpo;
    
    radio_cuerpo = 0.15;
    densidad_fluido = 1.293;
    densidad_cuerpo = 5.536;
    masa_fluido=(4.0/3.0)*PI*pow(radio_cuerpo, 3.0)*densidad_fluido;
    masa_cuerpo=(4.0/3.0)*PI*pow(radio_cuerpo, 3.0)*densidad_cuerpo;
    coef_friccion=6.0*PI*radio_cuerpo;
}


double f1(double t, double u1, double u2)
{
    return (u2);
}

double f2(double t, double u1, double u2)
{
    return (g*(1.0-(masa_fluido/masa_cuerpo))-coef_friccion*coef_viscosidad*u2);
}

double trayectoria_vacio(double t)
{
    return ((1.0/2.0)*g*pow(t, 2.0));
}

void RK4(double tinicial, double tfinal,
		 double u1_inicial, double u2_inicial,
		 int n)
{
    double k1, k2, k3, k4;
    double l1, l2, l3, l4;
    double h;
    int i;
    
    h = (tfinal-tinicial)/n;
    t[0] = tinicial;
    u1[0] = u1_inicial;
    u2[0] = u2_inicial;
    for (i=0; i < n; i++) {
        k1=h*f1(t[i], u1[i], u2[i]);
        l1=h*f2(t[i], u1[i], u2[i]);
        k2=h*f1(t[i]+h/2.0, u1[i]+k1/2.0, u2[i]+l1/2.0);
        l2=h*f2(t[i]+h/2.0, u1[i]+k1/2.0, u2[i]+l1/2.0);
        k3=h*f1(t[i]+h/2.0, u1[i]+k2/2.0, u2[i]+l2/2.0);
        l3=h*f2(t[i]+h/2.0, u1[i]+k2/2.0, u2[i]+l2/2.0);
        k4=h*f1(t[i]+h, u1[i]+k3, u2[i]+l3);
        l4=h*f2(t[i]+h, u1[i]+k3, u2[i]+l3);
        u1[i+1]=u1[i]+(1.0/6.0)*(k1 + 2.0*k2 + 2.0*k3+ k4);
        u2[i+1]=u2[i]+(1.0/6.0)*(l1 + 2.0*l2 + 2.0*l3+ l4);
        t[i+1]=t[i] + h;
	}
}

void init(void)
{
    glClearColor(0, 0, 0, 0);
    
    glEnable(GL_LINE_SMOOTH); // Aliasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    init_parametros();
    RK4(0.0, 1.0, 0.0, 0.0, MAXPUNTOS);
}

void display(void)
{
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );
    glLoadIdentity();
    
    //ejes
    glColor3f(0.0, 0.5, 0.8);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 5.0);
    glEnd();
    
    //grafica de la solucion numerica en verde
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (i=0; i<MAXPUNTOS; i++)
        glVertex2f(t[i], u1[i]);
    glEnd();
    
    //grafica de la trayectoria en el vacio en rojo
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (i=0; i<MAXPUNTOS; i++)
        glVertex2f(t[i], trayectoria_vacio(t[i]));
    glEnd();
    
    glFlush ();
}

void reshape (int w, int h)
{
    if (!h)
        return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.2, 1.2, -0.2, 5.2);
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
    glutCreateWindow ("Friccion en un Fluido");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
