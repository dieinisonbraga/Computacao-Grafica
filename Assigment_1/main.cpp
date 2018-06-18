#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <model3ds.h>
#include <vector>

#include "gui.h"

#include "CameraDistante.h"
#include "Desenha.h"
#include "mybib/arvoremodel.h"
#include "mybib/solo.h"
#include "mybib/objeto.h"
#include "mybib/casa.h"
#include "mybib/arvore.h"
#include "mybib/modelo3ds.h"
#include "mybib/caixa.h"
#include "mybib/muro.h"
#include "mybib/grama.h"
#include "mybib/banco.h"
#include "mybib/helpers.h"


using namespace std;

vector<Objeto*> objetos; // vetor de objetos que compoem a cena
int indexObjeto = -1; //iterador para vetor de objetos

//iterador para lista de objetos
Objeto* objetoSelecionado = NULL;
int indiceObjetoSelecionado = -1;

Transformacao transformacao = Transformacao::NENHUMA;

//variaveis globais
int width = 800;
int height = 600;

float x = 0.0;
float y = 0.0;
float z = 0.0;

//ponto em coords locais, a ser calculado em coords de mundo
float pl[4] = { 0.0, 0.0, 0.0, 1.0 };
//ponto em coords globais, resultado da conversao a partir de pl
float pg[4] = { 0.0, 0.0, 0.0, 1.0 };

bool lbpressed = false;
bool mbpressed = false;
bool rbpressed = false;
bool desenhaGrade = true;
bool desenhaEixos = true;

//bool trans_luz = false;

float last_x = 0.0;
float last_y = 0.0;

Camera* cam = new CameraDistante(0,5,40, 0,3,0, 0,1,0);
//Camera* cam2 = new CameraDistante(0,10,60, 0,1,0, 0,1,0);

//GLfloat light_position[] = { 1.5f, 1.5f, 1.5f, 1.0f };
GLfloat light_position[] = { 10, 10, 10, 1.0f };
GLint light_types[] = {GL_POSITION, GL_AMBIENT};
int selectecdLightType = 0;

float savedCamera[9];

static bool trans_luz = false;
bool projecao = true;

bool manual_cam = false;
bool change_manual_cam = false;

void desenha_camera(float tam) {
    GLUquadricObj *quad = gluNewQuadric();

    glPushMatrix();
      Desenha::drawBox( -tam,-tam,0.0, tam,tam,2*tam );
      glTranslated(0,0,-tam);
      Desenha::gluClosedCylinder(quad, tam, tam/2, tam, 16,16);
    glPopMatrix();

    gluDeleteQuadric(quad);
}


/* GLUT callback Handlers */

void resize(int w, int h)
{
    width = w;
    height = h;
}

void displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float ar = height>0 ? (float) width / (float) height : 1.0;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(projecao){
        gluPerspective(30.,ar,0.1,1000.);//Projeção pespectiva como default
    }else{
        glOrtho(-1.0, 1.0,-1.0,1.0,-1.0, 1.0);
        glOrtho(-10.0, 10.0,-10.0,10.0,-10.0,10.0);
        glOrtho(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    }

}

void displayEnd()
{
    glutSwapBuffers();
}

void displayInner()
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam->e.x,cam->e.y,cam->e.z,
              cam->c.x,cam->c.y,cam->c.z,
              cam->u.x,cam->u.y,cam->u.z);
    //sistema global
    glPushMatrix();
        if(desenhaEixos) Desenha::drawEixos(1); //desenhando eixos do sistema de coordenadas global
        if(desenhaGrade) Desenha::drawGrid( 50, 0, 50, 1 ); //chao
    glPopMatrix();

    glPushMatrix();
        GUI::setLight(0, light_position[0],light_position[1],light_position[2],false,false);
        glLightfv(GL_LIGHT0, light_types[selectecdLightType], light_position);
        GUI::drawFloor(50.0,50.0,0.5,0.5);
    glPopMatrix();

    for(auto o: objetos){
        o->desenharObjeto();
    }

    if(objetoSelecionado != NULL){
        objetoSelecionado->desenharObjeto();
    }

    for(auto o: objetos){
        o->desenharSombra(light_position);
    }

}

void display()
{
    displayInit();
    displayInner();
    displayEnd();
}

