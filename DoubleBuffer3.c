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
// How double buffering enhances animation
// Press <ESC> to exit this application
// 2)
// basic usage of : 
//					glutSwapBuffers()
//
// LOCAL_DoubleBufferFlag controls whether the program will run 
// with or without double buffering
// Run the program twice, each one in a different way

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

static int  	 LOCAL_DoubleBufferFlag;
static double	 LOCAL_angle  = 0.0f;

static void Display(void)
{
	float	 endX, endY;
	float	 angle;

	glClear( GL_COLOR_BUFFER_BIT );

	LOCAL_angle += 0.001;
	glBegin( GL_POLYGON );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		angle = LOCAL_angle;
		endX = cos( angle );
		endY = sin( angle );
		glVertex3f( endX, endY, 0.0f );
		angle = angle + 0.7854f;		// 45.0f * (2*3.1416f / 360.0f)
		endX = cos( angle ) * 1.4142f;	// 2 * sqrt( 2.0 )
		endY = sin( angle ) * 1.4142f;
		glVertex3f( endX, endY, 0.0f );
		angle = angle + 0.7854f;		// 45.0f * (2*3.1416f / 360.0f)
		endX = cos( angle );
		endY = sin( angle );
		glVertex3f( endX, endY, 0.0f );
	glEnd( );

	if( LOCAL_DoubleBufferFlag ) {
		glutSwapBuffers();
	}
	else {
		glFlush();
	}
	glutPostRedisplay( );
}

// This function will be called whenever the user pushes one key
static void Keyboard (unsigned char key, int x, int y)
{
	switch(key)
	{
		break;
	case 27:  // <ESC>
		exit( 0 );
		break;
	default:
		printf( "%d %c\n", key, key );
	}

	glutPostRedisplay( );
}

int main(int argc, char** argv)
{

	printf("This program shows how double buffering enhances animation\n");
	printf("Press <ESC> to finish\n");
	printf("\n");
	printf("Input 1 or 0 (1=Use double buff) (0=no) ");
	scanf("%d", &LOCAL_DoubleBufferFlag );

	glutInit(&argc,argv);

	if( LOCAL_DoubleBufferFlag ) {
		glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
	}
	else {
		glutInitDisplayMode ( GLUT_RGB | GLUT_SINGLE );
	}
	glutInitWindowSize ( 400, 400 );
	glutInitWindowPosition ( 550, 350 );
	glutCreateWindow( "Double Buffer" );

	glutDisplayFunc( Display );
	glutKeyboardFunc( Keyboard );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glColor3f( 1.0f, 0.0f, 0.0f );

	glutMainLoop( );

	return 0;   
}
