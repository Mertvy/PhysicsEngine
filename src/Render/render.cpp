//
// Created by Alex on 7/23/2023.
//
#include <GL/glut.h>
#include "render.h"
#include <math.h>
#include <iostream>
//add object to world and such
void createObject(float x, float y, float z, float mass, World* world){
    Vector3D* pos = new Vector3D(x, y, z);
    Vector3D* vel = new Vector3D(0, 0,0);
    Vector3D* force = new Vector3D(0, 0,0);
    force->x = world->gravity->x * mass;
    force->y = world->gravity->y * mass;
    force->z = world->gravity->z * mass;
    Object* obj = new Object(pos, vel, force, mass);
    world->addObject(obj);
}

void createCircle(float x, float y, float z, float mass, float r, World* world){
    Vector3D* pos = new Vector3D(x, y, z);
    Vector3D* vel = new Vector3D(0, 0,0);
    Vector3D* force = new Vector3D(0, 0,0);
    force->x = world->gravity->x * mass;
    force->y = world->gravity->y * mass;
    force->z = world->gravity->z * mass;
    Circle* cir = new Circle(pos, vel, force, mass, r);
    world->addObject(cir);
}


void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int theta = 0; theta < 360; theta++) {
        glVertex2f(r * cos(theta) + cx, r * sin(theta) + cy);
    }
    glEnd();
}


