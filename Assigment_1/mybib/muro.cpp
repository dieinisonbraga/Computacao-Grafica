#include "muro.h"

Muro::Muro(){
    this->r = 1;
    this->g = (float)204/255;
    this->b = (float)153/255;
}

string Muro::identificador(){
    return "muro";
}

void Muro::desenhar(){
    if(this->selecionado) glColor3f(1,0,0);
    else glColor3d(r, g, b);
    glPushMatrix();
        glTranslated(0,0.5,0);

        glPushMatrix();
            glTranslated(7, 0.5, 7);
            glScaled(5, 2, 1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-3, 0.5, 7);
            glScaled(5, 2, 1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(2, 1, -7);
            glScaled(14, 3, 1);
            glutSolidCube(1);
        glPopMatrix();


        glPushMatrix();
            glTranslated(9, 1, 0);
            glScaled(1, 3, 15);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-5, 1, 0);
            glScaled(1, 3, 15);
            glutSolidCube(1);
        glPopMatrix();
     glPopMatrix();
}
