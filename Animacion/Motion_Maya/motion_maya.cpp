//
//  Practica5.cpp
//  Animacion
//
//  Created by sueric on 25/09/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//


/* Among other things, the example illustrates how to:
 1)  Alojar memoria (crear clase allocator)
 2)  Importar una escena de FBX, también soporta obj (sino está animado)
 3)  Triangular todos los mesehs
 4)  Get a las cameras
 5)  Encontrar y colocar la camara default
 6)  Settings camera para projection
 7)  Calcular posicion local y global de un nodo
 8)  Calcular orientacion de camara
 9)  Calcular orientacion de luces
 10) Calcular shape deformation of mesh vertices;
 11) Calcular link deformation of mesh vertices.
 12) Mostrar point cache simulation of a mesh.
 13) Get a los poses
 14) Dibujar escena con su pose
 */


/*
 ESTRUCTURA                                                                     - FbxNode *lightNode - FbxLight *light
        - FbxGlobalSettings *settings           - FbxNode *cubeNode ------->    - FbxMesh *cube
 
 SCENE  - FbxNode *rootnode ---------------->   - FbxMesh *cameraNode - FbxCamera *camera
        - FbxAnimEvaluator *evaluator
 */


#include "SceneContext.h" // Principal acceso a librería FBX

#ifdef __APPLE__
#include <GLUI/glui.h>
#else
#include <GL/glui.h>
#endif

#include "GL/glut.h"

void ExitFunction();
void CreateMenus();

// Menus callbacks
void cameraSelection(int menuItem);
void zoomModeSelection(int menuItem);
void animStackSelection(int menuItem);
void menuSelection(int menuItem);
void poseSelection(int menuItem);
void shadingModeSelection(int menuItem);

// Callbacks
void timer(int);
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int, int);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

// info scene
SceneContext *escena;

// Menu item ids
#define PRODUCER_PERSPECTIVE_ITEM   100
#define PRODUCER_TOP_ITEM           101
#define PRODUCER_BOTTOM_ITEM        102
#define PRODUCER_FRONT_ITEM         103
#define PRODUCER_BACK_ITEM          104
#define PRODUCER_RIGHT_ITEM         105
#define PRODUCER_LEFT_ITEM          106
#define CAMERA_SWITCHER_ITEM        107

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int MENU_SHADING_MODE_WIREFRAME = 1;
const int MENU_SHADING_MODE_SHADED = 2;

const int MENU_ZOOM_FOCAL_LENGTH = 1;
const int MENU_ZOOM_POSITION = 2;

const char * MENU_STRING_SHADING_MODE_WIREFRAME = "Wired";
const char * MENU_STRING_SHADING_MODE_SHADED = "Solid/Shaded";

const int PLAY = 1;
const int EXIT = -1;

// GLUI
int main_window;
GLUI *glui, *glui2;

// MemoryAllocator Class
class MemoryAllocator {
public:
	static void* MyMalloc(size_t pSize)
    {
        char *p = (char*)malloc(pSize+1);
        *p = '#';
        return p+1;
    }

	static void* MyCalloc(size_t pCount, size_t pSize)
    {
        char *p = (char*)calloc(pCount, pSize+1);
        *p = '#';
        return p+1;
    }

	static void* MyRealloc(void* pData, size_t pSize)
    {
        if (pData) {    
            
            FBX_ASSERT(*((char*)pData-1)=='#');
            
            if (*((char*)pData-1)=='#') {
                char *p = (char*)realloc((char*)pData-1, pSize+1);
                *p = '#';
                return p+1;
            }
            else {   // Mismatch
                char *p = (char*)realloc((char*)pData, pSize+1);
                *p = '#';
                return p+1;
            }
        }
        else {
            char *p = (char*)realloc(NULL, pSize+1);
            *p = '#';
            return p+1;
        }
    }

	static void MyFree(void* pData)
    {
        if (pData==NULL) return;
        
        FBX_ASSERT(*((char*)pData-1)=='#');
        
        if (*((char*)pData-1)=='#') free((char*)pData-1);
        else free(pData); // Mismatch
    }
};

static bool gAutoQuit = false;

// delete la escena
void ExitFunction()
{
    delete escena;
}

