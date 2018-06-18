#ifndef CAIXA_H
#define CAIXA_H

#include "objeto.h"

class Caixa : public Objeto
{
public:
    Caixa();
    string identificador();
    void desenhar();
};

#endif // CAIXA_H
