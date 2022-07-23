QT += widgets opengl openglwidgets gui

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    axes.cpp \
    glrenderer.cpp \
    gridlines.cpp \
    main.cpp \
    mainwindow.cpp \
    transforms.cpp

HEADERS += \
    CS1230Lib/shaderloader.h \
    axes.h \
    glrenderer.h \
    gridlines.h \
    mainwindow.h \
    transforms.h


# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += glm
DEPENDPATH += glm

DISTFILES += \
    Resources/Shaders/arrow.frag \
    Resources/Shaders/arrow.vert \
    Resources/Shaders/axes.frag \
    Resources/Shaders/axes.vert \
    Resources/Shaders/grid.frag \
    Resources/Shaders/grid.vert
