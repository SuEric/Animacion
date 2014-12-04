#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#define altoCuerpo 0.8
#define anchoCuerpo 0.5

#define anchoCabeza 0.25
#define altoCabeza 0.4

#define largoBrazo 0.25
#define anchoBrazo 0.1

#define largoPierna 0.35
#define anchoPierna 0.15

// Colores
GLfloat vRosa[] = {1.0,0.5,0.6,1.0}; // Rosa
GLfloat vVerde[] = {0.0,1.0,0.0,1.0}; // Verde
GLfloat vAzul[] = {0.0,0.6,1.0,1.0}; // Azul
GLfloat vMorado[] = {0.5,0.3,0.7,1.0}; // Morado
GLfloat vAmarillo[] = {1.0,1.0,0.0,1.0}; // Amarillo
GLfloat vRojo[] = {1.0,0.0,0.0,1.0}; //Rojo
GLfloat vCafe[] = {0.36,0.2,0.09,1.0}; // Cafe
GLfloat vCafeClaro[] = {0.87, 0.72, 0.52}; //cafe claro
GLfloat vBlanco[] = {1.0,1.0,1.0,1.0}; // Blanco
GLfloat vNaranja[] = {1.0,0.5,0.0,1.0}; // Naranja
GLfloat vNegro[] = {0.0,0.0,0.0}; // Negro
GLfloat vGris[] = {0.6,0.6,0.6}; // Gris
GLfloat vVerdeOscuro[] = {0.0,0.4,0.0,1.0}; // Verde oscuro
GLfloat vVerdeMike[] = {0.7372, 0.9333, 0.40784}; // Verde mike
GLfloat vAzulMezclilla[] = {0.2901, 0.4977, 0.54509}; // Azul mezclilla
GLfloat vVerdeAlien[] = {0.67843, 1.0, 0.18431}; // Verde Alien
GLfloat vAzulOscuro[] = {0.0, 0.0, 0.54117}; // Azul oscuro

GLUquadric *qobj;
GLuint textura;

// Luces
GLfloat luz_difusa[] = {0.1, 0.1, 0.1, 1.0};
GLfloat luz_ambiente[] = {0.1, 0.1, 0.1, 1.0};
GLfloat luz_especular[] = {0.1, 0.1, 0.1, 1.0};
GLfloat posicion[] = {0.0, 3.0, 45.0}; // Referencia

float alpha = 0, beta = 0; // Rotaciones de camara
int x00, y00; // Coordenada del click

float
tx = 0, ty = 0, tz = 0, // Traslaciones escenario
sx = 0.5, sy = 0.7, sz = 0.7; // Escalados escenario

float movx = 0;
float rot = 90;

int ndx_ll = 0, ndx_rl = 7, max_flex = 14; // rotaciones y max flexibilidad en piernas

// Rotaciones piernas y Tronco
float rotLeg_up[] =  {30.0, 15.0, 0.0, -15.0, -30.0, -40.0, -30.0, -20.0, -15.0, -10.0, -5.0, 0.0, 10.0, 20.0};
float rotLeg_down[] = {5.0, 30.0, 60.0, 60.0, 50.0, 30.0, 20.0, 20.0, 10.0, 10.0, 5.0, 5.0, 5.0, 5.0};
float rotTrunk[] = {-7.0, -3.0, 3.0, 7.0, 11.0, 15.0, 11.0, 7.0, 3.0, -3.0, -7.0, -11.0, -15.0, -11.0};

