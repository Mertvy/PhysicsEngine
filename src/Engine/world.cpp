//
// Created by Nicholas Weiss on 7/18/2023.
//

#include "world.h"
#include <vector>

struct Object {
    Vector3D* position;
    Vector3D* velocity;
    Vector3D* force;
    float mass;

    Object(Vector3D* position, Vector3D* velocity, Vector3D* force, float mass) {
        this->position = position;
        this->velocity = velocity;
        this->force = force;
        this->mass = mass;
    }
    ~Object() {
        delete this->position;
        delete this->velocity;
        delete this->force;
    }
};

World::World(float dt, Vector3D* gravity) {
    this->dt = dt;
    this-> gravity = gravity;
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
    dVel->scale(dt/obj->mass);

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
