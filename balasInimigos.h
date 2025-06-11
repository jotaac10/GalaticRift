#pragma once
#include "systemLibraries.h"

class balasInimigos {
public:
    GLfloat position[2];    
    GLfloat speed = 0.3f;    // Velocidade da bala

    balasInimigos(GLfloat x, GLfloat y, GLfloat s); // Construtor

    void draw();             
    void update();          
    void cabeca();          
    GLfloat* getPosition();  
};
