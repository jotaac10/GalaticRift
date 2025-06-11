#include "EnemyLvl3.h"

EnemyLvl3::EnemyLvl3(GLfloat xPos, GLfloat yPos, GLfloat scl) {
	position[0] = xPos;
	position[1] = yPos;

	if (scl < 0.1f || scl > 3.0f)
		scale = 1.0f;
	else
		scale = scl;

	enemyHalfSize3[0] = scale * 3.0f;
	enemyHalfSize3[1] = scale * 1.25f;
}

//bodyEnemy2 GRAPHIC ELEMENT
GLvoid EnemyLvl3::bodyEnemy3(GLvoid) {
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 2.0f);
		glVertex2f(2.0f, 2.0f);
		glVertex2f(2.0f, 0.0f);
	} glEnd();
}

//bodyEnemy2 GRAPHIC ELEMENT
GLvoid EnemyLvl3::bodyWing3(GLvoid) {
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, 0.0f);
	} glEnd();
}

GLvoid EnemyLvl3::triangleWingEnemy3(GLvoid) {
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES); {
		glVertex2f(0.0f, 1.0f);  // Primeiro vértice
		glVertex2f(1.0f, 1.0f);  // Segundo vértice
		glVertex2f(0.5f, 0.0f);  // Terceiro vértice
	} glEnd();
}

//wingEnemy3 GRAPHIC ELEMENT
GLvoid EnemyLvl3::wingsEnemy3(GLvoid) {
	glColor3f(1.0f, 0.5f, 0.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.25f);
		glVertex2f(0.0f, 0.75f);
		glVertex2f(1.0f, 0.75f);
		glVertex2f(1.0f, 0.25f);
	} glEnd();

}

GLvoid EnemyLvl3::drawEnemyNivel3(GLvoid) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(position[0], position[1], 0.0f);
	glScalef(scale, scale, 0.0f);

	glTranslatef(-1.0f, -0.75f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	bodyEnemy3();

	//leftSide
	glTranslatef(-1.0f, 0.50f, 0.0f);
	wingsEnemy3();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(-2.0f, 0.50f, 0.0f);
	bodyWing3();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glTranslatef(-2.0f, -0.50f, 0.0f);
	triangleWingEnemy3();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	//rightSide
	glTranslatef(2.0f, 0.50f, 0.0f);
	wingsEnemy3();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(3.0f, 0.50f, 0.0f);
	bodyWing3();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(3.0f, -0.5f, 0.0f);
	triangleWingEnemy3();
	glMatrixMode(GL_MODELVIEW);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}


//move the ship to a new position based on current position, direction and speed
GLvoid EnemyLvl3::move(GLint direction) {
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

GLfloat* EnemyLvl3::getPosition(GLvoid) {
	return position;
}

EnemyLvl3::~EnemyLvl3() {
	bodyEnemy3();
}