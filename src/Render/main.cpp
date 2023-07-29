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

Vector3D* grav = new Vector3D(0, -0.5, 0);
World* world = new World(1, grav);

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

void display(){
    //clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //draw
    world->draw();
    glBegin(GL_LINES);
    glVertex2f(500, 500);
    glVertex2f(500, -500);
    glVertex2f(500, -500);
    glVertex2f(-500, -500);
    glVertex2f(-500, -500);
    glVertex2f(-500, 500);
    glVertex2f(-500, 500);
    glVertex2f(500, 500);
    glEnd();
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
    world->update();

}

void mouse(int button, int state, int x, int y) {
    if(button == 0 && state == 0) {
        createObject((float)x - 960,(float)-y + 540, 0,5,world);
    }
}