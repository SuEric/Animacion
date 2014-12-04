#include <iostream>
#include <iomanip>
#include <GLUT/glut.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <stdio.h>

void myIdle();

unsigned int radioComp = -2;

#define REYNOLDS 0
#define PERSECUTION 1
#define FLOCK 2

int velocidad = 10;

unsigned int seleccion = 2;

double tamano = 0.48,	trianguloy = tamano * 8,	posicion = 0.05,	angulo = 1.0,
gmedida  = tamano * 200,	grmedida  = tamano * 200, minX = -gmedida/2.0, maxX = gmedida/2.0,
minZ = -gmedida/2.0,		maxZ =  gmedida/2.0,		x_umbral = gmedida / 10.0,
z_umbral = grmedida / 10.0;

/*
double tamano = 0.18,trianguloy = tamano * 2,posicion = 0.05,angulo = 1.0,
gmedida  = tamano * 200,grmedida  = tamano * 200,minX = -gmedida/2.0,maxX =  gmedida/2.0,
minZ = -gmedida/5.0,maxZ =  gmedida/2.0,x_umbral = gmedida / 10.0,z_umbral = grmedida / 10.0;
*/
int fmedida = 50; //cuantos

double ejex = 0,ejey = ( grmedida * 1.25),ejez = 0,atx = 0,aty = 0,atz = 0,upx = 0,upy = 0,upz = 1,
rotx = 0,roty = 0,fov = 45.0,aspecto = 1.0,cerca = 0.1,lejos = (gmedida * 4);

const double PI = 3.141592654,d2r = PI / 180.0,r2d = 180.0 / PI;
using namespace std;

int aleatorio(int min, int max) {
    return min + (rand() % (max-min));
}

class objeto {
public:
    objeto(int i, float xTrans = 1, float yTrans = 1, float zTrans = 1) {
        inicioo = i;
        
        switch (seleccion) {
            case REYNOLDS:
                curX = aleatorio((-gmedida/2.0), (gmedida/2.0));
                curZ = aleatorio((-grmedida/2.0), (grmedida/2.0));
                
                curAng = aleatorio(-180, 180);
                break;
                
            case PERSECUTION:
                curAng = 8.0;
                
                if (i == 0) {
                    curX = gmedida/(4.0-(1.5)*xTrans);
                    curZ = gmedida/(4.0- (0.1)*zTrans);
                    transY = (1.5)*yTrans; // Fijo
                }
                
                if(i%2 == 0) { // pares
                    curX = gmedida/(4.0-(1.5)*xTrans);
                    curZ = gmedida/(4.0- (0.1)*zTrans);
                    transY = (1.5)*yTrans; // Fijo
                }
                else { //impares
                    curX = gmedida/(1.0-xTrans);
                    curZ = gmedida/(1.0-zTrans);
                    transY = yTrans; // Fijo
                }
                break;
            case FLOCK:
                curX = aleatorio((-gmedida/2.0), (gmedida/2.0));
                curZ = aleatorio((-grmedida/2.0), (grmedida/2.0));
                
                curAng = aleatorio(-180, 180);
                break;
        }
        
        prevX = curX;
        prevZ = curZ;
        prevAng = curAng;
        
        colorR = 0.77;
        colorG = 0.44;
        colorB = 0.0;
    }
    
