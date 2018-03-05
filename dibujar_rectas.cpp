
/* 
 * File:   dibujo_lineas.cpp
 * Author: camilojcr
 * Camilo José Cruz Rivera 1428907
 *
 * Created on 27 de febrero de 2018, 13:21
 */
//


#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <utility>
#include <cstdio>
using namespace std;

typedef pair<GLfloat,GLfloat> par;
typedef vector<par> vect;

GLfloat x1=0,y1=0,x2=0,y2=0;
vect points;
int opcion;

void display(void) {
     glClear(GL_COLOR_BUFFER_BIT);

     glBegin(GL_POINTS);
	 glColor3f ( 0.0f, 1.0f, 1.0f );
	 for(int i = 0; i < points.size(); i++){
	 	glVertex2f(points[i].first, points[i].second);	
	 }

	 glColor3f ( 1.0f, 0.0f, 1.0f );
	 glVertex2f(x1, y1);
	 glVertex2f(x2, y2);
     glEnd(); 
     glFlush();
}


void incremental(){
	GLfloat y, dy, dx, m;
	dy = y2 - y1;
	dx = x2 - x1;
	if(dx != 0) m = dy/dx;
	if(abs(m) > 1 || dx == 0){
		m = dx/dy;
	}
	m /= 10;
	y = y1;
	for(GLfloat x = x1; x <= x2; x += 0.0015625f){
		points.push_back(par(x,y));		
		y = y + m/64.0;
	}

	if(x1 == x2){
		for(y = y1; y <= y2; y += 0.0015625f){
			points.push_back(par(x1,y));
			y = y + m/64.0;
		}
	}
}

void puntoMedio(){
	GLfloat y, dy, dx, m, d, increm, increm2, x;
	dx = x2 - x1;
	dy = y2 - y1;
	d = 2 * dy - dx;
	increm = 2 * dy;
	increm2 = 2 * (dy-dx);
	x = x1;
	y = y1;
	points.push_back(par(x,y));
	while(x + 0.01f < x2 || y + 0.01f < y2){
		if(x1 == x2){
			y  = y + 0.01f;
			points.push_back(par(x,y));
			continue;
		}

		if(d <= 0.0f){
			d += increm;
			x = x + 0.01f;
		}else{
			d += increm2;
			x = x + 0.01f;
			y = y + 0.01f;
		}
		points.push_back(par(x,y));
	}
}


int main(int argc, char* argv[]) {

	cout << "***********************************" << endl;
    cout << "**** SISTEMA DE LINEAS SIMPLES ****" << endl;
    cout << "***********************************" << endl << endl;
    
    cout << "El siguiente sistema permite El dibujo de una linea sencilla entre dos puntos"<< endl;
    cout << "Utilizando uno de los dos siguientes algoritmos: INCREMENTAL O PUNTO MEDIO " <<endl <<endl;


    string titulo = "("+string(argv[1]) +","+ string(argv[2]) +") - ("+ string(argv[3]) +","+ string(argv[4]) + ")";

    x1 = atof(argv[1]);
    y1 = atof(argv[2]);
    x2 = atof(argv[3]);
    y2 = atof(argv[4]);
    
    points.clear();   

    int respuesta = 1;
    do{
        if(respuesta != 1 and respuesta != 2){
            cout << "RESPUESTA NO VALIDA" << endl;
        }

    	cout << "Seleccione el algoritmo a utilizar" << endl;
    	cout << "1. Algoritmo Incremental" << endl;
    	cout << "2. Algoritmo de punto medio" << endl;
    	cin >> respuesta;
    
    }while(respuesta != 1 and respuesta != 2);

    if(respuesta == 1){
        incremental();
    }else if(respuesta  == 2){
        puntoMedio();
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow(titulo.c_str());
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}