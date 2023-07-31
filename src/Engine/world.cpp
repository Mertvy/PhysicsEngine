//
// Created by Nicholas Weiss on 7/18/2023.
//
#include <iostream>
#include "world.h"
#include "../Render/render.h"
#include <vector>
#include "collision.h"

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
    delete dPos;
    delete dVel;

}

void World::update() {
    for (Object *obj: objects) {
        updateObject(obj, dt);
    }
}

void World::draw(){
    for(Object *obj: objects){
        drawCircle(obj->position->x, obj->position->y, 50);
    }
}
