#include "carro3ds.h"

Carro3ds::Carro3ds()
{
    this->modelo = new Model3DS("models/Cilek__Bed.3DS");
}

string Carro3ds::identificador(){
    return "carro3ds";
}

void Carro3ds::moverFrente(){
    u += delta;
}

void Carro3ds::moverTras(){
    u -= delta;
}

void Carro3ds::desenhar()
{
    cout << "..." << endl;
}

void Carro3ds::desenharComSpline(Spline spline, Camera* cam){

    Vetor3D ponto;
    static int i = 0;
    for(int j = 0; j<4; j++){
        ponto = spline.pn[i+j];
        spline.p[j] = ponto;
    }

    Vetor3D z_ = spline.getD1(u) * (-1);
    Vetor3D y_ = spline.getD2(u);
    Vetor3D x_ = y_ ^ z_;
    y_ = z_ ^ x_;
    Vetor3D t_ = spline.getPoint(u);
    z_.normaliza();
    y_.normaliza();
    x_.normaliza();

    double T[] = {
        x_.x, y_.x, z_.x, t_.x,
        x_.y, y_.y, z_.y, t_.y,
        x_.z, y_.z, z_.z, t_.z,
        0   , 0   , 0   , 1
    };

    glPushMatrix();
        glColor3f(1, 0, 0);
        glMultTransposeMatrixd(T);
        glTranslated(0, -0.01, 0);
        glRotated(85, 1, 0, 0);
        glScaled(.01,.01,.01);
        this->modelo->drawModel();
    glPopMatrix();

    if(u >= 1){
        u = 0;
        i++;
        if(i > spline.pn.size()-4)
            i = 0;
    }

    cam->e = spline.getPoint(u-20*delta) ;
    cam->c = spline.getPoint(u) + spline.getD1(u);
    cam->u = (spline.getD2(u-20*delta) * (-1)).getUnit();
    cam->e = cam->u + cam->e;
}
