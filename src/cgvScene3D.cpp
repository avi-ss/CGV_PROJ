#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"
#include "cgvLight.h"
#include "cgvMaterial.h"
#include "cgvCubie.h"
#include "cgvCube.h"

// Constructor methods -----------------------------------

cgvScene3D::cgvScene3D():cube(new cgvCube(1)) {

	axes = true;
}

cgvScene3D::~cgvScene3D() {}


// Public methods ----------------------------------------

void draw_axes(void) {
	GLfloat red[] = { 1,0,0,1.0 };
	GLfloat green[] = { 0,1,0,1.0 };
	GLfloat blue[] = { 0,0,1,1.0 };

	glBegin(GL_LINES);
	glMaterialfv(GL_FRONT, GL_EMISSION, red);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, green);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, blue);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}


void cgvScene3D::render() {

	// lights
	GLfloat light0[4] = { 5.0,5.0,5.0,1 }; // point light source  
	glLightfv(GL_LIGHT0, GL_POSITION, light0); // this light is placed here and it remains still 
	glEnable(GL_LIGHT0);

	// create the model
	glPushMatrix(); // store the model matrices

	// draw the axes
	if (axes) draw_axes();

	cube->render();

	glPopMatrix(); // restore the modelview matrix 

}


