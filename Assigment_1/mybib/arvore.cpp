#include "arvore.h"

Arvore::Arvore()
{
    this->r = 0;
    this->g = 0.6;
    this->b = 0;
}

string Arvore::identificador(){
    return "arvore";
}

void Arvore::desenhar(){
    GLUquadric* quad = gluNewQuadric(); //desenha objeto quadrático
    if(this->selecionado) glColor3f(1,0,0);
    else glColor3f((float)102/255, (float)51/255, 0);
    glTranslated(6.5,0,-4);
    glScaled(4,4.5,4);
    glPushMatrix();
        glTranslated(0,0,0);
        glRotated(270, 1, 0, 0);
        Desenha::gluClosedCylinder(quad, .02, .02, 1, 20, 1);
    glPopMatrix();

    if(this->selecionado) glColor3f(1,0,0);
    else glColor3d(r,g,b);

    //Cone
    glPushMatrix();
        glTranslated(0, .7, 0);
        glRotated(270, 1, 0, 0);
        Desenha::gluClosedCylinder(quad, .5, 0.2, 0.3, 20, 1);
    glPopMatrix();

    //Cone
    glPushMatrix();
        glTranslated(0, 1, 0);
        glRotated(270, 1, 0, 0);
        Desenha::gluClosedCylinder(quad, 0.4, 0.15, .25, 20, 1);
    glPopMatrix();

    //Cone
    glPushMatrix();
        glTranslated(0, 1.25, 0);
        glRotated(270, 1, 0, 0);
        Desenha::gluClosedCylinder(quad, 0.3, 0, .3, 20, 1);
    glPopMatrix();
}
