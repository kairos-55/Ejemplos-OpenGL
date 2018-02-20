//	Program developed by
//	Alex Garcia-Alonso
//	Facultad de Informatica
//	Euskal Herriko Unibertsitatea
//	http://www.sc.ehu.es/ccwgamoa
//
// Libraries required : opengl32.lib glu32.lib glut32.lib
//
// This example shows 
// 1)
// How to avoid image distortion in 2D drawings 
// How a window is defined on the world coordinate system (2D)
// 2)
// basic usage of : glMatrixMode glLoadIdentity 
//					glViewport glOrtho
//					glGetIntegerv
//					glutReshapeFunc( myNewSize )
//						void myNewSize( int w, int h )

#include <GL/glut.h>
#include <stdio.h>

static GLfloat	 LOCAL_Red   = 0.4f;
static GLfloat	 LOCAL_Green = 0.4f;
static GLfloat	 LOCAL_Blue  = 0.4f;

static void Display(void)
{
	GLint	 viewport[4];
	float	 aspect;
	float	 viewportHeight, viewportWidth;

	glClear( GL_COLOR_BUFFER_BIT );

	// define a visualization volume
	// keep LOCAL_aspect ratio of the picture
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	glGetIntegerv( GL_VIEWPORT, viewport );
	viewportHeight = viewport[3];
	viewportWidth  = viewport[2];
	if( viewportHeight == 0 ) viewportHeight = 1;
	if( viewportWidth  == 0 ) viewportWidth  = 1;
	aspect = viewportWidth / viewportHeight;
	glOrtho( 0.0f, 100.0f*aspect, 0.0f, 100.0f, 0.0f, 100.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glColor3f( 0.0f, 0.0f, 0.0f );
	glBegin( GL_POLYGON );
		glVertex3f(  40.0f,  40.0f, 0.0f );
		glVertex3f(  60.0f,  40.0f, 0.0f );
		glVertex3f(  60.0f,  60.0f, 0.0f );
		glVertex3f(  40.0f,  60.0f, 0.0f );
	glEnd();

	glColor3f( LOCAL_Red, LOCAL_Green, LOCAL_Blue );

	glBegin( GL_LINES );
		glVertex3f(  20.0f,  20.0f, 0.0f );
		glVertex3f(  80.0f,  80.0f, 0.0f );
		glVertex3f(  20.0f,  10.0f, 0.0f );
		glVertex3f(  20.0f,  90.0f, 0.0f );
	glEnd( );

	glutSwapBuffers();
}

static void Keyboard (unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'r': 
		if (LOCAL_Red > 0.01f) LOCAL_Red -= 0.1f;
		printf ( "red   : ");
		break;
	case 'R':
		if (LOCAL_Red < 1.0f) LOCAL_Red += 0.1f;
		printf ( "red   : ");
		break;
	case 'b': 
		if (LOCAL_Blue > 0.01f) LOCAL_Blue -= 0.1f;
		printf ( "blue  : ");
		break;
	case 'B':
		if (LOCAL_Blue < 1.0f) LOCAL_Blue += 0.1f;
		printf ( "blue  : ");
		break;
	case 'g': 
		if (LOCAL_Green > 0.01f) LOCAL_Green -= 0.1f;
		printf ( "green : ");
		break;
	case 'G':
		if (LOCAL_Green < 1.0f) LOCAL_Green += 0.1f;
		printf ( "green : ");
		break;
	case 27:  // <ESC>
		exit( 0 );
		break;
	default:
		printf( "%d %c\n", key, key );
	}

	printf ( " (R = %f) (G = %f) (B = %f) \n",LOCAL_Red, LOCAL_Green, LOCAL_Blue );

	glutPostRedisplay( );
}

// This function will be called whenever the size of the window changes
static void Resize( int w, int h )
{
	// use the whole window to place drawings
	glViewport( 0, 0, w, h );
	printf( "Resize %d %d\n", w, h );
}

int main(int argc, char** argv)
{
	printf("This program show a way that \n");
	printf("changes in the window does not change line inclination\n");
	printf("\n");
	printf("You can also change the color of the segments\n");
	printf("use <R><r><G><g><B><b>\n");
	printf("\n");
	printf("Press <ESC> to finish\n");
	glutInit(&argc,argv);

	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize ( 200, 200 );
	glutInitWindowPosition ( 550, 350 );
	glutCreateWindow( "Window to Viewport" );

	glutDisplayFunc( Display );
	glutKeyboardFunc( Keyboard );

	// the size of the window has been changed
	glutReshapeFunc( Resize );

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	glutMainLoop( );

	return 0;   
}
