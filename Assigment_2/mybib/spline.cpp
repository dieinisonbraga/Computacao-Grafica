#include "spline.h"

Spline::Spline(){
    p = new Vetor3D[4];
    this->setMode(SplineMode::BSPLINE);
}

void Spline::setPontosControle(vector<Vetor3D> pontosControle){
    pn.clear();
    for(Vetor3D p : pontosControle){
        this->pn.push_back(p);
    }

    for(int i = 0; i<pn.size() && pn.size() <= 4; i++){
        p[i] = pn[i];
    }

}

void Spline::removePontosControle(){
    this->pn.clear();
    delete p;
    p = new Vetor3D[4];
}

void Spline::addPontoControle(Vetor3D ponto){
    this->pn.push_back(ponto);
}

void Spline::setMode(SplineMode mode){
    this->mode = mode;

    if(mode == SplineMode::INTERPOLADORA){
        float Maux[4][4] = {
            {1, 0, 0, 0},
            {-5.5, 9, -4.5, 1},
            {9, -22.5, 18, -4.5},
            {-4.5, 13.5, -13.5, 4.5}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                M[i][j] = Maux[i][j];
            }
        }
    }

    if(mode == SplineMode::HERMITE){
        float Maux[][4] = {
            {2, -2, 1, 1},
            {-3, 3, -2, -1},
            {0, 0, 1, 0},
            {1, 0, 0, 0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                M[i][j] = Maux[i][j];
            }
        }
    }
    else if(mode == SplineMode::BEZIER){
        float Maux[][4] = {
            {-1, 3, -3, 1},
            {3, -6, 3, 0},
            {-3, 3, 0, 0},
            {1, 0, 0, 0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                M[i][j] = Maux[i][j];
            }
        }

    }
    else if(mode == SplineMode::BSPLINE){
        float Maux[][4] = {
            {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
            {3/6.0, -6/6.0, 3/6.0, 0/6.0},
            {-3/6.0, 0/6.0, 3/6.0, 0/6.0},
            {1/6.0, 4/6.0, 1/6.0, 0/6.0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                M[i][j] = Maux[i][j];
            }
        }
    }
    else if(mode == SplineMode::CATMULLROM){
        float Maux[][4] = {
            {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
            {2/2.0, -5/2.0, 4/2.0, -1/2.0},
            {-1/2.0, 0.0, 1/2.0, 0.0},
            {0.0, 2/2.0, 0.0, 0.0}
        };

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                M[i][j] = Maux[i][j];
            }
        }
    }
}

SplineMode Spline::getMode(){
    return this->mode;
}

Vetor3D Spline::getPoint(float u){

    Vetor3D resultado;
    float us[] = {pow(u, 3), pow(u, 2), u, 1};

    float matriz[4];

    for(int i = 0; i<4; i++){
        matriz[i] = 0;
        for(int j = 0; j<4; j++){
            matriz[i] += us[j] * M[j][i];
        }
    }

    for(int i = 0; i<4; i++){
        resultado.x += matriz[i] * p[i].x;
        resultado.y += matriz[i] * p[i].y;
        resultado.z += matriz[i] * p[i].z;
    }

    return resultado;
}

Vetor3D Spline::getD1(float u){

    Vetor3D resultado;
    float us[] = {3*pow(u, 2), 2*u, 1, 0};

    float matriz[4];

    for(int i = 0; i<4; i++){
        matriz[i] = 0;
        for(int j = 0; j<4; j++){
            matriz[i] += us[j] * M[j][i];
        }
    }

    for(int i = 0; i<4; i++){
        resultado.x += matriz[i] * p[i].x;
        resultado.y += matriz[i] * p[i].y;
        resultado.z += matriz[i] * p[i].z;
    }

    return resultado;

}

Vetor3D Spline::getD2(float u){

    Vetor3D resultado;
    float us[] = {6*u, 2, 0, 0};

    float matriz[4];

    for(int i = 0; i<4; i++){
        matriz[i] = 0;
        for(int j = 0; j<4; j++){
            matriz[i] += us[j] * M[j][i];
        }
    }

    for(int i = 0; i<4; i++){
        resultado.x += matriz[i] * p[i].x;
        resultado.y += matriz[i] * p[i].y;
        resultado.z += matriz[i] * p[i].z;
    }

    return resultado;

}

vector<Vetor3D> Spline::getPontosControle(){
    return pn;
}

int Spline::getQtdPontosControle(){
    return pn.size();
}

void Spline::desenharCurva(){

    Vetor3D ponto;
    for(int i = 0; i<=pn.size()-4; i++){

        for(int j = 0; j<4; j++){
            ponto = pn[i+j];
            p[j] = ponto;
        }

        for(float u = 0; u<=1; u+=delta){
            Vetor3D z_ = getD1(u) * (-1);
            Vetor3D y_ = getD2(u);
            Vetor3D x_ = y_ ^ z_;
            y_ = z_ ^ x_;
            Vetor3D t_ = getPoint(u);
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
                glColor3f(0, 0, 0);
                glMultTransposeMatrixd(T);
                desenharTrechoLocal();
            glPopMatrix();

        }
    }

}

void Spline::desenharTrechoLocal(){

    glPushMatrix();
        glTranslated(0.25, 0, 0);
        glRotated(90, 0, 1, 0);
        glRotated(180, 1, 0, 0);
        glPushMatrix();
            glColor3f(0,0,0);
            Desenha::drawQuadFace(Vetor3D(0,0,0), Vetor3D(.1, 0, .9));
            glColor3f(1,1,1);
            Desenha::drawQuadFace(Vetor3D(0, 0.001, .29), Vetor3D(.3, 0.001, .31));
        glPopMatrix();
    glPopMatrix();
}
