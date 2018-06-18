#ifndef ARVORE_H
#define ARVORE_H

#include "objeto.h"

class Arvore : public Objeto
{
public:
    Arvore();
    string identificador();
    void desenhar();
};

#endif // ARVORE_H
