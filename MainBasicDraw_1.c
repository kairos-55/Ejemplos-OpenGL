//	Program developed by
//	Alex Garcia-Alonso
//	Facultad de Informatica
//	Euskal Herriko Unibertsitatea
//	http://www.sc.ehu.es/ccwgamoa
//
// Libraries required : opengl32.lib glu32.lib glut32.lib
//
// This program draws three segments on the screen
// and one white square
// Note the coordinates used for the vertices of the segments
// and their position on the picture that this program draws
// Run the program and follow the instructions that this program prints
// Then, test what happens if the x or y coordinates in glVertex3f
// are greater than 1.0 or lower than -1.0

// OpenGL functions and (concepts) :
//		Parameters, or-ing parameters
// * gl
//		pure "output", but lacks connection with display
//		glClear			(command)
//		glClearColor	(state)
//		glBegin   glEnd
//		glVertex3f		(geometry)
//		glColor3f		(attribute, state)
//		glFlush, glFinish
//						(command stack & processing, debbuging)
//						(mapping from modelling coordinates to display coordinates)
//						(aspect ratio)
//						(need for a transformation management system)
// * glut
//		window system independent "window" & "input" management
//		glutInitDisplayModeg( GLUT_RGB | GLUT_SINGLE );
//		glutInitWindowSize( WIDTH, HEIGHT );
//		glutInitWindowPosition ( X, Y ); 
//			X,Y : Window´s upper left corner position in screen coordinates
//				  Screen origen is placed at Screen´s Upper Left Corner
//		glutCreateWindow("window title");
//
//		Event handling, similar to 
//				The X Window system, MOTIF, MFF, ...
//														(event)
//		void Display(void);								(callback function)
//		glutDisplayFunc( Display );						(binding event & callback)
//		glutMainLoop();									(dispatching events)
//

#include <GL/glut.h>
#include <stdio.h>

static void Display(void)
{
	// draw the background color
	glClear( GL_COLOR_BUFFER_BIT );

	// draw lines
	glColor3f ( 1.0f, 1.0f, 1.0f );  // white
	glBegin( GL_LINE_LOOP );
		glVertex3f( -.95f, -.95f, 0.0f );
		glVertex3f( -.95f, +.95f, 0.0f );
		glVertex3f( +.95f, +.95f, 0.0f );
		glVertex3f( +.95f, -.95f, 0.0f );
	glEnd();

	glBegin( GL_LINES );
		glColor3f ( 0.0f, 1.0f, 0.0f );  // green
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 0.4f, 0.0f );  // vertical segment
	
		glColor3f ( 1.0f, 0.0f, 0.0f );  // red
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.8f, 0.0f, 0.0f );  // horizontal segment

		glColor3f ( 1.0f, 1.0f, 0.0f );  // yellow
		glVertex3f( 0.2f, 0.2f, 0.0f );
		glVertex3f( 0.6f, 0.6f, 0.0f );  // oblique segment
	glEnd();

	// commands the process of all the graphic actions issued up to now
	// but do not waits for their completion
	// glFinish(); makes the same request but does not return
	// untill all the graphic actions have been completed
	glFlush();
}

int main(int argc, char** argv)
{
	printf("NOTES :\n");
	printf(" * Increase and decrease the vertical size of the graphic window\n");
	printf("   >> watch how the slope of the oblique segment changes\n");
	printf(" * Change freely the aspect ratio of the window\n");
	printf("   >> watch how the picture's aspect ratio changes\n");
	printf(" \n");
	printf("Exit procedure: \n");
	printf(" kill the graphic window\n");
	printf(" then, set the focus on this window and press any key\n");
	printf(" \n");

	// define parameters that will be used to create windows
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_RGB | GLUT_SINGLE );
	glutInitWindowSize ( 200, 200 );
	glutInitWindowPosition ( 550, 350 );

	// create one window for OpenGL graphics
	glutCreateWindow("BasicDraw");

	// associate one function to one event
	//   whenever the graphic window must be drawn again
	//   Display is called
	//		Its name can be changed : Display, Draw, Paint, Picture, ...
	//		However the function declaration must be as glutDisplayFunc expects
	//			void Display(void)
	glutDisplayFunc( Display );

	// set OpenGL state values
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	// main loop
	glutMainLoop();

	return 0;   
}
