#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "bib/CameraDistante.h"
#include "bib/Desenha.h"
#include "mybib/spline.h"
#include "mybib/carro3ds.h"

using namespace std;

int width = 800;
int height = 600;

float tx = 0.0;
float ty = 0.0;
float tz = 0.0;

//ponto em coords locais, a ser calculado em coords de mundo
float pl[4] = { 0.0, 0.0, 0.0, 1.0 };
//ponto em coords globais, resultado da conversao a partir de pl
float pg[4] = { 0.0, 0.0, 0.0, 1.0 };

bool lbpressed = false;
bool mbpressed = false;
bool rbpressed = false;
bool desenhaEixos = true;
bool desenhaGrade = true;

float savedCamera[9];

float last_x = 0.0;
float last_y = 0.0;

vector<PontoControle*> pontosControle;
int indiceObjeto = -1;
bool mostrarPontosControle;

Transformacoes transformacao = Transformacoes::NENHUMA;

vector<Camera*> cameras;
Camera* cam;

Spline *spline;
Carro3ds *carro;

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

    gluPerspective(50.,ar,0.1,1000.);
}

void displayEnd()
{
    glutSwapBuffers();
}

void displayInner()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cam->e.x, cam->e.y, cam->e.z,
              cam->c.x, cam->c.y, cam->c.z,
              cam->u.x, cam->u.y, cam->u.z);

    glPushMatrix();
    if(desenhaEixos)
        Desenha::drawEixos(1);
    if(desenhaGrade)
        Desenha::drawGrid(10, 0, 10, 1);
    glPopMatrix();

    if(mostrarPontosControle){
        for(auto p : pontosControle){
            p->desenharObjeto();
        }
    }

    vector<Vetor3D> pontos;
    for(PontoControle* p : pontosControle){
        pontos.push_back(p->getValoresTranslacao());
    }
    spline->setPontosControle(pontos);
    spline->desenharCurva();
    carro->desenharComSpline(*spline, cameras[1]);
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

void mouseMove(int x, int y) {
    float fator = 10.0;
    if (lbpressed && !rbpressed && !mbpressed) {
        if (transformacao == Transformacoes::NENHUMA) {
            cam->rotatex(y,last_y);
            cam->rotatey(x,last_x);
        } else {
            tz += (y - last_y)/fator;
            tx += (x - last_x)/fator;
            ty = pontosControle[indiceObjeto]->getValoresTransformacao(transformacao).y;
            pontosControle[indiceObjeto]->setValoresTransformacao(transformacao, Vetor3D(tx, ty, tz));
        }
    }
    fator = 100.0;
    if (!lbpressed && rbpressed && !mbpressed) {
        if (transformacao == Transformacoes::NENHUMA) {
            cam->translatex(x,last_x);
            cam->translatey(y,last_y);
        } else {
            tx += (x - last_x)/fator;
            ty += -(y - last_y)/fator;
            tz = pontosControle[indiceObjeto]->getValoresTransformacao(transformacao).z;
            pontosControle[indiceObjeto]->setValoresTransformacao(transformacao, Vetor3D(tx, ty, tz));
        }
    }
    if (lbpressed && rbpressed && !mbpressed) {
        cam->zoom(y,last_y);
    }

    last_x = x;
    last_y = y;
}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 13:
    case 27:
        exit(0);
        break;
    case 'q':
        desenhaGrade = !desenhaGrade;
        break;

    case 'F':
        glutFullScreen();
        break;

    case 'I':
        spline->setMode(SplineMode::INTERPOLADORA);
        break;

    case 'B':
        spline->setMode(SplineMode::BEZIER);
        break;

    case 'H':
        spline->setMode(SplineMode::HERMITE);
        break;

    case 'C':
        spline->setMode(SplineMode::CATMULLROM);
        break;

    case 'S':
        spline->setMode(SplineMode::BSPLINE);
        break;

    case 'c':
        static int posCam = 0;
        posCam++;
        cam = cameras[posCam%cameras.size()];
    break;

    case 'f':
        glutReshapeWindow(800,600);
        break;

    case 'p':
        mostrarPontosControle = !mostrarPontosControle;
        break;

    case 'n':
        if(spline->getMode() == SplineMode::BSPLINE || spline->getMode() == SplineMode::CATMULLROM)
            pontosControle.push_back(new PontoControle(Vetor3D(0,0,0)));
        break;
    case 't':
        if(transformacao != Transformacoes::TRANSLACAO
                && (indiceObjeto >= 0 && indiceObjeto < pontosControle.size())){
            transformacao = Transformacoes::TRANSLACAO;
            tx = pontosControle[indiceObjeto]->getValoresTranslacao().x;
            ty = pontosControle[indiceObjeto]->getValoresTranslacao().y;
            tx = pontosControle[indiceObjeto]->getValoresTranslacao().z;
        }
        else
            transformacao = Transformacoes::NENHUMA;
        break;

    case 's':
        indiceObjeto++;
        transformacao = Transformacoes::NENHUMA;
        if(indiceObjeto > 0 && indiceObjeto <= pontosControle.size()){
            pontosControle[indiceObjeto-1]->selecionado = false;
        }
        else if(indiceObjeto > pontosControle.size()){
            indiceObjeto = -1;
        }
        if(indiceObjeto >= 0 && indiceObjeto < pontosControle.size()){
            pontosControle[indiceObjeto]->selecionado = true;
        }
        else{
            indiceObjeto = -1;
        }
        break;

    case 'w':
    {
        desenhaEixos = !desenhaEixos;
        break;
    }

    }

    glutPostRedisplay();
}

void specialKey(int key, int x, int y){
    if(key == GLUT_KEY_DOWN){
        carro->moverTras();
    }
    if(key == GLUT_KEY_UP){
        carro->moverFrente();
    }
}

void idle(void)
{
    glutPostRedisplay();
}

void inicializar(int* argc, char** argv){
    //chamadas de inicializacao da GLUT
    glutInit(argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Trabalho II");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutIdleFunc(idle);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    //chamadas de inicializacao da OpenGL
    //glClearColor(1,1,1,1);
    glClearColor(0.3,0.3,0.3,1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);

    //iniciando o loop principal da glut
    glutMainLoop();
}

int main(int argc, char** argv)
{

    cameras.push_back(new CameraDistante());
    cameras.push_back(new CameraDistante());

    cam = cameras[0];

    spline = new Spline();
    spline->addPontoControle(Vetor3D(0, 0, 0));
    spline->addPontoControle(Vetor3D(1, 1, 0));
    spline->addPontoControle(Vetor3D(5, 2, 0));
    spline->addPontoControle(Vetor3D(5, 0, 0));

    for(Vetor3D v : spline->getPontosControle()){
        pontosControle.push_back(new PontoControle(v));
    }

    carro = new Carro3ds();
    inicializar(&argc, argv);

    return EXIT_SUCCESS;
}
