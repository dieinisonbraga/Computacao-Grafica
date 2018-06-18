#ifndef BANCO_H
#define BANCO_H

#include "modelo3ds.h"

class Banco : public Modelo3DS
{
public:
    Banco();
    string identificador();
    void desenhar();
};

#endif // BANCO_H
