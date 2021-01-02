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


class cgvCubie
{
private:

	float angle = 90.0f;

	float length;
	cgvPoint3D position;
	cgvPoint3D angleAxis;

public:

	cgvCubie() {
		position = cgvPoint3D();
		angleAxis = cgvPoint3D(0, 0, 0);
	}

	cgvCubie(float x, float y, float z, float len) {

		position = cgvPoint3D(x, y, z);
		length = len;
		angleAxis = cgvPoint3D(0, 0, 0);
	}

	void rotateX(int dir) {
		angleAxis = cgvPoint3D(dir, 0, 0);
	}

	void rotateY(int dir) {
		angleAxis = cgvPoint3D(0, dir, 0);
	}

	void rotateZ(int dir) {
		angleAxis = cgvPoint3D(0, 0, dir);
	}

	void update(int x, int y, int z) {
		position[X] = x;
		position[Y] = y;
		position[Z] = z;
	}

	bool anyRotation() {
		return (angleAxis[X] != 0.0f || angleAxis[Y] != 0.0f || angleAxis[Z] != 0.0f);
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

		if (anyRotation()) {
			std::cout << "holaa" << std::endl;
			glRotatef(angle, angleAxis[X], angleAxis[Y], angleAxis[Z]); 
		}

		glTranslatef(position[X], position[Y], position[Z]);

		// Front-face Quad
		glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT, GL_EMISSION, green);
		glNormal3f(0, 0, 1);
		glVertex3f(-r, -r, -r);
		glVertex3f(r, -r, -r);
		glVertex3f(r, r, -r);
		glVertex3f(-r, r, -r);

		// Back-face Quad
		glNormal3f(0, 0, -1);
		glMaterialfv(GL_FRONT, GL_EMISSION, blue);
		glVertex3f(r, r, r);
		glVertex3f(r, -r, r);
		glVertex3f(-r, -r, r);
		glVertex3f(-r, r, r);

		// Right-face Quad
		glNormal3f(1, 0, 0);
		glMaterialfv(GL_FRONT, GL_EMISSION, red);
		glVertex3f(r, r, r);
		glVertex3f(r, -r, r);
		glVertex3f(r, -r, -r);
		glVertex3f(r, r, -r);

		// Left-face Quad
		glNormal3f(-1, 0, 0);
		glMaterialfv(GL_FRONT, GL_EMISSION, orange);
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