    void mover(void)
    {
        switch (seleccion) {
            case REYNOLDS:
                {double dx = sin(curAng * d2r)/2, dz = cos(curAng * d2r)/2;
                
                curX += (dx * posicion);
                curZ += (dz * posicion);
                
                double distizquierda = fabs(curX - maxX),
                distderecha = fabs(curX - minX),
                distarriba = fabs(curZ - maxZ),
                distabajo = fabs(curZ - minZ);
                
                bool cercaizquierda = (distizquierda <= x_umbral),
                cercaderecha = (distderecha <= x_umbral),
                cercaarriba = (distarriba <= z_umbral),
                cercaabajo = (distabajo <= z_umbral);
                
                distizquierda = fabs((x_umbral - distizquierda) / x_umbral);
                distderecha = fabs((x_umbral - distderecha) / x_umbral);
                distarriba = fabs((z_umbral - distarriba) / z_umbral);
                distabajo = fabs((z_umbral - distabajo) / z_umbral);
                
                
                double targetAng = 0,dist = 0;
                if (cercaarriba && cercaderecha) {
                    if ((90 <= curAng) && (curAng <= 180))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distarriba,2) + pow(distderecha, 2));
                }
                else if (cercaarriba && cercaizquierda) {
                    if ((-180 <= curAng) && (curAng <= -90))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distarriba,2) + pow(distizquierda, 2));
                }
                else if (cercaabajo && cercaderecha) {
                    if ((0 <= curAng) && (curAng <= 90))
                        return;
                    
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distabajo,2) + pow(distderecha, 2));
                }
                else if (cercaabajo && cercaizquierda) {
                    if ((-90 <= curAng) && (curAng <= 0))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distabajo,2) + pow(distizquierda, 2));
                }
                else if (cercaarriba) {
                    dist = distarriba;
                    if ((0 <= curAng) && (curAng < 180))
                        targetAng = 180.0 - curAng;
                    else if ((-180 < curAng) && (curAng < 0))
                        targetAng = curAng - 180.0;
                    else
                        return;
                }
                else if (cercaabajo) {
                    dist = distabajo;
                    if ((0 < curAng) && (curAng <= 180))
                        targetAng = 180.0 - curAng;
                    else if ((-180 < curAng) && (curAng < 0))
                        targetAng = 180.0 - curAng;
                    else
                        return;
                }
                else if (cercaizquierda) {
                    dist = distizquierda;
                    if ((-90 < curAng) && (curAng <= 90))
                        targetAng = -curAng;
                    else if ((90 < curAng) && (curAng < 270))
                        targetAng = 360 - curAng;
                    else
                        return;
                }
                else if (cercaderecha) {
                    dist = distderecha;
                    if ((-270 < curAng) && (curAng <= -90))
                        targetAng = -curAng - 360.0;
                    else if ((-90 < curAng) && (curAng < 90))
                        targetAng = -curAng;
                    else
                        return;
                }
                
                double targetAngChg = targetAng - curAng;
                
                curAng += (dist / 20.0) * targetAngChg;
                while (curAng < -180)
                    curAng += 360;
                while (curAng > 180)
                    curAng -= 360;
                    break;}
                
            case PERSECUTION:
                {double dx = sin(curAng * d2r),dz = cos(curAng * d2r);
                
                curX += (dx * posicion) * velocidad;
                curZ += (dz * posicion) * velocidad;
                
                double distizquierda = fabs(curX - maxX) - radioComp, distderecha = fabs(curX - minX),
                distarriba = fabs(curZ - maxZ) + radioComp, distabajo = fabs(curZ - minZ) - radioComp;
                
                bool cercaizquierda = (distizquierda <= x_umbral), cercaderecha = (distderecha <= x_umbral),
                cercaarriba = (distarriba <= z_umbral), cercaabajo = (distabajo <= z_umbral);
                
                distizquierda = fabs((x_umbral - distizquierda) / x_umbral);
                distderecha = fabs((x_umbral - distderecha) / x_umbral);
                distarriba = fabs((z_umbral - distarriba) / z_umbral);
                distabajo = fabs((z_umbral - distabajo) / z_umbral);
                
                double targetAng = 90, dist = 4;
                    
                if (cercaarriba && cercaderecha) {
                    if ((90 <= curAng) && (curAng <= 180))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distarriba,2) + pow(distderecha, 2));
                }
                else if (cercaarriba && cercaizquierda) {
                    if ((-180 <= curAng) && (curAng <= -90))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distarriba,2) + pow(distizquierda, 2));
                }
                else if (cercaabajo && cercaderecha) {
                    if ((0 <= curAng) && (curAng <= 90))
                        return;
                    
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distabajo,2) + pow(distderecha, 2));
                }
                else if (cercaabajo && cercaizquierda) {
                    if ((-90 <= curAng) && (curAng <= 0))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distabajo,2) + pow(distizquierda, 2));
                }
                else if (cercaarriba) {
                    dist = distarriba;
                    if ((0 <= curAng) && (curAng < 180))
                        targetAng = 180.0 - curAng;
                    else if ((-180 < curAng) && (curAng < 0))
                        targetAng = curAng - 180.0;
                    else
                        return;
                }
                else if (cercaabajo) {
                    dist = distabajo;
                    if ((0 < curAng) && (curAng <= 180))
                        targetAng = 180.0 - curAng;
                    else if ((-180 < curAng) && (curAng < 0))
                        targetAng = 180.0 - curAng;
                    else
                        return;
                }
                else if (cercaizquierda) {
                    dist = distizquierda;
                    if ((-90 < curAng) && (curAng <= 90))
                        targetAng = -curAng;
                    else if ((90 < curAng) && (curAng < 270))
                        targetAng = 360 - curAng;
                    else
                        return;
                }
                else if (cercaderecha) {
                    dist = distderecha;
                    if ((-270 < curAng) && (curAng <= -90))
                        targetAng = -curAng - 360.0;
                    else if ((-90 < curAng) && (curAng < 90))
                        targetAng = -curAng;
                    else
                        return;
                }
                    double targetAngChg = targetAng - curAng;
                    curAng += (dist / 20.0) * targetAngChg;
                    while (curAng < -180)
                        curAng += 360;
                    while (curAng > 180)
                        curAng -= 360;
                    }
                break;
            case FLOCK:
                {double dx = sin(curAng * d2r),dz = cos(curAng * d2r);
                
                curX += (dx * posicion);
                curZ += (dz * posicion);
                
                double distizquierda = fabs(curX - maxX),distderecha = fabs(curX - minX),
                distarriba = fabs(curZ - maxZ),distabajo = fabs(curZ - minZ);
                
                bool paredizquierda = (distizquierda <= x_umbral),paredderecha = (distderecha <= x_umbral),
                paredarriba = (distarriba <= z_umbral),paredabajo = (distabajo <= z_umbral);
                
                distizquierda = fabs((x_umbral - distizquierda) / x_umbral);
                distderecha = fabs((x_umbral - distderecha) / x_umbral);
                distarriba = fabs((z_umbral - distarriba) / z_umbral);
                distabajo = fabs((z_umbral - distabajo) / z_umbral);
                
                
                double targetAng = 0,dist = 0;
                if (paredarriba && paredderecha) {
                    if ((200 <= curAng) && (curAng <= 300))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distarriba,2) + pow(distderecha, 2));
                }
                else if (paredarriba && paredizquierda) {
                    if ((-360 <= curAng) && (curAng <= -180))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distarriba,2) + pow(distizquierda, 2));
                }
                else if (paredabajo && paredderecha)
                {
                    if ((20 <= curAng) && (curAng <= 40))
                        return;
                    
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distabajo,2) + pow(distderecha, 2));
                }
                else if (paredabajo && paredizquierda)
                {
                    if ((-40 <= curAng) && (curAng <= 50))
                        return;
                    targetAng = 180.0 + curAng;
                    dist = sqrt(pow(distabajo,2) + pow(distizquierda, 2));
                }
                else if (paredarriba)
                {
                    dist = distarriba;
                    if ((0 <= curAng) && (curAng < 180))
                        targetAng = 180.0 - curAng;
                    else if ((-180 < curAng) && (curAng < 0))
                        targetAng = curAng - 180.0;
                    else
                        return;
                }
                else if (paredabajo)
                {
                    dist = distabajo;
                    if ((0 < curAng) && (curAng <= 180))
                        targetAng = 180.0 - curAng;
                    else if ((-180 < curAng) && (curAng < 0))
                        targetAng = 180.0 - curAng;
                    else
                        return;
                }
                else if (paredizquierda)
                {
                    dist = distizquierda;
                    if ((-90 < curAng) && (curAng <= 90))
                        targetAng = -curAng;
                    else if ((90 < curAng) && (curAng < 270))
                        targetAng = 360 - curAng;
                    else
                        return;
                }
                else if (paredderecha)
                {
                    dist = distderecha;
                    if ((-270 < curAng) && (curAng <= -90))
                        targetAng = -curAng - 360.0;
                    else if ((-90 < curAng) && (curAng < 90))
                        targetAng = -curAng;
                    else
                        return;
                }
                
                double targetAngChg = targetAng - curAng;
                
                curAng += (dist / 20.0) * targetAngChg;
                while (curAng < -180)
                    curAng += 360;
                while (curAng > 180)
                    curAng -= 360;}
                break;
        }
    }
    
    struct Dist {
        int i;
        double d;
    };
    void encuentracerca(vector<objeto> objetos) {
        vector<Dist> dists;
        cerca.clear();
        int min;
        for (int i = 0; i < objetos.size(); i++) {
            
            if (objetos[i].inicioo == inicioo)
                continue;
            
            Dist dist;
            dist.i = i;
            dist.d = sqrt(pow((objetos[i].prevX - prevX), 2.0) +
                          pow((objetos[i].prevZ - prevZ), 4.0));
            dists.push_back(dist);
        }
        for (int i = 0; ((i<8) && (i<dists.size()-1)); i++) {
            min = i;
            for (int j = i+1; j < dists.size(); j++) {
                if (dists[j].d < dists[min].d)
                    min = j;
            }
            cerca.push_back(dists[min].i);
            swap(dists[i], dists[min]);
        }
    }
    
    // Comunes
    double curX; double curZ; double curAng;
	double transY;
    double prevX; double prevZ; double prevAng;
    double colorR; double colorG; double colorB;
    int inicioo;
    vector<int> cerca;
};

