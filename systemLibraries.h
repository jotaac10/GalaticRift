#pragma once

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#if defined(_WIN32) || defined (_WIN64)
#include <GL/freeglut.h>
#elif defined (__APPLE_) || defined (__MACH__) || defined (TARGET_OS_MAC)
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

//Declare project wide variables and data structures
extern GLfloat worldCoords[4];
extern GLfloat shipHalfSize[2];
extern GLfloat enemyHalfSize[2];
extern GLfloat enemyHalfSize2[2];
extern GLfloat enemyHalfSize3[2];
extern GLfloat enemiesSpeed;