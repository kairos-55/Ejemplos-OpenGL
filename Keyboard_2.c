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
// How the program can be controlled using the keyboard 
// pressing the keys 'r' 'g' 'b'
// the color of the line changes
// shift increases, unshifted decreases
// Press <ESC> to exit this application
// 2)
// basic usage of : 
//					glLineWidth( float )
//					glutKeyboardFunc( DoIt )
//						void DoIt (unsigned char key, int x, int y)
//					glutPostRedisplay()

#include <GL/glut.h>
#include <stdio.h>

static GLfloat	 LOCAL_Red   = 0.5f;
static GLfloat	 LOCAL_Green = 0.5f;
static GLfloat	 LOCAL_Blue  = 0.5f;

static void Display(void)
{
	glClear( GL_COLOR_BUFFER_BIT );

	glColor3f( 0.0f, 0.0f, 0.0f );
	glBegin( GL_POLYGON );
		glVertex3f( -0.3f, -0.3f, 0.0f );
		glVertex3f(  0.3f, -0.3f, 0.0f );
		glVertex3f(  0.3f,  0.3f, 0.0f );
		glVertex3f( -0.3f,  0.3f, 0.0f );
	glEnd();
	
	// Set state values that define properties that
	// will be assigned to future primitives
	glColor3f( LOCAL_Red, LOCAL_Green, LOCAL_Blue );
//	glLineWidth( 10.0f );

	glBegin( GL_LINES );
		glVertex3f( -0.8f, -0.8f, 0.0f );
		glVertex3f(  0.8f,  0.8f, 0.0f );
	glEnd();

	glFlush();
}

// This function will be called whenever the user pushes one key
static void Keyboard (unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'r': 
		if ( LOCAL_Red > 0.01f ) LOCAL_Red -= 0.1f;
		printf ("red   : ");
		break;
	case 'R':
		if ( LOCAL_Red < 1.0f ) LOCAL_Red += 0.1f;
		printf ("red   : ");
		break;
	case 'b': 
		if ( LOCAL_Blue > 0.01f ) LOCAL_Blue -= 0.1f;
		printf ("blue  : ");
		break;
	case 'B':
		if ( LOCAL_Blue < 1.0f ) LOCAL_Blue += 0.1f;
		printf ("blue  : ");
		break;
	case 'g': 
		if ( LOCAL_Green > 0.01f ) LOCAL_Green -= 0.1f;
		printf ("green : ");
		break;
	case 'G':
		if ( LOCAL_Green < 1.0f ) LOCAL_Green += 0.1f;
		printf ("green : ");
		break;
	case 27:  // <ESC>
		exit( 0 );
		break;
	default:
		printf("%d %c %d %d\n", key, key, x, y );
	}

	printf ("(R = %f) (G = %f) (B = %f) \n", LOCAL_Red, LOCAL_Green, LOCAL_Blue );

	// The screen must be drawn to show the new values
	glutPostRedisplay();
}

int main(int argc, char** argv)
{

	printf("This program changes the color of the oblique segment\n");
	printf("Press <ESC> to finish\n");
	printf("Press <r> <R> to increase/decrease the red   component\n");
	printf("Press <g> <G> to increase/decrease the green component\n");
	printf("Press <b> <B> to increase/decrease the blue  component\n");

	glutInit(&argc,argv);

	glutInitDisplayMode ( GLUT_RGB );
	glutInitWindowSize ( 200, 200 );
	glutInitWindowPosition ( 550, 350 );
	glutCreateWindow( "Keyboard" );

	glutDisplayFunc( Display );
	glutKeyboardFunc( Keyboard );

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	glutMainLoop();

	return 0;   
}
