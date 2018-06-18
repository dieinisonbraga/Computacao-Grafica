#ifndef OBJETO_H
#define OBJETO_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
#include "bib/Desenha.h"
#include "bib/Vetor3D.h"

using namespace std;

enum Transformacao{
    TRANSLACAO, ESCALA, ROTACAO, NENHUMA
};

class Objeto
{
protected:

    float sx{1.0}, sy{1.0}, sz{1.0}; //Escalar
    float tx{0.0}, ty{0.0}, tz{0.0}; //Transladar
    float ax{0.0}, ay{0.0}, az{0.0}; //Rotacao
    float r{0.0}, g{0.0}, b{0.0}; //cor
    bool drawEixos{false}; // não desenhar eixos por padrão
    virtual void desenhar() = 0;

public:
    bool selecionado{false}; //atributo para informar se o objeto esta selecionado, falso por padrão
    virtual void desenharSombra(GLfloat* light_position);
    virtual void desenharObjeto();
    virtual string identificador() = 0;
    bool getDrawEixos();
    void desenhaEixos();
    void escondeEixos();
    void setTransformacao(Transformacao t, Vetor3D valores);
    void setTransalacao(Vetor3D valores);
    void setEscala(Vetor3D valores);
    void setRotacao(Vetor3D valores);
    Vetor3D getValoresTransformacao(Transformacao t);
    Vetor3D getEixosTranslacao();
    Vetor3D getEixosEscala();
    Vetor3D getAngulosRotacao();
};

#endif // OBJETO_H
