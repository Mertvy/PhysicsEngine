//
// Created by Nicholas Weiss on 7/18/2023.
//
#include <iostream>
#include "world.h"
#include "../Render/render.h"
#include <vector>

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
        double distance = sqrt(pow((cir1->position->x - cir2->position->x), 2) +
                               pow((cir1->position->y - cir2->position->y), 2) +
                               pow((cir1->position->z - cir2->position->z), 2));
        if (distance >= cir1->radius + cir2->radius) return;
        Vector3D* direction = new Vector3D(cir1->position->x - cir2->position->x,
                                           cir1->position->y - cir2->position->y,
                                           cir1->position->z - cir2->position->z);
        direction->scale(1/sqrt(pow(direction->x, 2) + pow(direction->y, 2) + pow(direction->z, 2)));
        cir1->force->add(direction);
        direction->scale(-1);
        cir2->force->add(direction);
        delete direction;
    }
    else if (auto line = dynamic_cast<LineSegment*>(obj)) {
        float u = line->end->x - line->start->x;
        float v = line->end->y - line->start->y;
        float w = line->end->z - line->start->z;
        float a = this->position->x;
        float b = this->position->y;
        float c = this->position->z;
        float X = line->start->x - a;
        float Y = line->start->y - b;
        float Z = line->start->z - c;
        float square = u*u + v*v + w*w;
        float linear = X*u + Y*v + Z*w;
        float constant = X*X + Y*Y + Z*Z - this->radius*this->radius;
        float discriminant = linear*linear - 4 * square * constant;
        if (discriminant <= 0) return;
        float t = ((-linear) + sqrt(discriminant))/(2*square);
        if (t > 1) return;
        Vector3D* slopeVec = new Vector3D(u, v, w)
        Vector3D* cirToStart = line->start->subtract(this->position);
        float projScalar = slopeVec->dot(cirToStart)/(slopeVec->magnitude*slopeVec->magnitude);
        slopeVec->scale(projScalar);
        Vector3D* direction
        delete slopeVec;
        delete cirToStart;
    }
}

LineSegment::LineSegment(Vector3D* start, Vector3D* end, Vector3D* velocity, Vector3D* force, float mass)
             : Object(new Vector3D(end->x+start->x/2.0, end->y+start->y/2.0, end->z+start->z/2.0), velocity, force, mass) {

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
