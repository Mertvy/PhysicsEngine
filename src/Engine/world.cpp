//
// Created by Nicholas Weiss on 7/18/2023.
//
#include <iostream>
#include "world.h"
#include "../Render/render.h"
#include <vector>
#include "collision.h"
#include <math.h>

Object::Object(Vector3D* position, Vector3D* velocity, Vector3D* force, float mass) {
        this->position = position;
        this->velocity = velocity;
        this->force = force;
        this->mass = mass;
}
Object::~Object(){
        delete this->position;
        delete this->velocity;
        delete this->force;
}


Circle::Circle(Vector3D* position, Vector3D* velocity, Vector3D* force, float mass, float radius)
        : Object(position, velocity, force, mass){
    this->radius = radius;
}

void Circle::collide(Object *obj) {
    if (auto cir2 = dynamic_cast<Circle*>(obj)) {
        Circle* cir1 = this;
        circleCircleCollision(cir1, cir2);
    }
    else if (auto line = dynamic_cast<LineSegment*>(obj)) {
        Circle* cir = this;
        circleLineCollision(cir, line);
    }
}

LineSegment::LineSegment(Vector3D* start, Vector3D* end, Vector3D* velocity, Vector3D* force, float mass)
             : Object(new Vector3D(end->x+start->x/2.0, end->y+start->y/2.0, end->z+start->z/2.0), velocity, force, mass) {
    this->start = start;
    this->end = end;
}

void LineSegment::collide(Object *obj) {
    if (auto cir = dynamic_cast<Circle*>(obj)) {
        LineSegment* line = this;
        circleLineCollision(cir, line);
    }
    else if (auto line2 = dynamic_cast<LineSegment*>(obj)) {
        LineSegment* line1 = this;
        lineLineCollision(line1, line2);
    }
}

World::World(float dt, Vector3D* gravity) {
    this->dt = dt;
    this->gravity = gravity;
}

void World::addObject(Object *obj) {
    objects.push_back(obj);
}

void World::removeObject(Object *obj) {
    for (int i = 0; i < objects.size(); i++) {
        if (obj == objects[i]) {
            objects.erase(objects.begin() + i);
        }
    }
}

void World::updateObject(Object *obj, float dt) {

    Vector3D* dPos = new Vector3D(obj->velocity);
    dPos->scale(dt);
    Vector3D* dVel = new Vector3D(obj->force);
    dVel->scale((dt)/(obj->mass));
    obj->position->add(dPos);
    obj->velocity->add(dVel);
    obj->force->x = obj->mass * gravity->x;
    obj->force->y = obj->mass * gravity->y;
    obj->force->z = obj->mass * gravity->z;
    delete dPos;
    delete dVel;

}

void World::update() {
    for (Object *obj: objects) {
        updateObject(obj, dt);
    }
    airresistance();
}

void World::draw(){
    for(Object *obj: objects){
        if(auto cir = dynamic_cast<Circle*>(obj)){
            drawCircle(cir->position->x, cir->position->y, cir->radius);
        }
        else if(auto line = dynamic_cast<LineSegment*>(obj)){
            drawLine(line->start->x, line->start->y, 0, line->end->x, line->end->y, 0);
        }
    }
}

void World::airresistance(){
    for(Object *obj: objects){
        if(auto cir = dynamic_cast<Circle*>(obj)){
            float resist = 0.5*pow(cir->velocity->magnitude, 2)*((cir->radius*3.1415926)/2) * .000005; //drag coefficient and fluid density small
            Vector3D* velcopy = new Vector3D(cir->velocity->x, cir->velocity->y, cir->velocity->z);
            velcopy->scale(-1);
            velcopy->scale(resist);
            cir->force->add(velcopy);
            delete velcopy;
        }
    }
}
