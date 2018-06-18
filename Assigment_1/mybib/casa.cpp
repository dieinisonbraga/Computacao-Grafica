#include "casa.h"

Casa::Casa(){
    this->r = 1;
    this->g = (float)204/255;
    this->b = (float)153/255;
}

string Casa::identificador(){
    return "casa";
}

void Casa::desenhar(){
    //paredes
    glRotated(90,0,1,0);
    glPushMatrix();
        if(this->selecionado) glColor3f(1,0,0);
        else glColor3d(r, g, b);
        glTranslated(0, 2.3, 0);
        glScaled(5, 4.5, 8);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        if(this->selecionado) glColor3f(1,0,0);
        else glColor3d(r, g, b);
        glTranslated(0, 4.6, -2);
        glScaled(5, 4.5, 4);
        glutSolidCube(1);
    glPopMatrix();
    //teto
    glPushMatrix();
        if(selecionado) glColor3f(1,0,0);
        else glColor3f(.59,.29,0);
        glRotated(270, 1,0,0);
        glTranslated(0, -1.9, 4.5);
        glutSolidCone(3, 2.5, 50,5);
    glPopMatrix();
    glPushMatrix();
        if(selecionado) glColor3f(1,0,0);
        else glColor3f(.59,.29,0);
        glRotated(270, 1,0,0);
        glTranslated(0, 1.9, 6.8);
        glutSolidCone(3, 2.5, 50,5);
    glPopMatrix();
    glTranslated(-2.5,0.1,-1);
    glRotated(270,0,1,0);
    glScaled(1.3,1.3,1.3);
    //porta
    glBegin(GL_POLYGON);
      glTranslated(-4.5,0,0);
       glColor3d(1,1,1);
        glVertex3d( 1.5, 0.0, 0.01 );
        glVertex3d( 2.5, 0.0, 0.01 );
        glVertex3d( 2.5, 2.0, 0.01 );
        glVertex3d( 1.5, 2.0, 0.01 );
    glEnd();
    glPushMatrix();
        glTranslated(1.59,1,0);
        glScaled(0.1,0.1,0.1);
        glColor3f(0,0,0);
        glutSolidSphere(1,10,5);
    glPopMatrix();
    //janela
    glTranslated(-5.4,1,0);
    glScaled(1.5,1.5,1.5);
    glBegin(GL_POLYGON);
      glColor3d(1,1,1);
        glVertex3d( 2.6, 1.5, 0.01 );
        glVertex3d( 3.6, 1.5, 0.01 );
        glVertex3d( 3.6, 2.5, 0.01 );
        glVertex3d( 2.6, 2.5, 0.01 );
    glEnd();
    glBegin(GL_LINES);
      glColor3d(0,0,1);
        glVertex3d( 2.6, 2.0, 0.02 );
        glVertex3d( 3.6, 2.0, 0.02 );
        glVertex3d( 3.1, 1.5, 0.02 );
        glVertex3d( 3.1, 2.5, 0.02 );
    glEnd();
    glTranslated(0,-1.5,0);
    glBegin(GL_POLYGON);
      glColor3d(1,1,1);
        glVertex3d( 2.6, 1.5, 0.01 );
        glVertex3d( 3.6, 1.5, 0.01 );
        glVertex3d( 3.6, 2.5, 0.01 );
        glVertex3d( 2.6, 2.5, 0.01 );
    glEnd();
    glBegin(GL_LINES);
      glColor3d(0,0,1);
        glVertex3d( 2.6, 2.0, 0.02 );
        glVertex3d( 3.6, 2.0, 0.02 );
        glVertex3d( 3.1, 1.5, 0.02 );
        glVertex3d( 3.1, 2.5, 0.02 );
    glEnd();
}
