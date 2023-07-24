//
// Created by Alex on 7/23/2023.
//
#include <GL/glut.h>
#include "render.h"
#include <math.h>

//add object to world and such
void createObject(float x, float y, float z, float mass, World world){
    Vector3D* pos = new Vector3D(x, y,z);
    Vector3D* vel = new Vector3D(0, 0,0);
    Vector3D* force = new Vector3D(0, 0,0);
    Object* obj = new Object(pos, vel, force, mass);
    world.addObject(obj);
}

//should draw circle when mouse clicked
void mouse(int button, int state, int x, int y){
    bool check;
    if(button == GLUT_LEFT_BUTTON){
        check = true;
    }
    if(button == GLUT_RIGHT_BUTTON){
        check = false;
    }
    if(check == true){
        drawCircle(x, y, 50);
    }
}

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int theta = 0; theta < 360; theta++) {
        glVertex2f(r * cos(theta) + cx, r * sin(theta) + cy);
    }
    glEnd();
}

