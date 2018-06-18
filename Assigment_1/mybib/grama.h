#ifndef GRAMA_H
#define GRAMA_H

#include "modelo3ds.h"

class Grama : public Modelo3DS
{
public:
    Grama();
    string identificador();
    void desenhar();
};

#endif // GRAMA_H
