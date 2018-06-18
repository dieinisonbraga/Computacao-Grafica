#include "objeto.h"

void Objeto::desenharObjeto(){
    //incluir objeto com sistema local já alinhado
    //com o sistema global
    glPushMatrix();

        glTranslated(tx,ty,tz);
        glRotated(ax,1,0,0);
        glRotated(ay,0,1,0);
        glRotated(az,0,0,1);
        if(drawEixos){
            Desenha::drawEixos(1);
        }
        glScaled(sx, sy, sz);

        desenhar();

    glPopMatrix();
}

bool Objeto::getDrawEixos(){
    return this->drawEixos;
}

void Objeto::desenhaEixos(){
    this->drawEixos = true;
}

void Objeto::escondeEixos(){
    this->drawEixos = false;
}

Vetor3D Objeto::getValoresTransformacao(Transformacao t){
    if(t == Transformacao::TRANSLACAO)
        return this->getEixosTranslacao();
    else if(t == Transformacao::ROTACAO)
        return this->getAngulosRotacao();
    else if(t == Transformacao::ESCALA)
        return this->getEixosEscala();
    else
        return Vetor3D(0,0,0);
}

void Objeto::setTransformacao(Transformacao t, Vetor3D valores){
    if(t == TRANSLACAO){
        this->setTransalacao(valores);
    }
    else if(t == ROTACAO){
        this->setRotacao(valores);
    }
    else if(t == ESCALA){
        this->setEscala(valores);
    }
}

void Objeto::setTransalacao(Vetor3D valores){
    this->tx = valores.x;
    this->ty = valores.y;
    this->tz = valores.z;
}

void Objeto::setRotacao(Vetor3D valores){
    this->ax = valores.x;
    this->ay = valores.y;
    this->az = valores.z;
}

void Objeto::setEscala(Vetor3D valores){
    this->sx = valores.x;
    this->sy = valores.y;
    this->sz = valores.z;
}

Vetor3D Objeto::getEixosTranslacao(){
    return Vetor3D(this->tx, this->ty, this->tz);
}

Vetor3D Objeto::getEixosEscala(){
    return Vetor3D(this->ax, this->ay, this->az);
}

Vetor3D Objeto::getAngulosRotacao(){
    return Vetor3D(this->sx, this->sy, this->sz);
}

void Objeto::desenharSombra(GLfloat *light_position){
    glPushMatrix();
    //matriz de projecão para gerar a sombra no plano y=0
    float sombrax[16] = {
        light_position[1], -light_position[0], 0.0, 0.0,
        0.0,               0.0,                0.0, 0.0,
        0.0, -light_position[2], light_position[1], 0.0,
        0.0, -light_position[3], 0.0,               light_position[1]
    };
    glMultTransposeMatrixf(sombrax);
    glTranslated(tx,ty,tz);
    glRotated(ax,1,0,0);
    glRotated(ay,0,1,0);
    glRotated(az,0,0,1);
    glScaled(sx, sy, sz);
    glDisable(GL_LIGHTING);
        glColor3d(.0,.0,.0);
        desenharObjeto();
    glEnable(GL_LIGHTING);
    glPopMatrix();

//    glPushMatrix();
//    //matriz de projecão para gerar a sombra no plano z=0
//    float sombraz[16] = {
//        light_position[2], 0.0, -light_position[0], 0.0,
//        0.0, light_position[2], -light_position[1], 0.0,
//        0.0, 0.0, 0.0, 0.0,
//        0.0, 0.0, -light_position[3], light_position[2]
//    };
//    glMultTransposeMatrixf(sombraz);
//    glTranslated(tx,ty,tz);
//    glRotated(ax,1,0,0);
//    glRotated(ay,0,1,0);
//    glRotated(az,0,0,1);
//    glScaled(sx, sy, sz);
//    glDisable(GL_LIGHTING);
//        glColor3d(0.0,0.0,0.0);
//        desenhar();
//    glEnable(GL_LIGHTING);
//    glPopMatrix();

//    glPushMatrix();
//    //matriz de projecão para gerar a sombra no plano x=0
//    float sombray[16] = {
//        0.0,               0.0,                0.0, 0.0,
//        -light_position[1], light_position[0], 0.0, 0.0,
//        -light_position[2], 0.0, light_position[0], 0.0,
//        -light_position[3], 0.0, 0.0,light_position[0]
//    };
//    glMultTransposeMatrixf(sombray);
//    glTranslated(tx,ty,tz);
//    glRotated(ax,1,0,0);
//    glRotated(ay,0,1,0);
//    glRotated(az,0,0,1);
//    glScaled(sx, sy, sz);
//    glDisable(GL_LIGHTING);
//        glColor3d(0.0,0.0,0.0);
//        desenhar();
//    glEnable(GL_LIGHTING);
//    glPopMatrix();
}
