#ifndef MURO_H
#define MURO_H

#include "objeto.h"

class Muro : public Objeto
{
public:
    Muro();
    string identificador();
    void setCor();
    void desenhar();
};

#endif // MURO_H
