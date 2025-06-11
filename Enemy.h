#pragma once

#include "systemLibraries.h"


class Enemy
{
private:
	GLfloat position[2]; //position [0] -> x, position[1] -> y
	GLfloat scale;
	GLfloat enemiesSpeed = 0.1f;

	GLvoid body(GLvoid);
	GLvoid leftWing(GLvoid);
	GLvoid rightWing(GLvoid);

public:
	Enemy(GLfloat, GLfloat, GLfloat);

	GLvoid move(GLint);
	GLvoid drawEnemyNivel1(GLvoid);
	GLfloat* getPosition(GLvoid);

	~Enemy();

};