vector<objeto> flock;

void limpiarObjetos(void)
{
    flock.clear();
}

void creaObjetos(void)
{
    srand((unsigned int)time(NULL));
    cout << setprecision(4) << fixed << showpoint;
    
    switch (seleccion) {
        case REYNOLDS:
            for (int i = 0; i < fmedida; i++) flock.push_back(objeto(i));
            break;
        case PERSECUTION:
            {float xTrans=0.0, yTrans=0.0, zTrans=0.0;
                for (int i = 0; i < fmedida; i++) {
                    if(i == 0) { // Lider
                        xTrans-=12.0;
                        yTrans-=3.0;
                        zTrans+=1.0;
                        
                        flock.push_back(objeto(i, xTrans-2, yTrans, zTrans));
                        
                        flock[i].colorR = 1;
                        flock[i].colorG = 1;
                        flock[i].colorB = 0;
                    }
                    else if(i!=0 &&  i%2==0) { // Par
                        xTrans-=3.0;
                        yTrans-=4.0;
                        zTrans+=1.0;
                        
                        flock.push_back(objeto(i, xTrans, yTrans, zTrans));
                        
                        flock[i].colorR = 1;
                        flock[i].colorG = 0;
                        flock[i].colorB = 0;
                    }
                    else {
                        xTrans-=3.0;
                        yTrans+=2.0;
                        zTrans-=10.0;
                        
                        flock.push_back(objeto(i, xTrans, yTrans, zTrans));
                        
                        flock[i].colorR = 1;
                        flock[i].colorG = 0;
                        flock[i].colorB = 0;
                    }
                }
            }
            break;
        case FLOCK:
            for (int i = 0; i < fmedida; i++) flock.push_back(objeto(i));
            break;
    }
}

