#include "Enemy.h"

//CONSTRUCTOR, RECEIVES INITIAL OBJECT POSITION
Enemy::Enemy(GLfloat xPos, GLfloat yPos, GLfloat scl) {
	position[0] = xPos;
	position[1] = yPos;

	if (scl < 0.1f || scl > 3.0f)
		scale = 1.0f;
	else
		scale = scl;

	enemyHalfSize[0] = scale * 5.0f;
	enemyHalfSize[1] = scale * 1.0f;
}

//BODY GRAPHIC ELEMENT
GLvoid Enemy::body(GLvoid) {
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.0f); 
		glVertex2f(0.0f, 2.0f); 
		glVertex2f(2.0f, 2.0f); 
		glVertex2f(2.0f, 0.0f); 
	} glEnd();

}

//leftWING GRAPHIC ELEMENT
GLvoid Enemy::leftWing(GLvoid) {
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.0f, 1.5f);
		glVertex2f(4.0f, 1.5f);
		glVertex2f(4.0f, 0.5f);
	} glEnd();
}

//rightWING GRAPHIC ELEMENT
GLvoid Enemy::rightWing(GLvoid) {
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.0f, 1.5f);
		glVertex2f(4.0f, 1.5f);
		glVertex2f(4.0f, 0.5f);
	} glEnd();
}


GLvoid Enemy::drawEnemyNivel1(GLvoid) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(position[0], position[1], 0.0f);
	glScalef(scale, scale, 0.0f);
	glTranslatef(-1.0f, -1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	body();
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-4.0f, 0.0f, 0.0f);
	leftWing();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, 0.0f);
	rightWing();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

//move the ship to a new position based on current position, direction and speed
GLvoid Enemy::move(GLint direction) {
	switch (direction) {
	case 0:
		position[0] += enemiesSpeed;
		break;
	case 1:
		position[1] -= enemiesSpeed;
		break;
	case 2:
		position[0] -= enemiesSpeed;
		break;
	case 3:
		position[1] += enemiesSpeed;
		break;
	}
}

GLfloat* Enemy::getPosition(GLvoid) {
	return position;
}

Enemy::~Enemy() {
	body();
}