void CreateMenus()
{
    // CAMERA MENU
    int lCameraMenu = glutCreateMenu(cameraSelection);

    glutAddMenuEntry(FBXSDK_CAMERA_PERSPECTIVE, PRODUCER_PERSPECTIVE_ITEM);
    glutAddMenuEntry(FBXSDK_CAMERA_TOP, PRODUCER_TOP_ITEM);
    glutAddMenuEntry(FBXSDK_CAMERA_BOTTOM, PRODUCER_BOTTOM_ITEM);
    glutAddMenuEntry(FBXSDK_CAMERA_FRONT, PRODUCER_FRONT_ITEM);
    glutAddMenuEntry(FBXSDK_CAMERA_BACK, PRODUCER_BACK_ITEM);
    glutAddMenuEntry(FBXSDK_CAMERA_RIGHT, PRODUCER_RIGHT_ITEM);
    glutAddMenuEntry(FBXSDK_CAMERA_LEFT, PRODUCER_LEFT_ITEM);

    /*
    const FbxArray<FbxNode *> & lCameraArray = escena->GetCameraArray();
    
    // Add the camera switcher if there is at least one camera in the scene
    if (lCameraArray.GetCount() > 0) glutAddMenuEntry(FBXSDK_CAMERA_SWITCHER, CAMERA_SWITCHER_ITEM);

    // Add the cameras contained in the scene
    for (int lCameraIndex = 0; lCameraIndex < lCameraArray.GetCount(); ++lCameraIndex) glutAddMenuEntry(lCameraArray[lCameraIndex]->GetName(), lCameraIndex);
     */

    // STACK MENU
    int lAnimStackMenu = glutCreateMenu(animStackSelection);
    int lCurrentAnimStackIndex = 0;

    const FbxArray<FbxString *> & lAnimStackNameArray = escena->GetAnimStackNameArray();

    // Add the animation stack names
    for (int lPoseIndex = 0; lPoseIndex < lAnimStackNameArray.GetCount(); ++lPoseIndex) {
        
        glutAddMenuEntry(lAnimStackNameArray[lPoseIndex]->Buffer(), lPoseIndex);

        // Track the current animation stack index.
        if (lAnimStackNameArray[lPoseIndex]->Compare(escena->GetScene()->ActiveAnimStackName.Get()) == 0)
            lCurrentAnimStackIndex = lPoseIndex;
    }

    // Call the animation stack selection callback immediately to 
    // initialize the start, stop and current time.
    animStackSelection(lCurrentAnimStackIndex);

    // SHADING MENU
    const int lShadingModeMenu = glutCreateMenu(shadingModeSelection);
    glutAddMenuEntry(MENU_STRING_SHADING_MODE_WIREFRAME, MENU_SHADING_MODE_WIREFRAME);
    glutAddMenuEntry(MENU_STRING_SHADING_MODE_SHADED, MENU_SHADING_MODE_SHADED);

    int lBindPoseCount = 0;
    int lRestPoseCount = 0;
    // Create a submenu for bind poses
    int lBindPoseMenu = glutCreateMenu(poseSelection);

    // Add the list of bind poses
    const FbxArray<FbxPose *> & lPoseArray = escena->GetPoseArray();
    
    for (int lPoseIndex = 0; lPoseIndex < lPoseArray.GetCount(); ++lPoseIndex)
        if (lPoseArray[lPoseIndex]->IsBindPose()) {
            glutAddMenuEntry(lPoseArray[lPoseIndex]->GetName(), lPoseIndex);
            lBindPoseCount++;
        }

    // Submenu rest poses
    int lRestPoseMenu = glutCreateMenu(poseSelection);

    // Lista de bind poses
    for (int lPoseIndex = 0; lPoseIndex < lPoseArray.GetCount(); ++lPoseIndex)
        if (lPoseArray[lPoseIndex]->IsRestPose()) {
            glutAddMenuEntry(lPoseArray[lPoseIndex]->GetName(), lPoseIndex);
            lRestPoseCount++;
        }

    // Submenu poses specific
    int lPoseMenu = 0;
    
    if (lBindPoseCount > 0 || lRestPoseCount > 0) {
        
        lPoseMenu = glutCreateMenu(poseSelection);
        
        if (lBindPoseCount>0) glutAddSubMenu("Bind Pose", lBindPoseMenu);
        if (lRestPoseCount>0) glutAddSubMenu("Rest Pose", lRestPoseMenu);
    }

    // ZOOM MENU
    
    /*int lZoomMenu = glutCreateMenu(zoomModeSelection);
    glutAddMenuEntry( "Lens", MENU_ZOOM_FOCAL_LENGTH);
    glutAddMenuEntry( "Position", MENU_ZOOM_POSITION);*/

    // Main menu
    glutCreateMenu(menuSelection);
    glutAddSubMenu("Camara", lCameraMenu);
    glutAddSubMenu("Animacion", lAnimStackMenu);
    glutAddSubMenu("Modo Modelo", lShadingModeMenu);
    
    if (lBindPoseCount>0 || lRestPoseCount>0) glutAddSubMenu("Go to Pose", lPoseMenu);
    
    //glutAddSubMenu( "Zoom Mode (+, -)", lZoomMenu);
    glutAddMenuEntry("Play (Space)", PLAY);
    glutAddMenuEntry("Exit (ESC)", EXIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Select the current camera.
void cameraSelection(int menuItem)
{
    const FbxArray<FbxNode*> & lCameraArray = escena->GetCameraArray();
    
    switch (menuItem) {
        case PRODUCER_PERSPECTIVE_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_PERSPECTIVE);
            break;
        case PRODUCER_TOP_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_TOP);
            break;
        case PRODUCER_BOTTOM_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_BOTTOM);
            break;
        case PRODUCER_FRONT_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_FRONT);
            break;
        case PRODUCER_BACK_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_BACK);
            break;
        case PRODUCER_RIGHT_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_RIGHT);
            break;
        case PRODUCER_LEFT_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_LEFT);
            break;
        case CAMERA_SWITCHER_ITEM:
            escena->SetCurrentCamera(FBXSDK_CAMERA_SWITCHER);
            break;
        default:
            if (menuItem >= 0 && menuItem < lCameraArray.GetCount())
                escena->SetCurrentCamera(lCameraArray[menuItem]->GetName());
    }
    
}

