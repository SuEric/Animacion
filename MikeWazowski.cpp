#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <GLUI/glui.h>
#else
#include <GL/glut.h>
#endif

#include "mike.h"

#define BUTTON_WALK          300
#define BUTTON_RUN           301
#define BUTTON_KICK          302

float xy_aspect;

/** These are the live variables passed into GLUI ***/
int main_window;
float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float obj_pos[] = { 0.0, 0.0, 0.0 };

/** These are the live variables passed into GLUI ***/
int obj_type = 0;

/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui, *glui2;
GLUI_Panel *obj_panel;
GLUI_RadioGroup *radio;

//retardo
void esperar(float segundos)
{
	clock_t fin, r, err;
	err = (clock_t)(-1);
	fin = clock() ;
	if (fin == err)
		return;
	fin = fin + segundos * CLOCKS_PER_SEC;
	while(1) {
		r = clock();
		if (r == err)
			return;
		if ( r < fin)
			continue;
		else
			break;
	}
}

void motion(char *file){
    if(ReadCSetFromFile(file) == 0)
		ComputeCSetAndMakeLists();
}

/**************************************** control_cb() *******************/
/* GLUI control callback */
void control_cb( int control )
{
	switch(control){
        case BUTTON_WALK:motion("motion_files/walking.cset");
            waitt = 0;
            velh=0;
            break;
        case BUTTON_RUN:motion("motion_files/running.cset");
            waitt = 1;
            velh=.4;
            break;
        case BUTTON_KICK:motion("motion_files/kick.cset");
            waitt =0;
            velh=0;
            break;
	}
}

void myGlutKeyboard(unsigned char Key, int x, int y)
{
    switch(Key) {
        case 27:
            exit(0);
    };
    
    glutPostRedisplay();
}

void myGlutMenu( int value )
{
    myGlutKeyboard( value, 0, 0 );
}

void myGlutIdle( void )
{
    angr++;
    fStep = fmod(fStep + IncStep+waitt, CYCLE_SIZE);
    Step = (int)fStep;
    
    ang += velh;
    if(ang >10) ang =0;
    
	
    /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
    if ( glutGetWindow() != main_window)
        glutSetWindow(main_window);
    
    /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
     application  */
    
    glutPostRedisplay();
}

/***************************************** myGlutMouse() **********/
void myGlutMouse(int button, int button_state, int x, int y)
{
    
}

void myGlutMotion(int x, int y )
{
    glutPostRedisplay();
}

void myGlutReshape( int w, int h)
{
    int tx, ty, tw, th;
    
    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);
    
    xy_aspect = (float)tw / (float)th;
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(GLfloat)tw/(GLfloat)th, .10,200.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,.4,-3.5);
    glRotatef(20,1,0,0);
    glScalef(0.15,0.15,0.15);
    
    glClear(GL_COLOR_BUFFER_BIT);
}

void myGlutSpecialFunc(int Key, int x, int y)
{
}

void drawText(const char *text, int length, int x, int y)
{
    double *matrix = new double[16];
    
    glMatrixMode(GL_PROJECTION);
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int) text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void SetupRC()
{
	GLfloat luz_ambiente[] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat luz_difusa[] = { 0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat posicion_luz[] = {0.0, 3.0, 45.0};
    
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    
    //PROPIEDADES DE LA ILUMINACION
	glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz);
	
    //SE ACTIVAN
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
    
	// genera automaticamente normales para superficies evaluadas
	glEnable(GL_AUTO_NORMAL);

    gluQuadricTexture(p, GL_TRUE);

}

void myGlutDisplay( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
    
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );
    glMultMatrixf(view_rotate);
    glRotatef(angr/2,0,1,0);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vCafeClaro);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vCafeClaro);
    
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-12,-12,6.9);
    mosaico(5,5,5,piso);
    glPopMatrix();
	
    glPushMatrix();
    glRotatef(-135,0,1,0);
    mike();
    glPopMatrix();
    
    std::string text = "Eric Garcia Perez, Motion Captures. Press Esc to exit.";
    
    drawText(text.data(), text.size(), 0, 600-10);
    
	glPopMatrix();
    
	glFlush ();
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( 900, 600 );
    
    main_window = glutCreateWindow( "Motion Capture" );
    GLUI_Master.set_glutSpecialFunc(myGlutSpecialFunc);
    
    glutDisplayFunc(myGlutDisplay);
  	
    SetupRC();
    
    GLUI_Master.set_glutReshapeFunc( myGlutReshape );
    GLUI_Master.set_glutKeyboardFunc( myGlutKeyboard );
    
    GLUI_Master.set_glutMouseFunc( myGlutMouse );
    glutMotionFunc( myGlutMotion );
    
    /****************************************/
    /*          Enable z-buferring          */
    /****************************************/
    
    glEnable(GL_DEPTH_TEST);
    
    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/
    
    glui2 = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);
    
    glui2->set_main_gfx_window(main_window);
    
    GLUI_Rotation *view_rot = glui2->add_rotation("Rotacion", view_rotate);
    view_rot->set_spin( 1.0 );
    //glui2->add_column( false );
    GLUI_Translation *trans_z =
    glui2->add_translation( "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2]);
    trans_z->set_speed( .2 );
    
    glui2->add_button( "Walk", BUTTON_WALK,control_cb);
    glui2->add_button( "Run", BUTTON_RUN,control_cb);
    glui2->add_button( "Kick", BUTTON_KICK,control_cb);
    
    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( myGlutIdle );
    
    glutMainLoop();
    return 0;
}