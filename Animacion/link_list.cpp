#include <iostream>
#include <cmath>

#include "link.h"
#include "link_list.h"

#define degrees(x) x*180/3.1415926

MatrixXf link_list::pseudoInverso()
{
    MatrixXf j = jacobiano();
    MatrixXf jjtInv = (j * j.transpose());
    jjtInv = jjtInv.inverse();
    
    return (j.transpose() * jjtInv);
}

void link_list::calculatePosition()
{
    float angle = 0;
    mPosition = VectorXf::Zero(2,1);
    
    for (int i = 0; i < mList.size(); i++) {
        angle += mList[i]->mAngle;
        mPosition(0) += mList[i]->mLength * cos(angle);
        mPosition(1) += -mList[i]->mLength * sin(angle);
    }
}

MatrixXf link_list::jacobiano()
{
    MatrixXf j = MatrixXf::Zero(2,mList.size());
    
    for (int col = 0; col < mList.size(); col++) {
        float angle = 0;
        
        for (int i = 0; i < mList.size(); i++) {
            angle += mList[i]->mAngle;
            if (i >= col) {
                j(0, col) += (-mList[i]->mLength*sin(angle));
                j(1, col) += (mList[i]->mLength*cos(angle));
            }
        }
    }
    
    return j;
}

void link_list::moveToPoint(const VectorXf position)
{
    // Nuevo target y se activa bandera
    mTargetPosition = position;
    mResolveTarget = true;
}

// Dibuja robot planar
void link_list::draw()
{
    glColor3f(0.0, 0.0, 1.0);
 
    glPushMatrix();
    
    glTranslatef(mBasePosition(0), mBasePosition(1), 0.0f);
    
    glutSolidSphere(2.0f, 20, 20);
    
    // Dibuja todos links y sus esferas (joints)
    for (int i = 0; i < mList.size(); i++) {
        mList[i]->mColor.apply(); // Color del link
        
        glRotatef(degrees(mList[i]->mAngle), 1.0f, 0.0f, 0.0f);
        gluCylinder(mList[i]->mObj, 1, 1, mList[i]->mLength, 20, 20);
        
        glTranslatef(0, 0, mList[i]->mLength);
        glutSolidSphere(1.5, 20, 20);
    }
    
    glPopMatrix();
}

void link_list::moveBy(float dx, float dy)
{
    VectorXf dAngles = VectorXf::Zero(mList.size(), 1);
    VectorXf dPosition = VectorXf::Zero(2, 1);
    
    dPosition(0) = dx;
    dPosition(1) = dy;
    
    dAngles = pseudoInverso() * dPosition;
    
    for (int i = 0; i < mList.size(); i++) mList[i]->mAngle += dAngles(i);
    
    calculatePosition();
}

void link_list::update()
{
    if(isTargetResolved()) return;
    
    float x = (mTargetPosition(0) - mPosition(0) > 1) ? mStep : -mStep;
    float y = (mTargetPosition(1) + mPosition(1) > 1) ? mStep : -mStep;
    
    moveBy(x, y);
}

bool link_list::isTargetResolved()
{
    if(fabs(mPosition(0) - mTargetPosition(0)) <= 2.0f &&
       fabs(mPosition(1) + mTargetPosition(1)) <= 2.0f) {
        mResolveTarget = false;
        return true;
    }
    
    return false;
}

VectorXf link_list::getPointWithinRange()
{
    VectorXf point = VectorXf::Zero(2, 1);
    float length = 0;
    
    for(int i = 0; i < mList.size(); i++) length += mList[i]->mLength;
    
    // Posicion aleatoria negativa/positiva en X,Y
    point(0) = ((rand() % 2 == 0) ? -1 : 1) * (rand() % (int)(length)*0.7);
    point(1) = ((rand() % 2 == 0) ? -1 : 1) * (rand() % (int)(length)*0.7);
    
    return point;
}