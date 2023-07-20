//
// Created by Alex on 7/20/2023.
//

#include <GL/glut.h>
#include <math.h>
#include "world.cpp"
#include "../util/Vector3D.cpp"


void display();
void reshape(int, int);
void timer(int);
void drawCircle(float, float, float);

const float PI = 3.141592653;
const float dt = 1000/60;


int main(int argc, char**argv){
    //initialize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1920,1080);

    glutCreateWindow("New Window");

    //callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    //loop
    glutMainLoop();
}

float x_pos =0, y_pos= 0, r=50, m=5;

void display(){
    //clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //draw
    drawCircle(x_pos, y_pos, r);

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
    //here is where to update x and y coordinates

}

void drawCircle(float cx, float cy, float r){
    glBegin(GL_POLYGON);
    for(int theta = 0; theta < 360; theta++){
        glVertex2f(r*cos(theta)+cx, r*sin(theta)+cy);
    }
    glEnd();
}