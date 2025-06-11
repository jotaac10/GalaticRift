#pragma once
#include "systemLibraries.h"
class balas {
public:
    GLfloat position[2];
    //GLfloat scale = 1.0f;
    GLfloat speed = 0.3f;
    balas(GLfloat x, GLfloat y, GLfloat s);
    void draw();
    void update();
    void body();
    void cabeca();
    GLfloat* getPosition(GLvoid);
};
