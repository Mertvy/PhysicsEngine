//
// Created by Alex on 7/20/2023.
//

#include <GL/glut.h>
#include <math.h>
#include <cstdio>
#include "../util/Vector3D.h"
#include "render.h"


void display();
void reshape(int, int);
void timer(int);
void drawCircle(float, float, float);
void mouse(int, int , int , int);

const float PI = 3.141592653;
const float dt = 1000/60;


int main(int argc, char**argv){
    //initialize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1920,1080);

    glutCreateWindow("Physics Engine");

    //callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    //loop
    glutMainLoop();
}

float x_pos =0, y_pos= 0, r=50, m=5;
int circles = 0;

void display(){
    //clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //draw
    for(int i = 0; i <= circles; i++){
        drawCircle(x_pos, y_pos, r);
        i++;
    }
    //display
    glutSwapBuffers();
};

void reshape(int width, int height){
    glViewport(0, 0, width, height); //window resize
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960, 960, -540, 540); //coordinate plane
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    //here is where to update x and y
    r++;
}

//should draw circle when mouse clicked
//this doesnt fucking work get this shit checked
void mouse(int button, int state, int x, int y){
    printf("%d, %d, %d, %d\n", button, state, x, y);
    if(button == 0 && state == 0){
        x_pos = x-960;
        y_pos = -y+540;
        r = 50;
        circles++;
    }

}
