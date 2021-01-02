#pragma once
#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include "cgvPoint3D.h"
#include "cgvCubie.h"
#include "cgvMatrix2D.h"

const int DIM = 3;

class cgvCube
{
	cgvCubie cube[DIM][DIM][DIM];

public:

	cgvCube(float lenght) {

		float offset = lenght;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {

					float x = lenght * i - offset;
					float y = lenght * j - offset;
					float z = lenght * k - offset;

					cube[i][j][k] = cgvCubie(x, y, z, lenght);
				}
			}
		}
	}

	void rotateZ(int dir) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cgvMatrix2D matrix = cgvMatrix2D();

				int x = cube[i][j][dir].getX();
				int y = cube[i][j][dir].getY();
				int z = cube[i][j][dir].getZ();

				matrix.rotate(dir * 90);
				matrix.translate(x, y);

				int newX = matrix.getX(); int newY = matrix.getY();

				cube[i][j][dir].update(newX, newY, z);
				cube[i][j][dir].rotateZ(dir);

				std::cout << "first: " << x << ", " << y << ", second: " << newX << ", "<< newY<< std::endl;
			}
		}
	}

	void render() {

		glPushMatrix();

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					cube[i][j][k].render();
				}
			}
		}

		glPopMatrix();
	}
};


