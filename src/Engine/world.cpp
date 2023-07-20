//
// Created by Nicholas Weiss on 7/18/2023.
//

#include "world.h"
#include "../util/Vector3D.h"
#include <vector>

struct Object {
    Vector3D* position;
    Vector3D* velocity;
    Vector3D* force;
    float mass;
};

class World {
private:
    std::vector<Object*> objects;
    float dt;
public:
    World(float dt) {
        this->dt = dt;
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

        Vector3D* dPos = new Vector3D(obj->velocity);
        dPos->scale(dt);

        Vector3D* dVel = new Vector3D(obj->force);
        dVel->scale(dt/obj->mass);

        obj->position->add(dPos);
        obj->velocity->add(dVel);

        delete dPos;
        delete dVel;
    }

    void update() {
        for (Object *obj: objects) {
            updateObject(obj, dt);
        }
    }
};
