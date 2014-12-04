#ifndef Animacion_LINK_H
#define Animacion_LINK_H

#include <vector>
#include "color.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define init_length 10
#define init_angle 0.785  // 3.14/4

class Link {
public:
    float mLength;
    float mAngle;
    GLUquadricObj *mObj;
    Color mColor;
    
    Link(Color c) {
        mObj = gluNewQuadric();
        gluQuadricDrawStyle(mObj, GLU_FILL);
        gluQuadricOrientation(mObj, GLU_OUTSIDE);
        gluQuadricNormals(mObj, GLU_SMOOTH);
        mColor = c;
        mAngle = init_angle;
        mLength = init_length;
    }
};

#endif // LINK_H
