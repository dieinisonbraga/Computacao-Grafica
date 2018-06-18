#ifndef SPLINE_H
#define SPLINE_H

#include "Vetor3D.h"
#include "pontocontrole.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include "mybib/carro3ds.h"
using namespace std;

enum SplineMode{
    INTERPOLADORA, BEZIER, HERMITE, BSPLINE, CATMULLROM
};

class Spline
{

friend class Carro3ds;
friend class Carro;
private:
    float M[4][4];
    Vetor3D* p;
    vector<Vetor3D> pn;
    float delta{.001};
    SplineMode mode;



public:
    Spline();

    void setPontosControle(vector<Vetor3D> pontosControle);

    void removePontosControle();

    void addPontoControle(Vetor3D ponto);

    void setMode(SplineMode);

    SplineMode getMode();

    Vetor3D getPoint(float u);

    Vetor3D getD1(float u);

    Vetor3D getD2(float u);

    vector<Vetor3D> getPontosControle();

    int getQtdPontosControle();

    void desenharCurva();

    void desenharTrechoLocal();

    friend class Carro3ds;
};

#endif // SPLINE_H
