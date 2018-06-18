#include "solo.h"

Solo::Solo(){
    this->r = .2;
    this->g = 1;
    this->b = .2;
}

Solo::Solo(int tam){
    this->tam = tam;
    this->r = .2;
    this->g = 1;
    this->b = .2;
}

string Solo::identificador(){
    return "solo";
}

void Solo::desenhar(){
    if(this->selecionado) glColor3f(1,0,0);
    else glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex3f(-tam, .001, -tam);
        glVertex3f(-tam, .001, tam);
        glVertex3f(tam, .001, tam);
        glVertex3f(tam, .001, -tam);
    glEnd();
}
