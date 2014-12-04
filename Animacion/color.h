#ifndef Animacion_COLOR_H
#define Animacion_COLOR_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

struct Color {
  float r;
  float g;
  float b;
  float a;
  inline void apply() {glColor4f(r, g, b, a);}
};

#endif // COLOR_H
