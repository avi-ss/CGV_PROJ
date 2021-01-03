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
	cgvCubie* cube[1];

public:

	cgvCube(float lenght) {

		int index = 0;

		/*for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					cube[index] = new cgvCubie(i, j, k, lenght);
					index++;
				}
			}
		}*/

		cube[index] = new cgvCubie(1, 1, 1, lenght);
	}

	void rotateX(int layer, int dir) {
		std::cout << "ROTATE X-------------------------------------------" << std::endl;
		for (int i = 0; i < 1; i++) {
			if (cube[i] != nullptr) {
				cgvMatrix2D matrix = cgvMatrix2D();

				int x = cube[i]->getX();
				int y = cube[i]->getY();
				int z = cube[i]->getZ();

				if (x == layer) {

					std::cout << "cubie: " << x << y << z << std::endl;

					matrix.rotate(dir * 90);
					matrix.translate(y, z);

					int newY = matrix.getX(); int newZ = matrix.getY();

					std::cout << "new cubie: " << x << newY << newZ << std::endl;

					cube[i]->update(x, newY, newZ);
					cube[i]->rotate('x', dir);
				}
			}
		}
	}

	void rotateY(int layer, int dir) {
		std::cout << "ROTATE Y-------------------------------------------" << std::endl;
		for (int i = 0; i < 1; i++) {
			if (cube[i] != nullptr) {
				cgvMatrix2D matrix = cgvMatrix2D();

				int x = cube[i]->getX();
				int y = cube[i]->getY();
				int z = cube[i]->getZ();

				if (y == layer) {

					std::cout << "cubie: " << x << y << z << std::endl;

					matrix.rotate(-dir * 90);
					matrix.translate(x, z);

					int newX = matrix.getX(); int newZ = matrix.getY();

					std::cout << "new cubie: " << newX << y << newZ << std::endl;

					cube[i]->update(newX, y, newZ);
					cube[i]->rotate('y', dir);
				}
			}
		}
	}

	void rotateZ(int layer, int dir) {
		std::cout << "ROTATE Z-------------------------------------------" << std::endl;
		for (int i = 0; i < 1; i++) {
			if (cube[i] != nullptr) {
				cgvMatrix2D matrix = cgvMatrix2D();

				int x = cube[i]->getX();
				int y = cube[i]->getY();
				int z = cube[i]->getZ();

				if (z == layer) {

					std::cout << "cubie: " << x << y << z << std::endl;

					matrix.rotate(dir * 90);
					matrix.translate(x, y);

					int newX = matrix.getX(); int newY = matrix.getY();

					std::cout << "new cubie: " << newX << newY << z << std::endl;

					cube[i]->update(newX, newY, z);
					cube[i]->rotate('z', dir);
				}
			}
		}
	}

	void render() {

		glPushMatrix();

		for (int i = 0; i < 1; i++) {
			if (cube[i] != nullptr) {
				cube[i]->render();
			}
		}

		glPopMatrix();
	}
};


