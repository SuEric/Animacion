//
//  math_3d.h
//  Animacion
//
//  Created by sueric on 06/10/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#ifndef Animacion_math_3d_h
#define Animacion_math_3d_h

struct Vector3f
{
    float x;
    float y;
    float z;
    
    Vector3f()
    {
    }
    
    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};


struct Matrix4f
{
    float m[4][4];
};


#endif