void menuSelection(int item)
{
    switch (item) {
        case -1:
            exit(0);
            break;
    }
}

void comportSelection(int item)
{
    glutIdleFunc(NULL);
    limpiarObjetos(); // Limpia los objetos
    switch (item) {
        case REYNOLDS:
            tamano = 0.48, trianguloy = tamano * 8, posicion = 0.05, angulo = 1.0,
            gmedida  = tamano * 200,	grmedida  = tamano * 200, minX = -gmedida/2.0, maxX = gmedida/2.0,
            minZ = -gmedida/2.0,	maxZ =  gmedida/2.0, x_umbral = gmedida / 10.0, z_umbral = grmedida / 10.0;
            
            ejex = 0, ejey = grmedida*1.25, ejez = 0, atx = 0, aty = 0, atz = 0, upx = 0, upy = 0, upz = 1;
            
            seleccion = REYNOLDS;
            break;
        case PERSECUTION:
            tamano = 0.18, trianguloy = tamano * 2, posicion = 0.05, angulo = 1.0,
            gmedida  = tamano * 200, grmedida  = tamano * 200, minX = -gmedida/2.0, maxX =  gmedida/2.0,
            
            minZ = -gmedida/5.0,maxZ =  gmedida/2.0,x_umbral = gmedida / 10.0,z_umbral = grmedida/10.0;
            
            ejex = 0, ejey = grmedida*1.25, ejez = 0,atx = 0, aty = 0, atz = 0, upx = 0, upy = 0, upz = 1;
            
            seleccion = PERSECUTION;
            break;
        case FLOCK:
            tamano = 0.7,trianguloy = tamano * 8,posicion = 0.05,angulo = 1.0,
            gmedida  = tamano * 180,grmedida  = tamano * 180,minX = -gmedida/2.0,maxX =  gmedida/2.0,
            minZ = -gmedida/2.0,maxZ =  gmedida/2.0,x_umbral = gmedida / 10.0,z_umbral = grmedida / 10.0;
            
            ejex = 0, ejey = grmedida*1.25, ejez = 0, atx = 0, aty = 0, atz = 0, upx = 0, upy = 0, upz = 1;
            seleccion = FLOCK;
    }
    creaObjetos(); // instancia los objetos
    glutIdleFunc(myIdle);
}

