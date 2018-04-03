/* 
 * File:   segunda_tortuga.cpp
 * Author: Camilo José Cruz Rivera 1428907
 * Author: Erik López Pacheco 1430406
 * Author: Jesús Alberto Ramírez Otálvaro 1422554
 *
 * Created on 26 de Marzo de 2018, 19:05
 */
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "camera.h"
#include "vector_tools.h"

static camera *LOCAL_MyCamera;
static int old_x, old_y;
static int current_mode = 0;

bool command = false; /* command mode */
char strCommand[256];

void Pan(int x, int y){
	float avance_x, avance_y;
	avance_x = (float)(old_x - x) / 10;
	avance_y = (float)(y - old_y) / 10;
	PanCamera( LOCAL_MyCamera, avance_x, avance_y);
	old_y = y;
	old_x = x;
	glutPostRedisplay();
}

void Tripode(int x, int y){
	float rotacion_x, rotacion_y;
	rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
	rotacion_y = (float)(old_y - y) * DEGREE_TO_RAD / 5;
	YawCamera( LOCAL_MyCamera, rotacion_x );
	PitchCamera( LOCAL_MyCamera, rotacion_y );
	old_y = y;
	old_x = x;
	glutPostRedisplay();
}

void Zoom(int x, int y){
	float zoom;
	zoom = (float) ((y - old_y) * DEGREE_TO_RAD);
	old_y = y;
	switch(LOCAL_MyCamera->camMovimiento){
		case CAM_EXAMINAR:
		if (LOCAL_MyCamera->camAperture + zoom > (5 * DEGREE_TO_RAD) &&
			LOCAL_MyCamera->camAperture + zoom < 175 * DEGREE_TO_RAD)
			LOCAL_MyCamera->camAperture=LOCAL_MyCamera->camAperture + zoom;
		break;
	}
	glutPostRedisplay();
}

void Andar(int x, int y){
	float rotacion_x, avance_y;
	avance_y = (float)(y - old_y) / 10;
	rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
	YawCamera( LOCAL_MyCamera, rotacion_x );
	AvanceFreeCamera( LOCAL_MyCamera, avance_y);
	old_y = y;
	old_x = x;
	glutPostRedisplay();
}

void Examinar(int x, int y){
	float rot_x, rot_y;
	rot_y = (float)(old_y - y);
	rot_x = (float)(x - old_x);
	Rotar_Latitud( LOCAL_MyCamera, rot_y * DEGREE_TO_RAD );
	Rotar_Longitud( LOCAL_MyCamera, rot_x * DEGREE_TO_RAD );
	old_y = y;
	old_x = x;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	old_x = x;
	old_y = y;
	switch(button){
		case GLUT_LEFT_BUTTON:
		switch(LOCAL_MyCamera->camMovimiento){
			case CAM_EXAMINAR:
			if (state == GLUT_DOWN) glutMotionFunc(Zoom);
			if (state == GLUT_UP){
				glutPassiveMotionFunc(Examinar);
				glutMotionFunc(NULL);
			}
			break;
			case CAM_PASEAR:
			if (state == GLUT_DOWN) glutMotionFunc(Andar);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;
			case CAM_TRIPODE:
			if (state == GLUT_DOWN) glutMotionFunc(Tripode);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;
			case CAM_PAN:
			if (state == GLUT_DOWN) glutMotionFunc(Pan);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;
		}
		break;
		case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) ;
		break;
		default:
		break;
	}

	glutPostRedisplay();

}

void MouseMotion(int x, int y){
	old_y = y;
	old_x = x;
}

