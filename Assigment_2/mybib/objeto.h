#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
#include "bib/Desenha.h"
#include "bib/Vetor3D.h"

using namespace std;

enum Transformacoes{
    TRANSLACAO, ROTACAO, ESCALA, NENHUMA
};

class Objeto
{
protected:

    float sx{1.0}, sy{1.0}, sz{1.0}; //Escalar
    float tx{0.0}, ty{0.0}, tz{0.0}; //Transladar
    float ax{0.0}, ay{0.0}, az{0.0}; //Rotacionar
    float cr{1.0}, cg{1.0}, cb{1.0}; //Cor
    bool desenhaEixos{false};
    virtual void desenhar() = 0;

public:
    bool selecionado{false};

    virtual string identificador() = 0;

    virtual void desenharObjeto();
    void desenharEixos();
    void ocultarEixos();
    void setValoresTransformacao(Transformacoes t, Vetor3D valores);
    void setValoresEscala(const Vetor3D values);
    void setValoresTranslacao(const Vetor3D values);
    void setAngulosRotacao(const Vetor3D values);
    Vetor3D getValoresTransformacao(Transformacoes t);
    Vetor3D getValoresTranslacao();
    Vetor3D getValoresEscala();
    Vetor3D getAngulosRotacao();

};

#endif // OBJECT_H
