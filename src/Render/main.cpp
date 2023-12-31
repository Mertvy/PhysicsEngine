//
// Created by Alex on 7/20/2023.
//

#include <GL/glut.h>
#include <math.h>
#include <cstdio>
#include <iostream>
#include "../util/Vector3D.h"
#include "render.h"
#include "collision.h"
#include <stdlib.h>

void display();
void reshape(int, int);
void timer(int);
void drawCircle(float, float, float);
void mouse(int, int , int , int);

Vector3D* grav = new Vector3D(0, -0.5, 0);
World* world = new World(.75, grav);

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
    for (int frame = 0; frame < 7; frame++) {
        for (int i = 0; i < world->objects.size(); i++) {
            for (int j = i + 1; j < world->objects.size(); j++) {
                if (auto cir = dynamic_cast<Circle *>(world->objects[i])) {
                    cir->collide(world->objects[j]);
                } else if (auto line = dynamic_cast<LineSegment *>(world->objects[i])) {
                    line->collide(world->objects[j]);
                }
            }
        }
    }
    world->update();
}

float drawline[4]; // for mouse
int counter = 0;

void mouse(int button, int state, int x, int y) {
    if(button == 0 && state == 0) {
        createCircle((float)x - 960,(float)-y + 540, 0,rand()%50+50, rand()%50+50, world);
    }
    else if(button == 1 && state == 0){
        createLine(900, 500, 0, 900, -500, 0, 5, world);
        createLine(900, -500, 0, -900, -500, 0, 5, world);
        createLine(-900, -500, 0, -900, 500, 0, 5, world);
        createLine(-900, 500, 0, 900, 500, 0, 5, world);
    }
    else if(button == 2 && state == 0){
        if(counter == 1){
            createLine(drawline[0], drawline[1], 0, (float)x - 960, (float)-y + 540, 0, 5, world);
            counter = 0;
        }else if(counter ==0){
            drawline[0] = (float)x - 960;
            drawline[1] = (float)-y + 540;
            counter++;
        }
    }
}