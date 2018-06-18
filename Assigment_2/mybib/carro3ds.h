#ifndef CARRO3DS_H
#define CARRO3DS_H

#include "modelo3ds.h"
#include "spline.h"
#include "CameraDistante.h"

class Spline;

class Carro3ds : public Modelo3DS
{
private:
    float u{0.0};
    float delta{0.01};
public:
    Carro3ds();
    ~Carro3ds();

    string identificador();

    void moverFrente();

    void moverTras();

    void desenhar();

    void desenharComSpline(Spline spline, Camera *cam);

};

#endif // CARRO3DS_H
