#include "balas.h"

void balas::update() {
    position[1] += speed;
    std::cout << "Bala Y: " << position[1] << std::endl;
}
GLvoid balas::body(GLvoid) {
    glColor3f(0.5f, 0.5f, 0.5f); // Cinzento

    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.15f, 0.5f);
    glVertex2f(0.15f, 0.0f);
    glEnd();
}

GLvoid balas::cabeca(GLvoid) {
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.075f, 0.05f);
    glVertex2f(0.15f, 0.0f);
    glEnd();
}
GLfloat* balas::getPosition(GLvoid) {
    return position;
}
balas::balas(GLfloat x, GLfloat y, GLfloat s) {
    position[0] = x;
    position[1] = y;
    speed = s;
}

GLvoid balas::draw(GLvoid) {
    glPushMatrix();
    glTranslatef(position[0], position[1], 0.0f); 
    glScalef(1, 1, 0.0f);

    body();

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);  
    cabeca();
    glPopMatrix();

    glPopMatrix();
}
