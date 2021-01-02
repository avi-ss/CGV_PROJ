#include <cstdlib>
#include <stdio.h>

#include "cgvInterface.h"


extern cgvInterface interface; // the callbacks must be static and this object is required to access to the variables of the class                  

// Constructor and destructor methods -----------------------------------

cgvInterface::cgvInterface() :camType(CGV_PARALLEL), currentCam(0) {
	//// TODO: Section D: initialize the attributes to select objects by list of impacts


	camera[0] = cgvCamera(cgvPoint3D(6.0, 4.0, 8), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
	camera[0].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
	// Top view
	camera[1] = cgvCamera(cgvPoint3D(0, 14.0, 0), cgvPoint3D(0, 0, 0), cgvPoint3D(-1, 0, 0));
	camera[1].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);

	// Lateral view
	camera[2] = cgvCamera(cgvPoint3D(14.0, 0, 0), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
	camera[2].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);

	// Front view
	camera[3] = cgvCamera(cgvPoint3D(0, 0, 14.0), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
	camera[3].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
}

cgvInterface::~cgvInterface() {}


// Public methods ----------------------------------------
void cgvInterface::create_world(void) {
	camera[0] = cgvCamera(cgvPoint3D(6.0, 4.0, 8), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
	camera[0].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);

}

void cgvInterface::configure_environment(int argc, char** argv,
	int _width_window, int _height_window,
	int _pos_X, int _pos_Y,
	string _title)
{
	// initialization of the interface variables																	
	width_window = _width_window;
	height_window = _height_window;

	// initialization of the display window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_width_window, _height_window);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_title.c_str());

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
	glClearColor(1.0, 1.0, 1.0, 0.0); // define the background color of the window

	glEnable(GL_LIGHTING); // enable the lighting of the scene
	glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation. 

	create_world(); // create the world (scene) to be rendered in the window
}

void cgvInterface::init_rendering_loop() {
	glutMainLoop(); // initialize the visualization loop of OpenGL
}

void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		////// Section B: include here the change of the camera to show the top, lateral, side and perspective views
	case 'p': // change the type of projection between parallel and perspective. 
		if (interface.camType == CGV_PARALLEL) {
			interface.camera[interface.currentCam].setPerspParameters(60, 1, 0.1, 200);
			interface.camType = CGV_PERSPECTIVE;
		}
		else {
			interface.camera[interface.currentCam].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
			interface.camType = CGV_PARALLEL;
		}
		break;
	case 'v': // change the current camera to show these views: panoramic, top, front and lateral view
		interface.currentCam = (interface.currentCam + 1) % 4;
		break;

	case 'a': // enable/disable the visualization of the axes
		interface.scene.set_axes(interface.scene.get_axes() ? false : true);

		break;
	case 27: // Escape key to exit
		exit(1);
		break;
	}
	glutPostRedisplay(); // renew the content of the window
}

void cgvInterface::set_glutReshapeFunc(int w, int h) {
	// dimension of the viewport with a new width and a new height of the display window 


	// store the new values of the viewport and the display window. 
	interface.set_width_window(w);
	interface.set_height_window(h);

	// Set up the kind of projection to be used
	interface.camera[interface.currentCam].apply();

}

void cgvInterface::set_glutDisplayFunc() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

	// set up the viewport
	glViewport(0, 0, interface.get_width_window(), interface.get_height_window());

	// Apply the camera and projection transformations 
	interface.camera[interface.currentCam].apply();

	// Render the scene
	interface.scene.render();

	// refresh the window
	glutSwapBuffers(); // it is used instead of glFlush(), to avoid flickering

}


//void cgvInterface::set_glutIdleFunc() {
//	///// TODO: Section D: Add the required code to animate your model in a realistic way. 
//	glutPostRedisplay();
//}


void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	// glutIdleFunc(set_glutIdleFunc);
}









