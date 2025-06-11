#include "balasInimigos.h"
#include "balas.h"

balasInimigos::balasInimigos(GLfloat x, GLfloat y, GLfloat s) {
    position[0] = x;
    position[1] = y;
    speed = s;
}

void balasInimigos::update() {
    position[1] -= speed; 
}


GLvoid balasInimigos::cabeca(GLvoid) {
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.075f, 0.05f);
    glVertex2f(0.5f, 0.0f);
    glEnd();
}

GLvoid balasInimigos::draw(GLvoid) {
    glPushMatrix();
    glTranslatef(position[0], position[1], 0.0f); // Posiciona a bala
    glScalef(1.0f, 1.0f, 1.0f);

    cabeca();

    glPopMatrix();
}

GLfloat* balasInimigos::getPosition(GLvoid) {
    return position;
}