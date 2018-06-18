#ifndef MODELO3DS_H
#define MODELO3DS_H

#include <GL/glut.h>
#include <GL/gl.h>
#include "objeto.h"
#include "model3ds.h"


class Modelo3DS : public Objeto
{
protected:
    Model3DS* modelo;
};

#endif // MODELO3DS_H
