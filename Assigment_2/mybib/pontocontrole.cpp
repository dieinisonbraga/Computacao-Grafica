#include "pontocontrole.h"

PontoControle::PontoControle(Vetor3D valoresTranslacao)
{
    this->tx = valoresTranslacao.x;
    this->ty = valoresTranslacao.y;
    this->tz = valoresTranslacao.z;
}

void PontoControle::desenhar(){
    if(!selecionado)glColor3f(0, 0, 1);
    else glColor3f(1, 1, 0);
    glutSolidSphere(.1, 36, 36);
}

string PontoControle::identificador(){
    return "pontoControle";
}

Vetor3D PontoControle::toVetor3D(){
    return Vetor3D(tx, ty, tz);
}