void mouseButton(int button, int state, int x, int y) {
        // if the left button is pressed
        if (button == GLUT_LEFT_BUTTON) {
                // when the button is pressed
                if (state == GLUT_DOWN) {
            lbpressed = true;
                } else {// state = GLUT_UP
            lbpressed = false;
                }
        }
        // if the middle button is pressed
        if (button == GLUT_MIDDLE_BUTTON) {
                // when the button is pressed
                if (state == GLUT_DOWN) {
            mbpressed = true;
                } else {// state = GLUT_UP
            mbpressed = false;
                }
        }
        // if the left button is pressed
        if (button == GLUT_RIGHT_BUTTON) {
                // when the button is pressed
                if (state == GLUT_DOWN) {
            rbpressed = true;
                } else {// state = GLUT_UP
            rbpressed = false;
                }
        }

    last_x = x;
    last_y = y;
}

void otherKey(int key, int x, int y){
    //se a seta para cima for apertada
    if(key == GLUT_KEY_UP){
        cam->zoom(2.0,0.0);//aumenta zoom
    }
    //se a seta para baixo for apertada
    if(key == GLUT_KEY_DOWN){
        cam->zoom(-2.0,0.0);//diminui zoom
    }
    //se a seta da esquerda for apertada
    if(key == GLUT_KEY_LEFT){
        cam->translatex(2.0,0.0);//move a camera para esquerda
    }
    //se a seta da direita for apertada
    if(key == GLUT_KEY_RIGHT){
        cam->translatex(-2.0,0.0);//move a camera para direita
    }
}