int LoadBMP(char *filename, int tex_name)
{
#define SAIR        {fclose(fp_archivo); return -1;}
#define CTOI(C)     (*(int*)&C)
    
    GLubyte     *image;
    GLubyte     Header[0x54];
    GLuint      DataPos, imageSize;
    GLsizei     Width,Height;
    
    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE * fp_archivo = fopen(filename,"rb");
    if (!fp_archivo)
        return -1;
    if (fread(Header,1,0x36,fp_archivo)!=0x36)
        SAIR;
    if (Header[0]!='B' || Header[1]!='M')
        SAIR;
    if (CTOI(Header[0x1E])!=0)
        SAIR;
    if (CTOI(Header[0x1C])!=24)
        SAIR;
    
    // Recupera los atributos de la altura y ancho de la imagen
    
    Width   = CTOI(Header[0x12]);
    Height  = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
    
    imageSize=Width*Height*3;
    
    // Llama a la imagen
    image = (GLubyte *) malloc ( imageSize );
    int retorno;
    retorno = fread(image,1,imageSize,fp_archivo);
    
    if (retorno !=imageSize)
    {
        free (image);
        SAIR;
    }
    
    // Invierte los valores de R y B
    int t, i;
    
    for ( i = 0; i < imageSize; i += 3 )
    {
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
    }
    
    // Tratamiento de textura para OpenGL
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MODULATE);
    
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    
    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    fclose (fp_archivo);
    free (image);
    return 1;
}

void disco(float radioI, float radioE, float slices, float loops)		//cuadrico del disco
{
	GLUquadricObj *q = gluNewQuadric();
    
	gluQuadricDrawStyle (q, GLU_FILL);
	gluQuadricNormals   (q, GLU_SMOOTH);
	gluQuadricTexture   (q, GL_TRUE);
	gluDisk(q, radioI, radioE, slices, loops); // Dibuja disco (suelo)
	gluDeleteQuadric(q);
}

void piso()
{
    
	glPushMatrix();
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
    
    glRotatef(45, 0.0, 1.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    
    disco(0.0, 4.5, 4,4);
	
    glPopMatrix();

}

void cuerpo(void)
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vRojo);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0, altoCuerpo/2 + 1.0, 0.0);
    glRotatef(rotTrunk[ndx_ll], 0.0, 1.0, 0.0);
    glScalef(anchoCuerpo, altoCuerpo, anchoCuerpo/2);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

void mechon()
{
	glColor3f(0,0,0);
	glPushMatrix();
	glScalef(1.0, 0.6, 0.7);
    gluCylinder(qobj,0.5,.5,3,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0,0,2);
    glRotatef(45,0,1,0);
    glScalef(1,.5,.7);
    gluSphere(qobj,.5,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0,0,2);
    glRotatef(45,0,1,0);
    glScalef(1,.5,.7);
    gluCylinder(qobj,.5,.2,2,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(1,0,3);
    glRotatef(90,0,1,0);
    glScalef(1,.5,.7);
    gluCylinder(qobj,.2,0,2,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(1,0,3);
    glRotatef(90,0,1,0);
    glScalef(1,.4,.7);
    gluSphere(qobj,.2,15,15);
	glPopMatrix();
}

void cabello()
{
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textura);
    gluSphere(qobj,.10,.100,.20);
	glPopMatrix();
    
	glPushMatrix();
    mechon();
	glPopMatrix();
    
	glPushMatrix();
    glRotatef(180,1,0,0);
    mechon();
    glPopMatrix();

	glPushMatrix();
    glRotatef(120,1,0,0);
    glRotatef(18,0,0,1);
    mechon();
	glPopMatrix();
	
    glPushMatrix();
    glRotatef(45,1,0,0);
    mechon();
	glPopMatrix();
    
}

void cabeza(void)
{
    glPushMatrix();
    
    glTranslatef(0.0, (altoCuerpo + 1.0), 0.0);
    glRotatef(rotTrunk[ndx_ll], 0.0, 1.0, 0.0);
    // Cabeza
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vAmarillo);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    glTranslatef(0.0, (altoCabeza/2), 0.0);
    glScalef(anchoCabeza + 0.5, altoCabeza, anchoCabeza);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Ojo der
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vBlanco);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vBlanco);
    glTranslatef(-0.1, (altoCabeza/3) + (0.1), anchoCabeza/2);
    glScalef(0.06, 0.06, 0.06/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Pupila der
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
    glTranslatef(-0.1, (altoCabeza/3) + (0.1), anchoCabeza/2 + 0.06/2);
    glScalef(0.03, 0.03, 0.03/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Ojo izq
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vBlanco);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vBlanco);
    glTranslatef(0.1, (altoCabeza/3) + (0.1), anchoCabeza/2);
    glScalef(0.06, 0.06, 0.06/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Pupila izq
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vNegro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vNegro);
    glTranslatef(0.1, (altoCabeza/3) + (0.1), anchoCabeza/2 + 0.06/2);
    glScalef(0.03, 0.03, 0.03/2);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Cabello
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, altoCabeza, 0.0);
    glRotatef(135.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(0.12, 0.12, 0.12);
    cabello();
    glPopMatrix();
    
    glPopMatrix();
}

