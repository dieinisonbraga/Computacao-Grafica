#ifndef SOLO_H
#define SOLO_H

#include "objeto.h"

class Solo : public Objeto
{
private:
    int tam{100};
public:
    Solo();

    Solo(int tam);
    void setTamanho(int tam);
    string identificador();
    void desenhar();
};

#endif // SOLO_H
