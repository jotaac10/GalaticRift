#include "Ship.h"

//CONSTRUCTOR, RECEIVES INITIAL OBJECT POSITION
Ship::Ship(GLfloat xPos, GLfloat yPos, GLfloat scl) {
	position[0] = xPos;
	position[1] = yPos;

	if (scl < 0.1f || scl > 3.0f)
		scale = 1.0f;
	else
		scale = scl;

	shipHalfSize[0] = scale * 3.0f;
	shipHalfSize[1] = scale * 3.0f;
}

//BODY GRAPHIC ELEMENT
GLvoid Ship::body(GLvoid) {
	glColor3f(0.0f, 0.0f, 1.0f); // cor azul

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.0f);  // canto inferior esquerdo
		glVertex2f(0.0f, 4.0f);  // canto superior esquerdo
		glVertex2f(2.0f, 4.0f);  // canto superior direito
		glVertex2f(2.0f, 0.0f);  // canto inferior direito
	} glEnd();
}

//COCKPIT GRAPHIC ELEMENT
GLvoid Ship::cockpit(GLvoid) {
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.0f, 2.0f);
		glVertex2f(2.0f, 0.0f);
	}glEnd();
}

//leftWING GRAPHIC ELEMENT
GLvoid Ship::leftWing(GLvoid) {
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(2.0f, 3.0f);
		glVertex2f(2.0f, 1.0f);
	}glEnd();
}

//rightWING GRAPHIC ELEMENT
GLvoid Ship::rightWing(GLvoid) {
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES); {
		glVertex2f(0.0f, 1.0f);
		glVertex2f(0.0f, 3.0f);
		glVertex2f(2.0f, 0.0f);
	}glEnd();
}
//CANNON GRAPHIC ELEMENT
GLvoid Ship::cannon(GLvoid) {
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS); {
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.3f, 0.0f);
		glVertex2f(0.3f, 1.0f);
		glVertex2f(0.0f, 1.0f);
	}glEnd();
}

GLvoid Ship::draw(GLvoid) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(position[0], position[1], 0.0f);
	glScalef(scale, scale, 0.0f);
	glTranslatef(-1.0f, -3.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	body();

	glTranslatef(0.0f, 4.0f, 0.0f);
	cockpit();

	//leftCannon
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-1.0f, 1.2f, 0.0f);
	cannon();

	//rightCannon
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(2.75f, 1.2f, 0.0f);
	cannon();

	//leftWing
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, 0.0f);
	leftWing();

	//rightWing
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, 0.0f);
	rightWing(); 
	

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopMatrix();

}

//move the ship to a new position based on current position, direction and speed
GLboolean Ship::move(GLint direction) {
	GLboolean canMove = false;
	switch (direction) {
	case 0: // right
		if ((position[0] + 2.5f * scale + speed) < worldCoords[1]) {
			position[0] += speed;
			canMove = true;
		}
		break;
	case 1: //down
		if ((position[1] - 2.5f * scale - speed) > worldCoords[2]) {
			position[1] -= speed;
			canMove = true;
		}
		break;
	case 2:	//left
		if ((position[0] - 2.5f * scale - speed) > worldCoords[0]) {
			position[0] -= speed;
			canMove = true;
		}
		break;
	case 3:	//up
		if ((position[1] + 2.5f * scale + speed) < worldCoords[3]) {
			position[1] += speed;
			canMove = true;
		}
		break;
	}
	//cout << position[0] << "," << position[1] << endl;
	return canMove;
}

GLfloat* Ship::getPosition(GLvoid) {
	return position;
}

Ship::~Ship() {
	body();
}