void brazoIzq(int ndx)
{
    glPushMatrix();
 
    glRotatef(rotLeg_up[ndx], 1.0, 0.0, 0.0);
    
    // Hombro 
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafe);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    glTranslatef(anchoCuerpo/2, 0.0, 0.0);
    glScalef(0.12, 0.12, 0.12);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Brazo 
    glPushMatrix();
    
    // Parte superior 
    glPushMatrix();
    glTranslatef( (anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2, - (largoBrazo/2), 0.0);
    glRotatef(30.0, 0.0, 0.0, 1.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Codo 
    glPushMatrix();
    glTranslatef(( (anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2 ) + anchoBrazo/2, -(largoBrazo/2) - largoBrazo/2, 0.0);
    glScalef(0.12/1.8, 0.12/1.8, 0.12/1.8);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Antebrazo
    glPushMatrix();
    glTranslatef(( (anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2 ) + anchoBrazo/2, -(largoBrazo/2) - largoBrazo, 0.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Mano
    glPushMatrix();
    glTranslatef( ((anchoCuerpo/2) + (anchoBrazo/2) + 0.12/2 ) + anchoBrazo/2, -(largoBrazo/2) - largoBrazo - largoBrazo/2, 0.0);
    glRotatef(120, 1, 0, 0);
    glRotatef(70, 0, 0, 1);
    glScalef(0.06, 0.05, 0.06);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void brazoDer(int ndx)
{
    glPushMatrix();
    
    glRotatef(rotLeg_up[ndx], 1.0, 0.0, 0.0);
    
    // Hombro
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafe);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vAzul);
    glTranslatef(-anchoCuerpo/2, 0.0, 0.0);
    glScalef(0.12, 0.12, 0.12);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Brazo 
    glPushMatrix();
    
    // Parte superior
    glPushMatrix();
    glTranslatef(- (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2, -(largoBrazo/2), 0.0);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Codo 
    glPushMatrix();
    glTranslatef(( - (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2 ) - anchoBrazo/2, -(largoBrazo/2) - largoBrazo/2, 0.0);
    glScalef(0.12/1.8, 0.12/1.8, 0.12/1.8);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    // Antebrazo 
    glPushMatrix();
    glTranslatef(( - (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2 ) - anchoBrazo/2, -(largoBrazo/2) - largoBrazo, 0.0);
    glScalef(anchoBrazo, largoBrazo, anchoBrazo);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Mano
    glPushMatrix();
    glTranslatef(( - (anchoCuerpo/2) - (anchoBrazo/2) - 0.12/2 ) - anchoBrazo/2, -(largoBrazo/2) - largoBrazo - largoBrazo/2, 0.0);
    glRotatef(120, 1, 0, 0);
    glRotatef(70, 0, 0, 1);
    glScalef(0.06, 0.05, 0.06);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void piernaIzq()
{
    glPushMatrix();
    
    glPushMatrix();
    
    // Parte superior
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, -largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Rodilla
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, -largoPierna - (0.12/1.6)/2, 0.0);
    glScalef(0.12/1.6, 0.12/1.6, 0.12/1.6);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslatef(0.0, -largoPierna, 0.0);
    glRotatef(rotLeg_down[ndx_ll], 1.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, - largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-anchoCuerpo/4, -largoPierna, 0.06);
    glRotatef(180, 0,1,1);
    glScalef(0.1, 0.3, 0.1);
    glutSolidCone(0.5, 0.6, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void piernaDer(void)
{
    glPushMatrix();
    
    glPushMatrix();
    
    // Parte superior
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, -largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Rodilla
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, -largoPierna - (0.12/1.6)/2, 0.0);
    glScalef(0.12/1.6, 0.12/1.6, 0.12/1.6);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    glPushMatrix();

    glTranslatef(0.0, -largoPierna, 0.0);
    glRotatef(rotLeg_down[ndx_rl], 1.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, - largoPierna/2, 0.0);
    glScalef(anchoPierna, largoPierna, anchoPierna);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(anchoCuerpo/4, -largoPierna, 0.06);
    glRotatef(180, 0,1,1);
    glScalef(0.1, 0.3, 0.1);
    glutSolidCone(0.5, 0.6, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void humanoide(void)
{
    cuerpo();
    
    cabeza();
    
    glPushMatrix();
    glTranslatef(0.0, (anchoCuerpo + 1.0) + (0.08), 0.0);
    brazoIzq(ndx_ll);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, (anchoCuerpo + 1.0) + (0.08), 0.0);
    brazoDer(ndx_rl);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(rotLeg_up[ndx_ll], 1.0, 0.0, 0.0);
    piernaIzq();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(rotLeg_up[ndx_rl], 1.0, 0.0, 0.0);
    piernaDer();
    glPopMatrix();
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 3.0f, 10.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia pantalla
    
    // Traslates, rotates y scales
    // de todo el escenario
	glTranslatef(tx, ty, tz); // tx,ty,tz nunca cambian (es el origen)
	glRotatef(alpha, 1.0f, 0.0f, 0.0f); // Rotate X escenario
	glRotatef(beta, 0.0f, 1.0f, 0.0f); // Rotate Y escenario
    glScalef(sx, sy, sz); // Escalado escenario
    
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    piso();
    glPopMatrix();
    
    glPushMatrix(); //Inicia humanoide
    
    glTranslatef(movx, 0.0, 0.0);
    glRotatef(rot, 0.0, 1.0, 0.0);
    
    humanoide();
    
    glPopMatrix(); //Fin humanoide
    
    glutSwapBuffers(); // Intercambio de buffers, evita efecto de parpadeo
}

void init(void) //SE PINTA EL FONDO Y DECLARA LA ILUMINACION
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
	
	//CUADRICO
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
    
    //PROPIEDADES DE LA ILUMINACION
	glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);
	
    //SE ACTIVAN
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
    
    // Texturas
    glEnable(GL_TEXTURE_2D);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textura);

    glBindTexture(GL_TEXTURE_2D, textura);
    LoadBMP("black_hair.BMP", 4);
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 80.0f;
    
    if(h == 0) h = 1;
    
    glViewport(0, 0, w, h); // Punto de visión
    
    glMatrixMode(GL_PROJECTION); // Modo de matriz
    glLoadIdentity(); // Carga matriz
    
    if (w <= h) glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    
    glMatrixMode(GL_MODELVIEW); // Modo matriz
    glLoadIdentity(); // Pone matriz
}

void onMouse(int button, int state, int x, int y)
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) x00= x; y00 = y; // Captura posicion del click
}

// Movimiento al tener mouse apretado
void onMotion(int x, int y)
{
	alpha = (alpha + (y - y00)); // Rotacion en X
	beta = (beta + (x - x00)); // Rotacion en Y
	x00 = x; y00 = y; // Actualiza posicion raton apretado
    
	glutPostRedisplay(); // Redibujado (no hay diferencia)
}

void anima(int value)
{
    if(movx >= 2.0) {
        movx = 0;
    }
    else
        movx += .05;
    
    // Modificación del grado de rotación de las piernas
    ndx_ll++;
    ndx_ll %= max_flex;
    ndx_rl++;
    ndx_rl %= max_flex;
    glutTimerFunc(150, anima, 1);
    glutPostRedisplay();
}

void teclado (unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case '+':
            sx += 0.2;
            sy += 0.2;
            sz += 0.2;
            break;
        case '-':
            sx-=.2;
            sy-=.2;
            sz-=.2;
            break;
    }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("Mike Wazowski");
	
    init();
	
    glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(teclado);
    glutMouseFunc(onMouse);
	glutMotionFunc(onMotion); // Giro de camara con mouse
    glutTimerFunc(5, anima, 1);
	
    glutMainLoop();
	
    return 0;
}