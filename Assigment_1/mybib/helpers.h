#ifndef HELPERS_H
#define HELPERS_H

#endif // HELPERS_H

#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "mybib/solo.h"
#include "mybib/arvoremodel.h"
#include "mybib/modelo3ds.h"
#include "mybib/arvore.h"
#include "mybib/banco.h"
#include "mybib/casa.h"
#include "mybib/grama.h"
#include "mybib/muro.h"
#include "mybib/objeto.h"

vector<Objeto*> carregarObjetosArquivo(string fileName);
void salvarObjetosArquivo(vector<Objeto*> objetos, string fileName);
