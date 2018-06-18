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
    bib/model3ds.h \
    mybib/objeto.h \
    mybib/casa.h \
    mybib/arvoremodel.h \
    mybib/modelo3ds.h \
    mybib/arvore.h \
    mybib/caixa.h \
    mybib/muro.h \
    mybib/grama.h \
    mybib/banco.h \
    mybib/solo.h \
    mybib/helpers.h \
    mybib/prediomodel.h \
    gui_glut/gui.h \
    gui_glut/extra.h

SOURCES += \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Vetor3D.cpp \
    main.cpp \
    bib/model3ds.cpp \
    mybib/objeto.cpp \
    mybib/casa.cpp \
    mybib/arvoremodel.cpp \
    mybib/modelo3ds.cpp \
    mybib/arvore.cpp \
    mybib/caixa.cpp \
    mybib/muro.cpp \
    mybib/grama.cpp \
    mybib/banco.cpp \
    mybib/solo.cpp \
    mybib/helpers.cpp \
    mybib/prediomodel.cpp \
    gui_glut/gui.cpp \
    gui_glut/extra.cpp

DISTFILES += \
    release/Trabalho_I \
    release/3ds/Dragon/blue ultimate Dragon.gif \
    release/3ds/Dragon/m32_UltimateBlueE_A_.png \
    release/3ds/Dragon/m32_UltimateBlueE_B_.png \
    release/3ds/Dragon/UltimateZunge.png \
    release/3ds/Dragon/Dragon.3DS \
    release/3ds/Cgtuts_Wood_Bench_3DS.3DS \
    release/3ds/dog.3ds \
    release/3ds/grass-block.3DS \
    release/3ds/missil.3ds \
    release/3ds/skeleton.3ds \
    release/3ds/Tree.3ds \
    release/3ds/wolf.3ds \
    release/3ds/Dragon/Blue  eyes Ultimate  Dragon.mtl \
    release/teste \
    release/3ds/Dragon/blue ultimate Dragon.gif \
    release/3ds/Dragon/Blue  eyes Ultimate  Dragon.mtl
