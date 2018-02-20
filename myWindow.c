#include <GL/glut.h>
#include <stdio.h>

	static float x1 = -0.05;
	static float x2 = -0.05;
	static float y1 = -0.05;
	static float y4 = -0.05;
	static float x3 = 0.05;
	static float x4 = 0.05;
	static float y2 = 0.05;
	static float y3 = 0.05;
	static int dir = 2;

static void move(){
	if(dir == 0){
		x1 += 0.001;
	    x2 += 0.001;
	    x3 += 0.001;
	    x4 += 0.001;
	}else if(dir == 1){
		y1 += 0.001;
	    y2 += 0.001;
	    y3 += 0.001;
	    y4 += 0.001;
	}else if(dir == 2){
		x1 -= 0.001;
	    x2 -= 0.001;
	    x3 -= 0.001;
	    x4 -= 0.001;
	}else if(dir == 3){
		y1 -= 0.001;
	    y2 -= 0.001;
	    y3 -= 0.001;
	    y4 -= 0.001;
	}
}	

static void Display(void)
{


	glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();
    glFlush();
	move();
  	glutPostRedisplay( );

}

static void Keyboard (unsigned char key, int x, int y)
{
	switch(key)
	{
		break;
	case 27:  // <ESC>
		exit( 0 );
		break;
	case 'a':
		dir = 2;
		break;
	case 's':
		dir = 3;
		break;
	case 'd':
		dir = 0;
		break;
	case 'w':
		dir = 1;
		break;

	default:
		printf( "%d %c\n", key, key );
	}

	glutPostRedisplay( );
}

int main(int argc, char** argv)
{
	printf("This program show something \n");
	printf("Press <ESC> to finish\n");
	glutInit(&argc,argv);

	glutInitDisplayMode ( GLUT_SINGLE );
	glutInitWindowSize ( 400, 400 );
	glutInitWindowPosition ( 550, 350 );
	glutCreateWindow( "My window" );

	glutDisplayFunc( Display );
	glutKeyboardFunc( Keyboard );


	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	glutMainLoop( );

	return 0;   
}




