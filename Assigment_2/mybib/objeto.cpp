#include "objeto.h"


void Objeto::setValoresTransformacao(Transformacoes t, Vetor3D valores){
    if(t == Transformacoes::TRANSLACAO)
        this->setValoresTranslacao(valores);
    else if(t == Transformacoes::ROTACAO)
        this->setAngulosRotacao(valores);
    else if(t = Transformacoes::ESCALA)
        this->setValoresEscala(valores);
}

void Objeto::desenharObjeto(){
    glPushMatrix();
        glTranslated(tx, ty, tz);
        glRotated(ax, 1, 0, 0);
        glRotated(ay, 0, 1, 0);
        glRotated(az, 0, 0, 1);
        if(desenhaEixos)
            Desenha::drawEixos(1);
        glScaled(sx, sy, sz);

        desenhar();

   glPopMatrix();
}

void Objeto::desenharEixos()
{
    this->desenhaEixos = true;
}

void Objeto::ocultarEixos()
{
    this->desenhaEixos = false;
}

void Objeto::setValoresEscala(const Vetor3D values){
    this->sx = values.x;
    this->sy = values.y;
    this->sz = values.z;
}

void Objeto::setValoresTranslacao(const Vetor3D values){
    this->tx = values.x;
    this->ty = values.y;
    this->tz = values.z;
}

void Objeto::setAngulosRotacao(const Vetor3D values){
    this->ax = values.x;
    this->ay = values.y;
    this->az = values.z;
}

Vetor3D Objeto::getValoresTransformacao(Transformacoes t)
{
    if(t == Transformacoes::TRANSLACAO)
        return this->getValoresTranslacao();
    else if(t == Transformacoes::ROTACAO)
        return this->getAngulosRotacao();
    else if(t == Transformacoes::ESCALA)
        return this->getValoresEscala();
    else
        return Vetor3D(0,0,0);
}

Vetor3D Objeto::getValoresTranslacao()
{
    return Vetor3D(tx, ty, tz);
}

Vetor3D Objeto::getValoresEscala()
{
    return Vetor3D(sx, sy, sz);
}

Vetor3D Objeto::getAngulosRotacao()
{
    return Vetor3D(ax, ay, az);
}