void createMenus(void)
{
    int comportamientos = glutCreateMenu(comportSelection);
    glutAddMenuEntry("Reynolds", REYNOLDS);
    glutAddMenuEntry("Persecución", PERSECUTION);
    glutAddMenuEntry("Manada", FLOCK);
    
    glutCreateMenu(menuSelection);
    glutAddSubMenu("Comportamiento", comportamientos);
    glutAddMenuEntry("EXIT", -1);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

void initializeGL(void)
{
    glClearColor(0.6, 0.6, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth(1);
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(fov, aspecto, cerca, lejos);
    
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, 1000, 720);
	glFlush();
    
    glLoadIdentity();
    
	glPushMatrix();
}

void dibuja(objeto solido)
{
    glPushMatrix();
    
    glColor3f(solido.colorR, solido.colorG, solido.colorB);
    
    if (seleccion == FLOCK) glTranslatef(solido.curX+1, trianguloy, solido.curZ+1);
    else glTranslatef(solido.curX, trianguloy, solido.curZ);
    
    glRotatef(solido.curAng, 0, 1, 0);
    glScalef(2.3, 2.3, 2.3);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, (tamano * 3));
    glVertex3f(-tamano/2.0, -tamano/2.0, 0);
    glVertex3f(-tamano/2.0,  tamano/2.0, 0);
    glVertex3f( tamano/2.0,  tamano/2.0, 0);
    glVertex3f( tamano/2.0, -tamano/2.0, 0);
    glVertex3f(-tamano/2.0, -tamano/2.0, 0);
    glEnd();
    
    glPopMatrix();
}

void myDisplay()
{
	// posicion de camara inicial
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspecto, cerca, lejos);
    
    glMatrixMode(GL_MODELVIEW);
    if (seleccion == FLOCK) glViewport(0, 0, 800, 800);
    else glViewport(0, 0, 1000, 720);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glLoadIdentity();
	gluLookAt(ejex, ejey, ejez, atx,  aty,  atz, upx,  upy,  upz);
    
    // Triangulos
    glPushMatrix();
	for (int i = 0; i < flock.size(); i++) {
        if (i == 0) radioComp = 0;
        else radioComp = 1;
        flock[i].mover();
		dibuja(flock[i]);
	}
	glPopMatrix();
    
    glFlush();
	glutSwapBuffers();
    
    if (seleccion == FLOCK)
        for (int i = 0; i < flock.size(); i++) {
            flock[i].prevX = flock[i].curX+5;
            flock[i].prevZ = flock[i].curZ+5;
            flock[i].prevAng = flock[i].curAng+5;
        }
    else
        for (int i = 0; i < flock.size(); i++) {
            flock[i].prevX = flock[i].curX;
            flock[i].prevZ = flock[i].curZ;
            flock[i].prevAng = flock[i].curAng;
        }
}

void myIdle()
{
    glutPostRedisplay(); // Animación constante
}

void myKeyboard(unsigned char key, int x, int y)
{
    if (('1' <= key) && (key <= '9')) {
        
        for (int i = 0; i < flock.size(); i++) {
            flock[i].colorR = 0;
            flock[i].colorG = 0;
            flock[i].colorB = 1;
        }
        
        objeto* center = &flock[int(key-'1')];
        center->encuentracerca(flock);
        
        center->colorR = 1;
        center->colorG = 0;
        center->colorB = 0;
        
        for (int i = 0; i < (center->cerca).size(); i++) {
            objeto* cur = &flock[(center->cerca[i])];
            cur->colorR = 0;
            cur->colorG = 1;
            cur->colorB = 0;
        }
    }
    else if (key == '0') {
        for (int i = 0; i < flock.size(); i++) {
            flock[i].colorR = 0;
            flock[i].colorG = 0;
            flock[i].colorB = 1;
        }
    } else if (key == 27) exit(0);
    
    glFlush();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    creaObjetos();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(1300, 900);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Comportamientos");
    
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    
    initializeGL();
    
    createMenus();
    glutMainLoop();
    
    return 0;
}