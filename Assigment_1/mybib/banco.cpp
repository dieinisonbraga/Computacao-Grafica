#include "banco.h"

Banco::Banco()
{
    this->modelo = new Model3DS("3ds/Cgtuts_Wood_Bench_3DS.3DS");
    this->tx = 0.0;
    this->ty = 0.0;
    this->tz = 0.0;
}


string Banco::identificador(){
    return "banco";
}

void Banco::desenhar(){
    if(this->selecionado) glColor3f(1,0,0);
    else glColor3f(0.55,0.34,0.26);
    glPushMatrix();
        glTranslated(6,0,0);
        glRotated(270,1,0,0);
        glRotated(270,0,0,1);
        glScaled(0.01, 0.01, 0.01);
        modelo->draw();
    glPopMatrix();
}
