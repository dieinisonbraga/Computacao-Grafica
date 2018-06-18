#include "arvoremodel.h"

ArvoreModel::ArvoreModel()
{
    this->modelo = new Model3DS("3ds/Tree.3ds");
    this->tx = 0.0;
    this->ty = 0.0;
    this->tz = 0.0;
}

//glBindTexture(GL_TEXTURE_2D, )

void ArvoreModel::desenhar(){
    if(this->selecionado) glColor3f(1,0,0);
    else glColor3f(0,1,0);
    glPushMatrix();
        glTranslated(0,0,0);
        glRotated(270,1,0,0);
        glScaled(0.2, 0.2, 0.2);
        modelo->draw();
    glPopMatrix();
}


