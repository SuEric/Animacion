#ifndef link_list_H
#define link_list_H

#include <vector>

#include "color.h"
#include "Eigen/Dense"
#include "link.h"

using namespace Eigen;

class link_list {
    std::vector<Link*> mList;
    VectorXf mBasePosition;
    VectorXf mPosition;
    VectorXf mTargetPosition;
    float mStep;
    bool mResolveTarget;
    Color mColor;
    
    void calculatePosition();
    
    // Cinematica Inversa
    MatrixXf jacobiano();
    MatrixXf pseudoInverso();
public:
    link_list() {
        mBasePosition = VectorXf::Zero(2, 1);
        mPosition = VectorXf::Zero(2, 1);
        mTargetPosition = VectorXf::Zero(2, 1);
        mStep = 0.5f;
        mResolveTarget = false;
    }
    void draw();
    void moveToPoint(const VectorXf position);
    void moveBy(float dx, float dy);
    void update();
    bool isTargetResolved();
    VectorXf getPointWithinRange();
    
    inline void setStep(float step) {step = mStep;}
    inline void addLink(Link *link) {mList.push_back(link); calculatePosition();}
    inline VectorXf getPosition() {return mPosition;}
};

#endif // link_list_H
