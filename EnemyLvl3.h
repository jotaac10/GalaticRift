#pragma once

#include "systemLibraries.h"


class EnemyLvl3
{
private:
	GLfloat position[2]; //position [0] -> x, position[1] -> y
	GLfloat speed = 0.4f;
	GLfloat scale;
	GLfloat enemiesSpeed = 0.2f;

	GLvoid bodyEnemy3(GLvoid);
	GLvoid triangleWingEnemy3(GLvoid);
	GLvoid wingsEnemy3(GLvoid);
	GLvoid bodyWing3(GLvoid);


public:
	EnemyLvl3(GLfloat, GLfloat, GLfloat);

	GLvoid move(GLint);
	GLvoid drawEnemyNivel3(GLvoid);
	GLfloat* getPosition(GLvoid);

	~EnemyLvl3();

};

