//
// Created by Nicholas Weiss on 7/18/2023.
//

#include "world.h"
#include <vector>

struct Object {
    float position[3];
    float velocity[3];
    float force[3];
    float mass;
};

class World {
private:
    std::vector<Object*> objects;
    float timeStep;
public:
    World(float timeStep) {
        this->timeStep = timeStep;
    }

    void addObject(Object *obj) {
        objects.push_back(obj);
    }

    void removeObject(Object *obj) {
        for (int i = 0; i < objects.size(); i++) {
            if (obj == objects[i]) {
                objects.erase(objects.begin() + i);
            }
        }
    }

    void updateObject(Object *obj, float dt) {
        obj->position[0] += obj->velocity[0] * dt;
        obj->position[1] += obj->velocity[1] * dt;
        obj->position[2] += obj->velocity[2] * dt;

        obj->velocity[0] += obj->force[0] * dt / obj->mass;
        obj->velocity[1] += obj->force[1] * dt / obj->mass;
        obj->velocity[2] += obj->force[2] * dt / obj->mass;
    }

    void update() {
        for (Object *obj: objects) {
            updateObject(obj, timeStep);
        }
    }
};