void zoomModeSelection(int menuItem)
{
    switch (menuItem) {
        case MENU_ZOOM_FOCAL_LENGTH:
            escena->SetZoomMode(SceneContext::ZOOM_FOCAL_LENGTH);
            break;
        case MENU_ZOOM_POSITION:
            escena->SetZoomMode(SceneContext::ZOOM_POSITION);
    }
}

// Select the current animation stack and set the start, stop and current time.
void animStackSelection(int menuItem)
{
    escena->SetCurrentAnimStack(menuItem);
}

void poseSelection(int menuItem)
{
    escena->SetCurrentPoseIndex(menuItem);
}

void shadingModeSelection(int menuItem)
{
    switch (menuItem) {
        case MENU_SHADING_MODE_WIREFRAME:
            escena->SetShadingMode(SHADING_MODE_WIREFRAME);
            break;
        case MENU_SHADING_MODE_SHADED:
            escena->SetShadingMode(SHADING_MODE_SHADED);
    }
}

void menuSelection(int menuItem)
{
    switch (menuItem) {
        case PLAY:
            escena->SetCurrentPoseIndex(-1);
            break;
        case EXIT:
            exit(0);
    }
}

void timer(int)
{
    // Ask to display the current frame only if necessary.
    if (escena->GetStatus() == SceneContext::MUST_BE_REFRESHED) glutPostRedisplay();

    escena->OnTimerClick();

    glutTimerFunc( (unsigned int) escena->GetFrameTime().GetMilliSeconds(), timer, 0);
}

void mouse(int button, int state, int x, int y)
{
    escena->OnMouse(button, state, x, y);
}

void reshape(int width, int height)
{
    escena->OnReshape(width, height);
}

// Exit the application from the keyboard.
void keyboard(unsigned char key, int x, int y)
{
    escena->OnKeyboard(key);
}

void motion(int x, int y)
{
    escena->OnMouseMotion(x, y);
}

void display(void)
{
    escena->OnDisplay();
    
    glutSwapBuffers();
    
    // Import the scene if it's ready to load.
    if (escena->GetStatus() == SceneContext::MUST_BE_LOADED) {
        // This function is only called in the first display callback
        // to make sure that the application window is opened and a
        // status message is displayed before.
        escena->LoadFile();
        
        CreateMenus();
        
        // Call the timer to display the first frame.
        glutTimerFunc((unsigned int)escena->GetFrameTime().GetMilliSeconds(), timer, 0);
    }
    
	if(gAutoQuit) exit(0);
}


void myGlutSpecialFunc(int Key, int x, int y)
{
}

int main(int argc, char** argv)
{
    // glut exit_hack destroy objects created by the FBX SDK.
    atexit(ExitFunction);
    
	// Custom memory allocator
    FbxSetMallocHandler(MemoryAllocator::MyMalloc);
    FbxSetReallocHandler(MemoryAllocator::MyRealloc);
    FbxSetFreeHandler(MemoryAllocator::MyFree);
    FbxSetCallocHandler(MemoryAllocator::MyCalloc);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    
    main_window = glutCreateWindow("Motion Capture");
    GLUI_Master.set_glutSpecialFunc(myGlutSpecialFunc);

    // initialize OpenGL (GLEW).
    const bool lSupportVBO = InitializeOpenGL();
    
	// set glut callbacks
    glutDisplayFunc(display);
    
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glEnable(GL_DEPTH_TEST);
    
	FbxString lFilePath("");
	
    for( int i = 1, c = argc; i < c; ++i )
        if( FbxString(argv[i]) == "-test" ) gAutoQuit = true;
		else if(lFilePath.IsEmpty()) lFilePath = argv[i];
    
	escena = new SceneContext(!lFilePath.IsEmpty() ? lFilePath.Buffer() : NULL, WINDOW_WIDTH, WINDOW_HEIGHT, lSupportVBO);
    
	glutMainLoop();
    
    return 0;
}