void mouseMove(int x1, int y1) {
    float fator = 10.0;
    if (lbpressed && !rbpressed && !mbpressed) {
        if(trans_luz){
            light_position[0] += (x1 - last_x)/fator;
            light_position[1] += -(y1 - last_y)/fator;
        }
        else if (transformacao == Transformacao::NENHUMA) {
            cam->rotatex(y1,last_y);
            cam->rotatey(x1,last_x);
        } else {
            z += (y1 - last_y)/fator;
            x += (x1 - last_x)/fator;
            y = objetos[indexObjeto]->getValoresTransformacao(transformacao).y;
            objetos[indexObjeto]->setTransformacao(transformacao, Vetor3D(x, y, z));
        }
    }
    fator = 100.0;
    if (!lbpressed && rbpressed && !mbpressed) {
        if(trans_luz){
            light_position[2] += (y - last_y);
        } else if (transformacao == Transformacao::NENHUMA) {
            cam->translatex(x1,last_x);
            cam->translatey(y1,last_y);
        } else {
            x += (x1 - last_x)/fator;
            y += -(y1 - last_y)/fator;
            z = objetos[indexObjeto]->getValoresTransformacao(transformacao).z;
            objetos[indexObjeto]->setTransformacao(transformacao, Vetor3D(x, y, z));
        }
    }
    if (lbpressed && rbpressed && !mbpressed) {
        cam->zoom(y1,last_y);
    }

    last_x = x1;
    last_y = y1;
}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 13 :
        case 27 :
            exit(0);
        break;

        case 'q':
            desenhaGrade = !desenhaGrade;
            break;

        case 'w':
            desenhaEixos = !desenhaEixos;
        break;

        case 'F':
            glutFullScreen();
            break;

        case 'f':
            glutReshapeWindow(800,600);
            break;

        case 'l':
            trans_luz = !trans_luz;
            break;

        case 'T':
            selectecdLightType++;
            selectecdLightType %= 2;
            break;

        //adiciona objeto no meu vetor de objetos
        case 'a':
            if(objetoSelecionado != NULL){
                objetos.push_back(objetoSelecionado);
            }
            indiceObjetoSelecionado = -1;
            objetoSelecionado = NULL;
        break;

        //deleta o objeto marcado do meu vetor de objetos
        case 'd':
            if(indexObjeto >= 0 && indexObjeto < objetos.size()){
                objetos.erase(objetos.begin() + indexObjeto);
                indexObjeto = -1;
                transformacao = Transformacao::NENHUMA;
            }
        break;

        case 't':
            if(transformacao != Transformacao::TRANSLACAO &&
                    (indexObjeto >= 0 && indexObjeto < objetos.size())){
                transformacao = Transformacao::TRANSLACAO;
                x = objetos[indexObjeto]->getEixosTranslacao().x;
                y = objetos[indexObjeto]->getEixosTranslacao().y;
                z = objetos[indexObjeto]->getEixosTranslacao().z;
            }else{
                transformacao = Transformacao::NENHUMA;
            }
        break;

        case 'r':
            if(transformacao != Transformacao::ROTACAO
                    && (indexObjeto >= 0 && indexObjeto < objetos.size())){
                transformacao = Transformacao::ROTACAO;
                x = objetos[indexObjeto]->getAngulosRotacao().x;
                y = objetos[indexObjeto]->getAngulosRotacao().y;
                z = objetos[indexObjeto]->getAngulosRotacao().z;
            }
            else
                transformacao = Transformacao::NENHUMA;
        break;

        case 'e':
            if(transformacao != Transformacao::ESCALA
                    && (indexObjeto >= 0 && indexObjeto < objetos.size())){
                transformacao = Transformacao::ESCALA;
                x = objetos[indexObjeto]->getEixosEscala().x;
                y = objetos[indexObjeto]->getEixosEscala().y;
                z = objetos[indexObjeto]->getEixosEscala().z;
            }
            else
                transformacao = Transformacao::NENHUMA;
        break;
        case 'n':
            indiceObjetoSelecionado++;
            if(indiceObjetoSelecionado < 5){
                if(indiceObjetoSelecionado%9 == 0) objetoSelecionado = new Casa();
                if(indiceObjetoSelecionado%9 == 1) objetoSelecionado = new Muro();
                if(indiceObjetoSelecionado%9 == 2) objetoSelecionado = new Arvore();
                if(indiceObjetoSelecionado%9 == 3) objetoSelecionado = new Grama();
                if(indiceObjetoSelecionado%9 == 4) objetoSelecionado = new Banco();
            } else {
               objetoSelecionado = NULL;
               indiceObjetoSelecionado = -1;
            }

        case 'm':
            indexObjeto++;
            transformacao = Transformacao::NENHUMA;
            cout << indexObjeto << endl;
            if(indexObjeto > 0 && indexObjeto <= objetos.size()){
                objetos[indexObjeto-1]->selecionado = false;
                objetos[indexObjeto-1]->escondeEixos();
            }
            else if(indexObjeto > objetos.size()){
                indexObjeto = -1;
            }
            if(indexObjeto >= 0 && indexObjeto < objetos.size()){
                objetos[indexObjeto]->selecionado = true;
                objetos[indexObjeto]->desenhaEixos();
            }
            else{
                indexObjeto = -1;
            }
        break;
        case 'b':
            indexObjeto--;
            transformacao = Transformacao::NENHUMA;
            cout << indexObjeto << endl;
            if(indexObjeto >= 0 && indexObjeto <= objetos.size()){
                objetos[indexObjeto+1]->selecionado = false;
                objetos[indexObjeto+1]->escondeEixos();
            }
            else if(indexObjeto < 0){
                indexObjeto = objetos.size();
            }
            if(indexObjeto >= 0 && indexObjeto < objetos.size()){
                objetos[indexObjeto]->selecionado = true;
                objetos[indexObjeto]->desenhaEixos();
            }
            else{
                indexObjeto = objetos.size();
            }
        break;

        case 'o':
            projecao = !projecao;
            break;

        case 'P':
        {
            Solo* solo = new Solo();
            objetos.push_back(solo);
            break;
        }

        case 'S':
        {
            cout << "Digite um nome para o arquivo: " << endl;
            string nome;
            cin >> nome;
            salvarObjetosArquivo(objetos, nome);
        break;
        }

        case 'L':
        {
            cout << "Digite o nome do arquivo: " << endl;
            string nomeL;
            cin >> nomeL;
            objetos = carregarObjetosArquivo(nomeL);
        break;
        }
    }
    glutPostRedisplay();
}

void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
        //chamadas de inicializacao da GLUT
        glutInit(&argc, argv);
        glutInitWindowSize(width,height);
        glutInitWindowPosition(10,10);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("Trabalho I");

        // Definindo as funções callback
        glutReshapeFunc(resize);
        glutDisplayFunc(display);
        glutKeyboardFunc(key);
        glutSpecialFunc(otherKey); //função de callback para chamada de teclas especias
        glutIdleFunc(idle);
        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

        //chamadas de inicializacao da OpenGL
        //glClearColor(0.3,0.3,0.3,1.0);
        glClearColor(0,0,0,1);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        //definindo uma luz
        glEnable(GL_LIGHT0);

        const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

        const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
        const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
        const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat high_shininess[] = { 100.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

        glutMainLoop();

    return EXIT_SUCCESS;
}
