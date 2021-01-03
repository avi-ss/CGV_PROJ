#pragma once

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include "cgvPoint3D.h"
#include "cgvColor.h"
#include <iostream>
#include <vector>

struct Rotation {

	char axis;
	int dir;

};

class cgvCubie
{

private:

	float angle = 90.0f;

	float length;
	cgvPoint3D position;
	std::vector<Rotation> rotations;

public:

	cgvCubie() {
		position = cgvPoint3D();
	}

	cgvCubie(float x, float y, float z, float len) {
		position[X] = x;
		position[Y] = y;
		position[Z] = z;
		length = len;
	}

	void rotate(char axis, int dir) {
		Rotation rot = { axis, dir };
		rotations.push_back(rot);
	}

	void update(int x, int y, int z) {
		position[X] = x;
		position[Y] = y;
		position[Z] = z;
	}

	void render() {

		GLfloat red[] = { 1,0,0,1.0 };
		GLfloat green[] = { 0,1,0,1.0 };
		GLfloat blue[] = { 0,0,1,1.0 };
		GLfloat white[] = { 1,1,1,1.0 };
		GLfloat orange[] = { 1,0.65,0,1.0 };
		GLfloat yellow[] = { 1,1,0,1.0 };

		float r = length / 2;

		glPushMatrix();
		glTranslatef(position[X], position[Y], position[Z]);
		if (!rotations.empty()) { 
			for (Rotation r : rotations) {
				switch (r.axis)
				{
				case 'x':
					glRotatef(angle, r.dir, 0, 0);
					break;
				case 'y':
					glRotatef(angle, 0, r.dir, 0);
					break;
				case 'z':
					glRotatef(angle, 0, 0, r.dir);
					break;
				default:
					break;
				}
			}
		}

		// Front-face Quad
		glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT, GL_EMISSION, orange);
		glNormal3f(0, 0, 1);
		glVertex3f(-r, -r, -r);
		glVertex3f(r, -r, -r);
		glVertex3f(r, r, -r);
		glVertex3f(-r, r, -r);

		// Back-face Quad
		glNormal3f(0, 0, -1);
		glMaterialfv(GL_FRONT, GL_EMISSION, red);
		glVertex3f(r, r, r);
		glVertex3f(r, -r, r);
		glVertex3f(-r, -r, r);
		glVertex3f(-r, r, r);

		// Right-face Quad
		glNormal3f(1, 0, 0);
		glMaterialfv(GL_FRONT, GL_EMISSION, blue);
		glVertex3f(r, r, r);
		glVertex3f(r, -r, r);
		glVertex3f(r, -r, -r);
		glVertex3f(r, r, -r);

		// Left-face Quad
		glNormal3f(-1, 0, 0);
		glMaterialfv(GL_FRONT, GL_EMISSION, green);
		glVertex3f(-r, r, r);
		glVertex3f(-r, -r, r);
		glVertex3f(-r, -r, -r);
		glVertex3f(-r, r, -r);

		// Top-face Quad
		glNormal3f(0, 1, 0);
		glMaterialfv(GL_FRONT, GL_EMISSION, white);
		glVertex3f(r, r, r);
		glVertex3f(r, r, -r);
		glVertex3f(-r, r, -r);
		glVertex3f(-r, r, r);

		// Bottom-face Quad
		glNormal3f(0, -1, 0);
		glMaterialfv(GL_FRONT, GL_EMISSION, yellow);
		glVertex3f(r, -r, r);
		glVertex3f(r, -r, -r);
		glVertex3f(-r, -r, -r);
		glVertex3f(-r, -r, r);

		glEnd();

		glPopMatrix();

	}

	int getX() { return position[X]; }
	int getY() { return position[Y]; }
	int getZ() { return position[Z]; }
};

