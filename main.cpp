// std
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include "LoadShaders.h"
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Hello My App" << endl;
	glutInit(&argc, argv);
	glutCreateWindow("Glew Test");
	GLenum err = glewInit();
	
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n");
	glewGetString(GLEW_VERSION);
	
	return 0;
}