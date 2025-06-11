#pragma once

#include "systemLibraries.h"


class Ship
{
private:
	GLfloat position[2]; //position [0] -> x, position[1] -> y
	GLfloat speed = 0.4f;
	GLfloat scale;

	GLvoid cockpit(GLvoid);
	GLvoid body(GLvoid);
	GLvoid leftWing(GLvoid);
	GLvoid rightWing(GLvoid);
	GLvoid cannon(GLvoid);

public:
	Ship(GLfloat, GLfloat, GLfloat);
	GLboolean move(GLint);
	GLvoid draw(GLvoid);
	GLfloat* getPosition(GLvoid);

	~Ship();

};

