//
// Created by Alex on 7/20/2023.
//

#include <GL/glut.h>
#include <math.h>

void display();
void reshape(int, int);
void timer(int);
void drawCircle(float, float, float);
const float PI = 3.141592653;

int main(int argc, char**argv){
    //initialize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(500,500);
    glutInitWindowSize(500,500);

    glutCreateWindow("New Window");

    //callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    //loop
    glutMainLoop();
}
//test circle animation
float x_pos = 0;

void display(){
    //clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //draw
    drawCircle(x_pos, 0, 10);

    //display
    glutSwapBuffers();
};

void reshape(int width, int height){
    glViewport(0, 0, width, height); //window resize
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100); //coordinate plane
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(100/60, timer,0);
    x_pos += 1;
    if(x_pos > 100){
        x_pos = -100;
    }
}

void drawCircle(float cx, float cy, float r){

    glBegin(GL_POLYGON);
    for(int theta = 0; theta < 360; theta ++){
        glVertex2f(r*cos(theta)+cx, r*sin(theta)+cy);
    }
    glEnd();

}