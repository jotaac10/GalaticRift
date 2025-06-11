#include "EnemyLvl2.h"

EnemyLvl2::EnemyLvl2(GLfloat xPos, GLfloat yPos, GLfloat scl) {
	position[0] = xPos;
	position[1] = yPos;

	if (scl < 0.1f || scl > 3.0f)
		scale = 1.0f;
	else
		scale = scl;

	enemyHalfSize2[0] = scale * 4.0f;
	enemyHalfSize2[1] = scale * 2.0f;
}

//bodyEnemy2 GRAPHIC ELEMENT
GLvoid EnemyLvl2::bodyEnemy2(GLvoid) {
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.0f, 1.5f);
		glVertex2f(4.0f, 1.5f);
		glVertex2f(4.0f, 0.5f);
	} glEnd();
}

GLvoid EnemyLvl2::triangleWingEnemy2(GLvoid) {
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES); {
		glVertex2f(1.0f, 0.0f);  // Primeiro vértice
		glVertex2f(0.0f, 2.0f);  // Segundo vértice
		glVertex2f(2.0f, 2.0f);  // Terceiro vértice
	} glEnd();
}

//wingEnemy2 GRAPHIC ELEMENT
GLvoid EnemyLvl2::wingsEnemy2(GLvoid) {
	glColor3f(1.0f, 0.5f, 0.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 2.0f);
		glVertex2f(2.0f, 2.0f);
		glVertex2f(2.0f, 0.0f);
	} glEnd();

}


GLvoid EnemyLvl2::drawEnemyNivel2(GLvoid) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(position[0], position[1], 0.0f);
	glScalef(scale, scale, 0.0f);

	glTranslatef(-2.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	bodyEnemy2();

	//leftBody
	glTranslatef(-2.0f, 0.0f, 0.0f);
	wingsEnemy2();

	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//rightBody
	glTranslatef(4.0f, 0.0f, 0.0f);
	wingsEnemy2();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//rightWingTriangle
	glTranslatef(4.0f, -2.0f, 0.0f);
	triangleWingEnemy2();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//leftWingTriangle
	glTranslatef(-2.0f, -2.0f, 0.0f);
	triangleWingEnemy2();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


//move the ship to a new position based on current position, direction and speed
GLvoid EnemyLvl2::move(GLint direction) {
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

GLfloat* EnemyLvl2::getPosition(GLvoid) {
	return position;
}

EnemyLvl2::~EnemyLvl2() {
	bodyEnemy2();
}
