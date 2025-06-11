#pragma once

#include "systemLibraries.h"


class EnemyLvl2
{
private:
	GLfloat position[2]; //position [0] -> x, position[1] -> y
	GLfloat speed = 0.4f;
	GLfloat scale;
	GLfloat enemiesSpeed = 0.2f;

	GLvoid bodyEnemy2(GLvoid);
	GLvoid triangleWingEnemy2(GLvoid);
	GLvoid wingsEnemy2(GLvoid);


public:
	EnemyLvl2(GLfloat, GLfloat, GLfloat);

	GLvoid move(GLint);
	GLvoid drawEnemyNivel2(GLvoid);
	GLfloat* getPosition(GLvoid);

	~EnemyLvl2();

};

