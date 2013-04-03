#include <stdlib.h>
#include "glew.h"
#include "glut.h"
#include <iostream>
using namespace std;
	
	
	void main(int argc, char **argv) {
		glutInit(&argc, argv);	
		glewInit();
		if (glewIsSupported("GL_VERSION_2_0"))
			cout<<"Ready for OpenGL 2.0";
		else {
			cout<<"OpenGL 2.0 not supported";
			exit(1);
		}
	
		//setShaders();
	
		glutMainLoop();
	}

	
