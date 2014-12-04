#include <iostream>
#include <cstdio>

#include "Modelo.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

int velocidad= 10;
float angulos_caminado[2][6];
double movimiento_base = 0.0f;

int rotate = 0;

int zoom_flag = GL_FALSE, rotate_flag = GL_FALSE ;

float langle_count = 30,
langle_count2 = 0,
rangle_count = -30,
rangle_count2 = 0,
zoom = 0.0f;

void keyboard (unsigned char key, int x, int y){
    switch(key){
        case 'S' :
            if ((velocidad+1)<1000) velocidad+=1;
            break ;
        case 's' :
            if ((velocidad-1)>3) velocidad-=1;
            else{
                if ((velocidad-0.1f)>2) velocidad-=0.1f;
            }
            break ;
        case 27 :
            exit(0);
            break;
        default :
            glutIdleFunc(NULL) ;
            break ;
    }
}


void special(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_UP :
            zoom += 1 ;
            glutPostRedisplay() ;
            break ;
        case GLUT_KEY_DOWN :
            zoom -= 1 ;
            glutPostRedisplay() ;
            break ;
        case GLUT_KEY_LEFT :
            rotate = (rotate + 5) % 360 ;
            glutPostRedisplay() ;
            break ;
        case GLUT_KEY_RIGHT :
            rotate = (rotate - 5) % 360 ;
            glutPostRedisplay() ;
            break ;
        default :
            break ;
    }
}

void display(void)
{    
    glClear(GL_COLOR_BUFFER_BIT) ;
    
    glPushMatrix() ;
    
    glPushMatrix() ;
    glTranslatef(0.0,0.0, zoom) ;  // tran,rot = zooming
    glRotatef(rotate,0.0,1.0,0.0) ;// rot,tran = moving
    Dibuja_Base_Legs() ;
    glPopMatrix() ;
    
    glPopMatrix() ;
    
    glutSwapBuffers() ;
    
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0) ;
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
    glTranslatef(0.0, 0.0, -5.0) ;
}

void timerFunction(int v)
{
    animar_base();
    glutTimerFunc(velocidad, timerFunction, 1);
}

void init()
{
    const GLubyte* informacion;
    
    glClearColor(1.0, 1.0, 1.0, 0.0) ;
    glShadeModel(GL_FLAT) ;
    
    informacion = glGetString(GL_VENDOR) ;
    cout << "Vendor: " << informacion << endl;
    informacion = glGetString(GL_RENDERER) ;
    cout << "Renderer: " << informacion << endl;
    informacion = glGetString(GL_EXTENSIONS) ;
    cout << "Extensions: " << informacion << endl;
    informacion = glGetString(GL_VERSION) ;
    cout << "Version: " << informacion << endl;
    
    angulos_caminado[0][3] = langle_count ;
    angulos_caminado[1][3] = rangle_count ;
    
    movimiento_base = mostrar_movimiento_base(langle_count,langle_count2,rangle_count,rangle_count) ;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
    
    glutInitWindowSize(400, 400) ;
    glutInitWindowPosition(100, 100) ;
    glutCreateWindow("Segundo Ejemplo : Piernas en movimiento") ;
    
    init() ;
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(velocidad, timerFunction, 1);
    
    glutMainLoop();
    return 0;
}
