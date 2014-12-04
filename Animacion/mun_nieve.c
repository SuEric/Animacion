#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Rotacion
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


////////////////////////////////////////////////////////////////////////////
// Cambia la vista
void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // previene de una division por cero
    if(h == 0)
        h = 1;

    // fija el Viewport a las dimensiones de la ventana
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;

    // resetea el sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // produce la proyeccion en perspectiva
    gluPerspective(35.0f, fAspect, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }


void SetupRC()
    {
    // valores de la luz y coordenadas
    GLfloat  luzBlanca[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat  fuenteLuz[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 posicion_luz[] = { -10.f, 5.0f, 5.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);	
    glFrontFace(GL_CCW);		
    glEnable(GL_CULL_FACE);	

    glEnable(GL_LIGHTING);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,luzBlanca);
    glLightfv(GL_LIGHT0,GL_AMBIENT,fuenteLuz);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,fuenteLuz);
    glLightfv(GL_LIGHT0,GL_POSITION,posicion_luz);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
	
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.25f, 0.25f, 0.50f, 1.0f );
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
                
        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);

	glutPostRedisplay();
	}


void RenderScene(void)
{
    GLUquadricObj *pObj;	
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(0.0f, -1.0f, -5.0f);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);

        pObj = gluNewQuadric();
        gluQuadricNormals(pObj, GLU_SMOOTH);
        
        glPushMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            gluSphere(pObj, .40f, 26, 13);  // abajo
        
            glTranslatef(0.0f, .550f, 0.0f); // seccion media
            gluSphere(pObj, .3f, 26, 13);
        
            glTranslatef(0.0f, 0.45f, 0.0f); // cabeza
            gluSphere(pObj, 0.24f, 26, 13);
        
            // ojos
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(0.1f, 0.1f, 0.21f);
            gluSphere(pObj, 0.02f, 26, 13);
        
            glTranslatef(-0.2f, 0.0f, 0.0f);
            gluSphere(pObj, 0.02f, 26, 13);
        
            // nariz
            glColor3f(1.0f, 0.3f, 0.3f);
            glTranslatef(0.1f, -0.12f, 0.0f);
            gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);
        glPopMatrix();
        
        // sombrero
        glPushMatrix();
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(0.0f, 1.17f, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.17f, 0.17f, 0.4f, 26, 13);
            
            glDisable(GL_CULL_FACE);
            gluDisk(pObj, 0.17f, 0.28f, 26, 13);
            glEnable(GL_CULL_FACE);
            
            glTranslatef(0.0f, 0.0f, 0.40f);
            gluDisk(pObj, 0.0f, 0.17f, 26, 13);
        glPopMatrix();
        
    // restaura el estado de la matriz
    glPopMatrix();

    glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modelando con cuadricos");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    
    return 0;
}
    
    
  