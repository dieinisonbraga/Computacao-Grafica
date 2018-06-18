#ifndef PONTOCONTROLE_H
#define PONTOCONTROLE_H

#include "objeto.h"

class PontoControle : public Objeto
{
public:
    PontoControle(Vetor3D valoresTranslacao);

    void desenhar();

    string identificador();

    Vetor3D toVetor3D();

};

#endif // PONTOCONTROLE_H