static void SpecialKey ( int key, int x, int y ){
	switch(key) {
		case GLUT_KEY_F1:
		glutPassiveMotionFunc(MouseMotion);
		LOCAL_MyCamera->camMovimiento = CAM_STOP;
		break;
		case GLUT_KEY_F2:
		glutPassiveMotionFunc(Examinar);
		LOCAL_MyCamera->camMovimiento = CAM_EXAMINAR;
		break;
		case GLUT_KEY_F3:
		glutPassiveMotionFunc(MouseMotion);
		LOCAL_MyCamera->camMovimiento = CAM_PASEAR;
		LOCAL_MyCamera->camAtY = 0;
		LOCAL_MyCamera->camViewY = 0;
		SetDependentParametersCamera( LOCAL_MyCamera );
		break;
		case GLUT_KEY_F4:
		if(LOCAL_MyCamera->camProjection == CAM_CONIC){
		LOCAL_MyCamera->x1=-3;
		LOCAL_MyCamera->x2=3;
		LOCAL_MyCamera->y1=-3;
		LOCAL_MyCamera->y2=3;
		LOCAL_MyCamera->z1=-5;
		LOCAL_MyCamera->z2=5;
		LOCAL_MyCamera->camProjection = CAM_PARALLEL;
		} else LOCAL_MyCamera->camProjection = CAM_CONIC;
		break;
		case GLUT_KEY_F5:		
		LOCAL_MyCamera->camMovimiento = CAM_TRIPODE;
		break;
		case GLUT_KEY_F6:		
		LOCAL_MyCamera->camMovimiento = CAM_PAN;
		break;
		case GLUT_KEY_HOME: //Reset Camera
		LOCAL_MyCamera->camAtX =0;
		LOCAL_MyCamera->camAtY =0;
		LOCAL_MyCamera->camAtZ =0;
		LOCAL_MyCamera->camViewX = 0;
		LOCAL_MyCamera->camViewY = 1;
		LOCAL_MyCamera->camViewZ = -3;
		SetDependentParametersCamera( LOCAL_MyCamera );
		break;
		default:
		printf("key %d %c X %d Y %d\n", key, key, x, y );
	}

	glutPostRedisplay();

}

void drawSphereTurtle() {

    int slices = 40;
    int stacks = 40;

    glPushMatrix();
    glScalef(1.0f, .3f, 1.0f);
    glutSolidSphere(1.0, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.7f, 0.0f, .7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.7f, 0.0f, .7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.7f, 0.0f, -.7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.7f, 0.0f, -.7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0f, .6f, 1.0f);
    glTranslatef(0.0f, 0.0f, -1.2f);
    glutSolidSphere(.4, slices, stacks);
    glPopMatrix();
}

void display(void) {
	SetGLCamera( LOCAL_MyCamera );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    drawSphereTurtle();
    glPopMatrix();
    
    glutSwapBuffers();
}

void parseCommand(char* strCommandParse) {
    char *strToken0;
    char *strToken1;
    double val;
    strToken0 = strtok(strCommandParse, " ");
    while ((strToken1 = strtok(NULL, " ")) != NULL) {
        val = atof(strToken1);
        if (!strcmp("fd", strToken0)) { // FORWARD
            glTranslatef(0.0, 0.0, val);
        } else if (!strcmp("bk", strToken0)) { // BACK
            glTranslatef(0.0, 0.0, -val);
        } else if (!strcmp("rt", strToken0)) { // RIGHT
            glRotatef(-val, 0., 1., 0.);
        } else if (!strcmp("lt", strToken0)) { // LEFT
            glRotatef(val, 0., 1., 0.);
        } else if (!strcmp("up", strToken0)) { // UP
            glRotatef(val, 1., 0., 0.);
        } else if (!strcmp("dn", strToken0)) { // DOWN
            glRotatef(-val, 1., 0., 0.);
        }
        strToken0 = strtok(NULL, " ");
        display();
    }
    // EXIT COMMAND MODE
    if (strToken0 != NULL && strncmp(strToken0, "exit", 4) == 0) {
        command = false;
        // HOME
    } else if (strToken0 != NULL && !strcmp("home", strToken0)) {
        glLoadIdentity();
    }
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	SetGLAspectRatioCamera( LOCAL_MyCamera );
}

void keyboard(unsigned char key, int x, int y) {
    if (command) {
        if (key == 13) {
            strcat(strCommand, " ");
            if (strlen(strCommand) == 1) command = false;
            parseCommand(strCommand);
            strcpy(strCommand, "");
        } else {
            char strKey[2] = " ";
            strKey[0] = key;
            printf(strKey);
            strcat(strCommand, strKey);
        }
    } else { // not in command mode
        switch (key) {
            case 'h':
                printf("help\n\n");
                printf("c - Toggle culling\n");
                printf("q/escape - Quit\n\n");
                break;
            case 'c':
                if (glIsEnabled(GL_CULL_FACE))
                    glDisable(GL_CULL_FACE);
                else
                    glEnable(GL_CULL_FACE);
                break;
            case '1':
                glRotatef(1.0, 1., 0., 0.);
                break;
            case '2':
                glRotatef(1.0, 0., 1., 0.);
                break;
            case 'i':
                command = true;
                break;
            case 'q':
                exit(0);
                break;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);    

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("tortuga");

    //glEnable(GL_COLOR_MATERIAL);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    LOCAL_MyCamera = CreatePositionCamera(0.0f, 1.0f, -3.0f);
	glutSpecialFunc(SpecialKey);
	glutPassiveMotionFunc(MouseMotion);
	glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}