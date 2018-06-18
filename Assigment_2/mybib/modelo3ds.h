#ifndef DESENHADOR3DS_H
#define DESENHADOR3DS_H

#include "objeto.h"
#include "model3ds.h"
#include <GL/glut.h>
#include <GL/gl.h>

class Modelo3DS : public Objeto
{
protected:
    Model3DS* modelo;

};

#endif // DESENHADOR3DS_H
