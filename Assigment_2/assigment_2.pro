TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += user

DEFINES += USE_SDL
LIBS += -lglut -lgsl -l3ds -lGLU -lGL -lm -lSDL -lSDL_image

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/Vetor3D.h \
    bib/cenario.h \
    bib/corrgb.h \
    bib/model3ds.h \
    mybib/spline.h \
    mybib/objeto.h \
    mybib/pontocontrole.h \
    mybib/modelo3ds.h \
    mybib/carro3ds.h \
    mybib/carro.h

SOURCES += \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Vetor3D.cpp \
    main.cpp \
    bib/model3ds.cpp \
    mybib/objeto.cpp \
    mybib/spline.cpp \
    mybib/pontocontrole.cpp \
    mybib/modelo3ds.cpp \
    mybib/carro3ds.cpp

DISTFILES += \
    mybib/Object.py

