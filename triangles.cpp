#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <GL/GL.h>

#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_Ids { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init(void)
{
	// create VAO
	glGenVertexArrays(NumVAOs, VAOs);
	// bind VAO
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
		{ -0.90, -0.90 }, // Triangle 1
		{  0.85, -0.90 },
		{ -0.90,  0.85 },
		{  0.90, -0.85 }, // Triangle 2
		{  0.90,  0.90 },
		{ -0.85,  0.90 },
	};

	// create vertex buffer (just a pointer)
	glGenBuffers(NumBuffers, Buffers);
	// bind vertex buffer (allocate actual data, assign the name, and activate)
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	// set data to vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	// link shader's attribute (vPosition) with data in buffer object
	// a connection between shader and the application
	// so that the data will be processed by opengl
	glVertexAttribPointer(vPosition, // [index] location of a variable input in vertex shader
		2, // [size] size number of values fore each vertex in the array
		GL_FLOAT,  // [type]
		GL_FALSE, // [Normalised] should data be constrained to normailze device coord
		0, // [stride] gap between the same data
		((const void*)(0))
		); // [Start Address]

	// enable shader's attribute for position
	glEnableVertexAttribArray(vPosition);
}

// display
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// switch to this vertex data
	glBindVertexArray(VAOs[Triangles]);
	// send vertex data to OpenGL pipeline, which would construct primitive (GL_Triangle)
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	// flush any pending opengl call to opengl pipeline for processing
	glFlush();
}

// main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	if (glewInit())
	{
		cerr << "Unable to initialise GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}