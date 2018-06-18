#include "prediomodel.h"

predioModel::predioModel()
{
    this->modelo = new Model3DS("3ds/Dragon/Dragon.3DS");
    this->tx = 0.0;
    this->ty = 0.0;
    this->tz = 0.0;
}

void predioModel::desenhar(){
    if(this->selecionado) glColor3f(1,0,0);

    glPushMatrix();
        glTranslated(0,1,0);
        glRotated(270,1,0,0);
        modelo->draw();
    glPopMatrix();
}
