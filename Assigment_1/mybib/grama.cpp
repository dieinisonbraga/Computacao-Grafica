#include "grama.h"

Grama::Grama()
{
    this->modelo = new Model3DS("3ds/grass-block.3DS");
    this->tx = 0.0;
    this->ty = 0.0;
    this->tz = 0.0;
}

string Grama::identificador(){
    return "grama";
}

void Grama::desenhar(){
    if(this->selecionado) glColor3f(1,0,0);
    else glColor3f(0,0.9,0);
    glPushMatrix();
        glTranslated(5,0.2,-5);
        glRotated(270,1,0,0);
        glScaled(0.2, 0.15, 0.06);
        modelo->draw();
    glPopMatrix();
}
