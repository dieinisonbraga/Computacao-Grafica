#include "mybib/helpers.h"

using namespace std;

vector<Objeto*> carregarObjetosArquivo(string fileName){

    vector<Objeto*> objetos;
    ifstream file;
    file.open(fileName);

    if(file.is_open()){

        while(!file.eof()){
            string linha;
            getline(file, linha);
            stringstream ss(linha);

            string tipoObj;

            if(linha[0] != '#'){

                Objeto* obj;

                ss >> tipoObj;
                if(tipoObj == "arvore") obj = new Arvore();
                else if(tipoObj == "muro") obj = new Muro();
                else if(tipoObj == "casa") obj = new Casa();
                else if(tipoObj == "grama") obj = new Grama();
                else if(tipoObj == "banco") obj = new Banco();
                else if(tipoObj == "solo") obj = new Solo();

                float sx, sy, sz; //Escalar
                float tx, ty, tz; //Transladar
                float ax, ay, az; //Rotacionar

                //Lendo valores translação
                ss >> tx;
                ss >> ty;
                ss >> tz;

                //Lendo valores rotacao
                ss >> ax;
                ss >> ay;
                ss >> az;

                //Lendo valores escala
                ss >> sx;
                ss >> sy;
                ss >> sz;

                obj->setTransalacao(Vetor3D(tx, ty, tz));
                obj->setRotacao(Vetor3D(ax, ay, az));
                obj->setEscala(Vetor3D(sx, sy, sz));
                objetos.push_back(obj);

            }

        }

        return objetos;

    }else{
        cout << "Erro ao abrir arquivo..." << endl;
        exit(-1);
    }

}

void salvarObjetosArquivo(vector<Objeto*> objetos, string fileName){
    ofstream file;
    file.open(fileName);

    for(auto o : objetos){

        float tx = o->getEixosTranslacao().x;
        float ty = o->getEixosTranslacao().y;
        float tz = o->getEixosTranslacao().z;

        float sx = o->getEixosEscala().x;
        float sy = o->getEixosEscala().y;
        float sz = o->getEixosEscala().z;

        float ax = o->getAngulosRotacao().x;
        float ay = o->getAngulosRotacao().y;
        float az = o->getAngulosRotacao().z;

        file << o->identificador() << " "
             << tx << " " << ty << " " << tz << " "
             << ax << " " << ay << " " << az << " "
             << sx << " " << sy << " " << sz << " ";

        file << endl;
    }

}
