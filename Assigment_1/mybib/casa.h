#ifndef CASA_H
#define CASA_H

#include "objeto.h"

class Casa : public Objeto
{
public:
    Casa();
    string identificador();
    void desenhar();
};

#endif // CASA_H
